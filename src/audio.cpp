#include "audio.h"

std::vector<audio::Source> sources;
float currentVolume = 1.0f;

namespace audio
{
    // Types
    std::string Source::type()
    {
        return "Source";
    }

    void Source::unload()
    {
        if (sourceType == SourceType::Static)
        {
            UnloadSound(sound);
        }
        else if (sourceType == SourceType::Stream)
        {
            UnloadMusicStream(music);
        }
    }

    SourceType Source::getSourceType()
    {
        return sourceType;
    }

    int Source::getChannelCount()
    {
        if (sourceType == SourceType::Static)
        {
            return sound.stream.channels;
        }
        else if (sourceType == SourceType::Stream)
        {
            return music.stream.channels;
        }
    }

    int Source::getSampleRate()
    {
        if (sourceType == SourceType::Static)
        {
            return sound.stream.sampleRate;
        }
        else if (sourceType == SourceType::Stream)
        {
            return music.stream.sampleRate;
        }
    }

    int Source::getSampleSize()
    {
        if (sourceType == SourceType::Static)
        {
            return sound.stream.sampleSize;
        }
        else if (sourceType == SourceType::Stream)
        {
            return music.stream.sampleSize;
        }
    }

    int Source::getSampleCount()
    {
        if (sourceType == SourceType::Static)
        {
            return sound.frameCount;
        }
        else if (sourceType == SourceType::Stream)
        {
            return music.frameCount;
        }
    }

    float Source::getPitch()
    {
        return pitch;
    }

    float Source::getVolume()
    {
        return volume;
    }

    float Source::getPan()
    {
        return pan;
    }

    float Source::getDuration()
    {
        if (sourceType == SourceType::Static)
        {
            return (float)sound.frameCount / (float)sound.stream.sampleRate;
        }
        else if (sourceType == SourceType::Stream)
        {
            return GetMusicTimeLength(music);
        }
    }

    bool Source::isPlaying()
    {
        if (sourceType == SourceType::Static)
        {
            return IsSoundPlaying(sound);
        }
        else if (sourceType == SourceType::Stream)
        {
            return IsMusicStreamPlaying(music);
        }
    }

    bool Source::isLooping()
    {
        if (sourceType == SourceType::Stream)
        {
            return music.looping;
        }
        else
        {
            return false;
        }
    }

    void Source::play()
    {
        if (sourceType == SourceType::Static)
        {
            PlaySound(sound);
        }
        else if (sourceType == SourceType::Stream)
        {
            PlayMusicStream(music);
        }
    }

    void Source::pause()
    {
        if (sourceType == SourceType::Static)
        {
            PauseSound(sound);
        }
        else if (sourceType == SourceType::Stream)
        {
            PauseMusicStream(music);
        }
    }

    void Source::resume()
    {
        if (sourceType == SourceType::Static)
        {
            ResumeSound(sound);
        }
        else if (sourceType == SourceType::Stream)
        {
            ResumeMusicStream(music);
        }
    }

    void Source::stop()
    {
        if (sourceType == SourceType::Static)
        {
            StopSound(sound);
        }
        else if (sourceType == SourceType::Stream)
        {
            StopMusicStream(music);
        }
    }

    void Source::seek(float time)
    {
        if (sourceType == SourceType::Stream)
        {
            SeekMusicStream(music, time);
        }
    }

    void Source::setPitch(float pitch)
    {
        this->pitch = pitch;

        if (sourceType == SourceType::Static)
        {
            SetSoundPitch(sound, pitch);
        }
        else if (sourceType == SourceType::Stream)
        {
            SetMusicPitch(music, pitch);
        }
    }

    void Source::setVolume(float volume)
    {
        this->volume = volume;

        if (sourceType == SourceType::Static)
        {
            SetSoundVolume(sound, volume);
        }
        else if (sourceType == SourceType::Stream)
        {
            SetMusicVolume(music, volume);
        }
    }

    void Source::setPan(float pan)
    {
        this->pan = pan;

        if (sourceType == SourceType::Static)
        {
            SetSoundPan(sound, pan);
        }
        else if (sourceType == SourceType::Stream)
        {
            SetMusicPan(music, pan);
        }
    }

    void Source::setLooping(bool looping)
    {
        if (sourceType == SourceType::Stream)
        {
            music.looping = looping;
        }
    }

    void registerAudioAPI(sol::state& lua)
    {
        lua.new_enum<SourceType>("SourceType", {
            {"Static", SourceType::Static},
            {"Stream", SourceType::Stream}
        });

        sol::usertype<Source> source_type = lua.new_usertype<Source>("Source");

        source_type["type"] = &Source::type;
        source_type["unload"] = &Source::unload;
        source_type["getSourceType"] = &Source::getSourceType;
        source_type["getChannelCount"] = &Source::getChannelCount;
        source_type["getSampleRate"] = &Source::getSampleRate;
        source_type["getSampleSize"] = &Source::getSampleSize;
        source_type["getSampleCount"] = &Source::getSampleCount;
        source_type["getPitch"] = &Source::getPitch;
        source_type["getVolume"] = &Source::getVolume;
        source_type["getPan"] = &Source::getPan;
        source_type["getDuration"] = &Source::getDuration;
        source_type["isPlaying"] = &Source::isPlaying;
        source_type["isLooping"] = &Source::isLooping;
        source_type["play"] = &Source::play;
        source_type["pause"] = &Source::pause;
        source_type["resume"] = &Source::resume;
        source_type["stop"] = &Source::stop;
        source_type["seek"] = &Source::seek;
        source_type["setPitch"] = &Source::setPitch;
        source_type["setVolume"] = &Source::setVolume;
        source_type["setPan"] = &Source::setPan;
        source_type["setLooping"] = &Source::setLooping;

        sol::table audio = lua.create_table();

        audio["getActiveSourceCount"] = &getActiveSourceCount;
        audio["getVolume"] = &getVolume;
        audio["newSource"] = &newSource;
        audio["setVolume"] = &setVolume;
        audio["stopAllSources"] = &stopAllSources;

        lua["cc"]["audio"] = audio;
    }

    int getActiveSourceCount()
    {
        return sources.size();
    }

    float getVolume()
    {
        return currentVolume;
    }

    Source newSource(std::string filename, SourceType type)
    {
        Source source;

        source.sourceType = type;

        if (type == SourceType::Static)
        {
            source.sound = LoadSound(filename.c_str());
        }
        else if (type == SourceType::Stream)
        {
            source.music = LoadMusicStream(filename.c_str());
        }

        sources.push_back(source);

        return source;
    }

    void setVolume(float volume)
    {
        currentVolume = volume;

        SetMasterVolume(volume);
    }

    void stopAllSources()
    {
        for (int i = 0; i < sources.size(); i++)
        {
            sources[i].stop();
        }
    }
}
