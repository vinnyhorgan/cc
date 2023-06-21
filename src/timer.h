#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

namespace timer
{
    // Functions

    // Utility
    void registerTimerAPI(sol::state& lua);

    // API
    float getDelta();
    float getFPS();
    float getTime();
    void sleep(float seconds);
}
