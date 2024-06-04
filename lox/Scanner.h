#ifndef INTERPRETERS_SCANNER_H
#define INTERPRETERS_SCANNER_H

#include <string>
#include <vector>
#include "Token.h"

class Scanner {
    Scanner(std::string source);

private:
    int start = 0;
    int current = 0;
    int line = 1;

    const std::string source;
    std::vector<Token> tokens;

    bool isAtEnd();

    void scanToken();

    char advance();

    void addToken(TokenType type);

    void addToken(TokenType type, const std::any &literal);

    bool match(char expected);

    char peek();
};


#endif //INTERPRETERS_SCANNER_H
