// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/* A Bison parser, made by GNU Bison 3.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
# define YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int CEvaluationParserdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
enum yytokentype
{
  TOKEN_NUMBER = 258,
  TOKEN_VARIABLE = 259,
  TOKEN_UNIT = 260,
  TOKEN_CALL = 261,
  TOKEN_FUNCTION = 262,
  TOKEN_FUNCTION_2 = 263,
  TOKEN_SIGN = 264,
  TOKEN_OPERATOR_POWER = 265,
  TOKEN_OPERATOR_MULTIPLY = 266,
  TOKEN_OPERATOR_MODULUS = 267,
  TOKEN_OPERATOR_REMAINDER = 268,
  TOKEN_OPERATOR_PLUS = 269,
  TOKEN_LOGICAL_CHOICE = 270,
  TOKEN_LOGICAL_VALUE = 271,
  TOKEN_LOGICAL_NOT = 272,
  TOKEN_LOGICAL_OR = 273,
  TOKEN_LOGICAL_XOR = 274,
  TOKEN_LOGICAL_AND = 275,
  TOKEN_LOGICAL_EQ = 276,
  TOKEN_LOGICAL_NE = 277,
  TOKEN_LOGICAL_GT = 278,
  TOKEN_LOGICAL_GE = 279,
  TOKEN_LOGICAL_LT = 280,
  TOKEN_LOGICAL_LE = 281,
  TOKEN_STRUCTURE_OPEN = 282,
  TOKEN_STRUCTURE_VECTOR_OPEN = 283,
  TOKEN_STRUCTURE_COMMA = 284,
  TOKEN_STRUCTURE_CLOSE = 285,
  TOKEN_STRUCTURE_VECTOR_CLOSE = 286
};
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE CEvaluationParserlval;

int CEvaluationParserparse(void);

#endif /* !YY_CEVALUATIONPARSER_CEVALUATIONPARSER_TAB_HPP_INCLUDED  */
