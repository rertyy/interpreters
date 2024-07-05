#ifndef INTERPRETERS_STMT_H
#define INTERPRETERS_STMT_H

#include <any>
#include <memory>
#include <vector>
#include "Token.h"
#include "Expr.h"

class Block;

class Expression;

class If;

class Print;

class Var;

class While;

class Stmt {
public:
    class Visitor;

    virtual ~Stmt() = default;

    virtual std::any accept(Visitor &visitor) = 0;
};

class Stmt::Visitor {
public:
    virtual std::any visitBlockStmt(Block &expr) = 0;

    virtual std::any visitExpressionStmt(Expression &expr) = 0;

    virtual std::any visitIfStmt(If &expr) = 0;

    virtual std::any visitPrintStmt(Print &expr) = 0;

    virtual std::any visitVarStmt(Var &expr) = 0;

    virtual std::any visitWhileStmt(While &expr) = 0;

};

class Block : public Stmt {
public:
    explicit Block(std::vector<std::shared_ptr<Stmt>> statements);

    std::vector<std::shared_ptr<Stmt>> statements;

    std::any accept(Visitor &visitor) override;
};

class Expression : public Stmt {
public:
    explicit Expression(std::shared_ptr<Expr> expression);

    std::shared_ptr<Expr> expression;

    std::any accept(Visitor &visitor) override;
};

class If : public Stmt {
public:
    explicit If(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> thenBranch, std::shared_ptr<Stmt> elseBranch);

    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmt> thenBranch;
    std::shared_ptr<Stmt> elseBranch;

    std::any accept(Visitor &visitor) override;
};

class Print : public Stmt {
public:
    explicit Print(std::shared_ptr<Expr> expression);

    std::shared_ptr<Expr> expression;

    std::any accept(Visitor &visitor) override;
};

class Var : public Stmt {
public:
    explicit Var(Token name, std::shared_ptr<Expr> initializer);

    Token name;
    std::shared_ptr<Expr> initializer;

    std::any accept(Visitor &visitor) override;
};

class While : public Stmt {
public:
    explicit While(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> body);

    std::shared_ptr<Expr> condition;
    std::shared_ptr<Stmt> body;

    std::any accept(Visitor &visitor) override;
};

#endif //INTERPRETERS_STMT_H
