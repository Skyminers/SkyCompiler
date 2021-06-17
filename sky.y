%{
#include <string>
#include <cstdio>
#include "nodeList.h"

void yyerror(char *s){
    printf("[Error]: %s", s);
    return ;
}

extern int yylex();
Program * root;
%}

%union {
    int iVal;
    float fVal;
    double dVal;
    char cVal;
    char* sVal;
    bool bVal;
    Program *program;
    GlobalArea *globalArea;
    ConstDec *constDec;
    ConstDecList *constDecList;
    ConstValue *constValue;
    VarDec *varDec;
    VarDecList *varDecList;
    SkyType *skyType;
    SkyVarType *skyVarType;
    SkyArrayType *skyArrayType;
    FuncDec *funcDec;
    CompoundStat *compoundStat;
    StatList *statList;
    IfStat *ifStat;
    JumpStat *jumpStat;
    ExprNode *expression;
    ExprList *exprList;
    AssignStat *assignStat;
    Identifier *identifier;
    StatNode *statement;
    VarDecListNode *varDecListNode;
    ConstDecListNode *constDecListNode;
    SkyFuncType *skyFuncType;
}

%type<program>                          program
%type<globalArea>                       global_area
%type<constDec>                         const_expr
%type<constDecList>                     const_list
%type<constDecListNode>                 const_declaration
%type<constValue>                       const_value
%type<varDec>                           var_expr
%type<varDecList>                       var_list para_list
%type<varDecListNode>                   var_declaration
%type<skyType>                          type_declaration
%type<skyVarType>                       var_type
%type<skyArrayType>                     array_type_declaration
%type<funcDec>                          func_declaration main_func
%type<compoundStat>                     compound_statement
%type<statList>                         statement_list
%type<ifStat>                           branch_statement
%type<statement>                        for_statement statement
%type<jumpStat>                         jump_statement
%type<expression>                       expression_all expression expression_or expression_and expr expr_shift term factor number
%type<exprList>                         expression_list
%type<assignStat>                       assign_statement
%type<identifier>                       name
%type<skyFuncType>                      func_type lambda_expression

%token<iVal> INTEGER
%token<fVal> FLOAT
%token<dVal> DOUBLE
%token<cVal> CHAR
%token<sVal> STRING IDENTIFIER MAIN INIT DEL
%token<bVal> BOOLEAN

%token  PRINT SCAN
        VAR LET NEW DELETE LAMBDA
        FUNCTION JUMP_BREAK JUMP_CONTINUE JUMP_RETURN
        IF ELSE FOR WHILE IN
        CLASS THIS
        TYPE_INT TYPE_INT_POINTER TYPE_INT_64 TYPE_INT_64_POINTER
        TYPE_CHAR TYPE_CHAR_POINTER
        TYPE_FLOAT TYPE_FLOAT_POINTER TYPE_DOUBLE TYPE_DOUBLE_POINTER
        TYPE_BOOL TYPE_BOOL_POINTER
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
        OPER_PLUS OPER_MINUS OPER_DIV OPER_MOD OPER_RIGHT OPER_LEFT OPER_PTR OPER_AND OPER_OR OPER_NOT
        OPER_LT OPER_LE OPER_GT OPER_GE OPER_EQ OPER_NE
        LF

%%

program
    : global_area main_func                                 { $$ = new Program($1, $2); root = $$;}
    ;

global_area
    : global_area const_declaration ';'                     { $$ = $1; $$->addConstDec($2->constDecList); }
    | global_area var_declaration ';'                       { $$ = $1; $$->addVarDec($2->varDecList); }
    | global_area func_declaration                          { $$ = $1; $$->addFuncDec($2); }
    |                                                       { $$ = new GlobalArea(); }
    ;

const_declaration
    : LET const_list                                        { $$ = new ConstDecListNode($2); }
    ;

const_list
    : const_list ',' const_expr                             { $$ = $1; $$->push_back($3); }
    | const_expr                                            { $$ = new ConstDecList(); $$->push_back($1); }
    ;

const_expr
    : name '=' const_value                                  { $$ = new ConstDec($1, $3); }
    ;

const_value
    : INTEGER                                               { $$ = new SkyInt($1); }
    | FLOAT                                                 { $$ = new SkyFloat($1); }
    | DOUBLE                                                { $$ = new SkyDouble($1); }
    | CHAR                                                  { $$ = new SkyChar($1); }
    | BOOLEAN                                               { $$ = new SkyBool($1); }
    | STRING                                                { $$ = new SkyCharPointer($1); }
    ;

var_declaration
    : VAR var_list                                          { $$ = new VarDecListNode($2); }
    ;

para_list
    :                                                       { $$ = new VarDecList(); }
    | var_list                                              { $$ = $1; }
    ;

