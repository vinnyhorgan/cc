#include "window.h"

std::string currentTitle = "";

namespace window
{
    void registerWindowAPI(sol::state& lua)
    {
        lua.new_enum<ConfigFlags>("Flag", {
            {"VSync", FLAG_VSYNC_HINT},
            {"Fullscreen", FLAG_FULLSCREEN_MODE},
            {"Resizable", FLAG_WINDOW_RESIZABLE},
            {"Undecorated", FLAG_WINDOW_UNDECORATED},
            {"Hidden", FLAG_WINDOW_HIDDEN},
            {"Minimized", FLAG_WINDOW_MINIMIZED},
            {"Maximized", FLAG_WINDOW_MAXIMIZED},
            {"Unfocused", FLAG_WINDOW_UNFOCUSED},
            {"Topmost", FLAG_WINDOW_TOPMOST},
            {"AlwaysRun", FLAG_WINDOW_ALWAYS_RUN},
            {"Transparent", FLAG_WINDOW_TRANSPARENT},
            {"HighDPI", FLAG_WINDOW_HIGHDPI},
            {"MousePassthrough", FLAG_WINDOW_MOUSE_PASSTHROUGH},
            {"MSAA4X", FLAG_MSAA_4X_HINT},
            {"Interlaced", FLAG_INTERLACED_HINT}
        });

        sol::table window = lua.create_table();

        window["getDPIScale"] = &getDPIScale;
        window["getDesktopDimensions"] = &getDesktopDimensions;
        window["getDimensions"] = &getDimensions;
        window["getDisplayCount"] = &getDisplayCount;
        window["getDisplayName"] = &getDisplayName;
        window["getMode"] = &getMode;
        window["getFullscreen"] = &getFullscreen;
        window["getHeight"] = &getHeight;
        window["getPosition"] = &getPosition;
        window["getTitle"] = &getTitle;
        window["getVSync"] = &getVSync;
        window["getWidth"] = &getWidth;
        window["hasFocus"] = &hasFocus;
        window["isMaximized"] = &isMaximized;
        window["isMinimized"] = &isMinimized;
        window["isOpen"] = &isOpen;
        window["isVisible"] = &isVisible;
        window["isResized"] = &isResized;
        window["maximize"] = &maximize;
        window["minimize"] = &minimize;
        window["restore"] = &restore;
        window["setFullscreen"] = &setFullscreen;
        window["setMode"] = &setMode;
        window["setIcon"] = &setIcon;
        window["setPosition"] = &setPosition;
        window["setTitle"] = &setTitle;
        window["setVSync"] = &setVSync;

        lua["cc"]["window"] = window;
    }

    std::tuple<float, float> getDPIScale()
    {
        return std::make_tuple(GetWindowScaleDPI().x, GetWindowScaleDPI().y);
    }

    std::tuple<int, int> getDesktopDimensions(int display)
    {
        return std::make_tuple(GetMonitorWidth(display), GetMonitorHeight(display));
    }

    std::tuple<int, int> getDimensions()
    {
        return std::make_tuple(GetScreenWidth(), GetScreenHeight());
    }

    int getDisplayCount()
    {
        return GetMonitorCount();
    }

    std::string getDisplayName(int display)
    {
        return GetMonitorName(display);
    }

    std::tuple<int, int, sol::table> getMode()
    {
        int width = GetScreenWidth();
        int height = GetScreenHeight();
        sol::table flags = sol::table();

        if (IsWindowState(FLAG_FULLSCREEN_MODE))
        {
            flags.add("Fullscreen");
        }

        if (IsWindowState(FLAG_WINDOW_RESIZABLE))
        {
            flags.add("Resizable");
        }

        if (IsWindowState(FLAG_WINDOW_UNDECORATED))
        {
            flags.add("Undecorated");
        }

        if (IsWindowState(FLAG_WINDOW_HIDDEN))
        {
            flags.add("Hidden");
        }

        if (IsWindowState(FLAG_WINDOW_MINIMIZED))
        {
            flags.add("Minimized");
        }

        if (IsWindowState(FLAG_WINDOW_MAXIMIZED))
        {
            flags.add("Maximized");
        }

        if (IsWindowState(FLAG_WINDOW_UNFOCUSED))
        {
            flags.add("Unfocused");
        }

        if (IsWindowState(FLAG_WINDOW_TOPMOST))
        {
            flags.add("Topmost");
        }

        if (IsWindowState(FLAG_WINDOW_ALWAYS_RUN))
        {
            flags.add("AlwaysRun");
        }

        if (IsWindowState(FLAG_WINDOW_TRANSPARENT))
        {
            flags.add("Transparent");
        }

        if (IsWindowState(FLAG_WINDOW_HIGHDPI))
        {
            flags.add("HighDPI");
        }

        if (IsWindowState(FLAG_WINDOW_MOUSE_PASSTHROUGH))
        {
            flags.add("MousePassthrough");
        }

        if (IsWindowState(FLAG_MSAA_4X_HINT))
        {
            flags.add("MSAA4X");
        }

        if (IsWindowState(FLAG_INTERLACED_HINT))
        {
            flags.add("Interlaced");
        }

        return std::make_tuple(width, height, flags);
    }

    bool getFullscreen()
    {
        return IsWindowFullscreen();
    }

    int getHeight()
    {
        return GetScreenHeight();
    }

    std::tuple<int, int> getPosition()
    {
        return std::make_tuple(GetWindowPosition().x, GetWindowPosition().y);
    }

    std::string getTitle()
    {
        return currentTitle;
    }

    bool getVSync()
    {
        return IsWindowState(FLAG_VSYNC_HINT);
    }

    int getWidth()
    {
        return GetScreenWidth();
    }

    bool hasFocus()
    {
        return IsWindowFocused();
    }

    bool isMaximized()
    {
        return IsWindowMaximized();
    }

    bool isMinimized()
    {
        return IsWindowMinimized();
    }

    bool isOpen()
    {
        return IsWindowReady();
    }

    bool isVisible()
    {
        return !IsWindowHidden();
    }

    bool isResized()
    {
        return IsWindowResized();
    }

    void maximize()
    {
        MaximizeWindow();
    }

    void minimize()
    {
        MinimizeWindow();
    }

    void restore()
    {
        RestoreWindow();
    }

    void setFullscreen(bool fullscreen)
    {
        if (fullscreen && !IsWindowFullscreen())
        {
            ToggleFullscreen();
        }
        else if (!fullscreen && IsWindowFullscreen())
        {
            ToggleFullscreen();
        }
    }

    void setMode(int width, int height, sol::table flags)
    {
        int flag = 0;

        for (auto& kv : flags)
        {
            flag |= kv.second.as<int>();
        }

        SetWindowSize(width, height);
        SetWindowState(flag);
    }

    void setIcon(graphics::Image image)
    {
        Image icon = LoadImageFromTexture(image.texture);
        SetWindowIcon(icon);
        UnloadImage(icon);
    }

    void setPosition(int x, int y)
    {
        SetWindowPosition(x, y);
    }

    void setTitle(std::string title)
    {
        currentTitle = title;
        SetWindowTitle(title.c_str());
    }

    void setVSync(bool vsync)
    {
        if (vsync)
        {
            SetWindowState(FLAG_VSYNC_HINT);
        }
        else
        {
            ClearWindowState(FLAG_VSYNC_HINT);
        }
    }
}
