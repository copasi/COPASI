// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <algorithm>
#include <cmath>
#include <limits>
#include <string>
#include <sstream>
#include <iostream>

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "copasi.h"

#include "utility.h"
#include "CCopasiMessage.h"

std::string ISODateTime(tm * pTime)
{
  char str[20];

  if (pTime)
    {
      sprintf(str, "%d-%.02d-%.02d %.02d:%.02d:%.02d",
              pTime->tm_year + 1900,
              pTime->tm_mon + 1,
              pTime->tm_mday,
              pTime->tm_hour,
              pTime->tm_min,
              pTime->tm_sec);
    }
  else
    {
      sprintf(str, "0000-00-00 00:00:00");
    }

  return (std::string) str;
}

std::string LocalTimeStamp()
{
  time_t Time;
  time(&Time);

  tm *sTime = NULL;
  sTime = localtime(&Time);

  return ISODateTime(sTime);
}

std::string UTCTimeStamp()
{
  time_t Time;
  time(&Time);

  tm *sTime = NULL;
  sTime = gmtime(&Time);

  return ISODateTime(sTime);
}

bool isNumber(const std::string & str)
{
  if (str.find_first_of("+-.0123456789")) return false;

  const char * Tail;
  strToDouble(str.c_str(), & Tail);

  if (*Tail) return false;

  return true;
}

std::string StringPrint(const char * format, ...)
{
  C_INT32 TextSize = INITIALTEXTSIZE;
  C_INT32 Printed = 0;

  char *Text = NULL;

  Text = new char[TextSize + 1];

  va_list Arguments; // = NULL;
  va_start(Arguments, format);
  Printed = vsnprintf(Text, TextSize + 1, format, Arguments);
  va_end(Arguments);

  while (Printed < 0 || TextSize < Printed)
    {
      delete [] Text;

      (Printed < 0) ? TextSize *= 2 : TextSize = Printed;
      Text = new char[TextSize + 1];

      va_list Arguments; // = NULL;
      va_start(Arguments, format);
      Printed = vsnprintf(Text, TextSize + 1, format, Arguments);
      va_end(Arguments);
    }

  std::string Result = Text;

  delete [] Text;
  return Result;
}

std::string unQuote(const std::string & name)
{
  std::string Name = name;
  std::string::size_type len = Name.length();

  if (len > 1 && Name[0] == '"' && Name[len - 1] == '"')
    {
      // Remove surrounding double quotes.
      Name = Name.substr(1, len - 2);

      // Remove escape sequences.
      std::string::size_type pos = Name.find("\\");

      while (pos != std::string::npos)
        {
          Name.erase(pos, 1);
          pos++;
          pos = Name.find("\\", pos);
        }
    }

  return Name;
}

std::string quote(const std::string & name,
                  const std::string & additionalEscapes)
{
  if (name.find_first_of(" \"" + additionalEscapes) == std::string::npos)
    return name;

#define toBeEscaped "\\\""
  std::string Escaped(name);
  std::string::size_type pos = Escaped.find_first_of(toBeEscaped);

  while (pos != std::string::npos)
    {
      Escaped.insert(pos, "\\");
      pos += 2;
      pos = Escaped.find_first_of(toBeEscaped, pos);
    }

  return "\"" + Escaped + "\"";
#undef toBeEscaped
}

bool stringReplace(std::string & str, const std::string & target, const std::string & replacement)
{
  bool replaced = false;

  std::string::size_type pos = str.find(target, 0);

  while (pos != std::string::npos)
    {
      replaced = true;

      str.replace(pos, target.length(), replacement, 0, std::string::npos);
      pos = str.find(target, 0);
    }

  return replaced;
}

/*
 * Fixes a string to be a SName element from SBML
 * (this is a destructive function, some changes are irreversible)
 *
 */

