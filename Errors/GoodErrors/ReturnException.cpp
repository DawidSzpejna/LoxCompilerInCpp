#include "ReturnException.h"
#include <sstream>


#include "../../Representation/CommonObject.h"


ReturnException::ReturnException (Object *value) {
    this->value = value;
}


const char *ReturnException::what() const throw(){
    //std::stringstream bb = std::stringstream();
    //bb << "ReturnException ";

    //if (value->have_bool) bb << value->bool_literal ? "true" : "false";
    //else if (value->have_float) bb << value->float_literal << " float";
    //else if (value->have_nill) bb << "nill";
    //else if (value->have_string) bb << value->string_literal << " string";

    //std::cout << bb.str() << std::endl;

    return "ReturnException";
}
