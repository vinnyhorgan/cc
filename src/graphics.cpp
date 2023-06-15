#include "graphics.h"

namespace graphics
{
    std::tuple<int, int> Image::getSize()
    {
        return std::make_tuple(texture.width, texture.height);
    }

    int Image::getWidth()
    {
        return texture.width;
    }

    int Image::getHeight()
    {
        return texture.height;
    }

    int Image::getMipmaps()
    {
        return texture.mipmaps;
    }

    std::string Image::getFilter()
    {
        switch (filter)
        {
            case TEXTURE_FILTER_POINT:
                return "point";
            case TEXTURE_FILTER_BILINEAR:
                return "bilinear";
        }
    }

    std::string Image::getWrap()
    {
        switch (wrap)
        {
            case TEXTURE_WRAP_REPEAT:
                return "repeat";
            case TEXTURE_WRAP_CLAMP:
                return "clamp";
            case TEXTURE_WRAP_MIRROR_REPEAT:
                return "mirror_repeat";
            case TEXTURE_WRAP_MIRROR_CLAMP:
                return "mirror_clamp";
        }
    }

    void Image::setFilter(std::string filter)
    {
        if (filter == "point")
        {
            this->filter = TEXTURE_FILTER_POINT;
        }
        else if (filter == "bilinear")
        {
            this->filter = TEXTURE_FILTER_BILINEAR;
        }
    }

    void Image::setWrap(std::string wrap)
    {
        if (wrap == "repeat")
        {
            this->wrap = TEXTURE_WRAP_REPEAT;
        }
        else if (wrap == "clamp")
        {
            this->wrap = TEXTURE_WRAP_CLAMP;
        }
        else if (wrap == "mirror_repeat")
        {
            this->wrap = TEXTURE_WRAP_MIRROR_REPEAT;
        }
        else if (wrap == "mirror_clamp")
        {
            this->wrap = TEXTURE_WRAP_MIRROR_CLAMP;
        }
    }

    void Image::unload()
    {
        UnloadTexture(texture);
    }

    void registerGraphicsAPI(sol::state& lua)
    {
        sol::usertype<Image> image_type = lua.new_usertype<Image>("Image");

        image_type["getSize"] = &Image::getSize;
        image_type["getWidth"] = &Image::getWidth;
        image_type["getHeight"] = &Image::getHeight;
        image_type["getMipmaps"] = &Image::getMipmaps;
        image_type["getFilter"] = &Image::getFilter;
        image_type["getWrap"] = &Image::getWrap;
        image_type["setFilter"] = &Image::setFilter;
        image_type["setWrap"] = &Image::setWrap;
        image_type["unload"] = &Image::unload;

        sol::table graphics = lua.create_table();

        graphics["loadTexture"] = graphics::loadTexture;
        graphics["unloadTexture"] = graphics::unloadTexture;
        graphics["drawTexture"] = graphics::drawTexture;

        lua["graphics"] = graphics;
    }

    Image loadTexture(std::string path)
    {
        Image image;

        image.texture = LoadTexture(path.c_str());
        image.filter = TEXTURE_FILTER_POINT;
        image.wrap = TEXTURE_WRAP_CLAMP;

        return image;
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
