//
// Created by 刘一辰 on 2021/5/20.
//

#ifndef CONVERTENGINE_H
#define CONVERTENGINE_H

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#include <cstdio>
#include <iostream>

using namespace std;

class ConvertEngine{
public:
    ConvertEngine(){
        mod = LLVMModuleCreateWithName("sky_module");
    }

    void newFunction(/*A careful module description is needed here.*/){
        // An a+b function is used to test.

        // Create function block
        LLVMTypeRef params[] = { LLVMInt32Type(), LLVMInt32Type()};
        auto retType = LLVMFunctionType(LLVMInt32Type(), params, 2, 0);
        auto sum = LLVMAddFunction(mod, "sum", retType);

        // Add function code
        auto entry = LLVMAppendBasicBlock(sum, "entry");
        auto builder = LLVMCreateBuilder();
        LLVMPositionBuilderAtEnd(builder, entry);
        auto tmp = LLVMBuildAdd(builder, LLVMGetParam(sum, 0), LLVMGetParam(sum, 1), "tmp");
        LLVMBuildRet(builder, tmp);

        // Check code
        char *buf = nullptr;
        LLVMVerifyModule(mod, LLVMAbortProcessAction, &buf);
        LLVMDisposeMessage(buf);
    }

    int compile(string filename){
        if(!filename.empty()) {
            filename = "sky.out";
        }
        if(LLVMWriteBitcodeToFile(mod, filename.c_str())){
            cerr << "[error] An error occurs at writing" << endl;
            return 1;
        }
        cout << "Compile successfully to " << filename << endl;
        return 0;
    }

private:
    LLVMModuleRef mod;
};

#endif //CONVERTENGINE_H