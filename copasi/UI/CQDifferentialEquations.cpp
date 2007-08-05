// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/05 10:00:19 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQDifferentialEquations.ui'
 **
 ** Created: So Aug 5 11:50:25 2007
 **      by: The User Interface Compiler ($Id: CQDifferentialEquations.cpp,v 1.1 2007/08/05 10:00:19 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQDifferentialEquations.h"

#include <qvariant.h>
#include <qscrollview.h>
#include <qpushbutton.h>
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
  spacer1 = new QSpacerItem(251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  CQDifferentialEquationsLayout->addItem(spacer1, 1, 0);

  mpSaveButton = new QPushButton(this, "mpSaveButton");

  CQDifferentialEquationsLayout->addWidget(mpSaveButton, 1, 1);

  mpScrollView = new QScrollView(this, "mpScrollView");

  CQDifferentialEquationsLayout->addMultiCellWidget(mpScrollView, 0, 0, 0, 1);
  languageChange();
  resize(QSize(600, 480).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpSaveButton, SIGNAL(clicked()), this, SLOT(slotSaveMML()));
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
  mpSaveButton->setText(tr("Save MathML to disk"));
}
