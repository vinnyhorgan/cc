#include "filesystem.h"

namespace filesystem
{
    void registerFilesystemAPI(sol::state& lua)
    {
        sol::table filesystem = lua.create_table();

        lua["cc"]["filesystem"] = filesystem;
    }
}
