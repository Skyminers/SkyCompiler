//
// Created by 刘一辰 on 2021/5/20.
//

#include "nodeList.h"
#include "convertEngine.h"
#include "CompileException.h"

extern ConvertEngine engine;

llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, llvm::StringRef VarName, llvm::Type* type) {
    llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(type, nullptr, VarName);
}

Value * Program::convertToCode() {
    this->globalArea->convertToCode();
    return this->mainFunc->convertToCode();
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
        return new GlobalVariable(*engine.getModule(), type->toLLVMType(), true, GlobalValue::ExternalLinkage, value->create(), id->name);
    } else {
        auto mem = CreateEntryBlockAlloca(engine.nowFunction(), id->name, type->toLLVMType());
        return builder.CreateStore(value->convertToCode(), mem);
    }
}



Constant* ConstValue::create() {
    switch(getType()) {
        case SKY_INT:
            return builder.getInt32(getValue().iVal);
        case SKY_BOOL:
            return builder.getInt1(getValue().bVal);
        case SKY_CHAR:
            return builder.getInt8(getValue().cVal);
        case SKY_CHAR_POINTER: {
            char *p = getValue().sVal;
            int siz = (int)strlen(p);
            vector<Constant *> vec;
            for (int i = 0; i < siz; ++i) {
                vec.push_back(builder.getInt8(*(p + i)));
            }
            auto arrType = ArrayType::get(builder.getInt8Ty(), siz);
            return ConstantArray::get(arrType, vec);
        }
        case SKY_FLOAT:
            return ConstantFP::get(builder.getFloatTy(), getValue().fVal);
        case SKY_DOUBLE:
            return ConstantFP::get(builder.getDoubleTy(), getValue().dVal);
        default:
            throw CompileException("fuck");

    }
    return nullptr;
}

Value * FuncDec::convertToCode() {
    vector<Type*> args;
    for (auto &it: *paraList) {
        args.push_back(it->type->toLLVMType());
    }
    auto funcType = FunctionType::get(retType->toLLVMType(), args, false);
    auto func = Function::Create(funcType, GlobalValue::ExternalLinkage, id->name, engine.getModule());
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
        return ArrayType::get(arrayType->type->toLLVMType(), arrayType->size);
    } else return llvm::Type::getVoidTy(context);
}

Value *SkyType::convertToCode() {
    return nullptr;
}

Value *Identifier::convertToCode() {
    auto value = engine.findVarByName(name);
    return new LoadInst(value->getType(), value, "tmp", false, builder.GetInsertBlock());
}
