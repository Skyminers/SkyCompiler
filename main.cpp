//
// Created by 刘一辰 on 2021/5/19.
//

#include "nodeList.h"
#include "convertEngine.h"
#include "sky.tab.h"

extern int yyparse();
extern Program * root;
extern ConvertEngine engine;
extern FILE *yyin, *yyout;
int main(){
    yyin = fopen("test.sky", "r");
    yyparse();
    if (root == nullptr) return -1;
    root->convertToCode();
    engine.compileToFile("compileOut.ir");
    return 0;
}