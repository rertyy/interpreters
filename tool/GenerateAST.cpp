#include "../include/tool/GenerateAST.h"
#include "../include/utils/utils.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

void GenerateAST::main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: generate_ast <cpp output directory> <header output directory>" << std::endl;
        exit(64);
    }
    std::string codeOutputDir = argv[1];
    std::string headerOutputDir = argv[2];
    defineAST(codeOutputDir, headerOutputDir, "Expr", {
            "Assign   : Token name, std::shared_ptr<Expr> value",
            "Binary   : std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right",
            "Call     : std::shared_ptr<Expr> callee, Token paren, std::vector<std::shared_ptr<Expr>> arguments",
            "Ternary  : std::shared_ptr<Expr> left, Token op1, std::shared_ptr<Expr> middle, Token op2, std::shared_ptr<Expr> right",
            "Grouping : std::shared_ptr<Expr> expression",
            "Literal  : std::any value",
            "Logical  : std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right",
            "Unary    : Token op, std::shared_ptr<Expr> right",
            "Variable : Token name",
    });
    defineAST(codeOutputDir, headerOutputDir, "Stmt", {
            "Block      : std::vector<std::shared_ptr<Stmt>> statements",
            "Expression : std::shared_ptr<Expr> expression",
            "Function   : Token name, std::vector<Token> params, std::vector<std::shared_ptr<Stmt>> body",
            "If         : std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> thenBranch, std::shared_ptr<Stmt> elseBranch",
            "Print      : std::shared_ptr<Expr> expression",
            "Break      : Token keyword",
            "Continue   : Token keyword",
            "Return     : Token keyword, std::shared_ptr<Expr> value",
            "Var        : Token name, std::shared_ptr<Expr> initializer",
            "While      : std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> body",
    });
}

void
GenerateAST::defineAST(const std::string &codeOutputDir, const std::string &headerOutputDir,
                       const std::string &baseName,
                       const std::vector<std::string> &types) {

    std::vector<std::pair<std::string, std::string>> typesVec;
    for (const auto &type: types) {
        std::string className = type.substr(0, type.find(':') - 1);
        std::string fields = type.substr(type.find(':') + 2);
        className = trim(className);
        fields = trim(fields);
        typesVec.emplace_back(className, fields);
    }

    std::string baseNameUpper = baseName;
    std::transform(baseNameUpper.begin(), baseNameUpper.end(), baseNameUpper.begin(), ::toupper);


    defineASTHeader(headerOutputDir, baseName, typesVec, baseNameUpper);
    defineASTCode(codeOutputDir, baseName, typesVec);
}

void GenerateAST::defineASTCode(const std::string &outputDir, const std::string &baseName,
                                const std::vector<std::pair<std::string, std::string>> &typesVec) {
    std::string path = outputDir + "/" + baseName + ".cpp";
    std::ofstream writer(path);
    if (!writer.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        exit(1);
    }

    std::cout << "Writing to " << path << std::endl;

    writer << "#include <any>" << std::endl;
    writer << "#include \"../include/lox/" << baseName << ".h\"" << std::endl;
    writer << std::endl;

    for (const auto &[className, fields]: typesVec) {
        writer << className << "::" << className << "(" << fields << ") : ";
        std::vector<std::string> fieldsVec = split(fields, ", ");
        for (size_t i = 0; i < fieldsVec.size(); ++i) {
            std::string fieldName = split(fieldsVec[i], " ").back();
            writer << fieldName << "(std::move(" << fieldName << "))";
            if (i < fieldsVec.size() - 1) {
                writer << ", ";
            }
        }
        writer << " {}" << std::endl;
        writer << std::endl;

        writer << "std::any " << className << "::accept(Visitor &visitor) {" << std::endl;
        writer << "    return visitor.visit" << className << baseName << "(*this);" << std::endl;
        writer << "}" << std::endl;
        writer << std::endl;
    }

    if (writer.fail()) {
        std::cerr << "Error occurred while writing to file: " << path << std::endl;
    } else {
        std::cout << "Done writing to " << path << std::endl;
    }
}


