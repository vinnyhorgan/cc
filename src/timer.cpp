#include "timer.h"

namespace timer
{
    void registerTimerAPI(sol::state& lua)
    {
        sol::table timer = lua.create_table();

        timer["getDelta"] = &getDelta;
        timer["getFPS"] = &getFPS;
        timer["getTime"] = &getTime;

        lua["cc"]["timer"] = timer;
    }

    float getDelta()
    {
        return GetFrameTime();
    }

    float getFPS()
    {
        return GetFPS();
    }

    float getTime()
    {
        return GetTime();
    }
}
