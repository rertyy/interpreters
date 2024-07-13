cmake_minimum_required(VERSION 3.29)
project(interpreters)

set(CMAKE_CXX_STANDARD 20)

add_executable(interpreters
        lox/Lox.cpp
        lox/Token.cpp
        include/lox/Token.h
        include/lox/TokenType.h
        include/lox/Lox.h
        main.cpp
        lox/Scanner.cpp
        include/lox/Scanner.h
        lox/Scanner.cpp
        lox/TokenType.cpp
        tool/GenerateAST.cpp
        include/tool/GenerateAST.h
        include/tool/GenerateAST.h
        utils/utils.cpp
        include/utils/utils.h
        include/utils/utils.h
        include/lox/Expr.h
        lox/Expr.cpp
        lox/AstPrinter.cpp
        include/lox/AstPrinter.h
        include/lox/AstPrinter.h
        include/lox/AstPrinter.h
        lox/Parser.cpp
        include/lox/Parser.h
        lox/Interpreter.cpp
        include/lox/Interpreter.h
        include/lox/RuntimeError.h
        include/lox/Stmt.h
        lox/Stmt.cpp
        lox/Environment.cpp
        include/lox/Environment.h
        include/lox/LoxCallable.h
        lox/Clock.cpp
        include/lox/Clock.h
        include/lox/LoxFunction.cpp
        include/lox/LoxFunction.h
)
