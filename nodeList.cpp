//
// Created by 刘一辰 on 2021/5/20.
//

#include "nodeList.h"
#include "convertEngine.h"
#include "CompileException.h"
#include <iostream>

extern ConvertEngine engine;

void printLog(string str) {
    cout << "[Log] " << str << endl;
}

void printError(string str) {
    cerr << "[Error] " << str << endl;
}

AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, llvm::StringRef VarName, llvm::Type* type) {
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(type, nullptr, VarName);
}

Value *calcOp(Value* left, Value* right, BinaryOperators op) {
    auto type1 = left->getType();
    auto type2 = right->getType();
    bool floatFlag = type1->isFloatTy() || type2->isFloatTy();
    bool doubleFlag = type1->isDoubleTy() || type2->isDoubleTy();
    switch (op) {
        case OP_PLUS:
            if (floatFlag || doubleFlag) {
                return builder.CreateFAdd(builder.CreateTrunc(left, builder.getDoubleTy(), "Convert"),
                                          builder.CreateTrunc(right, builder.getDoubleTy(), "Convert"), "addFloat");
            } else {
                return builder.CreateAdd(left, right, "addInt");
            }
        case OP_MINUS:
            if (floatFlag || doubleFlag) {
                return builder.CreateFSub(builder.CreateTrunc(left, builder.getDoubleTy(), "Convert"),
                                          builder.CreateTrunc(right, builder.getDoubleTy(), "Convert"), "subFloat");
            } else {
                return builder.CreateSub(left, right, "subInt");
            }
        case OP_MUL:
            if (floatFlag || doubleFlag) {
                return builder.CreateFMul(builder.CreateTrunc(left, builder.getDoubleTy(), "Convert"),
                                          builder.CreateTrunc(right, builder.getDoubleTy(), "Convert"), "mulFloat");
            } else {
                return builder.CreateMul(left, right, "mulInt");
            }
        case OP_DIV:
            if (floatFlag || doubleFlag) {
                return builder.CreateFDiv(builder.CreateTrunc(left, builder.getDoubleTy(), "Convert"),
                                          builder.CreateTrunc(right, builder.getDoubleTy(), "Convert"), "divSigned");
            } else {
                return builder.CreateSDiv(left, right, "divFloat");
            }
        case OP_EQ:
            return builder.CreateICmpEQ(left, right, "equal");
        case OP_NE:
            return builder.CreateICmpNE(left, right, "neq");
        case OP_GT:
            return builder.CreateICmpSGT(left, right, "gt");
        case OP_LT:
            return builder.CreateICmpSLT(left, right, "lt");
        case OP_GE:
            return builder.CreateICmpSGE(left, right, "ge");
        case OP_LE:
            return builder.CreateICmpSLE(left, right, "le");
        case OP_AND:
            return builder.CreateAnd(left, right, "and");
        case OP_OR:
            return builder.CreateOr(left, right, "or");
        case OP_XOR:
            return builder.CreateXor(left, right, "xor");
        case OP_MOD:
            return builder.CreateSRem(left, right, "mod");
        case OP_LEFT:
            return builder.CreateShl(left, right, "shl");
        case OP_RIGHT:
            return builder.CreateAShr(left, right, "shr");
        case OP_PTR:
            return nullptr;
    }

}

Value * Program::convertToCode() {
    puts("Entered convert");
    if (globalArea == nullptr) {
        printError( "globalArea pointer is nullptr");
        return nullptr;
    }
    this->globalArea->convertToCode();

    if (mainFunc == nullptr) {
        printError( "No main function found.");
        return nullptr;
    }
    return this->mainFunc->convertToCode();
}

