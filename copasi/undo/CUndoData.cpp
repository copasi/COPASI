// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi.h"

#include "CUndoData.h"

#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "CopasiDataModel/CCopasiDataModel.h"

CUndoData::CUndoData():
  mType(CUndoData::CHANGE),
  mOldData(),
  mNewData(),
  mDependentData(),
  mTime(),
  mAuthorID(C_INVALID_INDEX)
{
  time(&mTime);
}

CUndoData::CUndoData(const Type & type, const CCopasiObject * pObject, const size_t & authorId):
  mType(type),
  mOldData(),
  mNewData(),
  mDependentData(),
  mTime(),
  mAuthorID(authorId)
{
  assert(pObject != NULL);

  time(&mTime);

  switch (mType)
    {
      case INSERT:
        // Sanity Check
        assert(pObject->isContainer());

        mNewData.addProperty(CData::OBJECT_PARENT_CN, pObject->getCN());
        break;

      case REMOVE:
        mOldData = pObject->toData();
        break;

      case CHANGE:
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
  mAuthorID(src.mAuthorID)
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
      case INSERT:
        success &= mNewData.addProperty(name, value);
        break;

      case REMOVE:
        success &= mOldData.addProperty(name, value);
        break;

      case CHANGE:
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
      case INSERT:
        success = false;
        break;

      case REMOVE:
        success = false;
        break;

      case CHANGE:
        success &= mOldData.addProperty(name, oldValue);
        success &= mNewData.addProperty(name, newValue);
        break;
    }

  return success;
}

bool CUndoData::addDependentData(const CUndoData & dependentData)
{
  mDependentData.push_back(dependentData);

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

const std::vector< CUndoData > CUndoData::getDependentData() const
{
  return mDependentData;
}

bool CUndoData::apply(const CCopasiDataModel & dataModel) const
{
  bool success = true;

  switch (mType)
    {
      case INSERT:
        success &= insert(dataModel, mNewData, std::vector< CUndoData >());
        break;

      case REMOVE:
        success &= remove(dataModel, mOldData, mDependentData);
        break;

      case CHANGE:
        success &= change(dataModel, mOldData, mNewData);
        break;
    }

  return success;
}

bool CUndoData::undo(const CCopasiDataModel & dataModel) const
{
  bool success = true;

  switch (mType)
    {
      case INSERT:
        success &= remove(dataModel, mNewData, std::vector< CUndoData >());
        break;

      case REMOVE:
        success &= insert(dataModel, mOldData, mDependentData);
        break;

      case CHANGE:
        success &= change(dataModel, mNewData, mOldData);
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

// static
bool CUndoData::insert(const CCopasiDataModel & dataModel, const CData & data, const std::vector< CUndoData > & dependentData)
{
  CCopasiContainer * pParent = getParent(dataModel, data);

  if (pParent == NULL)
    return false;

  CCopasiObject * pObject = pParent->insert(data);

  if (pObject == NULL)
    return false;

  bool success = pObject->applyData(data);

  std::vector< CUndoData >::const_iterator it = dependentData.begin();
  std::vector< CUndoData >::const_iterator end = dependentData.end();

  for (; it != end; ++it)
    {
      // If we are here we have independent data, i.e, this is triggered as an undo of a remove
      success &= it->undo(dataModel);
    }

  return success;
}

// static
bool CUndoData::remove(const CCopasiDataModel & dataModel, const CData & data, const std::vector< CUndoData > & dependentData)
{
  CCopasiObject * pObject = getObject(dataModel, data);

  if (pObject == NULL)
    return false;

  delete pObject;

  bool success = true;

  std::vector< CUndoData >::const_iterator it = dependentData.begin();
  std::vector< CUndoData >::const_iterator end = dependentData.end();

  for (; it != end; ++it)
    {
      // If we are here we have independent data, i.e, this is triggered as a redo of a remove
      success &= it->apply(dataModel);
    }

  return success;
}

// static
bool CUndoData::change(const CCopasiDataModel & dataModel, const CData & oldData, const CData & newData)
{
  CCopasiObject * pObject = getObject(dataModel, oldData);

  // We must always have the old object;
  if (pObject == NULL)
    return false;

  bool success = true;

  // A special case is that the ParentCN has changed, i.e., the object has moved

  if (oldData.getProperty("ParentCN").toString() != newData.getProperty("ParentCN").toString())
    {
      // We need to move
      CCopasiContainer * pContainer = pObject->getObjectParent();

      if (pContainer != NULL)
        pContainer->remove(pObject);

      pContainer = getParent(dataModel, newData);

      if (pContainer != NULL)
        pContainer->add(pObject, true);
    }

  success &= pObject->setObjectName(newData.getProperty("ObjectName").toString());

  success &= pObject->applyData(newData);

  return success;
}

// static
CCopasiContainer * CUndoData::getParent(const CCopasiDataModel & dataModel, const CData & data)
{
  const CCopasiContainer * pParent = NULL;

  if (!data.empty())
    pParent = dynamic_cast< const CCopasiContainer * >(dataModel.getObject(data.getProperty("ParentCN").toString()));

  return const_cast< CCopasiContainer * >(pParent);
}

// static
CCopasiObject * CUndoData::getObject(const CCopasiDataModel & dataModel, const CData & data)
{
  const CCopasiObject * pObject = NULL;
  CCopasiContainer * pParent = getParent(dataModel, data);

  if (pParent != NULL)
    pObject =
      dynamic_cast< const CCopasiObject * >(pParent->getObject(data.getProperty("ObjectType").toString() + "=" + data.getProperty("ObjectName").toString()));

  return const_cast< CCopasiObject * >(pObject);
}
