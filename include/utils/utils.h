#ifndef INTERPRETERS_UTILS_H
#define INTERPRETERS_UTILS_H

#include <vector>
#include <string>
#include <any>

std::vector<std::string> split(const std::string &str, const std::string &delimiter);

std::string ltrim(const std::string &s);

std::string rtrim(const std::string &s, const std::string &charsToRemove);

std::string trim(const std::string &s);

std::string castAnyToString(const std::any &value);

bool isNumber(const std::any &s);

bool isString(const std::any &s);

bool isBool(const std::any &s);

bool isNil(const std::any &s);

bool isEquals(const std::any &a, const std::any &b);

#endif //INTERPRETERS_UTILS_H


