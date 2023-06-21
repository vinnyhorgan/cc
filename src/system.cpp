#include "system.h"

namespace systemc
{
    void registerSystemAPI(sol::state& lua)
    {
        lua.new_enum<OS>("OS", {
            {"Windows", OS::Windows},
            {"Linux", OS::Linux},
            {"MacOS", OS::MacOS}
        });

        sol::table system = lua.create_table();

        lua["cc"]["system"] = system;
    }

    std::string getClipboardText()
    {
        return GetClipboardText();
    }

    OS getOS()
    {
        #if defined(_WIN32)
            return OS::Windows;
        #elif defined(__APPLE__)
            return OS::MacOS;
        #elif defined(__linux__)
            return OS::Linux;
        #endif
    }

    void openURL(std::string url)
    {
        OpenURL(url.c_str());
    }

    void setClipboardText(std::string text)
    {
        SetClipboardText(text.c_str());
    }
}
