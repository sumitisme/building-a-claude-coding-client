// main code for the claude clone made using openrouterapi
// environmental variables =>   OPENROUTER_API_KEY
//                              VCPKG_ROOT

#include <cstdlib> // for stuff like getenv
#include <iostream>
#include <string>

#include <cpr/cpr.h> // Handles C++ requests. No need to program from socket level if I use this.
#include <nlohmann/json.hpp> // json library since I am using APIs. I'll convert C++ stuff into Json with this.

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    // argv[0] = ./build.sh
    // argv[1] = "-p" 
    // argv[2] = the prompt itself

    if (std::string(argv[1]) != "-p") {
        std::cout << "-p missing as an argument\n";
        return -1;
    }

    std::string prompt = argv[2];

    if (prompt == "") { // using prompt.empty() also works here        std::cout << "no prompt given\n";
        return -2;
    }

    const char* api_key_env = std::getenv("OPENROUTER_API_KEY");

    std::string api_key; // If API_KEY exists in the environment then use it, else keep the api_key value as null
    api_key = (api_key_env != NULL) ? api_key_env : "";

    const char* base_url_env = std::getenv("OPENROUTER_BASE_URL");

    std::string base_url;
    base_url = (base_url_env != NULL) ? base_url_env : "https://openrouter.ai/api/v1";

    if(api_key == "") {
        std::cout << "OPENROUTER_API_KEY not set\n";
        return -3;
    }

    // Making a dictionary to initialize the model used and the messaging format
    json request_body = {
        {"model", "anthropic/claude-haiku-4.5"},
        {"messages", json::array({
            {{"role", "user"}, {"content", prompt}}
        })}
    };

    // http request made using cpr::Post
    cpr::Response response = cpr::Post(
        cpr::Url(base_url + "/chat/completions"), // using "https://openrouter.ai/api/v1/chat/completions" to go to the chatroom
        cpr::Header {
            {"Authorization", "Bearer" + api_key}
            {"Content-Type", "application/json"}
        },
        cpr::Body{request_body.dump()} // converting the json stuff into plain string
    );

    if (response.status_code != 200) { // 200 means stuff is going good
        std::cout << "HTTP error \n";
        std::cout << "Error status code: " << response.status_code << std::endl;
        return -4;
    }

    // converting the text file into string
    json result = json:parse(response.text);

    if (!result.contains("choices") || result["choices"].empty()) {
        std::cout << "No choices in response\n";
        return -5;
    }

    std::cout << result["choices"][0]["message"]["content"].get<std::string> << std::endl; // using get<std::string> to remove all the quotations

    return 0;
}