#include <any>
#include "../include/lox/Expr.h"

std::any Assign::accept(Visitor &visitor) {
    return visitor.visitAssignExpr(*this);
}

std::any Binary::accept(Visitor &visitor) {
    return visitor.visitBinaryExpr(*this);
}

std::any Grouping::accept(Visitor &visitor) {
    return visitor.visitGroupingExpr(*this);
}

std::any Literal::accept(Visitor &visitor) {
    return visitor.visitLiteralExpr(*this);
}

std::any Unary::accept(Visitor &visitor) {
    return visitor.visitUnaryExpr(*this);
}

std::any Variable::accept(Visitor &visitor) {
    return visitor.visitVariableExpr(*this);
}

