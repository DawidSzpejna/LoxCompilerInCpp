#include "Environment.h"


#include "../Errors/Runtime/RuntimeError.h"
#include "Token.h"
#include "Stmt.h"
#include "CommonObject.h"


Environment::Environment() {
    values = new std::map<std::string, Object *>();
    this->enclosing = nullptr;
}


Environment::Environment(Environment *enclosing) {
    values = new std::map<std::string, Object *>();
    this->enclosing = enclosing;
}


Environment::~Environment() {
    delete values;

    if (this->enclosing != nullptr) {
        delete enclosing;
    }
}


void Environment::define(std::string name, Object *value) {
    if (values->count(name) != 0) {
        values->at(name) = value;
        return;
    }

    values->insert({name, value});
}


Object *Environment::get(Token* name) {
    if (values->count(name->lexem) != 0) {
        return values->at(name->lexem);
    }

    if (enclosing != nullptr) return enclosing->get(name);

    throw RuntimeError(name, 
        "Undefined variable '" + name->lexem + "'.");
}


void Environment::assign(Token *name, Object *value) {
    if (values->count(name->lexem) != 0) {
        Object *oldValue = values->at(name->lexem);
        values->at(name->lexem) = value;

        delete oldValue;
        return;
    }

    if (enclosing != nullptr) {
        enclosing->assign(name, value);
        return;
    }

    throw RuntimeError(name, 
        "Undefined variable '" + name->lexem + "'.");
}
