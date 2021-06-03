//
// Created by 刘一辰 on 2021/5/20.
//

#ifndef NODELIST_H
#define NODELIST_H

#include "llvm/IR/Value.h"
#include "defineList.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace llvm;
using namespace std;

class SkyType;
class Identifier;
class StatNode;
class CompoundStat;
class FuncDec;
class ConstDec;
class VarDec;
class GlobalArea;
class ExprNode;
class ClassDec;
class PointerNode;

typedef vector<Identifier*> IdentifierList;
typedef vector<StatNode*>   StatList;
typedef vector<FuncDec*>    FuncDecList;
typedef vector<ConstDec*>   ConstDecList;
typedef vector<VarDec*>     VarDecList;
typedef vector<ExprNode*>   ExprList;
typedef vector<ClassDec*>   ClassDecList;

// enum type of variable and const
// const type only contains: int, char, float, double, char*, bool
// Example:
//          123    -> new SkyInt(123) -> SkyInt.value.iVal = 123, SkyInt.getType() = SKY_INT
//          '1'    -> new SkyChar('1') -> SkyChar.value.cVal = '1', SkyChar.getType() = SKY_CHAR
//          1.23f  -> new SkyFloat(1.23f) -> SkyFloat.value.fVal = 1.23f, SkyFloat.getType() = SKY_FLOAT
//          1.23   -> new SkyDouble(1.23) -> SkyDouble.value.dVal = 1.23, SkyDouble.getType() = SKY_DOUBLE
//          "123"  -> new SkyCharPointer("123") -> SkyCharPointer.value.sVal = "123", SkyCharPointer.getType() = SKY_CHAR_POINTER
//          true   -> new SkyBool(true) -> SkyBool.value.bVal = true, SkyBool.getType() = SKY_BOOl
enum SkyVarType {
    SKY_INT,
    SKY_INT_POINTER,
    SKY_INT_64,
    SKY_INT_64_POINTER,
    SKY_CHAR,
    SKY_CHAR_POINTER,
    SKY_FLOAT,
    SKY_FLOAT_POINTER,
    SKY_DOUBLE,
    SKY_DOUBLE_POINTER,
    SKY_BOOL,
    SKY_BOOL_POINTER
};

union ConstValueUnion{
    int iVal;
    bool bVal;
    char cVal;
    char* sVal;
    float fVal;
    double dVal;
};

enum SkyTypes {
    SKY_ARRAY,
    SKY_VOID,
    SKY_VAR
};

enum BinaryOperators {
    OP_PLUS,
    OP_MINUS,
    OP_MUL,
    OP_DIV,
    OP_EQ,
    OP_NE,
    OP_GT,
    OP_LT,
    OP_GE,
    OP_LE,
    OP_AND,
    OP_OR,
    OP_XOR,
    OP_MOD,
    OP_LEFT,  // "<<"
    OP_RIGHT, // ">>"
    OP_PTR
};

enum TypeOfJump {
    BREAK,
    CONTINUE,
    RETURN
};

class ASTNode{
public:
    virtual Value *convertToCode() = 0;
    virtual ~ASTNode() = default;
};

// the node for expression
// expression has return value
class ExprNode: public ASTNode {

};

// the node for statement
// statement doesn't have return value
class StatNode: public ASTNode {
public:
//    void forward();
    void backward();
//    BasicBlock *afterBB{};
};

// Program is split into GlobalArea and MainFunction
class Program: public StatNode {
public:
    Program(GlobalArea *globalArea, FuncDec *mainFunc): globalArea(globalArea), mainFunc(mainFunc) { }
    Value *convertToCode() override;

private:
    GlobalArea* globalArea;
    FuncDec *mainFunc;
};

class ConstValue: public ExprNode{
public:
    Value *convertToCode() override;
    virtual SkyVarType getType() = 0;
    virtual ConstValueUnion getValue() = 0;
    virtual ConstValue *operator-() = 0;
};

