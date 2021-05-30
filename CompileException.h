//
// Created by LiuYichen on 2021/5/31.
//

#ifndef COMPILEEXCEPTION_H
#define COMPILEEXCEPTION_H

#include <string>
#include <utility>

class CompileException {
public:
    std::string errorMsg;
    explicit CompileException(std::string msg="Empty error msg."): errorMsg(std::move(msg)){}
};

class VarNotFound : CompileException{};


#endif //COMPILEEXCEPTION_H
