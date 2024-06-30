#include "../include/utils/utils.h"


#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>


std::vector<std::string> split(const std::string &str, const std::string &delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        tokens.emplace_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    tokens.emplace_back(str.substr(start));
    return tokens;
}

std::string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t");
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(" \t");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

std::string castAnyToString(const std::any &value) {
    if (!value.has_value()) {
        std::cerr << "Failed to cast empty value to string" << std::endl;
        return {};
    } else if (isString(value)) {
        return std::any_cast<std::string>(value);
    } else if (isNumber(value)) {
        std::string doubleString = std::to_string(std::any_cast<double>(value));
        if (doubleString.size() >= 2 && doubleString.substr(doubleString.size() - 2) == ".0") {
            return doubleString.substr(0, doubleString.size() - 2);
        } else {
            return doubleString;
        }
    } else if (isBool(value)) {
        return std::any_cast<bool>(value) ? "true" : "false";
    } else if (isNil(value)) {
        return "nil";
    } else {
        std::cerr << "Failed to cast type " << value.type().name() << " to string" << std::endl;
        return {};
    }
}


bool isNumber(const std::any &s) {
    return s.type() == typeid(double);
}

bool isString(const std::any &s) {
    return s.type() == typeid(std::string);
}

bool isBool(const std::any &s) {
    return s.type() == typeid(bool);
}

bool isNil(const std::any &s) {
    return s.type() == typeid(std::nullptr_t);
}


bool isEquals(const std::any &a, const std::any &b) {
    if (!a.has_value() || !b.has_value()) {
        return !a.has_value() && !b.has_value();
    } else if (isNil(a) && isNil(b)) {
        return true;
    } else if (isNumber(a) && isNumber(b)) {
        return std::any_cast<double>(a) == std::any_cast<double>(b);
    } else if (isString(a) && isString(b)) {
        return std::any_cast<std::string>(a) == std::any_cast<std::string>(b);
    } else if (isBool(a) && isBool(b)) {
        return std::any_cast<bool>(a) == std::any_cast<bool>(b);
    } else {
        return false;
    }
}