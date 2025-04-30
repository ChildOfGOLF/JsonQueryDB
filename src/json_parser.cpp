#include "json_parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

namespace {
    class JsonReader {
        public:
            JsonReader(const std::string& str) : json(str), pos(0) {}

            char peek() const {
                return json[pos];
            }

            char get() {
                return json[pos++];
            }

            void skipSpace() {
                while (pos < json.size() && std::isspace(json[pos])) {
                    pos++;
                }
            }

        private:
            const std::string& json;
            size_t pos;
    };
}

std::string parseString(JsonReader& reader) {
    std::string result;
    if (reader.get() != '"') {
        throw std::runtime_error("Строка должна начинаться с кавычки");
    }

    while (true) {
        char ch = reader.get();
        if (ch == '"') {
            break;
        } else if (ch == '\\') {
            char escaped = reader.get();
            switch (escaped) {
                case '"': result += '"'; break;
                case '\\': result += '\\'; break;
                case '/': result += '/'; break;
                case 'b': result += '\b'; break;
                case 'f': result += '\f'; break;
                case 'n': result += '\n'; break;
                case 'r': result += '\r'; break;
                case 't': result += '\t'; break;
            }
        } else {
            result += ch;
        }
    }

    return result;
}

double parseNumber(JsonReader& reader) {
    std::string numberStr;

    if (reader.peek() == '-') {
        numberStr += reader.get();
    }

    while (std::isdigit(reader.peek())) {
        numberStr += reader.get();
    }

    if (reader.peek() == '.') {
        numberStr += reader.get();
        if (!std::isdigit(reader.peek())) {
            throw std::runtime_error("Ожидалась цифра после точки в числе");
        }
        while (std::isdigit(reader.peek())) {
            numberStr += reader.get();
        }
    }

    if (reader.peek() == 'e' || reader.peek() == 'E') {
        numberStr += reader.get();

        if (reader.peek() == '+' || reader.peek() == '-') {
            numberStr += reader.get();
        }

        while (std::isdigit(reader.peek())) {
            numberStr += reader.get();
        }
    }
        return std::stod(numberStr);
}

JsonValue parseLiteral(JsonReader& reader) {
    if (reader.peek() == 't') {
        if (reader.get() == 't' &&
            reader.get() == 'r' &&
            reader.get() == 'u' &&
            reader.get() == 'e') {
                return true;
            }
    } else if (reader.peek() == 'f') {
        if (reader.get() == 'f' &&
            reader.get() == 'a' &&
            reader.get() == 'l' &&
            reader.get() == 's' &&
            reader.get() == 'e') {
                return false;
            }
    } else if (reader.peek() == 'n') {
        if (reader.get() == 'n' &&
            reader.get() == 'u' &&
            reader.get() == 'l' &&
            reader.get() == 'l') {
                return nullptr;
            }
    }

    throw std::runtime_error("Неизвестный литерал");
}


namespace {
    JsonValue parseValue(JsonReader& reader) {
        reader.skipSpace();
        char ch = reader.peek();

        if (ch == '{') {
            // parseObject
        } else if (ch == '[') {
            //parseArray
        } else if (ch == '"') {
            return parseString(reader);
        } else if (std::isdigit(ch)) {
            return parseNumber(reader);
        } else if (ch == 't' || ch == 'f' || ch == 'n') {
            return parseLiteral(reader);
        }
    }
}

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
    JsonReader reader(json_str);
    reader.skipSpace();
    return parseValue(reader);
}
