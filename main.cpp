#include <memory>
#include "include/lox/Lox.h"
#include "include/tool/GenerateAST.h"
#include "include/lox/Expr.h"
#include "include/lox/AstPrinter.h"


void testAst() {
    std::shared_ptr<Expr> expression = std::make_shared<Binary>(
            std::make_shared<Unary>(
                    Token(TokenType::MINUS, "-", std::any(), 1),
                    std::make_shared<Literal>(123)),
            Token(TokenType::STAR, "*", std::any(), 1),
            std::make_shared<Grouping>(
                    std::make_shared<Literal>(45.67)));

//    std::shared_ptr<Expr> expression = std::make_shared<Literal>("45.67");

    AstPrinter printer;
    std::cout << printer.print(*expression) << std::endl;
}

void codegen() {
    char *args[] = {const_cast<char *>("generate_ast"),
                    const_cast<char *>("/home/ian/interpreters/lox"),
                    const_cast<char *>("/home/ian/interpreters/include/lox")};
    GenerateAST::main(3, args);
}


int main(int argc, char *argv[]) {
//    codegen();
//    testAst();
    Lox::runFile("/home/ian/interpreters/test/scope.txt");
//    Lox::main(argc, argv);
    return 0;
}
