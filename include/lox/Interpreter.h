#ifndef INTERPRETERS_INTERPRETER_H
#define INTERPRETERS_INTERPRETER_H

#include "Expr.h"

// Class for evaluating expressions
class Interpreter : public Expr::Visitor {
public:
    std::any visitLiteralExpr(Literal &expr) override;

    std::any visitGroupingExpr(Grouping &expr) override;

    std::any visitUnaryExpr(Unary &expr) override;

    std::any visitBinaryExpr(Binary &expr) override;

    /**
     * Entry point for interpreter methods
     * @param expr
     */
    void interpret(Expr &expr);

private:
    std::any evaluate(Expr &expr);

    // False and nil are falsey, everything else is truthy
    bool isTruthy(std::any object);

    bool isEqual(const std::any &a, const std::any &b);

    /**
     * Check if the operand is a number
     * @param op
     * @param operand
     */
    void checkNumberOperand(const Token &op, const std::any &operand);

    void checkNumberOperands(const Token &op, const std::any &left, const std::any &right);

};


#endif //INTERPRETERS_INTERPRETER_H
