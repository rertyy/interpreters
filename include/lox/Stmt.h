#ifndef INTERPRETERS_STMT_H
#define INTERPRETERS_STMT_H

#include <any>
#include <memory>
#include <vector>
#include "Token.h"
#include "Expr.h"

class Block;

class Expression;

class Function;

class If;

class Print;

class Break;

class Continue;

class Return;

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

    virtual std::any visitFunctionStmt(Function &expr) = 0;

    virtual std::any visitIfStmt(If &expr) = 0;

    virtual std::any visitPrintStmt(Print &expr) = 0;

    virtual std::any visitBreakStmt(Break &expr) = 0;

    virtual std::any visitContinueStmt(Continue &expr) = 0;

    virtual std::any visitReturnStmt(Return &expr) = 0;

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

class Function : public Stmt {
public:
    explicit Function(Token name, std::vector<Token> params, std::vector<std::shared_ptr<Stmt>> body);

    Token name;
    std::vector<Token> params;
    std::vector<std::shared_ptr<Stmt>> body;

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

class Break : public Stmt {
public:
    explicit Break(Token keyword);

    Token keyword;

    std::any accept(Visitor &visitor) override;
};

class Continue : public Stmt {
public:
    explicit Continue(Token keyword);

    Token keyword;

    std::any accept(Visitor &visitor) override;
};

class Return : public Stmt {
public:
    explicit Return(Token keyword, std::shared_ptr<Expr> value);

    Token keyword;
    std::shared_ptr<Expr> value;

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
