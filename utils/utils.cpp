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
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start));
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
    }

    if (value.type() == typeid(std::string)) {
        return std::any_cast<std::string>(value);
    } else if (value.type() == typeid(const char *)) {
        return {std::any_cast<const char *>(value)};
    } else if (value.type() == typeid(char)) {
        return {1, std::any_cast<char>(value)};
    } else if (value.type() == typeid(int)) {
        return std::to_string(std::any_cast<int>(value));
    } else if (value.type() == typeid(float)) {
        return std::to_string(std::any_cast<float>(value));
    } else if (value.type() == typeid(double)) {
        return std::to_string(std::any_cast<double>(value));
    } else if (value.type() == typeid(bool)) {
        return std::any_cast<bool>(value) ? "true" : "false";
    } else if (value.type() == typeid(long)) {
        return std::to_string(std::any_cast<long>(value));
    } else if (value.type() == typeid(unsigned int)) {
        return std::to_string(std::any_cast<unsigned int>(value));
    } else if (value.type() == typeid(unsigned long)) {
        return std::to_string(std::any_cast<unsigned long>(value));
    } else if (value.type() == typeid(std::vector<char>)) {
        auto charVec = std::any_cast<std::vector<char>>(value);
        return {charVec.begin(), charVec.end()};
    } else {
        std::cerr << "Failed to cast type " << value.type().name() << " to string" << std::endl;
        return {};
    }
}