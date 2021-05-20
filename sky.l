%{

#include " sky.y.h"
using namespace std;


%}


/*ToBeFinished: sky keywords*/


/*ToBeFinished: sky data type*/


/*ToBeFinished: sky symbols*/


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



