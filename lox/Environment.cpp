#include "../include/lox/Environment.h"
#include "../include/lox/TokenType.h"

void Environment::define(const std::string &name, const std::any &value) {
    values[name] = value;

}

std::any Environment::get(const Token &name) const {
    if (values.find(name.lexeme) != values.end()) {
        return values.at(name.lexeme);
    }
    throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}

void Environment::assign(const Token &name, const std::any &value) {
    if (values.find(name.lexeme) != values.end()) {
        values[name.lexeme] = value;
        return;
    }
    throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");

}

