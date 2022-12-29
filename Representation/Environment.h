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
    Environment *ancestor(int distance);
    Object *get(Token* name);
    Object *getAt(int distance, std::string name);
    void assignAt(int distance, Token *name, Object *value);
    void assign(Token *name, Object *value);
};


#endif /* _CPPLOX_ENVIRONMENT_ */