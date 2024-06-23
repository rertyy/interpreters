#include <any>
#include "../include/lox/Expr.h"

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
