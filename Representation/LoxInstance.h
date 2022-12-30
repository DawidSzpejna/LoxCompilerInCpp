#ifndef _CPPLOX_LOXINSTANCE_
#define _CPPLOX_LOXINSTANCE_


class LoxClass;
class Object;
class Token;


#include <iostream>
#include <map>


class LoxInstance {
private: 
    LoxClass *klass;
    std::map<std::string, Object *> *fileds;

public: 
    LoxInstance(LoxClass *klass);

    Object *get(Token *name);
    void set(Token *name, Object *value);
    std::string toString();
};


#endif
