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
  public:
    CCopasiStaticString(const std::string & name = "",
                        const CCopasiContainer * pParent = NULL);

    CCopasiStaticString(const CCopasiStaticString & src,
                        const CCopasiContainer * pParent = NULL);

    ~CCopasiStaticString();

    void cleanup();

    const std::string & getStaticString() const;
  };
#endif // COPASI_CCopasiStaticString
