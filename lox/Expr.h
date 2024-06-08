#ifndef INTERPRETERS_EXPR_H
#define INTERPRETERS_EXPR_H

#include <any>
#include <memory>
#include "Token.h"

class Visitor;
class Binary;
class Grouping;
class Literal;
class Unary;

class Expr {
public:
    virtual ~Expr() = default;
    virtual std::any accept(Visitor &visitor) = 0;
};

class Visitor {
public:
    virtual std::any visitBinaryExpr(const Binary &expr) = 0;
    virtual std::any visitGroupingExpr(const Grouping &expr) = 0;
    virtual std::any visitLiteralExpr(const Literal &expr) = 0;
    virtual std::any visitUnaryExpr(const Unary &expr) = 0;
};

class Binary : public Expr {
public:
    Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    std::any accept(Visitor &visitor) override;
};

class Grouping : public Expr {
public:
    Grouping(std::shared_ptr<Expr> expression) : expression(std::move(expression)) {}

    std::shared_ptr<Expr> expression;

    std::any accept(Visitor &visitor) override;
};

class Literal : public Expr {
public:
    Literal(std::any value) : value(std::move(value)) {}

    std::any value;

    std::any accept(Visitor &visitor) override;
};

class Unary : public Expr {
public:
    Unary(Token op, std::shared_ptr<Expr> right) : op(std::move(op)), right(std::move(right)) {}

    Token op;
    std::shared_ptr<Expr> right;

    std::any accept(Visitor &visitor) override;
};

#endif //INTERPRETERS_EXPR_H
