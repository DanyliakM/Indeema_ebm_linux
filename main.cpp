#include <iostream>
#include "logger.hpp"
#include "JsonParser.hpp"

int main() {
    UartDevInfo devInfo;

    if (!JsonParser::parseConfig("config.json", devInfo)) {
        Logger::error("Зупинка програми, помилкa конфігурації.");
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