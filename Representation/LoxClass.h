#ifndef _CPPLOX_LOXCLASS_
#define _CPPLOX_LOXCLASS_


#define CONSTRUCTOR_NAME "init"


class Token;
class Interpreter;
class Function;
class Object;
class Environment;
class LoxFunction;


#include <iostream>
#include <map>


#include "LoxCallable.h"


class LoxClass : public LoxCallable {
private:
    std::map<std::string, LoxFunction *> *methods;

public:
    std::string name;

    LoxClass(std::string name, std::map<std::string, LoxFunction *> *methods);

    LoxFunction *findMethod(std::string name);
    int arity() override;
    Object *call(Interpreter *interpreter, std::vector<Object *> *arguments) override;

    std::string toString() override;
};


#endif
