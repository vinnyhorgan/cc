#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

#include "graphics.h"

namespace window
{
    // Functions

    // Utility
    void registerWindowAPI(sol::state& lua);

    // API
    std::tuple<float, float> getDPIScale();
    std::tuple<int, int> getDesktopDimensions(int display);
    std::tuple<int, int> getDimensions();
    int getDisplayCount();
    std::string getDisplayName(int display);
    std::tuple<int, int, sol::table> getMode();
    bool getFullscreen();
    int getHeight();
    std::tuple<int, int> getPosition();
    std::string getTitle();
    bool getVSync();
    int getWidth();
    bool hasFocus();
    bool isMaximized();
    bool isMinimized();
    bool isOpen();
    bool isVisible();
    bool isResized();
    void maximize();
    void minimize();
    void restore();
    void setFullscreen(bool fullscreen);
    void setMode(int width, int height, sol::table flags);
    void setIcon(graphics::Image image);
    void setPosition(int x, int y);
    void setTitle(std::string title);
    void setVSync(bool vsync);
}
