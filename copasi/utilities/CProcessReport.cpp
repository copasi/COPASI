// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "CProcessReport.h"

#include "CVector.h"
#include "CopasiTime.h"

#include "report/CCopasiObject.h"

CProcessReportItem::CProcessReportItem():
  CCopasiParameter("NoName", CCopasiParameter::DOUBLE),
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

CProcessReport::CProcessReport(const unsigned int & maxTime):
  mProcessReportItemList(1),
  mpEndTime(NULL)
{
  mProcessReportItemList[0] = NULL;

  if (maxTime > 0)
    {
      mpEndTime = new CCopasiTimeVariable(CCopasiTimeVariable::getCurrentWallTime() + maxTime * LLONG_CONST(1000000));
    }
}

CProcessReport::~CProcessReport()
{
  size_t i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    pdelete(mProcessReportItemList[i]);

  pdelete(mpEndTime);
}

size_t CProcessReport::addItem(const std::string & name,
                               const std::string & value,
                               const std::string * pEndValue)
{
  return addItem(name, CCopasiParameter::STRING, &value, pEndValue);
}

size_t CProcessReport::addItem(const std::string & name,
                               const C_INT32 & value,
                               const C_INT32 * pEndValue)
{
  return addItem(name, CCopasiParameter::INT, &value, pEndValue);
}

size_t CProcessReport::addItem(const std::string & name,
                               const unsigned C_INT32 & value,
                               const unsigned C_INT32 * pEndValue)
{
  return addItem(name, CCopasiParameter::UINT, &value, pEndValue);
}

size_t CProcessReport::addItem(const std::string & name,
                               const C_FLOAT64 & value,
                               const C_FLOAT64 * pEndValue)
{
  return addItem(name, CCopasiParameter::DOUBLE, &value, pEndValue);
}

size_t CProcessReport::addItem(const std::string & name,
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

bool CProcessReport::progress()
{
  bool success = true;
  size_t i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] && !progressItem(i)) success = false;

  return success && proceed();
}

bool CProcessReport::progressItem(const size_t & handle)
{
  return isValidHandle(handle) && proceed();
}

bool CProcessReport::proceed()
{
  if (mpEndTime == NULL) return true;

  return (CCopasiTimeVariable::getCurrentWallTime() < *mpEndTime);
}

bool CProcessReport::reset()
{
  bool success = true;
  size_t i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] && !resetItem(i)) success = false;

  return success;
}

bool CProcessReport::resetItem(const size_t & handle)
{
  return isValidHandle(handle) && proceed();
}

bool CProcessReport::finish()
{
  bool success = true;
  size_t i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] && !finishItem(i)) success = false;

  return success;
}

bool CProcessReport::finishItem(const size_t & handle)
{
  if (!isValidHandle(handle)) return false;

  pdelete(mProcessReportItemList[handle]);
  return true;
}

bool CProcessReport::isValidHandle(const size_t handle) const
{
  return (handle < mProcessReportItemList.size() &&
          mProcessReportItemList[handle] != NULL);
}

bool CProcessReport::setName(const std::string & name)
{
  mName = name;
  return true;
}
