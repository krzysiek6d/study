//
// Created by pawluch on 25.07.22.
//

#ifndef STATIC_INITIALIZATION_IN_HEADERS_INFO_DATA_H
#define STATIC_INITIALIZATION_IN_HEADERS_INFO_DATA_H


#include <map>
#include <string>
#include "my_enum.h"

const std::map<EType, std::map<std::string, std::string>> huge_map =
        {
                {
                        EType::EType1,
                        {
                                {"key1_1", "value"},
                                {"key1_2", "value"},
                                {"key1_3", "value"},
                                {"key1_4", "value"},
                                {"key1_5", "value"},
                                {"key1_6", "value"},
                        },
                },
                {
                        EType::EType2,
                        {
                                {"key2_1", "value"},
                                {"key2_2", "value"},
                                {"key2_3", "value"},
                                {"key2_4", "value"},
                                {"key2_5", "value"},
                                {"key2_6", "value"},
                        },
                },
                {
                        EType::EType3,
                        {
                                {"key3_1", "value"},
                                {"key3_2", "value"},
                                {"key3_3", "value"},
                                {"key3_4", "value"},
                                {"key3_5", "value"},
                                {"key3_6", "value"},
                        },
                },
        };

std::string getvalues(EType type);

#endif //STATIC_INITIALIZATION_IN_HEADERS_INFO_DATA_H
