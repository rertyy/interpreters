#include <iostream>
#include <optional>
#include "../include/lox/Environment.h"
#include "../include/lox/TokenType.h"
#include "../include/utils/utils.h"


Environment::Environment(std::shared_ptr<Environment> enclosing) : enclosing(std::move(enclosing)) {}


void Environment::define(const std::string &name, const std::optional<std::any> &value) {
    values[name] = value;

}

std::any Environment::get(const Token &name) const {
    if (values.find(name.lexeme) != values.end()) {
        auto valueAt = values.at(name.lexeme);
        if (valueAt.has_value()) {
            return valueAt.value();
        } else {
            throw RuntimeError(name, "Uninitialised variable '" + name.lexeme + "'.");
        }

    }
    if (enclosing != nullptr) {
        return enclosing->get(name);
    }

    throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}

void Environment::assign(const Token &name, const std::any &value) {
    if (values.find(name.lexeme) != values.end()) {
        values[name.lexeme] = std::make_optional<>(value);
        return;
    }
    if (enclosing != nullptr) {
        enclosing->assign(name, value);
        return;
    }
    throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");

}

