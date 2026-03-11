#include <iostream>
#include <string>
#include <thread>
#include "JsonParser.hpp"
#include "UartService.hpp"
#include "MqttService.hpp"
#include "logger.hpp"

int main() {
    UartDevInfo uartInfo;
    if (!JsonParser::parseConfig("config.json", uartInfo)) {
        return 1;
    }

    UARTService uart(uartInfo.path, uartInfo.baudrate);
    if (!uart.start()) {
        Logger::error("UART Init failed");
    } else {
        Logger::info("UART Init success");
    }

    MqttService mqtt("tcp://broker.hivemq.com:1883", "myroslav_host_55443322", "indeema/esp32/command", "indeema/esp32/status");
    if (!mqtt.connect()) {
        Logger::error("MQTT Init failed");
    } else {
        Logger::info("MQTT Init success");
    }

    std::jthread uartListener([&uart](std::stop_token st) {
        while (!st.stop_requested()) {
            std::string data = uart.readData();
            if (!data.empty()) {
                Logger::info("UART Status: " + data);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    bool running = true;
    while (running) {
        std::cout << "\n1 - UART\n2 - MQTT\n0 - Exit\n> ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) break;

        if (choice == 1 || choice == 2) {
            int r, g, b;
            std::cout << "R G B: ";
            std::cin >> r >> g >> b;

            std::string payload = std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b);

            if (choice == 1) {
                std::string uart_payload = payload + "\r\n";
                std::cout << "[UART DEBUG] Відправка: " << uart_payload;
                uart.send(uart_payload);
            } else {
                std::cout << "[MQTT DEBUG] Відправка: " << payload << "\n";
                mqtt.send(payload);
            }
        }
    }

    return 0;
}