#ifndef INTERPRETERS_INTERPRETER_H
#define INTERPRETERS_INTERPRETER_H

#include <vector>
#include "Expr.h"
#include "Stmt.h"
#include "Environment.h"

// Class for evaluating expressions
class Interpreter : public virtual Expr::Visitor, public virtual Stmt::Visitor {
public:
    // Expression visitors
    std::any visitLiteralExpr(Literal &expr) override;

    std::any visitGroupingExpr(Grouping &expr) override;

    std::any visitUnaryExpr(Unary &expr) override;

    std::any visitBinaryExpr(Binary &expr) override;

    std::any visitVariableExpr(Variable &expr) override;

    // Statement visitors
    std::any visitExpressionStmt(Expression &stmt) override;

    std::any visitPrintStmt(Print &stmt) override;

    std::any visitVarStmt(Var &stmt) override;


    /**
     * Entry point for interpreter methods
     */
    void interpret(Expr &expr);

    void interpret(std::vector<std::shared_ptr<Stmt>> &statements);

private:

    Environment environment;

    // Evaluate an expression
    std::any evaluate(Expr &expr);

    // Execute a statement
    void execute(Stmt &stmt);

    // False and nil are falsey, everything else is truthy
    bool isTruthy(const std::any &object) const;

    bool isEqual(const std::any &a, const std::any &b) const;

    /**
     * Check if the operand is a number
     */
    void checkNumberOperand(const Token &op, const std::any &operand);

    void checkNumberOperands(const Token &op, const std::any &left, const std::any &right) const;


};


#endif //INTERPRETERS_INTERPRETER_H
