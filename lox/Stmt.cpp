#include <any>
#include "../include/lox/Stmt.h"

std::any Expression::accept(Visitor &visitor) {
    return visitor.visitExpressionStmt(*this);
}

std::any Print::accept(Visitor &visitor) {
    return visitor.visitPrintStmt(*this);
}

