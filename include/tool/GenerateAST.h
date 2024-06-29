#ifndef INTERPRETERS_GENERATEAST_H
#define INTERPRETERS_GENERATEAST_H


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class GenerateAST {
public:
    static void main(int argc, char *argv[]);

private:
    static void
    defineAST(const std::string &codeOutputDir, const std::string &headerOutputDir, const std::string &baseName,
              const std::vector<std::string> &types);

    static void
    defineType(std::ofstream &writer, const std::string &baseName,
               const std::string &className, const std::string &fields);

    static void defineVisitor(std::ofstream &writer, const std::string &baseName,
                              const std::vector<std::pair<std::string, std::string>> &typesVec);

    static void defineASTCode(const std::string &outputDir, const std::string &baseName,
                              const std::vector<std::pair<std::string, std::string>> &typesVec);

    static void defineASTHeader(const std::string &outputDir, const std::string &baseName,
                                const std::vector<std::pair<std::string, std::string>> &typesVec,
                                const std::string &baseNameUpper);

    static void defineBaseClass(std::ofstream &writer, const std::string &baseName);

    static void
    defineSubclasses(std::ofstream &hWriter, const std::string &baseName,
                     const std::vector<std::pair<std::string, std::string>> &typesVec);

    static void
    defineForwardDecls(std::ofstream &writer,
                       const std::vector<std::pair<std::string, std::string>> &typesVec);
};


#endif //INTERPRETERS_GENERATEAST_H
