/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CProcessReport.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/19 13:57:47 $
   End CVS Header */

#include "copasi.h"

#include "utilities/CVector.h"
#include "CProcessReport.h"
#include "report/CCopasiObject.h"

CProcessReportItem::CProcessReportItem():
    CCopasiParameter("NoName", CCopasiParameter::DOUBLE),
    mpEndValue(NULL)
{
  mpEndValue = mpValue;
  mpValue = NULL;
}

CProcessReportItem::CProcessReportItem(const std::string & name,
                                       const Type & type,
                                       const void * pValue,
                                       const void * pEndValue):
    CCopasiParameter(name, type, pEndValue, NULL, "ProcessReportItem"),
    mpEndValue(NULL)
{
  mpEndValue = mpValue;
  mpValue = const_cast<void *>(pValue);
}

CProcessReportItem::CProcessReportItem(const CProcessReportItem & src):
    CCopasiParameter(src.getObjectName(), src.getType(), src.mpEndValue, NULL, "ProcessReportItem"),
    mpEndValue(NULL)
{
  mpEndValue = mpValue;
  mpValue = src.mpValue;
}

CProcessReportItem::~CProcessReportItem()
{
  mpValue = mpEndValue;
}

const void * CProcessReportItem::getEndValue() const
  {return mpEndValue;}

void * CProcessReportItem::getEndValue()
{return mpEndValue;}

CProcessReport::CProcessReport():
    mProcessReportItemList(1)
{
  unsigned C_INT32 i, imax = mProcessReportItemList.size();

  for (i = 0; i < imax; i++) mProcessReportItemList[i] = NULL;
}

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

bool CProcessReport::progress(const unsigned C_INT32 & handle)
{return (isValidHandle(handle) || handle == C_INVALID_INDEX);}

bool CProcessReport::proceed()
{return true;}

bool CProcessReport::reset(const unsigned C_INT32 & handle)
{return (isValidHandle(handle) || handle == C_INVALID_INDEX);}

bool CProcessReport::finish(const unsigned C_INT32 & handle)
{
  if (handle == C_INVALID_INDEX)
    {
      unsigned C_INT32 i, imax = mProcessReportItemList.size();

      for (i = 0; i < imax; i++)
        pdelete(mProcessReportItemList[i]);

      return true;
    }

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
