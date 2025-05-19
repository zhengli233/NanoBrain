#ifndef PARAM_HPP_
#define PARAM_HPP_

#include <string>
#include <any>

enum class ParamType { INT, FLOAT, STRING, BOOL, UNKNOWN };
enum class ParamScope { TASK, PRIMITIVE };

struct Param {
    std::string name;
    ParamType type;
    ParamScope scope;
    std::any value;
    bool is_assigned = false;
    int request_count = 0;
};

inline ParamType parseType(const std::string& type_str) {
    if (type_str == "int") return ParamType::INT;
    if (type_str == "float") return ParamType::FLOAT;
    if (type_str == "string") return ParamType::STRING;
    if (type_str == "bool") return ParamType::BOOL;
    return ParamType::UNKNOWN;
}

inline ParamScope parseScope(const std::string& scope_str) {
    if (scope_str == "task") return ParamScope::TASK;
    if (scope_str == "primitive") return ParamScope::PRIMITIVE;
    return ParamScope::PRIMITIVE;  // 默认是 primitive
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
