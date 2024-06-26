#include <any>
#include "../include/lox/Expr.h"

std::any Binary::accept(const Visitor &visitor) const {
    return visitor.visitBinaryExpr(*this);
}

std::any Grouping::accept(const Visitor &visitor) const {
    return visitor.visitGroupingExpr(*this);
}

std::any Literal::accept(const Visitor &visitor) const {
    return visitor.visitLiteralExpr(*this);
}

std::any Unary::accept(const Visitor &visitor) const {
    return visitor.visitUnaryExpr(*this);
}
