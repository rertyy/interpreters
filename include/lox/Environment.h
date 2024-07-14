#ifndef INTERPRETERS_ENVIRONMENT_H
#define INTERPRETERS_ENVIRONMENT_H

#include <unordered_map>
#include <any>
#include <string>
#include <memory>
#include "exceptions/RuntimeError.h"
#include <optional>

class Environment {

public:

    Environment();

    explicit Environment(std::shared_ptr<Environment> enclosing);

    std::shared_ptr<Environment> enclosing;


    std::any get(const Token &name) const;

    void define(const std::string &name, const std::any &value);

    void assign(const Token &name, const std::any &value);

private:
    std::unordered_map<std::string, std::optional<std::any>> values;


};


#endif //INTERPRETERS_ENVIRONMENT_H
