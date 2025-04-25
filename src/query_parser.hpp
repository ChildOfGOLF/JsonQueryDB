#ifndef QUERY_PARSER_HPP
#define QUERY_PARSER_HPP

#include <string>
#include <vector>

// Условие
// Напримр id > 7
struct Condition {
    std::string field;
    std::string op;
    std::string value;
};

// Запрос
struct Query {
    std::vector<std::string> selectFields;    // Поля
    std::vector<Condition> whereConditions;   // Условия
    // Нужно написать булеву логику для and or
};

// Парсит строку запроса в структуру
Query parseQuery(const std::string& input);

#endif
