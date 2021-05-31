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
    for(auto &it: *myParaList){
        args.insert(args.end(), /*通过 it 取出他的长度*/, );
    }
    return nullptr;
}