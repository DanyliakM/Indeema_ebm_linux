#include "logger.hpp"
#include <iostream>
#include <fstream> 

void Logger::log(const std::string& message) {
 
    std::cout << "[LOG]: " << message << std::endl;
    
    history.push_back(message);

    std::ofstream file("system.log", std::ios::app);
    if (file.is_open()) {
        file << message << std::endl;
    }
}