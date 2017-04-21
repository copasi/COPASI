// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
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

class CDataString: public CDataObject
{
  // Attributes
private:
  std::string mStaticString;

protected:
  CDataString(const CDataString & src);

  // Operations
public:
  CDataString(const std::string & name = "",
              const CDataContainer * pParent = NO_PARENT,
              const std::string & type = "String",
              const CFlags< Flag > & flag = CFlags< Flag >::None);

  CDataString(const CDataString & src,
              const CDataContainer * pParent);

  ~CDataString();

  virtual std::string getObjectDisplayName() const;

  CDataString & operator = (const std::string & rhs);

  virtual void print(std::ostream * ostream) const;

  const std::string & getStaticString() const;
};

class CCopasiReportSeparator: public CDataString
{
protected:
  CCopasiReportSeparator(const CCopasiReportSeparator & src);

public:
  CCopasiReportSeparator(const std::string & name = "",
                         const CDataContainer * pParent = NO_PARENT);

  CCopasiReportSeparator(const CDataString & src,
                         const CDataContainer * pParent);

  ~CCopasiReportSeparator();

  virtual std::string getObjectDisplayName() const;

  CCopasiReportSeparator & operator = (const std::string & rhs);
};
#endif // COPASI_CCopasiStaticString
