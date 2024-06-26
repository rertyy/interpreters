#include <any>
#include "../include/lox/Stmt.h"

std::any Expression::accept(const Visitor &visitor) const {
    return visitor.visitExpressionStmt(*this);
}

std::any Print::accept(const Visitor &visitor) const {
    return visitor.visitPrintStmt(*this);
}

