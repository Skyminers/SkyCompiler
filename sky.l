%{

#include " sky.y.h"
using namespace std;


%}


  /*ToBeFinished: sky keywords*/

KW_VAR var  
KW_LET let
KW_FUN fun 
KW_IF if 
KW_FOR for 







  /*ToBeFinished: sky data type*/

TYPE_INT int
TYPE_INT_64 int64
TYPE_CHAR char
TYPE_BOOL bool
TYPE_FLOAT float
TYPE_DOUBLE double


  /*ToBeFinished: sky symbols*/

SYM_LCURLYBRACE "{"
SYM_RCURLYBRACE "}"




  /*ToBeFinished: sky others*/



%%

  /*the process of Lexical analysis*/






%%

int yyerror(const char *s){
  fprintf(stderr, "error : %s \n", s);
  return 0;
}

int main(){
  yylex();
  return 0;
}



