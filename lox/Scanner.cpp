#include "Scanner.h"
#include "Lox.h"

#include <utility>

using
enum TokenType;

Scanner::Scanner(std::string source) : source(std::move(source)) {}

const std::unordered_map<std::string, TokenType> Scanner::keywords{
        {"and",    AND},
        {"class",  CLASS},
        {"else",   ELSE},
        {"false",  FALSE},
        {"for",    FOR},
        {"fun",    FUN},
        {"if",     IF},
        {"nil",    NIL},
        {"or",     OR},
        {"print",  PRINT},
        {"return", RETURN},
        {"super",  SUPER},
        {"this",   THIS},
        {"true",   TRUE},
        {"var",    VAR},
        {"while",  WHILE}
};


bool Scanner::isAtEnd() {
    return current >= source.length();
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        // We are at the beginning of the next lexeme.
        start = current;
        scanToken();
    }

    tokens.emplace_back(EOFTOKEN, "", nullptr, line);
    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(':
            addToken(LEFT_PAREN);
            break;
        case ')':
            addToken(RIGHT_PAREN);
            break;
        case '{':
            addToken(LEFT_BRACE);
            break;
        case '}':
            addToken(RIGHT_BRACE);
            break;
        case ',':
            addToken(COMMA);
            break;
        case '.':
            addToken(DOT);
            break;
        case '-':
            addToken(MINUS);
            break;
        case '+':
            addToken(PLUS);
            break;
        case ';':
            addToken(SEMICOLON);
            break;
        case '*':
            addToken(STAR);
            break;
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if (peek() == '/') lineComment();
            else if (peek() == '*') multilineComment();
            else addToken(SLASH);

            break;


        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            ++line;
            break;
        case '"':
            string();
            break;
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                Lox::error(line, "Unexpected character.");
            }
            break;
    }
}


void Scanner::addToken(TokenType type) {
    addToken(type, nullptr);
}

void Scanner::addToken(TokenType type, const std::any &literal) {
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal, line);
}

char Scanner::advance() {
    return source[current++];
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;

    ++current;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') ++line;
        advance();
    }

    if (isAtEnd()) {
        Lox::error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(STRING, value);
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

void Scanner::number() {
    while (isDigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();

        while (isDigit(peek())) advance();
    }

    addToken(NUMBER,
             std::stod(source.substr(start, current - start)));
}

char Scanner::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current);
    auto keywordIt = keywords.find(text);
    TokenType type = (keywordIt != keywords.end()) ? keywordIt->second : IDENTIFIER;

    addToken(type);

}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

void Scanner::lineComment() {
    advance();
    // A comment goes until the end of the line.
    while (peek() != '\n' && !isAtEnd()) advance();
}

void Scanner::multilineComment() {
    advance();
    // Multi-line comment
    while (!isAtEnd()) {
        if (peek() == '*' && peekNext() == '/') {
            advance();
            advance();
            break;
        }
        if (peek() == '\n') ++line;
        advance();
    }
    if (isAtEnd()) {
        Lox::error(line, "Unterminated comment.");
    }

}


