// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi.h"

#include "CUndoData.h"

#include "copasi/core/CDataContainer.h"
#include "core/CRegisteredCommonName.h"
#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CDataVector.h"
#include "model/CMetab.h"

// static
const CEnumAnnotation< std::string, CUndoData::Type > CUndoData::TypeName(
{
  "Insert",
  "Change",
  "Remove"
});

CUndoData::CUndoData():
  mType(CUndoData::Type::CHANGE),
  mOldData(),
  mNewData(),
  mDependentData(),
  mTime(),
  mAuthorID(C_INVALID_INDEX),
  mChangedProperties()
{
  time(&mTime);
}

CUndoData::CUndoData(const Type & type, const CDataObject * pObject, const size_t & authorId):
  mType(type),
  mOldData(),
  mNewData(),
  mDependentData(),
  mTime(),
  mAuthorID(authorId),
  mChangedProperties()
{
  assert(pObject != NULL);

  time(&mTime);

  switch (mType)
    {
      case Type::INSERT:
        mNewData = pObject->toData();

        for (CData::const_iterator it = mNewData.begin(), end = mNewData.end(); it != end; ++it)
          {
            mChangedProperties.insert(it->first);
          }

        break;

      case Type::REMOVE:
        mOldData = pObject->toData();

        for (CData::const_iterator it = mOldData.begin(), end = mOldData.end(); it != end; ++it)
          {
            mChangedProperties.insert(it->first);
          }

        break;

      case Type::CHANGE:
        assert(pObject->getObjectParent() != NULL);

        mOldData.addProperty(CData::OBJECT_PARENT_CN, pObject->getObjectParent()->getCN());
        mOldData.addProperty(CData::OBJECT_TYPE, pObject->getObjectType());
        mOldData.addProperty(CData::OBJECT_NAME, pObject->getObjectName());

        mNewData.addProperty(CData::OBJECT_PARENT_CN, pObject->getObjectParent()->getCN());
        mNewData.addProperty(CData::OBJECT_TYPE, pObject->getObjectType());
        mNewData.addProperty(CData::OBJECT_NAME, pObject->getObjectName());

        break;
    }
}

CUndoData::CUndoData(const CUndoData & src):
  mType(src.mType),
  mOldData(src.mOldData),
  mNewData(src.mNewData),
  mDependentData(src.mDependentData),
  mTime(src.mTime),
  mAuthorID(src.mAuthorID),
  mChangedProperties(src.mChangedProperties)
{}

CUndoData::~CUndoData()
{}

const CUndoData::Type & CUndoData::getType() const
{
  return mType;
}

bool CUndoData::addProperty(const CData::Property & property, const CDataValue & value)
{
  return addProperty(CData::PropertyName[property], value);
}

bool CUndoData::addProperty(const std::string & name, const CDataValue & value)
{
  bool success = true;

  switch (mType)
    {
      case Type::INSERT:
        success &= mNewData.addProperty(name, value);
        mChangedProperties.insert(name);
        break;

      case Type::REMOVE:
        success &= mOldData.addProperty(name, value);
        mChangedProperties.insert(name);
        break;

      case Type::CHANGE:
        success = false;
        break;
    }

  return success;
}

bool CUndoData::addProperty(const CData::Property & property, const CDataValue & oldValue, const CDataValue & newValue)
{
  return addProperty(CData::PropertyName[property], oldValue, newValue);
}

bool CUndoData::addProperty(const std::string & name, const CDataValue & oldValue, const CDataValue & newValue)
{
  bool success = true;

  switch (mType)
    {
      case Type::INSERT:
        success = false;
        break;

      case Type::REMOVE:
        success = false;
        break;

      case Type::CHANGE:
        success &= mOldData.addProperty(name, oldValue);
        success &= mNewData.addProperty(name, newValue);

        if (oldValue != newValue)
          {
            mChangedProperties.insert(name);
          }
        else
          {
            mChangedProperties.erase(name);
            success = false;
          }

        break;
    }

  return success;
}

