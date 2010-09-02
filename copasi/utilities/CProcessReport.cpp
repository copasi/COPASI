/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CProcessReport.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $
   $Date: 2010/09/02 14:31:13 $
   End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "utilities/CVector.h"
#include "CProcessReport.h"
#include "report/CCopasiObject.h"

CProcessReportItem::CProcessReportItem():
    CCopasiParameter("NoName", CCopasiParameter::DOUBLE),
    mEndValue(),
    mHasEndValue(false)
{
  mEndValue = mValue;
  mValue.pDOUBLE = NULL;
}

CProcessReportItem::CProcessReportItem(const std::string & name,
                                       const Type & type,
                                       const void * pValue,
                                       const void * pEndValue):
    CCopasiParameter(name, type, pEndValue, NULL, "ProcessReportItem"),
    mEndValue(),
    mHasEndValue(pEndValue != NULL)
{
  mEndValue = mValue;
  mValue.pVOID = const_cast<void *>(pValue);
}

CProcessReportItem::CProcessReportItem(const CProcessReportItem & src):
    CCopasiParameter(src.getObjectName(), src.getType(), src.mEndValue.pVOID, NULL, "ProcessReportItem"),
    mEndValue(),
    mHasEndValue(src.mHasEndValue)
{
  mEndValue = mValue;
  mValue = src.mValue;
}

CProcessReportItem::~CProcessReportItem()
{
  mValue = mEndValue;
}

const bool & CProcessReportItem::hasEndValue() const {return mHasEndValue;}

const CCopasiParameter::Value & CProcessReportItem::getEndValue() const
{return mEndValue;}

CCopasiParameter::Value & CProcessReportItem::getEndValue()
{return mEndValue;}

CProcessReport::CProcessReport():
    mProcessReportItemList(1)
{mProcessReportItemList[0] = NULL;}

CProcessReport::~CProcessReport()
{
  unsigned C_INT32 i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    pdelete(mProcessReportItemList[i]);
}

unsigned C_INT32 CProcessReport::addItem(const std::string & name,
    const CCopasiParameter::Type & type,
    const void * pValue,
    const void * pEndValue)
{
  unsigned C_INT32 i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] == NULL) break;

  unsigned C_INT32 handle = i;

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
  unsigned C_INT32 i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] && !progressItem(i)) success = false;

  return success;
}

bool CProcessReport::progressItem(const unsigned C_INT32 & handle)
{return isValidHandle(handle);}

bool CProcessReport::proceed()
{return true;}

bool CProcessReport::reset()
{
  bool success = true;
  unsigned C_INT32 i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] && !resetItem(i)) success = false;

  return success;
}

bool CProcessReport::resetItem(const unsigned C_INT32 & handle)
{return isValidHandle(handle);}

bool CProcessReport::finish()
{
  bool success = true;
  unsigned C_INT32 i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++)
    if (mProcessReportItemList[i] && !finishItem(i)) success = false;

  return success;
}

bool CProcessReport::finishItem(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle)) return false;

  pdelete(mProcessReportItemList[handle]);
  return true;
}

bool CProcessReport::isValidHandle(const unsigned C_INT32 handle) const
{
  return (handle < mProcessReportItemList.size() &&
          mProcessReportItemList[handle] != NULL);
}

bool CProcessReport::setName(const std::string & name)
{
  mName = name;
  return true;
}
