#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

namespace event
{
    // Functions

    // Utility
    void registerEventAPI(sol::state& lua);
    bool shouldQuit();

    // API
    void quit();
}
