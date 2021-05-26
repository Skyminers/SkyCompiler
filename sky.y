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

%token  KW_VAR KW_LET KW_NEW KW_DELETE
        KW_FUNCTION
        KW_IF KW_ELSE KW_FOR KW_WHILE KW_DO
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

program: global_area main_func ;

global_area:
    global_area const_declaration
    | global_area var_declaration
    | global_area func_declaration
    | ;

const_declaration:
    KW_LET const_list
    | ;

const_list:
    const_list SYM_COMMA const_expr
    | const_expr ;

const_expr: const_name SYM_ASSIGN const_value ;

const_value:
    INTEGER
    | FLOAT
    | DOUBLE
    | CHAR
    | BOOLEAN
    | STRING ;

var_declaration:
    KW_VAR var_list
    | ;

var_list:
    var_list SYM_COMMA var_expr
    | var_expr ;

var_expr:
    var_name SYM_ASSIGN expression
    | var_name SYM_COLON var_type ;

var_type:
    TYPE_INT | TYPE_INT_POINTER | TYPE_INT_64 | TYPE_INT_64_POINTER
    | TYPE_CHAR | TYPE_CHAR_POINTER
    | TYPE_FLOAT | TYPE_FLOAT_POINTER | TYPE_DOUBLE | TYPE_DOUBLE_POINTER
    | TYPE_BOOL | TYPE_BOOL_POINTER

func_declaration: ;

main_func: return_type MAIN SYM_LCB statement_list SYM_RCB ;

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

compound_statement: SYM_LCB statement_list SYM_RCB ;

branch_statement: KW_IF SYM_LP expression SYM_RP statement else_part ;

else_part:
    KW_ELSE statement
    | ;


%%

