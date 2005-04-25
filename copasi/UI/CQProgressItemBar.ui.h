/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQProgressItemBar.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:13:22 $
   End CVS Header */

#include "qtUtilities.h"

bool CQProgressItemBar::initFromProcessReportItem(CProcessReportItem * pItem)
{
  mpItem = pItem;
  mpValue = mpItem->getValue();
  mpStart = NULL;
  mpEnd = mpItem->getEndValue();

  mItemName->setText(FROM_UTF8(mpItem->getObjectName()));
  mProgressBar->setTotalSteps(1000);

  return reset();
}

bool CQProgressItemBar::process()
{
  (this->*mpProgress)();
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
      mFactor = 1000.0 / (*(C_FLOAT64 *)mpEnd - *(C_FLOAT64 *)mpStart);
      mpProgress = & CQProgressItemBar::setProgressFromDOUBLE;
      break;

    case CCopasiParameter::INT:
      if (!mpStart)
        mpStart = new C_INT32(*(C_INT32 *)mpValue);
      else
        *(C_INT32 *)mpStart = *(C_INT32 *)mpValue;
      mFactor = 1000.0 / ((C_FLOAT64)(*(C_INT32 *)mpEnd - *(C_INT32 *)mpStart));
      mpProgress = & CQProgressItemBar::setProgressFromINT;
      break;

    case CCopasiParameter::UINT:
      if (!mpStart)
        mpStart = new unsigned C_INT32(*(unsigned C_INT32 *)mpValue);
      else
        *(unsigned C_INT32 *)mpStart = *(unsigned C_INT32 *)mpValue;
      mFactor = 1000.0 / ((C_FLOAT64)(*(unsigned C_INT32 *)mpEnd - *(unsigned C_INT32 *)mpStart));
      mpProgress = & CQProgressItemBar::setProgressFromUINT;
      break;

    default:
      break;
    }

  return process();
}

void CQProgressItemBar::setProgressFromDOUBLE()
{
  mProgressBar->setProgress((C_INT32)(mFactor * (*(C_FLOAT64 *)mpValue - *(C_FLOAT64 *)mpStart)));
}

void CQProgressItemBar::setProgressFromINT()
{
  mProgressBar->setProgress((C_INT32)(mFactor * (*(C_INT32 *)mpValue - *(C_INT32 *)mpStart)));
}

void CQProgressItemBar::setProgressFromUINT()
{
  mProgressBar->setProgress((C_INT32)(mFactor * (*(unsigned C_INT32 *)mpValue - *(unsigned C_INT32 *)mpStart)));
}
