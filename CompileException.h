//
// Created by LiuYichen on 2021/5/31.
//

#ifndef COMPILEEXCEPTION_H
#define COMPILEEXCEPTION_H

#include <string>
#include <utility>

class CompileException : std::exception{
public:
    explicit CompileException(std::string msg): errorMsg(std::move(msg)){}
    std::string getErrorMsg(){
        return "[Error] : " + errorMsg;
    }
private:
    std::string errorMsg;
};

class VarNotFound : CompileException{
public:
    VarNotFound(std::string msg): CompileException(msg){}
};

class FuncNotFound : CompileException{
public:
    FuncNotFound(std::string msg): CompileException(msg){}
};



#endif //COMPILEEXCEPTION_H
