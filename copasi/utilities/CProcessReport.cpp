// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

#include "CProcessReport.h"

#include "CopasiTime.h"

#include "copasi/core/CDataObject.h"
#include "copasi/core/CVector.h"

CProcessReportItem::CProcessReportItem():
  CCopasiParameter("NoName", CCopasiParameter::Type::DOUBLE),
  mpEndValue(NULL),
  mHasEndValue(false)
{
  mpEndValue = mpValue;
  mpValue = NULL;
}

CProcessReportItem::CProcessReportItem(const std::string & name,
                                       const Type & type,
                                       const void * pValue,
                                       const void * pEndValue):
  CCopasiParameter(name, type, pEndValue, NULL, "ProcessReportItem"),
  mpEndValue(NULL),
  mHasEndValue(pEndValue != NULL)
{
  mpEndValue = mpValue;
  mpValue = const_cast<void *>(pValue);
}

CProcessReportItem::CProcessReportItem(const CProcessReportItem & src):
  CCopasiParameter(src.getObjectName(), src.getType(), src.mpEndValue, NULL, "ProcessReportItem"),
  mpEndValue(NULL),
  mHasEndValue(src.mHasEndValue)
{
  mpEndValue = mpValue;
  mpValue = src.mpValue;
}

CProcessReportItem::~CProcessReportItem()
{
  mpValue = mpEndValue;
}

void * CProcessReportItem::getEndValuePointer()
{
  return mpEndValue;
}

const bool & CProcessReportItem::hasEndValue() const {return mHasEndValue;}

CProcessReportInterface::CProcessReportInterface(const unsigned int & maxTime)
  : mProccessingInstruction(ProccessingInstruction::Continue)
  , mIgnoreStop(false)
  , mProcessReportItemList(1)
  , mpEndTime(NULL)
{
  mProcessReportItemList[0] = NULL;

  if (maxTime > 0)
    {
      mpEndTime = new CCopasiTimeVariable(CCopasiTimeVariable::getCurrentWallTime() + maxTime * LLONG_CONST(1000000));
    }
}

CProcessReportInterface::~CProcessReportInterface()
{
  size_t i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    pdelete(mProcessReportItemList[i]);

  pdelete(mpEndTime);
}

size_t CProcessReportInterface::addItem(const std::string & name,
                                        const CCopasiParameter::Type & type,
                                        const void * pValue,
                                        const void * pEndValue)
{
  size_t i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] == NULL) break;

  size_t handle = i;

  if (i == imax) // We need to resize.
    {
      CVector< CProcessReportItem * > tmp = mProcessReportItemList;
      mProcessReportItemList.resize(2 * imax); // Note, imax is never zero

      for (i = 0; i < imax; i++)  // Copy existing items
        mProcessReportItemList[i] = tmp[i];

      imax *= 2;

      while (i < imax) mProcessReportItemList[i++] = NULL;
    }

  mProcessReportItemList[handle] = new CProcessReportItem(name, type, pValue, pEndValue);
  return handle;
}

bool CProcessReportInterface::progress()
{
  bool success = true;
  size_t i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] && !progressItem(i)) success = false;

  return success && proceed();
}

bool CProcessReportInterface::progressItem(const size_t & handle)
{
  return isValidHandle(handle) && proceed();
}

bool CProcessReportInterface::proceed()
{
  if (mpEndTime != NULL
      && *mpEndTime < CCopasiTimeVariable::getCurrentWallTime())
    return false;

  return mProccessingInstruction == ProccessingInstruction::Continue
         || (mIgnoreStop && mProccessingInstruction == ProccessingInstruction::Stop);
}

bool CProcessReportInterface::reset()
{
  bool success = true;
  size_t i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] && !resetItem(i)) success = false;

  return success;
}

bool CProcessReportInterface::resetItem(const size_t & handle)
{
  return isValidHandle(handle) && proceed();
}

bool CProcessReportInterface::finish()
{
  bool success = true;
  size_t i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] && !finishItem(i)) success = false;

  return success;
}

