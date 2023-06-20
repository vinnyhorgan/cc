#include "gui.h"

#include <rlImGui.h>
#include <imfilebrowser.h>
#include <imgui_memory_editor.h>

ImGui::FileBrowser fileDialog; // TODO add flag support

namespace gui
{
    void registerGuiAPI(sol::state& lua)
    {
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
    }

    void updateFileDialog(sol::state& lua)
    {
        sol::function fileDialogSelected = lua["fileDialogSelected"];

        fileDialog.Display();

        if (fileDialog.HasSelected())
        {
            std::string path = fileDialog.GetSelected().string();

            fileDialogSelected(path);

            fileDialog.ClearSelected();
        }
    }

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

    void openFileDialog(std::string title, std::string filter)
    {
        if (filter == "")
        {
            filter = ".*";
        }

        fileDialog.SetTitle(title.c_str());
        fileDialog.SetTypeFilters({ filter });
        fileDialog.Open();
    }
}
