/*
 * Copyright (c) 1998,1999,2000,2001,2002 Tal Davidson. All rights reserved.
 *
 * astyle_main.cpp
 * Copyright (c) 1998,1999,2000 Tal Davidson (davidsont@bigfoot.com). All rights reserved.
 *
 * This file is a part of "Artistic Style" - an indentater and reformatter
 * of C, C++, C# and Java source files.
 *
 * The "Artistic Style" project, including all files needed to compile it,
 * is free software; you can redistribute it and/or use it and/or modify it
 * under the terms of the GNU General Public License as published 
 * by the Free Software Foundation; either version 2 of the License, 
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.
 *
 */

#include "compiler_defines.h"
#include "astyle.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#define IS_OPTION(arg,op)          ((arg).compare(op)==0)
#define IS_OPTIONS(arg,a,b)        (IS_OPTION((arg),(a)) || IS_OPTION((arg),(b)))

#define IS_PARAM_OPTION(arg,op)    ((arg).COMPARE(0, strlen(op) , string(op))==0)
#define IS_PARAM_OPTIONS(arg,a,b)  (IS_PARAM_OPTION((arg),(a)) || IS_PARAM_OPTION((arg),(b)))

#define GET_PARAM(arg,op)          ((arg).substr(strlen(op)))
#define GET_PARAMS(arg,a,b)        (IS_PARAM_OPTION((arg),(a)) ? GET_PARAM((arg),(a)) : GET_PARAM((arg),(b)))

#ifdef USES_NAMESPACE
using namespace std;
using namespace astyle;
#endif

// default options:
ostream *_err = &cerr;
string _suffix = ".orig";
bool _modeManuallySet;

const string _version = "1.15.3";

class ASStreamIterator :
      public ASSourceIterator
  {
  public:
    ASStreamIterator(istream *in);
    virtual ~ASStreamIterator();
    bool hasMoreLines() const;
    string nextLine();

  private:
    istream * inStream;
    char buffer[2048];
  };

ASStreamIterator::ASStreamIterator(istream *in)
{
  inStream = in;
}

ASStreamIterator::~ASStreamIterator()
{
  delete inStream;
}

bool ASStreamIterator::hasMoreLines() const
  {
    if (*inStream)
      return true;
    else
      return false;
  }

/*
string ASStreamIterator::nextLine()
{
   char theInChar;
   char peekedChar;
   int  theBufferPosn = 0;
 
   //
   // treat '\n', '\r', '\n\r' and '\r\n' as an endline.
   //
   while (theBufferPosn < 2047 && inStream->get(theInChar))
   // while not eof
   {
      if (theInChar != '\n' && theInChar != '\r')
      {
  buffer[theBufferPosn] = theInChar;
         theBufferPosn++;
      }
      else
      {
 peekedChar = inStream->peek();
 if (peekedChar != theInChar && (peekedChar == '\r' || peekedChar == '\n'))
         {
            inStream->get(theInChar);
         }
         break;
      }
   }
   buffer[theBufferPosn] = '\0';
 
   return string(buffer);
}
 */

string ASStreamIterator::nextLine()
{
  char *srcPtr;
  char *filterPtr;

  inStream->getline(buffer, 2047);
  srcPtr = filterPtr = buffer;

  while (*srcPtr != 0)
    {
      if (*srcPtr != '\r')
        *filterPtr++ = *srcPtr;
      srcPtr++;
    }
  *filterPtr = 0;

  return string(buffer);
}

void error(const char *why, const char* what)
{
  (*_err) << why << ' ' << what << '\n';
  exit(1);
}

