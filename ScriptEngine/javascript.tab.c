/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 5 "javascript.y"


#include <string.h>
#include <stdio.h>
#include "ParseTree.h"

extern int g_nLineNumber;

/* global script data pointers ************************************************************/

LPNODE g_pScriptNode = NULL;			//pointer to script's root node
LPFUNCTION g_pFunctionList = NULL;		//pointer to script's function list
LPNODE g_pNodeList = NULL;              //pointer to linear script node list


/* item creation functions ****************************************************************/
void yyerror( char *s );

LPNODE NewNode( NODETYPE type, LPNODE pLeft, LPNODE pRight, LPNODE pOther1 = NULL, LPNODE pOther2 = NULL )
{
	if( type == ntINVALID ) return NULL;

    LPNODE pNew = new NODE;

    pNew->NodeType = type;
    pNew->Left.pNode = pLeft;
    pNew->Right.pNode = pRight;
	pNew->Other1.pNode = pOther1;
	pNew->Other2.pNode = pOther2;
    pNew->fLeaf = FALSE;

    pNew->nLineNumber = g_nLineNumber;

    //link it in to the global list
    pNew->next = g_pNodeList;
    g_pNodeList = pNew;

    return pNew;
}

LPNODE NewLeaf( NODETYPE type, int nValue )
{
	if( type == ntINVALID ) return NULL;

    LPNODE pNew = new NODE;

	pNew->NodeType = type;
	pNew->Left.nValue = nValue;
	pNew->Right.nValue = 0;
	pNew->Other1.nValue = 0;
	pNew->Other2.nValue = 0;
	pNew->fLeaf = TRUE;
    pNew->fString = FALSE;

    pNew->nLineNumber = g_nLineNumber;

    //link it in to the global list
    pNew->next = g_pNodeList;
    g_pNodeList = pNew;

	return pNew;
}

LPNODE NewLeaf( NODETYPE type, double dValue )
{
	if( type == ntINVALID ) return NULL;

    LPNODE pNew = new NODE;

	pNew->NodeType = type;
	pNew->Left.dValue = dValue;
	pNew->Right.dValue = 0;
	pNew->Other1.dValue = 0;
	pNew->Other2.dValue = 0;
	pNew->fLeaf = TRUE;
    pNew->fString = FALSE;

    pNew->nLineNumber = g_nLineNumber;

    //link it in to the global list
    pNew->next = g_pNodeList;
    g_pNodeList = pNew;

	return pNew;
}


LPNODE NewLeaf( NODETYPE type, char* pszString = NULL )
{
	if( type == ntINVALID ) return NULL;

    LPNODE pNew = new NODE;

	pNew->NodeType = type;
	pNew->Left.strToken = pszString == NULL ? NULL : strdup(pszString);
	pNew->Right.strToken = NULL;
	pNew->Other1.strToken = NULL;
	pNew->Other2.strToken = NULL;
	pNew->fLeaf = TRUE;
    pNew->fString = TRUE;

    pNew->nLineNumber = g_nLineNumber;

    //link it in to the global list
    pNew->next = g_pNodeList;
    g_pNodeList = pNew;


	return pNew;
}



LPARGUMENT NewFormalArgument( LPARGUMENT pArguments, LPNODE pNodeName )
{
	if( pArguments )
	{
		LPARGUMENT pList = pArguments;
		while( pList )
		{
			if( strcmp( pList->pNode->Left.strToken, pNodeName->Left.strToken ) == 0 )
            {
                yyerror( "Argument already exists!" );
				return NULL;
            }
			pList = pList->next;
		}
	}

	//allocate the argument structure and fill it in
	LPARGUMENT pNew = new ARGUMENT;
	pNew->pNode = pNodeName;
	pNew->next = NULL;

	//link it to the list (at the end - the arguments must be in order)
	if( pArguments == NULL )
		//this is the first item
		return pNew;
	else
	{
		//a list exists already - add this one at the end
		LPARGUMENT pEndOfList = pArguments;
		while( pEndOfList->next != NULL ) pEndOfList = pEndOfList->next;
		
		pEndOfList->next = pNew;
		return pArguments;
	}
}

LPNODE NewFunction( LPNODE pFunctionBodyNode, LPARGUMENT pArguments, LPNODE pFunctionNameLeaf )
{
	if( pArguments )
	{
		LPFUNCTION pList = g_pFunctionList;
		while( pList )
		{
			if( strcmp( pList->pFunctionNameLeaf->Left.strToken, pFunctionNameLeaf->Left.strToken ) == 0 )
            {
				yyerror( "Function already exists" );
				return NULL;
            }
			pList = pList->next;
		}
	}

	//allocate the function stucture and fill it in
	LPFUNCTION pNew = new FUNCTION;
	pNew->pFunctionNameLeaf = pFunctionNameLeaf;
	pNew->pFunctionBodyNode = pFunctionBodyNode;
	pNew->pArguments = pArguments;
	
	//link it to the list (at the start - the function order does not matter)
	pNew->next = g_pFunctionList;
	g_pFunctionList = pNew;

	return pFunctionNameLeaf;
}

LPARGUMENT NewActualArgument( LPARGUMENT pArguments, LPNODE pNodeValue )
{
	//allocate the argument structure and fill it in
	LPARGUMENT pNew = new ARGUMENT;
	pNew->pNode = pNodeValue;
	pNew->next = NULL;

	//link it to the list (at the end - the arguments must be in order)
	if( pArguments == NULL )
		//this is the first item
		return pNew;
	else
	{
		//a list exists already - add this one at the end
		LPARGUMENT pEndOfList = pArguments;
		while( pEndOfList->next != NULL ) pEndOfList = pEndOfList->next;
		
		pEndOfList->next = pNew;
		return pArguments;
	}
}



