#ifndef PARAM_HPP_
#define PARAM_HPP_

#include <string>
#include <any>

enum class ParamType { INT, FLOAT, STRING, BOOL, UNKNOWN };

struct Param {
    std::string name;
    ParamType type;
};

inline ParamType parseType(const std::string& type_str) {
    if (type_str == "int") return ParamType::INT;
    if (type_str == "float") return ParamType::FLOAT;
    if (type_str == "string") return ParamType::STRING;
    if (type_str == "bool") return ParamType::BOOL;
    return ParamType::UNKNOWN;
}

inline std::string paramTypeToString(ParamType type) {
    switch (type) {
        case ParamType::INT: return "int";
        case ParamType::FLOAT: return "float";
        case ParamType::STRING: return "string";
        case ParamType::BOOL: return "bool";
        default: return "unknown";
    }
}

#endif  // PARAM_HPP_
