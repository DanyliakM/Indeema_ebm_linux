#include <iostream>
#include "JsonParser.hpp"
#include "UartService.hpp"

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
        std::string buffer = "";
        while (true) {
            std::string data = uart.readData();
            if (!data.empty()) {
                buffer += data;
                size_t pos = buffer.find('\n');
                if ( pos != std::string::npos) {
                    std::string completedMessage = buffer.substr(0, pos);
                    Logger::info("Отримано дані: " + data);

                    buffer.erase(0, pos +1);
                }
            }
            usleep(100000);
        }
    } else {
        Logger::error("Не вдалося відкрити " + devInfo.path);
    }
    
    return 0;
}