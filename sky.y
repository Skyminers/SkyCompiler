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
%token<sVal> STRING
%token<bVal> BOOLEAN

%token  VAR LET NEW DELETE
        FUNCTION
        IF ELSE FOR WHILE DO
        CLASS INIT DEL THIS
        TYPE_INT TYPE_INT_POINTER TYPE_INT_64 TYPE_INT_64_POINTER
        TYPE_CHAR TYPE_CHAR_POINTER
        TYPE_FLOAT TYPE_FLOAT_POINTER TYPE_DOUBLE TYPE_DOUBLE_POINTER
        TYPE_BOOL TYPE_BOOL_POINTER
        LCB RCB LP RP LB RB
        SLC BoC EoC
        DOT COMMA COLON
        PLUS MINUS MUL DIV MOD
        MT LT ET
        RT ASSIGN NEWLINE

%%

program: global_area main_func ;

global_area:
    global_area const_declaration
    | global_area var_declaration
    | global_area func_declaration
    | ;

const_declaration:
    LET const_list
    | ;

const_list:
    const_list COMMA const_expr
    | const_expr ;

const_expr: const_name ASSIGN const_value ;

const_value:
    INTEGER
    | FLOAT
    | DOUBLE
    | CHAR
    | BOOLEAN
    | STRING ;

var_declaration:
    VAR var_list
    | ;

var_list:
    var_list COMMA var_expr
    | var_expr ;

var_expr:
    var_name ASSIGN expression
    | var_name COLON var_type ;

var_type:
    TYPE_INT | TYPE_INT_POINTER | TYPE_INT_64 | TYPE_INT_64_POINTER
    | TYPE_CHAR | TYPE_CHAR_POINTER
    | TYPE_FLOAT | TYPE_FLOAT_POINTER | TYPE_DOUBLE | TYPE_DOUBLE_POINTER
    | TYPE_BOOL | TYPE_BOOL_POINTER

func_declaration: ;

main_func: return_type MAIN LCB statement_list RCB ;

statement_list:
    statement_list statement
    | ;

statement:
    compound_statement
    | branch_statement
    | while_statement
    | for_statement
    | assign_statement
    | assign_subscr_statement
    | print_statement
    | expression_statement
    | break_statement
    | return_statement ;

compound_statement: LCB statement_list RCB ;

branch_statement: IF LP expression RP statement else_part ;

else_part:
    ELSE statement
    | ;


%%