bool CUndoData::isSetProperty(const CData::Property & property) const
{
  return isSetProperty(CData::PropertyName[property]);
}

bool CUndoData::isSetProperty(const std::string & name) const
{
  bool isSet = true;

  switch (mType)
    {
      case Type::INSERT:
        isSet &= mNewData.isSetProperty(name);
        break;

      case Type::REMOVE:
        isSet &= mOldData.isSetProperty(name);
        break;

      case Type::CHANGE:
        isSet &= mNewData.isSetProperty(name);
        isSet &= mOldData.isSetProperty(name);
        break;
    }

  return isSet;
}

bool CUndoData::appendData(const CData & data)
{
  bool success = true;

  switch (mType)
    {
      case Type::INSERT:
        success &= mNewData.appendData(data);
        break;

      case Type::REMOVE:
        success &= mOldData.appendData(data);
        break;

      case Type::CHANGE:
        success = false;
        break;
    }

  return success;
}

bool CUndoData::appendData(const CData & oldData, const CData & newData)
{
  bool success = true;

  switch (mType)
    {
      case Type::INSERT:
        success = false;
        break;

      case Type::REMOVE:
        success = false;
        break;

      case Type::CHANGE:
        success &= mOldData.appendData(oldData);
        success &= mNewData.appendData(newData);
        break;
    }

  return success;
}

bool CUndoData::addDependentData(const CUndoData & dependentData)
{
  mDependentData.push_back(dependentData);

  return true;
}

bool CUndoData::addDependentData(std::vector< CUndoData > & dependentData, bool sort)
{
  if (sort)
    {
      std::sort(dependentData.begin(), dependentData.end());
    }

  mDependentData.insert(mDependentData.end(), dependentData.begin(), dependentData.end());

  return true;
}

const CData & CUndoData::getOldData() const
{
  return mOldData;
}

const CData & CUndoData::getNewData() const
{
  return mNewData;
}

const std::vector< CUndoData > & CUndoData::getDependentData() const
{
  return mDependentData;
}

std::vector< CUndoData > & CUndoData::getDependentData()
{
  return mDependentData;
}

const std::set< std::string > & CUndoData::getChangedProperties() const
{
  return mChangedProperties;
}

bool CUndoData::apply(const CDataModel & dataModel) const
{
  bool success = true;

  switch (mType)
    {
      case Type::INSERT:
        success &= insert(dataModel, true);
        break;

      case Type::REMOVE:
        success &= remove(dataModel, true);
        break;

      case Type::CHANGE:
        success &= change(dataModel, true);
        break;
    }

  return success;
}

bool CUndoData::undo(const CDataModel & dataModel) const
{
  bool success = true;

  switch (mType)
    {
      case Type::INSERT:
        success &= remove(dataModel, false);
        break;

      case Type::REMOVE:
        success &= insert(dataModel, false);
        break;

      case Type::CHANGE:
        success &= change(dataModel, false);
        break;
    }

  return success;
}

const std::time_t & CUndoData::getTime() const
{
  return mTime;
}

std::tm * CUndoData::getLocalTime() const
{
  return localtime(&mTime);
}

std::tm * CUndoData::getUTCTime() const
{
  return gmtime(&mTime);
}

const size_t CUndoData::getAuthorID() const
{
  return mAuthorID;
}

std::string CUndoData::getObjectDisplayName() const
{
  std::string DisplayName("Unknown");

  switch (mType)
    {
      case Type::INSERT:
        DisplayName = mNewData.getProperty(CData::OBJECT_NAME).toString();
        break;

      case Type::REMOVE:
      case Type::CHANGE:
        DisplayName = mOldData.getProperty(CData::OBJECT_NAME).toString();
        break;
    }

  // Species will always have the name of the parent compartment appended.
  if (getObjectType() == "Metabolite")
    {
      CCommonName CN;

      switch (mType)
        {
          case Type::INSERT:
            CN = mNewData.getProperty(CData::OBJECT_PARENT_CN).toString();
            break;

          case Type::REMOVE:
          case Type::CHANGE:
            CN = mOldData.getProperty(CData::OBJECT_TYPE).toString();
            break;
        }

      while (!CN.empty() && CN.getObjectType() != "Compartment")
        {
          CN = CN.getRemainder();
        }

      if (!CN.empty())
        {
          DisplayName += "{" + CN.getObjectName() + "}";
        }
    }

  return DisplayName;
}

