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

#endif