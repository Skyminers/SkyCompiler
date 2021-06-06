/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "sky.y"

#include <string>
#include <cstdio>
#include "nodeList.h"

void yyerror(char *s){
    printf("[Error]: %s", s);
    return ;
}

extern int yylex();
Program * root;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 276 "sky.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 289 "sky.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   213

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNRULES -- Number of states.  */
#define YYNSTATES  216

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,     2,
      72,    73,    77,     2,    67,     2,    78,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    74,
       2,    68,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    71,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,     2,    76,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    18,    19,    22,
      26,    28,    32,    34,    36,    38,    40,    42,    44,    47,
      51,    53,    57,    61,    63,    65,    70,    72,    74,    76,
      78,    80,    82,    84,    86,    88,    90,    92,    94,   101,
     110,   118,   122,   125,   126,   128,   130,   132,   134,   136,
     138,   140,   144,   150,   158,   164,   176,   178,   180,   182,
     185,   189,   191,   195,   197,   201,   205,   209,   213,   217,
     221,   223,   227,   231,   233,   237,   241,   243,   247,   251,
     255,   257,   260,   263,   265,   270,   274,   278,   283,   285,
     287,   293,   298,   304,   307,   312,   315,   319,   321,   322,
     326,   333,   335,   342,   345,   346,   350,   359,   368,   371
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      81,     0,    -1,    82,    94,    -1,    82,    83,    -1,    82,
      87,    -1,    82,    93,    -1,    82,   112,    -1,    -1,    16,
      84,    -1,    84,    67,    85,    -1,    85,    -1,   111,    68,
      86,    -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,
      12,    -1,     7,    -1,    15,    88,    -1,    88,    67,    89,
      -1,    89,    -1,   111,    68,   101,    -1,   111,    69,    90,
      -1,    92,    -1,    91,    -1,    92,    70,     3,    71,    -1,
      30,    -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,
      40,    -1,    41,    -1,    19,   111,    72,    88,    73,    97,
      -1,    19,   111,    72,    88,    73,    56,    92,    97,    -1,
      19,     9,    72,    73,    56,    30,    97,    -1,    95,    74,
      96,    -1,    96,    74,    -1,    -1,    97,    -1,    98,    -1,
      99,    -1,   100,    -1,   110,    -1,    87,    -1,    83,    -1,
      75,    95,    76,    -1,    23,    72,   101,    73,    97,    -1,
      23,    72,   101,    73,    97,    24,    97,    -1,    26,    72,
     101,    73,    97,    -1,    25,   111,    27,    70,   101,    67,
     101,    67,   101,    71,    97,    -1,    20,    -1,    21,    -1,
      22,    -1,    22,   101,    -1,   101,    58,   102,    -1,   102,
      -1,   102,    57,   103,    -1,   103,    -1,   103,    64,   104,
      -1,   103,    65,   104,    -1,   103,    62,   104,    -1,   103,
      60,   104,    -1,   103,    63,   104,    -1,   103,    61,   104,
      -1,   104,    -1,   104,    55,   105,    -1,   104,    54,   105,
      -1,   105,    -1,   105,    50,   106,    -1,   105,    51,   106,
      -1,   106,    -1,   106,    77,   107,    -1,   106,    52,   107,
      -1,   106,    53,   107,    -1,   107,    -1,    51,   107,    -1,
      59,   107,    -1,   108,    -1,   111,    70,   101,    71,    -1,
     111,    78,   111,    -1,    72,   101,    73,    -1,   111,    72,
     109,    73,    -1,    86,    -1,   111,    -1,    77,   111,    70,
     101,    71,    -1,    77,   111,    78,   111,    -1,    77,   111,
      72,   109,    73,    -1,    77,   111,    -1,    77,    72,   101,
      73,    -1,    79,   111,    -1,   109,    67,   101,    -1,   101,
      -1,    -1,   111,    68,   101,    -1,   111,    70,   101,    71,
      68,   101,    -1,     8,    -1,    28,   111,   113,    75,   114,
      76,    -1,    69,   111,    -1,    -1,   115,   116,   117,    -1,
      19,    10,    72,    88,    73,    56,    92,    97,    -1,    19,
      11,    72,    88,    73,    56,    92,    97,    -1,   117,    93,
      -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,   103,   104,   105,   106,   107,   111,   115,
     116,   120,   124,   125,   126,   127,   128,   129,   133,   137,
     138,   142,   143,   147,   148,   152,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   171,   172,
     176,   180,   181,   182,   186,   187,   188,   189,   190,   191,
     192,   196,   200,   201,   205,   206,   210,   211,   212,   213,
     217,   218,   222,   223,   227,   228,   229,   230,   231,   232,
     233,   237,   238,   239,   243,   244,   245,   249,   250,   251,
     252,   256,   257,   258,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   277,   278,   279,   283,
     284,   288,   292,   296,   297,   301,   305,   309,   313,   314
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "FLOAT", "DOUBLE", "CHAR",
  "STRING", "IDENTIFIER", "MAIN", "INIT", "DEL", "BOOLEAN", "PRINT",
  "SCAN", "VAR", "LET", "NEW", "DELETE", "FUNCTION", "JUMP_BREAK",
  "JUMP_CONTINUE", "JUMP_RETURN", "IF", "ELSE", "FOR", "WHILE", "IN",
  "CLASS", "THIS", "TYPE_INT", "TYPE_INT_POINTER", "TYPE_INT_64",
  "TYPE_INT_64_POINTER", "TYPE_CHAR", "TYPE_CHAR_POINTER", "TYPE_FLOAT",
  "TYPE_FLOAT_POINTER", "TYPE_DOUBLE", "TYPE_DOUBLE_POINTER", "TYPE_BOOL",
  "TYPE_BOOL_POINTER", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN",
  "OPER_PLUS", "OPER_MINUS", "OPER_DIV", "OPER_MOD", "OPER_RIGHT",
  "OPER_LEFT", "OPER_PTR", "OPER_AND", "OPER_OR", "OPER_NOT", "OPER_LT",
  "OPER_LE", "OPER_GT", "OPER_GE", "OPER_EQ", "OPER_NE", "LF", "','",
  "'='", "':'", "'['", "']'", "'('", "')'", "';'", "'{'", "'}'", "'*'",
  "'.'", "'&'", "$accept", "program", "global_area", "const_declaration",
  "const_list", "const_expr", "const_value", "var_declaration", "var_list",
  "var_expr", "type_declaration", "array_type_declaration", "var_type",
  "func_declaration", "main_func", "statement_list", "statement",
  "compound_statement", "branch_statement", "for_statement",
  "jump_statement", "expression", "expression_or", "expression_and",
  "expr", "expr_shift", "term", "factor", "number", "expression_list",
  "assign_statement", "name", "class_declaration", "inherit_part",
  "class_body", "class_init", "class_del", "func_declaration_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,    44,    61,    58,
      91,    93,    40,    41,    59,   123,   125,    42,    46,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    82,    82,    83,    84,
      84,    85,    86,    86,    86,    86,    86,    86,    87,    88,
      88,    89,    89,    90,    90,    91,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    93,    93,
      94,    95,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    97,    98,    98,    99,    99,   100,   100,   100,   100,
     101,   101,   102,   102,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   104,   105,   105,   105,   106,   106,   106,
     106,   107,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   109,   109,   109,   110,
     110,   111,   112,   113,   113,   114,   115,   116,   117,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     0,     2,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     2,     3,
       1,     3,     3,     1,     1,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     6,     8,
       7,     3,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     3,     5,     7,     5,    11,     1,     1,     1,     2,
       3,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     1,     4,     3,     3,     4,     1,     1,
       5,     4,     5,     2,     4,     2,     3,     1,     0,     3,
       6,     1,     6,     2,     0,     3,     8,     8,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,     0,     0,     1,     0,     0,     0,     0,     3,     4,
       5,     2,     6,   101,    18,    20,     0,     8,    10,     0,
       0,     0,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,    12,    13,    14,    15,    17,    16,     0,
       0,     0,     0,     0,    88,    21,    61,    63,    70,    73,
      76,    80,    83,    89,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    22,    24,    23,     9,
      11,     0,     0,   103,     0,    81,    82,     0,     0,    93,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    98,     0,     0,
       0,     0,     0,     0,     0,    86,     0,     0,    98,     0,
      60,    62,    67,    69,    66,    68,    64,    65,    72,    71,
      74,    75,    78,    79,    77,     0,    97,     0,    85,     0,
       0,     0,    43,    38,     0,   102,     0,   109,    94,     0,
       0,    91,    84,     0,    87,    25,    40,     0,    56,    57,
      58,     0,     0,     0,    50,    49,     0,     0,    44,    45,
      46,    47,    48,     0,     0,     0,   105,    90,    92,    96,
      39,    59,     0,     0,     0,     0,    51,    42,     0,     0,
       0,     0,     0,   108,     0,     0,     0,    41,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    52,     0,
      54,     0,     0,     0,     0,     0,   100,   106,     0,    53,
       0,   107,     0,     0,     0,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   154,    17,    18,    44,   155,    14,    15,
      66,    67,    68,    10,    11,   156,   157,   158,   159,   160,
     161,   126,    46,    47,    48,    49,    50,    51,    52,   127,
     162,    53,    12,    31,   103,   104,   137,   166
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -127
static const yytype_int16 yypact[] =
{
    -127,     8,    52,  -127,    24,    24,    84,    24,  -127,  -127,
    -127,  -127,  -127,  -127,   -15,  -127,    48,   -12,  -127,    70,
     -13,   -10,    44,    24,     7,   159,    24,   118,    67,    24,
      24,    21,  -127,  -127,  -127,  -127,  -127,  -127,  -127,     7,
       7,     7,     1,    24,  -127,    95,   102,    71,   -26,    77,
     -31,  -127,  -127,    29,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,    90,  -127,
    -127,   106,   -49,  -127,   144,  -127,  -127,   -17,     7,    33,
    -127,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,    24,   161,
     135,   -40,   156,    91,   149,  -127,    -9,     7,     7,    24,
     102,    71,   -26,   -26,   -26,   -26,   -26,   -26,    77,    77,
     -31,   -31,  -127,  -127,  -127,     3,    95,   -42,  -127,    99,
      96,   159,    22,  -127,   101,  -127,   163,  -127,  -127,     5,
     -16,  -127,  -127,     7,  -127,  -127,  -127,    96,  -127,  -127,
       7,   103,    24,   104,  -127,  -127,    28,   108,  -127,  -127,
    -127,  -127,  -127,    69,    24,   111,   165,  -127,  -127,    95,
    -127,    95,     7,   153,     7,    22,  -127,  -127,     7,     7,
      42,    24,    24,  -127,    -8,   115,     2,  -127,    95,    11,
     130,    45,    96,     7,    96,   119,   159,   145,   178,    23,
    -127,     7,    96,   159,    96,     7,    95,  -127,    96,  -127,
      27,  -127,     7,    20,    96,  -127
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -127,  -127,  -127,   201,  -127,   179,   177,   204,   -23,   184,
    -127,  -127,  -126,    43,  -127,  -127,    35,   -94,  -127,  -127,
    -127,   -24,   127,   129,    59,    62,    65,    -6,  -127,   105,
    -127,    -3,  -127,  -127,  -127,  -127,  -127,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      45,    16,    19,    21,    22,   147,    72,   133,     3,    13,
      33,    34,    35,    36,    37,    13,   131,    77,    23,    38,
      16,    93,    94,    19,   101,   143,    16,    73,    89,    90,
      13,   144,    13,    75,    76,   132,   146,     4,     5,    79,
      80,    81,   148,   149,   150,   151,    95,   152,   153,    81,
      81,   143,    23,   170,   106,    26,   105,   168,    39,    28,
      81,    81,    29,    81,   138,   192,    40,     4,     5,    81,
     202,     6,   125,    78,   142,   194,   167,   208,    81,    41,
       7,    81,   195,   139,    42,    81,    43,   122,   123,   124,
     205,   214,    13,    20,   212,   128,    74,   132,   198,    96,
     200,    97,   175,   107,   176,   108,   141,    98,   207,    23,
     209,   109,    23,    30,   211,   190,    24,    25,   197,   169,
     215,    33,    34,    35,    36,    37,   171,    91,    92,   163,
      38,    83,    84,    85,    86,    87,    88,   178,    27,   179,
      71,   180,   112,   113,   114,   115,   116,   117,   184,   173,
     186,   118,   119,    81,   188,   189,   120,   121,   191,    82,
      99,    16,   100,   102,   129,   130,   134,   135,   136,   199,
     145,   132,   163,   164,   165,   172,   174,   206,    16,    21,
     185,   210,   177,   181,   182,   193,   196,   201,   213,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,   203,   204,     8,    70,    69,     9,    32,   110,   183,
     187,   111,     0,   140
};

