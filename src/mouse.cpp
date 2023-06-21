#include "mouse.h"

bool grab = false;

namespace mouse
{
    void registerMouseAPI(sol::state& lua)
    {
        lua.new_enum<MouseButton>("Button", {
            {"Left", MOUSE_BUTTON_LEFT},
            {"Right", MOUSE_BUTTON_RIGHT},
            {"Middle", MOUSE_BUTTON_MIDDLE},
            {"Side", MOUSE_BUTTON_SIDE},
            {"Extra", MOUSE_BUTTON_EXTRA},
            {"Forward", MOUSE_BUTTON_FORWARD},
            {"Backward", MOUSE_BUTTON_BACK}
        });

        lua.new_enum<MouseCursor>("Cursor", {
            {"Default", MOUSE_CURSOR_DEFAULT},
            {"Arrow", MOUSE_CURSOR_ARROW},
            {"Ibeam", MOUSE_CURSOR_IBEAM},
            {"Crosshair", MOUSE_CURSOR_CROSSHAIR},
            {"PointingHand", MOUSE_CURSOR_POINTING_HAND},
            {"ResizeEW", MOUSE_CURSOR_RESIZE_EW},
            {"ResizeNS", MOUSE_CURSOR_RESIZE_NS},
            {"ResizeNWSE", MOUSE_CURSOR_RESIZE_NWSE},
            {"ResizeNESW", MOUSE_CURSOR_RESIZE_NESW},
            {"ResizeAll", MOUSE_CURSOR_RESIZE_ALL},
            {"NotAllowed", MOUSE_CURSOR_NOT_ALLOWED}
        });

        sol::table mouse = lua.create_table();

        mouse["getPosition"] = &getPosition;
        mouse["getDelta"] = &getDelta;
        mouse["getWheelMove"] = &getWheelMove;
        mouse["getX"] = &getX;
        mouse["getY"] = &getY;
        mouse["isDown"] = &isDown;
        mouse["isPressed"] = &isPressed;
        mouse["isReleased"] = &isReleased;
        mouse["isGrabbed"] = &isGrabbed;
        mouse["isVisible"] = &isVisible;
        mouse["setCursor"] = &setCursor;
        mouse["setPosition"] = &setPosition;
        mouse["setX"] = &setX;
        mouse["setY"] = &setY;
        mouse["setGrabbed"] = &setGrabbed;
        mouse["setVisible"] = &setVisible;

        lua["cc"]["mouse"] = mouse;
    }

    std::tuple<int, int> getPosition()
    {
        return std::make_tuple(GetMouseX(), GetMouseY());
    }

    std::tuple<float, float> getDelta()
    {
        Vector2 delta = GetMouseDelta();
        return std::make_tuple(delta.x, delta.y);
    }

    float getWheelMove()
    {
        return GetMouseWheelMove();
    }

    int getX()
    {
        return GetMouseX();
    }

    int getY()
    {
        return GetMouseY();
    }

    bool isDown(MouseButton button)
    {
        return IsMouseButtonDown(button);
    }

    bool isPressed(MouseButton button)
    {
        return IsMouseButtonPressed(button);
    }

    bool isReleased(MouseButton button)
    {
        return IsMouseButtonReleased(button);
    }

    bool isGrabbed()
    {
        return grab;
    }

    bool isVisible()
    {
        return !IsCursorHidden();
    }

    void setCursor(MouseCursor cursor)
    {
        SetMouseCursor(cursor);
    }

    void setPosition(int x, int y)
    {
        SetMousePosition(x, y);
    }

    void setX(int x)
    {
        SetMousePosition(x, GetMouseY());
    }

    void setY(int y)
    {
        SetMousePosition(GetMouseX(), y);
    }

    void setGrabbed(bool grabbed)
    {
        grab = grabbed;

        if (grab)
        {
            DisableCursor();
        }
        else
        {
            EnableCursor();
        }
    }

    void setVisible(bool visible)
    {
        if (visible)
        {
            ShowCursor();
        }
        else
        {
            HideCursor();
        }
    }
}
