#ifndef INTERPRETERS_TOKEN_H
#define INTERPRETERS_TOKEN_H

#include <string>
#include <any>
#include <ostream>
#include "TokenType.h"


class Token {
public:
    Token(TokenType type, std::string lexeme, std::any literal, int line);

    std::string toString() const;

    // Friend declaration for operator<<
//    friend std::ostream &operator<<(std::ostream &os, const Token &token);

private:
    const TokenType type;
    const std::string lexeme;
    const std::any literal;
    const int line;
};

#endif //INTERPRETERS_TOKEN_H