std::string CUndoData::getObjectType() const
{
  switch (mType)
    {
      case Type::INSERT:
        return mNewData.getProperty(CData::OBJECT_TYPE).toString();
        break;

      case Type::REMOVE:
      case Type::CHANGE:
        return mOldData.getProperty(CData::OBJECT_TYPE).toString();
        break;
    }

  return "Unknown";
}

bool CUndoData::operator < (const CUndoData & rhs) const
{
  if (mType != rhs.mType) return mType < rhs.mType;

  switch (mType)
    {
      case Type::INSERT:
      {
        const std::string & CN = mNewData.getProperty(CData::Property::OBJECT_PARENT_CN).toString();
        const std::string & RhsCN = rhs.mNewData.getProperty(CData::Property::OBJECT_PARENT_CN).toString();

        if (CN != RhsCN) return CN < RhsCN;
      }
      break;

      case Type::REMOVE:
      {
        const std::string & CN = mOldData.getProperty(CData::Property::OBJECT_PARENT_CN).toString();
        const std::string & RhsCN = rhs.mOldData.getProperty(CData::Property::OBJECT_PARENT_CN).toString();

        if (CN != RhsCN) return CN > RhsCN;
      }
      break;

      case Type::CHANGE:
      {
        const std::string & CN = mNewData.getProperty(CData::Property::OBJECT_PARENT_CN).toString();
        const std::string & RhsCN = rhs.mNewData.getProperty(CData::Property::OBJECT_PARENT_CN).toString();

        if (CN != RhsCN) return CN < RhsCN;
      }

      {
        const std::string & CN = mOldData.getProperty(CData::Property::OBJECT_PARENT_CN).toString();
        const std::string & RhsCN = rhs.mOldData.getProperty(CData::Property::OBJECT_PARENT_CN).toString();

        if (CN != RhsCN) return CN > RhsCN;
      }
      break;
    }

  // At the point the data is of the same point and type now we sort by the index
  switch (mType)
    {
      case Type::INSERT:
      {
        const unsigned C_INT32 & Index = mNewData.getProperty(CData::Property::OBJECT_INDEX).toUint();
        const unsigned C_INT32 & RhsIndex = rhs.mNewData.getProperty(CData::Property::OBJECT_INDEX).toUint();

        if (Index != RhsIndex) return Index < RhsIndex;
      }
      break;

      case Type::REMOVE:
      {
        const unsigned C_INT32 & Index = mOldData.getProperty(CData::Property::OBJECT_INDEX).toUint();
        const unsigned C_INT32 & RhsIndex = rhs.mOldData.getProperty(CData::Property::OBJECT_INDEX).toUint();

        if (Index != RhsIndex) return Index > RhsIndex;
      }
      break;

      case Type::CHANGE:
      {
        const unsigned C_INT32 & Index = mNewData.getProperty(CData::Property::OBJECT_INDEX).toUint();
        const unsigned C_INT32 & RhsIndex = rhs.mNewData.getProperty(CData::Property::OBJECT_INDEX).toUint();

        if (Index != RhsIndex) return Index < RhsIndex;
      }

      {
        const unsigned C_INT32 & Index = mOldData.getProperty(CData::Property::OBJECT_INDEX).toUint();
        const unsigned C_INT32 & RhsIndex = rhs.mOldData.getProperty(CData::Property::OBJECT_INDEX).toUint();

        if (Index != RhsIndex) return Index > RhsIndex;
      }
      break;
    }

  // Default by pointer
  return this < &rhs;
}

