#include "Environment.h"


Environmnet::Environmnet() {
    values = new std::map<std::string, Object *>();
    this->enclosing = nullptr;
}


Environmnet::Environmnet(Environmnet *enclosing) {
    values = new std::map<std::string, Object *>();
    this->enclosing = enclosing;
}


Environmnet::~Environmnet() {
    delete values;

    if (this->enclosing != nullptr) {
        delete enclosing;
    }
}


void Environmnet::define(std::string name, Object *value) {
    if (values->count(name) != 0) {
        values->at(name) = value;
        return;
    }

    values->insert({name, value});
}


Object *Environmnet::get(Token* name) {
    if (values->count(name->lexem) != 0) {
        return values->at(name->lexem);
    }

    if (enclosing != nullptr) return enclosing->get(name);

    throw RuntimeError(name, 
        "Undefined variable '" + name->lexem + "'.");
}


void Environmnet::assign(Token *name, Object *value) {
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
