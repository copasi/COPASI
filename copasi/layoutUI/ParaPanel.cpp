// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/ParaPanel.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/07/06 10:14:27 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'ParaPanel.ui'
 **
 ** Created: Fri Jul 6 08:51:22 2007
 **      by: The User Interface Compiler ($Id: ParaPanel.cpp,v 1.3 2007/07/06 10:14:27 urost Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "ParaPanel.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qslider.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "ParaPanel.ui.h"

/*
 *  Constructs a ParaPanel as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
ParaPanel::ParaPanel(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("ParaPanel");
  QFont f(font());
  f.setBold(TRUE);
  setFont(f);
  ParaPanelLayout = new QVBoxLayout(this, 11, 6, "ParaPanelLayout");

  paraLabel = new QLabel(this, "paraLabel");
  QFont paraLabel_font(paraLabel->font());
  paraLabel_font.setPointSize(12);
  paraLabel->setFont(paraLabel_font);
  ParaPanelLayout->addWidget(paraLabel);

  layout1 = new QHBoxLayout(0, 0, 6, "layout1");

  frameRateLabel = new QLabel(this, "frameRateLabel");
  layout1->addWidget(frameRateLabel);

  spinBox1 = new QSpinBox(this, "spinBox1");
  layout1->addWidget(spinBox1);
  ParaPanelLayout->addLayout(layout1);

  layout3 = new QHBoxLayout(0, 0, 6, "layout3");

  schedModeLabel = new QLabel(this, "schedModeLabel");
  layout3->addWidget(schedModeLabel);

  scalingButtonGroup = new QButtonGroup(this, "scalingButtonGroup");

  QWidget* privateLayoutWidget = new QWidget(scalingButtonGroup, "layout2");
  privateLayoutWidget->setGeometry(QRect(10, 10, 156, 52));
  layout2 = new QVBoxLayout(privateLayoutWidget, 11, 6, "layout2");

  individScalButton = new QRadioButton(privateLayoutWidget, "individScalButton");
  layout2->addWidget(individScalButton);

  globalScalButton = new QRadioButton(privateLayoutWidget, "globalScalButton");
  layout2->addWidget(globalScalButton);
  layout3->addWidget(scalingButtonGroup);
  ParaPanelLayout->addLayout(layout3);

  animModeLabel = new QLabel(this, "animModeLabel");
  QFont animModeLabel_font(animModeLabel->font());
  animModeLabel_font.setPointSize(12);
  animModeLabel->setFont(animModeLabel_font);
  ParaPanelLayout->addWidget(animModeLabel);

  stepSlider = new QSlider(this, "stepSlider");
  stepSlider->setEnabled(FALSE);
  stepSlider->setOrientation(QSlider::Horizontal);
  stepSlider->setTickmarks(QSlider::Below);
  stepSlider->setTickInterval(10);
  ParaPanelLayout->addWidget(stepSlider);
  languageChange();
  resize(QSize(420, 275).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // tab order
  setTabOrder(spinBox1, individScalButton);
  setTabOrder(individScalButton, globalScalButton);
  setTabOrder(globalScalButton, stepSlider);

  // buddies
  frameRateLabel->setBuddy(spinBox1);
  schedModeLabel->setBuddy(individScalButton);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ParaPanel::~ParaPanel()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ParaPanel::languageChange()
{
  setCaption(tr("Form1"));
  paraLabel->setText(tr("Simulation Parameters"));
  frameRateLabel->setText(tr("Frame rate (k frames /sec)"));
  schedModeLabel->setText(tr("Scheduling Mode"));
  scalingButtonGroup->setTitle(QString::null);
  individScalButton->setText(tr("Individual Scaling"));
  globalScalButton->setText(tr("Global Scaling"));
  animModeLabel->setText(tr("Animation parameters"));
}
