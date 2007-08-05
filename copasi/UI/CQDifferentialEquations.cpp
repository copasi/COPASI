// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/05 12:24:53 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQDifferentialEquations.ui'
 **
 ** Created: So Aug 5 14:22:48 2007
 **      by: The User Interface Compiler ($Id: CQDifferentialEquations.cpp,v 1.2 2007/08/05 12:24:53 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQDifferentialEquations.h"

#include <qvariant.h>
#include <qscrollview.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "copasiWidget.h"
#include "CQDifferentialEquations.ui.h"

/*
 *  Constructs a CQDifferentialEquations which is a child of 'parent', with the
 *  name 'name'.'
 */
CQDifferentialEquations::CQDifferentialEquations(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("CQDifferentialEquations");
  CQDifferentialEquationsLayout = new QGridLayout(this, 1, 1, 11, 6, "CQDifferentialEquationsLayout");

  mpScrollView = new QScrollView(this, "mpScrollView");

  CQDifferentialEquationsLayout->addMultiCellWidget(mpScrollView, 0, 0, 0, 2);

  textLabelParameters = new QLabel(this, "textLabelParameters");
  textLabelParameters->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQDifferentialEquationsLayout->addWidget(textLabelParameters, 1, 0);

  textLabelFunctions = new QLabel(this, "textLabelFunctions");
  textLabelFunctions->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQDifferentialEquationsLayout->addWidget(textLabelFunctions, 2, 0);

  layout1 = new QHBoxLayout(0, 0, 6, "layout1");

  comboBoxParameters = new QComboBox(FALSE, this, "comboBoxParameters");
  layout1->addWidget(comboBoxParameters);
  spacer1_2 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout1->addItem(spacer1_2);

  CQDifferentialEquationsLayout->addLayout(layout1, 1, 1);

  layout2 = new QHBoxLayout(0, 0, 6, "layout2");

  comboBoxFunctions = new QComboBox(FALSE, this, "comboBoxFunctions");
  layout2->addWidget(comboBoxFunctions);
  spacer1 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout2->addItem(spacer1);

  CQDifferentialEquationsLayout->addLayout(layout2, 2, 1);

  layout3 = new QVBoxLayout(0, 0, 6, "layout3");

  mpSaveButton = new QPushButton(this, "mpSaveButton");
  layout3->addWidget(mpSaveButton);
  spacer3 = new QSpacerItem(20, 71, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout3->addItem(spacer3);

  CQDifferentialEquationsLayout->addMultiCellLayout(layout3, 1, 2, 2, 2);
  languageChange();
  resize(QSize(673, 573).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpSaveButton, SIGNAL(clicked()), this, SLOT(slotSaveMML()));
  connect(comboBoxParameters, SIGNAL(activated(int)), this, SLOT(slotUpdateWidget()));
  connect(comboBoxFunctions, SIGNAL(activated(int)), this, SLOT(slotUpdateWidget()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQDifferentialEquations::~CQDifferentialEquations()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQDifferentialEquations::languageChange()
{
  setCaption(tr("Form1"));
  textLabelParameters->setText(tr("local parameters"));
  textLabelFunctions->setText(tr("functions"));
  comboBoxParameters->clear();
  comboBoxParameters->insertItem(tr("display numerical value"));
  comboBoxParameters->insertItem(tr("display name"));
  comboBoxFunctions->clear();
  comboBoxFunctions->insertItem(tr("display name"));
  comboBoxFunctions->insertItem(tr("expand only kinetic functions"));
  comboBoxFunctions->insertItem(tr("expand all functions"));
  mpSaveButton->setText(tr("Save MathML to disk"));
}
