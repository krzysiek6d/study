#include <iostream>
#include <codec/SensorInfo.hpp>
#include <google/protobuf/text_format.h>

void findAsciiThatCanBeAmbigious(char beginChar, char endChar)
{
    for (char c = beginChar; c <= endChar; c++)
    {
        if ((c & 0b00000111) == 0) {
            int filedNumber = c >> 3;
            printf("possible ambigiouity: {char: %c, fieldNo: %d}\n", c, filedNumber);
        }
    }
}

int main() {
    //findAsciiThatCanBeAmbigious('a', 'z');
    //findAsciiThatCanBeAmbigious('A', 'Z');

    SensorInfo sensor;
    sensor.name = "xEpRhRHOPRX!";
    //sensor.name = "sensor1";
    sensor.data.time = 2341234;
    sensor.data.value1 = 12;
    sensor.data.value2 = 99;
    sensor.data.description = "this is awesome";

    auto encoded = encode(sensor);
    std::cout << encoded ;

    return 0;
}


