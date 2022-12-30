#ifndef _CPPLOX_LOXFUNCTION_
#define _CPPLOX_LOXFUNCTION_


class Function;
class Environment;
class Object;
class Interpreter;
class LoxInstance;


#include <vector>
#include <iostream>


#include "LoxCallable.h"


class LoxFunction : public LoxCallable {
public:
    Function *declaration;
    Environment *closure;
    bool isInitializer;

public:
    LoxFunction(Function * declaration, Environment *env, bool isInitializer);

    LoxFunction *bind(LoxInstance *instace);
    virtual int arity() override;
    virtual Object *call(Interpreter *interpreter, std::vector<Object *> *arguments) override;
    virtual std::string toString() override;
};

#endif
