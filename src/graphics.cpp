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

    FilterMode Image::getFilter()
    {
        return filter;
    }

    WrapMode Image::getWrap()
    {
        return wrap;
    }

    void Image::setFilter(FilterMode filter)
    {
        this->filter = filter;

        if (filter == FilterMode::Point)
        {
            SetTextureFilter(texture, TEXTURE_FILTER_POINT);
        }
        else if (filter == FilterMode::Bilinear)
        {
            SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
        }
    }

    void Image::setWrap(WrapMode wrap)
    {
        this->wrap = wrap;

        if (wrap == WrapMode::Repeat)
        {
            SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);
        }
        else if (wrap == WrapMode::Clamp)
        {
            SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
        }
        else if (wrap == WrapMode::MirrorRepeat)
        {
            SetTextureWrap(texture, TEXTURE_WRAP_MIRROR_REPEAT);
        }
        else if (wrap == WrapMode::MirrorClamp)
        {
            SetTextureWrap(texture, TEXTURE_WRAP_MIRROR_CLAMP);
        }
    }

    void Image::unload()
    {
        UnloadTexture(texture);
    }

    void registerGraphicsAPI(sol::state& lua)
    {
        lua.new_enum<FilterMode>("FilterMode",
        {
            {"Point", FilterMode::Point},
            {"Bilinear", FilterMode::Bilinear}
        });

        lua.new_enum<WrapMode>("WrapMode",
        {
            {"Repeat", WrapMode::Repeat},
            {"Clamp", WrapMode::Clamp},
            {"MirrorRepeat", WrapMode::MirrorRepeat},
            {"MirrorClamp", WrapMode::MirrorClamp}
        });

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
        image.setFilter(FilterMode::Point);
        image.setWrap(WrapMode::Clamp);

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
