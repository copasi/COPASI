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

class CCopasiStaticString: public std::string
  {
    // Operations
  public:
    CCopasiStaticString();

    CCopasiStaticString(const std::string & name);

    ~CCopasiStaticString();

    void cleanup();
  };
#endif // COPASI_CCopasiStaticString