// static
bool CUndoData::insert(const CDataModel & dataModel, const bool & apply) const
{
  const CData & Data = getData(apply);

  CDataContainer * pParent = getParent(dataModel, Data);

  if (pParent == NULL)
    return false;

  CDataObject * pObject = pParent->insert(Data);

  if (pObject == NULL)
    return false;

  bool success = pObject->applyData(Data);
  success &= processDependentData(dataModel, apply);

  return success;
}

// static
bool CUndoData::remove(const CDataModel & dataModel, const bool & apply) const
{
  const CData & Data = getData(apply);

  CDataObject * pObject = getObject(dataModel, Data);

  if (pObject == NULL)
    return false;

  delete pObject;

  return processDependentData(dataModel, apply);
}

// static
bool CUndoData::change(const CDataModel & dataModel, const bool & apply) const
{
  const CData & OldData = getData(!apply);
  const CData & NewData = getData(apply);

  CDataObject * pObject = getObject(dataModel, OldData);

  // We must always have the old object;
  if (pObject == NULL)
    return false;

  bool success = true;

  // A special case is that the ParentCN has changed, i.e., the object has moved

  if (OldData.getProperty(CData::OBJECT_PARENT_CN).toString() != NewData.getProperty(CData::OBJECT_PARENT_CN).toString())
    {
      // We need to move
      CDataContainer * pContainer = pObject->getObjectParent();

      if (pContainer != NULL)
        pContainer->remove(pObject);

      pContainer = getParent(dataModel, NewData);

      if (pContainer != NULL)
        pContainer->add(pObject, true);
    }

  success &= pObject->applyData(NewData);
  success &= processDependentData(dataModel, apply);

  return success;
}

bool CUndoData::processDependentData(const CDataModel & dataModel, const bool & apply) const
{
  bool success = true;

  // The order of processing of dependent data
  if (apply)
    {
      std::vector< CUndoData >::const_iterator it = mDependentData.begin();
      std::vector< CUndoData >::const_iterator end = mDependentData.end();

      for (; it != end; ++it)
        {
          // If we are here we have dependent data, e.g. particle number changes
          success &= it->apply(dataModel);
        }
    }
  else
    {
      std::vector< CUndoData >::const_reverse_iterator it = mDependentData.rbegin();
      std::vector< CUndoData >::const_reverse_iterator end = mDependentData.rend();

      for (; it != end; ++it)
        {
          // If we are here we have dependent data, e.g. particle number changes
          success &= it->undo(dataModel);
        }
    }

  return success;
}

const CData & CUndoData::getData(const bool & apply) const
{
  switch (mType)
    {
      case Type::CHANGE:
        if (apply)
          return mNewData;
        else
          return mOldData;

        break;

      case Type::INSERT:
        return mNewData;

      case Type::REMOVE:
        return mOldData;
    }

  // This will never be reached. It is there to satisfy the compiler.
  return mNewData;
}

// static
CDataContainer * CUndoData::getParent(const CDataModel & dataModel, const CData & data)
{
  const CDataContainer * pParent = NULL;

  if (!data.empty())
    pParent = dynamic_cast< const CDataContainer * >(dataModel.getObject(data.getProperty(CData::OBJECT_PARENT_CN).toString()));

  return const_cast< CDataContainer * >(pParent);
}

// static
CDataObject * CUndoData::getObject(const CDataModel & dataModel, const CData & data)
{
  const CDataObject * pObject = NULL;
  CDataContainer * pParent = getParent(dataModel, data);

  if (pParent != NULL)
    pObject =
      dynamic_cast< const CDataObject * >(pParent->getObject(data.getProperty(CData::OBJECT_TYPE).toString() + "=" + data.getProperty(CData::OBJECT_NAME).toString()));

  return const_cast< CDataObject * >(pObject);
}
