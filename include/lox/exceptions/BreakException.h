#ifndef INTERPRETERS_BREAKEXCEPTION_H
#define INTERPRETERS_BREAKEXCEPTION_H

#include <stdexcept>

class BreakException : public std::runtime_error {
public:
    explicit BreakException() : std::runtime_error("Break") {}

};


#endif //INTERPRETERS_BREAKEXCEPTION_H
