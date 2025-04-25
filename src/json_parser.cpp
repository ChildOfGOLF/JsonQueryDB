#include "json_parser.hpp"
#include <fstream>
#include <stdexcept>

JsonValue parseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Ошбика откртыия файла: " + filename);
    }
    // Написать парсер
    return JsonArray{};
}
