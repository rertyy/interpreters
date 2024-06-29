#ifndef INTERPRETERS_STMT_H
#define INTERPRETERS_STMT_H

#include <any>
#include <memory>
#include "Token.h"
#include "Expr.h"

class Expression;

class Print;

class Var;

class Stmt {
public:
    class Visitor;

    virtual ~Stmt() = default;

    virtual std::any accept(Visitor &visitor) = 0;
};

class Stmt::Visitor {
public:
    virtual std::any visitExpressionStmt(Expression &expr) = 0;

    virtual std::any visitPrintStmt(Print &expr) = 0;

    virtual std::any visitVarStmt(Var &expr) = 0;

};

class Expression : public Stmt {
public:
    explicit Expression(std::shared_ptr<Expr> expression) : expression(std::move(expression)) {}

    std::shared_ptr<Expr> expression;

    std::any accept(Visitor &visitor) override;
};

class Print : public Stmt {
public:
    explicit Print(std::shared_ptr<Expr> expression) : expression(std::move(expression)) {}

    std::shared_ptr<Expr> expression;

    std::any accept(Visitor &visitor) override;
};

class Var : public Stmt {
public:
    explicit Var(Token name, std::shared_ptr<Expr> initializer) : name(std::move(name)),
                                                                  initializer(std::move(initializer)) {}

    Token name;
    std::shared_ptr<Expr> initializer;

    std::any accept(Visitor &visitor) override;
};

#endif //INTERPRETERS_STMT_H
