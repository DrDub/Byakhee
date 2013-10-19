/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2053 of yacc.c  */
#line 305 "javascript.y"

	LPNODE pNode;
	LPARGUMENT pFormalArgs;
	LPARGUMENT pActualArgs;
    NODETYPE NodeType;


/* Line 2053 of yacc.c  */
#line 113 "javascript.tab.h"
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
