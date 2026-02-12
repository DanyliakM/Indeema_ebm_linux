#include "logger.hpp"
#include <memory> 

int main() {
    
    std::unique_ptr<Logger> myLogger = std::make_unique<Logger>();

    myLogger->log("Hello World!");
  
    return 0;
}