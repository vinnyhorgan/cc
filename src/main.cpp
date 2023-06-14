#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <spdlog/spdlog.h>
#include <raylib.h>
#include <rlImGui.h>

#include <string>

std::string luoToLua(const std::string& code) {
    std::string result = code;

    // Replace not equals
    size_t pos = result.find("!=");
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

namespace gui
{
    void enableDocking()
    {
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    }

    void disableDocking()
    {
        ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;
    }

    void enableKeyboard()
    {
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    }

    void disableKeyboard()
    {
        ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NavEnableKeyboard;
    }

    void dockSpace()
    {
        ImGui::DockSpaceOverViewport();
    }

    void begin(std::string title)
    {
        ImGui::Begin(title.c_str());
    }

    void end()
    {
        ImGui::End();
    }

    void text(std::string text)
    {
        ImGui::Text(text.c_str());
    }

    bool button(std::string text)
    {
        return ImGui::Button(text.c_str());
    }

    bool beginMainMenuBar()
    {
        return ImGui::BeginMainMenuBar();
    }

    void endMainMenuBar()
    {
        ImGui::EndMainMenuBar();
    }

    bool beginMenu(std::string label)
    {
        return ImGui::BeginMenu(label.c_str());
    }

    void endMenu()
    {
        ImGui::EndMenu();
    }

    bool menuItem(std::string label)
    {
        return ImGui::MenuItem(label.c_str());
    }

    int sliderInt(std::string label, int value, int min, int max)
    {
        ImGui::SliderInt(label.c_str(), &value, min, max);

        return value;
    }

    float sliderFloat(std::string label, float value, float min, float max)
    {
        ImGui::SliderFloat(label.c_str(), &value, min, max);

        return value;
    }

    bool checkbox(std::string label, bool value)
    {
        ImGui::Checkbox(label.c_str(), &value);

        return value;
    }
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
    SetTraceLogCallback(log);

    sol::state lua;

    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::string, sol::lib::table);

    std::string main = LoadFileText("demo/main.lua");

    std::string transpiled = luoToLua(main);

    lua.script(transpiled);

    sol::function load = lua["load"];
    sol::function update = lua["update"];
    sol::function draw = lua["draw"];

    sol::table gui = lua.create_table();

    gui["enableDocking"] = gui::enableDocking;
    gui["disableDocking"] = gui::disableDocking;
    gui["enableKeyboard"] = gui::enableKeyboard;
    gui["disableKeyboard"] = gui::disableKeyboard;
    gui["dockSpace"] = gui::dockSpace;
    gui["begin"] = gui::begin;
    gui["endd"] = gui::end; // bruh
    gui["text"] = gui::text;
    gui["button"] = gui::button;
    gui["beginMainMenuBar"] = gui::beginMainMenuBar;
    gui["endMainMenuBar"] = gui::endMainMenuBar;
    gui["beginMenu"] = gui::beginMenu;
    gui["endMenu"] = gui::endMenu;
    gui["menuItem"] = gui::menuItem;
    gui["sliderInt"] = gui::sliderInt;
    gui["sliderFloat"] = gui::sliderFloat;
    gui["checkbox"] = gui::checkbox;

    lua["gui"] = gui;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Creative Coding by Vinny Horgan");
    SetTargetFPS(60);

    InitAudioDevice();

    rlImGuiSetup(true);

    load();

    while (!WindowShouldClose())
    {
        update();

        BeginDrawing();

        ClearBackground(BLACK);

        rlImGuiBegin();

        draw();

        rlImGuiEnd();

        EndDrawing();
    }

    rlImGuiShutdown();

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
