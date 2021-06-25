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
    Function *scan, *print;

private:
    Function *main;
    stack<Function*> funcList;
    vector<BasicBlock*> breakBlock;
    vector<BasicBlock*> continueBlock;
    vector<string> lambdaName;
    int lambdaCount;
public:
    /*
     * ArrayType is constant var, which need start point and length.
     * So, array type should be different from normal var.
     * */
    map<string, SkyArrayType*> arrayMap;
    bool flagIsReturn;

public:
    ConvertEngine(){
        module = new Module("skyModule", context);
        int layoutID = module->getDataLayout().getAllocaAddrSpace();
        lambdaCount = 0;
        // scan function
        vector<Type*> valuesType;
        valuesType.push_back(builder.getInt8PtrTy());
        auto funcType = FunctionType::get(builder.getInt32Ty(), makeArrayRef(valuesType), true);
        scan = Function::Create(funcType, Function::ExternalLinkage, Twine("scanf"), module);
        scan->setCallingConv(CallingConv::C);

        // print function
        funcType = FunctionType::get(builder.getInt32Ty(), makeArrayRef(valuesType), true);
        print = Function::Create(funcType, Function::ExternalLinkage, Twine("printf"), module);
        print->setCallingConv(CallingConv::C);

    }

    /*
     * Below two function is used to find var by name.
     * Note: Array type is different from normal var.
     * */
    Value* findVarByName(string varName);
    Value* findVarByName(char* varName);

    /*
     * Below function is used to maintain function stack.
     * - nowFunction : return current function
     * - enterFunction : enter a new function (this func should be called when you call a new function)
     * - exitFunction : exit current function (this func should be called when you meet return in function)
     * */
    int funcStackSize() {return funcList.size();}
    Function* nowFunction() { return funcList.top();}
    void enterFunction(Function* func){ funcList.push(func);}
    void exitFunction(){ funcList.pop(); }

    void compileToFile(string fileName);

    /*
     * BasicBlock dataStruct is used to get the break block and continue block,
     * when we use break or continue in loops
     * */
    BasicBlock* getCurBreakBlock();
    BasicBlock* getCurContinueBlock();
    void enterLoop(BasicBlock* breakBlock, BasicBlock* continueBlock);
    void exitLoop();

    /*
     * Lambda ID , we use id->name to maintain lambda function
     * */
    string getFuncNameByID(int id);
    int pushNewFunction();
};

#endif //CONVERTENGINE_H