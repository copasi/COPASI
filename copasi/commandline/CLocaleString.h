// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commandline/CLocaleString.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:26:18 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <string>

#ifndef COPASI_CLocaleString
#define COPASI_CLocaleString

class CLocaleString
{
public:
#ifdef WIN32
  typedef wchar_t lchar;
#else
  typedef char lchar;
#endif

  static CLocaleString fromUtf8(const std::string & utf8);

  // Operations
  CLocaleString();

  CLocaleString(const lchar * str);

  CLocaleString(const CLocaleString & src);

  ~CLocaleString();

  CLocaleString & operator = (const CLocaleString & rhs);

  CLocaleString & operator = (const lchar * str);

  std::string toUtf8() const;

  const lchar * c_str() const;

private:
  // Attributes
  lchar * mpStr;
};

#endif // COPASI_CLocaleString
