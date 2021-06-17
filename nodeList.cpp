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

/*
 * Create a memory to alloca value in function.
 * */
AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, llvm::StringRef VarName, llvm::Type* type) {
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(type, nullptr, VarName);
}

/*
 * Binary operator function:
 * Support :
 *  add, sub, mul, div, equ, neq, LT, GT, LE, GE, and, or, xor, sl, rl
 *  Note: all params of binary operator need to be the same type
 * */
Value *calcOp(Value* left, Value* right, BinaryOperators op) {
    auto type1 = left->getType();
    auto type2 = right->getType();

    // check the float flag
    bool floatFlag = type1->isFloatTy() || type2->isFloatTy();
    bool doubleFlag = type1->isDoubleTy() || type2->isDoubleTy();
    switch (op) {
        case OP_PLUS:
            if (floatFlag || doubleFlag) {
                return builder.CreateFAdd(left, right, "addFloat");
            } else {
                return builder.CreateAdd(left, right, "addInt");
            }
        case OP_MINUS:
            if (floatFlag || doubleFlag) {
                return builder.CreateFSub(left, right, "subFloat");
            } else {
                return builder.CreateSub(left, right, "subInt");
            }
        case OP_MUL:
            if (floatFlag || doubleFlag) {
                return builder.CreateFMul(left, right, "mulFloat");
            } else {
                return builder.CreateMul(left, right, "mulInt");
            }
        case OP_DIV:
            if (floatFlag || doubleFlag) {
                return builder.CreateFDiv(left, right, "divSigned");
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

/*
 * Entrance of total AST tree
 * We begin to convert AST tree to LLVM-IR code from this node.
 * */
Value * Program::convertToCode() {
    puts("Entered convert");
    if (globalArea == nullptr) {
        printError( "globalArea pointer is nullptr");
        return nullptr;
    }

    // Global declaration : const, var, function [and class]
    this->globalArea->convertToCode();

    // We must have a main function as the beginning function
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
            it->convertToCode(); // const value for declaration
        }
    }
    if (varDecList != nullptr) {
        printLog("Construct var declaration");
        for (auto &it: *varDecList) {
            it->convertToCode(); // var value for declaration
        }
    }
    if (funcDecList != nullptr) {
        printLog("Construct function declaration");
        for (auto &it: *funcDecList) {
            it->convertToCode(); // func for declaration
        }
    }
    // TODO: Class type declaration
//    for(auto &it: *classDecList){
//        it->convertToCode();
//    }
    return nullptr;
}

/*
 * Convert const value to LLVM-IR code
 * */
Value * ConstDec::convertToCode() {
    if ( isGlobal() ) { // Global value should be declared in module (heap memory)
        return new GlobalVariable(*engine.getModule(), type->toLLVMType(), true, GlobalValue::ExternalLinkage, value->create(), id->name);
    } else { // Inner value should be declared in function (stack memory);
        auto mem = CreateEntryBlockAlloca(engine.nowFunction(), id->name, type->toLLVMType());
        return builder.CreateStore(value->convertToCode(), mem);
    }
}

// Return Int32 value
Value *SkyInt::convertToCode() {
    return builder.getInt32(value.iVal);
}

// Return Double value
Value *SkyDouble::convertToCode() {
    return ConstantFP::get(builder.getDoubleTy(), value.dVal);
}

// Return Float value
Value *SkyFloat::convertToCode() {
    return ConstantFP::get(builder.getFloatTy(), value.iVal);
}

// Return Char value
Value *SkyChar::convertToCode() {
    return builder.getInt8(value.cVal);
}

// Return Bool value
Value *SkyBool::convertToCode() {
    return builder.getInt1(value.bVal);
}

// Return Char* value (Actually is arrayType in LLVM)
Value *SkyCharPointer::convertToCode() {
    char *p = value.sVal;
    int siz = (int)strlen(p);
    vector<Constant *> vec;
    vec.resize(siz);
    for (int i = 0; i < siz; ++i) {
        vec[i] = builder.getInt8(*(p + i)); // get all default char value
    }
    auto arrType = ArrayType::get(builder.getInt8Ty(), siz);
    return ConstantArray::get(arrType, vec);
}

/*
 * Constant Create: create the constant value to use
 * Value is decidable because it is constant, so this function directly return the value of its type
 * */
Constant* ConstValue::create() {
    switch(getType()) {
        case SKY_INT:
            return builder.getInt32(getValue().iVal);
        case SKY_BOOL:
            return builder.getInt1(getValue().bVal);
        case SKY_CHAR:
            return builder.getInt8(getValue().cVal);
        case SKY_CHAR_POINTER: { // Pointer is a special type
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

// As same as constant declaration (with small difference)
Value *VarDec::convertToCode() {
    if (type->type == SKY_AUTO) {
        type->type = expr->type;
    }
    if (type->type == SKY_ARRAY) {
        engine.arrayMap[id->name] = type->arrayType;
    }
    auto varType = type->toLLVMType();
    if(isGlobal()) { // Difference is that : we should not pass initValue to it.
        return new GlobalVariable(*engine.getModule(), varType, false, GlobalValue::ExternalLinkage, type->Create(), id->name);
    } else {
        return CreateEntryBlockAlloca(engine.nowFunction(), id->name, varType);
    }
    // TODO: Need call assign to support usage: var a = 2;
    return nullptr;
}

/*
 * Create a var with its type
 * This function will return a Value* dependencies on it Type, and use 0 to initialize it.
 * */
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
                // TODO: pointers
            case SKY_INT_POINTER:
            case SKY_INT_64_POINTER:
            case SKY_CHAR_POINTER:
            case SKY_FLOAT_POINTER:
            case SKY_DOUBLE_POINTER:
            case SKY_BOOL_POINTER:
                return builder.getInt32(0);
        }
    } else if(type == SKY_ARRAY) { //Array type is a special type
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

/*
 *  Function declaration : this function is used to declare function
 *  1. construct params
 *  2. convert body
 *  3. end
 * */
Value * FuncDec::convertToCode() {
    funcType->funcName = id->name;
    return funcType->convertToCode();
}

Value * SkyFuncType::convertToCode() {
    vector<Type*> args;
    if (paraList != nullptr) {
        for (auto &it: *paraList) {
            args.push_back(it->type->toLLVMType());
        }
    }
    // func (args) -> retType {}
    auto funcType = FunctionType::get(retType->toLLVMType(), args, false);
    auto func = Function::Create(funcType, GlobalValue::ExternalLinkage, funcName, engine.getModule());
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
        ret = CreateEntryBlockAlloca(func, funcName, retType->toLLVMType());
    }

    body->convertToCode();

    engine.exitFunction();
    // Maintain the function stack
    if (engine.funcStackSize()) {
        auto nowFunc = engine.nowFunction();
        builder.SetInsertPoint(&(nowFunc->getBasicBlockList().back()));
    }
    return func;
}

/*
 * TO LLVM type : this function is used to cast our type : SkyType to LLVM type
 * */
Type * SkyType::toLLVMType() {
    if(type == SKY_VAR) {
        switch (*varType) {
            case SkyVarType::SKY_INT:
                return builder.getInt32Ty();
            case SkyVarType::SKY_INT_64:
                return builder.getInt64Ty();
            case SkyVarType::SKY_CHAR:
                return builder.getInt8Ty();
            case SkyVarType::SKY_FLOAT:
                return builder.getFloatTy();
            case SkyVarType::SKY_DOUBLE:
                return builder.getDoubleTy();
            case SkyVarType::SKY_BOOL:
                return builder.getInt1Ty();
                // TODO: pointers
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
    } else if (type == SKY_ARRAY) { // Array type is special
        return ArrayType::get(arrayType->type->toLLVMType(), arrayType->size);
    } else if (type == SKY_FUNC) {
        return builder.getInt32Ty();
    } else return llvm::Type::getVoidTy(context);
}

/*
 * Identifier conversion : load the value of this identifier and return a pointer which point to it.
 * */
Value *Identifier::convertToCode() {
    auto value = engine.findVarByName(name); // Find name first
    // Note: this function will get exception if we can not find correct var in context.
    return new LoadInst(value->getType()->getPointerElementType(), value, AMAZING_NAME, false, builder.GetInsertBlock());
}

/*
 * CompoundStat: {}, which used to contain lots of lines of code
 * */
Value *CompoundStat::convertToCode() {
    for (auto it : *statList) {
        it->convertToCode();
    }
    return nullptr;
}

/*
 * AssignStart : This function is used to load value of right to left identifier (arrayReference)
 * */
Value *AssignStat::convertToCode() {
    Value *res = nullptr;
    switch (type) {
        case ID_ASSIGN: // Identifier = value*
            return builder.CreateStore(expr->convertToCode(), engine.findVarByName(id->name));
        case ARRAY_ASSIGN: // ArratReference = value*
            return builder.CreateStore(expr->convertToCode(), arrayRef->getValueI());
        case LAMBDA_ASSIGN: // identifier = lambda
            int funcID = engine.pushNewFunction();
            dynamic_cast<SkyFuncType *>(expr)->funcName = engine.getFuncNameByID(funcID);
            expr->convertToCode();
            return builder.CreateStore(builder.getInt32(0), engine.findVarByName(id->name));
    }
    return nullptr;
}

/*
 * BinaryExpr : Format function.
 * */
Value *BinaryExpr::convertToCode() {
    auto leftValue = this->left->convertToCode();
    auto rightValue = this->right->convertToCode();
    return calcOp(leftValue, rightValue, op);
}

/*
 * ArrayReference, this function is used with the function below.
 * */
Value *ArrayReference::convertToCode() {
    return builder.CreateLoad(getValueI(), "arrReference");
}

/*
 * GetValueI : this function is used to get de addr of identifier[index]
 * */
Value *ArrayReference::getValueI() {
    auto arr = engine.findVarByName(id->name);
    auto index = subInd->convertToCode();
    vector<Value*> valueVec;
    valueVec.push_back(builder.getInt32(0)); // unknown params, but we need this
    valueVec.push_back(index);
    // Create a GEP to save value
    return builder.CreateInBoundsGEP(arr, ArrayRef<Value *>(valueVec));
}

/*
 * Function Call: this function is used to call function
 * */
Value *FuncCall::convertToCode() {
    auto func = engine.getModule()->getFunction(id->name);
    if (func == nullptr) { // If this function is not implement
        throw FuncNotFound(*(new string(id->name)) + " not found");
    }

    // System function should have its own call function, because it needs some special settings.
    if (strcmp(id->name, "printf") == 0 || strcmp(id->name, "scanf") == 0) {
        return callSysIO();
    }

    // Get all params
    vector<Value*> inputArgs;
    auto funcNeed = func->arg_begin();
    if (args != nullptr) {
        for (auto &it : *args) {
            if (funcNeed->hasNonNullAttr()) {
                auto *addr = engine.findVarByName(dynamic_cast<Identifier *>(it)->name);
                inputArgs.push_back(addr);
            } else {
                inputArgs.push_back(it->convertToCode());
            }
            funcNeed++;
        }
    }

    // Create Call sentences
    Value *ret = builder.CreateCall(func, inputArgs, "callFunc");
    return ret;
}


/*
 * If Status:
 *     if (condition) {
 *         -then-
 *     } else {
 *         -else-
 *     }
 *     -common-
 * condition -> then/else -> common
 * Note: LLVM do not permit any code after br or ret in the same basic block,
 *       so we must check this condition.
 * */
Value *IfStat::convertToCode() {

    Value *condValue = condExpr->convertToCode();
    condValue = builder.CreateICmpNE(condValue, ConstantInt::get(Type::getInt1Ty(context), 0, true), "if");

    auto func = engine.nowFunction();

    // Create 3 basic blocks to contain codes
    auto thenCond = BasicBlock::Create(context, "thenCond", func);
    auto elseCond = BasicBlock::Create(context, "elseCond", func);
    auto common = BasicBlock::Create(context, "common", func);

    // then
    auto branch = builder.CreateCondBr(condValue, thenCond, elseCond);
    builder.SetInsertPoint(thenCond);

    engine.flagIsReturn = false;
    thenStat->convertToCode();
    if (!engine.flagIsReturn) {// Do not create br, is jump is in body
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
    if (!engine.flagIsReturn) { // Do not create br, is jump is in body
        builder.CreateBr(common);
    }
    engine.flagIsReturn = false;
    elseCond = builder.GetInsertBlock();

    builder.SetInsertPoint(common);
    return branch;
}

/*
 * for Status:
 *     for condition {
 *         -loop-
 *     }
 *     -breakBlock-
 * condition -> loop/breakkBlock, loop->condition
 * Note: LLVM do not permit any code after br or ret in the same basic block,
 *       so we must check this condition.
 * */
Value *ForStat::convertToCode() {
    auto func = engine.nowFunction();

    Value * startValue = start->convertToCode();
    Value * endValue = end->convertToCode();
    Value * stepValue = step->convertToCode();

    Value * varValue = engine.findVarByName(forVar->name);
    builder.CreateStore(startValue, varValue);

    // Create 3 basic blocks to contain codes
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

/*
 * While Status:
 *     while condition {
 *         -loop-
 *     }
 *     -breakBlock-
 * condition -> loop/breakkBlock, loop->condition
 * Note: LLVM do not permit any code after br or ret in the same basic block,
 *       so we must check this condition.
 * */
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

/*
 * Jump Status: Control codes
 * - break : exit now loop
 * - continue : directly enter the condition part in current loop
 * - return : exit the function and return value
 * Note : No code is allowed to be write after JumpStat, so we used a flag to pass a signal.
 * */
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

/*
 * Return the pointer directly, if a reference value is needed.
 * */
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

/*
 * System function : scanf and printf
 * To implement the input and output of our language, we use the function of C : scanf , printf.
 * However, to adapt the format of scanf and printf, we need to convert our type to stander.
 * */
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
            // (I don't know why I should use indices[], but it works)
            auto zero = llvm::Constant::getNullValue(builder.getInt32Ty());
            Constant* indices[] = {zero, zero};
            // Convert to a char pointer
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

Value *SkyFuncType::convertToCode() {
    return nullptr;
}

Value *SkyAutoType::convertToCode() {
    return nullptr;
}
