// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/core/CDataObject.h"

class CCopasiStaticString: public CDataObject
{
  // Attributes
private:
  std::string mStaticString;

protected:
  CCopasiStaticString(const CCopasiStaticString & src);

  // Operations
public:
  CCopasiStaticString(const std::string & name = "",
                      const CDataContainer * pParent = NO_PARENT,
                      const std::string & type = "String",
                      const CFlags< Flag > & flag = CFlags< Flag >::None);

  CCopasiStaticString(const CCopasiStaticString & src,
                      const CDataContainer * pParent);

  ~CCopasiStaticString();

  virtual std::string getObjectDisplayName() const;

  CCopasiStaticString & operator = (const std::string & rhs);

  virtual void print(std::ostream * ostream) const;

  const std::string & getStaticString() const;
};

class CCopasiReportSeparator: public CCopasiStaticString
{
protected:
  CCopasiReportSeparator(const CCopasiReportSeparator & src);

public:
  CCopasiReportSeparator(const std::string & name = "",
                         const CDataContainer * pParent = NO_PARENT);

  CCopasiReportSeparator(const CCopasiStaticString & src,
                         const CDataContainer * pParent);

  ~CCopasiReportSeparator();

  virtual std::string getObjectDisplayName() const;

  CCopasiReportSeparator & operator = (const std::string & rhs);
};
#endif // COPASI_CCopasiStaticString
