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
public:
    Module *getModule() const;

private:
    uint layoutID;
    Function *scan, *print;
public:
    Function *getScan() const;
    Function *getPrint() const;
    Function *getMain() const;

private:
    Function *main;
    stack<Function*> funcList;
    vector<BasicBlock*> breakBlock;
    vector<BasicBlock*> continueBlock;
public:
    /*
     * ArrayType is constant var, which need start point and length.
     * So, array type should be different from normal var.
     * */
    map<string, SkyArrayType*> arrayMap;
    map<uint, string> ptrMap;


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
     * Below two function is used to find var by name.
     * Note: Array type is different from normal var.
     * */
    SkyArrayType* findArrayValue(string varName);
    Value* findVarByName(string varName);

    /*
     * Below function is used to maintain function stack.
     * - nowFunction : return current function
     * - enterFunction : enter a new function (this func should be called when you call a new function)
     * - exitFunction : exit current function (this func should be called when you meet return in function)
     * */
    Function* nowFunction(){ return funcList.top();}
    void enterFunction(Function* func){ funcList.push(func);}
    void exitFunction(){ funcList.pop(); }

    Function* askForFunction(string funcName);
    void compileToFile(string fileName);

    BasicBlock* getCurBreakBlock();
    BasicBlock* getCurContinueBlock();
    void enterLoop(BasicBlock* breakBlock, BasicBlock* continueBlock);
    void exitLoop();
};

#endif //CONVERTENGINE_H