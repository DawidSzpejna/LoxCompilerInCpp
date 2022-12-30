#include "Representation/Token.h"
#include "Representation/CommonObject.h"
#include "Representation/Stmt.h"
#include "Scanner/Scanner.h"
#include "Parser/Parser.h"
#include "Interpreter/Interpreter.h"
#include "Errors/CppLoxError.h"
#include "Resolver/Resolver.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <list>


#define SCRIPT 1
#define HAVE_SCRIPT 2


void runFile(std::string path);
void run(std::string source);


template <typename R>
void clean(std::vector<R *> *tokens)
{
    for (auto it = tokens->begin(); it != tokens->end(); it++) {
        delete *it;
    }

    delete tokens;
}


static Interpreter interpreter = Interpreter();


int main(int argc, char** argv)
{
    if (argc == HAVE_SCRIPT) {
        runFile(argv[SCRIPT]);
    }
    else {
        std::cerr << "Usage: cpplox [script]\n";
        exit(64);
    }

    return 0;
}


void runFile(std::string path)
{
    std::ifstream my_source_file(path);
    if (my_source_file.fail()) {
        std::cerr << "Reading script '" << path << "' failed\n";
        exit(64);
    }

    std::stringstream buffer;
    buffer << my_source_file.rdbuf();

    run(buffer.str());

    if (CppLoxError::hadError) exit(65);
    if (CppLoxError::hadRuntimeError) exit(70);
}


void run(std::string source)
{
    std::vector<Token *>* tokens = new std::vector<Token *>();
    Scanner scanner = Scanner(source, tokens);
    scanner.scanTokens();

    Parser* parser = new Parser(tokens);
    std::vector<Stmt *> *statements = parser->parse();

    // Stop if there was a syntax error.
    if (CppLoxError::hadError) return;

    Resolver *resolver = new Resolver(&interpreter);
    resolver->resolve(statements);


    // Stop if there was a resolution error.
    if (CppLoxError::hadError) return;

    interpreter.interpret(statements);

    clean(tokens);
    clean(statements);
    delete parser;
    delete resolver;
}
