/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CKeyFactory.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/01/09 21:21:31 $
   End CVS Header */

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

CKeyFactory GlobalKeys;

CKeyFactory::CDecisionVector::CDecisionVector():
    CVector< bool >()
{}

CKeyFactory::CDecisionVector::CDecisionVector(const std::string & str):
    CVector< bool >(256)
{
  unsigned C_INT32 i, imax;

  for (i = 0, imax = size(); i < imax; i++)
    (* (CVector< bool > *) this)[i] = false;

  for (i = 0, imax = str.length(); i < imax; i++)
    (* (CVector< bool > *) this)[(unsigned C_INT32) str[i]] = true;
}

CKeyFactory::CDecisionVector::~CDecisionVector() {}

const bool & CKeyFactory::CDecisionVector::operator () (const unsigned char & c) const
  {return (* (CVector< bool > *) this)[(unsigned C_INT32) c];}

CKeyFactory::HashTable::HashTable():
    mBeyond(0),
    mSize(128),
    mpTable(new CVector< CCopasiObject * >(128)),
    mFree()
{memset(mpTable->array(), 0, mSize * sizeof(CCopasiObject *));}

CKeyFactory::HashTable::HashTable(const CKeyFactory::HashTable & src):
    mBeyond(src.mBeyond),
    mSize(src.mSize),
    mpTable(new CVector< CCopasiObject * >(* src.mpTable)),
    mFree(src.mFree)
{}

CKeyFactory::HashTable::~HashTable() {pdelete(mpTable);}

unsigned C_INT32 CKeyFactory::HashTable::add(CCopasiObject * pObject)
{
  unsigned C_INT32 index;

  if (!mFree.empty())
    {
      index = mFree.top();
      mFree.pop();
    }
  else
    {
      index = mBeyond;

      mBeyond++;
      if (mBeyond > mSize)
        {
          CVector< CCopasiObject * > * pTmp = mpTable;
          mpTable = new CVector< CCopasiObject * >(mSize * 2);
          memcpy(mpTable->array(), pTmp->array(),
                 mSize * sizeof(CCopasiObject *));
          memset(mpTable->array() + mSize, 0,
                 mSize * sizeof(CCopasiObject *));
          mSize *= 2;
          delete pTmp;
        }
    }

  (*mpTable)[index] = pObject;
  return index;
}

bool CKeyFactory::HashTable::addFix(const unsigned C_INT32 & index,
                                    CCopasiObject * pObject)
{
  while (index >= mSize)
    {
      CVector< CCopasiObject * > * pTmp = mpTable;
      mpTable = new CVector< CCopasiObject * >(mSize * 2);
      memcpy(mpTable->array(), pTmp->array(),
             mSize * sizeof(CCopasiObject *));
      memset(mpTable->array() + mSize, 0,
             mSize * sizeof(CCopasiObject *));
      mSize *= 2;
      delete pTmp;
    }

  if ((*mpTable)[index]) return false;

  (*mpTable)[index] = pObject;
  return true;
}

CCopasiObject * CKeyFactory::HashTable::get(const unsigned C_INT32 & index)
{
  if (index < mSize) return (*mpTable)[index];

  return NULL;
}

bool CKeyFactory::HashTable::remove(const unsigned C_INT32 & index)
{
  if (index < mSize)
    {
      if (!(*mpTable)[index]) return false;

      (*mpTable)[index] = NULL;
      mFree.push(index);

      return true;
    }

  return false;
}

CKeyFactory::CDecisionVector CKeyFactory::isDigit("0123456789");

CKeyFactory::CKeyFactory():
    mKeyTable()
{}

CKeyFactory::~CKeyFactory() {}

std::string CKeyFactory::add(const std::string & prefix,
                             CCopasiObject * pObject)
{
  std::map< std::string, CKeyFactory::HashTable >::iterator it =
    mKeyTable.find(prefix);
  if (it == mKeyTable.end())
    {
      std::pair<std::map< std::string, CKeyFactory::HashTable >::iterator, bool> ret =
        mKeyTable.insert(std::map< std::string, CKeyFactory::HashTable >::value_type(prefix, CKeyFactory::HashTable()));

      it = ret.first;
    }

  std::stringstream key;
  key << prefix + "_" << it->second.add(pObject);

  return key.str();
}

bool CKeyFactory::addFix(const std::string & key, CCopasiObject * pObject)
{
  unsigned C_INT32 pos = key.length() - 1;
  while (isDigit(key[pos]) && pos) --pos;

  std::string Prefix = key.substr(0, pos);
  unsigned C_INT32 index = atoi(key.substr(pos + 1).c_str());

  std::map< std::string, CKeyFactory::HashTable >::iterator it =
    mKeyTable.find(Prefix);
  if (it == mKeyTable.end())
    {
      std::pair<std::map< std::string, CKeyFactory::HashTable >::iterator, bool> ret =
        mKeyTable.insert(std::map< std::string, CKeyFactory::HashTable >::value_type(Prefix, CKeyFactory::HashTable()));

      it = ret.first;
    }

  return it->second.addFix(index, pObject);
}

bool CKeyFactory::remove(const std::string & key)
{
  unsigned C_INT32 pos = key.length() - 1;
  while (isDigit(key[pos]) && pos) --pos;

  std::string Prefix = key.substr(0, pos);
  unsigned C_INT32 index = atoi(key.substr(pos + 1).c_str());

  std::map< std::string, CKeyFactory::HashTable >::iterator it =
    mKeyTable.find(Prefix);
  if (it == mKeyTable.end()) return false;

  return it->second.remove(index);
}

CCopasiObject * CKeyFactory::get(const std::string & key)
{
  unsigned C_INT32 pos = key.length() - 1;
  while (isDigit(key[pos]) && pos) --pos;

  std::string Prefix = key.substr(0, pos);
  unsigned C_INT32 index = atoi(key.substr(pos + 1).c_str());

  std::map< std::string, CKeyFactory::HashTable >::iterator it =
    mKeyTable.find(Prefix);
  if (it == mKeyTable.end()) return NULL;

  return it->second.get(index);
}
