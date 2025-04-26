#include <iostream>
#include <string>
#include "json_parser.hpp"
#include "query_parser.hpp"

int main() {
    try {
        JsonValue result = parseFromFile("data/data.json");

        std::cout << "Содержимое файла: \n" << std::get<std::string>(result) << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
