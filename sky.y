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
    Program *program;
    GlobalArea *globalArea;
    ConstDec *constDec;
    ConstDecList *constDecList;
    ConstValue *constValue;
}

%type<program>                          program
%type<globalArea>                       global_area
%type<constDec>                         const_expr
%type<constDecList>                     const_declaration const_list
%type<constValue>                       const_value

%token<iVal> INTEGER
%token<fVal> FLOAT
%token<dVal> DOUBLE
%token<cVal> CHAR
%token<sVal> STRING IDENTIFIER
%token<bVal> BOOLEAN

%token  MAIN VAR LET NEW DELETE
        FUNCTION BREAK CONTINUE RETURN
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
    : global_area main_func                                         { $$ = new Program($1, $2); }
    ;

global_area
    : global_area const_declaration                                 { $$ = $1; $$->addConstDec($2); }
    | global_area var_declaration                                   { $$ = $1; $$->addVarDec($2); }
    | global_area func_declaration                                  { $$ = $1; $$->addFuncDec($2); }
    |                                                               { $$ = new GlobalArea(); }
    ;

const_declaration
    : LET const_list                                                { $$ = $2; }
    ;

const_list
    : const_list ',' const_expr                                     { $$ = $1; $$->push_back($3); }
    | const_expr                                                    { $$ = new ConstDecList(); $$->push_back($1); }
    ;

const_expr
    : const_name '=' const_value                                    { $$ = new ConstDec($1, $3); }
    ;

const_value
    : INTEGER                                                       { $$ = new SkyInt($1); }
    | FLOAT                                                         { $$ = new SkyFloat($1); }
    | DOUBLE                                                        { $$ = new SkyDouble($1); }
    | CHAR                                                          { $$ = new SkyChar($1); }
    | BOOLEAN                                                       { $$ = new SkyBool($1); }
    | STRING                                                        { $$ = new SkyString($1); }
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

func_declaration
    : FUNCTION func_name '(' parameter_list ')' '[' OP_PTR return_type ']' '{' statement_list '}' 
    ;

parameter_list
    :
    parameter_list ',' var_name ':' var_type
    | var_name ':' var_type
    | 
    ;

return_type:
    TYPE_INT 
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
    | assign_statement
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
    | DO statement WHILE '(' expression ')'
    | FOR '(' expression_statement expression_statement ')' statement
    | FOR '(' expression_statement expression_statement expression ')' statement
    ;

jump_statement
    : BREAK
    | CONTINUE
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

assign_statement
    : var_name assign_operator expression

assign_operator
    : OR_ASSIGN
    | ADD_ASSIGN
    | AND_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    | MUL_ASSIGN
    | SUB_ASSIGN
    | XOR_ASSIGN
    | '='
    ;

print_statement
    : PRINTF '(' print_content ')'

print_content
    : content_var_list
    | IDENTIFIER
    ;

content_var_list
    : var_type_list ',' var_name_list 
    ;

var_type_list
    : var_type var_type_list
    ;

var_name_list
    : var_name var_name_list
    ;

const_name
    : STRING
    ;    

var_name
    : STRING
    ;

func_name
    : STRING
    ;

%%

