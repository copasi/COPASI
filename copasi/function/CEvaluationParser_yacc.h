// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationParser_yacc.h,v $
//   $Revision: 1.19.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/05 16:53:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

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
  TOKEN_NUMBER = 258,
  TOKEN_VARIABLE = 259,
  TOKEN_CALL = 260,
  TOKEN_FUNCTION = 261,
  TOKEN_FUNCTION_2 = 262,
  TOKEN_SIGN = 263,
  TOKEN_OPERATOR_POWER = 264,
  TOKEN_OPERATOR_MULTIPLY = 265,
  TOKEN_OPERATOR_MODULUS = 266,
  TOKEN_OPERATOR_PLUS = 267,
  TOKEN_LOGICAL_CHOICE = 268,
  TOKEN_LOGICAL_VALUE = 269,
  TOKEN_LOGICAL_NOT = 270,
  TOKEN_LOGICAL_OR = 271,
  TOKEN_LOGICAL_XOR = 272,
  TOKEN_LOGICAL_AND = 273,
  TOKEN_LOGICAL_EQ = 274,
  TOKEN_LOGICAL_NE = 275,
  TOKEN_LOGICAL_GT = 276,
  TOKEN_LOGICAL_GE = 277,
  TOKEN_LOGICAL_LT = 278,
  TOKEN_LOGICAL_LE = 279,
  TOKEN_STRUCTURE_OPEN = 280,
  TOKEN_STRUCTURE_VECTOR_OPEN = 281,
  TOKEN_STRUCTURE_COMMA = 282,
  TOKEN_STRUCTURE_CLOSE = 283,
  TOKEN_STRUCTURE_VECTOR_CLOSE = 284
};
#endif
/* Tokens.  */
#define TOKEN_NUMBER 258
#define TOKEN_VARIABLE 259
#define TOKEN_CALL 260
#define TOKEN_FUNCTION 261
#define TOKEN_FUNCTION_2 262
#define TOKEN_SIGN 263
#define TOKEN_OPERATOR_POWER 264
#define TOKEN_OPERATOR_MULTIPLY 265
#define TOKEN_OPERATOR_MODULUS 266
#define TOKEN_OPERATOR_PLUS 267
#define TOKEN_LOGICAL_CHOICE 268
#define TOKEN_LOGICAL_VALUE 269
#define TOKEN_LOGICAL_NOT 270
#define TOKEN_LOGICAL_OR 271
#define TOKEN_LOGICAL_XOR 272
#define TOKEN_LOGICAL_AND 273
#define TOKEN_LOGICAL_EQ 274
#define TOKEN_LOGICAL_NE 275
#define TOKEN_LOGICAL_GT 276
#define TOKEN_LOGICAL_GE 277
#define TOKEN_LOGICAL_LT 278
#define TOKEN_LOGICAL_LE 279
#define TOKEN_STRUCTURE_OPEN 280
#define TOKEN_STRUCTURE_VECTOR_OPEN 281
#define TOKEN_STRUCTURE_COMMA 282
#define TOKEN_STRUCTURE_CLOSE 283
#define TOKEN_STRUCTURE_VECTOR_CLOSE 284

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE CEvaluationParserlval;