static const yytype_int16 yycheck[] =
{
      24,     4,     5,     6,     7,   131,    29,   101,     0,     8,
       3,     4,     5,     6,     7,     8,    56,    41,    67,    12,
      23,    52,    53,    26,    73,    67,    29,    30,    54,    55,
       8,    73,     8,    39,    40,    75,   130,    15,    16,    42,
      43,    58,    20,    21,    22,    23,    77,    25,    26,    58,
      58,    67,    67,   147,    78,    67,    73,    73,    51,    72,
      58,    58,    72,    58,    73,    73,    59,    15,    16,    58,
     196,    19,    96,    72,    71,    73,    71,   203,    58,    72,
      28,    58,    71,   107,    77,    58,    79,    93,    94,    95,
      67,    71,     8,     9,    67,    98,    75,    75,   192,    70,
     194,    72,    74,    70,    76,    72,   109,    78,   202,    67,
     204,    78,    67,    69,   208,    73,    68,    69,    73,   143,
     214,     3,     4,     5,     6,     7,   150,    50,    51,   132,
      12,    60,    61,    62,    63,    64,    65,    68,    68,    70,
      73,   164,    83,    84,    85,    86,    87,    88,   172,   152,
     174,    89,    90,    58,   178,   179,    91,    92,   181,    57,
      70,   164,    56,    19,     3,    30,    10,    76,    19,   193,
      71,    75,   175,    72,    11,    72,    72,   201,   181,   182,
      27,   205,    74,    72,    19,    70,    56,    68,   212,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    56,    24,     2,    27,    26,     2,    23,    81,   166,
     175,    82,    -1,   108
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    81,    82,     0,    15,    16,    19,    28,    83,    87,
      93,    94,   112,     8,    88,    89,   111,    84,    85,   111,
       9,   111,   111,    67,    68,    69,    67,    68,    72,    72,
      69,   113,    89,     3,     4,     5,     6,     7,    12,    51,
      59,    72,    77,    79,    86,   101,   102,   103,   104,   105,
     106,   107,   108,   111,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    90,    91,    92,    85,
      86,    73,    88,   111,    75,   107,   107,   101,    72,   111,
     111,    58,    57,    60,    61,    62,    63,    64,    65,    54,
      55,    50,    51,    52,    53,    77,    70,    72,    78,    70,
      56,    73,    19,   114,   115,    73,   101,    70,    72,    78,
     102,   103,   104,   104,   104,   104,   104,   104,   105,   105,
     106,   106,   107,   107,   107,   101,   101,   109,   111,     3,
      30,    56,    75,    97,    10,    76,    19,   116,    73,   101,
     109,   111,    71,    67,    73,    71,    97,    92,    20,    21,
      22,    23,    25,    26,    83,    87,    95,    96,    97,    98,
      99,   100,   110,   111,    72,    11,   117,    71,    73,   101,
      97,   101,    72,   111,    72,    74,    76,    74,    68,    70,
      88,    72,    19,    93,   101,    27,   101,    96,   101,   101,
      73,    88,    73,    70,    73,    71,    56,    73,    97,   101,
      97,    68,    92,    56,    24,    67,   101,    97,    92,    97,
     101,    97,    67,   101,    71,    97
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 99 "sky.y"
    { (yyval.program) = new Program((yyvsp[(1) - (2)].globalArea), (yyvsp[(2) - (2)].funcDec)); root = (yyval.program);;}
    break;

  case 3:
#line 103 "sky.y"
    { (yyval.globalArea) = (yyvsp[(1) - (2)].globalArea); (yyval.globalArea)->addConstDec((yyvsp[(2) - (2)].constDecListNode)->constDecList); ;}
    break;

  case 4:
#line 104 "sky.y"
    { (yyval.globalArea) = (yyvsp[(1) - (2)].globalArea); (yyval.globalArea)->addVarDec((yyvsp[(2) - (2)].varDecListNode)->varDecList); ;}
    break;

  case 5:
#line 105 "sky.y"
    { (yyval.globalArea) = (yyvsp[(1) - (2)].globalArea); (yyval.globalArea)->addFuncDec((yyvsp[(2) - (2)].funcDec)); ;}
    break;

  case 6:
#line 106 "sky.y"
    { (yyval.globalArea) = (yyvsp[(1) - (2)].globalArea); (yyval.globalArea)->addClassDec((yyvsp[(2) - (2)].classDec)); ;}
    break;

  case 7:
#line 107 "sky.y"
    { (yyval.globalArea) = new GlobalArea(); ;}
    break;

  case 8:
#line 111 "sky.y"
    { (yyval.constDecListNode) = new ConstDecListNode((yyvsp[(2) - (2)].constDecList)); ;}
    break;

  case 9:
#line 115 "sky.y"
    { (yyval.constDecList) = (yyvsp[(1) - (3)].constDecList); (yyval.constDecList)->push_back((yyvsp[(3) - (3)].constDec)); ;}
    break;

  case 10:
#line 116 "sky.y"
    { (yyval.constDecList) = new ConstDecList(); (yyval.constDecList)->push_back((yyvsp[(1) - (1)].constDec)); ;}
    break;

  case 11:
#line 120 "sky.y"
    { (yyval.constDec) = new ConstDec((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].constValue)); ;}
    break;

  case 12:
