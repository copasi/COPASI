/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiStaticString.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/12 22:14:25 $
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
                        const CCopasiContainer * pParent = NULL);

    CCopasiStaticString(const CCopasiStaticString & src,
                        const CCopasiContainer * pParent = NULL);

    ~CCopasiStaticString();

    CCopasiStaticString & operator = (const std::string & rhs);

    virtual void print(std::ostream * ostream) const;

    const std::string & getStaticString() const;
  };
#endif // COPASI_CCopasiStaticString
