/**
 * CKeyFactory class.
 * This class is used to create a unique key whithin COPASI. It also allows
 * retreival of the CCopasiObject the key is assigned to.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CKeyFactory
#define COPASI_CKeyFactory

#include <string>
#include <map>

class CCopasiObject;

class CKeyFactory
  {
    // Attributes
  protected:
    static std::map< std::string, CCopasiObject * > mKeyMap;

    // Operations
  public:
    static std::string add(const std::string & prefix, CCopasiObject *);

    static bool remove(const std::string & key);

    static CCopasiObject * get(const std::string & key);
  };

#endif // COPASI_CKeyFactory
