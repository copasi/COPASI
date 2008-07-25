// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/07/25 06:30:01 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQDifferentialEquations.ui'
 **
 ** Created: Wed Jul 23 14:04:51 2008
 **      by: The User Interface Compiler ($Id: CQDifferentialEquations.cpp,v 1.3 2008/07/25 06:30:01 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQDifferentialEquations.h"

#include <qvariant.h>
#include <qscrollview.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "qscrollview.h"
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
  CQDifferentialEquationsLayout = new QVBoxLayout(this, 11, 6, "CQDifferentialEquationsLayout");

  mpScrollView = new QScrollView(this, "mpScrollView");
  mpScrollView->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 194, mpScrollView->sizePolicy().hasHeightForWidth()));
  CQDifferentialEquationsLayout->addWidget(mpScrollView);

  layout9 = new QGridLayout(0, 1, 1, 0, 6, "layout9");

  mpSaveButton = new QPushButton(this, "mpSaveButton");

  layout9->addWidget(mpSaveButton, 0, 4);
  spacer1_2 = new QSpacerItem(242, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout9->addMultiCell(spacer1_2, 0, 0, 2, 3);

  comboBoxFunctions = new QComboBox(FALSE, this, "comboBoxFunctions");

  layout9->addMultiCellWidget(comboBoxFunctions, 1, 1, 1, 2);

  comboBoxParameters = new QComboBox(FALSE, this, "comboBoxParameters");

  layout9->addWidget(comboBoxParameters, 0, 1);

  textLabelParameters = new QLabel(this, "textLabelParameters");
  textLabelParameters->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout9->addWidget(textLabelParameters, 0, 0);
  spacer1 = new QSpacerItem(212, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout9->addItem(spacer1, 1, 3);

  textLabelFunctions = new QLabel(this, "textLabelFunctions");
  textLabelFunctions->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout9->addWidget(textLabelFunctions, 1, 0);
  CQDifferentialEquationsLayout->addLayout(layout9);
  languageChange();
  resize(QSize(673, 573).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpSaveButton, SIGNAL(clicked()), this, SLOT(slotSave()));
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
  mpSaveButton->setText(tr("Save Formula to Disk"));
  comboBoxFunctions->clear();
  comboBoxFunctions->insertItem(tr("display name"));
  comboBoxFunctions->insertItem(tr("expand only kinetic functions"));
  comboBoxFunctions->insertItem(tr("expand all functions"));
  comboBoxParameters->clear();
  comboBoxParameters->insertItem(tr("display numerical value"));
  comboBoxParameters->insertItem(tr("display name"));
  textLabelParameters->setText(tr("local parameters"));
  textLabelFunctions->setText(tr("functions"));
}
