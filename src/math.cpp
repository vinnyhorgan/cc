#include "math.h"

#include <FastNoiseLite.h>

namespace math
{
    void registerMathAPI(sol::state& lua)
    {
        sol::table math = lua.create_table();

        math["random"] = sol::overload(sol::resolve<float()>(&random), sol::resolve<int(int)>(&random), sol::resolve<int(int, int)>(&random));
        math["setRandomSeed"] = &setRandomSeed;
        math["noise"] = sol::overload(sol::resolve<float(float, float)>(&noise), sol::resolve<float(float, float, float)>(&noise));

        lua["cc"]["math"] = math;
    }

    float random()
    {
        // float between 0 and 1
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

    void setRandomSeed(int seed)
    {
        SetRandomSeed(seed);
    }

    float noise(float x, float y)
    {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

        return noise.GetNoise(x, y);
    }

    float noise(float x, float y, float z)
    {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

        return noise.GetNoise(x, y, z);
    }
}
