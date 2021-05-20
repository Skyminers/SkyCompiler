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
    double fVal;
    int iVal;
    char* *sVal;
}

%token<fVal> FLOAT
%token<iVal> INTEGER
%token<sVal> STRING

%%

begin : begin exp '\n'{
    printf("exp = %d\n", $2);
} | begin '\n'
  | ;
