#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <vector>
#include <string>
#include <iostream>



class Logger {
    std::vector<std::string> history; 
public:
    void log(const std::string& message);
    void printHistory();
};

#endif