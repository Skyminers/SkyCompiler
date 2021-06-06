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
int main(int argc, char** argv){
    if (argc >= 2) {
        yyin = fopen(argv[1], "r");
    } else {
        puts("Invalid param. fuck you!");
        return 0;
    }
    yyparse();
    if (root == nullptr) return -1;
    root->convertToCode();
    if (argc != 3) {
        engine.compileToFile("compileOut.ir");
        system("llc compileOut.ir");
        system("gcc compileOut.ir.s -o compileOut");
    } else {
        string fileName = string(argv[2]);
        engine.compileToFile(fileName+".ir");
        system(("llc " + fileName).c_str());
        system(("gcc " + fileName + ".s" + " -o " + fileName).c_str());
    }
    return 0;
}