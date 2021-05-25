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
    char* cVal;
    double dVal;
};

class ASTNode{
public:
    virtual Value convertToCode() = 0;
    virtual ~ASTNode() = default;
};

class Expression: ASTNode {

};

class Statement: public ASTNode{
public:
//    void forward();
//    void backword();
//    BasicBlock *afterBB{};
};

class ConstValue: public Statement{
public:
    Value convertToCode() override;
    virtual SkyDataType getType() = 0;
    virtual ConstValueUnion getValue() = 0;
    virtual ConstValue *operator-() = 0;
//    virtual bool isValidRange() {
//        SkyDataType myType = getType();
//        return myType == SKY_INT;
//    }
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
    Value convertToCode() override;

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
    Value convertToCode() override;

private:
    ConstValueUnion myDouble{};
};

class SkyString: public ConstValue {
public:
    explicit SkyString(char* v) {
        myString.cVal = new char[strlen(v) + 1];
        strcpy(myString.cVal, v);
    }
    ~SkyString() override {
        delete[] myString.cVal;
    }
    SkyDataType getType() override {
        return SKY_STRING;
    }
    ConstValueUnion getValue() override {
        return myString;
    }
    Value convertToCode() override;

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
    Value convertToCode() override;

private:
    ConstValueUnion myBool{};
};

class ConstValueDeclaration: public Statement {
public:

private:

};

class SkyArrayType: public Statement {
public:
    SkyArrayType(SkyType *type, SkyType *range): myType(type), myRange(range) { }
    Value convertToCode() override;

private:
    SkyType *myType, *myRange;
};

class SkyRangeType: public Statement {
public:
    SkyRangeType(ConstValue *left, ConstValue *right): left(left), right(right) { }
    Value convertToCode() override;
    size_t size() {
        int countSize = 0;

        return countSize;
    }

private:
    ConstValue *left, *right;
};

class SkyType: public Statement {
public:
    explicit SkyType(SkyArrayType *arrayType): arrayType(arrayType), myType(SKY_ARRAY) { }
    explicit SkyType(SkyRangeType *rangeType): rangeType(rangeType), myType(SKY_RANGE) { }
    SkyType(): myType(SKY_VOID) { }
    Value convertToCode() override;
//    Type* toLLVMType();
//    Constant* initValue(ConstValue *v = nullptr);

private:
    SkyArrayType *arrayType{};
    SkyRangeType *rangeType{};
    SkyTypes myType;
};

#endif
