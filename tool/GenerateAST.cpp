#include "GenerateAST.h"
#include "../utils/utils.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

void GenerateAST::main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: generate_ast <output directory>" << std::endl;
        exit(64);
    }
    std::string outputDir = argv[1];
    defineAST(outputDir, "Expr", {
            "Binary   : std::shared_ptr<Expr<T>> left, Token op, std::shared_ptr<Expr<T>> right",
            "Grouping : std::shared_ptr<Expr<T>> expression",
            "Literal  : T value",
            "Unary    : Token op, std::shared_ptr<Expr<T>> right"
    });
}

void GenerateAST::defineAST(const std::string &outputDir, const std::string &baseName,
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


    defineASTHeader(outputDir, baseName, typesVec, baseNameUpper);
    defineASTCode(outputDir, baseName, typesVec);
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

    writer << "#include \"" << baseName << ".h\"" << std::endl;
    writer << std::endl;

    for (const auto &[className, fields]: typesVec) {
        writer << "template<typename T>" << std::endl;
        writer << "T " << className << "<T>::accept(Visitor<T> &visitor) const {" << std::endl;
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
    writer << "#include \"Token.h\"" << std::endl;
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
    writer << "template<typename T>" << std::endl;
    writer << "class Visitor;" << std::endl;
    for (const auto &[className, fields]: typesVec) {
        writer << "template<typename T>" << std::endl;
        writer << "class " << className << ";" << std::endl;
    }
    writer << std::endl;
}


void GenerateAST::defineBaseClass(std::ofstream &writer, const std::string &baseName) {
    writer << "template<typename T>" << std::endl;
    writer << "class " << baseName << " {" << std::endl;
    writer << "public:" << std::endl;
    writer << "    virtual ~" << baseName << "() = default;" << std::endl;
    writer << "    virtual T accept(Visitor<T> &visitor) const = 0;" << std::endl;
    writer << "};" << std::endl;
    writer << std::endl;
}

void
GenerateAST::defineVisitor(std::ofstream &writer, const std::string &baseName,
                           const std::vector<std::pair<std::string, std::string>> &typesVec) {
    writer << "template<typename T>" << std::endl;
    writer << "class Visitor {" << std::endl;
    writer << "public:" << std::endl;
    for (const auto &[className, fieldName]: typesVec) {
        writer << "    virtual T visit" << className << baseName << "(const " << className
               << "<T> &expr) const = 0;"
               << std::endl;
    }
    writer << "friend class " << baseName << "<T>" ";" << std::endl;
    writer << "};" << std::endl;
    writer << std::endl;
}

void GenerateAST::defineSubclasses(std::ofstream &hWriter, const std::string &baseName,
                                   const std::vector<std::pair<std::string, std::string>> &typesVec) {
    for (const auto &[className, fields]: typesVec) {
        defineType(hWriter, baseName, className, fields);
    }
}

void GenerateAST::defineType(std::ofstream &writer, const std::string &baseName, const std::string &className,
                             const std::string &fields) {
    writer << "template<typename T>" << std::endl;
    writer << "class " << className << " : public " << baseName << "<T> {" << std::endl;
    writer << "public:" << std::endl;

    // Constructor
    writer << "    explicit " << className << "(" << fields << ") : ";
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

    // Fields
    for (const auto &field: fieldsVec) {
        writer << "    " << field << ";" << std::endl;
    }

    writer << std::endl;
    writer << "    T accept(Visitor<T> &visitor) const override;" << std::endl;
    writer << "};" << std::endl;
    writer << std::endl;
}
