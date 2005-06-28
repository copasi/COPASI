/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQProgressItemBar.ui.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/28 19:50:14 $
   End CVS Header */

#include "qtUtilities.h"

bool CQProgressItemBar::initFromProcessReportItem(CProcessReportItem * pItem)
{
  mpItem = pItem;
  mValue = mpItem->getValue();
  mEnd = mpItem->getEndValue();

  mItemName->setText(FROM_UTF8(mpItem->getObjectName()));
  mProgressBar->setTotalSteps(100);

  mLastSet = -1; // indcates was never set;

  mStart.pDOUBLE = NULL; // needed so that reset() does allocation
  return reset();
}

bool CQProgressItemBar::process()
{
  (this->*mpSetValue)();

  if (mCurrentValue != mLastSet)
    {
      mProgressBar->setProgress(mCurrentValue);
      mLastSet = mCurrentValue;
    }

  return true;
}

bool CQProgressItemBar::reset()
{
  switch (mpItem->getType())
    {
    case CCopasiParameter::DOUBLE:
    case CCopasiParameter::UDOUBLE:
      if (!mStart.pDOUBLE)
        mStart.pDOUBLE = new C_FLOAT64;

      * mStart.pDOUBLE = * mValue.pDOUBLE;
      mFactor = 100.0 / (* mEnd.pDOUBLE - * mStart.pDOUBLE);
      mpSetValue = & CQProgressItemBar::setValueFromDOUBLE;
      break;

    case CCopasiParameter::INT:
      if (!mStart.pINT)
        mStart.pINT = new C_INT32;

      * mStart.pINT = * mValue.pINT;
      mFactor = 100.0 / ((C_FLOAT64)(* mEnd.pINT - * mStart.pINT));
      mpSetValue = & CQProgressItemBar::setValueFromINT;
      break;

    case CCopasiParameter::UINT:
      if (!mStart.pUINT)
        mStart.pUINT = new unsigned C_INT32;

      * mStart.pUINT = * mValue.pUINT;
      mFactor = 100.0 / ((C_FLOAT64)(* mEnd.pUINT - * mStart.pUINT));
      mpSetValue = & CQProgressItemBar::setValueFromUINT;
      break;

    default:
      break;
    }

  return process();
}

void CQProgressItemBar::setValueFromDOUBLE()
{mCurrentValue = (C_INT32)(mFactor * (* mValue.pDOUBLE - * mStart.pDOUBLE));}

void CQProgressItemBar::setValueFromINT()
{mCurrentValue = (C_INT32)(mFactor * (* mValue.pINT - * mStart.pINT));}

void CQProgressItemBar::setValueFromUINT()
{mCurrentValue = (C_INT32)(mFactor * (* mValue.pUINT - * mStart.pUINT));}
