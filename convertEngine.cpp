//
// Created by 刘一辰 on 2021/5/20.
//

#include "convertEngine.h"

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
    //auto result = nowFunc->getValueSymbolTable()->lookup(varName);
}
// Unit test
int main() {
    engine.compile();
}