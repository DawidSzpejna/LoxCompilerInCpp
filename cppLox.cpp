#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "Representation/Token.h"
#include "tools/PrettyPrinter/Prettyprinter.h"
#include "Scanner/Scanner.h"
#include "Parser/Parser.h"
#include "Interpreter/Interpreter.h"
#include "Errors/CppLoxError.h"


#define SCRIPT 1
#define HAVE_SCRIPT 2


void runFile(std::string path);
void runPrompt();
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


using namespace std;


int main(int argc, char** argv)
{

    if (argc > HAVE_SCRIPT) {
        cerr << "Usage: cpplox [script]\n";
        exit(64);
    }
    else if (argc == HAVE_SCRIPT) {
        runFile(argv[SCRIPT]);
    }
    else {
        runPrompt();
    }

    return 0;
}


void runFile(std::string path)
{
    std::ifstream my_source_file(path);
    std::stringstream buffer;
    buffer << my_source_file.rdbuf();

    run(buffer.str());

    if (CppLoxError::hadError) exit(65);
    if (CppLoxError::hadRuntimeError) exit(70);
}


void runPrompt() 
{
    // będzie w przyszłości
    CppLoxError::hadError = false;
}


void run(std::string source)
{
    vector<Token *>* tokens = new vector<Token *>();
    Scanner scanner = Scanner(source, tokens);
    scanner.scanTokens();

    for (auto it = tokens->begin(); it != tokens->end(); it++) {
        Token* tk = *it;
        std::cout << **it << std::endl;
    }


    Parser* parser = new Parser(tokens);
    std::vector<Stmt *> *statements = parser->parse();

    if (CppLoxError::hadError) return;

    //AstPrinter prettyPr = AstPrinter();

    //std::cout << prettyPr.printf(expr) + "\n"; 
    interpreter.interpret(statements);

    clean(tokens);
    clean(statements);
    delete parser;
}
