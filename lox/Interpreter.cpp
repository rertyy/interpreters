#include "Interpreter.h"

std::any Interpreter::visitLiteralExpr(Literal &expr) {
    return expr.value;
}

std::any Interpreter::visitGroupingExpr(Grouping &expr) {
    return evaluate(*expr.expression);
}

std::any Interpreter::evaluate(Expr &expr) {
    return expr.accept(*this);
}
