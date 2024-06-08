#ifndef INTERPRETERS_EXPR_H
#define INTERPRETERS_EXPR_H

#include <any>
#include <memory>
#include "Token.h"

template<typename T>
class Visitor;
template<typename T>
class Binary;
template<typename T>
class Grouping;
template<typename T>
class Literal;
template<typename T>
class Unary;

template<typename T>
class Expr {
public:
    virtual ~Expr() = default;
    virtual T accept(Visitor<T> &visitor) const = 0;
};

template<typename T>
class Visitor {
public:
    virtual T visitBinaryExpr(const Binary<T> &expr) const = 0;
    virtual T visitGroupingExpr(const Grouping<T> &expr) const = 0;
    virtual T visitLiteralExpr(const Literal<T> &expr) const = 0;
    virtual T visitUnaryExpr(const Unary<T> &expr) const = 0;
friend class Expr<T>;
};

template<typename T>
class Binary : public Expr<T> {
public:
    explicit Binary(std::shared_ptr<Expr<T>> left, Token op, std::shared_ptr<Expr<T>> right) : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    std::shared_ptr<Expr<T>> left;
    Token op;
    std::shared_ptr<Expr<T>> right;

    T accept(Visitor<T> &visitor) const override;
};

template<typename T>
class Grouping : public Expr<T> {
public:
    explicit Grouping(std::shared_ptr<Expr<T>> expression) : expression(std::move(expression)) {}

    std::shared_ptr<Expr<T>> expression;

    T accept(Visitor<T> &visitor) const override;
};

template<typename T>
class Literal : public Expr<T> {
public:
    explicit Literal(T value) : value(std::move(value)) {}

    T value;

    T accept(Visitor<T> &visitor) const override;
};

template<typename T>
class Unary : public Expr<T> {
public:
    explicit Unary(Token op, std::shared_ptr<Expr<T>> right) : op(std::move(op)), right(std::move(right)) {}

    Token op;
    std::shared_ptr<Expr<T>> right;

    T accept(Visitor<T> &visitor) const override;
};

#endif //INTERPRETERS_EXPR_H
