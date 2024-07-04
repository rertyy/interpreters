#include <iostream>
#include "../include/lox/Parser.h"

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), current(0) {}

bool Parser::match(const std::vector<TokenType> &types) {
    bool it = std::ranges::any_of(types, [this](const TokenType &type) {
        return (check(type));
    });

    if (it) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(const TokenType &type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}


Token &Parser::advance() {
    if (!isAtEnd()) ++current;
    return previous();
}

bool Parser::isAtEnd() {
    return peek().type == EOF_TOKEN;
}

Token &Parser::peek() {
    return tokens[current];
}

Token &Parser::previous() {
    return tokens[current - 1];
}

std::shared_ptr<Expr> Parser::expression() {
    return commaOperator();
}

// I added this! This is a comma operator for CPP which has left-to-right associativity
// and has lower precedence than assignment
std::shared_ptr<Expr> Parser::commaOperator() {
    std::shared_ptr<Expr> expr = ternary();

    while (match({COMMA})) {
        Token &op = previous();
        std::shared_ptr<Expr> right = commaOperator();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}

// Binary functions
std::shared_ptr<Expr> Parser::equality() {
    std::shared_ptr<Expr> expr = comparison();

    while (match({BANG_EQUAL, EQUAL_EQUAL})) {
        Token &op = previous();
        std::shared_ptr<Expr> right = comparison();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}


std::shared_ptr<Expr> Parser::comparison() {
    std::shared_ptr<Expr> expr = term();

    while (match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        Token &op = previous();
        std::shared_ptr<Expr> right = term();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::term() {
    std::shared_ptr<Expr> expr = factor();

    while (match({MINUS, PLUS})) {
        Token &op = previous();
        std::shared_ptr<Expr> right = factor();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> expr = unary();

    while (match({SLASH, STAR})) {
        Token &op = previous();
        std::shared_ptr<Expr> right = unary();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::unary() {
    while (match({BANG, MINUS})) {
        Token &op = previous();
        std::shared_ptr<Expr> right = unary();
        return std::make_shared<Unary>(op, right);
    }
    return primary();
}

std::shared_ptr<Expr> Parser::ternary() {
    std::shared_ptr<Expr> expr = assignment();
    if (match({QUESTION})) {
        Token &op1 = previous();
        std::shared_ptr<Expr> thenExpr = assignment();
        consume(COLON, "Expect ':' after expression.");
        Token &op2 = previous();
        std::shared_ptr<Expr> elseExpr = ternary();
        return std::make_shared<Ternary>(expr, op1,
                                         thenExpr, op2,
                                         elseExpr);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::primary() {
    if (match({FALSE})) return std::make_shared<Literal>(false);
    if (match({TRUE})) return std::make_shared<Literal>(true);
    if (match({NIL})) return std::make_shared<Literal>(nullptr);
    if (match({NUMBER, STRING})) return std::make_shared<Literal>(previous().literal);
    if (match({IDENTIFIER})) return std::make_shared<Variable>(previous());
    if (match({LEFT_PAREN})) {
        std::shared_ptr<Expr> expr = expression();
        // Look for closing bracket
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_shared<Grouping>(expr);
    }

    throw error(peek(), "Expect expression.");
}

Token &Parser::consume(TokenType type, const std::string &message) {
    bool checked = check(type);
    if (checked) {
        return advance();
    }
    throw error(peek(), message);
}

Parser::ParseError Parser::error(const Token &token, const std::string &message) {
    Lox::error(token, message);
    throw ParseError{};
}

// Checks until statement boundary before synchronizing state for error handling
void Parser::synchronize() {
    advance();

    while (!isAtEnd()) {
        if (previous().type == SEMICOLON) return;
    }
    switch (peek().type) {
        case CLASS:
        case FUN:
        case VAR:
        case FOR:
        case IF:
        case WHILE:
        case PRINT:
        case RETURN:
            return;
        default:
            advance();
    }
}

std::shared_ptr<Expr> Parser::parseExpr() {
    try {
        return expression();
    } catch (const ParseError &error) {
        Lox::hadError = true;
        return nullptr;
    }
}

std::vector<std::shared_ptr<Stmt>> Parser::parse() {
    std::vector<std::shared_ptr<Stmt>> statements;
    while (!isAtEnd()) {
        try {
            statements.emplace_back(declaration());
        } catch (const ParseError &error) {
            std::cout << "error found" << std::endl;
            Lox::hadError = true;
        }
    }
    return statements;
}

std::shared_ptr<Stmt> Parser::statement() {
    if (match({IF})) {
        return ifStatement();
    }
    if (match({PRINT})) {
        return printStatement();
    }
    if (match({LEFT_BRACE})) {
        return std::make_shared<Block>(block());
    }
    return expressionStatement();
}

std::shared_ptr<Stmt> Parser::ifStatement() {
    consume(LEFT_PAREN, "Expect '(' after 'if'.");
    std::shared_ptr<Expr> condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after if condition.");

    std::shared_ptr<Stmt> thenBranch = statement();
    std::shared_ptr<Stmt> elseBranch = nullptr;
    // This match here means that else is tied to most recent if statement.
    if (match({ELSE})) {
        elseBranch = statement();
    }
    return std::make_shared<If>(condition, thenBranch, elseBranch);
}


std::shared_ptr<Stmt> Parser::printStatement() {
    std::shared_ptr<Expr> value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return std::make_shared<Print>(value);
}

std::shared_ptr<Stmt> Parser::expressionStatement() {
    std::shared_ptr<Expr> expr = expression();
    consume(SEMICOLON, "Expect ';' after expression.");
    return std::make_shared<Expression>(expr);
}

std::shared_ptr<Stmt> Parser::declaration() {
    try {
        if (match({VAR})) return varDeclaration();
        return statement();
    } catch (const ParseError &error) {
        synchronize();
        return nullptr;
    }
}

std::shared_ptr<Stmt> Parser::varDeclaration() {
    Token &name = consume(IDENTIFIER, "Expect variable name.");

    std::shared_ptr<Expr> initializer = nullptr;
    if (match({EQUAL})) {
        initializer = expression();
    }

    consume(SEMICOLON, "Expect ';' after variable declaration.");
    return std::make_shared<Var>(name, initializer);
}

// Because LHS and RHS are both valid expressions, run expressions on both LHS and RHS
std::shared_ptr<Expr> Parser::assignment() {
    std::shared_ptr<Expr> expr = logicalOr();

    if (match({EQUAL})) {
        Token &equals = previous(); // the l-value
        std::shared_ptr<Expr> value = assignment();
        // assignment is right-associative i.e. y=x=1 has y==1

        // dynamic_cast is equivalent to Java instanceof
        if (auto varPtr = std::dynamic_pointer_cast<Variable>(expr)) {
            Token name = varPtr->name;
            return std::make_shared<Assign>(name, value);
        }
        // Don't throw because parser knows which point it is inside the code
        error(equals, "Invalid assignment target.");
    }
    return expr;
}

std::shared_ptr<Expr> Parser::logicalOr() {
    std::shared_ptr<Expr> expr = logicalAnd();

    while (match({OR})) {
        Token &op = previous();
        std::shared_ptr<Expr> right = logicalAnd();
        expr = std::make_shared<Logical>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::logicalAnd() {
    std::shared_ptr<Expr> expr = equality();

    while (match({AND})) {
        Token &op = previous();
        std::shared_ptr<Expr> right = equality();
        expr = std::make_shared<Logical>(expr, op, right);
    }
    return expr;
}


std::vector<std::shared_ptr<Stmt>> Parser::block() {
    std::vector<std::shared_ptr<Stmt>> statements;

    // isAtEnd() to ensure parser doesn't fail when there is no closing brace
    while (!check(RIGHT_BRACE) && !isAtEnd()) {
        statements.emplace_back(declaration());
    }
    consume(RIGHT_BRACE, "Expect '}' after block.");
    return statements;
}