template <class ITER>
bool parseOptions(ASFormatter &formatter,
                  const ITER &optionsBegin,
                  const ITER &optionsEnd,
                  const string &errorInfo)
{
  ITER option;
  bool ok = true;
  string arg, subArg;

  for (option = optionsBegin; option != optionsEnd; ++option)
    {
      arg = *option; //string(*option);

      if (arg.COMPARE(0, 2, string("--")) == 0)
        ok &= parseOption(formatter, arg.substr(2), errorInfo);
      else if (arg[0] == '-')
        {
          int i;

          for (i = 1; i < arg.length(); ++i)
            {
              if (isalpha(arg[i]) && i > 1)
                {
                  ok &= parseOption(formatter, subArg, errorInfo);
                  subArg = "";
                }
              subArg.append(1, arg[i]);
            }
          ok &= parseOption(formatter, subArg, errorInfo);
          subArg = "";
        }
      else
        {
          ok &= parseOption(formatter, arg, errorInfo);
          subArg = "";
        }
    }

  return ok;
}

void manuallySetJavaStyle(ASFormatter &formatter)
{
  formatter.setJavaStyle();
  _modeManuallySet = true;
}

void manuallySetCStyle(ASFormatter &formatter)
{
  formatter.setCStyle();
  _modeManuallySet = true;
}