#line 124 "sky.y"
    { (yyval.constValue) = new SkyInt((yyvsp[(1) - (1)].iVal)); ;}
    break;

  case 13:
#line 125 "sky.y"
    { (yyval.constValue) = new SkyFloat((yyvsp[(1) - (1)].fVal)); ;}
    break;

  case 14:
#line 126 "sky.y"
    { (yyval.constValue) = new SkyDouble((yyvsp[(1) - (1)].dVal)); ;}
    break;

  case 15:
#line 127 "sky.y"
    { (yyval.constValue) = new SkyChar((yyvsp[(1) - (1)].cVal)); ;}
    break;

  case 16:
#line 128 "sky.y"
    { (yyval.constValue) = new SkyBool((yyvsp[(1) - (1)].bVal)); ;}
    break;

  case 17:
#line 129 "sky.y"
    { (yyval.constValue) = new SkyCharPointer((yyvsp[(1) - (1)].sVal)); ;}
    break;

  case 18:
#line 133 "sky.y"
    { (yyval.varDecListNode) = new VarDecListNode((yyvsp[(2) - (2)].varDecList)); ;}
    break;

  case 19:
#line 137 "sky.y"
    { (yyval.varDecList) = (yyvsp[(1) - (3)].varDecList); (yyval.varDecList)->push_back((yyvsp[(3) - (3)].varDec)); ;}
    break;

  case 20:
