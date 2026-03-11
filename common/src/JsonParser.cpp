#include "JsonParser.hpp"
#include "logger.hpp"
#include <fstream>
#include <jsoncpp/json/json.h>

bool JsonParser::parseConfig(const std::string& filePath, UartDevInfo& info) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Logger::error("Не вдалося відкрити файл конфігурації: " + filePath);
        return false;
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    if (!Json::parseFromStream(builder, file, &root, &errs)) {
        Logger::error("Помилка парсингу JSON: " + errs);
        return false;
    }

    if (!root.isMember("uart") || !root["uart"].isMember("device") || !root["uart"].isMember("baudrate")) {
        Logger::error("Невірний формат JSON: відсутні поля 'uart', 'device' або 'baudrate'");
        return false;
    }

    info.path = root["uart"]["device"].asString();
    info.baudrate = root["uart"]["baudrate"].asInt();

    return true;
}