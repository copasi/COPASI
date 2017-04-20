// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CKeyFactory class.
 * This class is used to create a unique key whithin COPASI. It also allows
 * retreival of the CDataObject the key is assigned to.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */
#include <sstream>
#include <stdlib.h>

#include "copasi/copasi.h"

#include "copasi/report/CKeyFactory.h"

bool CKeyFactory::isValidKey(const std::string & key,
                             const std::string & prefix)
{
  if (key == "" && prefix == "") return true;

  size_t digitsStart = key.length() - 1;

  while (isDigit(key[digitsStart]) && digitsStart) --digitsStart;

  if (digitsStart < 1 || digitsStart > key.length() - 2 || key[digitsStart] != '_') return false;

  if (prefix != "")
    {
      if (prefix != key.substr(0, digitsStart)) return false;
      else return true;
    }

  size_t prefixEnd = 0;

  while (isPrefix(key[prefixEnd]) && prefixEnd < digitsStart) ++prefixEnd;

  return (prefixEnd == digitsStart);
}

CKeyFactory::CDecisionVector::CDecisionVector():
  CVector< bool >()
{}

CKeyFactory::CDecisionVector::CDecisionVector(const std::string & str):
  CVector< bool >(256)
{
  size_t i, imax;

  for (i = 0, imax = size(); i < imax; i++)
    (*(CVector< bool > *) this)[i] = false;

  for (i = 0, imax = str.length(); i < imax; i++)
    (*(CVector< bool > *) this)[(size_t) str[i]] = true;
}

CKeyFactory::CDecisionVector::~CDecisionVector() {}

const bool & CKeyFactory::CDecisionVector::operator()(const unsigned char & c) const
{return (*(CVector< bool > *) this)[(size_t) c];}

CKeyFactory::HashTable::HashTable():
  mBeyond(0),
  mSize(128),
  mTable(128),
  mFree()
{memset(mTable.array(), 0, mSize * sizeof(CDataObject *));}

CKeyFactory::HashTable::HashTable(const CKeyFactory::HashTable & src):
  mBeyond(src.mBeyond),
  mSize(src.mSize),
  mTable(src.mTable),
  mFree(src.mFree)
{}

CKeyFactory::HashTable::~HashTable() {}

size_t CKeyFactory::HashTable::add(CDataObject * pObject)
{
  size_t index;

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
          mTable.resize(mSize * 2, true);
          memset(mTable.array() + mSize, 0, mSize * sizeof(CDataObject *));
          mSize *= 2;
        }
    }

  mTable[index] = pObject;
  return index;
}

bool CKeyFactory::HashTable::addFix(const size_t & index,
                                    CDataObject * pObject)
{
  while (index >= mSize)
    {
      mTable.resize(mSize * 2, true);
      memset(mTable.array() + mSize, 0,
             mSize * sizeof(CDataObject *));
      mSize *= 2;
    }

  if (mTable[index]) return false;

  mTable[index] = pObject;
  return true;
}

CDataObject * CKeyFactory::HashTable::get(const size_t & index)
{
  if (index < mSize) return mTable[index];

  return NULL;
}

bool CKeyFactory::HashTable::remove(const size_t & index)
{
  if (index < mSize)
    {
      if (!mTable[index]) return false;

      mTable[index] = NULL;
      mFree.push(index);

      return true;
    }

  return false;
}

CKeyFactory::CDecisionVector CKeyFactory::isDigit("0123456789");

CKeyFactory::CDecisionVector CKeyFactory::isPrefix("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

CKeyFactory::CKeyFactory():
  mKeyTable()
{}

CKeyFactory::~CKeyFactory() {}

std::string CKeyFactory::add(const std::string & prefix,
                             CDataObject * pObject)
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

bool CKeyFactory::addFix(const std::string & key, CDataObject * pObject)
{
  size_t pos = key.length() - 1;

  while (isDigit(key[pos]) && pos) --pos;

  std::string Prefix = key.substr(0, pos);
  size_t index = atoi(key.substr(pos + 1).c_str());

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
  size_t pos = key.length();

  if (pos == 0) return false;

  --pos;

  while (isDigit(key[pos]) && pos) --pos;

  std::string Prefix = key.substr(0, pos);

  size_t index = 0;

  if (pos + 1 < key.length())
    index = atoi(key.substr(pos + 1).c_str());

  std::map< std::string, CKeyFactory::HashTable >::iterator it =
    mKeyTable.find(Prefix);

  if (it == mKeyTable.end()) return false;

  return it->second.remove(index);
}

CDataObject * CKeyFactory::get(const std::string & key)
{
  if (key.length() == 0) return NULL;

  size_t pos = key.length() - 1; //TODO !!!pos can be invalid (-1); not anymore, but look for other errors like this

  while (isDigit(key[pos]) && pos) --pos;

  std::string Prefix = key.substr(0, pos);
  size_t index = atoi(key.substr(pos + 1).c_str());

  std::map< std::string, CKeyFactory::HashTable >::iterator it =
    mKeyTable.find(Prefix);

  if (it == mKeyTable.end()) return NULL;

  return it->second.get(index);
}
