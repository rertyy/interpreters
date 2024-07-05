#ifndef INTERPRETERS_EXPR_H
#define INTERPRETERS_EXPR_H

#include <any>
#include <memory>
#include <vector>
#include "Token.h"
#include "Expr.h"

class Assign;

class Binary;

class Ternary;

class Grouping;

class Literal;

class Logical;

class Unary;

class Variable;

class Expr {
public:
    class Visitor;

    virtual ~Expr() = default;

    virtual std::any accept(Visitor &visitor) = 0;
};

class Expr::Visitor {
public:
    virtual std::any visitAssignExpr(Assign &expr) = 0;

    virtual std::any visitBinaryExpr(Binary &expr) = 0;

    virtual std::any visitTernaryExpr(Ternary &expr) = 0;

    virtual std::any visitGroupingExpr(Grouping &expr) = 0;

    virtual std::any visitLiteralExpr(Literal &expr) = 0;

    virtual std::any visitLogicalExpr(Logical &expr) = 0;

    virtual std::any visitUnaryExpr(Unary &expr) = 0;

    virtual std::any visitVariableExpr(Variable &expr) = 0;

};

class Assign : public Expr {
public:
    explicit Assign(Token name, std::shared_ptr<Expr> value);

    Token name;
    std::shared_ptr<Expr> value;

    std::any accept(Visitor &visitor) override;
};

class Binary : public Expr {
public:
    explicit Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);

    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    std::any accept(Visitor &visitor) override;
};

class Ternary : public Expr {
public:
    explicit Ternary(std::shared_ptr<Expr> left, Token op1, std::shared_ptr<Expr> middle, Token op2,
                     std::shared_ptr<Expr> right);

    std::shared_ptr<Expr> left;
    Token op1;
    std::shared_ptr<Expr> middle;
    Token op2;
    std::shared_ptr<Expr> right;

    std::any accept(Visitor &visitor) override;
};

class Grouping : public Expr {
public:
    explicit Grouping(std::shared_ptr<Expr> expression);

    std::shared_ptr<Expr> expression;

    std::any accept(Visitor &visitor) override;
};

class Literal : public Expr {
public:
    explicit Literal(std::any value);

    std::any value;

    std::any accept(Visitor &visitor) override;
};

class Logical : public Expr {
public:
    explicit Logical(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);

    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    std::any accept(Visitor &visitor) override;
};

class Unary : public Expr {
public:
    explicit Unary(Token op, std::shared_ptr<Expr> right);

    Token op;
    std::shared_ptr<Expr> right;

    std::any accept(Visitor &visitor) override;
};

class Variable : public Expr {
public:
    explicit Variable(Token name);

    Token name;

    std::any accept(Visitor &visitor) override;
};

#endif //INTERPRETERS_EXPR_H
