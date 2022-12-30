#include "Resolver.h"


#include "../Interpreter/Interpreter.h"
#include "../Representation/Stmt.h"
#include "../Representation/Expressions.h"
#include "../Representation/Token.h"
#include "../Errors/CppLoxError.h"
#include "../Representation/LoxClass.h"


Resolver::Resolver(Interpreter* interpreter) {
    this->interpreter = interpreter;
    this->currentFunction = FunctionType::NONE;
    this->currentClass = ClassType::NONE;

    scopes = new std::vector<std::map<std::string, bool> *>();
}


Resolver::~Resolver() {
    delete scopes;
}


// ----------------------- Statements ------------------------------


void Resolver::visitBlockStmt(Block *stmt) {
    beginScope();
    resolve(stmt->statements);
    endScope();
}


void Resolver::visitClassStmt(Class *stmt) {
    ClassType enclossingClass = currentClass;
    currentClass = ClassType::CLASS;


    declare(stmt->name);
    define(stmt->name);

    beginScope();
    scopes->back()->insert({"this", true});

    for (auto it = stmt->methods->begin(); it != stmt->methods->end(); it++) {
        FunctionType declaration = FunctionType::METHOD;
        if ((*it)->name->lexem == CONSTRUCTOR_NAME) {
            declaration = FunctionType::INITIALIZER;
        }

        resolveFunctions(*it, declaration);
    }

    endScope();

    currentClass = enclossingClass;
}


void Resolver::visitVarStmt(Var *stmt) {
    declare(stmt->name);
    if (stmt->initializer != nullptr) {
        resolve(stmt->initializer);
    }
    define(stmt->name);
}


void Resolver::visitFunctionStmt(Function *stmt) {
    declare(stmt->name);
    define(stmt->name);

    resolveFunctions(stmt, FunctionType::FUNCTION);
}


void Resolver::visitExpressionStmt(Expression *stmt) {
    resolve(stmt->expression);
}


void Resolver::visitIfStmt(If *stmt) {
    resolve(stmt->condition);
    resolve(stmt->thenBranch);
    if (stmt->elseBranch != nullptr) resolve(stmt->elseBranch);
}


void Resolver::visitPrintStmt(Print *stmt) {
    resolve(stmt->expression);
}


void Resolver::visitReturnStmt(Return *stmt) {
    if (currentFunction == FunctionType::NONE) {
        CppLoxError::error(stmt->keyword, 
            "Can't return from top-level code.");
    }

    if (stmt->value != nullptr) {
        if (currentFunction == FunctionType::INITIALIZER) {
            CppLoxError::error(stmt->keyword, "Can't return a value from an initializer.");
        }
        resolve(stmt->value);
    }
}


void Resolver::visitWhileStmt(While *stmt) {
    resolve(stmt->condition);
    resolve(stmt->body);
}


// ----------------------- Expresions ------------------------------


Object *Resolver::visitVariableExpr(Variable *expr) {
    if (!scopes->empty() && 
        scopes->back()->count(expr->name->lexem) != 0 && 
        (*(scopes->back()))[expr->name->lexem] == false) 
        {
            CppLoxError::error(expr->name, 
            "Can't read local variable in its own initializer.");
        }
    resolveLocal(expr, expr->name);

    return nullptr;
}


Object *Resolver::visitAssignExpr(Assign *expr) {
    resolve(expr->value);
    resolveLocal(expr, expr->name);

    return nullptr;
}


Object *Resolver::visitBinaryExpr(Binary *expr) {
    resolve(expr->left);
    resolve(expr->right);

    return nullptr;
}


Object *Resolver::visitCallExpr(Call *expr) {
    resolve(expr->callee);

    for (auto it = expr->arguments->begin(); it != expr->arguments->end(); it++) {
        resolve(*it);
    }

    return nullptr;
}


Object *Resolver::visitGetExpr(Get *expr) {
    resolve(expr->object);

    return nullptr;
}


Object *Resolver::visitGroupingExpr(Grouping *expr) {
    resolve(expr->expression);

    return nullptr;
}


Object *Resolver::visitLiteralExpr(Literal *expr) {
    // nothing ..

    return nullptr;
}


Object *Resolver::visitLogicalExpr(Logical *expr) {
    resolve(expr->left);
    resolve(expr->right);

    return nullptr;
}


Object *Resolver::visitSetExpr(Set *expr) {
    resolve(expr->value);
    resolve(expr->object);

    return nullptr;
}


Object *Resolver::visitThisExpr(This *expr) {
    if (currentClass == ClassType::NONE) {
        CppLoxError::error(expr->keyword, "Can't use 'this' outside of a class.");
        return nullptr;
    }


    resolveLocal(expr, expr->keyword);

    return nullptr;
}


Object *Resolver::visitUnaryExpr(Unary *expr) {
    resolve(expr->right);

    return nullptr;
}


// -------------------------------------------------------------------


void Resolver::resolveLocal(Expr *expr, Token *name) {
    for (int i = scopes->size() - 1; i >= 0; i--) {
        if (((*scopes)[i])->count(name->lexem) != 0) {
            interpreter->resolve(expr, scopes->size() - 1 - i);
            return;
        }
    }
}


void Resolver::resolve(std::vector<Stmt *> *statements){
    for (auto it = statements->begin(); it != statements->end(); it++) {
        resolve(*it);
    }
}


void Resolver::resolve(Stmt *stmt) {
    stmt->accpetV(this);
}


void Resolver::resolve(Expr *expr) {
    expr->accpetO(this);
}


void Resolver::beginScope() {
    scopes->push_back(new std::map<std::string, bool>());
}


void Resolver::endScope() {
    std::map<std::string, bool> *tmp = scopes->back();
    scopes->pop_back();

    delete tmp;
}


void Resolver::declare(Token *token) {
    if (scopes->empty()) return;

    std::map<std::string, bool> *scope = scopes->back();
    if (scope->count(token->lexem) != 0) {
        CppLoxError::error(token,
            "Already a variable with this name in this scope");
    }

    scope->insert({token->lexem, false});
}


void Resolver::define(Token *token) {
    if (scopes->empty()) return;
    (*(scopes->back()))[token->lexem] = true;
}

void Resolver::resolveFunctions(Function *function, FunctionType type) {
    FunctionType enclosingFunction = currentFunction;
    currentFunction = type;

    beginScope();
    for (auto it = function->params->begin(); it != function->params->end(); it++) {
        declare(*it);
        define(*it);
    }
    resolve(function->body);
    endScope();

    currentFunction = enclosingFunction;
}