void GenerateAST::defineASTHeader(const std::string &outputDir, const std::string &baseName,
                                  const std::vector<std::pair<std::string, std::string>> &typesVec,
                                  const std::string &baseNameUpper) {
    std::string path = outputDir + "/" + baseName + ".h";
    std::ofstream writer(path);

    if (!writer.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        exit(1);
    }

    std::cout << "Writing to " << path << std::endl;

    // Initialise
    writer << "#ifndef INTERPRETERS_" << baseNameUpper << "_H" << std::endl;
    writer << "#define INTERPRETERS_" << baseNameUpper << "_H" << std::endl;
    writer << std::endl;

    // Imports
    writer << "#include <any>" << std::endl;
    writer << "#include <memory>" << std::endl;
    writer << "#include <vector>" << std::endl;
    writer << "#include \"Token.h\"" << std::endl;
    writer << "#include \"Expr.h\"" << std::endl;
    writer << std::endl;

    // Forward declarations
    defineForwardDecls(writer, typesVec);
    defineBaseClass(writer, baseName);
    defineVisitor(writer, baseName, typesVec);
    defineSubclasses(writer, baseName, typesVec);

    writer << "#endif //INTERPRETERS_" << baseNameUpper << "_H" << std::endl;
    writer.close();

    if (writer.fail()) {
        std::cerr << "Error occurred while writing to file: " << path << std::endl;
    } else {
        std::cout << "Done writing to " << path << std::endl;
    }
}

void GenerateAST::defineForwardDecls(std::ofstream &writer,
                                     const std::vector<std::pair<std::string, std::string>> &typesVec) {
    for (const auto &[className, fields]: typesVec) {
        writer << "class " << className << ";" << std::endl;
        writer << std::endl;
    }
}


void GenerateAST::defineBaseClass(std::ofstream &writer, const std::string &baseName) {
    writer << "class " << baseName << " {" << std::endl;
    writer << "public:" << std::endl;
    writer << "    class Visitor;" << std::endl;
    writer << std::endl;
    writer << "    virtual ~" << baseName << "() = default;" << std::endl;
    writer << std::endl;
    writer << "    virtual std::any accept(Visitor &visitor) = 0;" << std::endl;
    writer << "};" << std::endl;
    writer << std::endl;
}

void
GenerateAST::defineVisitor(std::ofstream &writer, const std::string &baseName,
                           const std::vector<std::pair<std::string, std::string>> &typesVec) {
    writer << "class " << baseName << "::Visitor {" << std::endl;
    writer << "public:" << std::endl;
    for (const auto &[className, fieldName]: typesVec) {
        writer << "    virtual std::any visit" << className << baseName << "(" << className
               << " &expr) = 0;"
               << std::endl;
        writer << std::endl;
    }
    writer << "};" << std::endl;
    writer << std::endl;
}

void GenerateAST::defineSubclasses(std::ofstream &writer, const std::string &baseName,
                                   const std::vector<std::pair<std::string, std::string>> &typesVec) {
    for (const auto &[className, fields]: typesVec) {
        defineType(writer, baseName, className, fields);
    }
}

void GenerateAST::defineType(std::ofstream &writer, const std::string &baseName, const std::string &className,
                             const std::string &fields) {
    writer << "class " << className << " : public " << baseName << " {" << std::endl;
    writer << "public:" << std::endl;

    // Constructor
    writer << "    explicit " << className << "(" << fields << ");" << std::endl;
    writer << std::endl;

    // Fields
    std::vector<std::string> fieldsVec = split(fields, ", ");
    for (const auto &field: fieldsVec) {
        writer << "    " << field << ";" << std::endl;
    }
    writer << std::endl;
    writer << "    std::any accept(Visitor &visitor) override;" << std::endl;
    writer << "};" << std::endl;
    writer << std::endl;
}


