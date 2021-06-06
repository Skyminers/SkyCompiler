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
     FUNCTION = 274,
     JUMP_BREAK = 275,
     JUMP_CONTINUE = 276,
     JUMP_RETURN = 277,
     IF = 278,
     ELSE = 279,
     FOR = 280,
     WHILE = 281,
     IN = 282,
     CLASS = 283,
     THIS = 284,
     TYPE_INT = 285,
     TYPE_INT_POINTER = 286,
     TYPE_INT_64 = 287,
     TYPE_INT_64_POINTER = 288,
     TYPE_CHAR = 289,
     TYPE_CHAR_POINTER = 290,
     TYPE_FLOAT = 291,
     TYPE_FLOAT_POINTER = 292,
     TYPE_DOUBLE = 293,
     TYPE_DOUBLE_POINTER = 294,
     TYPE_BOOL = 295,
     TYPE_BOOL_POINTER = 296,
     ADD_ASSIGN = 297,
     SUB_ASSIGN = 298,
     MUL_ASSIGN = 299,
     DIV_ASSIGN = 300,
     MOD_ASSIGN = 301,
     AND_ASSIGN = 302,
     XOR_ASSIGN = 303,
     OR_ASSIGN = 304,
     OPER_PLUS = 305,
     OPER_MINUS = 306,
     OPER_DIV = 307,
     OPER_MOD = 308,
     OPER_RIGHT = 309,
     OPER_LEFT = 310,
     OPER_PTR = 311,
     OPER_AND = 312,
     OPER_OR = 313,
     OPER_NOT = 314,
     OPER_LT = 315,
     OPER_LE = 316,
     OPER_GT = 317,
     OPER_GE = 318,
     OPER_EQ = 319,
     OPER_NE = 320,
     LF = 321
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
#define FUNCTION 274
#define JUMP_BREAK 275
#define JUMP_CONTINUE 276
#define JUMP_RETURN 277
#define IF 278
#define ELSE 279
#define FOR 280
#define WHILE 281
#define IN 282
#define CLASS 283
#define THIS 284
#define TYPE_INT 285
#define TYPE_INT_POINTER 286
#define TYPE_INT_64 287
#define TYPE_INT_64_POINTER 288
#define TYPE_CHAR 289
#define TYPE_CHAR_POINTER 290
#define TYPE_FLOAT 291
#define TYPE_FLOAT_POINTER 292
#define TYPE_DOUBLE 293
#define TYPE_DOUBLE_POINTER 294
#define TYPE_BOOL 295
#define TYPE_BOOL_POINTER 296
#define ADD_ASSIGN 297
#define SUB_ASSIGN 298
#define MUL_ASSIGN 299
#define DIV_ASSIGN 300
#define MOD_ASSIGN 301
#define AND_ASSIGN 302
#define XOR_ASSIGN 303
#define OR_ASSIGN 304
#define OPER_PLUS 305
#define OPER_MINUS 306
#define OPER_DIV 307
#define OPER_MOD 308
#define OPER_RIGHT 309
#define OPER_LEFT 310
#define OPER_PTR 311
#define OPER_AND 312
#define OPER_OR 313
#define OPER_NOT 314
#define OPER_LT 315
#define OPER_LE 316
#define OPER_GT 317
#define OPER_GE 318
#define OPER_EQ 319
#define OPER_NE 320
#define LF 321




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
}
/* Line 1529 of yacc.c.  */
#line 215 "sky.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

