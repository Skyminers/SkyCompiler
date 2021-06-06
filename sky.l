%{

#include<stdio.h>
#include<string>
#include "nodeList.h"
#include "sky.tab.h"
extern "C" int yywrap() {return 1;}
using namespace std;

%}

  /*definition omitted*/

%%

  /*the process of Lexical analysis*/
[ \t\n]                       {  }
"var"                         {return VAR;}  
"let"                         {return LET;} 
"new"                         {return NEW;}
"delete"                      {return DELETE;}
"func"                        {return FUNCTION;}
"return"                      {return JUMP_RETURN;}
"if"                          {return IF;}
"else"                        {return ELSE;}
"for"                         {return FOR;} 
"while"                       {return WHILE;}
"in"                          {return IN;}
"continue"                    {return JUMP_CONTINUE;}
"break"                       {return JUMP_BREAK;}
"class"                       {return CLASS;}
"this"                        {return THIS;}         /*自身指针*/

"int"                         {return TYPE_INT;}
"int*"                        {return TYPE_INT_POINTER;}
"int64"                       {return TYPE_INT_64;}
"int64*"                      {return TYPE_INT_64_POINTER;}
"char"                        {return TYPE_CHAR;} 
"char*"                       {return TYPE_CHAR_POINTER;} 
"float"                       {return TYPE_FLOAT;}  
"float*"                      {return TYPE_FLOAT_POINTER;} 
"double"                      {return TYPE_DOUBLE;}   
"double*"                     {return TYPE_DOUBLE_POINTER;} 
"bool"                        {return TYPE_BOOL;} 
"bool*"                       {return TYPE_BOOL_POINTER;} 

"{"                           {return('{');}        /*left curly brace*/
"}"                           {return('}');}        /*right curly brace*/
"("                           {return('(');}        /*left parenthesis*/
")"                           {return(')');}        /*right parenthesis*/
"["                           {return('[');}        /*left bracket*/                
"]"                           {return(']');}        /*right bracket*/                
"."                           {return('.');}
","                           {return(',');}
":"                           {return(':');}
";"                           {return(';');}
"="                           {return('=');}        /*赋值*/   
"+="                          {return ADD_ASSIGN;}
"-="                          {return SUB_ASSIGN;}
"*="                          {return MUL_ASSIGN;}
"/="                          {return DIV_ASSIGN;}
"%="                          {return MOD_ASSIGN;}
"&="                          {return AND_ASSIGN;}
"^="                          {return XOR_ASSIGN;}
"|="                          {return OR_ASSIGN;}
"!"                           {return OPER_NOT;}
"+"                           {return OPER_PLUS;}           
"-"                           {return OPER_MINUS;}           
"*"                           {return('*');}
"/"                           {return OPER_DIV;} 
"%"                           {return OPER_MOD;} 
">>"                          {return OPER_RIGHT;}
"<<"                          {return OPER_LEFT;}
"->"                          {return OPER_PTR;}      /*pointer or return type*/ 
"&&"                          {return OPER_AND;}
"&"                           {return('&');}
"||"                          {return OPER_OR;}
"<"                           {return OPER_LT;}       /*less than*/ 
"<="                          {return OPER_LE;}
">"                           {return OPER_GT;}       /*greater than*/           
">="                          {return OPER_GE;}
"=="                          {return OPER_EQ;}         
"!="                          {return OPER_NE;}

"//"[^\n]*                    { }

\'.\'                         {
                                yylval.cVal = yytext[1];
                                return CHAR;    
                              }

\'\\[nt0]\'                   {
                                if (yytext[2] == 'n') {
                                    yylval.cVal = '\n';
                                }
                                if (yytext[2] == 't') {
                                    yylval.cVal = '\t';
                                }
                                if (yytext[2] == '0') {
                                    yylval.cVal = '\0';
                                }
                                return CHAR;
                              }

  /*Only lowercase true and false are allowed.*/
"true"|"false"                {
                                bool tmp;
                                sscanf(yytext, "%d", &tmp);
                                yylval.bVal = tmp;
                                return BOOLEAN;
                              }

"__init__"                    {
                                yylval.sVal = new char[yyleng+1];
                                strcpy(yylval.sVal, yytext);
                                return INIT;
                              }

"__del__"                     {
                                yylval.sVal = new char[yyleng+1];
                                strcpy(yylval.sVal, yytext);
                                return DEL;
                              }

"main"                        {
                                yylval.sVal = new char[yyleng+1];
                                strcpy(yylval.sVal, yytext);
                                //printf("%s\n", yytext);
                                return MAIN;
                              }

[a-zA-Z_][a-zA-Z0-9_]*        { 
                                yylval.sVal = new char[yyleng+1];
                                strcpy(yylval.sVal, yytext);
                                //printf("%s\n", yytext);
                                return IDENTIFIER;
                              }

\"(\\.|[^\\\"])*\"           {
                                yylval.sVal = new char[yyleng-1];
                                memcpy(yylval.sVal, yytext+1, strlen(yytext)-2);
                                yylval.sVal[yyleng-2] = '\0';
                                //printf("%s\n", yylval.sVal);
                                return STRING;
                              }

[0-9]+\.[0-9]+                { 
                                double tmp;
                                sscanf(yytext, "%lf", &tmp);
                                yylval.dVal = tmp;
                                return DOUBLE; 
                              }

[0-9]+\.[0-9]+[fF]            { 
                                float tmp;
                                sscanf(yytext, "%f[fF]", &tmp);
                                yylval.fVal = tmp;
                                return FLOAT; 
                              }                              

[0-9]+                        {
                                int tmp;                                                          
                                sscanf(yytext, "%d", &tmp);
                                yylval.iVal = tmp; 
                                return INTEGER; 
                              }

%%