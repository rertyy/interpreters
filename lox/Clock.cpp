#include "../include/lox/Clock.h"
#include <string>
#include <chrono>


int Clock::arity() {
    return 0;
}

std::any Clock::call(Interpreter &interpreter, const std::vector<std::any> &arguments) {
    // https://stackoverflow.com/questions/2831841/how-to-get-the-time-in-milliseconds-in-c
    namespace sc = std::chrono;

    auto time = sc::system_clock::now(); // get the current time

    auto since_epoch = time.time_since_epoch(); // get the duration since epoch

    auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);

    long now = millis.count();

    return std::to_string(now);
}

std::string Clock::toString() const {
    return "<native fn>";
}

std::ostream &operator<<(std::ostream &os, const Clock &clock) {
    os << clock.toString();
    return os;
}
