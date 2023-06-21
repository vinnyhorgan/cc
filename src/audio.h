#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

namespace audio
{
    // Enums
    enum SourceType
    {
        Static,
        Stream
    };

    // Types
    class Source
    {
    public:
        SourceType sourceType;
        Sound sound;
        Music music;

        float pitch = 1.0f;
        float volume = 1.0f;
        float pan = 0.5f;

        std::string type();
        void unload();

        SourceType getSourceType();
        int getChannelCount();
        int getSampleRate();
        int getSampleSize();
        int getSampleCount();
        float getPitch();
        float getVolume();
        float getPan();
        float getDuration();
        bool isPlaying();
        bool isLooping();
        void play();
        void pause();
        void resume();
        void stop();
        void seek(float time);
        void setPitch(float pitch);
        void setVolume(float volume);
        void setPan(float pan);
        void setLooping(bool looping);
    };

    // Functions

    // Utility
    void registerAudioAPI(sol::state& lua);

    // API
    int getActiveSourceCount();
    float getVolume();
    Source newSource(std::string filename, SourceType type);
    void setVolume(float volume);
    void stopAllSources();
}