#line 138 "sky.y"
    { (yyval.varDecList) = new VarDecList(); (yyval.varDecList)->push_back((yyvsp[(1) - (1)].varDec)); ;}
    break;

  case 21:
#line 142 "sky.y"
    { (yyval.varDec) = new VarDec((yyvsp[(1) - (3)].identifier), nullptr, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 22:
#line 143 "sky.y"
    { (yyval.varDec) = new VarDec((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].skyType), nullptr); ;}
    break;

  case 23:
#line 147 "sky.y"
    { (yyval.skyType) = new SkyType((yyvsp[(1) - (1)].skyVarType)); ;}
    break;

  case 24:
#line 148 "sky.y"
    { (yyval.skyType) = new SkyType((yyvsp[(1) - (1)].skyArrayType)); ;}
    break;

  case 25:
#line 152 "sky.y"
    { (yyval.skyArrayType) = new SkyArrayType(new SkyType((yyvsp[(1) - (4)].skyVarType)), (yyvsp[(3) - (4)].iVal)); ;}
    break;

  case 26:
#line 156 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_INT); ;}
    break;

  case 27:
#line 157 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_INT_POINTER); ;}
    break;

  case 28:
#line 158 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_INT_64); ;}
    break;

  case 29:
#line 159 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_INT_64_POINTER); ;}
    break;

  case 30:
#line 160 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_CHAR); ;}
    break;

  case 31:
#line 161 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_CHAR_POINTER); ;}
    break;

  case 32:
#line 162 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_FLOAT); ;}
    break;

  case 33:
#line 163 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_FLOAT_POINTER); ;}
    break;

  case 34:
#line 164 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_DOUBLE); ;}
    break;

  case 35:
#line 165 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_DOUBLE_POINTER); ;}
    break;

  case 36:
#line 166 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_BOOL); ;}
    break;

  case 37:
#line 167 "sky.y"
    { (yyval.skyVarType) = new SkyVarType(SkyVarType::SKY_BOOL_POINTER); ;}
    break;

  case 38:
#line 171 "sky.y"
    { (yyval.funcDec) = new FuncDec((yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].varDecList), (yyvsp[(6) - (6)].compoundStat)); ;}
    break;

  case 39:
