//
// Created by 刘一辰 on 2021/5/20.
//

#ifndef NODELIST_H
#define NODELIST_H

#include "llvm/IR/Value.h"
#include "defineList.h"
#include <iostream>
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

typedef vector<Identifier*> IdentifierList;
typedef vector<StatNode*>   StatList;
typedef vector<FuncDec*>    FuncDecList;
typedef vector<ConstDec*>   ConstDecList;
typedef vector<VarDec*>     VarDecList;
typedef vector<ExprNode*>   ExprList;
typedef vector<ClassDec*>   ClassDecList;


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
    SKY_BOOL_POINTER,
    SKY_STRING
};

enum SkyTypes {
    SKY_ARRAY,
    SKY_RANGE,
    SKY_VOID,
    SKY_VAR,
//    SKY_ENUM,
    SKY_CLASS,
//    SKY_ENUM_RANGE,
//    SKY_USER_DEFINE,
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
    OP_LEFT,
    OP_RIGHT,
    OP_INC,
    OP_DEC,
    OP_PTR
};

enum TypeOfIteration {
    FOR,
    WHILE,
    DO_WHILE
};

enum TypeOfJump {
    BREAK,
    CONTINUE,
    RETURN
};

enum AssignType {
    ID_ASSIGN,
    ARRAY_ASSIGN,
    CLASS_ASSIGN
};

union ConstValueUnion{
    int iVal;
    long long i64Val;
    bool bVal;
    char cVal;
    char* sVal;
    float fVal;
    double dVal;
};

class ASTNode{
public:
    virtual Value *convertToCode() = 0;
    virtual ~ASTNode() = default;
};

class ExprNode: public ASTNode {

};

class StatNode: public ASTNode {
public:
//    void forward();
    void backward();
//    BasicBlock *afterBB{};
};

class Program: public StatNode {
public:
    Program(GlobalArea *globalArea, FuncDec *mainFunc): globalArea(globalArea), mainFunc(mainFunc) { }
    Value *convertToCode() override;

private:
    GlobalArea* globalArea;
    FuncDec *mainFunc;
};

