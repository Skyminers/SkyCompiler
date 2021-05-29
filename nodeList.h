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
class Parameter;
class StatNode;
class CompoundStat;
class FuncDec;
class ConstDec;
class VarDec;
class GlobalArea;

typedef vector<Identifier*> IdentifierList;
typedef vector<Parameter*>  ParaList;
typedef vector<StatNode*>   StatList;
typedef vector<FuncDec*>    FuncDecList;
typedef vector<ConstDec*>   ConstDecList;
typedef vector<VarDec*>     VarDecList;


enum SkyVarType {
    TYPE_INT,
    TYPE_INT_POINTER,
    TYPE_INT_64,
    TYPE_INT_64_POINTER,
    TYPE_CHAR,
    TYPE_CHAR_POINTER,
    TYPE_FLOAT,
    TYPE_FLOAT_POINTER,
    TYPE_DOUBLE,
    TYPE_DOUBLE_POINTER,
    TYPE_BOOL,
    TYPE_BOOL_POINTER
};

enum SkyTypes {
    SKY_ARRAY,
    SKY_RANGE,
    SKY_VOID,
    SKY_VAR,
//    SKY_ENUM,
//    SKY_RECORD,
//    SKY_ENUM_RANGE,
//    SKY_USER_DEFINE,
};

enum BinaryOperator {
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
    void backword();
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
    void addFuncDec(FuncDecList *fd) {
        funcDecList->insert(funcDecList->end(), fd->begin(), fd->end());
    }

private:
    ConstDecList *constDecList;
    VarDecList *varDecList;
    FuncDecList *funcDecList;
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
        return TYPE_INT;
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
        return TYPE_INT_64;
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
        return TYPE_DOUBLE;
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
        return TYPE_FLOAT;
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
        return TYPE_CHAR;
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

class SkyCharS: public ConstValue {
public:
    explicit SkyCharS(char* v) {
        myString.sVal = new char[strlen(v) + 1];
        strcpy(myString.sVal, v);
    }
    ~SkyCharS() override {
        delete[] myString.sVal;
    }
    SkyVarType getType() override {
        return TYPE_CHAR_POINTER;
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
        return TYPE_BOOL;
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

class SkyRangeType: public StatNode {
public:
    SkyRangeType(ConstValue *left, ConstValue *right): left(left), right(right) { }
    Value *convertToCode() override;
    Value *mapIndex();
    size_t size() {
        int countSize = 0;
        if (left->getType() == TYPE_INT && left->getType() == right->getType()) {
            countSize = right->getValue().iVal - left->getValue().iVal;
            if (countSize <= 0) {
                throw range_error("ERROR: left range > right range!");
            }
        } else {
            throw domain_error("ERROR: range type error!");
        }
        return countSize;
    }

private:
    ConstValue *left, *right;
};

class SkyType: public StatNode {
public:
    explicit SkyType(SkyArrayType *arrayType): arrayType(arrayType), myType(SKY_ARRAY) { }
    explicit SkyType(SkyRangeType *rangeType): rangeType(rangeType), myType(SKY_RANGE) { }
    explicit SkyType(SkyVarType varType): varType(varType), myType(SKY_VAR) { }
    SkyType(): myType(SKY_VOID) { }
    Value *convertToCode() override;
//    Type* toLLVMType();
//    Constant* initValue(ConstValue *v = nullptr);

private:
    SkyArrayType *arrayType{};
    SkyRangeType *rangeType{};
    SkyVarType varType;
    SkyTypes myType;
};

class Identifier: public ExprNode {
public:
    explicit Identifier(string *name): myIdName(name) { }
    string getName() {
        return *myIdName;
    }
    Value *convertToCode() override;

private:
    string *myIdName;
};

class VarDec: public StatNode {
public:
    VarDec(Identifier *id, SkyType *type): myId(id), myType(type) { }
    Value *convertToCode() override;


private:
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
    FuncDec(Identifier *name, ParaList *paraList, SkyType *returnType): myId(name), myParaList(paraList), myRetType(returnType) { }
    FuncDec(Identifier *name, ParaList *paraList): myId(name), myParaList(paraList) {
        myRetType = new SkyType();
    }
    Value *convertToCode() override;

private:
    Identifier *myId;
    ParaList *myParaList;
    SkyType *myRetType;
    CompoundStat *funcBody;
};

class Parameter: public StatNode {
public:
    Parameter(IdentifierList *idList, bool isVar): myIdList(idList), isVar(isVar) { }
    Value *convertToCode() override;

private:
    IdentifierList *myIdList;
    bool isVar;
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

class IfStat: public StatNode {
public:
    IfStat(ExprNode *condExpr, StatNode *thenStat, StatNode *elseStat): condExpr(condExpr), thenStat(thenStat), elseStat(elseStat) { }
    Value *convertToCode() override;

private:
    ExprNode *condExpr;
    StatNode *thenStat, *elseStat;
};

class ForStat: public StatNode {
public:
    ForStat(ExprNode *forInit, ExprNode *forCond, ExprNode *forStep, StatNode *forBody):
        forInit(forInit), forCond(forCond), forStep(forStep), forBody(forBody) { }

private:
    ExprNode *forInit, *forCond, *forStep;
    StatNode *forBody;
};

class WhileStat: public StatNode {
public:
    WhileStat(ExprNode *whileCond, StatNode *whileBody): whileCond(whileCond), whileBody(whileBody) { }

private:
    ExprNode *whileCond;
    StatNode *whileBody;
};

class CompoundStat: public StatNode {
public:
    CompoundStat(StatList *statList): statList(statList) { }

private:
    StatList *statList;
};

class BinaryExpr: public ExprNode {
public:
    BinaryExpr(ExprNode *left, BinaryOperator op, ExprNode *right): left(left), op(op), right(right) { }

private:
    ExprNode *left, *right;
    BinaryOperator op;
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

#endif
