//
// Created by 刘一辰 on 2021/5/20.
//

#ifndef CONVERTENGINE_H
#define CONVERTENGINE_H

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Target/TargetMachine.h>

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
using namespace llvm;
static LLVMContext context;
static IRBuilder<> builder(context);

class ConvertEngine{
private:
    Module *module;
    uint layoutID;
    Function *scan, *print;
    Function *main;
public:
    ConvertEngine(){
        module = new Module("skyModule", context);
        layoutID = module->getDataLayout().getAllocaAddrSpace();

        // scan function
        auto funcType = FunctionType::get(builder.getInt32Ty(), true);
        scan = Function::Create(funcType, Function::ExternalLinkage, Twine("scanf"), module);
        scan->setCallingConv(CallingConv::C);

        // print function
        vector<Type*> valuesType;
        valuesType.push_back(builder.getInt8PtrTy());
        funcType = FunctionType::get(builder.getInt32Ty(), makeArrayRef(valuesType), true);
        print = Function::Create(funcType, Function::ExternalLinkage, Twine("printf"), module);
        print->setCallingConv(CallingConv::C);
    }


    void compile();
};

#endif //CONVERTENGINE_H