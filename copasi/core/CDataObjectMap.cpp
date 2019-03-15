// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "CDataObjectMap.h"
#include "CDataObject.h"

CDataObjectMap::iterator::iterator():
  mpMap(NULL),
  mNameEnd(true),
  mName(),
  mObjectEnd(true),
  mObject()
{}

CDataObjectMap::iterator::iterator(const CDataObjectMap & map,
                                   const bool & begin):
  mpMap(&map),
  mNameEnd(true),
  mName(),
  mObjectEnd(true),
  mObject()
{
  if (mpMap != NULL &&
      mpMap->begin() != mpMap->end())
    {
      if (begin)
        {
          mNameEnd = false;
          mName = const_cast< std::map< std::string, std::set< CDataObject * > > * >(mpMap)->begin();

          if (!mName->second.empty())
            {
              mObjectEnd = false;
              mObject = mName->second.begin();
            }
        }
    }
}

CDataObjectMap::iterator::iterator(const CDataObjectMap::iterator & src):
  mpMap(src.mpMap),
  mNameEnd(src.mNameEnd),
  mName(src.mName),
  mObjectEnd(src.mObjectEnd),
  mObject(src.mObject)
{}

CDataObjectMap::iterator::~iterator()
{}

CDataObject * CDataObjectMap::iterator::operator*() const
{
  if (!mObjectEnd)
    return *mObject;

  return NULL;
}

CDataObject * CDataObjectMap::iterator::operator->() const
{
  if (!mObjectEnd)
    return *mObject;

  return NULL;
}

CDataObjectMap::iterator & CDataObjectMap::iterator::operator++()
{
  if (!mNameEnd || !mObjectEnd)
    {
      mObject++;

      if (mObject == mName->second.end() || mObjectEnd)
        {
          if (mName != mpMap->end() && !mNameEnd)
            {
              mName++;
            }

          if (mName != mpMap->end() && !mNameEnd)
            {
              mObjectEnd = false;
              mObject = mName->second.begin();
            }
          else
            {
              mNameEnd = true;
              mObjectEnd = true;
            }
        }
    }

  return *this;
}

CDataObjectMap::iterator CDataObjectMap::iterator::operator++(int)
{
  iterator Current(*this);
  operator++();

  return Current;
}

bool CDataObjectMap::iterator::operator != (const iterator & rhs) const
{
  return (mpMap != rhs.mpMap ||
          mNameEnd != rhs.mNameEnd ||
          mObjectEnd != rhs.mObjectEnd ||
          (!mNameEnd && mName != rhs.mName) ||
          (!mObjectEnd && mObject != rhs.mObject));
}

CDataObjectMap::const_iterator::const_iterator():
  mpMap(NULL),
  mNameEnd(true),
  mItName(),
  mObjectEnd(true),
  mItpObject()
{}

CDataObjectMap::const_iterator::const_iterator(const CDataObjectMap & map,
    const bool & begin):
  mpMap(&map),
  mNameEnd(true),
  mItName(),
  mObjectEnd(true),
  mItpObject()
{
  if (mpMap != NULL &&
      mpMap->begin() != mpMap->end())
    {
      if (begin)
        {
          mNameEnd = false;
          mItName = const_cast< std::map< std::string, std::set< CDataObject * > > * >(mpMap)->begin();

          if (!mItName->second.empty())
            {
              mObjectEnd = false;
              mItpObject = mItName->second.begin();
            }
        }
    }
}

CDataObjectMap::const_iterator::const_iterator(const CDataObjectMap::const_iterator & src):
  mpMap(src.mpMap),
  mNameEnd(src.mNameEnd),
  mItName(src.mItName),
  mObjectEnd(src.mObjectEnd),
  mItpObject(src.mItpObject)
{}

CDataObjectMap::const_iterator::const_iterator(const CDataObjectMap::iterator & src):
  mpMap(src.mpMap),
  mNameEnd(src.mNameEnd),
  mItName(src.mName),
  mObjectEnd(src.mObjectEnd),
  mItpObject(src.mObject)
{}

CDataObjectMap::const_iterator::~const_iterator()
{}

CDataObject * CDataObjectMap::const_iterator::operator*() const
{
  return mObjectEnd ? NULL : *mItpObject;
}

CDataObject * CDataObjectMap::const_iterator::operator->() const
{
  return mObjectEnd ? NULL : *mItpObject;
}

