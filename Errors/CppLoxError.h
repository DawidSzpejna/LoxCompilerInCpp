#ifndef _CPPLOX_CPPLOXERROR_
#define _CPPLOX_CPPLOXERROR_

#include "../Representation/Token.h"
#include "Runtime/RuntimeError.h"

#include <iostream>

class CppLoxError
{
public:
    static bool hadError;
    static bool hadRuntimeError;

    static void error(int line, std::string message);
    static void error(Token* token, std::string message);
    static void report(int line, std::string where, std::string message);
    static void runtimeError(RuntimeError &error);

private:
    CppLoxError() {}
};
#endif
