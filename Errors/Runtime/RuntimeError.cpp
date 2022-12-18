#include "RuntimeError.h"


RuntimeError::RuntimeError(Token *token, std::string message) {
    this->message = message;
    token = token;
}


const char *RuntimeError::what() const throw() {
    return message.c_str();
}


RuntimeError::~RuntimeError() {
    //delete token;
}
