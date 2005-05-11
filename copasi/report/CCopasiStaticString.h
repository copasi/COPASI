/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiStaticString.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/11 17:46:17 $
   End CVS Header */

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

    CCopasiReportSeparator & operator = (const std::string & rhs);
  };
#endif // COPASI_CCopasiStaticString
