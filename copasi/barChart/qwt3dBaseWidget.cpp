// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/Attic/qwt3dBaseWidget.cpp,v $
//   $Revision: 1.6.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/27 17:40:54 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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

#include "qwt3dBaseWidget.h"

#include <qvariant.h>
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

/*
 *  Constructs a BaseWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
BaseWidget::BaseWidget(QWidget* parent, const char*  name, Qt::WFlags fl)
    : QWidget(parent, fl),
    mpSlider(false)
{
  if (!name)
    setName("BaseWidget");

  mpBaseWidgetLayout = new QGridLayout(this, 1, 1, 0, 0, "BaseWidgetLayout");

  mpVBoxBig = new QVBoxLayout(0, "VBoxBig");

  mpHBoxBig = new QHBoxLayout(0, "HBoxBig");

  mpFrame = new QFrame(this, "Frame");
  mpFrame->setFrameShape(QFrame::StyledPanel);
  mpFrame->setFrameShadow(QFrame::Sunken);
  mpHBoxBig->addWidget(mpFrame, 0, 0);

  mpVBoxSmall = new QVBoxLayout(0, "VBoxSmall");
  mpHBoxBig->addLayout(mpVBoxSmall, 0);

  mpVBoxBig->addLayout(mpHBoxBig, 0);
  mpHBoxSmall = new QHBoxLayout(0, "HBoxSmall");

  mpVBoxBig->addLayout(mpHBoxSmall, 0);
  mpBaseWidgetLayout->addLayout(mpVBoxBig, 0, 0);

  mScaleFactor = 1000;
}

/*
 *  Destroys the object and frees any allocated resources
 */
BaseWidget::~BaseWidget()
{}

void BaseWidget::activateSlider()
{
  mpSlider = true;
  mpLabelRow = new QLabel(this, "LabelRow");
  mpLabelRow->setText("Row");
  mpVBoxSmall->addWidget(mpLabelRow, 0, 0);
  mpSliderRow = new QSlider(this, "SliderRow");

  mpSliderRow->setMinimum(0);
  mpSliderRow->setMaximum(0);

  mpSliderRow->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpSliderRow->setOrientation(Qt::Vertical);
  mpVBoxSmall->addWidget(mpSliderRow, 0, 0);

  mpLabelColumn = new QLabel(this, "LabelColumn");
  mpLabelColumn->setText("Column ");
  mpHBoxSmall->addWidget(mpLabelColumn, 0, 0);
  mpSliderColumn = new QSlider(this, "SliderColumn");

  mpSliderColumn->setMinimum(0);
  mpSliderColumn->setMaximum(0);

  mpSliderColumn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpSliderColumn->setOrientation(Qt::Horizontal);
  mpHBoxSmall->addWidget(mpSliderColumn, 0, 0);
  mpHBoxSmall->addSpacing(24);

  QToolTip::add(mpSliderRow, "move slider to view requested row-description");
  QToolTip::add(mpSliderColumn, "move slider to view requested column-description");

  connect(mpSliderColumn, SIGNAL(valueChanged(int)), this, SLOT(setSlider()));
  connect(mpSliderRow, SIGNAL(valueChanged(int)), this, SLOT(setSlider()));
}

void BaseWidget::setSlider()
{
  if (!mpSlider) return;

  int col = mpSliderColumn->value();
  int row = mpSliderRow->value();

#ifdef DEBUG_UI
  qDebug() << "A BaseWidget::setSlider -> col = " << col << " - row = " << row;
#endif

  sliderMoved(mpSliderColumn->value() / mScaleFactor, mpSliderRow->value() / mScaleFactor);

#ifdef DEBUG_UI
  qDebug() << "B BaseWidget::setSlider -> col = " << col << " - row = " << row;
#endif

  mpSliderColumn->setValue(col);
  mpSliderRow->setValue(row);

#ifdef DEBUG_UI
  qDebug() << "C BaseWidget::setSlider -> col = " << mpSliderColumn->value() << " - row = " << mpSliderRow->value();
#endif
}

int BaseWidget::scaleFactor()
{
  return mScaleFactor;
}

void BaseWidget::languageChange()
{}
