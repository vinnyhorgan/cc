#include "timer.h"

#include <chrono>
#include <thread>

namespace timer
{
    void registerTimerAPI(sol::state& lua)
    {
        sol::table timer = lua.create_table();

        timer["getDelta"] = &getDelta;
        timer["getFPS"] = &getFPS;
        timer["getTime"] = &getTime;
        timer["sleep"] = &sleep;

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

    void sleep(float seconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds * 1000)));
    }
}
