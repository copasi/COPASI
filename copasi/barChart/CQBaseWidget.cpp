// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/CQBaseWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:33:34 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtCore/QVariant>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qslider.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qaction.h>
#include <qmenubar.h>

//Added by qt3to4:
#include <iostream>

#ifdef DEBUG_UI
#include <QtDebug>
#endif

#include "CQBaseWidget.h"

/*
 *  Constructs a CQBaseWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
CQBaseWidget::CQBaseWidget(QWidget* parent, const char* /* name */, Qt::WFlags fl)
    : QWidget(parent, fl),
    mSliderActive(false),
    mScaleFactor(1000)
{
  setupUi(this);

  setSliderActive(mSliderActive);

  connect(mpSliderRow, SIGNAL(valueChanged(int)), this, SLOT(setSlider()));
  connect(mpSliderColumn, SIGNAL(valueChanged(int)), this, SLOT(setSlider()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQBaseWidget::~CQBaseWidget()
{}

void CQBaseWidget::setSliderActive(const bool & active)
{
  mSliderActive = active;

  if (mSliderActive)
    {
      mpLabelRow->show();
      mpSliderRow->show();
      mpLabelColumn->show();
      mpSliderColumn->show();
    }
  else
    {
      mpLabelRow->hide();
      mpSliderRow->hide();
      mpLabelColumn->hide();
      mpSliderColumn->hide();

    }
}

bool CQBaseWidget::isSliderActive() const
{
  return mSliderActive;
}

void CQBaseWidget::setSlider()
{
  if (!mSliderActive) return;

  int row = mpSliderRow->value();
  int col = mpSliderColumn->value();

#ifdef DEBUG_UI
  qDebug() << "A CQBaseWidget::setSlider -> col = " << col << " - row = " << row;
#endif

  sliderMoved(mpSliderColumn->value() / mScaleFactor, mpSliderRow->value() / mScaleFactor);

#ifdef DEBUG_UI
  qDebug() << "B CQBaseWidget::setSlider -> col = " << col << " - row = " << row;
#endif

  mpSliderRow->setValue(row);
  mpSliderColumn->setValue(col);

#ifdef DEBUG_UI
  qDebug() << "C CQBaseWidget::setSlider -> col = " << mSliderActiveColumn->value() << " - row = " << mSliderActiveRow->value();
#endif
}

int CQBaseWidget::scaleFactor()
{
  return mScaleFactor;
}
