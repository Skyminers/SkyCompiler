//
// Created by 刘一辰 on 2021/5/20.
//

#include "nodeList.h"
#include "convertEngine.h"

Value* ASTNode::convertToCode() {
    return nullptr;
}

Value* ConstValue::convertToCode() {
    return nullptr;
}

Value* SkyInt::convertToCode() {
    return nullptr;
}

Value* SkyDouble::convertToCode() {
    return nullptr;
}

Value *SkyFloat::convertToCode() {
    return ConstValue::convertToCode();
}

Value *SkyChar::convertToCode() {
    return ConstValue::convertToCode();
}


Value* SkyString::convertToCode() {
    return nullptr;
}

Value* SkyBool::convertToCode() {
    return nullptr;
}

Value* SkyType::convertToCode() {
    return nullptr;
}

Value* SkyArrayType::convertToCode() {
    return nullptr;
}

Value* SkyRangeType::convertToCode() {
    return nullptr;
}

Value *SkyRangeType::mapIndex() {
    return nullptr;
}

Value *Identifier::convertToCode() {
    return nullptr;
}

Value *VarDec::convertToCode() {
    return nullptr;
}

Value *ConstDec::convertToCode() {
    return nullptr;
}

Value *Parameter::convertToCode() {
    return nullptr;
}

Value *FuncDec::convertToCode() {
    return nullptr;
}

Value *Program::convertToCode() {
    return nullptr;
}
