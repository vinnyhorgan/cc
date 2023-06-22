#include "math.h"

#include <raymath.h>
#include <reasings.h>
#include <FastNoiseLite.h>
#include <spdlog/spdlog.h>

// Variables
FastNoiseLite fastnoiselite;
math::NoiseType noiseType = math::NoiseType::OpenSimplex;
int noiseSeed = 1337;
float noiseFrequency = 0.01f;
int randomSeed = 0;

namespace math
{
    // Types

    // Vector
    std::string Vector::type()
    {
        return "Vector";
    }

    Vector Vector::add(Vector other)
    {
        Vector2 result = Vector2Add(toVector2(), other.toVector2());
        return Vector{result.x, result.y};
    }

    Vector Vector::add(float value)
    {
        Vector2 result = Vector2AddValue(toVector2(), value);
        return Vector{result.x, result.y};
    }

    Vector Vector::sub(Vector other)
    {
        Vector2 result = Vector2Subtract(toVector2(), other.toVector2());
        return Vector{result.x, result.y};
    }

    Vector Vector::sub(float value)
    {
        Vector2 result = Vector2SubtractValue(toVector2(), value);
        return Vector{result.x, result.y};
    }

    Vector Vector::scale(float scale)
    {
        Vector2 result = Vector2Scale(toVector2(), scale);
        return Vector{result.x, result.y};
    }

    Vector Vector::mul(Vector other)
    {
        Vector2 result = Vector2Multiply(toVector2(), other.toVector2());
        return Vector{result.x, result.y};
    }

    Vector Vector::div(Vector other)
    {
        Vector2 result = Vector2Divide(toVector2(), other.toVector2());
        return Vector{result.x, result.y};
    }

    Vector Vector::normalize()
    {
        Vector2 result = Vector2Normalize(toVector2());
        return Vector{result.x, result.y};
    }

    Vector Vector::rotate(float angle)
    {
        Vector2 result = Vector2Rotate(toVector2(), angle);
        return Vector{result.x, result.y};
    }

    float Vector::length()
    {
        return Vector2Length(toVector2());
    }

    float Vector::distance(Vector other)
    {
        return Vector2Distance(toVector2(), other.toVector2());
    }

    float Vector::dot(Vector other)
    {
        return Vector2DotProduct(toVector2(), other.toVector2());
    }

    float Vector::angle(Vector other)
    {
        return Vector2Angle(toVector2(), other.toVector2());
    }

    Vector2 Vector::toVector2()
    {
        return Vector2{x, y};
    }

    // Functions

    // Utility
    sol::table registerMathAPI(sol::state& lua)
    {
        lua.new_enum<NoiseType>("NoiseType", {
            {"OpenSimplex", NoiseType::OpenSimplex},
            {"Perlin", NoiseType::Perlin}
        });

        lua.new_enum<TweenType>("TweenType", {
            {"Linear", TweenType::Linear},
            {"LinearIn", TweenType::LinearIn},
            {"LinearOut", TweenType::LinearOut},
            {"LinearInOut", TweenType::LinearInOut},
            {"SineIn", TweenType::SineIn},
            {"SineOut", TweenType::SineOut},
            {"SineInOut", TweenType::SineInOut},
            {"CircularIn", TweenType::CircularIn},
            {"CircularOut", TweenType::CircularOut},
            {"CircularInOut", TweenType::CircularInOut},
            {"CubicIn", TweenType::CubicIn},
            {"CubicOut", TweenType::CubicOut},
            {"CubicInOut", TweenType::CubicInOut},
            {"QuadraticIn", TweenType::QuadraticIn},
            {"QuadraticOut", TweenType::QuadraticOut},
            {"QuadraticInOut", TweenType::QuadraticInOut},
            {"ExponentialIn", TweenType::ExponentialIn},
            {"ExponentialOut", TweenType::ExponentialOut},
            {"ExponentialInOut", TweenType::ExponentialInOut},
            {"BackIn", TweenType::BackIn},
            {"BackOut", TweenType::BackOut},
            {"BackInOut", TweenType::BackInOut},
            {"BounceIn", TweenType::BounceIn},
            {"BounceOut", TweenType::BounceOut},
            {"BounceInOut", TweenType::BounceInOut},
            {"ElasticIn", TweenType::ElasticIn},
            {"ElasticOut", TweenType::ElasticOut},
            {"ElasticInOut", TweenType::ElasticInOut}
        });

        sol::usertype<Vector> vectorType = lua.new_usertype<Vector>("Vector");

        vectorType["x"] = &Vector::x;
        vectorType["y"] = &Vector::y;
        vectorType["type"] = &Vector::type;
        vectorType["add"] = sol::overload(sol::resolve<Vector(Vector)>(&Vector::add), sol::resolve<Vector(float)>(&Vector::add));
        vectorType["sub"] = sol::overload(sol::resolve<Vector(Vector)>(&Vector::sub), sol::resolve<Vector(float)>(&Vector::sub));
        vectorType["scale"] = &Vector::scale;
        vectorType["mul"] = &Vector::mul;
        vectorType["div"] = &Vector::div;
        vectorType["normalize"] = &Vector::normalize;
        vectorType["rotate"] = &Vector::rotate;
        vectorType["length"] = &Vector::length;
        vectorType["distance"] = &Vector::distance;
        vectorType["dot"] = &Vector::dot;
        vectorType["angle"] = &Vector::angle;

        sol::table math = lua.create_table();

        math["clamp"] = clamp;
        math["getNoiseFrequency"] = getNoiseFrequency;
        math["getNoiseType"] = getNoiseType;
        math["getNoiseSeed"] = getNoiseSeed;
        math["getRandomSeed"] = getRandomSeed;
        math["lerp"] = lerp;
        math["newVector2"] = newVector2;
        math["noise"] = sol::overload(sol::resolve<float(float, float)>(noise), sol::resolve<float(float, float, float)>(noise));
        math["normalize"] = normalize;
        math["random"] = sol::overload(sol::resolve<float()>(random), sol::resolve<int(int)>(random), sol::resolve<int(int, int)>(random));
        math["remap"] = remap;
        math["setNoiseFrequency"] = setNoiseFrequency;
        math["setNoiseType"] = setNoiseType;
        math["setNoiseSeed"] = setNoiseSeed;
        math["setRandomSeed"] = setRandomSeed;
        math["tween"] = sol::overload(sol::resolve<float(float, float, float, float)>(tween), sol::resolve<float(float, float, float, float, TweenType)>(tween));
        math["wrap"] = wrap;

        return math;
    }

