#pragma once

#include <string>
#include <sol/sol.hpp>
#include <raylib.h>

namespace graphics
{
    // Utility
    void registerGraphicsFunctions(sol::state& lua);

    // API
    Texture loadTexture(std::string path);
    void unloadTexture(Texture texture);
    void drawTexture(Texture texture, int posX, int posY);
}
