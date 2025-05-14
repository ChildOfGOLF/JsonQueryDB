#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include <variant>
#include <vector>
#include <map>

struct JsonObject;
struct JsonArray;

// Универсальный JSON
using JsonValue = std::variant<
    std::string,
    double,
    bool,
    std::nullptr_t,
    JsonObject,
    JsonArray
>;

struct JsonObject {
    std::map<std::string, JsonValue> values;
};

struct JsonArray {
    std::vector<JsonValue> values;
};

// Парсит JSON и возвращает  JsonValue
JsonValue parseFromFile(const std::string& filename);
// Можно добавить parseFromString
JsonValue parseFromString(const std::string& json_str);

// Функция для преобразования JsonValue в строку для вывода
std::string stringifyJsonValue(const JsonValue& value);

#endif