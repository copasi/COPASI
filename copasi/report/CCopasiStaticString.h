/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiStaticString.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:01 $
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
