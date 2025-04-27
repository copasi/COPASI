// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <string>

#ifndef COPASI_CLocaleString
#define COPASI_CLocaleString

class CLocaleString
{
public:
#if defined(WIN32) && !defined(__MINGW32__) && !defined(__MINGW64__)
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
