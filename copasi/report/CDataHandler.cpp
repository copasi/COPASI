// Copyright (C) 2020 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "CDataHandler.h"
#include "copasi/core/CDataTimer.h"

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRootContainer.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/utilities/utility.h"
#include "copasi/commandline/CLocaleString.h"
#include <copasi/math/CMathObject.h>

//////////////////////////////////////////////////
//
//class CDataHandler
//
//////////////////////////////////////////////////
CDataHandler::CDataHandler(bool separate)
  : COutputHandler()
  , mCNsBefore()
  , mCNsDuring()
  , mCNsAfter()
  , mAfterObjectList()
  , mDuringObjectList()
  , mBeforeObjectList()
  , mBeforeData()
  , mDuringData()
  , mAfterData()
  , mSeparate(separate)
{}

CDataHandler::CDataHandler(const CDataHandler & src)
  : COutputHandler(src)
  , mCNsBefore(src.mCNsBefore)
  , mCNsDuring(src.mCNsDuring)
  , mCNsAfter(src.mCNsAfter)
  , mAfterObjectList(src.mAfterObjectList)
  , mDuringObjectList(src.mDuringObjectList)
  , mBeforeObjectList(src.mBeforeObjectList)
  , mBeforeData(src.mBeforeData)
  , mDuringData(src.mDuringData)
  , mAfterData(src.mAfterData)
  , mSeparate(src.mSeparate)
{}

CDataHandler::~CDataHandler()
{
  cleanup();
}

void CDataHandler::addBeforeName(const CRegisteredCommonName & name)
{
  mCNsBefore.push_back(name);
}

void CDataHandler::addDuringName(const CRegisteredCommonName & name)
{
  mCNsDuring.push_back(name);
}

void CDataHandler::addAfterName(const CRegisteredCommonName & name)
{
  mCNsAfter.push_back(name);
}

bool CDataHandler::addName(const CRegisteredCommonName & name, const Activity & activity)
{
  switch (activity)
    {
      case COutputInterface::BEFORE:
        addBeforeName(name);
        return true;

      case COutputInterface::DURING:
        addDuringName(name);
        return true;

      case COutputInterface::AFTER:
        addAfterName(name);
        return true;

      default:
        return false;
    }
}

std::vector< CRegisteredCommonName > * CDataHandler::getNames(const Activity & activity)
{
  switch (activity)
    {
      case COutputInterface::BEFORE:
        return &mCNsBefore;

      case COutputInterface::DURING:
        return &mCNsDuring;

      case COutputInterface::AFTER:
        return &mCNsAfter;

      default:
        return NULL;
    }
}

void CDataHandler::clearNames(const Activity & activity)
{
  switch (activity)
    {
      case COutputInterface::BEFORE:
        mCNsBefore.clear();
        return;

      case COutputInterface::DURING:
        mCNsDuring.clear();
        return;

      case COutputInterface::AFTER:
        mCNsAfter.clear();
        return;

      default:
        return;
    }
}

const std::vector< C_FLOAT64 > & CDataHandler::getBeforeData() const
{
  return mBeforeData;
}

const std::vector< std::vector< C_FLOAT64 > > & CDataHandler::getDuringData() const
{
  return mDuringData;
}

const std::vector< C_FLOAT64 > & CDataHandler::getAfterData() const
{
  return mAfterData;
}

bool CDataHandler::getSeparate() const
{
  return mSeparate;
}

void CDataHandler::setSeparate(bool separate)
{
  mSeparate = separate;
}

void CDataHandler::cleanup()
{
  mBeforeObjectList.clear();
  mDuringObjectList.clear();
  mAfterObjectList.clear();

  finish();
  close();
}

void CDataHandler::output(const Activity & activity)
{
  switch (activity)
    {
      case COutputInterface::BEFORE:
        storeDataBefore();
        break;

      case COutputInterface::DURING:
        storeDataDuring();
        break;

      case COutputInterface::AFTER:
        storeDataAfter();
        break;
    }
}

