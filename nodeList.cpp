//
// Created by 刘一辰 on 2021/5/20.
//

#include "nodeList.h"
#include "convertEngine.h"

extern ConvertEngine engine;

llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, llvm::StringRef VarName, llvm::Type* type) {
    llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(type, nullptr, VarName);
}

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

Value * ConstDec::convertToCode() {
    if ( isGlobal() ) {
        return new GlobalVariable(*engine.getModule(), value->getType(), true, GlobalValue::ExternalLinkage, value->getValue())
    }
    return nullptr;
}

Value *ConstValue::convertToCode() {
    switch(getType()) {
        case SKY_INT:
            return builder.getInt32(getValue().iVal);
        case SKY_BOOL:
            return builder.getInt1(getValue().bVal);
        case SKY_CHAR:
            return builder.getInt8(getValue().cVal);
        case SKY_CHAR_POINTER:

    }
    return nullptr;
}

Value * FuncDec::convertToCode() {
    vector<Type*> args;
    for (auto &it: *paraList) {
        args.push_back(it->type->toLLVMType());
    }
    auto funcType = FunctionType::get(retType->toLLVMType(), args, false);
    auto func = Function::Create(funcType, GlobalValue::ExternalLinkage, id->getName(), engine.getModule());
    engine.enterFunction(func);
    BasicBlock *funcBlock = BasicBlock::Create(context, "function begin", func, nullptr);
    builder.SetInsertPoint(funcBlock);

    // calc params
    auto iterToPara = func->arg_begin();
    for (auto &it: *paraList) {
        auto mem = CreateEntryBlockAlloca(func, it->id->name, it->type->toLLVMType());
        builder.CreateStore(iterToPara++,  mem);
    }
    Value * ret = nullptr;
    if ( retType->type != SkyTypes::SKY_VOID ){
        ret = CreateEntryBlockAlloca(func, id->name, retType->toLLVMType());
    }

    body->convertToCode();

    if ( retType->type != SkyTypes::SKY_VOID ) {
        auto retValue = id->convertToCode();
        builder.CreateRet(retValue);
    } else {
        builder.CreateRetVoid();
    }

    engine.exitFunction();
    builder.SetInsertPoint(&(engine.nowFunction())->getBasicBlockList().back());
    return func;
}

Type * SkyType::toLLVMType() {
    if(type == SKY_VAR) {
        switch (*varType) {
            case SkyVarType::SKY_INT:
                return llvm::Type::getInt32Ty(context);
            case SkyVarType::SKY_INT_64:
                return llvm::Type::getInt64Ty(context);
            case SkyVarType::SKY_CHAR:
                return llvm::Type::getInt8Ty(context);
            case SkyVarType::SKY_FLOAT:
                return llvm::Type::getFloatTy(context);
            case SkyVarType::SKY_DOUBLE:
                return llvm::Type::getDoubleTy(context);
            case SkyVarType::SKY_BOOL:
                return llvm::Type::getInt1Ty(context);
            case SkyVarType::SKY_INT_POINTER:
                return llvm::Type::getInt32PtrTy(context);
            case SkyVarType::SKY_CHAR_POINTER:
                return llvm::Type::getInt8PtrTy(context);
            case SkyVarType::SKY_INT_64_POINTER:
                return llvm::Type::getInt64PtrTy(context);
            case SkyVarType::SKY_FLOAT_POINTER:
                return llvm::Type::getFloatPtrTy(context);
            case SkyVarType::SKY_DOUBLE_POINTER:
                return llvm::Type::getDoublePtrTy(context);
            case SkyVarType::SKY_BOOL_POINTER:
                return llvm::Type::getInt1PtrTy(context);
        }
    } else if (type == SKY_ARRAY) {
        ArrayType::get(arrayType->type->toLLVMType(), arrayType->size);
    }
}

Value *SkyType::convertToCode() {
    return nullptr;
}

Value *Identifier::convertToCode() {
    return new LoadInst(engine.findVarByName(name), "tmp", false, builder.GetInsertBlock());
}
