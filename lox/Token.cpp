#include "Token.h"
#include <ostream>
#include <any>
#include <utility>
#include "TokenType.h"

Token::Token(TokenType type, std::string lexeme, std::any literal, int line)
        : type(type), lexeme((std::move(lexeme))), literal(std::move(literal)), line(line) {}

std::string Token::toString() const {
    return ::tokenTypeToString(type) + " " + lexeme + " " + std::to_string(line);
}

