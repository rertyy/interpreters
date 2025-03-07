#include "../include/lox/TokenType.h"
#include <unordered_map>
#include <string>

const std::unordered_map<int, std::string> tokenTypeMap = {
        {0,  "LEFT_PAREN"},
        {1,  "RIGHT_PAREN"},
        {2,  "LEFT_BRACE"},
        {3,  "RIGHT_BRACE"},
        {4,  "COMMA"},
        {5,  "DOT"},
        {6,  "MINUS"},
        {7,  "PLUS"},
        {8,  "SEMICOLON"},
        {9,  "SLASH"},
        {10, "STAR"},
        {11, "BANG"},
        {12, "BANG_EQUAL"},
        {13, "EQUAL"},
        {14, "EQUAL_EQUAL"},
        {15, "GREATER"},
        {16, "GREATER_EQUAL"},
        {17, "LESS"},
        {18, "LESS_EQUAL"},
        {19, "IDENTIFIER"},
        {20, "STRING"},
        {21, "NUMBER"},
        {22, "AND"},
        {23, "CLASS"},
        {24, "ELSE"},
        {25, "FALSE"},
        {26, "FUN"},
        {27, "FOR"},
        {28, "IF"},
        {29, "NIL"},
        {30, "OR"},
        {31, "PRINT"},
        {32, "RETURN"},
        {33, "SUPER"},
        {34, "THIS"},
        {35, "TRUE"},
        {36, "VAR"},
        {37, "WHILE"},
        {38, "EOF_TOKEN"},
        {39, "QUESTION"},
        {40, "COLON"},
        {41, "BREAK"},
        {42, "CONTINUE"}
};

std::string tokenTypeToString(TokenType type) {
    return tokenTypeMap.at(static_cast<int>(type));
}

