//
// Created by regan on 2023/1/28.
//
#include "inc/SysUtil.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

int ping(const char * ip){
    int fd[2];
    pipe(fd);
    int pid = fork();
    if(pid==0){
        // children
        close(1); // 关闭stdout
        dup(fd[1]);
        char command[64];
        sprintf(command,"ping %s -c 1 -w 2",ip);
        system(command);
        exit(1);
    }else{
        // parent
        char buf[512];
        read(fd[0],buf,512);
        std::string  str(buf);
        if(str.find("0 received,")!=std::string::npos){
            return 9999;
        }
        int pos = str.find("time=");
        int pos2 = str.find(" ms");
        std::string  ret= str.substr(pos+5,pos2-pos-1-4);
        return std::stoi(ret);
    }
}

nlohmann::json GetConfigMessage(){
    nlohmann::json node;
    try
    {
        http::Request request{"http://127.0.0.1:9090/configs"};
        const auto response = request.send("GET", "{}", {
        });
        node= nlohmann::json::parse(std::string{response.body.begin(), response.body.end()});
        return node;
    }
    catch (const std::exception& e)
    {
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
    }
    return 0;

}
