#ifndef INTERPRETERS_EXPR_H
#define INTERPRETERS_EXPR_H

#include <any>
#include <memory>
#include "Token.h"

class Binary;

class Grouping;

class Literal;

class Unary;

class Variable;

class Expr {
public:
    class Visitor;

    virtual ~Expr() = default;

    virtual std::any accept(Visitor &visitor) = 0;
};

/**
 * Visitor pattern for Expr.
 * Visitor pattern is declared within Expr hierarchy because other classes have their own Visitor as well.
 * Visitor pattern is normally used for double dispatch, i.e. virtual polymorphism on obj1.accept(obj2)
 * where obj1 is the visitor and obj2 is the visited and **BOTH** obj1 and obj2 can have runtime polymorphism
 *
 * This is used in Ch5 for printing the AST.
 * AstPrinter inherits from Expr::Visitor. Let expr, the visited, be Binary{}
 *
 * AstPrinter.cpp:  AstPrinter::print(expr) calls expr.accept(*this).
 * Expr.cpp:        Binary::accept(AstPrinter{}) calls visitor.visitBinaryExpr(*this).
 * Expr.cpp:        AstPrinter::visitBinaryExpr(expr) calls AstPrinter::parenthesize() which repeats the process
 *
 * This allows the visitor to automatically call the correct method based on the type of the visited object.
 * Kinda like a switch statement within the Visitor method, so you shift onus of completeness onto the Visitor
 * And you can modify the Visitor to your needs
 */
class Expr::Visitor {
public:
    virtual std::any visitBinaryExpr(Binary &expr) = 0;

    virtual std::any visitGroupingExpr(Grouping &expr) = 0;

    virtual std::any visitLiteralExpr(Literal &expr) = 0;

    virtual std::any visitUnaryExpr(Unary &expr) = 0;

    virtual std::any visitVariableExpr(Variable &expr) = 0;
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

class Variable : public Expr {
public:
    explicit Variable(Token name) : name(std::move(name)) {}

    Token name;

    std::any accept(Visitor &visitor) override;
};

#endif //INTERPRETERS_EXPR_H
