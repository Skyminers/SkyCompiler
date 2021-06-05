%{
#include <string>
#include <cstdio>
#include "nodeList.h"

void yyerror(char *s){
    printf("[Error]: %s", s);
    return ;
}

extern int yylex();
%}

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
    ClassDec *classDec;
    Identifier *identifier;
    ClassBody *classBody;
    FuncDecList *funcDecList;
    StatNode *statement;
}

%type<program>                          program
%type<globalArea>                       global_area
%type<constDec>                         const_expr
%type<constDecList>                     const_declaration const_list
%type<constValue>                       const_value
%type<varDec>                           var_expr
%type<varDecList>                       var_declaration var_list
%type<skyType>                          type_declaration
%type<skyVarType>                       var_type
%type<skyArrayType>                     array_type_declaration
%type<funcDec>                          func_declaration main_func class_init class_del
%type<compoundStat>                     compound_statement
%type<statList>                         statement_list
%type<ifStat>                           branch_statement
%type<statement>                        for_statement statement
%type<jumpStat>                         jump_statement
%type<expression>                       expression expression_or expression_and expr expr_shift term factor number
%type<exprList>                         expression_list
%type<assignStat>                       assign_statement
%type<classDec>                         class_declaration
%type<identifier>                       inherit_part name
%type<classBody>                        class_body
%type<funcDecList>                      func_declaration_list

%token<iVal> INTEGER
%token<fVal> FLOAT
%token<dVal> DOUBLE
%token<cVal> CHAR
%token<sVal> STRING IDENTIFIER
%token<bVal> BOOLEAN

%token  MAIN PRINT SCAN
        VAR LET NEW DELETE
        FUNCTION BREAK CONTINUE RETURN
        IF ELSE FOR WHILE IN
        CLASS INIT DEL THIS
        TYPE_INT TYPE_INT_POINTER TYPE_INT_64 TYPE_INT_64_POINTER
        TYPE_CHAR TYPE_CHAR_POINTER
        TYPE_FLOAT TYPE_FLOAT_POINTER TYPE_DOUBLE TYPE_DOUBLE_POINTER
        TYPE_BOOL TYPE_BOOL_POINTER
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
        OP_PLUS OP_MINUS OP_DIV OP_MOD OP_RIGHT OP_LEFT OP_PTR OP_AND OP_OR OP_NOT
        OP_LT OP_LE OP_GT OP_GE OP_EQ OP_NE
        LF

%%

program
    : global_area main_func                                 { $$ = new Program($1, $2); }
    ;

global_area
    : global_area const_declaration                         { $$ = $1; $$->addConstDec($2); }
    | global_area var_declaration                           { $$ = $1; $$->addVarDec($2); }
    | global_area func_declaration                          { $$ = $1; $$->addFuncDec($2); }
    | global_area class_declaration                         { $$ = $1; $$->addClassDec($2); }
    |                                                       { $$ = new GlobalArea(); }
    ;

const_declaration
    : LET const_list                                        { $$ = $2; }
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
    : VAR var_list                                          { $$ = $2; }
    ;

var_list
    : var_list ',' var_expr                                 { $$ = $1; $$->push_back($3); }
    | var_expr                                              { $$ = new VarDecList(); $$->push_back($1); }
    ;

var_expr
    : name '=' expression                                   { $$ = new VarDec($1, nullptr, $3); }
    | name ':' type_declaration                             { $$ = new VarDec($1, $3, nullptr); }
    ;

type_declaration
    : var_type                                              { $$ = new SkyType($1); }
    | array_type_declaration                                { $$ = new SkyType($1); }
    ;

array_type_declaration
    : var_type '[' INTEGER ']'                              { $$ = new SkyArrayType(new SkyType($1), $3); }
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
    : FUNCTION name '(' var_list ')' compound_statement     { $$ = new FuncDec($2, $4, $6); }
    | FUNCTION name '(' var_list ')' OP_PTR var_type compound_statement     { $$ = new FuncDec($2, $4, $7, $8); }
    ;

main_func
    : FUNCTION MAIN '(' ')' OP_PTR TYPE_INT compound_statement     { $$ = new FuncDec(new Identifier(MAIN), nullptr, new SkyVarType(SkyVarType::SKY_INT), $7); }
    ;

statement_list
    : statement_list LF statement                           { $$ = $1; $$->push_back($3); }
    | statement                                             { $$ = new StatList(); $$->push_back($1); }
    |                                                       { $$ = new StatList(); }
    ;

statement
    : compound_statement                                    { $$ = $1; }
    | branch_statement                                      { $$ = $1; }
    | for_statement                                         { $$ = $1; }
    | expression                                            { $$ = $1; }
    | jump_statement                                        { $$ = $1; }
    | assign_statement                                      { $$ = $1; }
    | var_declaration                                       { $$ = $1; }
    | const_declaration                                     { $$ = $1; }
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
    : BREAK                                                 { $$ = new JumpStat(TypeOfJump::BREAK, nullptr); }
    | CONTINUE                                              { $$ = new JumpStat(TypeOfJump::CONTINUE, nullptr); }
    | RETURN                                                { $$ = new JumpStat(TypeOfJump::RETURN, nullptr); }
    | RETURN expression                                     { $$ = new JumpStat(TypeOfJump::RETURN, $2); }
    ;

expression
    : expression OP_OR expression_or                        { $$ = new BinaryExpr($1, BinaryOperators::OP_OR, $3); }
    | expression_or                                         { $$ = $1; }
    ;

