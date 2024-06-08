#include "lox/Lox.h"
#include "tool/GenerateAST.h"

int main(int argc, char *argv[]) {
    Lox::main(argc, argv);
    return 0;
}


int codegen() {
    char *args[] = {const_cast<char *>("generate_ast"), const_cast<char *>("/home/ian/interpreters/lox")};
    GenerateAST::main(2, args);

    return 0;
}
