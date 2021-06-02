//
// Created by 刘一辰 on 2021/5/20.
//

#include "nodeList.h"
#include "convertEngine.h"

extern ConvertEngine engine;

Value * Program::convertToCode() {
    engine.createMainFunction();
    auto mainFunc = engine.getMain();
    auto mainBlock = BasicBlock::Create(context, "main", mainFunc);
    engine.enterFunction(mainFunc);
    builder.SetInsertPoint(mainBlock);
    this->globalArea->convertToCode();
    this->mainFunc->convertToCode();
    builder.CreateRet(builder.getInt32(1));
    return nullptr;
}

Value * GlobalArea::convertToCode() {
    for(auto &it: *constDecList){
        it->convertToCode();
    }
    for(auto &it: *varDecList){
        it->convertToCode();
    }
    for(auto &it: *funcDecList){
        it->convertToCode();
    }
    for(auto &it: *classDecList){
        it->convertToCode();
    }
    return nullptr;
}

Value * Identifier::convertToCode() {

    return nullptr;
}

Value * ConstDec::convertToCode() {

    return nullptr;
}

Value * FuncDec::convertToCode() {
    vector<Type*> args;
    for (auto &it: *paraList) {
        args.push_back(it->type->toLLVMType());
    }
    return nullptr;
}

Type * SkyType::toLLVMType() {
    switch (*varType) {
        case SkyVarType::SKY_INT: return llvm::Type::getInt32Ty(context);
        case SkyVarType::SKY_INT_64: return llvm::Type::getInt64Ty(context);
        case SkyVarType::SKY_CHAR: return llvm::Type::getInt8Ty(context);
        case SkyVarType::SKY_FLOAT: return llvm::Type::getFloatTy(context);
        case SkyVarType::SKY_DOUBLE: return llvm::Type::getDoubleTy(context);
        case SkyVarType::SKY_BOOL: return llvm::Type::getInt1Ty(context);
        case SkyVarType::SKY_INT_POINTER: return llvm::Type::getInt32PtrTy(context);
        case SkyVarType::SKY_CHAR_POINTER: return llvm::Type::getInt8PtrTy(context);
        case SkyVarType::SKY_INT_64_POINTER: return llvm::Type::getInt64PtrTy(context);
        case SkyVarType::SKY_FLOAT_POINTER: return llvm::Type::getFloatPtrTy(context);
        case SkyVarType::SKY_DOUBLE_POINTER: return llvm::Type::getDoublePtrTy(context);
        case SkyVarType::SKY_BOOL_POINTER: return llvm::Type::getInt1PtrTy(context);

    }
}