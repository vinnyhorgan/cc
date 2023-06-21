#include "event.h"

#include <iostream>

bool shouldQuitz = false; // bruh

namespace event
{
    void registerEventAPI(sol::state& lua)
    {
        sol::table event = lua.create_table();

        event["quit"] = &quit;

        lua["cc"]["event"] = event;
    }

    bool shouldQuit()
    {
        return shouldQuitz || WindowShouldClose();
    }

    void quit()
    {
        shouldQuitz = true;
    }
}
