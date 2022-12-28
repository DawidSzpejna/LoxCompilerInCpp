#include "Interpreter.h"


#include "../Representation/Stmt.h"
#include "../Representation/Expressions.h"
#include "../Representation/Environment.h"
#include "../Representation/LoxCallable.h"
#include "../Errors/CppLoxError.h"
#include "../Errors/Runtime/RuntimeError.h"
#include "../Representation/CommonObject.h"
#include "../Errors/GoodErrors/ReturnException.h"


// ------------------------------------------- NATIVE FUNCTIONS


class : public LoxCallable {
public:
    int arity() override {
        return 0;
    }

    Object *call(Interpreter *interpreter, std::vector<Object *> *arguments) override {
        return new Object(12.0f);
    }

    std::string toString() {
        return "<native clock()>";
    }
} test;


// -------------------------------------------------------------


Interpreter::Interpreter() {
    globals = new Environment();
    environment = globals;

    Object *clock_function = new Object(&test);
    globals->define("clock", clock_function);
}


void Interpreter::interpret(std::vector<Stmt*> *expression) {
    try {
        for (auto it = expression->begin(); it != expression->end(); it++) {
            execute(*it);
        }
    }
    catch (RuntimeError error) {
        CppLoxError::runtimeError(error);
    }
}


Object *Interpreter::visitBinaryExpr(Binary* expr) {
    Object *right = evaluate(expr->right);
    Object *left = evaluate(expr->left);

    Object* obj = nullptr;
    switch (expr->this_operator->type)
    {
        case TokenType::MINUS: {
            checkNumberOperands(expr->this_operator, left, right);
                float answer = left->float_literal - right->float_literal;

                obj = new Object(answer);
        } break;

        case TokenType::SLASH: {
            checkNumberOperands(expr->this_operator, left, right);
            //if (right->have_float && left->have_float) {
                float answer = left->float_literal / right->float_literal;

                obj = new Object(answer);
            //}
        } break;
    
        case TokenType::STAR: {
            checkNumberOperands(expr->this_operator, left, right);
            //if (right->have_float && left->have_float) {
                float answer = left->float_literal * right->float_literal;

                obj = new Object(answer);
            //}
        } break;

        case TokenType::PLUS: {
            if (right->have_float && left->have_float) {
                float answer = left->float_literal + right->float_literal;

                obj = new Object(answer);
            }
            else if (right->have_string && left->have_string) {
                std::string answer = left->string_literal + right->string_literal;


                obj = new Object(answer);
            }
            else {
                throw RuntimeError(expr->this_operator, "Operand must be two numbers or two strings.");
            }
        } break;

        case TokenType::GREATER: {
            checkNumberOperands(expr->this_operator, left, right);
            //if (right->have_float && left->have_float) {
                bool answer = left->float_literal > right->float_literal;

                obj = new Object(answer);
            //}
        } break;

        case TokenType::GREATER_EQUAL: {
            checkNumberOperands(expr->this_operator, left, right);
            //if (right->have_float && left->have_float) {
                bool answer = left->float_literal >= right->float_literal;

                obj = new Object(answer);
            //}
        } break;


        case TokenType::LESS: {
            checkNumberOperands(expr->this_operator, left, right);
            //if (right->have_float && left->have_float) {
                bool answer = left->float_literal < right->float_literal;

                obj = new Object(answer);
            //}
        } break;


        case TokenType::LESS_EQUAL: {
            checkNumberOperands(expr->this_operator, left, right);
            //if (right->have_float && left->have_float) {
                bool answer = left->float_literal <= right->float_literal;

                obj = new Object(answer);
            //}
        } break;


        case TokenType::BANG_EQUAL: {
            bool answer = !isEqual(left, right);

            obj = new Object(answer);
        } break;

        case TokenType::EQUAL_EQUAL: {
            bool answer = isEqual(left, right);

            obj = new Object(answer);
        }
    }

    // delete right;
    // delete left;

    return obj;
}


Object *Interpreter::visitCallExpr(Call *expr) {
    Object *callee = evaluate(expr->callee);

    std::vector<Object *> *arguments = new std::vector<Object *>();
    for (auto it = expr->arguments->begin(); it != expr->arguments->end(); it++) {
        arguments->push_back((Object *)evaluate(*it));
    }

    if (!callee->have_function) {
        throw RuntimeError(expr->paren, "Can only call functions and classes.");
    }

    LoxCallable *function = callee->fun_object;

    if (function->arity() != arguments->size()) {
        std::stringstream message;
        message << "Expected " << function->arity() << " arguments but got " << arguments->size() << ".";

        throw RuntimeError(expr->paren, message.str());
    }

    return function->call(this, arguments);
}