bool CProcessReportInterface::finishItem(const size_t & handle)
{
  if (!isValidHandle(handle)) return false;

  pdelete(mProcessReportItemList[handle]);
  return true;
}

bool CProcessReportInterface::isValidHandle(const size_t handle) const
{
  return (handle < mProcessReportItemList.size() &&
          mProcessReportItemList[handle] != NULL);
}

bool CProcessReportInterface::setName(const std::string & name)
{
  mName = name;
  return true;
}

void CProcessReportInterface::setIgnoreStop(const bool & ignoreStop)
{
  mIgnoreStop = ignoreStop;
}

const bool & CProcessReportInterface::getIgnoreStop() const\
{
  return mIgnoreStop;
}

CProcessReport::CProcessReport(CProcessReportInterface * pInterface)
  : mpInterface(pInterface)
  , mLevel(0)
  , mMaxDisplayLevel(2)
{}

CProcessReport::~CProcessReport()
{}

CProcessReport::operator bool() const
{
  return mpInterface != NULL;
}

CProcessReport CProcessReport::operator++()
{
  ++mLevel;

  return *this;
}

size_t CProcessReport::addItem(const std::string & name,
                               const std::string & value,
                               const std::string * pEndValue)
{
  if (mpInterface != NULL
      && mLevel < mMaxDisplayLevel)
    return mpInterface->addItem(name, CCopasiParameter::Type::STRING, &value, pEndValue);

  return C_INVALID_INDEX;
}

size_t CProcessReport::addItem(const std::string & name,
                               const C_INT32 & value,
                               const C_INT32 * pEndValue)
{
  if (mpInterface != NULL
      && mLevel < mMaxDisplayLevel)
    return mpInterface->addItem(name, CCopasiParameter::Type::INT, &value, pEndValue);

  return C_INVALID_INDEX;
}

size_t CProcessReport::addItem(const std::string & name,
                               const unsigned C_INT32 & value,
                               const unsigned C_INT32 * pEndValue)
{
  if (mpInterface != NULL
      && mLevel < mMaxDisplayLevel)
    return mpInterface->addItem(name, CCopasiParameter::Type::UINT, &value, pEndValue);

  return C_INVALID_INDEX;
}

size_t CProcessReport::addItem(const std::string & name,
                               const C_FLOAT64 & value,
                               const C_FLOAT64 * pEndValue)
{
  if (mpInterface != NULL
      && mLevel < mMaxDisplayLevel)
    return mpInterface->addItem(name, CCopasiParameter::Type::DOUBLE, &value, pEndValue);

  return C_INVALID_INDEX;
}

bool CProcessReport::progress()
{
  if (mpInterface != NULL)
    return mpInterface->progress();

  return proceed();
}

bool CProcessReport::progressItem(const size_t & handle)
{
  if (mpInterface != NULL
      && mLevel < mMaxDisplayLevel)
    return mpInterface->progressItem(handle);

  return proceed();
}

bool CProcessReport::resetItem(const size_t & handle)
{
  if (mpInterface != NULL
      && mLevel < mMaxDisplayLevel)
    return mpInterface->resetItem(handle);

  return proceed();
}

bool CProcessReport::finish()
{
  if (mpInterface != NULL)
    return mpInterface->finish();

  return proceed();
}

bool CProcessReport::finishItem(const size_t & handle)
{
  if (mpInterface != NULL
      && mLevel < mMaxDisplayLevel)
    return mpInterface->finishItem(handle);

  return proceed();
}

bool CProcessReport::proceed()
{
  if (mpInterface != NULL)
    return mpInterface->proceed();

  return true;
}

bool CProcessReport::setName(const std::string & name)
{
  if (mpInterface != NULL)
    return mpInterface->setName(name);

  return false;
}

void CProcessReport::setIgnoreStop(const bool & ignoreStop)
{
  if (mpInterface != NULL)
    mpInterface->setIgnoreStop(ignoreStop);

  return;
}
