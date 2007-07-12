// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/ParaPanel.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/07/12 15:48:15 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'ParaPanel.ui'
 **
 ** Created: Do Jul 12 17:42:39 2007
 **      by: The User Interface Compiler ($Id: ParaPanel.cpp,v 1.4 2007/07/12 15:48:15 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "ParaPanel.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qspinbox.h>
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
  ParaPanelLayout = new QGridLayout(this, 1, 1, 11, 6, "ParaPanelLayout");

  schedModeLabel = new QLabel(this, "schedModeLabel");

  ParaPanelLayout->addWidget(schedModeLabel, 2, 0);

  scalingButtonGroup = new QButtonGroup(this, "scalingButtonGroup");
  scalingButtonGroup->setColumnLayout(0, Qt::Vertical);
  scalingButtonGroup->layout()->setSpacing(6);
  scalingButtonGroup->layout()->setMargin(11);
  scalingButtonGroupLayout = new QVBoxLayout(scalingButtonGroup->layout());
  scalingButtonGroupLayout->setAlignment(Qt::AlignTop);

  individScalButton = new QRadioButton(scalingButtonGroup, "individScalButton");
  scalingButtonGroupLayout->addWidget(individScalButton);

  globalScalButton = new QRadioButton(scalingButtonGroup, "globalScalButton");
  scalingButtonGroupLayout->addWidget(globalScalButton);

  ParaPanelLayout->addWidget(scalingButtonGroup, 2, 1);

  frameRateLabel = new QLabel(this, "frameRateLabel");

  ParaPanelLayout->addWidget(frameRateLabel, 1, 0);

  spinBox1 = new QSpinBox(this, "spinBox1");

  ParaPanelLayout->addWidget(spinBox1, 1, 1);
  spacer1 = new QSpacerItem(20, 495, QSizePolicy::Minimum, QSizePolicy::Expanding);
  ParaPanelLayout->addItem(spacer1, 4, 0);

  paraLabel = new QLabel(this, "paraLabel");
  QFont paraLabel_font(paraLabel->font());
  paraLabel_font.setPointSize(12);
  paraLabel->setFont(paraLabel_font);

  ParaPanelLayout->addWidget(paraLabel, 0, 1);
  languageChange();
  resize(QSize(419, 304).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // tab order
  setTabOrder(spinBox1, individScalButton);
  setTabOrder(individScalButton, globalScalButton);

  // buddies
  schedModeLabel->setBuddy(individScalButton);
  frameRateLabel->setBuddy(spinBox1);
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
  schedModeLabel->setText(tr("<p align=\"right\">Scheduling Mode</p>"));
  scalingButtonGroup->setTitle(QString::null);
  individScalButton->setText(tr("Individual Scaling"));
  globalScalButton->setText(tr("Global Scaling"));
  frameRateLabel->setText(tr("<p align=\"right\">Frame rate (k frames /sec)</p>"));
  paraLabel->setText(tr("Simulation Parameters"));
}
