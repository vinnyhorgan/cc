#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

#include <string>

namespace graphics
{
    class Image
    {
    public:
        Texture texture;
        TextureFilter filter;
        TextureWrap wrap;

        std::tuple<int, int> getSize();
        int getWidth();
        int getHeight();
        int getMipmaps();
        std::string getFilter();
        std::string getWrap();
        void setFilter(std::string filter);
        void setWrap(std::string wrap);
        void unload();
    };

    // Utility
    void registerGraphicsAPI(sol::state& lua);

    // API
    Image loadTexture(std::string path);
    void unloadTexture(Texture texture);
    void drawTexture(Texture texture, int posX, int posY);
}
