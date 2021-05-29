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
    VarDec *varDec;
    VarDecList *varDecList;
    SkyTypes *skyTypes;
    SkyVarType *skyVarType;
    SkyArrayType *skyArrayType;
    FuncDec *funcDec;
}

%type<program>                          program
%type<globalArea>                       global_area
%type<constDec>                         const_expr
%type<constDecList>                     const_declaration const_list
%type<constValue>                       const_value
%type<varDec>                           var_expr
%type<varDecList>                       var_declaration var_list
%type<skyTypes>                         type_declaration
%type<skyVarType>                       var_type
%type<skyArrayType>                     array_type_declaration
%type<funcDec>                          func_declaration

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
    : name '=' const_value                                          { $$ = new ConstDec($1, $3); }
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
    : VAR var_list                                                  { $$ = $2; }
    ;

var_list
    : var_list ',' var_expr                                         { $$ = $1; $$->push_back($3); }
    | var_expr                                                      { $$ = new VarDecList(); $$->push_back($1); }
    ;

var_expr
    : name '=' expression
    | name ':' type_declaration                                     { $$ = new VarDec($1, $3); }
    ;

type_declaration
    : var_type                                                      { $$ = new SkyType($1); }
    | array_type_declaration                                        { $$ = new SkyType($1); }
    ;

array_type_declaration
    : var_type '[' INTEGER ']'                                      { $$ = new SkyArrayType($1, $3); }
    ;

var_type
    : TYPE_INT                                                      { $$ = new SkyVarType($1); }
    | TYPE_INT_POINTER                                              { $$ = new SkyVarType($1); }
    | TYPE_INT_64                                                   { $$ = new SkyVarType($1); }
    | TYPE_INT_64_POINTER                                           { $$ = new SkyVarType($1); }
    | TYPE_CHAR                                                     { $$ = new SkyVarType($1); }
    | TYPE_CHAR_POINTER                                             { $$ = new SkyVarType($1); }
    | TYPE_FLOAT                                                    { $$ = new SkyVarType($1); }
    | TYPE_FLOAT_POINTER                                            { $$ = new SkyVarType($1); }
    | TYPE_DOUBLE                                                   { $$ = new SkyVarType($1); }
    | TYPE_DOUBLE_POINTER                                           { $$ = new SkyVarType($1); }
    | TYPE_BOOL                                                     { $$ = new SkyVarType($1); }
    | TYPE_BOOL_POINTER                                             { $$ = new SkyVarType($1); }
    ;

func_declaration
    : FUNCTION name '(' var_list ')' '{' statement_list '}'         { $$ = new FuncDec($2, $4, $7); }
    | FUNCTION name '(' var_list ')' OP_PTR var_type '{' statement_list '}'
                                                                    { $$ = new FuncDec($2, $4, $7, $9); }
    ;

main_func
    : FUNCTION MAIN '(' var_list ')' OP_PTR return_type '{' statement_list '}'
                                                                    { $$ = new FuncDec(new Identifier(MAIN), $4, $7, $9); }
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
    : expression OP_OR expression_or             { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_OR, $3); }
    | expression_or                              { $$ = $1; }
    ;

expression_or
    : expression_or OP_AND expression_and        { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_AND, $3); }
    | expression_and                             { $$ = $1; }
    ;

expression_and
    : expression_and OP_EQ expr                  { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_EQ, $3); }
    | expression_and OP_NE expr                  { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_NE, $3); }
    | expression_and OP_GT expr                  { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_GT, $3); }
    | expression_and OP_LT expr                  { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_LT, $3); }
    | expression_and OP_GE expr                  { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_GE, $3); }
    | expression_and OP_LE expr                  { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_LE, $3); }
    | expr                                       { $$ = $1; }
    ;

expr
    : expr OP_LEFT expr_shift                    { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_LEFT, $3); }
    | expr OP_RIGHT expr_shift                   { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_RIGHT, $3); }
    | expr_shift                                 { $$ = $1; }
    ;

expr_shift
    : expr_shift  OP_PLUS term                   { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_PLUS, $3); }
    | expr_shift  OP_MINUS term                  { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_MINUS, $3); }
    | term                                       { $$ = $1; }
    ;

term
    : term OP_MUL factor                         { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_MUL, $3); }
    | term OP_DIV factor                         { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_DIV, $3); }
    | term OP_MOD factor                         { $$ = new BinaryExpression($1, BinaryExpr::BinaryOperator::OP_MOD, $3); }
    | factor                                     { $$ = $1; }
    ;

factor
    : OP_INC factor
    | factor OP_INC
    | OP_DEC factor
    | factor OP_DEC
    | OP_MINUS factor                            { $$ = new BinaryExpression(new Integer(0), BinaryExpression::BinaryOperator::OP_MINUS, $2); }
    | OP_NOT factor
    | number                                     { $$ = $1; }
    ;

number
    : number '[' expression ']'                  { $$ = new ArrayRef($1, $3); }
    | number '.' IDENTIFIER
    | '(' expression ')'                         { $$ = $2; }
    | number '(' expression_list ')'
    | const_value                                { $$ = $1; }
    | IDENTIFIER                                 { $$ = $1; }
    ;


expression_list
    : expression ',' expression_list
    | expression
    |
    ;

assign_statement
    : name assign_operator expression

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
    : var_type_list ',' name_list
    ;

var_type_list
    : var_type var_type_list
    ;

name_list
    : name name_list
    ;

name
    : IDENTIFIER                                                    { $$ = new Identifier($1); }

%%

