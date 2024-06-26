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
