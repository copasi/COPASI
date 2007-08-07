// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/Attic/CQCopasiLayoutWidget.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/07 15:35:41 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQCopasiLayoutWidget.ui'
 **
 ** Created: Di Aug 7 17:31:11 2007
 **      by: The User Interface Compiler ($Id: CQCopasiLayoutWidget.cpp,v 1.3 2007/08/07 15:35:41 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQCopasiLayoutWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "UI/copasiWidget.h"
#include "CQCopasiLayoutWidget.ui.h"

/*
 *  Constructs a CQCopasiLayoutWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCopasiLayoutWidget::CQCopasiLayoutWidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("CQCopasiLayoutWidget");
  CQCopasiLayoutWidgetLayout = new QVBoxLayout(this, 11, 6, "CQCopasiLayoutWidgetLayout");
  spacer4 = new QSpacerItem(20, 61, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQCopasiLayoutWidgetLayout->addItem(spacer4);

  mpShowLayoutOld = new QPushButton(this, "mpShowLayoutOld");
  CQCopasiLayoutWidgetLayout->addWidget(mpShowLayoutOld);
  languageChange();
  resize(QSize(673, 573).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpShowLayoutOld, SIGNAL(clicked()), this, SLOT(displayNetworkWidgetOld()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQCopasiLayoutWidget::~CQCopasiLayoutWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQCopasiLayoutWidget::languageChange()
{
  setCaption(tr("Form1"));
  mpShowLayoutOld->setText(tr("Show Layout"));
}