class SkyInt : public ConstValue {
public:
    explicit SkyInt(int v) {
        value.iVal = v;
    }
    SkyVarType getType() override {
        return SKY_INT;
    }
    ConstValueUnion getValue() override {
        return value;
    }
    ConstValue *operator-() override {
        return new SkyInt(-value.iVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion value{};
};

class SkyDouble: public ConstValue {
public:
    explicit SkyDouble(double v) {
        value.dVal = v;
    }
    SkyVarType getType() override {
        return SKY_DOUBLE;
    }
    ConstValueUnion getValue() override {
        return value;
    }
    ConstValue *operator-() override {
        return new SkyDouble(-value.dVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion value{};
};

class SkyFloat: public ConstValue {
public:
    explicit SkyFloat(float v) {
        value.fVal = v;
    }
    SkyVarType getType() override {
        return SKY_FLOAT;
    }
    ConstValueUnion getValue() override {
        return value;
    }
    ConstValue *operator-() override {
        return new SkyDouble(-value.fVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion value{};
};

class SkyChar: public ConstValue {
public:
    explicit SkyChar(char v) {
        value.cVal = v;
    }
    SkyVarType getType() override {
        return SKY_CHAR;
    }
    ConstValueUnion getValue() override {
        return value;
    }
    ConstValue *operator-() override {
        return new SkyDouble(-value.cVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion value{};
};

class SkyCharPointer: public ConstValue {
public:
    explicit SkyCharPointer(const string& v) {
        value.sVal = (char*)v.c_str();
    }
    SkyVarType getType() override {
        return SKY_CHAR_POINTER;
    }
    ConstValueUnion getValue() override {
        return value;
    }
    Value *convertToCode() override;

private:
    ConstValueUnion value{};
};

class SkyBool: public ConstValue {
public:
    explicit SkyBool(bool v) {
        value.bVal = v;
    }
    SkyVarType getType() override {
        return SKY_BOOL;
    }
    ConstValueUnion getValue() override {
        return value;
    }
    ConstValue *operator-() override {
        return new SkyBool(!value.bVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion value{};
};

class SkyArrayType: public StatNode {
public:
    SkyArrayType(SkyVarType *type, int size): type(type), size(size) { }
    Value *convertToCode() override;

private:
    SkyVarType *type;
    int size;
};

// all the types in Sky
// including:   SKY_ARRAY : array type   example: int[10]
//              SKY_VAR : simple types (SKY_INT, SKY_FLOAT, ...)
//              SKY_VOID : now is only used in the function return type, which means the function has no return value
class SkyType: public StatNode {
public:
    explicit SkyType(SkyArrayType *arrayType): arrayType(arrayType), type(SKY_ARRAY) { }
    explicit SkyType(SkyVarType *varType): varType(varType), type(SKY_VAR) { }
    SkyType(): type(SKY_VOID) { }
    Value *convertToCode() override;
    Type* toLLVMType();
//    Constant* initValue(ConstValue *v = nullptr);

    SkyArrayType *arrayType{};
    SkyVarType *varType{};
    SkyTypes type;
};

// In human terms, it can be seen as the name of something(variable, function, class, const, ...)
class Identifier: public ExprNode {
public:
    explicit Identifier(string name): name(std::move(name)) { }
    Value *convertToCode() override;
    string name;
};

class VarDec: public StatNode {
public:
    VarDec(Identifier *id, SkyType *type, ExprNode* expr): id(id), type(type), expr(expr), global(false) { }
    Value *convertToCode() override;
    bool isGlobal() const {
        return this->global;
    }
    void setGlobal() {
        this->global = true;
    }
    Identifier *id;
    SkyType *type;    // if type == nullptr, need Type Inference
    ExprNode *expr;     // when type == nullptr, calculate this expr to get the type
    bool global;
};

class ConstDec: public StatNode {
public:
    ConstDec(Identifier *id, ConstValue *cv): id(id), value(cv), global(false) { }
    Value *convertToCode() override;
    bool isGlobal() const {
        return this->global;
    }
    void setGlobal() {
        this->global = true;
    }

private:
    Identifier *id;
    ConstValue *value;
    bool global;
};

class TypeDec: public StatNode {
public:
    TypeDec(Identifier *id, SkyType *type): id(id), type(type) { }

private:
    Identifier *id;
    SkyType *type;
};

class FuncDec: public StatNode {
public:
    FuncDec(Identifier *name, VarDecList *paraList, SkyType *returnType, CompoundStat *funcBody): id(name), paraList(paraList), retType(returnType), body(funcBody) { }
    FuncDec(Identifier *name, VarDecList *paraList, CompoundStat *funcBody): id(name), paraList(paraList), body(funcBody) {
        retType = new SkyType();
    }
    Value *convertToCode() override;

private:
    Identifier *id;
    VarDecList *paraList;
    SkyType *retType;
    CompoundStat *body;
};

class ClassBody: public StatNode {
public:
    ClassBody(FuncDec *init, FuncDec *del, FuncDecList *funcList): initClass(init), delClass(del), funcList(funcList) { }

private:
    FuncDec *initClass, *delClass;
    FuncDecList *funcList;
};

class ClassDec: public StatNode {
public:
    ClassDec(Identifier *name, Identifier *father, ClassBody *body): name(name), father(father), body(body) { }

private:
    Identifier *name, *father; // father can be null
    ClassBody *body;
};

class AssignStat: public StatNode {
public:
    AssignStat(ExprNode *lexpr, ExprNode *rexpr): left_expr(lexpr), right_expr(rexpr) { }

private:
    ExprNode *left_expr, *right_expr;
};

class PrintStat: public StatNode {
public:
    explicit PrintStat(ExprList *exprList): exprList(exprList) { }

private:
    ExprList *exprList;
};

class ScanStat: public StatNode {
public:
    explicit ScanStat(IdentifierList *nameList): nameList(nameList) { }
    IdentifierList *nameList;
};

class IfStat: public StatNode {
public:
    IfStat(ExprNode *condExpr, CompoundStat *thenStat, CompoundStat *elseStat): condExpr(condExpr), thenStat(thenStat), elseStat(elseStat) { }
    Value *convertToCode() override;

private:
    ExprNode *condExpr;
    CompoundStat *thenStat, *elseStat;
};

class ForStat: public StatNode {
public:
    ForStat(Identifier *forVar, int start, int end, int step, CompoundStat* body):
         forVar(forVar), start(start), end(end), step(step), body(body) { }

private:
    int start, end, step;
    CompoundStat *body;
    Identifier *forVar;
};

class WhileStat: public StatNode {
public:
    WhileStat(ExprNode *cond, CompoundStat* body): cond(cond), body(body) { }

private:
    ExprNode *cond;
    CompoundStat *body;
};

class JumpStat: public StatNode {
public:
    JumpStat(TypeOfJump type, ExprNode *retExpr): type(type), retExpr(retExpr) { }

private:
    ExprNode *retExpr;
    TypeOfJump type;
};

class CompoundStat: public StatNode {
public:
    explicit CompoundStat(StatList *statList): statList(statList) { }

private:
    StatList *statList;
};

class BinaryExpr: public ExprNode {
public:
    BinaryExpr(ExprNode *left, BinaryOperators op, ExprNode *right): left(left), op(op), right(right) { }

private:
    ExprNode *left, *right;
    BinaryOperators op;
};

class ArrayRef: public ExprNode {
public:
    ArrayRef(Identifier *id, ExprNode *subInd): id(id), subInd(subInd) { }

private:
    Identifier *id;
    ExprNode *subInd;
};

class ClassRef: public ExprNode {
public:
    ClassRef(Identifier *id, Identifier *childId): id(id), childId(childId) { }

private:
    Identifier *id, *childId;
};

class FuncCall: public ExprNode, StatNode {
public:
    FuncCall(Identifier *id, ExprList *args): id(id), args(args) { }

private:
    Identifier *id;
    ExprList *args;
};

class PointerNode: public ExprNode {
public:
    PointerNode(ExprNode *expr): expr(expr) { }
    ExprNode *expr;
};

class ReferenceNode: public ExprNode {
    ReferenceNode(Identifier *id): id(id) { }
    Identifier *id;
};

// GlobalArea can only do some definition
// including const, variable, function and class
// especially, function and class can only be defined in the GlobalArea
class GlobalArea: public StatNode {
public:
    GlobalArea() = default;
    void addConstDec(ConstDecList *cd) {
        for (auto & constDec : *cd) {
            constDec->setGlobal();
        }
        constDecList->insert(constDecList->end(), cd->begin(), cd->end());
    }
    void addVarDec(VarDecList *vd) {
        for (auto & varDec : *vd) {
            varDec->setGlobal();
        }
        varDecList->insert(varDecList->end(), vd->begin(), vd->end());
    }
    void addFuncDec(FuncDec *fd) {
        funcDecList->push_back(fd);
    }
    void addClassDec(ClassDec *cd) {
        classDecList->push_back(cd);
    }
    Value *convertToCode() override;

private:
    ConstDecList *constDecList{};
    VarDecList *varDecList{};
    FuncDecList *funcDecList{};
    ClassDecList *classDecList{};
};

#endif
