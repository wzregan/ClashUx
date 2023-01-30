// Created by regan on 2023/1/28.
//

#ifndef CLASHUX_SYSUTIL_H
#define CLASHUX_SYSUTIL_H
#include <HTTPRequest.hpp>
#include <nlohmann/json.hpp>
int ping(const char *);
nlohmann::json GetConfigMessage();
int updateConfig(nlohmann::json node);



#endif //CLASHUX_SYSUTIL_H
