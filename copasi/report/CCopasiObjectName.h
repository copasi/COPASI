/**
 * Class CCopasiObjectName
 *
 * This class is the class for handling Copasi object names.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CCopasiObjectName
#define COPASI_CCopasiObjectName

#include <string>

/** @dia:pos 21.4754,29.8662 */
class CCopasiObjectName: public string
  {
    // Operations
  public:
    CCopasiObjectName();

    CCopasiObjectName(const std::string & name);

    CCopasiObjectName(const CCopasiObjectName & src);

    ~CCopasiObjectName();

    CCopasiObjectName getPrimary() const;

    CCopasiObjectName getRemainder() const;

    std::string getObjectType() const;

    std::string getObjectName() const;

    unsigned C_INT32 getIndex(const unsigned C_INT32 & pos = 0) const;

    std::string getName(const unsigned C_INT32 & pos = 0) const;

    static std::string escape(const std::string & name);

    static std::string unescape(const std::string & name);

    // private:
    std::string::size_type findEx(const std::string & toFind,
                                  const std::string::size_type & pos = 0) const;
  };
#endif // COPASI_CCopasiObjectName
