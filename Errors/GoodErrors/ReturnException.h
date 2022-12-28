#ifndef _CPPLOX_RETURNEXCEPTION_
#define _CPPLOX_RETURNEXCEPTION_


class Object;


//#include <iostream>
#include <exception>


class ReturnException : std::exception {
public:
    Object *value;

    ReturnException (Object *value);

    const char *what() const throw();
};


#endif
