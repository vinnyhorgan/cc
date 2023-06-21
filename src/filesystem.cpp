#include "filesystem.h"

#include <spdlog/spdlog.h>

namespace filesystem
{
    void registerFilesystemAPI(sol::state& lua)
    {
        sol::table filesystem = lua.create_table();

        filesystem["loadFileData"] = &loadFileData;
        filesystem["saveFileData"] = &saveFileData;
        filesystem["loadFileText"] = &loadFileText;
        filesystem["saveFileText"] = &saveFileText;
        filesystem["fileExists"] = &fileExists;
        filesystem["directoryExists"] = &directoryExists;
        filesystem["isFileExtension"] = &isFileExtension;
        filesystem["getFileSize"] = &getFileSize;
        filesystem["getFileExtension"] = &getFileExtension;
        filesystem["getFileName"] = &getFileName;
        filesystem["getFileNameWithoutExtension"] = &getFileNameWithoutExtension;
        filesystem["getDirectoryPath"] = &getDirectoryPath;
        filesystem["getPrevDirectoryPath"] = &getPrevDirectoryPath;
        filesystem["getWorkingDirectory"] = &getWorkingDirectory;
        filesystem["getAppDirectory"] = &getAppDirectory;
        filesystem["changeDirectory"] = &changeDirectory;
        filesystem["isPathFile"] = &isPathFile;
        filesystem["getDirectoryFiles"] = &getDirectoryFiles;
        filesystem["isFileDropped"] = &isFileDropped;
        filesystem["getDroppedFiles"] = &getDroppedFiles;
        filesystem["getFileModTime"] = &getFileModTime;

        lua["cc"]["filesystem"] = filesystem;
    }

    data::Data loadFileData(std::string filename)
    {
        data::Data data;

        unsigned int size = 0;
        unsigned char *fileData = LoadFileData(filename.c_str(), &size);

        if (fileData != NULL)
        {
            for (int i = 0; i < (int)size; i++)
            {
                data.data.push_back(fileData[i]);
            }

            UnloadFileData(fileData);

            spdlog::info("Loaded file data: {}, size: {}", filename, size);
        }
        else
        {
            spdlog::error("Failed to load file data: {}", filename);
        }

        return data;
    }

    void saveFileData(std::string filename, data::Data data)
    {
        unsigned char *fileData = new unsigned char[data.data.size()];

        for (int i = 0; i < (int)data.data.size(); i++)
        {
            fileData[i] = data.data[i];
        }

        SaveFileData(filename.c_str(), fileData, data.data.size());

        delete[] fileData;

        spdlog::info("Saved file data: {}, size: {}", filename, data.data.size());
    }

    std::string loadFileText(std::string filename)
    {
        std::string text;

        char *fileText = LoadFileText(filename.c_str());

        if (fileText != NULL)
        {
            text = fileText;

            UnloadFileText(fileText);

            spdlog::info("Loaded file text: {}", filename);
        }
        else
        {
            spdlog::error("Failed to load file text: {}", filename);
        }

        return text;
    }

    void saveFileText(std::string filename, std::string text)
    {
        SaveFileText(filename.c_str(), const_cast<char*>(text.c_str()));

        spdlog::info("Saved file text: {}", filename);
    }

    bool fileExists(std::string filename)
    {
        return FileExists(filename.c_str());
    }

    bool directoryExists(std::string path)
    {
        return DirectoryExists(path.c_str());
    }

    bool isFileExtension(std::string filename, std::string ext)
    {
        return IsFileExtension(filename.c_str(), ext.c_str());
    }

    int getFileSize(std::string filename)
    {
        return GetFileLength(filename.c_str());
    }

    std::string getFileExtension(std::string filename)
    {
        return GetFileExtension(filename.c_str());
    }

    std::string getFileName(std::string filename)
    {
        return GetFileName(filename.c_str());
    }

    std::string getFileNameWithoutExtension(std::string filename)
    {
        return GetFileNameWithoutExt(filename.c_str());
    }

    std::string getDirectoryPath(std::string filename)
    {
        return GetDirectoryPath(filename.c_str());
    }

    std::string getPrevDirectoryPath(std::string filename)
    {
        return GetPrevDirectoryPath(filename.c_str());
    }

    std::string getWorkingDirectory()
    {
        return GetWorkingDirectory();
    }

    std::string getAppDirectory()
    {
        return GetApplicationDirectory();
    }

    bool changeDirectory(std::string path)
    {
        return ChangeDirectory(path.c_str());
    }

    bool isPathFile(std::string path)
    {
        return IsFileDropped();
    }

    sol::table getDirectoryFiles(std::string path, sol::this_state state)
    {
        sol::state_view lua(state);

        sol::table files = lua.create_table();

        FilePathList list = LoadDirectoryFiles(path.c_str());

        for (int i = 0; i < (int)list.count; i++)
        {
            files.add(list.paths[i]);
        }

        UnloadDirectoryFiles(list);

        return files;
    }

    bool isFileDropped()
    {
        return IsFileDropped();
    }

    sol::table getDroppedFiles(sol::this_state state)
    {
        sol::state_view lua(state);

        sol::table files = lua.create_table();

        FilePathList list = LoadDroppedFiles();

        for (int i = 0; i < (int)list.count; i++)
        {
            files.add(list.paths[i]);
        }

        UnloadDroppedFiles(list);

        return files;
    }

    float getFileModTime(std::string filename)
    {
        return GetFileModTime(filename.c_str());
    }
}
