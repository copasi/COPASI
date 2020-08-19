// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include "CQProgressItemBar.h"

#include "qtUtilities.h"
#include "copasi/utilities/CProcessReport.h"

/*
 *  Constructs a CQProgressItemBar which is a child of 'parent', with the
 *  name 'name'.'
 */
CQProgressItemBar::CQProgressItemBar(QWidget* parent, const char* name):
  CQProgressItem(parent, name),
  mFactor(1.0),
  mpEnd(NULL),
  mpStart(NULL),
  mpValue(NULL),
  mLastSet(0),
  mCurrentValue(0)
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
  mpValue = mpItem->getValuePointer();
  mpEnd = mpItem->getEndValuePointer();

  mItemName->setText(FROM_UTF8(mpItem->getObjectName()));
  mProgressBar->setMinimum(0);
  mProgressBar->setMaximum(100);

  mLastSet = -1; // indicates was never set;

  // needed so that reset() does allocation
  if (mpStart != NULL) destroy();

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
      case CCopasiParameter::Type::DOUBLE:
      case CCopasiParameter::Type::UDOUBLE:

        if (mpStart == NULL)
          mpStart = new C_FLOAT64;

        * static_cast< C_FLOAT64 * >(mpStart) = * static_cast< C_FLOAT64 * >(mpValue);
        mFactor = 100.0 / (* static_cast< C_FLOAT64 * >(mpEnd) - * static_cast< C_FLOAT64 *>(mpStart));
        mpSetValue = & CQProgressItemBar::setValueFromDOUBLE;
        break;

      case CCopasiParameter::Type::INT:

        if (mpStart == NULL)
          mpStart = new C_INT32;

        * static_cast< C_INT32 * >(mpStart) = * static_cast< C_INT32 * >(mpValue);
        mFactor = 100.0 / ((C_FLOAT64)(* static_cast< C_INT32 * >(mpEnd) - * static_cast< C_INT32 * >(mpStart)));
        mpSetValue = & CQProgressItemBar::setValueFromINT;
        break;

      case CCopasiParameter::Type::UINT:

        if (mpStart == NULL)
          mpStart = new unsigned C_INT32;

        * static_cast< unsigned C_INT32 * >(mpStart) = * static_cast< unsigned C_INT32 * >(mpValue);
        mFactor = 100.0 / ((C_FLOAT64)(* static_cast< unsigned C_INT32 * >(mpEnd) - * static_cast< unsigned C_INT32 * >(mpStart)));
        mpSetValue = & CQProgressItemBar::setValueFromUINT;
        break;

      default:
        break;
    }

  // if mFactor is invalid (happens for start == end), reset
  if (mFactor != mFactor || mFactor > 100)
    mFactor = 100;

  return process();
}

void CQProgressItemBar::setValueFromDOUBLE()
{mCurrentValue = (C_INT32)(mFactor * (* static_cast< C_FLOAT64 * >(mpValue) - * static_cast< C_FLOAT64 * >(mpStart)));}

void CQProgressItemBar::setValueFromINT()
{mCurrentValue = (C_INT32)(mFactor * (* static_cast< C_INT32 * >(mpValue) - * static_cast< C_INT32 * >(mpStart)));}

void CQProgressItemBar::setValueFromUINT()
{mCurrentValue = (C_INT32)(mFactor * (* static_cast< unsigned C_INT32 * >(mpValue) - * static_cast< unsigned C_INT32 * >(mpStart)));}

void CQProgressItemBar::destroy()
{
  if (mpItem == NULL) return;

  CCopasiParameter::deleteValue(mpItem->getType(), mpStart);
}

void CQProgressItemBar::init()
{
  mpItem = NULL;
  mpStart = NULL;
}
