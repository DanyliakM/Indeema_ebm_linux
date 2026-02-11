#include "logger.hpp"
#include <iostream>
#include <fstream> // Бібліотека для роботи з файлами

void Logger::log(const std::string& message) {
    // 1. Вивід у консоль
    std::cout << "[LOG]: " << message << std::endl;
    
    // 2. Збереження у вектор
    history.push_back(message);

    // 3. Запис у файл (режим append - додавання в кінець)
    std::ofstream file("system.log", std::ios::app);
    if (file.is_open()) {
        file << message << std::endl;
    }
}