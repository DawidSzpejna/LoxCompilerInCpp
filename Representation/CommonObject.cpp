#include "CommonObject.h"


#include "LoxCallable.h"


#include <sstream>


Object::Object()
{
    ClearMe();
}


Object::Object(std::string str) : Object()
{
    string_literal = str;
    have_string = true;
}


Object::Object(float number) : Object()
{
    float_literal = number;
    have_float = true;
}


Object::Object(bool bl) : Object()
{
    bool_literal = bl;
    have_bool = true;
}


Object::Object(void *ptr) : Object()
{
    have_nill = true;
}


Object::Object(LoxCallable *fun)  : Object()
{
    have_function = true;
    fun_object = fun;
}


Object *Object::Clone(){
    Object* tmp = new Object();
    tmp->have_bool = this->have_bool;
    tmp->have_float = this->have_float;
    tmp->have_nill = this->have_nill;
    tmp->have_string = this->have_string;
    tmp->have_function = this->have_function;
    
    tmp->bool_literal = this->bool_literal;
    tmp->float_literal = this->float_literal;
    tmp->string_literal = this->string_literal;
    tmp->fun_object = this->fun_object; // <------------- wymaga poprawy !!!
    
    return tmp;   
}


void Object::ClearMe()
{
    have_string = have_float = have_bool = have_nill = have_function = false;
}



std::string Object::toString() {
    if (have_float) {
        std::stringstream bld = std::stringstream();
        bld << float_literal;
        return bld.str();
    }

    if (have_bool) {
        return bool_literal ? "true" : "false";
    }

    if (have_nill) {
        return "nill";
    }

    if (have_function) {
        return fun_object->toString();
    }

    return string_literal;
}
