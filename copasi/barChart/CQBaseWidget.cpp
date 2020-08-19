// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QVariant>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QLayout>
#include <QToolTip>
#include <QAction>
#include <QMenuBar>

//Added by qt3to4:
#include <iostream>

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

#include "CQBaseWidget.h"

/*
 *  Constructs a CQBaseWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
CQBaseWidget::CQBaseWidget(QWidget* parent, const char* /* name */, Qt::WindowFlags fl)
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

void CQBaseWidget::setSliderActive(const bool &active)
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
  qDebug() << "C CQBaseWidget::setSlider -> col = " << mpSliderColumn->value() << " - row = " << mpSliderRow->value();
#endif
}

int CQBaseWidget::scaleFactor()
{
  return mScaleFactor;
}
