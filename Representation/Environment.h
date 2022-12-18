#ifndef _CPPLOX_ENVIRONMENT_
#define _CPPLOX_ENVIRONMENT_


#include <map>
#include <iostream>
#include "../Errors/Runtime/RuntimeError.h"
#include "Stmt.h"


class Environmnet {
private:
    Environmnet *enclosing;
    std::map<std::string, Object *>* values;

public:
    Environmnet();
    Environmnet(Environmnet *enclosing);
    ~Environmnet();
    void define(std::string name, Object *value);
    Object *get(Token* name);
    void assign(Token *name, Object *value);
};


#endif /* _CPPLOX_ENVIRONMENT_ */