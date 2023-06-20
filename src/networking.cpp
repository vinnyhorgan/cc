#include "networking.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

namespace networking
{
    void registerNetworkingAPI(sol::state& lua)
    {
        sol::table networking = lua.create_table();

        networking["httpGet"] = &httpGet;

        lua["cc"]["networking"] = networking;
    }

    std::string httpGet(std::string url)
    {
        httplib::Client client(url.c_str());

        auto response = client.Get("/");

        if (response)
        {
            if (response->status == 200)
            {
                return response->body;
            }
            else
            {
                return "Error: " + std::to_string(response->status);
            }
        }
        else
        {
            // auto err = response.error();

            return "Error";
        }
    }
}
