#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

namespace mouse
{
    // Functions

    // Utility
    void registerMouseAPI(sol::state& lua);

    // API
    std::tuple<int, int> getPosition();
    std::tuple<float, float> getDelta();
    float getWheelMove();
    int getX();
    int getY();
    bool isDown(MouseButton button);
    bool isPressed(MouseButton button);
    bool isReleased(MouseButton button);
    bool isGrabbed();
    bool isVisible();
    void setCursor(MouseCursor cursor);
    void setPosition(int x, int y);
    void setX(int x);
    void setY(int y);
    void setGrabbed(bool grabbed);
    void setVisible(bool visible);
}
