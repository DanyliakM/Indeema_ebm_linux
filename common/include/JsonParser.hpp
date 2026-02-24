#pragma once
#include <string>
#include <serial/serial.h> 
#include <unistd.h>        
#include "logger.hpp"      

struct UartDevInfo {
    std::string path;
    int baudrate;
};

class JsonParser {
public:
    static bool parseConfig(const std::string& filePath, UartDevInfo& info);
};

