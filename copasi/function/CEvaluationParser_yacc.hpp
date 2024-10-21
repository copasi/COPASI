/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
# define YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int CEvaluationParserdebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_NUMBER = 258,            /* TOKEN_NUMBER  */
    TOKEN_VARIABLE = 259,          /* TOKEN_VARIABLE  */
    TOKEN_UNIT = 260,              /* TOKEN_UNIT  */
    TOKEN_CALL = 261,              /* TOKEN_CALL  */
    TOKEN_FUNCTION = 262,          /* TOKEN_FUNCTION  */
    TOKEN_FUNCTION_1 = 263,        /* TOKEN_FUNCTION_1  */
    TOKEN_FUNCTION_2 = 264,        /* TOKEN_FUNCTION_2  */
    TOKEN_SIGN = 265,              /* TOKEN_SIGN  */
    TOKEN_OPERATOR_POWER = 266,    /* TOKEN_OPERATOR_POWER  */
    TOKEN_OPERATOR_MULTIPLY = 267, /* TOKEN_OPERATOR_MULTIPLY  */
    TOKEN_OPERATOR_MODULUS = 268,  /* TOKEN_OPERATOR_MODULUS  */
    TOKEN_OPERATOR_REMAINDER = 269, /* TOKEN_OPERATOR_REMAINDER  */
    TOKEN_OPERATOR_PLUS = 270,     /* TOKEN_OPERATOR_PLUS  */
    TOKEN_LOGICAL_CHOICE = 271,    /* TOKEN_LOGICAL_CHOICE  */
    TOKEN_LOGICAL_VALUE = 272,     /* TOKEN_LOGICAL_VALUE  */
    TOKEN_LOGICAL_NOT = 273,       /* TOKEN_LOGICAL_NOT  */
    TOKEN_LOGICAL_OR = 274,        /* TOKEN_LOGICAL_OR  */
    TOKEN_LOGICAL_XOR = 275,       /* TOKEN_LOGICAL_XOR  */
    TOKEN_LOGICAL_AND = 276,       /* TOKEN_LOGICAL_AND  */
    TOKEN_LOGICAL_EQ = 277,        /* TOKEN_LOGICAL_EQ  */
    TOKEN_LOGICAL_NE = 278,        /* TOKEN_LOGICAL_NE  */
    TOKEN_LOGICAL_GT = 279,        /* TOKEN_LOGICAL_GT  */
    TOKEN_LOGICAL_GE = 280,        /* TOKEN_LOGICAL_GE  */
    TOKEN_LOGICAL_LT = 281,        /* TOKEN_LOGICAL_LT  */
    TOKEN_LOGICAL_LE = 282,        /* TOKEN_LOGICAL_LE  */
    TOKEN_STRUCTURE_OPEN = 283,    /* TOKEN_STRUCTURE_OPEN  */
    TOKEN_STRUCTURE_VECTOR_OPEN = 284, /* TOKEN_STRUCTURE_VECTOR_OPEN  */
    TOKEN_STRUCTURE_COMMA = 285,   /* TOKEN_STRUCTURE_COMMA  */
    TOKEN_STRUCTURE_CLOSE = 286,   /* TOKEN_STRUCTURE_CLOSE  */
    TOKEN_STRUCTURE_VECTOR_CLOSE = 287 /* TOKEN_STRUCTURE_VECTOR_CLOSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE CEvaluationParserlval;


int CEvaluationParserparse (void);


#endif /* !YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED  */