    // API
    float clamp(float value, float min, float max)
    {
        return Clamp(value, min, max);
    }

    float getNoiseFrequency()
    {
        return noiseFrequency;
    }

    NoiseType getNoiseType()
    {
        return noiseType;
    }

    int getNoiseSeed()
    {
        return noiseSeed;
    }

    int getRandomSeed()
    {
        return randomSeed;
    }

    float lerp(float start, float end, float amount)
    {
        return Lerp(start, end, amount);
    }

    Vector newVector2()
    {
        return Vector{ 0, 0 };
    }

    float noise(float x, float y)
    {
        return fastnoiselite.GetNoise(x, y);
    }

    float noise(float x, float y, float z)
    {
        return fastnoiselite.GetNoise(x, y, z);
    }

    float normalize(float value, float start, float end)
    {
        return Normalize(value, start, end);
    }

    float random()
    {
        return GetRandomValue(0, 100) / 100.0f;
    }

    int random(int max)
    {
        return GetRandomValue(1, max);
    }

    int random(int min, int max)
    {
        return GetRandomValue(min, max);
    }

    float remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd)
    {
        return Remap(value, inputStart, inputEnd, outputStart, outputEnd);
    }

    void setNoiseFrequency(float frequency)
    {
        noiseFrequency = frequency;
        fastnoiselite.SetFrequency(frequency);
    }

    void setNoiseType(NoiseType type)
    {
        noiseType = type;
        fastnoiselite.SetNoiseType((FastNoiseLite::NoiseType)type);
    }

    void setNoiseSeed(int seed)
    {
        noiseSeed = seed;
        fastnoiselite.SetSeed(seed);
    }

    void setRandomSeed(int seed)
    {
        SetRandomSeed(seed);
    }

    float tween(float timer, float start, float end, float durationInSeconds)
    {
        return EaseLinearNone(timer, start, end - start, durationInSeconds);
    }

    float tween(float timer, float start, float end, float durationInSeconds, TweenType type)
    {
        switch (type)
        {
            case TweenType::Linear:
                return EaseLinearNone(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::LinearIn:
                return EaseLinearIn(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::LinearOut:
                return EaseLinearOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::LinearInOut:
                return EaseLinearInOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::SineIn:
                return EaseSineIn(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::SineOut:
                return EaseSineOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::SineInOut:
                return EaseSineInOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::CircularIn:
                return EaseCircIn(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::CircularOut:
                return EaseCircOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::CircularInOut:
                return EaseCircInOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::CubicIn:
                return EaseCubicIn(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::CubicOut:
                return EaseCubicOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::CubicInOut:
                return EaseCubicInOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::QuadraticIn:
                return EaseQuadIn(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::QuadraticOut:
                return EaseQuadOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::QuadraticInOut:
                return EaseQuadInOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::ExponentialIn:
                return EaseExpoIn(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::ExponentialOut:
                return EaseExpoOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::ExponentialInOut:
                return EaseExpoInOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::BackIn:
                return EaseBackIn(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::BackOut:
                return EaseBackOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::BackInOut:
                return EaseBackInOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::BounceIn:
                return EaseBounceIn(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::BounceOut:
                return EaseBounceOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::BounceInOut:
                return EaseBounceInOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::ElasticIn:
                return EaseElasticIn(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::ElasticOut:
                return EaseElasticOut(timer, start, end - start, durationInSeconds);
                break;
            case TweenType::ElasticInOut:
                return EaseElasticInOut(timer, start, end - start, durationInSeconds);
                break;
            default:
                break;
        }

        return 0;
    }

    float wrap(float value, float min, float max)
    {
        return Wrap(value, min, max);
    }
}