CDataObjectMap::const_iterator & CDataObjectMap::const_iterator::operator++()
{
  if (mNameEnd)
    return *this;

  if (!mObjectEnd)
    {
      mItpObject++;
      mObjectEnd = (mItpObject == mItName->second.end());

      if (!mObjectEnd)
        return *this;
    }

  // It is save to advance the name iterator since we are not at the end;
  mItName++;
  mNameEnd = (mItName == mpMap->end());

  if (mNameEnd)
    {
      return *this;
    }

  // We do not have empty sets therefore we are sure that we are not at the end
  mObjectEnd = false;
  mItpObject = mItName->second.begin();

  return *this;
}

CDataObjectMap::const_iterator CDataObjectMap::const_iterator::operator++(int)
{
  const_iterator Current(*this);
  operator++();

  return Current;
}

bool CDataObjectMap::const_iterator::operator != (const const_iterator & rhs) const
{
  return (mpMap != rhs.mpMap ||
          mNameEnd != rhs.mNameEnd ||
          mObjectEnd != rhs.mObjectEnd ||
          (!mNameEnd && mItName != rhs.mItName) ||
          (!mObjectEnd && mItpObject != rhs.mItpObject));
}

CDataObjectMap::CDataObjectMap():
  CDataObjectMap::data()
{}

CDataObjectMap::CDataObjectMap(const CDataObjectMap & src):
  CDataObjectMap::data(src)
{}

CDataObjectMap::~CDataObjectMap()
{}

std::pair< std::set< CDataObject * >::iterator, bool > CDataObjectMap::insert(CDataObject * pObject)
{
  if (pObject == NULL)
    {
      return std::make_pair(std::set< CDataObject * >::iterator(), false);
    }

  std::map< std::string, std::set< CDataObject * > >::iterator itMap = data::find(pObject->getObjectName());

  if (itMap == data::end())
    {
      itMap = data::insert(std::make_pair(pObject->getObjectName(), std::set< CDataObject * >())).first;
    }

  return itMap->second.insert(pObject);
}

bool CDataObjectMap::erase(CDataObject * pObject)
{
  if (pObject == NULL) return false;

  std::map< std::string, std::set< CDataObject * > >::iterator itMap = data::find(pObject->getObjectName());

  if (itMap != data::end())
    {
      bool success = (itMap->second.erase(pObject) > 0);

      if (itMap->second.empty())
        {
          data::erase(itMap);
        }

      return success;
    }

  return false;
}

void CDataObjectMap::clear()
{
  data::clear();
}

bool CDataObjectMap::contains(CDataObject * pObject) const
{
  if (pObject == NULL) return false;

  std::map< std::string, std::set< CDataObject * > >::const_iterator itMap = data::find(pObject->getObjectName());

  if (itMap != data::end())
    {
      return (itMap->second.find(pObject) != itMap->second.end());
    }

  return false;
}

void CDataObjectMap::objectRenamed(CDataObject * pObject, const std::string & oldName)
{
  if (pObject != NULL)
    {
      // We cannot use erase since the object has already been renamed.
      std::map< std::string, std::set< CDataObject * > >::iterator itMap = data::find(oldName);

      if (itMap != data::end())
        {
          bool success = (itMap->second.erase(pObject) > 0);

          if (itMap->second.empty())
            {
              data::erase(itMap);
            }
        }

      insert(pObject);
    }
}

std::pair< std::set< CDataObject * >::const_iterator, std::set< CDataObject * >::const_iterator > CDataObjectMap::equal_range(const std::string & name) const
{
  std::map< std::string, std::set< CDataObject * > >::const_iterator itMap = data::find(name);

  if (itMap != data::end())
    {
      return std::make_pair(itMap->second.begin(), itMap->second.end());
    }

  static std::set< CDataObject * > Set;
  return std::make_pair(Set.begin(), Set.end());
}

CDataObjectMap::iterator CDataObjectMap::begin()
{
  return iterator(*this, true);
}

CDataObjectMap::iterator CDataObjectMap::end()
{
  return iterator(*this, false);
}

CDataObjectMap::const_iterator CDataObjectMap::begin() const
{
  return const_iterator(*this, true);
}

CDataObjectMap::const_iterator CDataObjectMap::end() const
{
  return const_iterator(*this, false);
}
