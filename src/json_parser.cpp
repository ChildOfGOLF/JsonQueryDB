#include "json_parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

JsonValue parseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Ошбика откртыия файла: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // чтение файла вв буфер

    return parseFromString(buffer.str());
}

JsonValue parseFromString(const std::string& json_str) {
    // Пока что возвращает только строку
    std::cout << "Парсинг строки: " << json_str << std::endl;

    return json_str;
}
