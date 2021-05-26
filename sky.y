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

%token  KW_VAR KW_LET KW_NEW KW_DELETE
        KW_FUNCTION
        KW_IF KW_FOR KW_WHILE KW_DO
        KW_CLASS KW_INIT KW_DEL KW_THIS
        TYPE_INT TYPE_INT_POINTER TYPE_INT_64 TYPE_INT_64_POINTER
        TYPE_CHAR TYPE_CHAR_POINTER 
        TYPE_FLOAT TYPE_FLOAT_POINTER TYPE_DOUBLE TYPE_DOUBLE_POINTER
        TYPE_BOOL TYPE_BOOL_POINTER
        SYM_LCB SYM_RCB SYM_LP SYM_RP SYM_LB SYM_RB
        SYM_SLC SYM_BoC SYM_EoC
        SYM_DOT SYM_COMMA SYM_COLON
        SYM_PLUS SYM_MINUS SYM_MUL SYM_DIV SYM_MOD
        SYM_MT SYM_LT SYM_ET
        SYM_RT SYM_ASSIGN SYM_NEWLINE


%%

begin : begin exp '\n'{
    printf("exp = %d\n", $2);
} | begin '\n'
  | ;
