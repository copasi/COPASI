// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqParser_yacc.h,v $
//   $Revision: 1.6.16.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/05 16:53:47 $
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
  TOKEN_MULTIPLY = 259,
  TOKEN_PLUS = 260,
  TOKEN_NAME = 261,
  TOKEN_BEGIN_PRODUCTS = 262,
  TOKEN_BEGIN_MODIFIERS = 263,
  TOKEN_BEGIN_COMPARTMENT = 264,
  TOKEN_END_COMPARTMENT = 265
};
#endif
/* Tokens.  */
#define TOKEN_NUMBER 258
#define TOKEN_MULTIPLY 259
#define TOKEN_PLUS 260
#define TOKEN_NAME 261
#define TOKEN_BEGIN_PRODUCTS 262
#define TOKEN_BEGIN_MODIFIERS 263
#define TOKEN_BEGIN_COMPARTMENT 264
#define TOKEN_END_COMPARTMENT 265

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE CChemEqParserlval;