int DecodeOctal( char* pszOctal )
{
	//it's in the C form of 0NNNNN
	int n = 0;
	sscanf( pszOctal+1, "%o", &n );

	return n;
}

double DecodeFloat( char* pszFloat )
{
	return atof( pszFloat );
}

int DecodeHex( char* pszHex )
{
	//it's in the C form of 0xNNNNN
	int n = 0;
	sscanf( pszHex+2, "%x", &n );

	return n;
}

int DecodeDecimal( char* pszDecimal )
{
	return atoi( pszDecimal );
}

/* tree destruction function **************************************************************/

void DeleteArguments( LPARGUMENT pArg )
{
	LPARGUMENT pTemp;
	while( pArg )
	{
		pTemp = pArg;
		pArg = pArg->next;
		delete pTemp;
	}
}

LPNODE DeleteNode( LPNODE pNode )
{
    if( pNode == NULL ) return NULL;
    LPNODE pReturn = pNode->next;

    //delete this node/leaf
    if( pNode->fLeaf == TRUE )
    {
        if( pNode->fString == TRUE )
        {
            //delete the strings
            delete[] pNode->Left.strToken;
            delete[] pNode->Right.strToken;
            delete[] pNode->Other1.strToken;
            delete[] pNode->Other2.strToken;
        }
    }
    else
    {
        //delete child nodes
        switch( pNode->NodeType )
        {
            case ntOBJECTMETHODCALL: 
                DeleteArguments( (LPARGUMENT)pNode->Other1.pNode ); 
                break;
            case ntFUNCTIONCALL:
            case ntCONSTRUCTOR:      
                DeleteArguments( (LPARGUMENT)pNode->Right.pNode ); 
                break;
        }
    }

    //delete this node
    delete pNode;

    return pReturn;
}

void FreeParseInformation( LPNODE pNodeList, LPFUNCTION pFunctionList )
{
    //delete the parse tree
    while( pNodeList ) pNodeList = DeleteNode( pNodeList );

    LPFUNCTION pTemp;
    while( pFunctionList )
    {
		DeleteArguments( pFunctionList->pArguments );
        
		pTemp = pFunctionList;
        pFunctionList = pFunctionList->next;
        delete pTemp;
    }
}



/* Line 371 of yacc.c  */
#line 368 "javascript.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "javascript.tab.h".  */
#ifndef YY_YY_JAVASCRIPT_TAB_H_INCLUDED
# define YY_YY_JAVASCRIPT_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FUNCTION = 258,
     IF = 259,
     ELSE = 260,
     FOR = 261,
     WHILE = 262,
     RETURN = 263,
     BREAK = 264,
     CONTINUE = 265,
     NEW = 266,
     STRING = 267,
     VAR = 268,
     OCTAL_DIGIT = 269,
     FLOAT_DIGIT = 270,
     HEX_DIGIT = 271,
     DECIMAL_DIGIT = 272,
     IDENTIFIER = 273,
     ASSIGN = 274,
     ADDASSIGN = 275,
     SUBASSIGN = 276,
     MULASSIGN = 277,
     DIVASSIGN = 278,
     MODASSIGN = 279,
     ANDASSIGN = 280,
     ORASSIGN = 281,
     XORASSIGN = 282,
     SHLASSIGN = 283,
     SSHRASSIGN = 284,
     LOGOR = 285,
     LOGAND = 286,
     BITOR = 287,
     BITAND = 288,
     BITXOR = 289,
     ISEQUALS = 290,
     ISNOTEQUALS = 291,
     ISLTHAN = 292,
     ISGTHAN = 293,
     ISLTHANEQUALS = 294,
     ISGTHANEQUALS = 295,
     SHL = 296,
     SSHR = 297,
     ADD = 298,
     MUL = 299,
     DIV = 300,
     MOD = 301,
     INCREMENT = 302,
     DECREMENT = 303
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 305 "javascript.y"

	LPNODE pNode;
	LPARGUMENT pFormalArgs;
	LPARGUMENT pActualArgs;
    NODETYPE NodeType;


