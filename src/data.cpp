#include "data.h"

#include <iostream>

namespace data
{
    std::string Data::type()
    {
        return "Data";
    }

    void Data::unload()
    {
        std::vector<unsigned char>().swap(data);
    }

    int Data::getSize()
    {
        return data.size();
    }

    sol::table Data::getData(sol::this_state state)
    {
        sol::state_view lua(state);

        sol::table data = lua.create_table();

        for (int i = 0; i < (int)this->data.size(); i++)
        {
            data[i + 1] = this->data[i];
        }

        return data;
    }

    void Data::append(sol::table data)
    {
        for (int i = 0; i < (int)data.size(); i++)
        {
            this->data.push_back(data[i + 1]);
        }
    }

    void registerDataAPI(sol::state& lua)
    {
        sol::usertype<Data> data_type = lua.new_usertype<Data>("Data");

        data_type["type"] = &Data::type;
        data_type["unload"] = &Data::unload;
        data_type["getSize"] = &Data::getSize;
        data_type["getData"] = &Data::getData;
        data_type["append"] = &Data::append;

        sol::table data = lua.create_table();

        data["newData"] = &newData;
        data["printTable"] = &printTable;

        lua["cc"]["data"] = data;
    }

    Data newData()
    {
        Data data;

        return data;
    }

    void printTable(sol::table table)
    {
        std::cout << "{\n";

        for (const auto& pair : table) {
            std::cout << "    ";

            if (pair.first.is<std::string>())
            {
                std::cout << pair.first.as<std::string>();
            }
            else
            {
                std::cout << "[" << pair.first.as<int>() << "]";
            }

            std::cout << " = ";
            sol::object value = pair.second;

            switch (value.get_type())
            {
                case sol::type::number:
                    std::cout << value.as<double>();
                    break;
                case sol::type::boolean:
                    std::cout << std::boolalpha << value.as<bool>();
                    break;
                case sol::type::string:
                    std::cout << "\"" << value.as<std::string>() << "\"";
                    break;
                case sol::type::table:
                    printTable(value.as<sol::table>());
                    break;
                default:
                    std::cout << "nil";
            }

            std::cout << ",\n";
        }

        std::cout << "}\n";
    }
}