#line 172 "sky.y"
    { (yyval.funcDec) = new FuncDec((yyvsp[(2) - (8)].identifier), (yyvsp[(4) - (8)].varDecList), new SkyType((yyvsp[(7) - (8)].skyVarType)), (yyvsp[(8) - (8)].compoundStat)); ;}
    break;

  case 40:
#line 176 "sky.y"
    { (yyval.funcDec) = new FuncDec(new Identifier((yyvsp[(2) - (7)].sVal)), nullptr, new SkyType(new SkyVarType(SkyVarType::SKY_INT)), (yyvsp[(7) - (7)].compoundStat)); ;}
    break;

  case 41:
#line 180 "sky.y"
    { (yyval.statList) = (yyvsp[(1) - (3)].statList); (yyval.statList)->push_back((yyvsp[(3) - (3)].statement)); ;}
    break;

  case 42:
#line 181 "sky.y"
    { (yyval.statList) = new StatList(); (yyval.statList)->push_back((yyvsp[(1) - (2)].statement)); ;}
    break;

  case 43:
#line 182 "sky.y"
    { (yyval.statList) = new StatList(); ;}
    break;

  case 44:
#line 186 "sky.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].compoundStat); ;}
    break;

  case 45:
#line 187 "sky.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].ifStat); ;}
    break;

  case 46:
