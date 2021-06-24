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

Value* ConvertEngine::findVarByName(char *varName) {
    return findVarByName(string(varName));
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

int ConvertEngine::pushNewFunction() {
    string str = "lambdaDefault_" + to_string(lambdaCount++);
    lambdaName.push_back(str);
    return lambdaCount-1;
}

string ConvertEngine::getFuncNameByID(int id) {
    assert(id < lambdaName.size());
    return lambdaName[id];
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