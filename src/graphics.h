#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

#include <string>

namespace graphics
{
    // Enums
    enum FilterMode
    {
        Point,
        Bilinear,
        Trilinear,
        Anisotropic4x,
        Anisotropic8x,
        Anisotropic16x
    };

    enum WrapMode
    {
        Clamp,
        Repeat,
        MirrorClamp,
        MirrorRepeat
    };

    enum PixelFormat
    {
        UncompressedGrayscale,
        UncompressedGrayAlpha,
        UncompressedR5G6B5,
        UncompressedR8G8B8,
        UncompressedR5G5B5A1,
        UncompressedR4G4B4A4,
        UncompressedR8G8B8A8,
        UncompressedR32,
        UncompressedR32G32B32,
        UncompressedR32G32B32A32,
        CompressedDXT1RGB,
        CompressedDXT1RGBA,
        CompressedDXT3RGBA,
        CompressedDXT5RGBA,
        CompressedETC1RGB,
        CompressedETC2RGB,
        CompressedETC2EACRGBA,
        CompressedPVRTRGB,
        CompressedPVRTRGBA,
        CompressedASTC4x4RGBA,
        CompressedASTC8x8RGBA
    };

    enum DrawMode
    {
        Fill,
        Line
    };

    enum BlendMode
    {
        Alpha,
        Additive,
        Multiplied,
        AddColors,
        SubtractColors
    };

    // Types
    class Image
    {
    public:
        Texture texture;
        FilterMode filter;
        WrapMode wrap;

        std::string type();
        void unload();

        std::tuple<int, int> getSize();
        int getWidth();
        int getHeight();
        int getMipmaps();
        FilterMode getFilter();
        WrapMode getWrap();
        PixelFormat getFormat();
        void setFilter(FilterMode filter);
        void setWrap(WrapMode wrap);
    };

    class Fontc // ehm...
    {
    public:
        Font font;

        std::string type();
        void unload();

        int getSize();
    };

    class Canvas
    {
    public:
        RenderTexture2D texture;
        FilterMode filter;
        WrapMode wrap;

        std::string type();
        void unload();

        std::tuple<int, int> getSize();
        int getWidth();
        int getHeight();
        int getMipmaps();
        FilterMode getFilter();
        WrapMode getWrap();
        PixelFormat getFormat();
        void setFilter(FilterMode filter);
        void setWrap(WrapMode wrap);
    };

    class Shaderc // same issue...
    {
    public:
        Shader shader;

        std::string type();
        void unload();

        bool hasUniform(std::string name);
        void send(std::string name, float value);
        void send(std::string name, bool value);
        void send(std::string name, sol::table value);
        void send(std::string name, Image image);
    };

    class Camerac // bruh
    {
    public:
        Camera2D camera;

        std::string type();

        void setTarget(int x, int y);
        void setOffset(int x, int y);
        void setRotation(float rotation);
        void setZoom(float zoom);
        std::tuple<int, int> getTarget();
        std::tuple<int, int> getOffset();
        float getRotation();
        float getZoom();
        std::tuple<int, int> getScreenToWorld(int x, int y);
        std::tuple<int, int> getWorldToScreen(int x, int y);
    };

    // Functions

    // Utility
    void registerGraphicsAPI(sol::state& lua);

    // API

    // Drawing
    void circle(DrawMode mode, int x, int y, float radius);
    void clear(int r, int g, int b);
    void clear(int r, int g, int b, int a);
    void draw(Image image, int x, int y);
    void draw(Image image, int x, int y, float rotation, float scale);
    void draw(Canvas canvas, int x, int y);
    void ellipse(DrawMode mode, int x, int y, float radiusX, float radiusY);
    void line(int x1, int y1, int x2, int y2);
    void point(int x, int y);
    void polygon(DrawMode mode, int x, int y, int sides, float radius);
    void polygon(DrawMode mode, int x, int y, int sides, float radius, float rotation);
    void print(std::string text, int x, int y);
    void print(std::string text, int x, int y, float rotation);
    void rectangle(DrawMode mode, int x, int y, int width, int height);
    void rectangle(DrawMode mode, int x, int y, int width, int height, float rotation);
    void triangle(DrawMode mode, int x1, int y1, int x2, int y2, int x3, int y3);

    // Object creation
    void captureScreenshot(std::string filename);
    Fontc newFont(std::string filename, int size);
    Image newImage(std::string filename);
    Canvas newCanvas(int width, int height);
    Shaderc newShader(std::string vertex, std::string fragment);
    Camerac newCamera();

    // Graphics state
    std::tuple<int, int, int, int> getBackgroundColor();
    std::tuple<int, int, int, int> getColor();
    Fontc getFont();
    void setBackgroundColor(int r, int g, int b);
    void setBackgroundColor(int r, int g, int b, int a);
    void setBlendMode(BlendMode mode);
    void setBlendMode();
    void setCanvas(Canvas canvas);
    void setCanvas();
    void setColor(int r, int g, int b);
    void setColor(int r, int g, int b, int a);
    void setFont(Fontc font);
    void setShader(Shaderc shader);
    void setShader();
    void setCamera(Camerac camera);
    void setCamera();

    // TODO: Add particle system and ideally video support
}
