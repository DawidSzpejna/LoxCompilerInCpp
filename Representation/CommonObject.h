#ifndef _CPPLOX_COMMONOBJECT_
#define _CPPLOX_COMMONOBJECT_


class LoxCallable;
class LoxClass;
class LoxInstance;


#include <iostream>


class Object {
public:
    bool have_string;
    std::string string_literal;

    bool have_float;
    float float_literal;
    
    bool have_bool;
    bool bool_literal;

    bool have_nill;

    bool have_function;
    LoxCallable *fun_object;

    bool have_class;
    LoxClass *class_object;

    bool have_instance;
    LoxInstance *instance_object;

public:
    Object();
    Object(std::string str);
    Object(float number);
    Object(bool bl);
    Object(void *ptr);
    Object(LoxCallable *fun);
    Object(LoxClass *klass);
    Object(LoxInstance *instance);

    void ClearMe();
    Object *Clone();

    std::string toString();
};


#endif /* _CPPLOX_COMMONOBJECT_ */
