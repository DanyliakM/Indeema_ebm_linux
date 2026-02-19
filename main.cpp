#include <iostream>
#include <serial/serial.h>
#include <unistd.h>
#include "logger.hpp"
#include "JsonParser.hpp"

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
            Logger::error("Ехо не повернулося. Перевір перемичку RX-TX!");
        }
    }
};

int main() {
    UartDevInfo devInfo;

    if (!JsonParser::parseConfig("config.json", devInfo)) {
        Logger::error("Зупинка програми через помилку конфігурації.");
        return 1;
    }

    UARTService uart(devInfo.path, devInfo.baudrate);
    
    if (uart.start()) {
        Logger::info("Порт " + devInfo.path + " успішно відкрито.");
        uart.testEcho("Indeema_Echo_Test");
    } else {
        Logger::error("Не вдалося відкрити " + devInfo.path);
    }
    
    return 0;
}