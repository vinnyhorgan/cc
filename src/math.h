#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

namespace math
{
    // Functions

    // Utility
    void registerMathAPI(sol::state& lua);

    // API
    float random();
    int random(int max);
    int random(int min, int max);
    void setRandomSeed(int seed);
    float noise(float x, float y);
    float noise(float x, float y, float z);
}
