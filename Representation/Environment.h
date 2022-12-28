#ifndef _CPPLOX_ENVIRONMENT_
#define _CPPLOX_ENVIRONMENT_


#include <map>
#include <iostream>


class Object;
class Token;


class Environment {
private:
    Environment *enclosing;
    std::map<std::string, Object *>* values;

public:
    Environment();
    Environment(Environment *enclosing);
    ~Environment();
    void define(std::string name, Object *value);
    Object *get(Token* name);
    void assign(Token *name, Object *value);
};


#endif /* _CPPLOX_ENVIRONMENT_ */