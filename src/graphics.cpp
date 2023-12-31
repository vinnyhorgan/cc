#include "graphics.h"

Color backgroundColor = BLACK;
Color color = WHITE;
Font currentFont = GetFontDefault();

namespace graphics
{
    // Types

    // Image
    std::string Image::type()
    {
        return "Image";
    }

    void Image::unload()
    {
        UnloadTexture(texture);
    }

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

    PixelFormat Image::getFormat()
    {
        return (PixelFormat)texture.format;
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
        else if (filter == FilterMode::Trilinear)
        {
            SetTextureFilter(texture, TEXTURE_FILTER_TRILINEAR);
        }
        else if (filter == FilterMode::Anisotropic4x)
        {
            SetTextureFilter(texture, TEXTURE_FILTER_ANISOTROPIC_4X);
        }
        else if (filter == FilterMode::Anisotropic8x)
        {
            SetTextureFilter(texture, TEXTURE_FILTER_ANISOTROPIC_8X);
        }
        else if (filter == FilterMode::Anisotropic16x)
        {
            SetTextureFilter(texture, TEXTURE_FILTER_ANISOTROPIC_16X);
        }
    }

    void Image::setWrap(WrapMode wrap)
    {
        this->wrap = wrap;

        if (wrap == WrapMode::Clamp)
        {
            SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
        }
        else if (wrap == WrapMode::Repeat)
        {
            SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);
        }
        else if (wrap == WrapMode::MirrorClamp)
        {
            SetTextureWrap(texture, TEXTURE_WRAP_MIRROR_CLAMP);
        }
        else if (wrap == WrapMode::MirrorRepeat)
        {
            SetTextureWrap(texture, TEXTURE_WRAP_MIRROR_REPEAT);
        }
    }

    // Font
    std::string Fontc::type()
    {
        return "Font";
    }

    void Fontc::unload()
    {
        UnloadFont(font);
    }

    int Fontc::getSize()
    {
        return font.baseSize;
    }

    // Canvas
    std::string Canvas::type()
    {
        return "Canvas";
    }

    void Canvas::unload()
    {
        UnloadRenderTexture(texture);
    }

    std::tuple<int, int> Canvas::getSize()
    {
        return std::make_tuple(texture.texture.width, texture.texture.height);
    }

    int Canvas::getWidth()
    {
        return texture.texture.width;
    }

    int Canvas::getHeight()
    {
        return texture.texture.height;
    }

    int Canvas::getMipmaps()
    {
        return texture.texture.mipmaps;
    }

    FilterMode Canvas::getFilter()
    {
        return filter;
    }

    WrapMode Canvas::getWrap()
    {
        return wrap;
    }

    PixelFormat Canvas::getFormat()
    {
        return (PixelFormat)texture.texture.format;
    }

    void Canvas::setFilter(FilterMode filter)
    {
        this->filter = filter;

        if (filter == FilterMode::Point)
        {
            SetTextureFilter(texture.texture, TEXTURE_FILTER_POINT);
        }
        else if (filter == FilterMode::Bilinear)
        {
            SetTextureFilter(texture.texture, TEXTURE_FILTER_BILINEAR);
        }
        else if (filter == FilterMode::Trilinear)
        {
            SetTextureFilter(texture.texture, TEXTURE_FILTER_TRILINEAR);
        }
        else if (filter == FilterMode::Anisotropic4x)
        {
            SetTextureFilter(texture.texture, TEXTURE_FILTER_ANISOTROPIC_4X);
        }
        else if (filter == FilterMode::Anisotropic8x)
        {
            SetTextureFilter(texture.texture, TEXTURE_FILTER_ANISOTROPIC_8X);
        }
        else if (filter == FilterMode::Anisotropic16x)
        {
            SetTextureFilter(texture.texture, TEXTURE_FILTER_ANISOTROPIC_16X);
        }
    }

    void Canvas::setWrap(WrapMode wrap)
    {
        this->wrap = wrap;

        if (wrap == WrapMode::Clamp)
        {
            SetTextureWrap(texture.texture, TEXTURE_WRAP_CLAMP);
        }
        else if (wrap == WrapMode::Repeat)
        {
            SetTextureWrap(texture.texture, TEXTURE_WRAP_REPEAT);
        }
        else if (wrap == WrapMode::MirrorClamp)
        {
            SetTextureWrap(texture.texture, TEXTURE_WRAP_MIRROR_CLAMP);
        }
        else if (wrap == WrapMode::MirrorRepeat)
        {
            SetTextureWrap(texture.texture, TEXTURE_WRAP_MIRROR_REPEAT);
        }
    }

    // Shader
    std::string Shaderc::type()
    {
        return "Shader";
    }

    void Shaderc::unload()
    {
        UnloadShader(shader);
    }

    bool Shaderc::hasUniform(std::string name)
    {
        return GetShaderLocation(shader, name.c_str()) != -1;
    }

    void Shaderc::send(std::string name, float value)
    {
        SetShaderValue(shader, GetShaderLocation(shader, name.c_str()), &value, SHADER_UNIFORM_FLOAT);
    }

    void Shaderc::send(std::string name, bool value)
    {
        SetShaderValue(shader, GetShaderLocation(shader, name.c_str()), &value, SHADER_UNIFORM_INT);
    }

    void Shaderc::send(std::string name, sol::table value)
    {
        if (value.size() == 2)
        {
            Vector2 vector2 = {value[1], value[2]};
            SetShaderValue(shader, GetShaderLocation(shader, name.c_str()), &vector2, SHADER_UNIFORM_VEC2);
        }
        else if (value.size() == 3)
        {
            Vector3 vector3 = {value[1], value[2], value[3]};
            SetShaderValue(shader, GetShaderLocation(shader, name.c_str()), &vector3, SHADER_UNIFORM_VEC3);
        }
        else if (value.size() == 4)
        {
            Vector4 vector4 = {value[1], value[2], value[3], value[4]};
            SetShaderValue(shader, GetShaderLocation(shader, name.c_str()), &vector4, SHADER_UNIFORM_VEC4);
        }
        else if (value.size() == 16)
        {
            Matrix matrix = {
                value[1], value[2], value[3], value[4],
                value[5], value[6], value[7], value[8],
                value[9], value[10], value[11], value[12],
                value[13], value[14], value[15], value[16]
            };

            SetShaderValueMatrix(shader, GetShaderLocation(shader, name.c_str()), matrix);
        }
    }

    void Shaderc::send(std::string name, Image image)
    {
        SetShaderValueTexture(shader, GetShaderLocation(shader, name.c_str()), image.texture);
    }

    // Camera
    std::string Camerac::type()
    {
        return "Camera";
    }

    void Camerac::setTarget(int x, int y)
    {
        camera.target = {(float)x, (float)y};
    }

    void Camerac::setOffset(int x, int y)
    {
        camera.offset = {(float)x, (float)y};
    }

    void Camerac::setRotation(float rotation)
    {
        camera.rotation = rotation;
    }

    void Camerac::setZoom(float zoom)
    {
        camera.zoom = zoom;
    }

    std::tuple<int, int> Camerac::getTarget()
    {
        return {camera.target.x, camera.target.y};
    }

    std::tuple<int, int> Camerac::getOffset()
    {
        return {camera.offset.x, camera.offset.y};
    }

    float Camerac::getRotation()
    {
        return camera.rotation;
    }

    float Camerac::getZoom()
    {
        return camera.zoom;
    }

    std::tuple<int, int> Camerac::getScreenToWorld(int x, int y)
    {
        Vector2 vector2 = GetScreenToWorld2D({(float)x, (float)y}, camera);
        return {vector2.x, vector2.y};
    }

    std::tuple<int, int> Camerac::getWorldToScreen(int x, int y)
    {
        Vector2 vector2 = GetWorldToScreen2D({(float)x, (float)y}, camera);
        return {vector2.x, vector2.y};
    }

    // Functions
    void registerGraphicsAPI(sol::state &lua)
    {
        lua.new_enum<FilterMode>("FilterMode", {
            {"Point", FilterMode::Point},
            {"Bilinear", FilterMode::Bilinear},
            {"Trilinear", FilterMode::Trilinear},
            {"Anisotropic4x", FilterMode::Anisotropic4x},
            {"Anisotropic8x", FilterMode::Anisotropic8x},
            {"Anisotropic16x", FilterMode::Anisotropic16x}
        });

        lua.new_enum<WrapMode>("WrapMode", {
            {"Clamp", WrapMode::Clamp},
            {"Repeat", WrapMode::Repeat},
            {"MirrorClamp", WrapMode::MirrorClamp},
            {"MirrorRepeat", WrapMode::MirrorRepeat}
        });

        lua.new_enum<PixelFormat>("PixelFormat", {
            {"UncompressedGrayscale", PixelFormat::UncompressedGrayscale},
            {"UncompressedGrayAlpha", PixelFormat::UncompressedGrayAlpha},
            {"UncompressedR5G6B5", PixelFormat::UncompressedR5G6B5},
            {"UncompressedR8G8B8", PixelFormat::UncompressedR8G8B8},
            {"UncompressedR5G5B5A1", PixelFormat::UncompressedR5G5B5A1},
            {"UncompressedR4G4B4A4", PixelFormat::UncompressedR4G4B4A4},
            {"UncompressedR8G8B8A8", PixelFormat::UncompressedR8G8B8A8},
            {"UncompressedR32", PixelFormat::UncompressedR32},
            {"UncompressedR32G32B32", PixelFormat::UncompressedR32G32B32},
            {"UncompressedR32G32B32A32", PixelFormat::UncompressedR32G32B32A32},
            {"CompressedDXT1RGB", PixelFormat::CompressedDXT1RGB},
            {"CompressedDXT1RGBA", PixelFormat::CompressedDXT1RGBA},
            {"CompressedDXT3RGBA", PixelFormat::CompressedDXT3RGBA},
            {"CompressedDXT5RGBA", PixelFormat::CompressedDXT5RGBA},
            {"CompressedETC1RGB", PixelFormat::CompressedETC1RGB},
            {"CompressedETC2RGB", PixelFormat::CompressedETC2RGB},
            {"CompressedETC2EACRGBA", PixelFormat::CompressedETC2EACRGBA},
            {"CompressedPVRTRGB", PixelFormat::CompressedPVRTRGB},
            {"CompressedPVRTRGBA", PixelFormat::CompressedPVRTRGBA},
            {"CompressedASTC4x4RGBA", PixelFormat::CompressedASTC4x4RGBA},
            {"CompressedASTC8x8RGBA", PixelFormat::CompressedASTC8x8RGBA}
        });

        lua.new_enum<DrawMode>("DrawMode", {
            {"Fill", DrawMode::Fill},
            {"Line", DrawMode::Line}
        });

        lua.new_enum<BlendMode>("BlendMode", {
            {"Alpha", BlendMode::Alpha},
            {"Additive", BlendMode::Additive},
            {"Multiplied", BlendMode::Multiplied},
            {"AddColors", BlendMode::AddColors},
            {"SubtractColors", BlendMode::SubtractColors}
        });

        sol::usertype<Image> image_type = lua.new_usertype<Image>("Image");

        image_type["type"] = &Image::type;
        image_type["unload"] = &Image::unload;
        image_type["getSize"] = &Image::getSize;
        image_type["getWidth"] = &Image::getWidth;
        image_type["getHeight"] = &Image::getHeight;
        image_type["getMipmaps"] = &Image::getMipmaps;
        image_type["getFilter"] = &Image::getFilter;
        image_type["getWrap"] = &Image::getWrap;
        image_type["getFormat"] = &Image::getFormat;
        image_type["setFilter"] = &Image::setFilter;
        image_type["setWrap"] = &Image::setWrap;

        sol::usertype<Fontc> font_type = lua.new_usertype<Fontc>("Font");

        font_type["type"] = &Fontc::type;
        font_type["unload"] = &Fontc::unload;
        font_type["getSize"] = &Fontc::getSize;

        sol::usertype<Canvas> canvas_type = lua.new_usertype<Canvas>("Canvas");

        canvas_type["type"] = &Canvas::type;
        canvas_type["unload"] = &Canvas::unload;
        canvas_type["getSize"] = &Canvas::getSize;
        canvas_type["getWidth"] = &Canvas::getWidth;
        canvas_type["getHeight"] = &Canvas::getHeight;
        canvas_type["getMipmaps"] = &Canvas::getMipmaps;
        canvas_type["getFilter"] = &Canvas::getFilter;
        canvas_type["getWrap"] = &Canvas::getWrap;
        canvas_type["getFormat"] = &Canvas::getFormat;
        canvas_type["setFilter"] = &Canvas::setFilter;
        canvas_type["setWrap"] = &Canvas::setWrap;

        sol::usertype<Shaderc> shader_type = lua.new_usertype<Shaderc>("Shader");

        shader_type["type"] = &Shaderc::type;
        shader_type["unload"] = &Shaderc::unload;
        shader_type["hasUniform"] = &Shaderc::hasUniform;
        shader_type["send"] = sol::overload(sol::resolve<void(std::string, float)>(&Shaderc::send), sol::resolve<void(std::string, bool)>(&Shaderc::send), sol::resolve<void(std::string, sol::table)>(&Shaderc::send), sol::resolve<void(std::string, Image)>(&Shaderc::send));

        sol::usertype<Camerac> camera_type = lua.new_usertype<Camerac>("Camera");

        camera_type["type"] = &Camerac::type;
        camera_type["setTarget"] = &Camerac::setTarget;
        camera_type["setOffset"] = &Camerac::setOffset;
        camera_type["setRotation"] = &Camerac::setRotation;
        camera_type["setZoom"] = &Camerac::setZoom;
        camera_type["getTarget"] = &Camerac::getTarget;
        camera_type["getOffset"] = &Camerac::getOffset;
        camera_type["getRotation"] = &Camerac::getRotation;
        camera_type["getZoom"] = &Camerac::getZoom;
        camera_type["getScreenToWorld"] = &Camerac::getScreenToWorld;
        camera_type["getWorldToScreen"] = &Camerac::getWorldToScreen;

        sol::table graphics = lua.create_table();

        graphics["circle"] = &circle;
        graphics["clear"] = sol::overload(sol::resolve<void(int, int, int)>(&clear), sol::resolve<void(int, int, int, int)>(&clear));
        graphics["draw"] = sol::overload(sol::resolve<void(Image, int, int)>(&draw), sol::resolve<void(Image, int, int, float, float)>(&draw), sol::resolve<void(Canvas, int, int)>(&draw));
        graphics["ellipse"] = &ellipse;
        graphics["line"] = &line;
        graphics["point"] = &point;
        graphics["polygon"] = sol::overload(sol::resolve<void(DrawMode, int, int, int, float)>(&polygon), sol::resolve<void(DrawMode, int, int, int, float, float)>(&polygon));
        graphics["print"] = sol::overload(sol::resolve<void(std::string, int, int)>(&print), sol::resolve<void(std::string, int, int, float)>(&print));
        graphics["rectangle"] = sol::overload(sol::resolve<void(DrawMode, int, int, int, int)>(&rectangle), sol::resolve<void(DrawMode, int, int, int, int, float)>(&rectangle));
        graphics["triangle"] = &triangle;
        graphics["captureScreenshot"] = &captureScreenshot;
        graphics["newFont"] = &newFont;
        graphics["newImage"] = &newImage;
        graphics["newCanvas"] = &newCanvas;
        graphics["newShader"] = &newShader;
        graphics["newCamera"] = &newCamera;
        graphics["getBackgroundColor"] = &getBackgroundColor;
        graphics["getColor"] = &getColor;
        graphics["getFont"] = &getFont;
        graphics["setBackgroundColor"] = sol::overload(sol::resolve<void(int, int, int)>(&setBackgroundColor), sol::resolve<void(int, int, int, int)>(&setBackgroundColor));
        graphics["setBlendMode"] = sol::overload(sol::resolve<void(BlendMode)>(&setBlendMode), sol::resolve<void()>(&setBlendMode));
        graphics["setCanvas"] = sol::overload(sol::resolve<void(Canvas)>(&setCanvas), sol::resolve<void()>(&setCanvas));
        graphics["setColor"] = sol::overload(sol::resolve<void(int, int, int)>(&setColor), sol::resolve<void(int, int, int, int)>(&setColor));
        graphics["setFont"] = &setFont;
        graphics["setShader"] = sol::overload(sol::resolve<void(Shaderc)>(&setShader), sol::resolve<void()>(&setShader));
        graphics["setCamera"] = sol::overload(sol::resolve<void(Camerac)>(&setCamera), sol::resolve<void()>(&setCamera));
        graphics["fade"] = fade;

        lua["cc"]["graphics"] = graphics;
    }

    std::tuple<int, int, int, int> fade(int r, int g, int b, float alpha)
    {
        Color faded = Fade({(unsigned char)r, (unsigned char)g, (unsigned char)b, 255}, alpha);

        return std::make_tuple(faded.r, faded.g, faded.b, faded.a);
    }

    void circle(DrawMode mode, float x, float y, float radius)
    {
        if (mode == DrawMode::Fill)
        {
            DrawCircle((int)x, (int)y, radius, color);
        }
        else if (mode == DrawMode::Line)
        {
            DrawCircleLines((int)x, (int)y, radius, color);
        }
    }

    void clear(int r, int g, int b)
    {
        ClearBackground({(unsigned char)r, (unsigned char)g, (unsigned char)b, 255});
    }

    void clear(int r, int g, int b, int a)
    {
        ClearBackground({(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a});
    }

    void draw(Image image, int x, int y)
    {
        DrawTexture(image.texture, x, y, color);
    }

    void draw(Image image, int x, int y, float rotation, float scale)
    {
        DrawTextureEx(image.texture, {(float)x, (float)y}, rotation, scale, color);
    }

    void draw(Canvas canvas, int x, int y)
    {
        DrawTexture(canvas.texture.texture, x, y, WHITE);
    }

    void ellipse(DrawMode mode, int x, int y, float radiusX, float radiusY)
    {
        if (mode == DrawMode::Fill)
        {
            DrawEllipse(x, y, radiusX, radiusY, color);
        }
        else if (mode == DrawMode::Line)
        {
            DrawEllipseLines(x, y, radiusX, radiusY, color);
        }
    }

    void line(int x1, int y1, int x2, int y2)
    {
        DrawLine(x1, y1, x2, y2, color);
    }

    void point(int x, int y)
    {
        DrawPixel(x, y, color);
    }

    void polygon(DrawMode mode, int x, int y, int sides, float radius)
    {
        if (mode == DrawMode::Fill)
        {
            DrawPoly({(float)x, (float)y}, sides, radius, 0, color);
        }
        else if (mode == DrawMode::Line)
        {
            DrawPolyLines({(float)x, (float)y}, sides, radius, 0, color);
        }
    }

    void polygon(DrawMode mode, int x, int y, int sides, float radius, float rotation)
    {
        if (mode == DrawMode::Fill)
        {
            DrawPoly({(float)x, (float)y}, sides, radius, rotation, color);
        }
        else if (mode == DrawMode::Line)
        {
            DrawPolyLines({(float)x, (float)y}, sides, radius, rotation, color);
        }
    }

    void print(std::string text, int x, int y)
    {
        int size = currentFont.baseSize;
        int spacing = 0;

        if (currentFont.baseSize == 0)
        {
            size = 20;
            spacing = 2;
        }

        DrawTextEx(currentFont, text.c_str(), {(float)x, (float)y}, size, spacing, color);
    }

    void print(std::string text, int x, int y, float rotation)
    {
        int size = currentFont.baseSize;
        int spacing = 0;

        if (currentFont.baseSize == 0)
        {
            size = 20;
            spacing = 2;
        }

        DrawTextPro(currentFont, text.c_str(), {(float)x, (float)y}, {0, 0}, rotation, size, spacing, color);
    }

    void rectangle(DrawMode mode, int x, int y, int width, int height)
    {
        if (mode == DrawMode::Fill)
        {
            DrawRectangle(x, y, width, height, color);
        }
        else if (mode == DrawMode::Line)
        {
            DrawRectangleLines(x, y, width, height, color);
        }
    }

    void rectangle(DrawMode mode, int x, int y, int width, int height, float rotation)
    {
        if (mode == DrawMode::Fill)
        {
            DrawRectanglePro({(float)x, (float)y, (float)width, (float)height}, {0, 0}, rotation, color);
        }
        else if (mode == DrawMode::Line)
        {
            DrawRectanglePro({(float)x, (float)y, (float)width, (float)height}, {0, 0}, rotation, color);
        }
    }

    void triangle(DrawMode mode, int x1, int y1, int x2, int y2, int x3, int y3)
    {
        if (mode == DrawMode::Fill)
        {
            DrawTriangle({(float)x1, (float)y1}, {(float)x2, (float)y2}, {(float)x3, (float)y3}, color);
        }
        else if (mode == DrawMode::Line)
        {
            DrawTriangleLines({(float)x1, (float)y1}, {(float)x2, (float)y2}, {(float)x3, (float)y3}, color);
        }
    }

    void captureScreenshot(std::string filename)
    {
        TakeScreenshot(filename.c_str());
    }

    Fontc newFont(std::string filename, int size)
    {
        Fontc font;
        font.font = LoadFontEx(filename.c_str(), size, 0, 0);

        return font;
    }

    Image newImage(std::string filename)
    {
        Image image;
        image.texture = LoadTexture(filename.c_str());
        image.setFilter(FilterMode::Point);
        image.setWrap(WrapMode::Clamp);

        return image;
    }

    Canvas newCanvas(int width, int height)
    {
        Canvas canvas;
        canvas.texture = LoadRenderTexture(width, height);
        canvas.setFilter(FilterMode::Point);
        canvas.setWrap(WrapMode::Clamp);

        return canvas;
    }

    Shaderc newShader(std::string vertex, std::string fragment)
    {
        Shaderc shader;
        shader.shader = LoadShader(vertex.c_str(), fragment.c_str());

        return shader;
    }

    Camerac newCamera()
    {
        Camerac camera;
        camera.camera.target = {0, 0};
        camera.camera.offset = {0, 0};
        camera.camera.rotation = 0;
        camera.camera.zoom = 1;

        return camera;
    }

    std::tuple<int, int, int, int> getBackgroundColor()
    {
        return std::make_tuple(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    }

    std::tuple<int, int, int, int> getColor()
    {
        return std::make_tuple(color.r, color.g, color.b, color.a);
    }

    Fontc getFont()
    {
        Fontc font;
        font.font = currentFont;

        return font;
    }

    void setBackgroundColor(int r, int g, int b)
    {
        backgroundColor = {(unsigned char)r, (unsigned char)g, (unsigned char)b, 255};
    }

    void setBackgroundColor(int r, int g, int b, int a)
    {
        backgroundColor = {(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
    }

    void setBlendMode(BlendMode mode)
    {
        BeginBlendMode(mode);
    }

    void setBlendMode()
    {
        EndBlendMode();
    }

    void setCanvas(Canvas canvas)
    {
        BeginTextureMode(canvas.texture);
    }

    void setCanvas()
    {
        EndTextureMode();
    }

    void setColor(int r, int g, int b)
    {
        color = {(unsigned char)r, (unsigned char)g, (unsigned char)b, 255};
    }

    void setColor(int r, int g, int b, int a)
    {
        color = {(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
    }

    void setFont(Fontc font)
    {
        currentFont = font.font;
    }

    void setShader(Shaderc shader)
    {
        BeginShaderMode(shader.shader);
    }

    void setShader()
    {
        EndShaderMode();
    }

    void setCamera(Camerac camera)
    {
        BeginMode2D(camera.camera);
    }

    void setCamera()
    {
        EndMode2D();
    }
}
