#include "../include/lox/Token.h"
#include <ostream>
#include <any>
#include <utility>
#include "../include/lox/TokenType.h"

Token::Token(TokenType type, std::string lexeme, std::any literal, int line)
        : type(type), lexeme((std::move(lexeme))), literal(std::move(literal)), line(line) {}

std::string Token::toString() const {
    return ::tokenTypeToString(type) + " " + lexeme + " " + std::to_string(line);
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    return os << token.toString();
}

