#ifndef INTERPRETERS_RETURNEXCEPTION_H
#define INTERPRETERS_RETURNEXCEPTION_H

#include <stdexcept>
#include <any>

class ReturnException : public std::runtime_error {
public:
    explicit ReturnException(std::any value) : std::runtime_error("Return"), value(std::move(value)) {}

    std::any value;

};


#endif //INTERPRETERS_RETURNEXCEPTION_H
