#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

namespace gamepad
{
    // Types
    class Gamepad
    {
    public:
        int id;

        std::string type();

        int getId();
        std::string getName();
        bool isDown(GamepadButton button);
        bool isPressed(GamepadButton button);
        bool isReleased(GamepadButton button);
        int getAxisCount();
        float getAxisMovement(GamepadAxis axis);
    };

    // Functions

    // Utility
    void registerGamepadAPI(sol::state& lua);

    // API
    sol::table getGamepads(sol::this_state state);
    int getGamepadCount();
}
