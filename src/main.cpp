#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <spdlog/spdlog.h>
#include <raylib.h>
#include <rlImGui.h>
#include <imfilebrowser.h>
#include <imgui_memory_editor.h>

#include <string>

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

namespace graphics
{
    Texture loadTexture(std::string path)
    {
        return LoadTexture(path.c_str());
    }

    void unloadTexture(Texture texture)
    {
        UnloadTexture(texture);
    }

    void drawTexture(Texture texture, int posX, int posY)
    {
        DrawTexture(texture, posX, posY, WHITE);
    }
}

ImGui::FileBrowser fileDialog;

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

    bool begin(std::string title, bool open, sol::table flags)
    {
        ImGuiWindowFlags windowFlags = 0;

        if (flags["noTitleBar"].get_or(false))
        {
            windowFlags |= ImGuiWindowFlags_NoTitleBar;
        }

        if (flags["noResize"].get_or(false))
        {
            windowFlags |= ImGuiWindowFlags_NoResize;
        }

        if (flags["noMove"].get_or(false))
        {
            windowFlags |= ImGuiWindowFlags_NoMove;
        }

        if (flags["menuBar"].get_or(false))
        {
            windowFlags |= ImGuiWindowFlags_MenuBar;
        }

        ImGui::Begin(title.c_str(), &open, windowFlags);

        return open;
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

    bool beginMenuBar()
    {
        return ImGui::BeginMenuBar();
    }

    void endMenuBar()
    {
        ImGui::EndMenuBar();
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

    std::string inputText(std::string label, std::string value)
    {
        char buffer[1024];

        strcpy(buffer, value.c_str());

        ImGui::InputText(label.c_str(), buffer, 1024);

        return std::string(buffer);
    }

    void sameLine()
    {
        ImGui::SameLine();
    }

    void separator()
    {
        ImGui::Separator();
    }

    void beginChild(std::string label)
    {
        ImGui::BeginChild(label.c_str(), ImVec2(0, 0), true);
    }

    void endChild()
    {
        ImGui::EndChild();
    }

    void textColored(std::string text, int r, int g, int b, int a)
    {
        ImGui::TextColored(ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f), text.c_str());
    }

    void openFileDialog(std::string title)
    {
        fileDialog.SetTitle(title.c_str());
        fileDialog.Open();
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

    std::string finalCode = classic + "\n" + transpiled;

    SaveFileText("debug.lua", const_cast<char*>(finalCode.c_str()));

    lua.script(finalCode);

    sol::function load = lua["load"];
    sol::function update = lua["update"];
    sol::function draw = lua["draw"];
    sol::function fileDialogSelected = lua["fileDialogSelected"];

    sol::table graphics = lua.create_table();

    graphics["loadTexture"] = graphics::loadTexture;
    graphics["unloadTexture"] = graphics::unloadTexture;
    graphics["drawTexture"] = graphics::drawTexture;

    lua["graphics"] = graphics;

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
    gui["beginMenuBar"] = gui::beginMenuBar;
    gui["endMenuBar"] = gui::endMenuBar;
    gui["beginMenu"] = gui::beginMenu;
    gui["endMenu"] = gui::endMenu;
    gui["menuItem"] = gui::menuItem;
    gui["sliderInt"] = gui::sliderInt;
    gui["sliderFloat"] = gui::sliderFloat;
    gui["checkbox"] = gui::checkbox;
    gui["inputText"] = gui::inputText;
    gui["sameLine"] = gui::sameLine;
    gui["separator"] = gui::separator;
    gui["beginChild"] = gui::beginChild;
    gui["endChild"] = gui::endChild;
    gui["textColored"] = gui::textColored;
    gui["openFileDialog"] = gui::openFileDialog;

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

        static MemoryEditor mem_edit_1;
        static char data[0x10000];
        size_t data_size = 0x10000;
        mem_edit_1.DrawWindow("Memory Editor", data, data_size);

        fileDialog.Display();

        if (fileDialog.HasSelected())
        {
            fileDialogSelected(fileDialog.GetSelected().string());

            fileDialog.ClearSelected();
        }

        rlImGuiEnd();

        EndDrawing();
    }

    rlImGuiShutdown();

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
