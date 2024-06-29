#ifndef INTERPRETERS_ENVIRONMENT_H
#define INTERPRETERS_ENVIRONMENT_H

#include <unordered_map>
#include <any>
#include <string>
#include "RuntimeError.h"


class Environment {

private:
    std::unordered_map<std::string, std::any> values;

public:
    std::any get(const Token &name) const;

    void define(const std::string &name, const std::any &value);
};


#endif //INTERPRETERS_ENVIRONMENT_H
