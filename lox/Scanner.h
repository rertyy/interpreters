#ifndef INTERPRETERS_SCANNER_H
#define INTERPRETERS_SCANNER_H

#include <string>
#include <vector>
#include "Token.h"
#include <unordered_map>
#include "TokenType.h"

using
enum TokenType;

class Scanner {
public:
    explicit Scanner(std::string source);

    std::vector<Token> scanTokens();

private:
    const static std::unordered_map<std::string, TokenType> keywords;

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

    void string();

    static bool isDigit(char c);

    void number();

    char peekNext();

    void identifier();

    bool isAlpha(char c);

    bool isAlphaNumeric(char c);

    void lineComment();

    void multilineComment();

};


#endif //INTERPRETERS_SCANNER_H
