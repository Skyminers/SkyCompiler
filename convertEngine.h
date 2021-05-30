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
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/Target/TargetMachine.h>

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>

#include "nodeList.h"

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
    stack<Function*> funcList;
    vector<BasicBlock*> blockID;

    /*
     * ArrayType is constant var, which need start point and length.
     * So, array type should be different from normal var.
     * */
    map<string, SkyArrayType*> arrayMap;

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

    /*
     * This function is used to create main function.
     * Main function is a special function which represented the entrance of program
     * */
    void createMainFunction();

    /*
     * Array type is different from normal var.
     * */
    SkyArrayType* findArrayValue(string varName);
    Value* findVarByName(string varName);


    void compile();
};

#endif //CONVERTENGINE_H