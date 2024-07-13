#ifndef INTERPRETERS_CLOCK_H
#define INTERPRETERS_CLOCK_H

#include "LoxCallable.h"
#include <any>
#include <vector>
#include <string>

class Clock : public LoxCallable {
public:

    Clock() = default;

    int arity() override;

    std::any call(Interpreter &interpreter, const std::vector<std::any> &arguments) override;

    std::string toString() const override;

    friend std::ostream &operator<<(std::ostream &os, const Clock &clock);
};


#endif //INTERPRETERS_CLOCK_H
