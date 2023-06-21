#pragma once

#include <sol/sol.hpp>
#include <raylib.h>

#include "data.h"

namespace filesystem
{
    // Functions

    // Utility
    void registerFilesystemAPI(sol::state& lua);

    // API
    data::Data loadFileData(std::string filename);
    void saveFileData(std::string filename, data::Data data);
    std::string loadFileText(std::string filename);
    void saveFileText(std::string filename, std::string text);
    bool fileExists(std::string filename);
    bool directoryExists(std::string path);
    bool isFileExtension(std::string filename, std::string ext);
    int getFileSize(std::string filename);
    std::string getFileExtension(std::string filename);
    std::string getFileName(std::string filename);
    std::string getFileNameWithoutExtension(std::string filename);
    std::string getDirectoryPath(std::string filename);
    std::string getPrevDirectoryPath(std::string filename);
    std::string getWorkingDirectory();
    std::string getAppDirectory();
    bool changeDirectory(std::string path);
    bool isPathFile(std::string path);
    sol::table getDirectoryFiles(std::string path, sol::this_state state);
    bool isFileDropped();
    sol::table getDroppedFiles(sol::this_state state);
    float getFileModTime(std::string filename);
}