Value * GlobalArea:: convertToCode() {
    if (constDecList != nullptr) {
        printLog("Construct const declaration");
        for (auto &it: *constDecList) {
            it->convertToCode();
        }
    }
    if (varDecList != nullptr) {
        printLog("Construct var declaration");
        for (auto &it: *varDecList) {
            it->convertToCode();
        }
    }
    if (funcDecList != nullptr) {
        printLog("Construct function declaration");
        for (auto &it: *funcDecList) {
            it->convertToCode();
        }
    }
//    for(auto &it: *classDecList){
//        it->convertToCode();
//    }
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

Value *SkyInt::convertToCode() {
    return builder.getInt32(value.iVal);
}

Value *SkyDouble::convertToCode() {
    return ConstantFP::get(builder.getDoubleTy(), value.dVal);
}

Value *SkyFloat::convertToCode() {
    return ConstantFP::get(builder.getFloatTy(), value.iVal);
}

Value *SkyChar::convertToCode() {
    return builder.getInt8(value.cVal);
}

Value *SkyBool::convertToCode() {
    return builder.getInt1(value.bVal);
}

Value *SkyCharPointer::convertToCode() {
    char *p = value.sVal;
    int siz = (int)strlen(p);
    vector<Constant *> vec;
    vec.resize(siz);
    for (int i = 0; i < siz; ++i) {
        vec[i] = builder.getInt8(*(p + i));
    }
    auto arrType = ArrayType::get(builder.getInt8Ty(), siz);
    return ConstantArray::get(arrType, vec);
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
            vec.resize(siz);
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
}

Value *VarDec::convertToCode() {
    if (type->type == SKY_ARRAY) {
        engine.arrayMap[id->name] = type->arrayType;
    }
    auto varType = type->toLLVMType();
    if(isGlobal()) {
        return new GlobalVariable(*engine.getModule(), varType, false, GlobalValue::ExternalLinkage, type->Create(), id->name);
    } else {
        return CreateEntryBlockAlloca(engine.nowFunction(), id->name, varType);
    }
    return nullptr;
}

Constant* SkyType::Create() {
    if(type == SKY_VAR) {
        switch (*varType) {
            case SKY_INT: // All default : 0
                return builder.getInt32(0);
            case SKY_INT_64:
                return builder.getInt64(0);
            case SKY_CHAR:
                return builder.getInt8(0);
            case SKY_FLOAT:
                return ConstantFP::get(builder.getFloatTy(), .0);
            case SKY_DOUBLE:
                return ConstantFP::get(builder.getDoubleTy(), .0);
            case SKY_BOOL:
                return builder.getInt1(false);
            case SKY_INT_POINTER:
            case SKY_INT_64_POINTER:
            case SKY_CHAR_POINTER:
            case SKY_FLOAT_POINTER:
            case SKY_DOUBLE_POINTER:
            case SKY_BOOL_POINTER:
                return builder.getInt32(0);
        }
    } else if(type == SKY_ARRAY) {
        int siz = arrayType->size;
        vector<Constant *> vec;
        vec.resize(siz);
        for (int i = 0; i < siz; ++i) {
            vec[i] = arrayType->type->Create();
        }
        auto arrType = ArrayType::get(toLLVMType(), siz);
        return ConstantArray::get(arrType, vec);
    }
}

Value * FuncDec::convertToCode() {
    vector<Type*> args;
    if (paraList != nullptr) {
        for (auto &it: *paraList) {
            args.push_back(it->type->toLLVMType());
        }
    }
    auto funcType = FunctionType::get(retType->toLLVMType(), args, false);
    auto func = Function::Create(funcType, GlobalValue::ExternalLinkage, id->name, engine.getModule());
    engine.enterFunction(func);
    BasicBlock *funcBlock = BasicBlock::Create(context, "function begin", func, nullptr);
    builder.SetInsertPoint(funcBlock);

    // calc params
    auto iterToPara = func->arg_begin();
    if (paraList != nullptr) {
        for (auto &it: *paraList) {
            auto mem = CreateEntryBlockAlloca(func, it->id->name, it->type->toLLVMType());
            builder.CreateStore(iterToPara++, mem);
        }
    }
    Value * ret = nullptr;
    if ( retType->type != SkyTypes::SKY_VOID ){
        ret = CreateEntryBlockAlloca(func, id->name, retType->toLLVMType());
    }

    body->convertToCode();

    engine.exitFunction();
    if (engine.funcStackSize()) {
        auto nowFunc = engine.nowFunction();
        builder.SetInsertPoint(&(nowFunc->getBasicBlockList().back()));
    }
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


Value *Identifier::convertToCode() {
    auto value = engine.findVarByName(name);
    return new LoadInst(value->getType()->getPointerElementType(), value, AMAZING_NAME, false, builder.GetInsertBlock());
}

Value *CompoundStat::convertToCode() {
    for (auto it : *statList) {
        it->convertToCode();
    }
    return nullptr;
}

Value *AssignStat::convertToCode() {
    Value *res = nullptr;
    switch (type) {
        case ID_ASSIGN:
            return builder.CreateStore(expr->convertToCode(), engine.findVarByName(id->name));
        case ARRAY_ASSIGN:
            return builder.CreateStore(expr->convertToCode(), arrayRef->getValueI());
    }
    return nullptr;
}

Value *BinaryExpr::convertToCode() {
    auto leftValue = this->left->convertToCode();
    auto rightValue = this->right->convertToCode();
    return calcOp(leftValue, rightValue, op);
}

Value *ArrayReference::convertToCode() {
    return builder.CreateLoad(getValueI(), "arrReference");
}

Value *ArrayReference::getValueI() {
    auto arr = engine.findVarByName(id->name);
    auto index = subInd->convertToCode();
    vector<Value*> valueVec;
    valueVec.push_back(builder.getInt32(0));
    valueVec.push_back(index);
    return builder.CreateInBoundsGEP(arr, ArrayRef<Value *>(valueVec));
}

Value *FuncCall::convertToCode() {
    auto func = engine.getModule()->getFunction(id->name);
    if (func == nullptr) {
        throw FuncNotFound(*(new string(id->name)) + " not found");
    }
    if (strcmp(id->name, "printf") == 0 || strcmp(id->name, "scanf") == 0) {
        return callSysIO();
    }
    vector<Value*> inputArgs;
    auto funcNeed = func->arg_begin();
    for (auto & it : *args) {
        if (funcNeed->hasNonNullAttr()) {
            auto * addr = engine.findVarByName(dynamic_cast<Identifier*>(it)->name);
            inputArgs.push_back(addr);
        } else {
            inputArgs.push_back(it->convertToCode());
        }
        funcNeed ++;
    }
    Value *ret = builder.CreateCall(func, inputArgs, "callFunc");
    return ret;
}

Value *IfStat::convertToCode() {

    Value *condValue = condExpr->convertToCode();
    condValue = builder.CreateICmpNE(condValue, ConstantInt::get(Type::getInt1Ty(context), 0, true), "if");

    auto func = engine.nowFunction();
    auto thenCond = BasicBlock::Create(context, "thenCond", func);
    auto elseCond = BasicBlock::Create(context, "elseCond", func);
    auto common = BasicBlock::Create(context, "common", func);

    // then
    auto branch = builder.CreateCondBr(condValue, thenCond, elseCond);
    builder.SetInsertPoint(thenCond);

    engine.flagIsReturn = false;
    thenStat->convertToCode();
    if (!engine.flagIsReturn) {
        builder.CreateBr(common);
    }
    engine.flagIsReturn = false;
    thenCond = builder.GetInsertBlock();

    // else
    builder.SetInsertPoint(elseCond);

    engine.flagIsReturn = false;
    if (elseStat != nullptr) {
        elseStat->convertToCode();
    }
    if (!engine.flagIsReturn) {
        builder.CreateBr(common);
    }
    engine.flagIsReturn = false;
    elseCond = builder.GetInsertBlock();

    builder.SetInsertPoint(common);
    return branch;
}

Value *ForStat::convertToCode() {
    auto func = engine.nowFunction();

    Value * startValue = start->convertToCode();
    Value * endValue = end->convertToCode();
    Value * stepValue = step->convertToCode();

    Value * varValue = engine.findVarByName(forVar->name);
    builder.CreateStore(startValue, varValue);

    BasicBlock *condition = BasicBlock::Create(context, "condition", func);
    BasicBlock *loop = BasicBlock::Create(context, "loopCode", func);
    BasicBlock *breakLoop = BasicBlock::Create(context, "breakLoop", func);
    engine.enterLoop(breakLoop, condition);

    // condition
    builder.CreateBr(condition);
    builder.SetInsertPoint(condition);
    auto nowValue = forVar->convertToCode();
    auto condValue = builder.CreateICmpSLT(nowValue, endValue);
    condValue = builder.CreateICmpNE(condValue, ConstantInt::get(Type::getInt1Ty(context), 0, true));
    auto branch = builder.CreateCondBr(condValue, loop, breakLoop);
    condition = builder.GetInsertBlock();

    // loop
    builder.SetInsertPoint(loop);
    engine.flagIsReturn = false;
    body->convertToCode();
    Value * newVarValue = builder.CreateAdd(nowValue, stepValue); // add step
    builder.CreateStore(newVarValue, varValue);
    if (!engine.flagIsReturn) {
        builder.CreateBr(condition);
    }
    engine.flagIsReturn = false;
    loop = builder.GetInsertBlock();

    builder.SetInsertPoint(breakLoop);
    engine.exitLoop();
    return branch;
}

Value *WhileStat::convertToCode() {
    auto func = engine.nowFunction();
    BasicBlock * condition = BasicBlock::Create(context, "condition", func);
    BasicBlock * loop = BasicBlock::Create(context, "loop", func);
    BasicBlock * breakLoop = BasicBlock::Create(context, "breakLoop", func);
    engine.enterLoop(breakLoop, condition);

    // condition
    builder.CreateBr(condition);
    builder.SetInsertPoint(condition);
    auto condValue = cond->convertToCode();
    condValue = builder.CreateICmpNE(condValue, ConstantInt::get(Type::getInt1Ty(context), 0, true));
    auto branch = builder.CreateCondBr(condValue, loop, breakLoop);
    condition = builder.GetInsertBlock();

    // loop
    builder.SetInsertPoint(loop);
    engine.flagIsReturn = false;
    body->convertToCode();
    if (!engine.flagIsReturn) {
        builder.CreateBr(condition);
    }
    engine.flagIsReturn = false;

    builder.SetInsertPoint(breakLoop);
    engine.exitLoop();
    return branch;
}

Value *JumpStat::convertToCode() {
    engine.flagIsReturn = true;
    switch ( type ) {
        case BREAK:
            return builder.CreateBr(engine.getCurBreakBlock());
        case CONTINUE:
            return builder.CreateBr(engine.getCurContinueBlock());
        case RETURN:
            if (retExpr != nullptr) {
                return builder.CreateRet(retExpr->convertToCode());
            } else {
                return builder.CreateRetVoid();
            }
    }
    return nullptr;
}

Value *ReferenceNode::convertToCode() {
    if (id != nullptr) return engine.findVarByName(id->name);
    else return arrayRef->getValueI();
}

Value * PointerNode::convertToCode() {
    return nullptr;
}

Value * SkyArrayType::convertToCode() {
    return nullptr;
}

Value * SkyType::convertToCode() {
    return nullptr;
}

Value * FuncCall::callSysIO() {
    auto func = engine.getModule()->getFunction(id->name);

    vector<Value*> inputArgs;
    auto funcNeed = func->arg_begin();
    bool flag = false;
    for (auto & it : *args) {
        if (!flag) {
            char* p = dynamic_cast<SkyCharPointer*>(it)->getValue().sVal;
            for (int i = 0; ; ++ i) {
                if ( *(p+i) == '\0' ) break;
                if( *(p+i) == '@' ) *(p+i) = '\n';
            }
            auto formatConst = llvm::ConstantDataArray::getString(context, p);
            auto formatStrVar = new llvm::GlobalVariable(*(engine.getModule()), llvm::ArrayType::get(builder.getInt8Ty(), strlen(p) + 1), true, llvm::GlobalValue::ExternalLinkage, formatConst, "printfStr");
            auto zero = llvm::Constant::getNullValue(builder.getInt32Ty());
            Constant* indices[] = {zero, zero};
            auto ptr = ConstantExpr::getGetElementPtr(formatStrVar->getType()->getElementType(), formatStrVar, indices);
            inputArgs.push_back(ptr);
            flag = true;
            funcNeed ++;
            continue;
        }
        inputArgs.push_back(it->convertToCode());
    }
    Value *ret = builder.CreateCall(func, inputArgs, "callFunc");
    return ret;
}

Value * VarDecListNode::convertToCode() {
    for (auto &it : *varDecList) {
        it->convertToCode();
    }
}

Value * ConstDecListNode::convertToCode() {
    for (auto &it : *constDecList) {
        it->convertToCode();
    }
}