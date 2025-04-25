#include <iostream>
#include <string>
#include "json_parser.hpp"
#include "query_parser.hpp"

int main() {
    std::cout << "JsonQueryDB. Комнады: load, query, exit\n";

    JsonValue data;
    bool dataLoad = false;
    std::string line;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        if (line == "exit") {
            break;
        } 
        else if (line.rfind("load ", 0) == 0) {
            std::string filename = line.substr(5);
            try {
                data = parseFromFile(filename);
                dataLoad = true;
                std::cout << "Загужено из:  " << filename << "\n";
            } catch (const std::exception& e) {
                std::cerr << "Ошибка: " << e.what() << "\n";
            }
        } 
        else if (line.rfind("query ", 0) == 0) {
            std::string qstr = line.substr(6);
            Query q = parseQuery(qstr);
            std::cout << "Выбраные поля:";
            for (auto& f : q.selectFields) {
                std::cout << " " << f;
            }
            std::cout << "\n";
        } 
        else {
            std::cout << "Используйте 'load', 'query', или 'exit'\n";
        }
    }

    return 0;
}