var_list
    : var_list ',' var_expr                                 { $$ = $1; $$->push_back($3); }
    | var_expr                                              { $$ = new VarDecList(); $$->push_back($1); }
    ;

var_expr
    : name '=' expression_all                               { $$ = new VarDec($1, new SkyType(new SkyAutoType()), $3); }
    | name ':' type_declaration                             { $$ = new VarDec($1, $3, nullptr); }
    | name                                                  { $$ = new VarDec($1, new SkyType(new SkyAutoType()), nullptr); }
    ;

type_declaration
    : var_type                                              { $$ = new SkyType($1); }
    | array_type_declaration                                { $$ = new SkyType($1); }
    | func_type                                             { $$ = new SkyType($1); }
    ;

array_type_declaration
    : var_type '[' INTEGER ']'                              { $$ = new SkyArrayType(new SkyType($1), $3); }
    ;

func_type
    : FUNCTION                                              { $$ = new SkyFuncType(); }
    ;

var_type
    : TYPE_INT                                              { $$ = new SkyVarType(SkyVarType::SKY_INT); }
    | TYPE_INT_POINTER                                      { $$ = new SkyVarType(SkyVarType::SKY_INT_POINTER); }
    | TYPE_INT_64                                           { $$ = new SkyVarType(SkyVarType::SKY_INT_64); }
    | TYPE_INT_64_POINTER                                   { $$ = new SkyVarType(SkyVarType::SKY_INT_64_POINTER); }
    | TYPE_CHAR                                             { $$ = new SkyVarType(SkyVarType::SKY_CHAR); }
    | TYPE_CHAR_POINTER                                     { $$ = new SkyVarType(SkyVarType::SKY_CHAR_POINTER); }
    | TYPE_FLOAT                                            { $$ = new SkyVarType(SkyVarType::SKY_FLOAT); }
    | TYPE_FLOAT_POINTER                                    { $$ = new SkyVarType(SkyVarType::SKY_FLOAT_POINTER); }
    | TYPE_DOUBLE                                           { $$ = new SkyVarType(SkyVarType::SKY_DOUBLE); }
    | TYPE_DOUBLE_POINTER                                   { $$ = new SkyVarType(SkyVarType::SKY_DOUBLE_POINTER); }
    | TYPE_BOOL                                             { $$ = new SkyVarType(SkyVarType::SKY_BOOL); }
    | TYPE_BOOL_POINTER                                     { $$ = new SkyVarType(SkyVarType::SKY_BOOL_POINTER); }
    ;

func_declaration
    : FUNCTION name '(' para_list ')' compound_statement    { $$ = new FuncDec($2, new SkyFuncType($4, $6)); }
    | FUNCTION name '(' para_list ')' OPER_PTR var_type compound_statement  { $$ = new FuncDec($2, new SkyFuncType($4, new SkyType($7), $8)); }
    ;

main_func
    : FUNCTION MAIN '(' ')' OPER_PTR TYPE_INT compound_statement    { $$ = new FuncDec(new Identifier($2), new SkyFuncType(nullptr, new SkyType(new SkyVarType(SkyVarType::SKY_INT)), $7)); }
    ;

statement_list
    : statement_list statement                              { $$ = $1; $$->push_back($2); }
    |                                                       { $$ = new StatList(); }
    ;

statement
    : compound_statement                                    { $$ = $1; }
    | branch_statement                                      { $$ = $1; }
    | for_statement                                         { $$ = $1; }
    | jump_statement ';'                                    { $$ = $1; }
    | assign_statement ';'                                  { $$ = $1; }
    | var_declaration ';'                                   { $$ = $1; }
    | const_declaration ';'                                 { $$ = $1; }
    | name '(' expression_list ')' ';'                      { $$ = new FuncCall($1, $3); }
    ;

compound_statement
    : '{' statement_list '}'                                { $$ = new CompoundStat($2); }
    ;

branch_statement
    : IF '(' expression ')' compound_statement              { $$ = new IfStat($3, $5, nullptr); }
    | IF '(' expression ')' compound_statement ELSE compound_statement  { $$ = new IfStat($3, $5, $7); }
    ;

for_statement
    : WHILE '(' expression ')' compound_statement           { $$ = new WhileStat($3, $5); }
    | FOR name IN '[' expression ',' expression ',' expression ']' compound_statement    { $$ = new ForStat($2, $5, $7, $9, $11); }
    ;

jump_statement
    : JUMP_BREAK                                             { $$ = new JumpStat(TypeOfJump::BREAK, nullptr); }
    | JUMP_CONTINUE                                          { $$ = new JumpStat(TypeOfJump::CONTINUE, nullptr); }
    | JUMP_RETURN                                            { $$ = new JumpStat(TypeOfJump::RETURN, nullptr); }
    | JUMP_RETURN expression                                 { $$ = new JumpStat(TypeOfJump::RETURN, $2); }
    ;

