#include "Token.h"
#include <ostream>
#include <any>
#include <utility>
#include "TokenType.h"

Token::Token(TokenType type, std::string lexeme, std::any literal, int line)
        : type(type), lexeme((std::move(lexeme))), literal(std::move(literal)), line(line) {}

TokenType Token::getType() const {
    return type;
}

std::string Token::getLexeme() const {
    return lexeme;
}

std::any Token::getLiteral() const {
    return literal;
}

int Token::getLine() const {
    return line;
}

std::string Token::toString() const {
    return ::tokenTypeToString(type) + " " + lexeme + " " + std::to_string(line);
}


//std::ostream &operator<<(std::ostream &os, const Token &token) {
//    return os << token.tokenTypeToString() << std::endl;
//}
