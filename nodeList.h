//
// Created by 刘一辰 on 2021/5/20.
//

#ifndef NODELIST_H
#define NODELIST_H

#include "llvm/IR/Value.h"
#include "defineList.h"
#include <iostream>

using namespace llvm;
using namespace std;

class SkyType;
class Identifier;

typedef vector<Identifier*> IdentifierList;

enum SkyDataType {
    SKY_INT,
    SKY_STRING,
    SKY_BOOL,
//    SKY_INT64,
    SKY_DOUBLE,
//    SKY_FLOAT
};

enum SkyTypes {
    SKY_ARRAY,
    SKY_RANGE,
    SKY_VOID,
//    SKY_ENUM,
//    SKY_RECORD,
//    SKY_ENUM_RANGE,
//    SKY_USER_DEFINE,
//    SKY_BUILT_IN
};

union ConstValueUnion{
    int iVal;
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

class Program: public ASTNode {
public:
    Program() = default;
    Value *convertToCode() override;

private:

};

class ExprNode: public ASTNode {

};

class StatNode: public ASTNode {
public:
//    void forward();
//    void backword();
//    BasicBlock *afterBB{};
};

class ListNode: public ASTNode {

};

class ConstValue: public ExprNode{
public:
    Value *convertToCode() override;
    virtual SkyDataType getType() = 0;
    virtual ConstValueUnion getValue() = 0;
    virtual ConstValue *operator-() = 0;
};

class SkyInt : public ConstValue {
public:
    explicit SkyInt(int v) {
        myInt.iVal = v;
    }
    SkyDataType getType() override {
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

class SkyDouble: public ConstValue {
public:
    explicit SkyDouble(double v) {
        myDouble.dVal = v;
    }
    SkyDataType getType() override {
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
    SkyDataType getType() override {
        return SKY_DOUBLE;
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
    SkyDataType getType() override {
        return SKY_DOUBLE;
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
    explicit SkyString(char* v) {
        myString.sVal = new char[strlen(v) + 1];
        strcpy(myString.sVal, v);
    }
    ~SkyString() override {
        delete[] myString.sVal;
    }
    SkyDataType getType() override {
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
    SkyDataType getType() override {
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

class ConstValueDeclaration: public StatNode {
public:

private:

};

class SkyArrayType: public StatNode {
public:
    SkyArrayType(SkyType *type, SkyType *range): myType(type), myRange(range) { }
    Value *convertToCode() override;

private:
    SkyType *myType, *myRange;
};

class SkyRangeType: public StatNode {
public:
    SkyRangeType(ConstValue *left, ConstValue *right): left(left), right(right) { }
    Value *convertToCode() override;
    Value *mapIndex();
    size_t size() {
        int countSize = 0;
        if (left->getType() == SKY_INT && left->getType() == right->getType()) {
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
    SkyType(): myType(SKY_VOID) { }
    Value *convertToCode() override;
//    Type* toLLVMType();
//    Constant* initValue(ConstValue *v = nullptr);

private:
    SkyArrayType *arrayType{};
    SkyRangeType *rangeType{};
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
    VarDec(IdentifierList *idList, SkyType *type): myIdList(idList), myType(type) { }
    Value *convertToCode() override;


private:
    IdentifierList *myIdList;
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
    FuncDec(Identifier *funcName)
};

class Parameter: public StatNode {
public:
    Parameter(IdentifierList *idList, bool )
};

#endif
