#ifndef INTERPRETERS_CONTINUEEXCEPTION_H
#define INTERPRETERS_CONTINUEEXCEPTION_H

#include <stdexcept>


class ContinueException : public std::runtime_error {
public:
    explicit ContinueException() : std::runtime_error("Continue") {}

};

#endif //INTERPRETERS_CONTINUEEXCEPTION_H