expression_or
    : expression_or OP_AND expression_and                   { $$ = new BinaryExpr($1, BinaryOperators::OP_AND, $3); }
    | expression_and                                        { $$ = $1; }
    ;

expression_and
    : expression_and OP_EQ expr                             { $$ = new BinaryExpr($1, BinaryOperators::OP_EQ, $3); }
    | expression_and OP_NE expr                             { $$ = new BinaryExpr($1, BinaryOperators::OP_NE, $3); }
    | expression_and OP_GT expr                             { $$ = new BinaryExpr($1, BinaryOperators::OP_GT, $3); }
    | expression_and OP_LT expr                             { $$ = new BinaryExpr($1, BinaryOperators::OP_LT, $3); }
    | expression_and OP_GE expr                             { $$ = new BinaryExpr($1, BinaryOperators::OP_GE, $3); }
    | expression_and OP_LE expr                             { $$ = new BinaryExpr($1, BinaryOperators::OP_LE, $3); }
    | expr                                                  { $$ = $1; }
    ;

expr
    : expr OP_LEFT expr_shift                               { $$ = new BinaryExpr($1, BinaryOperators::OP_LEFT, $3); }
    | expr OP_RIGHT expr_shift                              { $$ = new BinaryExpr($1, BinaryOperators::OP_RIGHT, $3); }
    | expr_shift                                            { $$ = $1; }
    ;

expr_shift
    : expr_shift OP_PLUS term                              { $$ = new BinaryExpr($1, BinaryOperators::OP_PLUS, $3); }
    | expr_shift OP_MINUS term                             { $$ = new BinaryExpr($1, BinaryOperators::OP_MINUS, $3); }
    | term                                                  { $$ = $1; }
    ;

term
    : term '*' factor                                       { $$ = new BinaryExpr($1, BinaryOperators::OP_MUL, $3); }
    | term OP_DIV factor                                    { $$ = new BinaryExpr($1, BinaryOperators::OP_DIV, $3); }
    | term OP_MOD factor                                    { $$ = new BinaryExpr($1, BinaryOperators::OP_MOD, $3); }
    | factor                                                { $$ = $1; }
    ;

factor
    : OP_MINUS factor                                       { $$ = new BinaryExpr(new Integer(0), BinaryOperators::OP_MINUS, $2); }
    | OP_NOT factor                                         { $$ = new BinaryExpr(new Boolean(true), BinaryOperators::OP_XOR, $2); }
    | number                                                { $$ = $1; }
    ;

number
    : name '[' expression ']'                               { $$ = new ArrayReference($1, $3); }
    | name '.' name                                         { $$ = new ClassRef($1, $3); }
    | '(' expression ')'                                    { $$ = $2; }
    | name '(' expression_list ')'                          { $$ = new FuncCall($1, $3); }
    | const_value                                           { $$ = $1; }
    | name                                                  { $$ = $1; }
    | '*' name '[' expression ']'                           { $$ = new PointerNode(new ArrayReference($2, $4)); }
    | '*' name '.' name                                     { $$ = new PointerNode(new ClassRef($2, $4)); }
    | '*' name '(' expression_list ')'                      { $$ = new PointerNode(new FuncCall($2, $4)); }
    | '*' name                                              { $$=  new PointerNode($2); }
    | '*' '(' expression ')'                                { $$ = new PointerNode($3); }
    | '&' name                                              { $$ = new ReferenceNode($2); }
    ;

expression_list
    : expression_list ',' expression                        { $$ = $1; $$->push_back($3); }
    | expression                                            { $$ = new ExprList(); $$->push_back($1); }
    |                                                       { $$ = nullptr; }
    ;

assign_statement
    : name '=' expression                                   { $$ = new AssignStat($1, $3); }
    | name '[' expression ']' '=' expression                { $$ = new AssignStat($1, $3, $6); }
    | name '.' name '=' expression                          { $$ = new AssignStat($1, $3, $5); }
    | '*' name '=' expression                               { $$ = new AssignStat(new PointerNode($2), $4); }
    | '*' name '[' expression ']' '=' expression            { $$ = new AssignStat(new PointerNode(new ArrayReference($2, $4)), $7); }
    | '*' name '.' name '=' expression                      { $$ = new AssignStat(new PointerNode(new ClassRef($2, $4)), $6); }
    | '*' '(' expression ')' '=' expression                 { $$ = new AssignStat(new PointerNode($3), $6); }
    ;

name
    : IDENTIFIER                                            { $$ = new Identifier($1); }
    ;

class_declaration
    : CLASS name inherit_part '{' class_body '}'            { $$ = new ClassDec($2, $3, $5); }
    ;

inherit_part
    : ':' name                                              { $$ = $2; }
    |                                                       { $$ = nullptr; }
    ;

class_body
    : class_init class_del func_declaration_list            { $$ = new ClassBody($1, $2, $3); }
    ;

class_init
    : FUNCTION INIT '(' var_list ')' OP_PTR var_type compound_statement     { $$ = new FuncDec(new Identifier(INIT), $4, $7, $8); }
    ;

class_del
    : FUNCTION DEL '(' var_list ')' OP_PTR var_type compound_statement      { $$ = new FuncDec(new Identifier(DEL), $4, $7, $8); }
    ;

func_declaration_list
    : func_declaration_list func_declaration                { $$ = $1; $$->push_back($2); }
    |                                                       { $$ = new FuncDecList(); }

%%

