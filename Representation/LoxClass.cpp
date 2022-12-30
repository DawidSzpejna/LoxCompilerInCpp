#include "LoxClass.h"


#include "Environment.h"
#include "CommonObject.h"
#include "Stmt.h"
#include "Environment.h"
#include "Token.h"
#include "LoxInstance.h"
#include "LoxFunction.h"
#include "../Interpreter/Interpreter.h"
#include "../Errors/GoodErrors/ReturnException.h"


LoxClass::LoxClass(std::string name,  std::map<std::string, LoxFunction *> *methods) {
    this->name = name;
    this->methods = methods;
}


LoxFunction *LoxClass::findMethod(std::string name) {
    if (methods->count(name) != 0) {
        return methods->at(name);
    }

    return nullptr;
}


int LoxClass::arity() {
    LoxFunction *initializer = findMethod(CONSTRUCTOR_NAME);
    if (initializer == nullptr) return 0;

    return initializer->arity();
}


// It is responsible for craating instances of classes.
Object *LoxClass::call(Interpreter *interpreter, std::vector<Object *> *arguments) {
    LoxInstance *instance = new LoxInstance(this);

    // If any constructor exists (which has a form "init(...)"), use it.
    LoxFunction *initializer = findMethod(CONSTRUCTOR_NAME);
    if (initializer != nullptr) {
        initializer->bind(instance)->call(interpreter, arguments);
    }
    
    Object *tmp = new Object(instance);
    return tmp;
}


std::string LoxClass::toString() {
    return name;
}
