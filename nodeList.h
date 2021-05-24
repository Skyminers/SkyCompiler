//
// Created by 刘一辰 on 2021/5/20.
//

#ifndef NODELIST_H
#define NODELIST_H

#include "defineList.h"

using namespace llvm;
class ASTNode{
public:
    virtual void convertToCode();
};

class Statement: ASTNode{

};

#ifdef  SCRIPT
class SingleValue : Statement{
public:
    void convertToCode() override;
private:
    union value{
        int iVal;
        bool bVal;
        char* sVal;
        double fVal;
    };
};
#endif

#endif