class GlobalArea: public StatNode {
public:
    GlobalArea() = default;
    void addConstDec(ConstDecList *cd) {
        constDecList->insert(constDecList->end(), cd->begin(), cd->end());
    }
    void addVarDec(VarDecList *vd) {
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
    ConstDecList *constDecList;
    VarDecList *varDecList;
    FuncDecList *funcDecList;
    ClassDecList *classDecList;
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
        myInt.iVal = v;
    }
    SkyVarType getType() override {
        return SKY_INT;
    }
    ConstValueUnion getValue() override {
        return myInt;
    }
    ConstValue *operator-() override {
        return new SkyInt(-myInt.iVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion myInt{};
};

class SkyInt64 : public ConstValue {
public:
    explicit SkyInt64(long long v) {
        myInt64.i64Val = v;
    }
    SkyVarType getType() override {
        return SKY_INT_64;
    }
    ConstValueUnion getValue() override {
        return myInt64;
    }
    ConstValue *operator-() override {
        return new SkyInt64(-myInt64.i64Val);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion myInt64{};
};

class SkyDouble: public ConstValue {
public:
    explicit SkyDouble(double v) {
        myDouble.dVal = v;
    }
    SkyVarType getType() override {
        return SKY_DOUBLE;
    }
    ConstValueUnion getValue() override {
        return myDouble;
    }
    ConstValue *operator-() override {
        return new SkyDouble(-myDouble.dVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion myDouble{};
};

class SkyFloat: public ConstValue {
public:
    explicit SkyFloat(float v) {
        myFloat.fVal = v;
    }
    SkyVarType getType() override {
        return SKY_FLOAT;
    }
    ConstValueUnion getValue() override {
        return myFloat;
    }
    ConstValue *operator-() override {
        return new SkyDouble(-myFloat.fVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion myFloat{};
};

class SkyChar: public ConstValue {
public:
    explicit SkyChar(float v) {
        myChar.cVal = v;
    }
    SkyVarType getType() override {
        return SKY_CHAR;
    }
    ConstValueUnion getValue() override {
        return myChar;
    }
    ConstValue *operator-() override {
        return new SkyDouble(-myChar.cVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion myChar{};
};

class SkyString: public ConstValue {
public:
    explicit SkyString(string v) {
        myString.sVal = (char*)v.c_str();
    }
    SkyVarType getType() override {
        return SKY_STRING;
    }
    ConstValueUnion getValue() override {
        return myString;
    }
    Value *convertToCode() override;

private:
    ConstValueUnion myString{};
};

class SkyBool: public ConstValue {
public:
    explicit SkyBool(bool v) {
        myBool.bVal = v;
    }
    SkyVarType getType() override {
        return SKY_BOOL;
    }
    ConstValueUnion getValue() override {
        return myBool;
    }
    ConstValue *operator-() override {
        return new SkyBool(!myBool.bVal);
    }
    Value *convertToCode() override;

private:
    ConstValueUnion myBool{};
};

class SkyArrayType: public StatNode {
public:
    SkyArrayType(SkyType *type, int size): myType(type), size(size) { }
    Value *convertToCode() override;

private:
    SkyType *myType;
    int size;
};

class SkyType: public StatNode {
public:
    explicit SkyType(SkyArrayType *arrayType): arrayType(arrayType), myType(SKY_ARRAY) { }
    explicit SkyType(SkyVarType varType): varType(varType), myType(SKY_VAR) { }
    SkyType(): myType(SKY_VOID) { }
    Value *convertToCode() override;
//    Type* toLLVMType();
//    Constant* initValue(ConstValue *v = nullptr);

    SkyArrayType *arrayType{};
    SkyVarType varType;
    SkyTypes myType;
private:
};

class Identifier: public ExprNode {
public:
    explicit Identifier(string name): myIdName(name) { }
    string getName() {
        return myIdName;
    }
    Value *convertToCode() override;

private:
    string myIdName;
};

class VarDec: public StatNode {
public:
    VarDec(Identifier *id, SkyType *type): myId(id), myType(type) { }
    Value *convertToCode() override;

    Identifier *myId;
    SkyType *myType;
};

class ConstDec: public StatNode {
public:
    ConstDec(Identifier *id, ConstValue *cv): myId(id), myValue(cv) { }
    Value *convertToCode() override;

private:
    Identifier *myId;
    ConstValue *myValue;
    SkyType *myType{};
};

class TypeDec: public StatNode {
public:
    TypeDec(Identifier *id, SkyType *type): myId(id), myType(type) { }

private:
    Identifier *myId;
    SkyType *myType;
};

class FuncDec: public StatNode {
public:
    FuncDec(Identifier *name, VarDecList *paraList, SkyType *returnType, CompoundStat *funcBody): myId(name), myParaList(paraList), myRetType(returnType), myBody(funcBody) { }
    FuncDec(Identifier *name, VarDecList *paraList, CompoundStat *funcBody): myId(name), myParaList(paraList), myBody(funcBody) {
        myRetType = new SkyType();
    }
    Value *convertToCode() override;

private:
    Identifier *myId;
    VarDecList *myParaList;
    SkyType *myRetType;
    CompoundStat *myBody;
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
    Identifier *name, *father;
    ClassBody *body;
};

class AssignStat: public StatNode {
public:
    AssignStat(Identifier *id, ExprNode *expr): targetId(id), expr(expr), type(ID_ASSIGN) { }
    AssignStat(Identifier *id, ExprNode *subInd, ExprNode *expr): targetId(id), subInd(subInd), expr(expr), type(ARRAY_ASSIGN) { }
    AssignStat(Identifier *id, Identifier *cid, ExprNode *expr): targetId(id), childId(cid), expr(expr), type(CLASS_ASSIGN) { }

private:
    Identifier *targetId, *childId;
    ExprNode *expr, *subInd;
    AssignType type;
};

class PrintStat: public StatNode {
public:
    explicit PrintStat(ExprList *exprList): exprList(exprList) { }

private:
    ExprList *exprList;
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
    StatNode *body;
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
    CompoundStat(StatList *statList): statList(statList) { }

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

#endif
