/**
 * CKeyFactory class.
 * This class is used to create a unique key whithin COPASI. It also allows
 * retreival of the CCopasiObject the key is assigned to.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */
#include "copasi.h"

#include <sstream>

#include "CKeyFactory.h"

std::map< std::string, CCopasiObject * > CKeyFactory::mKeyMap;

std::map< std::string, unsigned C_INT32 > CKeyFactory::mCounterMap;

std::map< std::string, bool > CKeyFactory::mOverflowMap;

std::string CKeyFactory::add(const std::string & prefix,
                             CCopasiObject * pObject)
{
  std::stringstream key;

  key << prefix + "";

  if (mCounterMap.count(prefix) == 0)
    {
      mCounterMap[prefix] = 0;
      mOverflowMap[prefix] = false;
    }

  unsigned C_INT32 * count = & mCounterMap.find(prefix)->second;
  key << (*count)++;

  if (mOverflowMap[prefix] == true)
    while (mKeyMap.count(key.str()))
      {
        key.str();
        key << prefix + "_";
        key << (*count)++;
      }

  mKeyMap[key.str()] = pObject;
  if ((*count) == 0) mOverflowMap[prefix] = true;

  return key.str();
}

bool CKeyFactory::remove(const std::string & key)
{return mKeyMap.erase(key) > 0;}

CCopasiObject * CKeyFactory::get(const std::string & key)
{
  std::map< std::string, CCopasiObject * >::const_iterator it =
    mKeyMap.find(key);

  if (it != mKeyMap.end()) return it->second;
  else return NULL;
}