bool parseOption(ASFormatter &formatter, const string &arg, const string &errorInfo)
{
  if (IS_PARAM_OPTION(arg, "suffix="))
    {
      string suffixParam = GET_PARAM(arg, "suffix=");
      if (suffixParam.length() > 0)
        _suffix = suffixParam;
    }
  else if (IS_OPTION(arg , "style=ansi"))
    {
      formatter.setBracketIndent(false);
      formatter.setSpaceIndentation(4);
      formatter.setBracketFormatMode(BREAK_MODE);
      formatter.setClassIndent(false);
      formatter.setSwitchIndent(false);
      formatter.setNamespaceIndent(false);
    }
  else if (IS_OPTION(arg , "style=gnu"))
    {
      formatter.setBlockIndent(true);
      formatter.setSpaceIndentation(2);
      formatter.setBracketFormatMode(BREAK_MODE);
      formatter.setClassIndent(false);
      formatter.setSwitchIndent(false);
      formatter.setNamespaceIndent(false);
    }
  else if (IS_OPTION(arg , "style=java"))
    {
      manuallySetJavaStyle(formatter);
      formatter.setBracketIndent(false);
      formatter.setSpaceIndentation(4);
      formatter.setBracketFormatMode(ATTACH_MODE);
      formatter.setSwitchIndent(false);
    }
  else if (IS_OPTION(arg , "style=kr"))
    {
      //manuallySetCStyle(formatter);
      formatter.setBracketIndent(false);
      formatter.setSpaceIndentation(4);
      formatter.setBracketFormatMode(ATTACH_MODE);
      formatter.setClassIndent(false);
      formatter.setSwitchIndent(false);
      formatter.setNamespaceIndent(false);
    }
  else if (IS_OPTION(arg , "style=linux"))
    {
      formatter.setBracketIndent(false);
      formatter.setSpaceIndentation(8);
      formatter.setBracketFormatMode(BDAC_MODE);
      formatter.setClassIndent(false);
      formatter.setSwitchIndent(false);
      formatter.setNamespaceIndent(false);
    }
  else if (IS_OPTIONS(arg , "c", "mode=c"))
    {
      manuallySetCStyle(formatter);
    }
  else if (IS_OPTIONS(arg , "j", "mode=java"))
    {
      manuallySetJavaStyle(formatter);
    }
  else if (IS_OPTIONS(arg, "t", "indent=tab="))
    {
      int spaceNum = 4;
      string spaceNumParam = GET_PARAMS(arg, "t", "indent=tab=");
      if (spaceNumParam.length() > 0)
        spaceNum = atoi(spaceNumParam.c_str());
      formatter.setTabIndentation(spaceNum, false);
    }
  else if (IS_OPTIONS(arg, "T", "force-indent=tab="))
    {
      int spaceNum = 4;
      string spaceNumParam = GET_PARAMS(arg, "T", "force-indent=tab=");
      if (spaceNumParam.length() > 0)
        spaceNum = atoi(spaceNumParam.c_str());
      formatter.setTabIndentation(spaceNum, true);
    }
  else if (IS_PARAM_OPTION(arg, "indent=tab"))
    {
      formatter.setTabIndentation(4);
    }
  else if (IS_PARAM_OPTIONS(arg, "s", "indent=spaces="))
    {
      int spaceNum = 4;
      string spaceNumParam = GET_PARAMS(arg, "s", "indent=spaces=");
      if (spaceNumParam.length() > 0)
        spaceNum = atoi(spaceNumParam.c_str());
      formatter.setSpaceIndentation(spaceNum);
    }
  else if (IS_PARAM_OPTION(arg, "indent=spaces"))
    {
      formatter.setSpaceIndentation(4);
    }
  else if (IS_PARAM_OPTIONS(arg, "m", "min-conditional-indent="))
    {
      int minIndent = 0;
      string minIndentParam = GET_PARAMS(arg, "m", "min-conditional-indent=");
      if (minIndentParam.length() > 0)
        minIndent = atoi(minIndentParam.c_str());
      formatter.setMinConditionalIndentLength(minIndent);
    }
  else if (IS_PARAM_OPTIONS(arg, "M", "max-instatement-indent="))
    {
      int maxIndent = 40;
      string maxIndentParam = GET_PARAMS(arg, "M", "max-instatement-indent=");
      if (maxIndentParam.length() > 0)
        maxIndent = atoi(maxIndentParam.c_str());
      formatter.setMaxInStatementIndentLength(maxIndent);
    }
  else if (IS_OPTIONS(arg, "B", "indent-brackets"))
    {
      formatter.setBracketIndent(true);
    }
  else if (IS_OPTIONS(arg, "G", "indent-blocks"))
    {
      formatter.setBlockIndent(true);
    }
  else if (IS_OPTIONS(arg, "N", "indent-namespaces"))
    {
      formatter.setNamespaceIndent(true);
    }
  else if (IS_OPTIONS(arg, "C", "indent-classes"))
    {
      formatter.setClassIndent(true);
    }
  else if (IS_OPTIONS(arg, "S", "indent-switches"))
    {
      formatter.setSwitchIndent(true);
    }
  else if (IS_OPTIONS(arg, "K", "indent-cases"))
    {
      formatter.setCaseIndent(true);
    }
  else if (IS_OPTIONS(arg, "L", "indent-labels"))
    {
      formatter.setLabelIndent(true);
    }
  else if (IS_OPTION(arg, "brackets=break-closing-headers"))
    {
      formatter.setBreakClosingHeaderBracketsMode(true);
    }
  else if (IS_OPTIONS(arg, "b", "brackets=break"))
    {
      formatter.setBracketFormatMode(BREAK_MODE);
    }
  else if (IS_OPTIONS(arg, "a", "brackets=attach"))
    {
      formatter.setBracketFormatMode(ATTACH_MODE);
    }
  else if (IS_OPTIONS(arg, "l", "brackets=linux"))
    {
      formatter.setBracketFormatMode(BDAC_MODE);
    }
  else if (IS_OPTIONS(arg, "O", "one-line=keep-blocks"))
    {
      formatter.setBreakOneLineBlocksMode(false);
    }
  else if (IS_OPTIONS(arg, "o", "one-line=keep-statements"))
    {
      formatter.setSingleStatementsMode(false);
    }
  else if (IS_OPTION(arg, "pad=paren"))
    {
      formatter.setParenthesisPaddingMode(true);
    }
  else if (IS_OPTIONS(arg, "P", "pad=all"))
    {
      formatter.setOperatorPaddingMode(true);
      formatter.setParenthesisPaddingMode(true);
    }
  else if (IS_OPTIONS(arg, "p", "pad=oper"))
    {
      formatter.setOperatorPaddingMode(true);
    }
  else if (IS_OPTIONS(arg, "E", "fill-empty-lines"))
    {
      formatter.setEmptyLineFill(true);
    }
  else if (IS_OPTION(arg, "indent-preprocessor"))
    {
      formatter.setPreprocessorIndent(true);
    }
  else if (IS_OPTION(arg, "convert-tabs"))
    {
      formatter.setTabSpaceConversionMode(true);
    }
  else if (IS_OPTION(arg, "break-blocks=all"))
    {
      formatter.setBreakBlocksMode(true);
      formatter.setBreakClosingHeaderBlocksMode(true);
    }
  else if (IS_OPTION(arg, "break-blocks"))
    {
      formatter.setBreakBlocksMode(true);
    }
  else if (IS_OPTION(arg, "break-elseifs"))
    {
      formatter.setBreakElseIfsMode(true);
    }
  else if (IS_OPTIONS(arg, "X", "errors-to-standard-output"))
    {
      _err = &cout;
    }
  else if (IS_OPTIONS(arg , "v", "version"))
    {
      (*_err) << "Artistic Style " << _version << endl;
      exit(1);
    }
  else
    {
      (*_err) << errorInfo << arg << endl;
      return false; // unknown option
    }

  return true; //o.k.
}

