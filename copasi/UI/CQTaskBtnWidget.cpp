// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskBtnWidget.cpp,v $
//   $Revision: 1.5.8.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/06 16:23:47 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTaskBtnWidget.ui'
 **
 ** Created: Tue Feb 6 11:11:40 2007
 **      by: The User Interface Compiler ($Id: CQTaskBtnWidget.cpp,v 1.5.8.1 2007/02/06 16:23:47 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQTaskBtnWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a CQTaskBtnWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTaskBtnWidget::CQTaskBtnWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CQTaskBtnWidget");
  CQTaskBtnWidgetLayout = new QVBoxLayout(this, 0, 6, "CQTaskBtnWidgetLayout");
  mpSpacerVertical = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Preferred);
  CQTaskBtnWidgetLayout->addItem(mpSpacerVertical);

  mpBtnLayout = new QHBoxLayout(0, 0, 6, "mpBtnLayout");

  mpBtnRun = new QPushButton(this, "mpBtnRun");
  mpBtnLayout->addWidget(mpBtnRun);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");
  mpBtnLayout->addWidget(mpBtnRevert);
  mpSpacerHorizontal = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpBtnLayout->addItem(mpSpacerHorizontal);

  mpBtnReport = new QPushButton(this, "mpBtnReport");
  mpBtnLayout->addWidget(mpBtnReport);

  mpBtnAssistant = new QPushButton(this, "mpBtnAssistant");
  mpBtnLayout->addWidget(mpBtnAssistant);
  CQTaskBtnWidgetLayout->addLayout(mpBtnLayout);
  languageChange();
  resize(QSize(372, 35).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // tab order
  setTabOrder(mpBtnRun, mpBtnRevert);
  setTabOrder(mpBtnRevert, mpBtnReport);
  setTabOrder(mpBtnReport, mpBtnAssistant);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTaskBtnWidget::~CQTaskBtnWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQTaskBtnWidget::languageChange()
{
  setCaption(tr("CQTaskBtnWidget"));
  mpBtnRun->setText(tr("Run"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnReport->setText(tr("Report"));
  mpBtnAssistant->setText(tr("Output Assistant"));
}
