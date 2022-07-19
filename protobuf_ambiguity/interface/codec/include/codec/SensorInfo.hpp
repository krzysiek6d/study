#pragma once
#include <string>

struct Details
{
    int time;
    int value1;
    int value2;
    std::string description;
};

struct SensorInfo
{
    std::string name;
    Details data;
};
std::string encode(const SensorInfo& sensorInfo);
void decode(std::string payload, SensorInfo& sensorInfo);