void importOptions(istream &in, vector<string> &optionsVector)
{
  char ch;
  string currentToken;

  while (in)
    {
      currentToken = "";
      do
        {
          in.get(ch);

          // treat '#' as line comments
          if (ch == '#')
            while (in)
              {
                in.get(ch);
                if (ch == '\n')
                  break;
              }

          // break options on spaces, tabs or new-lines
          if (ch == ' ' || ch == '\t' || ch == '\n')
            break;
          else
            currentToken.append(1, ch);
        }
      while (in);

      if (currentToken.length() != 0)
        optionsVector.push_back(currentToken);
    }
}

bool stringEndsWith(const string &str, const string &suffix)
{
  int strIndex = str.length() - 1;
  int suffixIndex = suffix.length() - 1;

  while (strIndex >= 0 && suffixIndex >= 0)
    {
      if (tolower(str[strIndex]) != tolower(suffix[suffixIndex]))
        return false;

      --strIndex;
      --suffixIndex;
    }

  return true;
}

void printHelp()
{
  (*_err) << endl;
  (*_err) << "Artistic Style " << _version << "   (http://www.bigfoot.com/~davidsont/astyle)\n";
  (*_err) << "                       (created by Tal Davidson, davidsont@bigfoot.com)\n";
  (*_err) << endl;
  (*_err) << "Usage  :  astyle [options] < Original > Beautified\n";
  (*_err) << "          astyle [options] Foo.cpp Bar.cpp  [...]\n";
  (*_err) << endl;
  (*_err) << "When indenting a specific file, the resulting indented file RETAINS the\n";
  (*_err) << "original file-name. The original pre-indented file is renamed, with a\n";
  (*_err) << "suffix of \".orig\" added to the original filename.\n";
  (*_err) << endl;
  (*_err) << "By default, astyle is set up to indent C/C++/C# files, with 4 spaces per\n";
  (*_err) << "indent, a maximal indentation of 40 spaces inside continuous statements,\n";
  (*_err) << "and NO formatting.\n";
  (*_err) << endl;
  (*_err) << "Option's Format:\n";
  (*_err) << "----------------\n";
  (*_err) << "    Long options (starting with '--') must be written one at a time.\n";
  (*_err) << "    Short options (starting with '-') may be appended together.\n";
  (*_err) << "    Thus, -bps4 is the same as -b -p -s4.\n";
  (*_err) << endl;
  (*_err) << "Predefined Styling options:\n";
  (*_err) << "--------------------\n";
  (*_err) << "    --style=ansi\n";
  (*_err) << "    ANSI style formatting/indenting.\n";
  (*_err) << endl;
  (*_err) << "    --style=kr\n";
  (*_err) << "    Kernighan&Ritchie style formatting/indenting.\n";
  (*_err) << endl;
  (*_err) << "    --style=gnu\n";
  (*_err) << "    GNU style formatting/indenting.\n";
  (*_err) << endl;
  (*_err) << "    --style=java\n";
  (*_err) << "    Java mode, with standard java style formatting/indenting.\n";
  (*_err) << endl;
  (*_err) << "    --style=linux\n";
  (*_err) << "    Linux mode (i.e. 8 spaces per indent, break definition-block\n";
  (*_err) << "    brackets but attach command-block brackets.\n";
  (*_err) << endl;
  (*_err) << "Indentation options:\n";
  (*_err) << "--------------------\n";
  (*_err) << "    -c   OR   --mode=c\n";
  (*_err) << "    Indent a C, C++ or C# source file (default)\n";
  (*_err) << endl;
  (*_err) << "    -j   OR   --mode=java\n";
  (*_err) << "    Indent a Java(TM) source file\n";
  (*_err) << endl;
  (*_err) << "    -s   OR   -s#   OR   --indent=spaces=#\n";
  (*_err) << "    Indent using # spaces per indent. Not specifying #\n";
  (*_err) << "    will result in a default of 4 spacec per indent.\n";
  (*_err) << endl;
  (*_err) << "    -t   OR   -t#   OR   --indent=tab=#\n";
  (*_err) << "    Indent using tab characters, assuming that each\n";
  (*_err) << "    tab is # spaces long. Not specifying # will result\n";
  (*_err) << "    in a default assumption of 4 spaces per tab.\n";
  (*_err) << endl;
  (*_err) << "    -T#   OR   --force-indent=tab=#";
  (*_err) << "    Indent using tab characters, assuming that each\n";
  (*_err) << "    tab is # spaces long. Force tabs to be used in areas\n";
  (*_err) << "    Astyle would prefer to use spaces.\n";
  (*_err) << endl;
  (*_err) << "    -C   OR   --indent-classes\n";
  (*_err) << "    Indent 'class' blocks, so that the inner 'public:',\n";
  (*_err) << "    'protected:' and 'private: headers are indented in\n";
  (*_err) << "    relation to the class block.\n";
  (*_err) << endl;
  (*_err) << "    -S   OR   --indent-switches\n";
  (*_err) << "    Indent 'switch' blocks, so that the inner 'case XXX:'\n";
  (*_err) << "    headers are indented in relation to the switch block.\n";
  (*_err) << endl;
  (*_err) << "    -K   OR   --indent-cases\n";
  (*_err) << "    Indent 'case XXX:' lines, so that they are flush with\n";
  (*_err) << "    their bodies..\n";
  (*_err) << endl;
  (*_err) << "    -N   OR   --indent-namespaces\n";
  (*_err) << "    Indent the contents of namespace blocks.\n";
  (*_err) << endl;
  (*_err) << "    -B   OR   --indent-brackets\n";
  (*_err) << "    Add extra indentation to '{' and '}' block brackets.\n";
  (*_err) << endl;
  (*_err) << "    -G   OR   --indent-blocks\n";
  (*_err) << "    Add extra indentation entire blocks (including brackets).\n";
  (*_err) << endl;
  (*_err) << "    -L   OR   --indent-labels\n";
  (*_err) << "    Indent labels so that they appear one indent less than\n";
  (*_err) << "    the current indentation level, rather than being\n";
  (*_err) << "    flushed completely to the left (which is the default).\n";
  (*_err) << endl;
  (*_err) << "    -m#  OR  --min-conditional-indent=#\n";
  (*_err) << "    Indent a minimal # spaces in a continuous conditional\n";
  (*_err) << "    belonging to a conditional header.\n";
  (*_err) << endl;
  (*_err) << "    -M#  OR  --max-instatement-indent=#\n";
  (*_err) << "    Indent a maximal # spaces in a continuous statement,\n";
  (*_err) << "    relatively to the previous line.\n";
  (*_err) << endl;
  (*_err) << "    -E  OR  --fill-empty-lines\n";
  (*_err) << "    Fill empty lines with the white space of their\n";
  (*_err) << "    previous lines.\n";
  (*_err) << endl;
  (*_err) << "    --indent-preprocessor\n";
  (*_err) << "    Indent multi-line #define statements\n";
  (*_err) << endl;
  (*_err) << "Formatting options:\n";
  (*_err) << "-------------------\n";
  (*_err) << "    -b  OR  --brackets=break\n";
  (*_err) << "    Break brackets from pre-block code (i.e. ANSI C/C++ style).\n";
  (*_err) << endl;
  (*_err) << "    -a  OR  --brackets=attach\n";
  (*_err) << "    Attach brackets to pre-block code (i.e. Java/K&R style).\n";
  (*_err) << endl;
  (*_err) << "    -l  OR  --brackets=linux\n";
  (*_err) << "    Break definition-block brackets and attach command-block\n";
  (*_err) << "    brackets.\n";
  (*_err) << endl;
  (*_err) << "    --brackets=break-closing-headers\n";
  (*_err) << "    Break brackets before closing headers (e.g. 'else', 'catch', ..).\n";
  (*_err) << "    Should be appended to --brackets=attach or --brackets=linux.\n";
  (*_err) << endl;
  (*_err) << "    -o   OR  --one-line=keep-statements\n";
  (*_err) << "    Don't break lines containing multiple statements into\n";
  (*_err) << "    multiple single-statement lines.\n";
  (*_err) << endl;
  (*_err) << "    -O   OR  --one-line=keep-blocks\n";
  (*_err) << "    Don't break blocks residing completely on one line\n";
  (*_err) << endl;
  (*_err) << "    -p   OR  --pad=oper\n";
  (*_err) << "    Insert space paddings around operators only.\n";
  (*_err) << endl;
  (*_err) << "    --pad=paren\n";
  (*_err) << "    Insert space paddings around parenthesies only.\n";
  (*_err) << endl;
  (*_err) << "    -P   OR  --pad=all\n";
  (*_err) << "    Insert space paddings around operators AND parenthesies.\n";
  (*_err) << endl;
  (*_err) << "    --convert-tabs\n";
  (*_err) << "    Convert tabs to spaces.\n";
  (*_err) << endl;
  (*_err) << "    --break-blocks\n";
  (*_err) << "    Insert empty lines around unrelated blocks, labels, classes, ...\n";
  (*_err) << endl;
  (*_err) << "    --break-blocks=all\n";
  (*_err) << "    Like --break-blocks, except also insert empty lines \n";
  (*_err) << "    around closing headers (e.g. 'else', 'catch', ...).\n";
  (*_err) << endl;
  (*_err) << "    --break-elseifs\n";
  (*_err) << "    Break 'else if()' statements into two different lines.\n";
  (*_err) << endl;
  (*_err) << "Other options:\n";
  (*_err) << "-------------\n";
  (*_err) << "    --suffix=####\n";
  (*_err) << "    Append the suffix #### instead of '.orig' to original filename.\n";
  (*_err) << endl;
  (*_err) << "    -X   OR  --errors-to-standard-output\n";
  (*_err) << "    Print errors and help information to standard-output rather than\n";
  (*_err) << "    to standard-error.\n";
  (*_err) << endl;
  (*_err) << "    -v   OR   --version\n";
  (*_err) << "    Print version number\n";
  (*_err) << endl;
  (*_err) << "    -h   OR   -?   OR   --help\n";
  (*_err) << "    Print this help message\n";
  (*_err) << endl;
  (*_err) << "Default options file:\n";
  (*_err) << "---------------------\n";
  (*_err) << "    Artistic Style looks for a default options file in the\n";
  (*_err) << "    following order:\n";
  (*_err) << "    1. The contents of the ARTISTIC_STYLE_OPTIONS environment\n";
  (*_err) << "       variable if it exists.\n";
  (*_err) << "    2. The file called .astylerc in the directory pointed to by the\n";
  (*_err) << "       HOME environment variable (i.e. $HOME/.astylerc).\n";
  (*_err) << "    3. The file called .astylerc in the directory pointed to by the\n";
  (*_err) << "       HOMEPATH environment variable (i.e. %HOMEPATH%\\.astylerc).\n";
  (*_err) << "    If a default options file is found, the options in this file\n";
  (*_err) << "    will be parsed BEFORE the command-line options.\n";
  (*_err) << "    Options within the default option file may be written without\n";
  (*_err) << "    the preliminary '-' or '--'.\n";
  (*_err) << endl;
}