Object *Interpreter::visitUnaryExpr(Unary* expr) {
    Object *right = evaluate(expr->right);

    switch (expr->this_operator->type)
    {
        case TokenType::BANG: {
            bool answer = isTruthy(right);

            right->ClearMe();
            right->have_bool = true;
            right->bool_literal = !answer;
            return right;
        }

        case TokenType::MINUS: {
            checkNumberOperand(expr->this_operator, right);
            //if (right->have_float) {
                right->float_literal *= -1;
                return right;
            //}
        } break;
    }

    return nullptr;
}


Object *Interpreter::visitGroupingExpr(Grouping* expr) {
    return evaluate(expr->expression);
}


Object *Interpreter::visitLiteralExpr(Literal* expr) {
    return expr->value;
}


Object *Interpreter::visitLogicalExpr(Logical* expr) {
    Object *left = evaluate(expr->left);

    if (expr->this_operator->type == TokenType::OR) {
      if (isTruthy(left)) return left;
    } else {
      if (!isTruthy(left)) return left;
    }

    return evaluate(expr->right);
}


Object *Interpreter::visitVariableExpr(Variable *expr) {
    return environment->get(expr->name);
}


Object *Interpreter::visitAssignExpr(Assign *expr) {
    Object *value = evaluate(expr->value);
    environment->assign(expr->name, value);
    return value;
}


void Interpreter::visitBlockStmt(Block *stmt) {
    executeBlock(stmt->statements, new Environment(environment));
}


void Interpreter::visitExpressionStmt(Expression *stmt) {
    evaluate(stmt->expression);
}


void Interpreter::visitFunctionStmt(Function *stmt) {
    LoxFunction *function = new LoxFunction(stmt, this->environment);
    environment->define(stmt->name->lexem, new Object(function));
}


void Interpreter::visitIfStmt(If *stmt) {
    if (isTruthy(evaluate(stmt->condition))) {
        execute(stmt->thenBranch);
    }
    else if (stmt->elseBranch != nullptr) {
        execute(stmt->elseBranch);
    }
}


void Interpreter::visitReturnStmt(Return *stmt) {
    Object *value = nullptr;
    if (stmt->value != nullptr) value = evaluate(stmt->value);

    throw ReturnException(value);
}


void Interpreter::visitPrintStmt(Print *stmt) {
    Object *value = evaluate(stmt->expression);
    std::cout << stringify(value)  << std::endl;
}


void Interpreter::visitVarStmt(Var *stmt) {
    Object *value = nullptr;
    if (stmt->initializer != nullptr) {
        value = evaluate(stmt->initializer);
    }

    environment->define(stmt->name->lexem, value);
}


void Interpreter::visitWhileStmt(While *stmt) {
    while (isTruthy(evaluate(stmt->condition))) {
        execute(stmt->body);
    }
}


Object *Interpreter::evaluate(Expr *expr) {
    return expr->accpetO(this);
}


void Interpreter::execute(Stmt *stmt) {
    stmt->accpetV(this);
}


void Interpreter::executeBlock(std::vector<Stmt *> *statements, Environment *environment) {
    Environment *previous = this->environment;
    bool CatchedSomething = false;

    try
    {
        this->environment = environment;

        for (auto it = statements->begin(); it != statements->end(); it++) {
            execute(*it);
        }
    }
    catch (...) {
        auto e = std::current_exception();
        this->environment = previous;
        CatchedSomething = true;

        throw;
    }

    if (!CatchedSomething) this->environment = previous;
}


bool Interpreter::isTruthy(Object *object) {
    if (object->have_nill) return false;
    if (object->have_bool) return object->bool_literal;

    return true;
}


bool Interpreter::isEqual(Object *a, Object *b) {
    const float EPSILON = 0.000001f;

    if (a->have_nill && b->have_nill) return true;

    if (a->have_float && b->have_float) {
        float comparing = a->float_literal - b->float_literal;
        
        if (comparing < 0) {
            comparing *= -1;
        }

        return comparing < EPSILON;
    }

    if (a->have_string && b->have_string) {
        return a->string_literal == b->string_literal;
    }

    if (a->have_bool && b->have_bool) {
        return a->bool_literal == b->bool_literal;
    }

    return false;
}


void Interpreter::checkNumberOperand(Token *oper, Object* operad) {
    if (operad->have_float) return;

    throw RuntimeError(oper, "Operand must be a number.");
}


void Interpreter::checkNumberOperands(Token *oper, Object* left, Object* right) {
    if (left->have_float && right->have_float) return;

    throw RuntimeError(oper, "Operands must be a numbers.");
}


std::string Interpreter::stringify(Object *object) {
    if (object == nullptr) return "nil";

    return object->toString();
}
