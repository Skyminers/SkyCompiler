%{
#include <string>
#include <cstdio>

void yyerror(char *s){
    printf("[Error]: %s", s);
    return ;
}

extern int yylex();
%}

%token LN // literal number 字面量-数字

%union {
    int iVal;
    float fVal;
    double dVal;
    char cVal;
    string sVal;
    
}

%token<iVal> INTEGER
%token<fVal> FLOAT
%token<dVal> DOUBLE
%token<cVal> CHAR
%token<sVal> STRING BOOLEAN

%token  VAR LET NEW DELETE
        FUNCTION RETURN
        IF FOR WHILE DO CONTINUE BREAK
        CLASS INIT DEL THIS
        TYPE_INT TYPE_INT_POINTER TYPE_INT_64 TYPE_INT_64_POINTER
        TYPE_CHAR TYPE_CHAR_POINTER 
        TYPE_FLOAT TYPE_FLOAT_POINTER TYPE_DOUBLE TYPE_DOUBLE_POINTER
        TYPE_BOOL TYPE_BOOL_POINTER
        LCB RCB LP RP LB RB
        SLC BoC EoC
        DOT COMMA COLON
        ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
        OP_PLUS OP_MINUS OP_MUL OP_DIV OP_MOD OP_RIGHT OP_LEFT OP_INC OP_DEC OP_PTR OP_AND OP_OR
        OP_LT OP_LE OP_GT OP_GE OP_EQ OP_NE
        NEWLINE


%%
