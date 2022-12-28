#ifndef _CPPLOX_LOXCALLABLE_
#define _CPPLOX_LOXCALLABLE_


class Token;
class Interpreter;
class Function;
class Object;
class Environment;


#include <vector>
#include <iostream>

class LoxCallable {
public:
    virtual int arity() = 0;
    virtual Object *call(Interpreter *interpreter, std::vector<Object *> *arguments)  = 0;
    virtual std::string toString() = 0;
};


class LoxFunction : public LoxCallable {
public:
    Function *declaration;
    Environment *closure;

public:
    LoxFunction(Function * declaration, Environment *env);

    virtual int arity() override;
    virtual Object *call(Interpreter *interpreter, std::vector<Object *> *arguments) override;
    virtual std::string toString() override;
};


#endif /* _CPPLOX_LOXCALLABLE_ */
