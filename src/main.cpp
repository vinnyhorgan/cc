#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <spdlog/spdlog.h>
#include <raylib.h>
#include <rlImGui.h>

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

// lua api
void guiBegin(std::string title)
{
    ImGui::Begin(title.c_str());
}

void guiEnd()
{
    ImGui::End();
}

void guiText(std::string text)
{
    ImGui::Text(text.c_str());
}

bool guiButton(std::string text)
{
    return ImGui::Button(text.c_str());
}

void guiEnableDocking()
{
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void guiDisableDocking()
{
    ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;
}

void guiDockSpace()
{
    ImGui::DockSpaceOverViewport();
}

int main()
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    lua.script_file("demo/main.lua");

    sol::function load = lua["load"];
    sol::function update = lua["update"];
    sol::function draw = lua["draw"];

    lua["guiBegin"] = guiBegin;
    lua["guiEnd"] = guiEnd;
    lua["guiText"] = guiText;
    lua["guiButton"] = guiButton;
    lua["guiEnableDocking"] = guiEnableDocking;
    lua["guiDisableDocking"] = guiDisableDocking;
    lua["guiDockSpace"] = guiDockSpace;

    SetTraceLogCallback(log);
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
