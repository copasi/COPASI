/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/utility.h,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: shoops $
   $Date: 2012/04/20 14:53:47 $
   End CVS Header */

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_utilities
#define COPASI_utilities

#include <string>
#include <string.h>
// #include <stdio.h>
#include <stdarg.h>

#define INITIALTEXTSIZE 1024

struct tm;

/**
 * Returns the time pointed to by pTime in ISO format
 */
std::string ISODateTime(tm * pTime);

/**
 * Returns the current local time in ISO format
 */
std::string LocalTimeStamp();

/**
 * Returns the current time in ISO format
 */
std::string UTCTimeStamp();

/**
 * Check whether the given string represents a number
 * @param const std::string & str
 * @return bool isNumber
 */
bool isNumber(const std::string & str);

/**
 *  sprintf like function for strings
 *  @param "const char *" format sprintf like format string
 *  @param ...
 *  @return "string"
 */
std::string StringPrint(const char * format, ...);

/**
 * Unesacape a quoted name. If the name is surrounded by quotes
 * these are removed and included escape sequences '\.' are reduced
 * to '.' else the name is returned unmodified.
 * @param const std::string & name
 * @return std::string unQuote
 */
std::string unQuote(const std::string & name);

/**
 * Surround a name with quotes if the name contains a space or
 * double quote else the name is returned unmodified. In the
 * quoted name " and \ are escaped. The parameter additionalEscapes
 * forces quotes around names containing any of the character in the
 * parameter.
 * @param const std::string & name
 * @param const std::string & additionalEscapes (default: "")
 * @return std::string quote
 */
std::string quote(const std::string & name,
                  const std::string & additionalEscapes = "");

/*
 * Fixes a string to be a SName element from SBML
 * (this is a destructive function, some changes are irreversible)
 *
 */
void FixSName(const std::string &original, std::string &fixed)
;

/*
 * Fixes a string to a XHTML valid equivalent
 */
void FixXHTML(const std::string &original, std::string &fixed)
;

/**
  * Convert an attribute to enum. If attribute is NULL
  * or no matching name is found the parameter enumDefault is returned.
  * Note: enumNames must be zero terminated.
  * @param const char * attribute
  * @param const char ** enumNames
  * @param const CType & enumDefault
  * @return CType enum
  */
template <class CType> CType toEnum(const char * attribute,
                                    const char ** enumNames,
                                    const CType & enumDefault)
{
  if (!attribute) return enumDefault;

  for (int i = 0; *enumNames; i++, enumNames++)
    if (!strcmp(attribute, *enumNames)) return static_cast< CType >(i);

  return enumDefault;
}

/**
  * Convert an attribute to enum. If attribute is ""
  * or no matching name is found the parameter enumDefault is returned.
  * Note: enumNames must be zero terminated.
  * @param const std::string & attribute
  * @param const std::string * enumNames
  * @param const CType & enumDefault
  * @return CType enum
  */
template <class CType> CType toEnum(const std::string & attribute,
                                    const std::string * enumNames,
                                    const CType & enumDefault)
{
  if (attribute == "") return enumDefault;

  for (int i = 0; *enumNames != ""; i++, enumNames++)
    if (attribute == *enumNames) return static_cast< CType >(i);

  return enumDefault;
}

/**
 * Convert a character sequence to a double
 * @param const char * str
 * @param char const ** pTail (default: NULL)
 * @return double
 */
double strToDouble(const char * str,
                   char const ** pTail = NULL);

/**
 * Convert a character sequence to a double
 * @param const char * str
 * @param char const ** pTail (default: NULL)
 * @return C_INT32
 */
C_INT32 strToInt(const char * str,
                 char const ** pTail = NULL);

/**
 * Convert a character sequence to a double
 * @param const char * str
 * @param char const ** pTail (default: NULL)
 * @return unsigned C_INT32
 */
unsigned C_INT32 strToUnsignedInt(const char * str,
                                  char const ** pTail = NULL);

/**
 * Convert a character sequence to a void pointer
 * @param const std::string str
 * @return void * pVoid
 */
void * stringToPointer(const std::string str);

/**
 * Convert a void pointer to a string
 * @param const void * pVoid
 * @return std::string str
 */
std::string pointerToString(const void * pVoid);


#endif // COPASI_utilities