#line 188 "sky.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].statement); ;}
    break;

  case 47:
#line 189 "sky.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].jumpStat); ;}
    break;

  case 48:
#line 190 "sky.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].assignStat); ;}
    break;

  case 49:
#line 191 "sky.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].varDecListNode); ;}
    break;

  case 50:
#line 192 "sky.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].constDecListNode); ;}
    break;

  case 51:
#line 196 "sky.y"
    { (yyval.compoundStat) = new CompoundStat((yyvsp[(2) - (3)].statList)); ;}
    break;

  case 52:
#line 200 "sky.y"
    { (yyval.ifStat) = new IfStat((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].compoundStat), nullptr); ;}
    break;

  case 53:
#line 201 "sky.y"
    { (yyval.ifStat) = new IfStat((yyvsp[(3) - (7)].expression), (yyvsp[(5) - (7)].compoundStat), (yyvsp[(7) - (7)].compoundStat)); ;}
    break;

  case 54:
#line 205 "sky.y"
    { (yyval.statement) = new WhileStat((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].compoundStat)); ;}
    break;

  case 55:
#line 206 "sky.y"
    { (yyval.statement) = new ForStat((yyvsp[(2) - (11)].identifier), (yyvsp[(5) - (11)].expression), (yyvsp[(7) - (11)].expression), (yyvsp[(9) - (11)].expression), (yyvsp[(11) - (11)].compoundStat)); ;}
    break;

  case 56:
