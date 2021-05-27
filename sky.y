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
    bool bVal;
}

%token<iVal> INTEGER
%token<fVal> FLOAT
%token<dVal> DOUBLE
%token<cVal> CHAR
%token<sVal> STRING IDENTIFIER
%token<bVal> BOOLEAN

%token  MAIN VAR LET NEW DELETE
        FUNCTION BREAK RETURN
        IF ELSE FOR WHILE DO
        CLASS INIT DEL THIS
        TYPE_INT TYPE_INT_POINTER TYPE_INT_64 TYPE_INT_64_POINTER
        TYPE_CHAR TYPE_CHAR_POINTER
        TYPE_FLOAT TYPE_FLOAT_POINTER TYPE_DOUBLE TYPE_DOUBLE_POINTER
        TYPE_BOOL TYPE_BOOL_POINTER
        SLC BoC EoC
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
        OP_PLUS OP_MINUS OP_MUL OP_DIV OP_MOD OP_RIGHT OP_LEFT OP_INC OP_DEC OP_PTR OP_AND OP_OR
        OP_LT OP_LE OP_GT OP_GE OP_EQ OP_NE
        NEWLINE

%%

program
    : global_area main_func
    ;

global_area
    : global_area const_declaration
    | global_area var_declaration
    | global_area func_declaration
    |
    ;

const_declaration
    : LET const_list
    |
    ;

const_list
    : const_list ',' const_expr
    | const_expr
    ;

const_expr
    : const_name '=' const_value
    ;

const_value
    : INTEGER
    | FLOAT
    | DOUBLE
    | CHAR
    | BOOLEAN
    | STRING
    ;

var_declaration
    : VAR var_list
    |
    ;

var_list
    : var_list ',' var_expr
    | var_expr
    ;

var_expr
    : var_name '=' expression
    | var_name ':' var_type
    ;

var_type
    : TYPE_INT
    | TYPE_INT_POINTER
    | TYPE_INT_64
    | TYPE_INT_64_POINTER
    | TYPE_CHAR
    | TYPE_CHAR_POINTER
    | TYPE_FLOAT
    | TYPE_FLOAT_POINTER
    | TYPE_DOUBLE
    | TYPE_DOUBLE_POINTER
    | TYPE_BOOL
    | TYPE_BOOL_POINTER
    ;

func_declaration: FUNCTION func_name '(' parameter_list ')' '[' OP_PTR return_type ']' '{' statement_list '}' ;

parameter_list:
    parameter_list ',' var_name ':' var_type
    | var_name ':' var_type
    | ;

return_type:
    TYPE_INT | TYPE_INT_POINTER | TYPE_INT_64 | TYPE_INT_64_POINTER
    | TYPE_CHAR | TYPE_CHAR_POINTER
    | TYPE_FLOAT | TYPE_FLOAT_POINTER | TYPE_DOUBLE | TYPE_DOUBLE_POINTER
    | TYPE_BOOL | TYPE_BOOL_POINTER
    | ;

main_func
    : FUNCTION MAIN '(' ')' OP_PTR return_type '{' statement_list '}'
    ;

statement_list
    : statement_list statement
    |
    ;

statement
    : compound_statement
    | branch_statement
    | iteration_statement
    | expression
    | jump_statement
    | '='_statement
    | print_statement
    | var_declaration
    | const_declaration
    ;

compound_statement
    : '{' statement_list '}'
    ;

branch_statement
    : IF '(' expression ')' statement
    | IF '(' expression ')' statement ELSE statement
    ;

iteration_statement
    : WHILE '(' expression ')' statement
    | FOR '(' expression_statement expression_statement ')' statement
    | FOR '(' expression_statement expression_statement expression ')' statement
    ;

jump_statement
    : BREAK
    | RETURN
    | RETURN expression
    ;

expression_statement
    : ';'
    | expression ';'
    ;

expression
    : expression OP_PLUS expression
    | expression OP_MINUS expression
    | expression OP_MUL expression
    | expression OP_DIV expression
    | expression OP_AND expression
    | expression OP_OR expression
    | expression '[' expression ']'
    | expression '.' IDENTIFIER
    | expression OP_EQ expression
    | expression OP_NE expression
    | expression OP_GT expression
    | expression OP_LT expression
    | expression OP_GE expression
    | expression OP_LE expression
    | MINUS expression
    | OP_NOT expression
    | '(' expression ')'
    | const_value
    | IDENTIFIER
    | expression '(' expression_list ')'
    ;

expression_list
    : expression ',' expression_list
    | expression
    |
    ;



%%

