#include <vector>
#include <string>
#include <iostream>

class Logger {
    std::vector<std::string> history; 
public:
    void log(const std::string& message);
    void printHistory();
};