void CDataHandler::separate(const Activity & activity)
{
  if (!mSeparate)
    return;

  switch (activity)
    {
      case COutputInterface::BEFORE:
        mBeforeData.push_back(std::numeric_limits< C_FLOAT64 >::quiet_NaN());
        break;

      case COutputInterface::DURING:
        mDuringData.push_back(std::vector<C_FLOAT64>());
        break;

      case COutputInterface::AFTER:
        mAfterData.push_back(std::numeric_limits< C_FLOAT64 >::quiet_NaN());
        break;

      default:
        break;
    }
}

void CDataHandler::finish()
{
  storeDataAfter();
}

C_FLOAT64 getValue(const CObjectInterface* pInt)
{
  const CDataObject * pObj = dynamic_cast< const CDataObject * >(pInt);

  if (pObj)
    {
      if (pObj->hasFlag(CDataObject::Flag::ValueInt))
        return (C_FLOAT64)(*(C_INT32 *) pInt->getValuePointer());

      if (pObj->hasFlag(CDataObject::Flag::ValueBool))
        return (C_FLOAT64)(*(bool*) pInt->getValuePointer());
    }

  return *static_cast< C_FLOAT64 * >(pInt->getValuePointer());
}

void CDataHandler::storeDataBefore()
{
  std::vector< CObjectInterface * >::iterator it = mBeforeObjectList.begin();
  std::vector< CObjectInterface * >::iterator end = mBeforeObjectList.end();

  if (it == end)
    return;

  for (; it != end; ++it)
    mBeforeData.push_back(getValue(*it));
}

void CDataHandler::storeDataDuring()
{
  std::vector< CObjectInterface * >::iterator it = mDuringObjectList.begin();
  std::vector< CObjectInterface * >::iterator end = mDuringObjectList.end();

  if (it == end)
    return;

  std::vector< C_FLOAT64 > row;

  for (; it != end; ++it)
    {
      row.push_back(getValue(*it));
    }

  mDuringData.push_back(row);
}

void CDataHandler::storeDataAfter()
{
  std::vector< CObjectInterface * >::iterator it = mAfterObjectList.begin();
  std::vector< CObjectInterface * >::iterator end = mAfterObjectList.end();

  if (it == end)
    return;

  for (; it != end; ++it)
    mAfterData.push_back(getValue(*it));
}

// Compile the List of Report Objects

bool CDataHandler::compile(CObjectInterface::ContainerList listOfContainer)
{
  bool success = true;
  COutputInterface::mObjects.clear();

  success &= generateObjectsFromName(listOfContainer, mBeforeObjectList,
                                     &mCNsBefore);

  success &= generateObjectsFromName(listOfContainer, mDuringObjectList,
                                     &mCNsDuring);

  success &= generateObjectsFromName(listOfContainer, mAfterObjectList,
                                     &mCNsAfter);

  return success;
}

// make to support parallel tasks
bool CDataHandler::generateObjectsFromName(const CObjectInterface::ContainerList & listOfContainer,
    std::vector< CObjectInterface * > & objectList,
    const std::vector< CRegisteredCommonName > * nameVector)
{
  bool result = true;
  objectList.clear();

  if (nameVector == NULL)
    return result;

  unsigned C_INT32 i;
  CObjectInterface * pObjectInterface;

  for (i = 0; i < nameVector->size(); ++i)
    {
      pObjectInterface = CObjectInterface::GetObjectFromCN(listOfContainer, (*nameVector)[i]);

      if (pObjectInterface == NULL)
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6, (*nameVector)[i].c_str());
          result = false;
          continue;
        }

      auto * pObj = dynamic_cast< CDataObject * >(pObjectInterface);
      bool isData = false;

      if (pObj && pObj->getObjectType() == "Reference")
        {
          isData = pObj->hasFlag(CDataObject::Flag::ValueBool)
                   || pObj->hasFlag(CDataObject::Flag::ValueInt)
                   || pObj->hasFlag(CDataObject::Flag::ValueDbl);
        }

      auto * pMathRef = dynamic_cast< CMathObject * >(pObjectInterface);

      if (!isData && pMathRef == NULL)
        {
          CCopasiMessage(CCopasiMessage::WARNING, "CDataHandler: This handler can only handle double value references. %s is not one.", (*nameVector)[i].c_str());
          result = false;
          continue;
        }

      mObjects.insert(pObjectInterface);
      objectList.push_back(pObjectInterface);
    }

  return result;
}
