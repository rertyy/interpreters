#ifndef INTERPRETERS_ASTPRINTER_H
#define INTERPRETERS_ASTPRINTER_H

#include "Expr.h"
#include <string>

class AstPrinter : public Visitor {
public:
    std::string print(Expr &expr);

    std::string visitBinaryExpr(Binary &expr) override;

    std::string visitGroupingExpr(Grouping &expr) override;

    std::string visitLiteralExpr(Literal &expr) override;

    std::string visitUnaryExpr(Unary &expr) override;

    template<typename... Exprs>
    std::string parenthesize(const std::string &name,
                             Exprs &&... expressions);
};

#endif //INTERPRETERS_ASTPRINTER_H
