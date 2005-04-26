/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQProgressItemBar.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/26 14:28:19 $
   End CVS Header */

#include "qtUtilities.h"

bool CQProgressItemBar::initFromProcessReportItem(CProcessReportItem * pItem)
{
  mpItem = pItem;
  mpValue = mpItem->getValue();
  mpStart = NULL;
  mpEnd = mpItem->getEndValue();

  mItemName->setText(FROM_UTF8(mpItem->getObjectName()));
  mProgressBar->setTotalSteps(100);

  mLastSet = -1; // indcates was never set;

  return reset();
}

bool CQProgressItemBar::process()
{
  (this->*mpSetValue)();

  if (mValue != mLastSet) mProgressBar->setProgress(mValue);

  return true;
}

bool CQProgressItemBar::reset()
{
  switch (mpItem->getType())
    {
    case CCopasiParameter::DOUBLE:
    case CCopasiParameter::UDOUBLE:
      if (!mpStart)
        mpStart = new C_FLOAT64(*(C_FLOAT64 *)mpValue);
      else
        *(C_FLOAT64 *)mpStart = *(C_FLOAT64 *)mpValue;
      mFactor = 100.0 / (*(C_FLOAT64 *)mpEnd - *(C_FLOAT64 *)mpStart);
      mpSetValue = & CQProgressItemBar::setValueFromDOUBLE;
      break;

    case CCopasiParameter::INT:
      if (!mpStart)
        mpStart = new C_INT32(*(C_INT32 *)mpValue);
      else
        *(C_INT32 *)mpStart = *(C_INT32 *)mpValue;
      mFactor = 100.0 / ((C_FLOAT64)(*(C_INT32 *)mpEnd - *(C_INT32 *)mpStart));
      mpSetValue = & CQProgressItemBar::setValueFromINT;
      break;

    case CCopasiParameter::UINT:
      if (!mpStart)
        mpStart = new unsigned C_INT32(*(unsigned C_INT32 *)mpValue);
      else
        *(unsigned C_INT32 *)mpStart = *(unsigned C_INT32 *)mpValue;
      mFactor = 100.0 / ((C_FLOAT64)(*(unsigned C_INT32 *)mpEnd - *(unsigned C_INT32 *)mpStart));
      mpSetValue = & CQProgressItemBar::setValueFromUINT;
      break;

    default:
      break;
    }

  return process();
}

void CQProgressItemBar::setValueFromDOUBLE()
{mValue = (C_INT32)(mFactor * (*(C_FLOAT64 *)mpValue - *(C_FLOAT64 *)mpStart));}

void CQProgressItemBar::setValueFromINT()
{mValue = (C_INT32)(mFactor * (*(C_INT32 *)mpValue - *(C_INT32 *)mpStart));}

void CQProgressItemBar::setValueFromUINT()
{mValue = (C_INT32)(mFactor * (*(unsigned C_INT32 *)mpValue - *(unsigned C_INT32 *)mpStart));}
