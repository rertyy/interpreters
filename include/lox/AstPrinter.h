#ifndef INTERPRETERS_ASTPRINTER_H
#define INTERPRETERS_ASTPRINTER_H

#include "Expr.h"
#include <string>

class AstPrinter : public Expr::Visitor {
public:
    std::string print(const Expr &expr);

    std::any visitBinaryExpr(const Binary &expr) const override;

    std::any visitGroupingExpr(const Grouping &expr) const override;

    std::any visitLiteralExpr(const Literal &expr) const override;

    std::any visitUnaryExpr(const Unary &expr) const override;

    template<typename... Exprs>
    std::string parenthesize(const std::string &name,
                             Exprs &&... expressions) const;
};

#endif //INTERPRETERS_ASTPRINTER_H
