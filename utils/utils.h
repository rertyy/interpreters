#ifndef INTERPRETERS_UTILS_H
#define INTERPRETERS_UTILS_H

#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string &str, const std::string &delimiter);

std::string ltrim(const std::string &s);

std::string rtrim(const std::string &s);

std::string trim(const std::string &s);


#endif //INTERPRETERS_UTILS_H


