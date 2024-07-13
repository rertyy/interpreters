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

/*
 * ============ GRAMMAR =============
 * program        → statement* EOF ;
 *
 * statement      → exprStmt
 *                | forStmt
 *                | ifStmt
 *                | printStmt
 *                | returnStmt
 *                | whileStmt
 *                | block ;*
 *
 * block          → "{" declaration* "}" ;
 *
 * declaration    → funDecl
 *                | varDecl
 *                | statement ;
 * varDecl        → "var" IDENTIFIER ( "=" expression )? ";" ;
 *
 * funDecl        → "fun" function ;
 * function       → IDENTIFIER "(" parameters? ")" block ;
 * parameters     → IDENTIFIER ( "," IDENTIFIER )* ;
 * arguments      → expression ( "," expression )* ;
 *
 * exprStmt       → expression ";" ;
 * forStmt        → "for" "(" ( varDecl | exprStmt | ";" )
 *                  expression? ";"
 *                  expression? ")" statement ;
 * ifStmt         → "if" "(" expression ")" statement
 *                   ( "else" statement )? ;
 * printStmt      → "print" expression ";" ;
 * returnStmt     → "return" expression? ";" ;
 * whileStmt      → "while" "(" expression ")" statement ;
 *
 * expression     → commaOperator ;
 * commaOperator  → ternary ( "," ternary )*
 * ternary        → assignment "?" assignment ":" ternary ;
 * // Note: ternary is right associative, so a == 1 ? "one" : a == 2 ? "two" : "many" is a == 1 ? "one" : (a == 2 ? "two" : "many")
 * assignment     → IDENTIFIER "=" assignment
 *                | logic_or ;
 *
 * logic_or       → logic_and ( "or" logic_and )* ;
 * logic_and      → equality ( "and" equality )* ;
 * equality       → comparison ( ( "!=" | "==" ) comparison )* ;
 * comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
 * term           → factor ( ( "-" | "+" ) factor )* ;
 * factor         → unary ( ( "/" | "*" ) unary )* ;
 * unary          → ( "!" | "-" ) unary | call;
 * call           → primary ( "(" arguments? ")" )* ;
 * primary        → NUMBER | STRING | "true" | "false" | "nil"
 *                | "(" expression ")" | IDENTIFIER ;
 */

// The syntax doesn't care that "and", "or" expressions  short-circuit. That’s a semantic concern.


class Parser {
public:
    explicit Parser(std::vector<Token> tokens);

    class ParseError : public std::runtime_error {
    public:
        ParseError() : std::runtime_error("Parse error") {}
    };


    std::shared_ptr<Expr> parseExpr();

    std::vector<std::shared_ptr<Stmt>> parse();

private:
    std::vector<Token> tokens;
    int current{0};

    /**
     * Check if the current token matches any of the given types, and advance if it does
     */
    bool match(const std::vector<TokenType> &types);

    /**
     * Check if the current token matches the given type, without advancing
     */
    bool check(const TokenType &type);

    /**
     * Advance the current token
     */
    Token &advance();

    /**
     * Checks for EOF_TOKEN
     */
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

    std::shared_ptr<Expr> call();

    std::shared_ptr<Expr> finishCall(const std::shared_ptr<Expr> &callee);

    std::shared_ptr<Expr> primary();

    /**
     * Look for TokenType type e.g. closing brackets
     */
    Token &consume(TokenType type, const std::string &message);

    /**
     * Parse error handling
     * Tells Lox that there is an error as well as the line number and the message
     */
    ParseError error(const Token &token, const std::string &message);

    /**
     * Checks until statement boundary before synchronizing state for error handling
     * Used for statements so tokens that are syntax errors are skipped
     * and the parser can continue parsing
     */
    void synchronize();

    std::shared_ptr<Expr> commaOperator();

    std::shared_ptr<Stmt> statement();

    std::shared_ptr<Stmt> forStatement();

    std::shared_ptr<Stmt> ifStatement();

    std::shared_ptr<Stmt> expressionStatement();

    std::shared_ptr<Function> function(const std::string &kind);

    std::shared_ptr<Expr> assignment();

    std::shared_ptr<Expr> logicalOr();

    std::shared_ptr<Expr> logicalAnd();

    std::shared_ptr<Stmt> printStatement();

    std::shared_ptr<Stmt> declaration();

    std::shared_ptr<Stmt> varDeclaration();

    std::shared_ptr<Stmt> whileStatement();

    std::vector<std::shared_ptr<Stmt>> block();

    std::shared_ptr<Expr> ternary();
};


#endif //INTERPRETERS_PARSER_H
