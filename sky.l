%{

#include<stdio.h>
#include<string>
#include "sky.y.h"
using namespace std;

%}

  /*definition omitted*/

%%

  /*the process of Lexical analysis*/
"var"                         {return VAR;}  
"let"                         {return LET;} 
"new"                         {return NEW;}
"delete"                      {return DELETE;}
"func"                        {return FUNCTION;}
"return"                      {return RETURN;} 
"if"                          {return IF;}
"for"                         {return FOR;} 
"while"                       {return WHILE;}
"do"                          {return DO;}
"continue"                    {return CONTINUE;}
"break"                       {return BREAK;}
"class"                       {return CLASS;}
"init"                        {return INIT;}         /*构造函数*/
"del"                         {return DEL;}          /*析构函数*/
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

"{"                           {return LCB;}       /*left curly brace*/
"}"                           {return RCB;}       /*right curly brace*/
"("                           {return LP;}        /*left parenthesis*/
")"                           {return RP;}        /*right parenthesis*/
"["                           {return LB;}        /*left bracket*/                
"]"                           {return RB;}        /*right bracket*/                
"//"                          {return SLC;}       /*single-line comment*/
"/*"                          {return BoC;}       /*beginning of comment*/
"*/"                          {return EoC;}       /*end of comment*/
"."                           {return DOT; }
","                           {return COMMA;}
":"                           {return COLON;}
"="                           {return ASSIGN;}       /*赋值*/   
"+="		                    	{return ADD_ASSIGN;}
"-="                          {return SUB_ASSIGN;}
"*="                    			{return MUL_ASSIGN;}
"/="	                    		{return DIV_ASSIGN;}
"%="		                    	{return MOD_ASSIGN;}
"&="	                    		{return AND_ASSIGN;}
"^="		                    	{return XOR_ASSIGN;}
"|="		                    	{return OR_ASSIGN;}
"+"                           {return OP_PLUS;}           
"-"                           {return OP_MINUS;}           
"*"                           {return OP_MUL;}           
"/"                           {return OP_DIV;} 
"%"                           {return OP_MOD;} 
">>"		                    	{return OP_RIGHT;}
"<<"		                    	{return OP_LEFT;}
"++"		                    	{return OP_INC;}      /*self-increase*/
"--"		                    	{return OP_DEC;}      /*self-decrease*/
"->"			                    {return OP_PTR;}      /*pointer or return type*/ 
"&&"	                    		{return OP_AND;}
"||"                    			{return OP_OR;}
"<"                           {return OP_LT;}       /*less than*/ 
"<="                    			{return OP_LE;}
">"                           {return OP_GT;}       /*greater than*/           
">="		                    	{return OP_GE;}
"=="                          {return OP_EQ;}         
"!="                          {return OP_NE;}  
\n                            {return NEWLINE;}                              

\'.\'                         {
                                yylval.cVal = yytext[1];
                                return CHAR;    
                              }

[a-zA-Z_][a-zA-Z0-9_]*        { 
                                yylval.sVal = new std::string(yytext, yyleng);
                                return STRING; 
                              }

"true"|"false"                {
                                yylval.sVal = new std::string(yytext, yyleng); 
                                return BOOLEAN;  
                              }  

[0-9]+\.[0-9]+                { 
                                double tmp;
                                sscanf(yytext, "%lf", &tmp);
                                yylval.dVal = tmp;
                                return DOUBLE; 
                              }

[0-9]+\.[0-9]+[fF]            { 
                                float tmp;
                                sscanf(yytext, "%f", &tmp);
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

int main(){
  yylex();
  return 0;
}
