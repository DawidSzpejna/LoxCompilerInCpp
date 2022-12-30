#include "LoxInstance.h"


#include "LoxClass.h"
#include "CommonObject.h"
#include "Token.h"
#include "LoxFunction.h"
#include "../Interpreter/Interpreter.h"
#include "../Errors/Runtime/RuntimeError.h"


LoxInstance::LoxInstance(LoxClass *klass) {
    this->klass = klass;
    this->fileds = new std::map<std::string, Object *>();
}


Object *LoxInstance::get(Token *name) {
    if (fileds->count(name->lexem) != 0) {
        return fileds->at(name->lexem);
    }

    LoxFunction *method = klass->findMethod(name->lexem);
    if (method != nullptr) return new Object(method->bind(this));

    throw RuntimeError(name, "Undefined property '" + name->lexem + "'.");
}


void LoxInstance::set(Token *name, Object *value) {
    if (fileds->count(name->lexem) == 0) {
        fileds->insert({name->lexem, value});
        return;
    }

    fileds->at(name->lexem) = value;
}


std::string LoxInstance::toString() {
    return klass->name + " instance";
}
