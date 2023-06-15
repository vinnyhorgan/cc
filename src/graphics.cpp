#include "graphics.h"

namespace graphics
{
    void registerGraphicsFunctions(sol::state& lua)
    {
        sol::table graphics = lua.create_table();

        graphics["loadTexture"] = graphics::loadTexture;
        graphics["unloadTexture"] = graphics::unloadTexture;
        graphics["drawTexture"] = graphics::drawTexture;

        lua["graphics"] = graphics;
    }

    Texture loadTexture(std::string path)
    {
        return LoadTexture(path.c_str());
    }

    void unloadTexture(Texture texture)
    {
        UnloadTexture(texture);
    }

    void drawTexture(Texture texture, int posX, int posY)
    {
        DrawTexture(texture, posX, posY, WHITE);
    }
}
