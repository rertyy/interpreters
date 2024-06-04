cmake_minimum_required(VERSION 3.29)
project(interpreters)

set(CMAKE_CXX_STANDARD 20)

add_executable(interpreters
        lox/Lox.cpp
        lox/Token.cpp
        lox/Token.h
        lox/TokenType.h
        lox/Lox.h
        main.cpp
        lox/Scanner.cpp
        lox/Scanner.h
        lox/Scanner.cpp
)
