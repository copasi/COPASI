/**
 * CKeyFactory class.
 * This class is used to create a unique key whithin COPASI. It also allows
 * retreival of the CCopasiObject the key is assigned to.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */
#include <sstream>

#include "copasi.h"
#include "CKeyFactory.h"

std::map< std::string, CCopasiObject * > CKeyFactory::mKeyMap;

std::string CKeyFactory::add(const std::string & prefix,
                             CCopasiObject * pObject)
{
  std::stringstream key;
  key << prefix << "_";
  std::streampos pos = key.str().length();

  unsigned C_INT32 count = 1;
  key << count++;
  while (mKeyMap.count(key.str()))
    {
      key.seekp(pos, std::ios::beg);
      key << count++;
    }

  mKeyMap[key.str()] = pObject;

  return key.str();
}

bool CKeyFactory::remove(const std::string & key)
{return mKeyMap.erase(key) > 0;}

CCopasiObject * CKeyFactory::get(const std::string & key)
{return mKeyMap[key];}
