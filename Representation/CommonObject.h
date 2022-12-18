#ifndef _CPPLOX_COMMONOBJECT_
#define _CPPLOX_COMMONOBJECT_


#include <iostream>
#include <sstream>


class Object {
public:
    bool have_string;
    std::string string_literal;

    bool have_float;
    float float_literal;
    
    bool have_bool;
    bool bool_literal;

    bool have_nill;

public:
    Object();
    Object(std::string str);
    Object(float number);
    Object(bool bl);
    Object(void *ptr);

    void ClearMe();
    Object *Clone();

    std::string toString();
};


#endif /* _CPPLOX_COMMONOBJECT_ */
