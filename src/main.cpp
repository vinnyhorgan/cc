#define SOL_ALL_SAFETIES_ON 1
#define SOL_SAFE_USERTYPE 1
#include <sol/sol.hpp>

#include <spdlog/spdlog.h>
#include <raylib.h>
#include <rlImGui.h>

#include <string>

#include "gui.h"
#include "graphics.h"
#include "keyboard.h"
#include "networking.h"
#include "mouse.h"
#include "timer.h"
#include "window.h"
#include "system.h"
#include "filesystem.h"
#include "data.h"
#include "gamepad.h"
#include "audio.h"

// lua classic library
std::string classic = R"(
local Object = {}
Object.__index = Object

function Object:new()
end

function Object:extend()
  local cls = {}
  for k, v in pairs(self) do
    if k:find("__") == 1 then
      cls[k] = v
    end
  end
  cls.__index = cls
  cls.super = self
  setmetatable(cls, self)
  return cls
end

function Object:implement(...)
  for _, cls in pairs({...}) do
    for k, v in pairs(cls) do
      if self[k] == nil and type(v) == "function" then
        self[k] = v
      end
    end
  end
end

function Object:is(T)
  local mt = getmetatable(self)
  while mt do
    if mt == T then
      return true
    end
    mt = getmetatable(mt)
  end
  return false
end

function Object:__tostring()
  return "Object"
end

function Object:__call(...)
  local obj = setmetatable({}, self)
  obj:new(...)
  return obj
end
)";

std::string luoToLua(const std::string& code) {
    std::string result = code;

    size_t pos = result.find("import(\"");
    while (pos != std::string::npos) {
        size_t endpos = result.find("\")", pos + 8);
        if (endpos != std::string::npos) {
            std::string filename = result.substr(pos + 8, endpos - pos - 8);

            std::string file_contents = LoadFileText(filename.c_str());
            result.replace(pos, endpos - pos + 2, file_contents);
        }
        pos = result.find("import(\"", pos + 1);
    }

    // Replace not equals
    pos = result.find("!=");
    while (pos != std::string::npos) {
        result.replace(pos, 2, "~=");
        pos = result.find("!=", pos + 2);
    }

    // Replace +=, -=, *=, /=, %=
    pos = result.find("+=");
    while (pos != std::string::npos) {
        // Find the nearest newline character before the += operator
        size_t lhs_start = result.rfind('\n', pos);
        if (lhs_start == std::string::npos) {
            lhs_start = 0;
        } else {
            // Include the newline character in the substring
            lhs_start += 1;
        }
        // Replace the += operator with = lhs + rhs
        result.replace(pos, 2, " = " + result.substr(lhs_start, pos - lhs_start) + " + ");
        pos = result.find("+=", pos + 2);
    }

    pos = result.find("-=");
    while (pos != std::string::npos) {
        size_t lhs_start = result.rfind('\n', pos);
        if (lhs_start == std::string::npos) {
            lhs_start = 0;
        } else {
            lhs_start += 1;
        }
        result.replace(pos, 2, " = " + result.substr(lhs_start, pos - lhs_start) + " - ");
        pos = result.find("-=", pos + 2);
    }

    pos = result.find("*=");
    while (pos != std::string::npos) {
        size_t lhs_start = result.rfind('\n', pos);
        if (lhs_start == std::string::npos) {
            lhs_start = 0;
        } else {
            lhs_start += 1;
        }
        result.replace(pos, 2, " = " + result.substr(lhs_start, pos - lhs_start) + " * ");
        pos = result.find("*=", pos + 2);
    }

    pos = result.find("/=");
    while (pos != std::string::npos) {
        size_t lhs_start = result.rfind('\n', pos);
        if (lhs_start == std::string::npos) {
            lhs_start = 0;
        } else {
            lhs_start += 1;
        }
        result.replace(pos, 2, " = " + result.substr(lhs_start, pos - lhs_start) + " / ");
        pos = result.find("/=", pos + 2);
    }

    pos = result.find("%=");
    while (pos != std::string::npos) {
        size_t lhs_start = result.rfind('\n', pos);
        if (lhs_start == std::string::npos) {
            lhs_start = 0;
        } else {
            lhs_start += 1;
        }
        result.replace(pos, 2, " = " + result.substr(lhs_start, pos - lhs_start) + " % ");
        pos = result.find("%=", pos + 2);
    }

    // TODO Replace array indexing

    return result;
}

void log(int msgType, const char* text, va_list args)
{
    char message[1024];

    vsprintf(message, text, args);

    switch (msgType)
    {
        case LOG_INFO:
            spdlog::info(message);
            break;
        case LOG_ERROR:
            spdlog::error(message);
            break;
        case LOG_WARNING:
            spdlog::warn(message);
            break;
        case LOG_DEBUG:
            spdlog::debug(message);
            break;
    }
}

int main()
{
    bool error = false;
    std::string error_message;
    bool copied = false;

    SetTraceLogCallback(log);

    sol::state lua;

    lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::math, sol::lib::string);

    std::string main = LoadFileText("demo/main.lua");

    std::string transpiled = luoToLua(main);

    lua.script(classic);

    sol::protected_function_result result = lua.safe_script(transpiled, sol::script_pass_on_error);

    if (!result.valid()) {
        sol::error err = result;
        spdlog::error("Error loading script: {}", err.what());

        error = true;
        error_message = err.what();
    }

    sol::protected_function load = lua["load"];
    sol::protected_function update = lua["update"];
    sol::protected_function draw = lua["draw"];

    lua["cc"] = lua.create_table();

    gui::registerGuiAPI(lua);
    graphics::registerGraphicsAPI(lua);
    keyboard::registerKeyboardAPI(lua);
    networking::registerNetworkingAPI(lua);
    mouse::registerMouseAPI(lua);
    timer::registerTimerAPI(lua);
    window::registerWindowAPI(lua);
    systemc::registerSystemAPI(lua);
    filesystem::registerFilesystemAPI(lua);
    data::registerDataAPI(lua);
    gamepad::registerGamepadAPI(lua);
    audio::registerAudioAPI(lua);

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(800, 600, "Creative Coding by Vinny Horgan");
    SetTargetFPS(60);
    SetExitKey(0);

    InitAudioDevice();

    rlImGuiSetup(true);

    result = load();

    if (!result.valid()) {
        sol::error err = result;
        spdlog::error("Error loading script: {}", err.what());

        error = true;
        error_message = err.what();
    }

    while (!WindowShouldClose())
    {
        if (error)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                SetClipboardText(error_message.c_str());
                copied = true;
            }

            BeginDrawing();

            ClearBackground(SKYBLUE);

            DrawText("Error: (click to copy to clipboard)", 10, 10, 20, WHITE);
            DrawText(error_message.c_str(), 10, 40, 20, WHITE);

            if (copied)
            {
                DrawText("Copied to clipboard!", 10, GetScreenHeight() - 30, 20, WHITE);
            }

            EndDrawing();
        }
        else
        {
            result = update(GetFrameTime());

            if (!result.valid()) {
                sol::error err = result;
                spdlog::error("Error updating script: {}", err.what());

                error = true;
                error_message = err.what();
            }

            BeginDrawing();

            ClearBackground(BLACK);

            rlImGuiBegin();

            result = draw();

            if (!result.valid()) {
                sol::error err = result;
                spdlog::error("Error drawing script: {}", err.what());

                error = true;
                error_message = err.what();
            }

            gui::updateFileDialog(lua);

            rlImGuiEnd();

            EndDrawing();
        }
    }

    rlImGuiShutdown();

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
