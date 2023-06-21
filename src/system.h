#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

namespace systemc // bruh
{
    enum OS
    {
        Windows,
        Linux,
        MacOS
    };

    // Functions

    // Utility
    void registerSystemAPI(sol::state& lua);

    // API
    std::string getClipboardText();
    OS getOS();
    void openURL(std::string url);
    void setClipboardText(std::string text);
}
