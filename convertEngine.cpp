//
// Created by 刘一辰 on 2021/5/20.
//

#include "convertEngine.h"
#include "CompileException.h"

ConvertEngine engine;

void ConvertEngine::compile() {
    module->print(dbgs(), nullptr);
}

void ConvertEngine::createMainFunction() {
    vector<Type*> valuesType;
    auto funcType = FunctionType::get(builder.getInt32Ty(), makeArrayRef(valuesType), false);
    main = Function::Create(funcType, GlobalValue::InternalLinkage, "main", module);
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

Function *ConvertEngine::getScan() const {
    return scan;
}

Function *ConvertEngine::getPrint() const {
    return print;
}

Function *ConvertEngine::getMain() const {
    return main;
}


// Unit test
int main() {
    engine.createMainFunction();
    auto mainFunc = engine.getMain();
    auto mainBlock = BasicBlock::Create(context, "main", mainFunc);
    engine.enterFunction(mainFunc);
    builder.SetInsertPoint(mainBlock);
    builder.CreateRet(builder.getInt32(0));
    engine.compile();
}