////
//// Created by 刘一辰 on 2021/5/20.
////
//
//#ifndef CONVERTENGINE_H
//#define CONVERTENGINE_H
//
//#include <llvm-c/Core.h>
//#include <llvm-c/ExecutionEngine.h>
//#include <llvm-c/Target.h>
//#include <llvm-c/Analysis.h>
//#include <llvm-c/BitWriter.h>
//#include <llvm/IR/Function.h>
//
//#include <cstdio>
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//class ConvertEngine{
//private:
//    LLVMModuleRef mod;
//    LLVMBasicBlockRef entry;
//    LLVMValueRef nowFunction;
//    LLVMBuilderRef builder;
//    bool returnFlag;
//    vector<LLVMValueRef> funcValueList;
//    LLVMValueRef printFunc;
//
//public:
//    ConvertEngine(){
//        mod = LLVMModuleCreateWithName("sky_module");
//        builder = LLVMCreateBuilder();
//        entry = nullptr;
//        nowFunction = nullptr;
////        std::vector<llvm::Type*> arg_types;
////        arg_types.push_back(LLVMIntPtrType(LLVMInt8Type()));
////        auto printf_type = llvm::FunctionType::get(LLVMInt32Type(), llvm::makeArrayRef(arg_types), true);
////        auto func = llvm::Function::Create(printf_type, llvm::Function::ExternalLinkage, llvm::Twine("printf"), mod.get());
//        printFunc = LLVMGetNamedFunction(mod, "printf");
//    }
//
//    void newFunction(/*A careful module description is needed here.*/){
//        // An a+b function is used to test.
//
//        // Create function block
//        LLVMTypeRef params[] = { LLVMInt32Type(), LLVMInt32Type()};
//        auto retType = LLVMFunctionType(LLVMInt32Type(), params, 2, 0);
//        auto sum = LLVMAddFunction(mod, "sum", retType);
//
//        // Add function code
//        auto entry = LLVMAppendBasicBlock(sum, "entry");
//        auto builder = LLVMCreateBuilder();
//        LLVMPositionBuilderAtEnd(builder, entry);
//        auto tmp = LLVMBuildAdd(builder, LLVMGetParam(sum, 0), LLVMGetParam(sum, 1), "tmp");
//        LLVMBuildRet(builder, tmp);
//
//        // Check code
//        char *buf = nullptr;
//        LLVMVerifyModule(mod, LLVMAbortProcessAction, &buf);
//        LLVMDisposeMessage(buf);
//    }
//
//    int printFunction(/*A description of output is needed*/){
//        LLVMPositionBuilderAtEnd(builder, entry);
//        LLVMValueRef a[] = { LLVMConstString("test", 4, false) };
//        auto tmp = LLVMBuildCall(builder, printFunc, a, 1, "tmp");
//        LLVMBuildRet(builder, tmp);
//    }
//
//    /*
//     * Create function
//     * 1. Call defineFunctionBegin()
//     * 2. Call right function to create basic code
//     * 3. Call defineFunctionEnd()
//     */
//
//    int defineFunctionBegin(/*A careful module description is needed here.*/){
//        if(nowFunction){
//            cerr << "[error] Can not define function in function" << endl;
//            return 1;
//        }
//        LLVMTypeRef params[] = { LLVMInt32Type(), LLVMInt32Type()}; // function params
//        auto retType = LLVMFunctionType(LLVMInt32Type(), params, 2, 0); // function return type
//        nowFunction = LLVMAddFunction(mod, "sum", retType); // function created
//        entry = LLVMAppendBasicBlock(nowFunction, "entry");
//        returnFlag = false;
//        funcValueList.clear();
//    }
//
//    int defineFunctionEnd(){
//        if(!nowFunction){
//            cerr << "[error] You should call defineFunctionBegin() before call defineFunctionEnd()" << endl;
//            return 1;
//        }
//        if(!entry){
//            cerr << "[error] Empty function is not allowed" << endl;
//            return 2;
//        }
//
//        if(!returnFlag){
//            cerr << "[error] Return can not be ignored" << endl;
//            return 3;
//        }
//        nowFunction = nullptr;
//        return 0;
//    }
//
//    int compile(string filename){
//        if(!filename.empty()) {
//            filename = "sky.out";
//        }
//        if(LLVMWriteBitcodeToFile(mod, filename.c_str())){
//            cerr << "[error] An error occurs at writing" << endl;
//            return 1;
//        }
//        cout << "Compile successfully to " << filename << endl;
//        return 0;
//    }
//};
//
//#endif //CONVERTENGINE_H