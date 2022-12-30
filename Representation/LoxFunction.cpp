#include "LoxFunction.h"


#include "../Representation/Environment.h"
#include "../Interpreter/Interpreter.h"
#include "../Representation/CommonObject.h"
#include "../Representation/Stmt.h"
#include "../Representation/Environment.h"
#include "../Representation/Token.h"
#include "../Errors/GoodErrors/ReturnException.h"


LoxFunction::LoxFunction(Function * declaration, Environment* env, bool isInitializer) :  LoxCallable() {
    this->closure = env;
    this->declaration = declaration;
    this->isInitializer = isInitializer;
}


LoxFunction *LoxFunction::bind(LoxInstance *instace) {
    Environment *environment = new Environment(closure);
    environment->define("this", new Object(instace));
    return new LoxFunction(declaration, environment, isInitializer);
}


int LoxFunction::arity() {
    return declaration->params->size();
}


Object *LoxFunction::call(Interpreter *interpreter, std::vector<Object *> *arguments) {
    Environment *environment = new Environment(closure);
    for (int i = 0; i < declaration->params->size(); i++) {
        environment->define((*(declaration->params))[i]->lexem, (*arguments)[i]);
    }

    try {
        interpreter->executeBlock(declaration->body, environment);
    }
    catch (ReturnException returnValue) {
        if (isInitializer) return closure->getAt(0, "this");

        return returnValue.value;
    }

    if (isInitializer) return closure->getAt(0, "this");
    return nullptr;
}


std::string LoxFunction::toString() {
    return "<fn " + declaration->name->lexem + ">";
}