#line 210 "sky.y"
    { (yyval.jumpStat) = new JumpStat(TypeOfJump::BREAK, nullptr); ;}
    break;

  case 57:
#line 211 "sky.y"
    { (yyval.jumpStat) = new JumpStat(TypeOfJump::CONTINUE, nullptr); ;}
    break;

  case 58:
#line 212 "sky.y"
    { (yyval.jumpStat) = new JumpStat(TypeOfJump::RETURN, nullptr); ;}
    break;

  case 59:
#line 213 "sky.y"
    { (yyval.jumpStat) = new JumpStat(TypeOfJump::RETURN, (yyvsp[(2) - (2)].expression)); ;}
    break;

  case 60:
#line 217 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_OR, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 61:
#line 218 "sky.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 62:
#line 222 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_AND, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 63:
#line 223 "sky.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 64:
#line 227 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_EQ, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 65:
#line 228 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_NE, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 66:
#line 229 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_GT, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 67:
#line 230 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_LT, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 68:
#line 231 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_GE, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 69:
#line 232 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_LE, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 70:
#line 233 "sky.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 71:
#line 237 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_LEFT, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 72:
#line 238 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_RIGHT, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 73:
#line 239 "sky.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 74:
#line 243 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_PLUS, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 75:
#line 244 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_MINUS, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 76:
#line 245 "sky.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 77:
#line 249 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_MUL, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 78:
#line 250 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_DIV, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 79:
#line 251 "sky.y"
    { (yyval.expression) = new BinaryExpr((yyvsp[(1) - (3)].expression), BinaryOperators::OP_MOD, (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 80:
#line 252 "sky.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 81:
#line 256 "sky.y"
    { (yyval.expression) = new BinaryExpr(new SkyInt(0), BinaryOperators::OP_MINUS, (yyvsp[(2) - (2)].expression)); ;}
    break;

  case 82:
#line 257 "sky.y"
    { (yyval.expression) = new BinaryExpr(new SkyBool(true), BinaryOperators::OP_XOR, (yyvsp[(2) - (2)].expression)); ;}
    break;

  case 83:
#line 258 "sky.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 84:
#line 262 "sky.y"
    { (yyval.expression) = new ArrayReference((yyvsp[(1) - (4)].identifier), (yyvsp[(3) - (4)].expression)); ;}
    break;

  case 85:
#line 263 "sky.y"
    { (yyval.expression) = new ClassRef((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].identifier)); ;}
    break;

  case 86:
#line 264 "sky.y"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); ;}
    break;

  case 87:
#line 265 "sky.y"
    { (yyval.expression) = new FuncCall((yyvsp[(1) - (4)].identifier), (yyvsp[(3) - (4)].exprList)); ;}
    break;

  case 88:
#line 266 "sky.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].constValue); ;}
    break;

  case 89:
#line 267 "sky.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].identifier); ;}
    break;

  case 90:
#line 268 "sky.y"
    { (yyval.expression) = new PointerNode(new ArrayReference((yyvsp[(2) - (5)].identifier), (yyvsp[(4) - (5)].expression))); ;}
    break;

  case 91:
#line 269 "sky.y"
    { (yyval.expression) = new PointerNode(new ClassRef((yyvsp[(2) - (4)].identifier), (yyvsp[(4) - (4)].identifier))); ;}
    break;

  case 92:
#line 270 "sky.y"
    { (yyval.expression) = new PointerNode(new FuncCall((yyvsp[(2) - (5)].identifier), (yyvsp[(4) - (5)].exprList))); ;}
    break;

  case 93:
#line 271 "sky.y"
    { (yyval.expression)=  new PointerNode((yyvsp[(2) - (2)].identifier)); ;}
    break;

  case 94:
#line 272 "sky.y"
    { (yyval.expression) = new PointerNode((yyvsp[(3) - (4)].expression)); ;}
    break;

  case 95:
#line 273 "sky.y"
    { (yyval.expression) = new ReferenceNode((yyvsp[(2) - (2)].identifier)); ;}
    break;

  case 96:
#line 277 "sky.y"
    { (yyval.exprList) = (yyvsp[(1) - (3)].exprList); (yyval.exprList)->push_back((yyvsp[(3) - (3)].expression)); ;}
    break;

  case 97:
#line 278 "sky.y"
    { (yyval.exprList) = new ExprList(); (yyval.exprList)->push_back((yyvsp[(1) - (1)].expression)); ;}
    break;

  case 98:
#line 279 "sky.y"
    { (yyval.exprList) = nullptr; ;}
    break;

  case 99:
#line 283 "sky.y"
    { (yyval.assignStat) = new AssignStat((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].expression)); ;}
    break;

  case 100:
#line 284 "sky.y"
    { (yyval.assignStat) = new AssignStat(new ArrayReference((yyvsp[(1) - (6)].identifier), (yyvsp[(3) - (6)].expression)), (yyvsp[(6) - (6)].expression)); ;}
    break;

  case 101:
#line 288 "sky.y"
    { (yyval.identifier) = new Identifier((yyvsp[(1) - (1)].sVal)); ;}
    break;

  case 102:
#line 292 "sky.y"
    { (yyval.classDec) = new ClassDec((yyvsp[(2) - (6)].identifier), (yyvsp[(3) - (6)].identifier), (yyvsp[(5) - (6)].classBody)); ;}
    break;

  case 103:
#line 296 "sky.y"
    { (yyval.identifier) = (yyvsp[(2) - (2)].identifier); ;}
    break;

  case 104:
#line 297 "sky.y"
    { (yyval.identifier) = nullptr; ;}
    break;

  case 105:
#line 301 "sky.y"
    { (yyval.classBody) = new ClassBody((yyvsp[(1) - (3)].funcDec), (yyvsp[(2) - (3)].funcDec), (yyvsp[(3) - (3)].funcDecList)); ;}
    break;

  case 106:
#line 305 "sky.y"
    { (yyval.funcDec) = new FuncDec(new Identifier((yyvsp[(2) - (8)].sVal)), (yyvsp[(4) - (8)].varDecList), new SkyType((yyvsp[(7) - (8)].skyVarType)), (yyvsp[(8) - (8)].compoundStat)); ;}
    break;

  case 107:
#line 309 "sky.y"
    { (yyval.funcDec) = new FuncDec(new Identifier((yyvsp[(2) - (8)].sVal)), (yyvsp[(4) - (8)].varDecList), new SkyType((yyvsp[(7) - (8)].skyVarType)), (yyvsp[(8) - (8)].compoundStat)); ;}
    break;

  case 108:
#line 313 "sky.y"
    { (yyval.funcDecList) = (yyvsp[(1) - (2)].funcDecList); (yyval.funcDecList)->push_back((yyvsp[(2) - (2)].funcDec)); ;}
    break;

  case 109:
#line 314 "sky.y"
    { (yyval.funcDecList) = new FuncDecList(); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2230 "sky.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 316 "sky.y"



