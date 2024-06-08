#include "Expr.h"

template<typename T>
T Binary<T>::accept(Visitor<T> &visitor) const {
    return visitor.visitBinaryExpr(*this);
}

template<typename T>
T Grouping<T>::accept(Visitor<T> &visitor) const {
    return visitor.visitGroupingExpr(*this);
}

template<typename T>
T Literal<T>::accept(Visitor<T> &visitor) const {
    return visitor.visitLiteralExpr(*this);
}

template<typename T>
T Unary<T>::accept(Visitor<T> &visitor) const {
    return visitor.visitUnaryExpr(*this);
}

