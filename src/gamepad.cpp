#include "gamepad.h"

namespace gamepad
{
    // Types

    std::string Gamepad::type()
    {
        return "Gamepad";
    }

    int Gamepad::getId()
    {
        return id;
    }

    std::string Gamepad::getName()
    {
        return GetGamepadName(id);
    }

    bool Gamepad::isDown(GamepadButton button)
    {
        return IsGamepadButtonDown(id, button);
    }

    bool Gamepad::isPressed(GamepadButton button)
    {
        return IsGamepadButtonPressed(id, button);
    }

    bool Gamepad::isReleased(GamepadButton button)
    {
        return IsGamepadButtonReleased(id, button);
    }

    int Gamepad::getAxisCount()
    {
        return GetGamepadAxisCount(id);
    }

    float Gamepad::getAxisMovement(GamepadAxis axis)
    {
        return GetGamepadAxisMovement(id, axis);
    }

    void registerGamepadAPI(sol::state& lua)
    {
        lua.new_enum<GamepadButton>("GamepadButton", {
            {"Unknown", GAMEPAD_BUTTON_UNKNOWN},
            {"LeftFaceUp", GAMEPAD_BUTTON_LEFT_FACE_UP},
            {"LeftFaceRight", GAMEPAD_BUTTON_LEFT_FACE_RIGHT},
            {"LeftFaceDown", GAMEPAD_BUTTON_LEFT_FACE_DOWN},
            {"LeftFaceLeft", GAMEPAD_BUTTON_LEFT_FACE_LEFT},
            {"RightFaceUp", GAMEPAD_BUTTON_RIGHT_FACE_UP},
            {"RightFaceRight", GAMEPAD_BUTTON_RIGHT_FACE_RIGHT},
            {"RightFaceDown", GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
            {"RightFaceLeft", GAMEPAD_BUTTON_RIGHT_FACE_LEFT},
            {"LeftTrigger1", GAMEPAD_BUTTON_LEFT_TRIGGER_1},
            {"LeftTrigger2", GAMEPAD_BUTTON_LEFT_TRIGGER_2},
            {"RightTrigger1", GAMEPAD_BUTTON_RIGHT_TRIGGER_1},
            {"RightTrigger2", GAMEPAD_BUTTON_RIGHT_TRIGGER_2},
            {"MiddleLeft", GAMEPAD_BUTTON_MIDDLE_LEFT},
            {"Middle", GAMEPAD_BUTTON_MIDDLE},
            {"MiddleRight", GAMEPAD_BUTTON_MIDDLE_RIGHT},
            {"LeftThumb", GAMEPAD_BUTTON_LEFT_THUMB},
            {"RightThumb", GAMEPAD_BUTTON_RIGHT_THUMB}
        });

        lua.new_enum<GamepadAxis>("GamepadAxis", {
            {"LeftX", GAMEPAD_AXIS_LEFT_X},
            {"LeftY", GAMEPAD_AXIS_LEFT_Y},
            {"RightX", GAMEPAD_AXIS_RIGHT_X},
            {"RightY", GAMEPAD_AXIS_RIGHT_Y},
            {"LeftTrigger", GAMEPAD_AXIS_LEFT_TRIGGER},
            {"RightTrigger", GAMEPAD_AXIS_RIGHT_TRIGGER}
        });

        sol::usertype<Gamepad> gamepad_type = lua.new_usertype<Gamepad>("Gamepad");

        gamepad_type["type"] = &Gamepad::type;
        gamepad_type["getId"] = &Gamepad::getId;
        gamepad_type["getName"] = &Gamepad::getName;
        gamepad_type["isDown"] = &Gamepad::isDown;
        gamepad_type["isPressed"] = &Gamepad::isPressed;
        gamepad_type["isReleased"] = &Gamepad::isReleased;
        gamepad_type["getAxisCount"] = &Gamepad::getAxisCount;
        gamepad_type["getAxisMovement"] = &Gamepad::getAxisMovement;

        sol::table gamepad = lua.create_table();

        gamepad["getGamepads"] = &getGamepads;
        gamepad["getGamepadCount"] = &getGamepadCount;

        lua["cc"]["gamepad"] = gamepad;
    }

    sol::table getGamepads(sol::this_state state)
    {
        sol::state_view lua(state);

        sol::table gamepads = lua.create_table();

        for (int i = 0; i < 4; i++)
        {
            if (IsGamepadAvailable(i))
            {
                Gamepad gamepad;

                gamepad.id = i;

                gamepads[i + 1] = gamepad;
            }
        }

        return gamepads;
    }

    int getGamepadCount()
    {
        int count = 0;

        for (int i = 0; i < 4; i++)
        {
            if (IsGamepadAvailable(i))
            {
                count++;
            }
        }

        return count;
    }
}
