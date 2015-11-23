// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * Class CCopasiStaticString
 *
 * This class is the class for storing Copasi Static String Names.
 *
 * Copyright Liang Xu 2002
 */

#ifndef COPASI_CCopasiStaticString
#define COPASI_CCopasiStaticString

#include <string>

#include "report/CCopasiObject.h"

class CCopasiStaticString: public CCopasiObject
{
  // Attributes
private:
  std::string mStaticString;

  // Operations
public:
  CCopasiStaticString(const std::string & name = "",
                      const CCopasiContainer * pParent = NULL,
                      const std::string & type = "String",
                      const unsigned C_INT32 & flag = CCopasiObject::StaticString);

  CCopasiStaticString(const CCopasiStaticString & src,
                      const CCopasiContainer * pParent = NULL);

  ~CCopasiStaticString();

  virtual std::string getObjectDisplayName() const;

  CCopasiStaticString & operator = (const std::string & rhs);

  virtual void print(std::ostream * ostream) const;

  const std::string & getStaticString() const;
};

class CCopasiReportSeparator: public CCopasiStaticString
{
public:
  CCopasiReportSeparator(const std::string & name = "",
                         const CCopasiContainer * pParent = NULL);

  CCopasiReportSeparator(const CCopasiStaticString & src,
                         const CCopasiContainer * pParent = NULL);

  ~CCopasiReportSeparator();

  virtual std::string getObjectDisplayName() const;

  CCopasiReportSeparator & operator = (const std::string & rhs);
};
#endif // COPASI_CCopasiStaticString