void FixSName(const std::string &original, std::string &fixed)
{
  size_t i, len;

  // check reserved names
  if (original == "abs") {fixed = "_abs"; return;}

  if (original == "acos") {fixed = "_acos"; return;}

  if (original == "and") {fixed = "_and"; return;}

  if (original == "asin") {fixed = "_asin"; return;}

  if (original == "atan") {fixed = "_atan"; return;}

  if (original == "ceil") {fixed = "_ceil"; return;}

  if (original == "cos") {fixed = "_cos"; return;}

  if (original == "exp") {fixed = "_exp"; return;}

  if (original == "floor") {fixed = "_floor"; return;}

  if (original == "hilli") {fixed = "_hilli"; return;}

  if (original == "hillmmr") {fixed = "_hillmmr"; return;}

  if (original == "hillmr") {fixed = "_hillmr"; return;}

  if (original == "hillr") {fixed = "_hillr"; return;}

  if (original == "isouur") {fixed = "_isouur"; return;}

  if (original == "log") {fixed = "_log"; return;}

  if (original == "log10") {fixed = "_log10"; return;}

  if (original == "massi") {fixed = "_massi"; return;}

  if (original == "massr") {fixed = "_massr"; return;}

  if (original == "not") {fixed = "_not"; return;}

  if (original == "or") {fixed = "_or"; return;}

  if (original == "ordbbr") {fixed = "_ordbbr"; return;}

  if (original == "ordbur") {fixed = "_ordbur"; return;}

  if (original == "ordubr") {fixed = "_ordubr"; return;}

  if (original == "pow") {fixed = "_pow"; return;}

  if (original == "ppbr") {fixed = "_ppbr"; return;}

  if (original == "sin") {fixed = "_sin"; return;}

  if (original == "sqr") {fixed = "_sqr"; return;}

  if (original == "sqrt") {fixed = "_sqrt"; return;}

  if (original == "substance") {fixed = "_substance"; return;}

  if (original == "time") {fixed = "_time"; return;}

  if (original == "tan") {fixed = "_tan"; return;}

  if (original == "umai") {fixed = "_umai"; return;}

  if (original == "umar") {fixed = "_umar"; return;}

  if (original == "uai") {fixed = "_uai"; return;}

  if (original == "ualii") {fixed = "_ualii"; return;}

  if (original == "uar") {fixed = "_uar"; return;}

  if (original == "ucii") {fixed = "_ucii"; return;}

  if (original == "ucir") {fixed = "_ucir"; return;}

  if (original == "ucti") {fixed = "_ucti"; return;}

  if (original == "uctr") {fixed = "_uctr"; return;}

  if (original == "uhmi") {fixed = "_uhmi"; return;}

  if (original == "uhmr") {fixed = "_uhmr"; return;}

  if (original == "umi") {fixed = "_umi"; return;}

  if (original == "unii") {fixed = "_unii"; return;}

  if (original == "unir") {fixed = "_unir"; return;}

  if (original == "uuhr") {fixed = "_uuhr"; return;}

  if (original == "umr") {fixed = "_umr"; return;}

  if (original == "usii") {fixed = "_usii"; return;}

  if (original == "usir") {fixed = "_usir"; return;}

  if (original == "uuci") {fixed = "_uuci"; return;}

  if (original == "uucr") {fixed = "_uucr"; return;}

  if (original == "uui") {fixed = "_uui"; return;}

  if (original == "uur") {fixed = "_uur"; return;}

  if (original == "volume") {fixed = "_volume"; return;}

  if (original == "xor") {fixed = "_xor"; return;}

  len = original.length();

  // check rule for initial characters
  // if first not a letter...
  if (((original[0] < 'A') || (original[0] > 'z')) && (original[0] != '_'))
    {
      if ((original[0] >= '0') && (original[0] <= '9'))
        fixed = "_" + original;
      else
        {fixed = original; fixed [0] = '_';}
    }
  else
    fixed = original;

  len = fixed.length();

  for (i = 1; i < len; i++)
    if ((fixed [i] != '_') && ((fixed [i] < 'A') || (fixed [i] > 'z')) &&
        ((fixed [i] < '0') || (fixed [i] > '9')))
      fixed [i] = '_';
}

double strToDouble(const char * str,
                   char const ** pTail)
{
  double Value = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  if (pTail != NULL)
    {
      *pTail = str;
    }

  if (str == NULL || *str == 0x0)
    {
      return Value;
    }

  std::istringstream in;

  in.imbue(std::locale::classic());
  in.str(str);

  in >> Value;

  if (pTail != NULL && !isnan(Value))
    {
      *pTail = str + std::min< size_t >(in.tellg(), strlen(str));
    }

  return Value;
}
C_INT32 strToInt(const char * str,
                 char const ** pTail)
{
  C_INT32 Value = std::numeric_limits< C_INT32 >::quiet_NaN();

  if (pTail != NULL)
    {
      *pTail = str;
    }

  if (str == NULL || *str == 0x0)
    {
      return Value;
    }

  std::istringstream in;

  in.imbue(std::locale::classic());
  in.str(str);

  in >> Value;

  if (pTail != NULL && !isnan(Value))
    {
      *pTail = str + std::min< size_t >(in.tellg(), strlen(str));
    }

  return Value;
}

unsigned C_INT32 strToUnsignedInt(const char * str,
                                  char const ** pTail)
{
  unsigned C_INT32 Value = std::numeric_limits< unsigned C_INT32 >::quiet_NaN();

  if (pTail != NULL)
    {
      *pTail = str;
    }

  if (str == NULL || *str == 0x0)
    {
      return Value;
    }

  std::istringstream in;

  in.imbue(std::locale::classic());
  in.str(str);

  in >> Value;

  if (pTail != NULL && !isnan(Value))
    {
      *pTail = str + std::min< size_t >(in.tellg(), strlen(str));
    }

  return Value;
}

void * stringToPointer(const std::string str)
{
  void * pPointer;

  sscanf(str.c_str(), "%p", &pPointer);

  return pPointer;
}

std::string pointerToString(const void * pVoid)
{
  char String[19];

  int Printed = sprintf(String, "%p", pVoid);

  if (Printed < 0 || 18 < Printed)
    {
      fatalError();
    }

  return String;
}

std::string nameToSbmlId(const std::string & name)
{
  // We convert all non allowed characters to '_'
  // letter ::= ’a’..’z’,’A’..’Z’
  // digit  ::= ’0’..’9’
  // idChar ::= letter | digit | ’_’
  // SId    ::= (letter | ’_’ ) idChar*

  std::ostringstream IdStream;

  std::string::const_iterator it = name.begin();
  std::string::const_iterator end = name.end();

  if ('0' <= *it && *it <= '9')
    {
      IdStream << '_';
    }

  for (; it != end; ++it)
    {
      // second, third or forth character of a multi-byte encoding
      if (0x80 == (*it & 0xc0))
        {
          continue;
        }

      if (('0' <= *it && *it <= '9') ||
          ('a' <= *it && *it <= 'z') ||
          ('A' <= *it && *it <= 'Z'))
        {
          IdStream << *it;
        }
      else
        {
          IdStream << '_';
        }
    }

  std::string Id = IdStream.str();

  if (Id[Id.length() - 1] != '_')
    {
      return Id;
    }

  return Id.substr(0, Id.length() - 1);
}
