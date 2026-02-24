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

class UARTService {
private:
    serial::Serial _serial;
public:
    UARTService(const std::string& port, int baud) {
        _serial.setPort(port);
        _serial.setBaudrate(baud);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        _serial.setTimeout(to);
    }

    bool start() {
        try {
            _serial.open();
            _serial.setFlowcontrol(serial::flowcontrol_none);
            return _serial.isOpen();
        } catch (...) { return false; }
    }

    void testEcho(const std::string& msg) {
        Logger::info("Відправка в порт: " + msg);
        _serial.write(msg);
        _serial.flush(); 

        usleep(100000); 

        if (_serial.available() > 0) {
            std::string result = _serial.read(_serial.available());
            Logger::info("УСПІХ! Отримано ехо: " + result);
        } else {
            Logger::error("Ехо не повернулося.  RX-TX!");
        }
    }
};