// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "CQProgressItemBar.h"
#include "CQProgressItem.h"
#include "qtUtilities.h"

/*
 *  Constructs a CQProgressItemBar which is a child of 'parent', with the
 *  name 'name'.'
 */
CQProgressItemBar::CQProgressItemBar(QWidget* parent, const char* name)
  : CQProgressItem(parent, name)
{
  Ui::CQProgressItemBar::setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItemBar::~CQProgressItemBar()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

bool CQProgressItemBar::initFromProcessReportItem(CProcessReportItem * pItem)
{
  mpItem = pItem;
  mValue = mpItem->getValue();
  mEnd = mpItem->getEndValue();

  mItemName->setText(FROM_UTF8(mpItem->getObjectName()));
  mProgressBar->setMinimum(0);
  mProgressBar->setMaximum(100);

  mLastSet = -1; // indicates was never set;

  // needed so that reset() does allocation
  if (mStart.pVOID != NULL) destroy();

  return reset();
}

bool CQProgressItemBar::process()
{
  (this->*mpSetValue)();

  if (mCurrentValue != mLastSet)
    {
      mProgressBar->setValue(mCurrentValue);
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

void CQProgressItemBar::destroy()
{
  if (mpItem == NULL) return;

  switch (mpItem->getType())
    {
      case CCopasiParameter::DOUBLE:
      case CCopasiParameter::UDOUBLE:
        pdelete(mStart.pDOUBLE);
        break;

      case CCopasiParameter::INT:
        pdelete(mStart.pINT);
        break;

      case CCopasiParameter::UINT:
        pdelete(mStart.pUINT);
        break;

      default:
        break;
    }
}

void CQProgressItemBar::init()
{
  mpItem = NULL;
  mStart.pVOID = NULL;
}
