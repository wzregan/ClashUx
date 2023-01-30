//
// Created by regan on 2023/1/29.
//
#include <iostream>
#include <HTTPRequest.hpp>
#include <nlohmann/json.hpp>
nlohmann::json GetConfigMessage(){
    nlohmann::json node;
    try
    {
        http::Request request{"http://127.0.0.1:9090/configs"};
        const auto response = request.send("GET", "{}", {
        });
        std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
        node= nlohmann::json::parse(std::string{response.body.begin(), response.body.end()});
        std::cout<<node["mixed-port"];
        return node;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
    return node;

}
int updateConfig(nlohmann::json node){
    try
    {
        http::Request request{"http://127.0.0.1:9090/configs"};
        const std::string body = node.dump();
        const auto response = request.send("PATCH", body, {
                {"Content-Type", "application/json"},
                {"Connection","close"}
        });
    }
    catch (const std::exception& e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
    return 0;

}

int main(){
    auto node = GetConfigMessage();
    node["mixed-port"] = 7890;
    updateConfig(node);
    return 0;
}