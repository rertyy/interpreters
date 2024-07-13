#ifndef INTERPRETERS_LOXCALLABLE_H
#define INTERPRETERS_LOXCALLABLE_H

#include <any>
#include <vector>
#include "Interpreter.h"

class LoxCallable {
public:
    virtual int arity() = 0;

    virtual std::any call(
            Interpreter &interpreter,
            const std::vector<std::any> &arguments
    ) = 0;

    virtual std::string toString() const = 0;

};

#endif //INTERPRETERS_LOXCALLABLE_H
