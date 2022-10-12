// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_utilities
#define COPASI_utilities

#include <string>
#include <array>
#include <string.h>
// #include <stdio.h>
#include <stdarg.h>
#include "copasi/copasi.h"

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
 * Converts the UTC time to time_t
 * @param const std::string utc
 * @return time_t time
 */
time_t timeFromUTC(const std::string utc);

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
/**
 * Replaces the all occurrences of target string in str with the replacement
 * and returns true if the target string was replaced
 * @param std::string & str
 * @param const std::string & target
 * @param const std::string & replacement
 * @return bool replaced
 */
bool stringReplace(std::string & str,
                   const std::string & target,
                   const std::string & replacement);

/*
 * Fixes a string to be a SName element from SBML
 * (this is a destructive function, some changes are irreversible)
 *
 */
void FixSName(const std::string &original, std::string &fixed)
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
 * Convert a string to a size_t index. Returns true if the conversion
 * is successful, i.e., the whole string has been converted.
 * @param const std::string & str
 * @param size_t & index
 * @return bool success
 */
bool strToIndex(const std::string & str, size_t & index);

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

/**
 * Convert a utf8 encoded name to a XmlId
 * @param const std::string & name
 * @return std::string SbmlId
 */
std::string nameToSbmlId(const std::string & name);

/**
 * Test whether a given XML tag is present in the first number of lines
 * of a given file.
 *
 * @param filename the filename to be tested
 * @param tagname the tag name to be tested for
 * @param numLines the number of lines to be tested (default 10)
 *
 * @return boolean indicating whether the tag appeared in the first numLines.
 */
bool containsTag(const std::string & filename, const std::string & tagname, int numLines = 10);

/**
 * Tests whether the file is SBML by reading the first 10 lines and looking
 * for the presence of the sbml tag.
 *
 * @param filename the filename to be tested
 *
 * @return true, if the first 10 lines contain the sbml tag, false otherwise.
 */
bool isProbablySBML(const std::string & filename);

/**
 * calculate the number of utf8 characters in a givent string
 *
 * @param const std::string & str
 * @return size_t utf8Length
 */
size_t utf8Length(const std::string & str);

#endif // COPASI_utilities
