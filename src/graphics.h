#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

#include <string>

namespace graphics
{
    enum FilterMode
    {
        Point,
        Bilinear
    };

    enum WrapMode
    {
        Repeat,
        Clamp,
        MirrorRepeat,
        MirrorClamp
    };

    class Image
    {
    public:
        Texture texture;
        FilterMode filter;
        WrapMode wrap;

        std::tuple<int, int> getSize();
        int getWidth();
        int getHeight();
        int getMipmaps();
        FilterMode getFilter();
        WrapMode getWrap();
        void setFilter(FilterMode filter);
        void setWrap(WrapMode wrap);
        void unload();
    };

    // Utility
    void registerGraphicsAPI(sol::state& lua);

    // API
    Image loadTexture(std::string path);
    void unloadTexture(Texture texture);
    void drawTexture(Texture texture, int posX, int posY);
}