expression_all
    : expression                                            { $$ = $1; }
    | lambda_expression                                     { $$ = $1; }
    ;

expression
    : expression OPER_OR expression_or                      { $$ = new BinaryExpr($1, BinaryOperators::OP_OR, $3); }
    | expression_or                                         { $$ = $1; }
    ;

expression_or
    : expression_or OPER_AND expression_and                 { $$ = new BinaryExpr($1, BinaryOperators::OP_AND, $3); }
    | expression_and                                        { $$ = $1; }
    ;

expression_and
    : expression_and OPER_EQ expr                           { $$ = new BinaryExpr($1, BinaryOperators::OP_EQ, $3); }
    | expression_and OPER_NE expr                           { $$ = new BinaryExpr($1, BinaryOperators::OP_NE, $3); }
    | expression_and OPER_GT expr                           { $$ = new BinaryExpr($1, BinaryOperators::OP_GT, $3); }
    | expression_and OPER_LT expr                           { $$ = new BinaryExpr($1, BinaryOperators::OP_LT, $3); }
    | expression_and OPER_GE expr                           { $$ = new BinaryExpr($1, BinaryOperators::OP_GE, $3); }
    | expression_and OPER_LE expr                           { $$ = new BinaryExpr($1, BinaryOperators::OP_LE, $3); }
    | expr                                                  { $$ = $1; }
    ;

expr
    : expr OPER_LEFT expr_shift                             { $$ = new BinaryExpr($1, BinaryOperators::OP_LEFT, $3); }
    | expr OPER_RIGHT expr_shift                            { $$ = new BinaryExpr($1, BinaryOperators::OP_RIGHT, $3); }
    | expr_shift                                            { $$ = $1; }
    ;

expr_shift
    : expr_shift OPER_PLUS term                             { $$ = new BinaryExpr($1, BinaryOperators::OP_PLUS, $3); }
    | expr_shift OPER_MINUS term                            { $$ = new BinaryExpr($1, BinaryOperators::OP_MINUS, $3); }
    | term                                                  { $$ = $1; }
    ;

term
    : term '*' factor                                       { $$ = new BinaryExpr($1, BinaryOperators::OP_MUL, $3); }
    | term OPER_DIV factor                                  { $$ = new BinaryExpr($1, BinaryOperators::OP_DIV, $3); }
    | term OPER_MOD factor                                  { $$ = new BinaryExpr($1, BinaryOperators::OP_MOD, $3); }
    | factor                                                { $$ = $1; }
    ;

factor
    : OPER_MINUS factor                                     { $$ = new BinaryExpr(new SkyInt(0), BinaryOperators::OP_MINUS, $2); }
    | OPER_NOT factor                                       { $$ = new BinaryExpr(new SkyBool(true), BinaryOperators::OP_XOR, $2); }
    | number                                                { $$ = $1; }
    ;

number
    : name '[' expression ']'                               { $$ = new ArrayReference($1, $3); }
    | '(' expression ')'                                    { $$ = $2; }
    | name '(' expression_list ')'                          { $$ = new FuncCall($1, $3); }
    | const_value                                           { $$ = $1; }
    | name                                                  { $$ = $1; }
    | '&' name                                              { $$ = new ReferenceNode($2); }
    | '&' name '[' expression ']'                           { $$ = new ReferenceNode(new ArrayReference($2, $4)); }
    ;

expression_list
    : expression_list ',' expression_all                    { $$ = $1; $$->push_back($3); }
    | expression_all                                        { $$ = new ExprList(); $$->push_back($1); }
    |                                                       { $$ = nullptr; }
    ;

lambda_expression
    : LAMBDA '(' para_list ')' ':' var_type OPER_PTR compound_statement     { $$ = new SkyFuncType($3, new SkyType($6), $8); }
    | LAMBDA '(' para_list ')' ':' var_type OPER_PTR expression             { $$ = new SkyFuncType($3, new SkyType($6), new CompoundStat());
                                                                              $$->body->statList->push_back(new JumpStat(TypeOfJump::RETURN, $8)); }
    | LAMBDA '(' para_list ')' OPER_PTR compound_statement  { $$ = new SkyFuncType($3, new SkyType(new SkyAutoType()), $6); }
    | LAMBDA '(' para_list ')' OPER_PTR expression          { $$ = new SkyFuncType($3, new SkyType(new SkyAutoType()), new CompoundStat());
                                                              $$->body->statList->push_back(new JumpStat(TypeOfJump::RETURN, $6)); }
    ;

assign_statement
    : name '=' expression_all                               { $$ = new AssignStat($1, $3); }
    | name '[' expression ']' '=' expression                { $$ = new AssignStat(new ArrayReference($1, $3), $6); }
    ;

name
    : IDENTIFIER                                            { $$ = new Identifier($1); }
    ;

%%

