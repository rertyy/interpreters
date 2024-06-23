#ifndef INTERPRETERS_EXPR_H
#define INTERPRETERS_EXPR_H

#include <any>
#include <memory>
#include "Token.h"

class Binary;

class Grouping;

class Literal;

class Unary;

class Expr {
public:
    class Visitor;

    virtual ~Expr() = default;

    virtual std::any accept(Visitor &visitor) = 0;
};

class Expr::Visitor {
public:
    virtual std::any visitBinaryExpr(Binary &expr) = 0;

    virtual std::any visitGroupingExpr(Grouping &expr) = 0;

    virtual std::any visitLiteralExpr(Literal &expr) = 0;

    virtual std::any visitUnaryExpr(Unary &expr) = 0;
};

class Binary : public Expr {
public:
    explicit Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right)
            : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    std::any accept(Visitor &visitor) override;
};

class Grouping : public Expr {
public:
    explicit Grouping(std::shared_ptr<Expr> expression) : expression(std::move(expression)) {}

    std::shared_ptr<Expr> expression;

    std::any accept(Visitor &visitor) override;
};

class Literal : public Expr {
public:
    explicit Literal(std::any value) : value(std::move(value)) {}

    std::any value;

    std::any accept(Visitor &visitor) override;
};

class Unary : public Expr {
public:
    explicit Unary(Token op, std::shared_ptr<Expr> right) : op(std::move(op)), right(std::move(right)) {}

    Token op;
    std::shared_ptr<Expr> right;

    std::any accept(Visitor &visitor) override;
};

#endif //INTERPRETERS_EXPR_H
