//
// Created by 刘一辰 on 2021/5/20.
//

#include <fstream>
#include "convertEngine.h"
#include "CompileException.h"

ConvertEngine engine;

void ConvertEngine::compileToFile(string fileName) {
    error_code ErrInfo;
    raw_ostream *out = new raw_fd_ostream(fileName, ErrInfo, sys::fs::CreationDisposition());
    module->print(*out , nullptr);
}

void ConvertEngine::createMainFunction() {
    vector<Type*> valuesType;
    auto funcType = FunctionType::get(builder.getInt32Ty(), makeArrayRef(valuesType), false);
    main = Function::Create(funcType, GlobalValue::ExternalLinkage, "main", module);
}

SkyArrayType* ConvertEngine::findArrayValue(string varName) {
    if(arrayMap.count(varName) == 0) return nullptr;
    return arrayMap[varName];
}

Value* ConvertEngine::findVarByName(string varName) {
    auto nowFunc = funcList.top();
    auto result = nowFunc->getValueSymbolTable()->lookup(varName);
    if(result != nullptr) return result;
    result = module->getGlobalVariable(varName);
    if(result == nullptr){
        throw VarNotFound(varName + " not found");
    }
    return result;
}

Function* ConvertEngine::askForFunction(string funcName) {
    auto func = module->getFunction(funcName);
    if(func == nullptr) throw FuncNotFound(funcName + " not found");
    return func;
}

Function *ConvertEngine::getScan() const {
    return scan;
}

Function *ConvertEngine::getPrint() const {
    return print;
}

Function *ConvertEngine::getMain() const {
    return main;
}

Module *ConvertEngine::getModule() const {
    return module;
}

BasicBlock *ConvertEngine::getCurBreakBlock() {
    return *breakBlock.rbegin();
}

BasicBlock *ConvertEngine::getCurContinueBlock() {
    return *continueBlock.rbegin();
}

void ConvertEngine::enterLoop(BasicBlock* breakBlock, BasicBlock* continueBlock) {
    this->breakBlock.push_back(breakBlock);
    this->continueBlock.push_back(continueBlock);
}

void ConvertEngine::exitLoop() {
    breakBlock.pop_back();
    continueBlock.pop_back();
}

// Unit test
//int main() {
//    engine.createMainFunction();
//    auto mainFunc = engine.getMain();
//    auto mainBlock = BasicBlock::Create(context, "main", mainFunc);
//    engine.enterFunction(mainFunc);
//    builder.SetInsertPoint(mainBlock);
//    builder.CreateRetVoid();
//    builder.CreateRet(builder.getInt32(0));
//    engine.compileToFile("skyModule");
//}