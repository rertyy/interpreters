#ifndef INTERPRETERS_PARSER_H
#define INTERPRETERS_PARSER_H

#include <vector>
#include <memory>
#include <algorithm>
#include <valarray>
#include "Token.h"
#include "TokenType.h"
#include "Expr.h"
#include "Lox.h"
#include "Stmt.h"

using
enum TokenType;

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

    class ParseError : public std::runtime_error {
    public:
        ParseError() : std::runtime_error("Parse error") {}
    };


    std::shared_ptr<Expr> parse();

    std::vector<std::shared_ptr<Stmt>> parseSequence();

private:
    std::vector<Token> tokens;
    int current = 0;

    /**
     * Check if the current token matches any of the given types, and advance if it does
     * @param types
     * @return
     */
    bool match(const std::vector<TokenType> &types);

    /**
     * Check if the current token matches the given type, without advancing
     * @param type
     * @return
     */
    bool check(const TokenType &type);

    Token &advance();

    bool isAtEnd();

    Token &peek();

    Token &previous();

    // Start
    std::shared_ptr<Expr> expression();

    // Binary functions
    std::shared_ptr<Expr> equality();

    std::shared_ptr<Expr> comparison();

    std::shared_ptr<Expr> term();

    std::shared_ptr<Expr> factor();

    std::shared_ptr<Expr> unary();

    std::shared_ptr<Expr> primary();

    // Look for closing brackets
    Token &consume(TokenType type, const std::string &message);

    ParseError error(const Token &token, const std::string &message);

    // Checks until statement boundary before synchronizing state for error handling
    void synchronize();

    std::shared_ptr<Expr> sequence();

    std::shared_ptr<Stmt> statement();

    std::shared_ptr<Stmt> expressionStatement();

    std::shared_ptr<Stmt> printStatement();
};


#endif //INTERPRETERS_PARSER_H
