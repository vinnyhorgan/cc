#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

namespace networking
{
    // Functions

    // Utility
    void registerNetworkingAPI(sol::state& lua);

    // API
    std::string httpGet(std::string url);
}
