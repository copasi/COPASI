// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi.h"

#include "CUndoData.h"

#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiVector.h"
#include "model/CMetab.h"

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

bool CUndoData::appendData(const CData & data)
{
  bool success = true;

  switch (mType)
    {
      case INSERT:
        success &= mNewData.appendData(data);
        break;

      case REMOVE:
        success &= mOldData.appendData(data);
        break;

      case CHANGE:
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
      case INSERT:
        success = false;
        break;

      case REMOVE:
        success = false;
        break;

      case CHANGE:
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

void CUndoData::recordDependentParticleNumberChange(const double factor, const CCopasiVector< CMetab > & species)
{
  // We need to record the old and new values for each species where new := factor * old
  CCopasiVector< CMetab >::const_iterator it = species.begin();
  CCopasiVector< CMetab >::const_iterator end = species.end();

  for (; it != end; ++it)
    {
      CUndoData Data(CHANGE, &*it, mAuthorID);
      Data.addProperty(CData::INITIAL_VALUE, it->getInitialValue(), factor * it->getInitialValue());
      mDependentData.push_back(Data);
    }
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

bool CUndoData::apply(const CCopasiDataModel & dataModel) const
{
  bool success = true;

  switch (mType)
    {
      case INSERT:
        success &= insert(dataModel, true);
        break;

      case REMOVE:
        success &= remove(dataModel, true);
        break;

      case CHANGE:
        success &= change(dataModel, true);
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
        success &= remove(dataModel, false);
        break;

      case REMOVE:
        success &= insert(dataModel, false);
        break;

      case CHANGE:
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

// static
bool CUndoData::insert(const CCopasiDataModel & dataModel, const bool & apply) const
{
  const CData & Data = getData(apply);

  CCopasiContainer * pParent = getParent(dataModel, Data);

  if (pParent == NULL)
    return false;

  CCopasiObject * pObject = pParent->insert(Data);

  if (pObject == NULL)
    return false;

  bool success = pObject->applyData(Data);
  success &= processDependentData(dataModel, apply);

  return success;
}

// static
bool CUndoData::remove(const CCopasiDataModel & dataModel, const bool & apply) const
{
  const CData & Data = getData(apply);

  CCopasiObject * pObject = getObject(dataModel, Data);

  if (pObject == NULL)
    return false;

  delete pObject;

  return processDependentData(dataModel, apply);
}

// static
bool CUndoData::change(const CCopasiDataModel & dataModel, const bool & apply) const
{
  const CData & OldData = getData(!apply);
  const CData & NewData = getData(apply);

  CCopasiObject * pObject = getObject(dataModel, OldData);

  // We must always have the old object;
  if (pObject == NULL)
    return false;

  bool success = true;

  // A special case is that the ParentCN has changed, i.e., the object has moved

  if (OldData.getProperty(CData::OBJECT_PARENT_CN).toString() != NewData.getProperty(CData::OBJECT_PARENT_CN).toString())
    {
      // We need to move
      CCopasiContainer * pContainer = pObject->getObjectParent();

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

bool CUndoData::processDependentData(const CCopasiDataModel & dataModel, const bool & apply) const
{
  bool success = true;

  std::vector< CUndoData >::const_iterator it = mDependentData.begin();
  std::vector< CUndoData >::const_iterator end = mDependentData.end();

  if (apply)
    {
      for (; it != end; ++it)
        {
          // If we are here we have dependent data, e.g. particle number changes
          success &= it->apply(dataModel);
        }
    }
  else
    {
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
  if (apply)
    return mNewData;

  return mOldData;
}

// static
CCopasiContainer * CUndoData::getParent(const CCopasiDataModel & dataModel, const CData & data)
{
  const CCopasiContainer * pParent = NULL;

  if (!data.empty())
    pParent = dynamic_cast< const CCopasiContainer * >(dataModel.getObject(data.getProperty(CData::OBJECT_PARENT_CN).toString()));

  return const_cast< CCopasiContainer * >(pParent);
}

// static
CCopasiObject * CUndoData::getObject(const CCopasiDataModel & dataModel, const CData & data)
{
  const CCopasiObject * pObject = NULL;
  CCopasiContainer * pParent = getParent(dataModel, data);

  if (pParent != NULL)
    pObject =
      dynamic_cast< const CCopasiObject * >(pParent->getObject(data.getProperty(CData::OBJECT_TYPE).toString() + "=" + data.getProperty(CData::OBJECT_NAME).toString()));

  return const_cast< CCopasiObject * >(pObject);
}
