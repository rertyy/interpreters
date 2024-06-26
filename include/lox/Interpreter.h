#ifndef INTERPRETERS_INTERPRETER_H
#define INTERPRETERS_INTERPRETER_H

#include <vector>
#include "Expr.h"
#include "Stmt.h"

// Class for evaluating expressions
class Interpreter : public virtual Expr::Visitor, public virtual Stmt::Visitor {
public:
    std::any visitLiteralExpr(const Literal &expr) const override;

    std::any visitGroupingExpr(const Grouping &expr) const override;

    std::any visitUnaryExpr(const Unary &expr) const override;

    std::any visitBinaryExpr(const Binary &expr) const override;

    std::any visitExpressionStmt(const Expression &stmt) const override;

    std::any visitPrintStmt(const Print &stmt) const override;

    /**
     * Entry point for interpreter methods
     * @param expr
     */
    void interpret(Expr &expr);
    void interpret(Expr &expr) const;

private:
    std::any evaluate(Expr &expr) const;

    // False and nil are falsey, everything else is truthy
    bool isTruthy(std::any object) const;

    bool isEqual(const std::any &a, const std::any &b) const;

    /**
     * Check if the operand is a number
     * @param op
     * @param operand
     */
    void checkNumberOperand(const Token &op, const std::any &operand);

    void checkNumberOperands(const Token &op, const std::any &left, const std::any &right) const;

    void execute(const Stmt &stmt) const;
};


#endif //INTERPRETERS_INTERPRETER_H
