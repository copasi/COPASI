/**
 * Class CCopasiStaticString
 *
 * This class is the class for storing Copasi Static String Names.
 *
 * Copyright Liang Xu 2002
 */

#ifndef COPASI_CCopasiStaticString
#define COPASI_CCopasiStaticString

#include "CCopasiObject.h"
#include <string>

class CCopasiStaticString: public CCopasiObject
  {
    // Operations
  private:
    std::string strObject;
  public:
    CCopasiStaticString();

    CCopasiStaticString(const std::string & name);

    ~CCopasiStaticString();

    void cleanup();

    const std::string& getStaticString()
    {
      return strObject;
    }
  };
#endif // COPASI_CCopasiStaticString
