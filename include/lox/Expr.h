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

    virtual std::any accept(const Visitor &visitor) const = 0;
};

class Expr::Visitor {
public:
    virtual std::any visitBinaryExpr(const Binary &expr) const = 0;

    virtual std::any visitGroupingExpr(const Grouping &expr) const = 0;

    virtual std::any visitLiteralExpr(const Literal &expr) const = 0;

    virtual std::any visitUnaryExpr(const Unary &expr) const = 0;
};

class Binary : public Expr {
public:
    explicit Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right)
            : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    const std::shared_ptr<Expr> left;
    const Token op;
    const std::shared_ptr<Expr> right;

    std::any accept(const Visitor &visitor) const override;
};

class Grouping : public Expr {
public:
    explicit Grouping(std::shared_ptr<Expr> expression) : expression(std::move(expression)) {}

    const std::shared_ptr<Expr> expression;

    std::any accept(const Visitor &visitor) const override;
};

class Literal : public Expr {
public:
    explicit Literal(std::any value) : value(std::move(value)) {}

    const std::any value;

    std::any accept(const Visitor &visitor) const override;
};

class Unary : public Expr {
public:
    explicit Unary(Token op, std::shared_ptr<Expr> right) : op(std::move(op)), right(std::move(right)) {}

    const Token op;
    const std::shared_ptr<Expr> right;

    std::any accept(const Visitor &visitor) const override;
};

#endif //INTERPRETERS_EXPR_H
