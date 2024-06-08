#include <any>
#include "Expr.h"

std::string Binary::accept(Visitor &visitor) {
    return visitor.visitBinaryExpr(*this);
}

std::string Grouping::accept(Visitor &visitor) {
    return visitor.visitGroupingExpr(*this);
}

std::string Literal::accept(Visitor &visitor) {
    return visitor.visitLiteralExpr(*this);
}

std::string Unary::accept(Visitor &visitor) {
    return visitor.visitUnaryExpr(*this);
}
