/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CKeyFactory.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:31:49 $
   End CVS Header */

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

    /**
     * A map of counters for the prefixes.
     */
    static std::map< std::string, unsigned C_INT32 > mCounterMap;

    /**
     * A map of counter overflows for the prefixes.
     */
    static std::map< std::string, bool > mOverflowMap;

    // Operations
  public:
    /**
     * Add an object with a key generated from the given prefix to the key map.
     * The return value is the actually generated key.
     * @param const std::string & prefix
     * @param CCopasiObject * pObject
     * @return std::string key
     */
    static std::string add(const std::string & prefix, CCopasiObject * pObject);

    /**
     * Remove the key and the related object from the key map.
     * @param const std::string & key
     * @return bool success
     */
    static bool remove(const std::string & key);

    /**
     * Retreive the object referred by key from the key map.
     * @param const std::string & key
     * @return CCopasiObject * pObject
     */
    static CCopasiObject * get(const std::string & key);
  };

#endif // COPASI_CKeyFactory
