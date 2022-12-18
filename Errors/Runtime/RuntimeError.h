#ifndef _CPPLOX_RUNTIMEERROR_
#define _CPPLOX_RUNTIMEERROR_


#include <iostream>
#include "../../Representation/Token.h"

class RuntimeError : public std::exception {
public:
    Token *token;
    std::string message;

public:
    RuntimeError(Token *token, std::string message);
    const char *what() const throw();
    ~RuntimeError();
};


#endif /* _CPPLOX_RUNTIMEERROR_ */