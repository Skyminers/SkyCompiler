/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     FLOAT = 259,
     DOUBLE = 260,
     CHAR = 261,
     STRING = 262,
     IDENTIFIER = 263,
     MAIN = 264,
     INIT = 265,
     DEL = 266,
     BOOLEAN = 267,
     PRINT = 268,
     SCAN = 269,
     VAR = 270,
     LET = 271,
     NEW = 272,
     DELETE = 273,
     LAMBDA = 274,
     FUNCTION = 275,
     JUMP_BREAK = 276,
     JUMP_CONTINUE = 277,
     JUMP_RETURN = 278,
     IF = 279,
     ELSE = 280,
     FOR = 281,
     WHILE = 282,
     IN = 283,
     CLASS = 284,
     THIS = 285,
     TYPE_INT = 286,
     TYPE_INT_POINTER = 287,
     TYPE_INT_64 = 288,
     TYPE_INT_64_POINTER = 289,
     TYPE_CHAR = 290,
     TYPE_CHAR_POINTER = 291,
     TYPE_FLOAT = 292,
     TYPE_FLOAT_POINTER = 293,
     TYPE_DOUBLE = 294,
     TYPE_DOUBLE_POINTER = 295,
     TYPE_BOOL = 296,
     TYPE_BOOL_POINTER = 297,
     ADD_ASSIGN = 298,
     SUB_ASSIGN = 299,
     MUL_ASSIGN = 300,
     DIV_ASSIGN = 301,
     MOD_ASSIGN = 302,
     AND_ASSIGN = 303,
     XOR_ASSIGN = 304,
     OR_ASSIGN = 305,
     OPER_PLUS = 306,
     OPER_MINUS = 307,
     OPER_DIV = 308,
     OPER_MOD = 309,
     OPER_RIGHT = 310,
     OPER_LEFT = 311,
     OPER_PTR = 312,
     OPER_AND = 313,
     OPER_OR = 314,
     OPER_NOT = 315,
     OPER_LT = 316,
     OPER_LE = 317,
     OPER_GT = 318,
     OPER_GE = 319,
     OPER_EQ = 320,
     OPER_NE = 321,
     LF = 322
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define FLOAT 259
#define DOUBLE 260
#define CHAR 261
#define STRING 262
#define IDENTIFIER 263
#define MAIN 264
#define INIT 265
#define DEL 266
#define BOOLEAN 267
#define PRINT 268
#define SCAN 269
#define VAR 270
#define LET 271
#define NEW 272
#define DELETE 273
#define LAMBDA 274
#define FUNCTION 275
#define JUMP_BREAK 276
#define JUMP_CONTINUE 277
#define JUMP_RETURN 278
#define IF 279
#define ELSE 280
#define FOR 281
#define WHILE 282
#define IN 283
#define CLASS 284
#define THIS 285
#define TYPE_INT 286
#define TYPE_INT_POINTER 287
#define TYPE_INT_64 288
#define TYPE_INT_64_POINTER 289
#define TYPE_CHAR 290
#define TYPE_CHAR_POINTER 291
#define TYPE_FLOAT 292
#define TYPE_FLOAT_POINTER 293
#define TYPE_DOUBLE 294
#define TYPE_DOUBLE_POINTER 295
#define TYPE_BOOL 296
#define TYPE_BOOL_POINTER 297
#define ADD_ASSIGN 298
#define SUB_ASSIGN 299
#define MUL_ASSIGN 300
#define DIV_ASSIGN 301
#define MOD_ASSIGN 302
#define AND_ASSIGN 303
#define XOR_ASSIGN 304
#define OR_ASSIGN 305
#define OPER_PLUS 306
#define OPER_MINUS 307
#define OPER_DIV 308
#define OPER_MOD 309
#define OPER_RIGHT 310
#define OPER_LEFT 311
#define OPER_PTR 312
#define OPER_AND 313
#define OPER_OR 314
#define OPER_NOT 315
#define OPER_LT 316
#define OPER_LE 317
#define OPER_GT 318
#define OPER_GE 319
#define OPER_EQ 320
#define OPER_NE 321
#define LF 322




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "sky.y"
{
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
    ClassDec *classDec;
    Identifier *identifier;
    ClassBody *classBody;
    FuncDecList *funcDecList;
    StatNode *statement;
    VarDecListNode *varDecListNode;
    ConstDecListNode *constDecListNode;
    SkyFuncType *skyFuncType;
}
/* Line 1529 of yacc.c.  */
#line 218 "sky.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

