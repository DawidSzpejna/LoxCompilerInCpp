#ifndef _CPPLOX_STMTVISITOR_
#define _CPPLOX_STMTVISITOR_


class Expression;
class Print;
class Var;
class Block;
class If;
class While;
class Function;
class Return;


template <typename R>
class StmtVisitor{
public:
    virtual R visitBlockStmt(Block *stmt) = 0;
    //virtual R visitClassStmt(Class stmt) = 0;
    virtual R visitExpressionStmt(Expression *stmt) = 0;
    virtual R visitFunctionStmt(Function *stmt) = 0;
    virtual R visitIfStmt(If *stmt) = 0;
    virtual R visitPrintStmt(Print *stmt) = 0;
    virtual R visitReturnStmt(Return *stmt) = 0;
    virtual R visitVarStmt(Var *stmt) = 0;
    virtual R visitWhileStmt(While *stmt) = 0;
};


#endif /* _CPPLOX_STMTVISITOR_ */
