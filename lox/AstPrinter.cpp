

#include "AstPrinter.h"
#include <string>
#include "Expr.h"


std::string AstPrinter::print(const Expr<std::string> &expr) {
    return expr.accept(*this);
}

std::string AstPrinter::visitBinaryExpr(const Binary<std::string> &expr) const {
    return std::string();
}

std::string AstPrinter::visitGroupingExpr(const Grouping<std::string> &expr) const {
    return std::string();
}

std::string AstPrinter::visitLiteralExpr(const Literal<std::string> &expr) const {
    return std::string();
}

std::string AstPrinter::visitUnaryExpr(const Unary<std::string> &expr) {
    return std::string();
}

