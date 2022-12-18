#include "CppLoxError.h"
bool CppLoxError::hadError = false;
bool CppLoxError::hadRuntimeError = false;

void CppLoxError::error(int line, std::string message) 
{
    report(line, "", message);
}


void CppLoxError::error(Token* token, std::string message) {
    if (token->type == TokenType::EOFF) {
        report(token->line, " at end", message);
    }
    else {
        report(token->line, " at '" + token->lexem + "'", message);
    }
}


void CppLoxError::report(int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error " << where << ": " << message << std::endl;
    hadError = true;
}


void CppLoxError::runtimeError(RuntimeError &error)
{
    std::string str = error.what();
    std::cerr << str + "\n[line " << error.token->line << "]" << std::endl;
    hadRuntimeError = true;
}
