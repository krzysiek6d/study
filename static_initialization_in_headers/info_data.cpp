//
// Created by pawluch on 25.07.22.
//
#include "info_data.h"

std::string getvalues(EType type)
{
    std::string result{};
    for (auto [key, value]: huge_map.at(type))
    {
        result += std::string("{") + key + std::string(": ") + value + std::string("}");
    }
    return result;
}