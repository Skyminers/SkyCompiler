%{

#include<stdio.h>
#include<string>
#include "sky.tab.c"
using namespace std;

%}

  /*definition omitted*/

%%

  /*the process of Lexical analysis*/
"main"                        {return MAIN;}
"var"                         {return VAR;}  
"let"                         {return LET;} 
"new"                         {return NEW;}
"delete"                      {return DELETE;}
"func"                        {return FUNCTION;}
"return"                      {return RETURN;} 
"if"                          {return IF;}
"else"                        {return ELSE;}
"for"                         {return FOR;} 
"while"                       {return WHILE;}
"in"                          {return IN;}
"continue"                    {return CONTINUE;}
"break"                       {return BREAK;}
"class"                       {return CLASS;}
"__init__"                    {return INIT;}         /*构造函数*/
"__del__"                     {return DEL;}          /*析构函数*/
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
\n                            {return LF;}

"//"[^\n]*                    { }

"/*"			              { comment(); }

\'.\'                         {
                                yylval.cVal = yytext[1];
                                return CHAR;    
                              }

  /*Only lowercase true and false are allowed.*/
"true"|"false"                {
                                bool tmp;
                                sscanf(yytext, "%d", &tmp);
                                yylval.bVal = tmp;
                                return BOOLEAN;
                              }

[a-zA-Z_][a-zA-Z0-9_]*        { 
                                yylval.sVal = new std::string(yytext, yyleng);
                                return IDENTIFIER;
                              }

\"(\\.|[^\\"])*\"             {
                                yylval.sVal = new std::string(yytext, yyleng);
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

int yyerror(const char *s){
  fprintf(stderr, "error : %s \n", s);
  return 0;
}

comment() {
	char c, c1;
loop:
	while ((c = input()) != '*' && c != 0) putchar(c);
	if ((c1 = input()) != '/' && c != 0) {
		unput(c1);
		goto loop;
	}
	if (c != 0) putchar(c1);
}

int main(){
  yylex();
  return 0;
}
