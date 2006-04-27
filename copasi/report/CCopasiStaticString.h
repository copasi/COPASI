/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiStaticString.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:31:09 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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

#include "CCopasiObject.h"

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

    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

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

    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    CCopasiReportSeparator & operator = (const std::string & rhs);
  };
#endif // COPASI_CCopasiStaticString
