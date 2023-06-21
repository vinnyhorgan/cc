#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

#include <vector>

namespace data
{
    // Types
    class Data
    {
    public:
        std::vector<unsigned char> data;

        std::string type();
        void unload();

        int getSize();
        sol::table getData(sol::this_state state);
        void append(sol::table data);
    };

    // Functions

    // Utility
    void registerDataAPI(sol::state& lua);

    // API
    Data newData();
    void printTable(sol::table table);
}
