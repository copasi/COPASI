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
    /**
     * The map of currently existing keys and the related objects.
     */
    static std::map< std::string, CCopasiObject * > mKeyMap;

    // Operations
  public:
    /**
     * Add an object with a key generated from the given prefix to the key map.
     * @param const std::string & prefix
     * @param CCopasiObject * pObject
     * @return std::string key
     */
    static std::string add(const std::string & prefix, CCopasiObject * pObject);

    /**
     * Remove the key an the related object from the key map.
     * @param const std::string & key
     * @return bool success
     */
    static bool remove(const std::string & key);

    /**
     * Retreive the object referred bey key from the key map.
     * @param const std::string & key
     * @return CCopasiObject * pObject
     */
    static CCopasiObject * get(const std::string & key);
  };

#endif // COPASI_CKeyFactory
