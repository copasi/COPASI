// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/Attic/qwt3dBaseWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2007/11/13 14:20:55 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "qwt3dBaseWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qslider.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <iostream>

/*
 *  Constructs a BaseWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
BaseWidget::BaseWidget(QWidget* parent, const char* name, WFlags fl, bool showSlider)
    : QWidget(parent, name, fl)
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

  // activateSlider();
  //  mpSlider = true;
  mpSlider = false;
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
  mpSliderRow->setMinValue(0);
  mpSliderRow->setMaxValue(0);
  mpSliderRow->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpSliderRow->setOrientation(QSlider::Vertical);
  mpVBoxSmall->addWidget(mpSliderRow, 0, 0);

  mpLabelColumn = new QLabel(this, "LabelColumn");
  mpLabelColumn->setText("Column");
  mpHBoxSmall->addWidget(mpLabelColumn, 0, 0);
  mpSliderColumn = new QSlider(this, "SliderColumn");
  mpSliderColumn->setMinValue(0);
  mpSliderColumn->setMaxValue(0);
  mpSliderColumn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpSliderColumn->setOrientation(QSlider::Horizontal);
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
  sliderMoved(mpSliderColumn->value(), mpSliderRow->value());
}

void BaseWidget::sliderMoved(int column, int row)
{}

void BaseWidget::languageChange()
{}