int main(int argc, char *argv[])
{
  ASFormatter formatter;
  vector<string> fileNameVector;
  vector<string> optionsVector;
  string optionsFileName = "";
  string arg;
  bool ok = true;
  bool shouldPrintHelp = false;
  bool shouldParseOptionsFile = true;

  _err = &cerr;
  _suffix = ".orig";
  _modeManuallySet = false;

  // manage flags
  for (int i = 1; i < argc; i++)
    {
      arg = string(argv[i]);

      if (IS_PARAM_OPTION(arg , "--options=none"))
        {
          shouldParseOptionsFile = false;
        }
      else if (IS_PARAM_OPTION(arg , "--options="))
        {
          optionsFileName = GET_PARAM(arg, "--options=");
        }
      else if (IS_OPTION(arg, "-h")
                || IS_OPTION(arg, "--help")
                || IS_OPTION(arg, "-?"))
        {
          shouldPrintHelp = true;
        }
      else if (arg[0] == '-')
        {
          optionsVector.push_back(arg);
        }
      else // file-name
        {
          fileNameVector.push_back(arg);
        }
    }

  // parse options file
  if (shouldParseOptionsFile)
    {
      if (optionsFileName.compare("") == 0)
        {
          char* env = getenv("ARTISTIC_STYLE_OPTIONS");
          if (env != NULL)
            optionsFileName = string(env);
        }
      if (optionsFileName.compare("") == 0)
        {
          char* env = getenv("HOME");
          if (env != NULL)
            optionsFileName = string(env) + string("/.astylerc");
        }
      if (optionsFileName.compare("") == 0)
        {
          char* env = getenv("HOMEPATH");
          if (env != NULL)
            optionsFileName = string(env) + string("/.astylerc");
        }

      if (optionsFileName.compare("") != 0)
        {
          ifstream optionsIn(optionsFileName.c_str());
          if (optionsIn)
            {
              vector<string> fileOptionsVector;
              importOptions(optionsIn, fileOptionsVector);
              ok = parseOptions(formatter,
                                fileOptionsVector.begin(),
                                fileOptionsVector.end(),
                                string("Unknown option in default options file: "));
            }

          optionsIn.close();
          if (!ok)
            {
              (*_err) << "For help on options, type 'astyle -h' " << endl;
            }
        }
    }

  // parse options from command line

  ok = parseOptions(formatter,
                    optionsVector.begin(),
                    optionsVector.end(),
                    string("Unknown command line option: "));
  if (!ok)
    {
      (*_err) << "For help on options, type 'astyle -h' " << endl;
      exit(1);
    }

  if (shouldPrintHelp)
    {
      printHelp();
      exit(1);
    }

  // if no files have been given, use cin for input and cout for output
  if (fileNameVector.empty())
    {
      formatter.init(new ASStreamIterator(&cin));

      while (formatter.hasMoreLines())
        {
          cout << formatter.nextLine();
          if (formatter.hasMoreLines())
            cout << endl;
        }
      cout.flush();
    }
  else
    {
      // indent the given files
      for (int i = 0; i < fileNameVector.size(); i++)
        {
          string originalFileName = fileNameVector[i];
          string inFileName = originalFileName + _suffix;

          remove(inFileName.c_str());

          if (rename(originalFileName.c_str(), inFileName.c_str()) < 0)
            error("Could not rename ", string(originalFileName + " to " + inFileName).c_str());

          ifstream in(inFileName.c_str());
          if (!in)
            error("Could not open input file", inFileName.c_str());

          ofstream out(originalFileName.c_str());
          if (!out)
            error("Could not open output file", originalFileName.c_str());

          // Unless a specific language mode has been, set the language mode
          // according to the file's suffix.
          if (!_modeManuallySet)
            {
              if (stringEndsWith(originalFileName, string(".java")))
                {
                  formatter.setJavaStyle();
                }
              else
                {
                  formatter.setCStyle();
                }
            }

          formatter.init(new ASStreamIterator(&in));
          while (formatter.hasMoreLines())
            {
              out << formatter.nextLine();
              if (formatter.hasMoreLines())
                out << endl;
            }

          out.flush();
          out.close();

          in.close();
        }
    }
  return 0;
}