/* Line 387 of yacc.c  */
#line 467 "javascript.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_JAVASCRIPT_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 495 "javascript.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  78
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   533

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNRULES -- Number of states.  */
#define YYNSTATES  203

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,     2,     2,     2,     2,     2,
      49,    50,     2,     2,    51,    57,    60,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    54,
       2,     2,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,    62,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,    53,    59,     2,     2,     2,
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
      45,    46,    47,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    14,    15,    22,    26,
      28,    29,    34,    38,    40,    45,    49,    53,    55,    59,
      61,    65,    68,    70,    73,    75,    77,    79,    81,    84,
      87,    90,    93,    95,   101,   109,   119,   125,   128,   130,
     132,   134,   136,   137,   139,   143,   145,   149,   151,   153,
     155,   157,   159,   161,   163,   165,   167,   169,   171,   173,
     179,   181,   185,   187,   191,   193,   197,   199,   203,   205,
     209,   211,   215,   219,   221,   225,   229,   233,   237,   239,
     243,   247,   249,   253,   257,   259,   263,   267,   271,   273,
     276,   279,   282,   285,   288,   290,   293,   296,   298,   302,
     304,   306,   308,   310,   312,   315,   317,   322,   327,   329,
     336,   340,   344,   346,   347,   352,   354,   356,   358,   360,
     362,   364,   366,   368,   370
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      64,     0,    -1,    69,    65,    -1,    65,    -1,    66,    65,
      -1,    74,    65,    -1,    -1,     3,   109,    49,    67,    50,
      68,    -1,    67,    51,   109,    -1,   109,    -1,    -1,    52,
      69,    73,    53,    -1,    52,    69,    53,    -1,    72,    -1,
      13,    70,    54,    69,    -1,    13,    70,    54,    -1,    71,
      51,    70,    -1,    71,    -1,   109,    19,    85,    -1,   109,
      -1,    52,    73,    53,    -1,    52,    53,    -1,    74,    -1,
      74,    73,    -1,    74,    -1,    75,    -1,    76,    -1,    77,
      -1,    78,    54,    -1,    79,    54,    -1,    80,    54,    -1,
      82,    54,    -1,    54,    -1,     4,    49,    82,    50,    72,
      -1,     4,    49,    82,    50,    72,     5,    72,    -1,     6,
      49,    81,    54,    81,    54,    81,    50,    72,    -1,     7,
      49,    82,    50,    72,    -1,     8,    82,    -1,     8,    -1,
       9,    -1,    10,    -1,    82,    -1,    -1,    83,    -1,    82,
      51,    83,    -1,    85,    -1,   105,    84,    83,    -1,    19,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,    29,
      -1,    86,    -1,    86,    55,    82,    56,    85,    -1,    87,
      -1,    86,    30,    87,    -1,    88,    -1,    87,    31,    88,
      -1,    89,    -1,    88,    32,    89,    -1,    90,    -1,    89,
      34,    90,    -1,    91,    -1,    90,    33,    91,    -1,    92,
      -1,    91,    35,    92,    -1,    91,    36,    92,    -1,    93,
      -1,    92,    37,    93,    -1,    92,    38,    93,    -1,    92,
      39,    93,    -1,    92,    40,    93,    -1,    94,    -1,    93,
      41,    94,    -1,    93,    42,    94,    -1,    95,    -1,    94,
      43,    95,    -1,    94,    57,    95,    -1,    96,    -1,    95,
      44,    96,    -1,    95,    45,    96,    -1,    95,    46,    96,
      -1,    97,    -1,    47,    96,    -1,    48,    96,    -1,    57,
      96,    -1,    58,    96,    -1,    59,    96,    -1,    98,    -1,
      97,    47,    -1,    97,    48,    -1,   109,    -1,    49,    82,
      50,    -1,   101,    -1,   102,    -1,    99,    -1,   107,    -1,
     108,    -1,    11,   100,    -1,   104,    -1,   109,    49,   103,
      50,    -1,   109,    49,   103,    50,    -1,   109,    -1,    97,
      60,   109,    49,   103,    50,    -1,    97,    60,   109,    -1,
     103,    51,    83,    -1,    83,    -1,    -1,    97,    61,    82,
      62,    -1,   102,    -1,   104,    -1,   106,    -1,   109,    -1,
      12,    -1,    14,    -1,    15,    -1,    16,    -1,    17,    -1,
      18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   330,   330,   331,   334,   335,   336,   341,   344,   345,
     346,   349,   350,   351,   356,   357,   360,   361,   364,   365,
     370,   371,   372,   375,   376,   380,   381,   382,   383,   384,
     385,   386,   387,   390,   391,   395,   399,   403,   404,   408,
     412,   418,   419,   422,   423,   426,   427,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   443,   444,
     447,   448,   451,   452,   455,   456,   459,   460,   463,   464,
     467,   468,   469,   472,   473,   474,   475,   476,   479,   480,
     481,   484,   485,   486,   489,   490,   491,   492,   495,   496,
     497,   498,   499,   500,   504,   505,   506,   507,   510,   511,
     512,   513,   514,   515,   516,   517,   522,   526,   527,   531,
     535,   539,   540,   541,   547,   551,   552,   553,   557,   561,
     608,   610,   612,   614,   619
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUNCTION", "IF", "ELSE", "FOR", "WHILE",
  "RETURN", "BREAK", "CONTINUE", "NEW", "STRING", "VAR", "OCTAL_DIGIT",
  "FLOAT_DIGIT", "HEX_DIGIT", "DECIMAL_DIGIT", "IDENTIFIER", "ASSIGN",
  "ADDASSIGN", "SUBASSIGN", "MULASSIGN", "DIVASSIGN", "MODASSIGN",
  "ANDASSIGN", "ORASSIGN", "XORASSIGN", "SHLASSIGN", "SSHRASSIGN", "LOGOR",
  "LOGAND", "BITOR", "BITAND", "BITXOR", "ISEQUALS", "ISNOTEQUALS",
  "ISLTHAN", "ISGTHAN", "ISLTHANEQUALS", "ISGTHANEQUALS", "SHL", "SSHR",
  "ADD", "MUL", "DIV", "MOD", "INCREMENT", "DECREMENT", "'('", "')'",
  "','", "'{'", "'}'", "';'", "'?'", "':'", "'-'", "'!'", "'~'", "'.'",
  "'['", "']'", "$accept", "script", "stmtsfuncs", "function", "args",
  "functionBody", "vars", "varDeclarations", "varDeclaration",
  "statementBlock", "statements", "statement", "ifStatement",
  "forStatement", "whileStatement", "returnStatement", "breakStatement",
  "continueStatement", "optionalExpression", "expression",
  "assign_expression", "assign_operator", "conditional_expression",
  "or_expression", "and_expression", "bitor_expression", "xor_expression",
  "bitand_expression", "equality_expression", "relational_expression",
  "shift_expression", "add_expression", "mult_expression",
  "unary_expression", "postfix_expression", "primary_expression",
  "functionCall", "constructor", "objectMethodCall", "objectMemberAccess",
  "params", "arrayDereference", "leftVariable", "variable", "string",
  "number", "identifier", YY_NULL
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,    40,
      41,    44,   123,   125,    59,    63,    58,    45,    33,   126,
      46,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    65,    66,    67,    67,
      67,    68,    68,    68,    69,    69,    70,    70,    71,    71,
      72,    72,    72,    73,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    75,    75,    76,    77,    78,    78,    79,
      80,    81,    81,    82,    82,    83,    83,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    90,    90,
      91,    91,    91,    92,    92,    92,    92,    92,    93,    93,
      93,    94,    94,    94,    95,    95,    95,    95,    96,    96,
      96,    96,    96,    96,    97,    97,    97,    97,    98,    98,
      98,    98,    98,    98,    98,    98,    99,   100,   100,   101,
     102,   103,   103,   103,   104,   105,   105,   105,   106,   107,
     108,   108,   108,   108,   109
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,     2,     0,     6,     3,     1,
       0,     4,     3,     1,     4,     3,     3,     1,     3,     1,
       3,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       2,     2,     1,     5,     7,     9,     5,     2,     1,     1,
       1,     1,     0,     1,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     2,     2,     1,     2,     2,     1,     3,     1,
       1,     1,     1,     1,     2,     1,     4,     4,     1,     6,
       3,     3,     1,     0,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     0,     0,    38,    39,    40,     0,   119,
       0,   120,   121,   122,   123,   124,     0,     0,     0,    32,
       0,     0,     0,     0,     3,     6,     6,     6,    25,    26,
      27,     0,     0,     0,     0,    43,    45,    58,    60,    62,
      64,    66,    68,    70,    73,    78,    81,    84,    88,    94,
     101,    99,   100,   105,     0,   117,   102,   103,    97,     0,
       0,    42,     0,    37,   104,   108,     0,    17,    19,    89,
     100,   105,    97,    90,     0,    91,    92,    93,     1,     4,
       2,     5,    28,    29,    30,     0,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    95,    96,     0,     0,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,     0,   113,    10,     0,     0,    41,     0,   113,    15,
       0,     0,    98,    44,    61,     0,    63,    65,    67,    69,
      71,    72,    74,    75,    76,    77,    79,    80,    82,    83,
      85,    86,    87,   110,     0,    46,   112,     0,     0,     9,
       0,    42,     0,     0,    14,    16,    18,     0,   113,   114,
     106,     0,     0,     0,     0,    33,    22,     0,    36,   107,
      59,     0,   111,     0,     7,    13,     8,    21,     0,    24,
       0,    42,   109,     0,    20,    23,    34,     0,    12,     0,
       0,    11,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    25,   158,   184,    26,    66,    67,   175,
     188,   176,    28,    29,    30,    31,    32,    33,   125,    34,
      35,   121,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    64,    51,    52,
     157,    53,    54,    55,    56,    57,    58
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -162
static const yytype_int16 yypact[] =
{
     214,    -9,   -15,   -13,    36,   463,  -162,  -162,    -9,  -162,
      -9,  -162,  -162,  -162,  -162,  -162,   463,   463,   463,  -162,
     463,   463,   463,    11,  -162,   237,   237,   237,  -162,  -162,
    -162,    33,    53,    87,    91,  -162,  -162,   -22,   125,   139,
     109,   142,    10,    41,    13,   -33,   102,  -162,     2,  -162,
    -162,  -162,    48,   380,   504,  -162,  -162,  -162,   309,   127,
     463,   463,   463,   126,  -162,   129,   130,   131,   160,  -162,
    -162,  -162,   132,  -162,    14,  -162,  -162,  -162,  -162,  -162,
    -162,  -162,  -162,  -162,  -162,   463,  -162,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,  -162,  -162,    -9,   463,
    -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,
    -162,   463,   463,    -9,    32,   136,   126,    99,   463,   167,
      -9,   463,  -162,  -162,   125,   -38,   139,   109,   142,    10,
      41,    41,    13,    13,    13,    13,   -33,   -33,   102,   102,
    -162,  -162,  -162,   137,   -45,  -162,  -162,   108,   110,  -162,
     308,   463,   308,   112,  -162,  -162,  -162,   463,   463,  -162,
    -162,   463,   364,    -9,   379,   180,  -162,   138,  -162,  -162,
    -162,   114,  -162,   293,  -162,  -162,  -162,  -162,   143,   450,
     308,   463,  -162,   435,  -162,  -162,  -162,   141,  -162,   144,
     308,  -162,  -162
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -162,  -162,   128,  -162,  -162,  -162,  -122,    65,  -162,  -160,
    -161,     0,  -162,  -162,  -162,  -162,  -162,  -162,  -156,    -4,
     -62,  -162,  -128,  -162,   146,   145,   147,   148,   107,    74,
      42,    70,    71,    31,  -162,  -162,  -162,  -162,  -162,    -1,
    -124,   111,  -162,  -162,  -162,  -162,    21
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -119
static const yytype_int16 yytable[] =
{
      27,    63,   178,   166,   163,   177,    85,   164,    87,    15,
     101,    78,   185,    85,    74,    70,    70,   169,   167,    70,
      70,    70,    59,   133,   102,    27,    27,    27,   195,    65,
     196,    68,   199,    88,    60,   197,    61,    72,    72,   180,
     202,    72,    72,    72,   181,    93,    94,    69,    73,   106,
     107,    75,    76,    77,    99,   100,   124,   126,   127,   155,
     156,   193,   108,   109,   132,    85,   156,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,    95,    96,
      97,    98,   160,    85,   135,    62,    70,    82,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,   154,   156,    83,    72,   182,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    71,    71,   153,
      70,    71,    71,    71,   150,   151,   152,   142,   143,   144,
     145,    84,    85,    91,   159,    86,   103,   104,   105,   162,
      85,    68,    72,    79,    80,    81,    89,   126,   170,   171,
     172,   173,   179,   171,   192,   171,    70,   140,   141,   146,
     147,    90,   148,   149,   189,    92,   123,    85,   128,   131,
      10,   122,   130,   189,   129,   190,   168,   126,    72,   189,
     161,   200,   191,   189,   186,   165,   194,   201,    71,   139,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,     1,     2,     0,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,   134,   136,     0,     0,   137,     0,   138,
       1,     2,    71,     3,     4,     5,     6,     7,     8,     9,
       0,    11,    12,    13,    14,    15,     0,     0,     0,     0,
       0,    16,    17,    18,     0,     0,     0,     0,    19,     0,
       0,    20,    21,    22,     0,     0,     0,     0,    71,     0,
       0,     0,     0,     0,    16,    17,    18,     0,     0,     0,
       0,    19,     0,     0,    20,    21,    22,     2,     0,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     2,     0,     3,     4,     5,     6,     7,     8,
       9,     0,    11,    12,    13,    14,    15,     0,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,     0,
      16,    17,    18,     0,     0,     0,   187,    19,     0,     0,
      20,    21,    22,     0,     0,    16,    17,    18,   122,     0,
     174,     0,    19,     0,     0,    20,    21,    22,     2,     0,
       3,     4,     5,     6,     7,     8,     9,     0,    11,    12,
      13,    14,    15,     2,     0,     3,     4,     5,     6,     7,
       8,     9,     0,    11,    12,    13,    14,    15,     0,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
       0,    16,    17,    18,     0,     0,   183,     0,    19,     0,
       0,    20,    21,    22,     0,     0,    16,    17,    18,     0,
       0,     0,   187,    19,     0,     0,    20,    21,    22,     2,
       0,     3,     4,     5,     6,     7,     8,     9,     0,    11,
      12,    13,    14,    15,     2,     0,     3,     4,     5,     6,
       7,     8,     9,     0,    11,    12,    13,    14,    15,     0,
       0,     0,     0,     0,     8,     9,     0,    11,    12,    13,
      14,    15,    16,    17,    18,     0,     0,     0,   198,    19,
       0,     0,    20,    21,    22,     0,     0,    16,    17,    18,
       0,     0,     0,     0,    19,     0,     0,    20,    21,    22,
      16,    17,    18,     0,     0,     0,     0,     0,     0,     0,
      20,    21,    22,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-162)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,     5,   162,   131,   128,   161,    51,   129,    30,    18,
      43,     0,   172,    51,    18,    16,    17,    62,    56,    20,
      21,    22,     1,    85,    57,    25,    26,    27,   189,     8,
     190,    10,   193,    55,    49,   191,    49,    16,    17,   167,
     200,    20,    21,    22,   168,    35,    36,    16,    17,    47,
      48,    20,    21,    22,    41,    42,    60,    61,    62,   121,
     122,   183,    60,    61,    50,    51,   128,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    37,    38,
      39,    40,    50,    51,    88,    49,    87,    54,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   109,   168,    54,    87,   171,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,    16,    17,   108,
     131,    20,    21,    22,   103,   104,   105,    95,    96,    97,
      98,    54,    51,    34,   123,    54,    44,    45,    46,    50,
      51,   130,   131,    25,    26,    27,    31,   161,    50,    51,
      50,    51,    50,    51,    50,    51,   167,    93,    94,    99,
     100,    32,   101,   102,   174,    33,    49,    51,    49,    19,
      13,    49,    51,   183,    54,     5,    49,   191,   167,   189,
      54,    50,    54,   193,   173,   130,    53,    53,    87,    92,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,     3,     4,    -1,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    87,    89,    -1,    -1,    90,    -1,    91,
       3,     4,   131,     6,     7,     8,     9,    10,    11,    12,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    57,    58,    59,    -1,    -1,    -1,    -1,   167,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    57,    58,    59,     4,    -1,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     4,    -1,     6,     7,     8,     9,    10,    11,
      12,    -1,    14,    15,    16,    17,    18,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      47,    48,    49,    -1,    -1,    -1,    53,    54,    -1,    -1,
      57,    58,    59,    -1,    -1,    47,    48,    49,    49,    -1,
      52,    -1,    54,    -1,    -1,    57,    58,    59,     4,    -1,
       6,     7,     8,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,    18,     4,    -1,     6,     7,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    47,    48,    49,    -1,    -1,    52,    -1,    54,    -1,
      -1,    57,    58,    59,    -1,    -1,    47,    48,    49,    -1,
      -1,    -1,    53,    54,    -1,    -1,    57,    58,    59,     4,
      -1,     6,     7,     8,     9,    10,    11,    12,    -1,    14,
      15,    16,    17,    18,     4,    -1,     6,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    11,    12,    -1,    14,    15,    16,
      17,    18,    47,    48,    49,    -1,    -1,    -1,    53,    54,
      -1,    -1,    57,    58,    59,    -1,    -1,    47,    48,    49,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    57,    58,    59,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    47,    48,    49,    54,
      57,    58,    59,    64,    65,    66,    69,    74,    75,    76,
      77,    78,    79,    80,    82,    83,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   101,   102,   104,   105,   106,   107,   108,   109,   109,
      49,    49,    49,    82,   100,   109,    70,    71,   109,    96,
     102,   104,   109,    96,    82,    96,    96,    96,     0,    65,
      65,    65,    54,    54,    54,    51,    54,    30,    55,    31,
      32,    34,    33,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    57,    44,    45,    46,    47,    48,    60,    61,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    84,    49,    49,    82,    81,    82,    82,    49,    54,
      51,    19,    50,    83,    87,    82,    88,    89,    90,    91,
      92,    92,    93,    93,    93,    93,    94,    94,    95,    95,
      96,    96,    96,   109,    82,    83,    83,   103,    67,   109,
      50,    54,    50,   103,    69,    70,    85,    56,    49,    62,
      50,    51,    50,    51,    52,    72,    74,    81,    72,    50,
      85,   103,    83,    52,    68,    72,   109,    53,    73,    74,
       5,    54,    50,    69,    53,    73,    72,    81,    53,    73,
      50,    53,    72
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1787 of yacc.c  */
#line 330 "javascript.y"
    { g_pScriptNode = NewNode( ntSTATEMENT, (yyvsp[(1) - (2)].pNode), (yyvsp[(2) - (2)].pNode) ); }
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 331 "javascript.y"
    { g_pScriptNode = NewNode( ntSTATEMENT, (yyvsp[(1) - (1)].pNode), NULL ); }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 334 "javascript.y"
    { (yyval.pNode) = (yyvsp[(2) - (2)].pNode); }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 335 "javascript.y"
    { (yyval.pNode) = NewNode( ntSTATEMENT, (yyvsp[(1) - (2)].pNode), (yyvsp[(2) - (2)].pNode) ); }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 336 "javascript.y"
    { (yyval.pNode) = NULL; }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 341 "javascript.y"
    { (yyval.pNode) = NewFunction( (yyvsp[(6) - (6)].pNode), (yyvsp[(4) - (6)].pFormalArgs), (yyvsp[(2) - (6)].pNode) ); }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 344 "javascript.y"
    { (yyval.pFormalArgs) = NewFormalArgument( (yyvsp[(1) - (3)].pFormalArgs), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 345 "javascript.y"
    { (yyval.pFormalArgs) = NewFormalArgument( NULL, (yyvsp[(1) - (1)].pNode) ); }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 346 "javascript.y"
    { (yyval.pFormalArgs) = NULL; }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 349 "javascript.y"
    { (yyval.pNode) = NewNode( ntSTATEMENT, (yyvsp[(2) - (4)].pNode), (yyvsp[(3) - (4)].pNode) ); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 350 "javascript.y"
    { (yyval.pNode) = (yyvsp[(2) - (3)].pNode); }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 351 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 356 "javascript.y"
    { (yyval.pNode) = NewNode( ntSTATEMENT, (yyvsp[(2) - (4)].pNode), (yyvsp[(4) - (4)].pNode) ); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 357 "javascript.y"
    { (yyval.pNode) = (yyvsp[(2) - (3)].pNode); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 360 "javascript.y"
    { (yyval.pNode) = NewNode( ntVARIABLELIST, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 361 "javascript.y"
    { (yyval.pNode) = NewNode( ntVARIABLELIST, (yyvsp[(1) - (1)].pNode), NULL ); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 364 "javascript.y"
    { (yyval.pNode) = NewNode( ntVARIABLE, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 365 "javascript.y"
    { (yyval.pNode) = NewNode( ntVARIABLE, (yyvsp[(1) - (1)].pNode), NULL ); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 370 "javascript.y"
    { (yyval.pNode) = (yyvsp[(2) - (3)].pNode); }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 371 "javascript.y"
    { (yyval.pNode) = NULL; }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 372 "javascript.y"
    { (yyval.pNode) = NewNode( ntSTATEMENT, (yyvsp[(1) - (1)].pNode), NULL ); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 375 "javascript.y"
    { (yyval.pNode) = NewNode( ntSTATEMENT, (yyvsp[(1) - (2)].pNode), (yyvsp[(2) - (2)].pNode) ); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 376 "javascript.y"
    { (yyval.pNode) = NewNode( ntSTATEMENT, (yyvsp[(1) - (1)].pNode), NULL ); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 380 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 381 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 382 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 383 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (2)].pNode); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 384 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (2)].pNode); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 385 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (2)].pNode); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 386 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (2)].pNode); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 387 "javascript.y"
    { (yyval.pNode) = NULL; }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 390 "javascript.y"
    { (yyval.pNode) = NewNode( ntIFSTATEMENT, (yyvsp[(3) - (5)].pNode), (yyvsp[(5) - (5)].pNode) ); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 391 "javascript.y"
    { (yyval.pNode) = NewNode( ntIFSTATEMENT, (yyvsp[(3) - (7)].pNode), (yyvsp[(5) - (7)].pNode), (yyvsp[(7) - (7)].pNode) ); }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 395 "javascript.y"
    { (yyval.pNode) = NewNode( ntFORSTATEMENT, (yyvsp[(3) - (9)].pNode), (yyvsp[(5) - (9)].pNode), (yyvsp[(7) - (9)].pNode), (yyvsp[(9) - (9)].pNode) ); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 399 "javascript.y"
    { (yyval.pNode) = NewNode( ntWHILESTATEMENT, (yyvsp[(3) - (5)].pNode), (yyvsp[(5) - (5)].pNode) ); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 403 "javascript.y"
    { (yyval.pNode) = NewNode( ntRETURNSTATEMENT, (yyvsp[(2) - (2)].pNode), NULL ); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 404 "javascript.y"
    { (yyval.pNode) = NewNode( ntRETURNSTATEMENT, NULL, NULL ); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 408 "javascript.y"
    { (yyval.pNode) = NewNode( ntBREAKSTATEMENT, NULL, NULL ); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 412 "javascript.y"
    { (yyval.pNode) = NewNode( ntCONTINUESTATEMENT, NULL, NULL ); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 418 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 419 "javascript.y"
    { (yyval.pNode) = NULL; }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 422 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 423 "javascript.y"
    { (yyval.pNode) = NewNode( ntEXPRESSION, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 426 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 427 "javascript.y"
    { (yyval.pNode) = NewNode( (yyvsp[(2) - (3)].NodeType), (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 430 "javascript.y"
    { (yyval.NodeType) = ntASSIGN; }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 431 "javascript.y"
    { (yyval.NodeType) = ntADDASSIGN; }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 432 "javascript.y"
    { (yyval.NodeType) = ntSUBASSIGN; }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 433 "javascript.y"
    { (yyval.NodeType) = ntMULASSIGN; }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 434 "javascript.y"
    { (yyval.NodeType) = ntDIVASSIGN; }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 435 "javascript.y"
    { (yyval.NodeType) = ntMODASSIGN; }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 436 "javascript.y"
    { (yyval.NodeType) = ntANDASSIGN; }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 437 "javascript.y"
    { (yyval.NodeType) = ntORASSIGN; }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 438 "javascript.y"
    { (yyval.NodeType) = ntXORASSIGN; }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 439 "javascript.y"
    { (yyval.NodeType) = ntSHLASSIGN; }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 440 "javascript.y"
    { (yyval.NodeType) = ntSSHRASSIGN; }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 443 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 444 "javascript.y"
    { (yyval.pNode) = NewNode( ntQUESTIONMARKCOLON, (yyvsp[(1) - (5)].pNode), (yyvsp[(3) - (5)].pNode), (yyvsp[(5) - (5)].pNode) ); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 447 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 448 "javascript.y"
    { (yyval.pNode) = NewNode( ntLOGOR, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 451 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 452 "javascript.y"
    { (yyval.pNode) = NewNode( ntLOGAND, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 455 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 456 "javascript.y"
    { (yyval.pNode) = NewNode( ntBITOR, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 459 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 460 "javascript.y"
    { (yyval.pNode) = NewNode( ntBITXOR, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 463 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 464 "javascript.y"
    { (yyval.pNode) = NewNode( ntBITAND, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 467 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 468 "javascript.y"
    { (yyval.pNode) = NewNode( ntISEQUALS, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 469 "javascript.y"
    { (yyval.pNode) = NewNode( ntISNOTEQUALS, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 472 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 473 "javascript.y"
    { (yyval.pNode) = NewNode( ntISLTHAN, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 474 "javascript.y"
    { (yyval.pNode) = NewNode( ntISGTHAN, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 475 "javascript.y"
    { (yyval.pNode) = NewNode( ntISLTHANEQUALS, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 476 "javascript.y"
    { (yyval.pNode) = NewNode( ntISGTHANEQUALS, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 479 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 480 "javascript.y"
    { (yyval.pNode) = NewNode( ntSHL, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 481 "javascript.y"
    { (yyval.pNode) = NewNode( ntSSHR, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 484 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 485 "javascript.y"
    { (yyval.pNode) = NewNode( ntADD, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 486 "javascript.y"
    { (yyval.pNode) = NewNode( ntSUB, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 489 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 490 "javascript.y"
    { (yyval.pNode) = NewNode( ntMUL, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 491 "javascript.y"
    { (yyval.pNode) = NewNode( ntDIV, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 492 "javascript.y"
    { (yyval.pNode) = NewNode( ntMOD, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 495 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 496 "javascript.y"
    { (yyval.pNode) = NewNode( ntPREINCREMENT, (yyvsp[(2) - (2)].pNode), NULL ); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 497 "javascript.y"
    { (yyval.pNode) = NewNode( ntPREDECREMENT, (yyvsp[(2) - (2)].pNode), NULL ); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 498 "javascript.y"
    { (yyval.pNode) = NewNode( ntNEGATE, (yyvsp[(2) - (2)].pNode), NULL ); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 499 "javascript.y"
    { (yyval.pNode) = NewNode( ntLOGICALNOT, (yyvsp[(2) - (2)].pNode), NULL ); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 500 "javascript.y"
    { (yyval.pNode) = NewNode( ntCOMPLIMENT, (yyvsp[(2) - (2)].pNode), NULL ); }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 504 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 505 "javascript.y"
    { (yyval.pNode) = NewNode( ntPOSTINCREMENT, (yyvsp[(1) - (2)].pNode), NULL ); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 506 "javascript.y"
    { (yyval.pNode) = NewNode( ntPOSTDECREMENT, (yyvsp[(1) - (2)].pNode), NULL ); }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 507 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 510 "javascript.y"
    { (yyval.pNode) = (yyvsp[(2) - (3)].pNode); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 511 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 512 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 513 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 514 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 515 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 516 "javascript.y"
    { (yyval.pNode) = NewNode( ntNEW, (yyvsp[(2) - (2)].pNode), NULL ); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 517 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 522 "javascript.y"
    { (yyval.pNode) = NewNode( ntFUNCTIONCALL, (yyvsp[(1) - (4)].pNode), (LPNODE)(yyvsp[(3) - (4)].pActualArgs) ); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 526 "javascript.y"
    { (yyval.pNode) = NewNode( ntCONSTRUCTOR, (yyvsp[(1) - (4)].pNode), (LPNODE)(yyvsp[(3) - (4)].pActualArgs) ); }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 527 "javascript.y"
    { (yyval.pNode) = NewNode( ntCONSTRUCTOR, (yyvsp[(1) - (1)].pNode), NULL ); }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 531 "javascript.y"
    { (yyval.pNode) = NewNode( ntOBJECTMETHODCALL, (yyvsp[(1) - (6)].pNode), (yyvsp[(3) - (6)].pNode), (LPNODE)(yyvsp[(5) - (6)].pActualArgs) ); }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 535 "javascript.y"
    { (yyval.pNode) = NewNode( ntOBJECTMEMBERACCESS, (yyvsp[(1) - (3)].pNode), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 539 "javascript.y"
    { (yyval.pActualArgs) = NewActualArgument( (yyvsp[(1) - (3)].pActualArgs), (yyvsp[(3) - (3)].pNode) ); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 540 "javascript.y"
    { (yyval.pActualArgs) = NewActualArgument( NULL, (yyvsp[(1) - (1)].pNode) ); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 541 "javascript.y"
    { (yyval.pActualArgs) = NULL; }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 547 "javascript.y"
    { (yyval.pNode) = NewNode( ntARRAYDEREFERENCE, (yyvsp[(1) - (4)].pNode), (yyvsp[(3) - (4)].pNode) ); }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 551 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 552 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 553 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 557 "javascript.y"
    { (yyval.pNode) = (yyvsp[(1) - (1)].pNode); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 562 "javascript.y"
    { 
						  //strip the quotes from the string
						  char* pszCloseQuote = &yytext[strlen(yytext)-1];
						  *pszCloseQuote = '\0';

                          //now search & replace escape codes
                          char* pszScan = &yytext[1], *pszWrite = yytext;
                          while( *pszScan != '\0' )
                          {
                              if( *pszScan == '\\' )
								  switch( pszScan[1] )
								  {
									  case 'a':  *pszWrite = '\a'; pszWrite++; pszScan+=2; break;
									  case 'b':  *pszWrite = '\b'; pszWrite++; pszScan+=2; break;
									  case 'f':  *pszWrite = '\f'; pszWrite++; pszScan+=2; break;
									  case 'n':  *pszWrite = '\n'; pszWrite++; pszScan+=2; break;
									  case 'r':  *pszWrite = '\r'; pszWrite++; pszScan+=2; break;
									  case 't':  *pszWrite = '\t'; pszWrite++; pszScan+=2; break;
									  case 'v':  *pszWrite = '\v'; pszWrite++; pszScan+=2; break;
									  case '?':  *pszWrite = '\?'; pszWrite++; pszScan+=2; break;
									  case '\'': *pszWrite = '\''; pszWrite++; pszScan+=2; break;
									  case '\"': *pszWrite = '\"'; pszWrite++; pszScan+=2; break;
									  case '\\': *pszWrite = '\\'; pszWrite++; pszScan+=2; break;
									  case '0':  *pszWrite = '\0'; pszWrite++; pszScan+=2; break;
									  default:
									  {
										  char szBuffer[128];
										  sprintf( szBuffer, "Invalid escape code: %c", pszScan[1] );
										  yyerror( szBuffer );
										  return 0;
									  }
								  }
							  else
							  {
								  *pszWrite = *pszScan;
								  pszWrite++;
								  pszScan++;
							  }
                          }
						  *pszWrite = '\0';

						  (yyval.pNode) = NewLeaf( ltSTRING, yytext ); 
                      }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 609 "javascript.y"
    { (yyval.pNode) = NewLeaf( ltNUMBER, DecodeOctal(yytext) ); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 611 "javascript.y"
    { (yyval.pNode) = NewLeaf( ltFLOAT, DecodeFloat(yytext) ); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 613 "javascript.y"
    { (yyval.pNode) = NewLeaf( ltNUMBER, DecodeHex(yytext) ); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 615 "javascript.y"
    { (yyval.pNode) = NewLeaf( ltNUMBER, DecodeDecimal(yytext) ); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 620 "javascript.y"
    { 
                            if( strlen( yytext ) >= MAX_IDENTIFIER )
                            {
                                char szBuffer[128];
                                sprintf( szBuffer, "Identifier length exceeds %d characters", MAX_IDENTIFIER );
                                yyerror( szBuffer );
                                return 0;
                            }
                            (yyval.pNode) = NewLeaf( ltIDENTIFIER, yytext ); 
                        }
    break;


/* Line 1787 of yacc.c  */
#line 2749 "javascript.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2050 of yacc.c  */
#line 633 "javascript.y"



/* scanner declarations - DOS and Windows (MFC) *******************************************/
#ifndef _WIN32
    #include "lex.yy.c"
    void yyerror( char *s ) { printf( "\nLine %d : %s\n%s\n\n", g_nLineNumber, s, yytext ); }
    main() { yyparse(); }
#else
    #include <io.h>
    #define isatty _isatty
    #include "lex.yy.c"
    extern HWND g_hWndOwner;
    void yyerror( char *s )
    {
        char* pszMessage = new char[strlen(s)+strlen(yytext)+256];
        sprintf( pszMessage, "Line %d : %s\n%s", g_nLineNumber, s, yytext );
        MessageBox( g_hWndOwner, pszMessage, "Script Error", MB_ICONEXCLAMATION|MB_TASKMODAL );
        delete[] pszMessage;
    }

    void ResetParser()
    {
    	yychar = -1;
    	yyerrflag = 0;
    	yynerrs = 0;
    
        YY_FLUSH_BUFFER;
    }

	void CleanupParser()
	{
		yy_delete_buffer( yy_current_buffer );
        free( yyss );
        free( yyvs );

		yy_current_buffer = 0;
		yyss = 0;
		yyvs = 0;
	}

#endif
