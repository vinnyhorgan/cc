#include "keyboard.h"

namespace keyboard
{
    void registerKeyboardAPI(sol::state& lua)
    {
        lua.new_enum<KeyboardKey>("Key", {
            {"A", KEY_A},
            {"B", KEY_B},
            {"C", KEY_C},
            {"D", KEY_D},
            {"E", KEY_E},
            {"F", KEY_F},
            {"G", KEY_G},
            {"H", KEY_H},
            {"I", KEY_I},
            {"J", KEY_J},
            {"K", KEY_K},
            {"L", KEY_L},
            {"M", KEY_M},
            {"N", KEY_N},
            {"O", KEY_O},
            {"P", KEY_P},
            {"Q", KEY_Q},
            {"R", KEY_R},
            {"S", KEY_S},
            {"T", KEY_T},
            {"U", KEY_U},
            {"V", KEY_V},
            {"W", KEY_W},
            {"X", KEY_X},
            {"Y", KEY_Y},
            {"Z", KEY_Z},
            {"Zero", KEY_ZERO},
            {"One", KEY_ONE},
            {"Two", KEY_TWO},
            {"Three", KEY_THREE},
            {"Four", KEY_FOUR},
            {"Five", KEY_FIVE},
            {"Six", KEY_SIX},
            {"Seven", KEY_SEVEN},
            {"Eight", KEY_EIGHT},
            {"Nine", KEY_NINE},
            {"Escape", KEY_ESCAPE},
            {"LeftControl", KEY_LEFT_CONTROL},
            {"LeftShift", KEY_LEFT_SHIFT},
            {"LeftAlt", KEY_LEFT_ALT},
            {"LeftSuper", KEY_LEFT_SUPER},
            {"RightControl", KEY_RIGHT_CONTROL},
            {"RightShift", KEY_RIGHT_SHIFT},
            {"RightAlt", KEY_RIGHT_ALT},
            {"RightSuper", KEY_RIGHT_SUPER},
            {"Backspace", KEY_BACKSPACE},
            {"Tab", KEY_TAB},
            {"Enter", KEY_ENTER},
            {"Space", KEY_SPACE},
            {"Grave", KEY_GRAVE},
            {"Minus", KEY_MINUS},
            {"Equal", KEY_EQUAL},
            {"LeftBracket", KEY_LEFT_BRACKET},
            {"RightBracket", KEY_RIGHT_BRACKET},
            {"Backslash", KEY_BACKSLASH},
            {"Semicolon", KEY_SEMICOLON},
            {"Apostrophe", KEY_APOSTROPHE},
            {"Comma", KEY_COMMA},
            {"Period", KEY_PERIOD},
            {"Slash", KEY_SLASH},
            {"F1", KEY_F1},
            {"F2", KEY_F2},
            {"F3", KEY_F3},
            {"F4", KEY_F4},
            {"F5", KEY_F5},
            {"F6", KEY_F6},
            {"F7", KEY_F7},
            {"F8", KEY_F8},
            {"F9", KEY_F9},
            {"F10", KEY_F10},
            {"F11", KEY_F11},
            {"F12", KEY_F12},
            {"Up", KEY_UP},
            {"Down", KEY_DOWN},
            {"Left", KEY_LEFT},
            {"Right", KEY_RIGHT},
            {"LeftControl", KEY_LEFT_CONTROL},
            {"RightControl", KEY_RIGHT_CONTROL},
            {"LeftShift", KEY_LEFT_SHIFT},
            {"RightShift", KEY_RIGHT_SHIFT},
            {"LeftAlt", KEY_LEFT_ALT},
            {"RightAlt", KEY_RIGHT_ALT},
            {"LeftSuper", KEY_LEFT_SUPER},
            {"RightSuper", KEY_RIGHT_SUPER},
            {"KbMenu", KEY_KB_MENU},
            {"LeftBracket", KEY_LEFT_BRACKET},
            {"Backslash", KEY_BACKSLASH},
            {"RightBracket", KEY_RIGHT_BRACKET},
            {"Grave", KEY_GRAVE},
            {"Kp0", KEY_KP_0},
            {"Kp1", KEY_KP_1},
            {"Kp2", KEY_KP_2},
            {"Kp3", KEY_KP_3},
            {"Kp4", KEY_KP_4},
            {"Kp5", KEY_KP_5},
            {"Kp6", KEY_KP_6},
            {"Kp7", KEY_KP_7},
            {"Kp8", KEY_KP_8},
            {"Kp9", KEY_KP_9},
            {"KpDecimal", KEY_KP_DECIMAL},
            {"KpDivide", KEY_KP_DIVIDE},
            {"KpMultiply", KEY_KP_MULTIPLY},
            {"KpSubtract", KEY_KP_SUBTRACT},
            {"KpAdd", KEY_KP_ADD},
            {"KpEnter", KEY_KP_ENTER},
            {"KpEqual", KEY_KP_EQUAL},
            {"Backspace", KEY_BACKSPACE},
            {"Insert", KEY_INSERT},
            {"Delete", KEY_DELETE},
            {"Right", KEY_RIGHT},
            {"Left", KEY_LEFT},
            {"Down", KEY_DOWN},
            {"Up", KEY_UP},
            {"PageUp", KEY_PAGE_UP},
        });

        sol::table keyboard = lua.create_table();

        keyboard["isDown"] = &isDown;
        keyboard["isPressed"] = &isPressed;
        keyboard["isReleased"] = &isReleased;

        lua["cc"]["keyboard"] = keyboard;
    }

    bool isDown(KeyboardKey key)
    {
        return IsKeyDown(key);
    }

    bool isPressed(KeyboardKey key)
    {
        return IsKeyPressed(key);
    }

    bool isReleased(KeyboardKey key)
    {
        return IsKeyReleased(key);
    }
}
