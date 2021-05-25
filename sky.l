%{

#include "sky.y.h"
using namespace std;

%}

  /*definition omitted*/

%%

  /*the process of Lexical analysis*/
"var"                       {return KW_VAR;}  
"let"                       {return KW_LET;} 
"new"                       {return KW_NEW;}
"delete"                    {return KW_DELETE;}
"func"                      {return KW_FUNCTION;} 
"if"                        {return KW_IF;}
"for"                       {return KW_FOR;} 
"while"                     {return KW_WHILE;}
"do"                        {return KW_DO;}
"class"                     {return KW_CLASS;}
"init"                      {return KW_INIT;}         /*构造函数*/
"del"                       {return KW_DEL;}          /*析构函数*/
"this"                      {return KW_THIS;}         /*自身指针*/

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

"{"                           {return SYM_LCB;}       /*left curly brace*/
"}"                           {return SYM_RCB;}       /*right curly brace*/
"("                           {return SYM_LP;}        /*left parenthesis*/
")"                           {return SYM_RP;}        /*right parenthesis*/
"["                           {return SYM_LB;}        /*left bracket*/                
"]"                           {return SYM_RB;}        /*right bracket*/                
"//"                          {return SYM_SLC;}       /*single-line comment*/
"/*"                          {return SYM_BoC;}       /*beginning of comment*/
"*/"                          {return SYM_EoC;}       /*end of comment*/
"."                           {return SYM_DOT; }
","                           {return SYM_COMMA;}
":"                           {return SYM_COLON;}
"+"                           {return SYM_PLUS;}           
"-"                           {return SYM_MINUS;}           
"*"                           {return SYM_MUL;}           
"/"                           {return SYM_DIV;} 
"%"                           {return SYM_MOD;}           
">"                           {return SYM_MT;}          /*more than*/           
"<"                           {return SYM_LT;}          /*less than*/           
"=="                          {return SYM_ET;}          /*equal to*/  
"->"                          {return SYM_RT;}          /*return type*/        
"="                           {return KW_ASSIGN;}       /*赋值*/   

[a-zA-Z_][a-zA-Z0-9_]*        { 
                                yylval.sVal = new std::string(yytext, yyleng);
                                return IDENTIFIER; 
                              }

%%

int yyerror(const char *s){
  fprintf(stderr, "error : %s \n", s);
  return 0;
}

int main(){
  yylex();
  return 0;
}
