#pragma once
#include <string>

struct UartDevInfo {
    std::string path;
    int baudrate;
};

class JsonParser {
public:
    static bool parseConfig(const std::string& filePath, UartDevInfo& info);
};