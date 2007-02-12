// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMCAWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/12 14:29:14 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMCAWidget.ui'
 **
 ** Created: Wed Feb 7 15:19:58 2007
 **      by: The User Interface Compiler ($Id: CQMCAWidget.cpp,v 1.2 2007/02/12 14:29:14 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQMCAWidget.h"

#include <qvariant.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQMCAWidget.ui.h"

/*
 *  Constructs a CQMCAWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMCAWidget::CQMCAWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  if (!name)
    setName("CQMCAWidget");
  CQMCAWidgetLayout = new QVBoxLayout(this, 11, 6, "CQMCAWidgetLayout");

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");
  mpSacer = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
  mpGridLayout->addItem(mpSacer, 0, 0);

  mpCheckSteadyState = new QCheckBox(this, "mpCheckSteadyState");

  mpGridLayout->addWidget(mpCheckSteadyState, 0, 1);

  mpLine = new QFrame(this, "mpLine");
  mpLine->setFrameShape(QFrame::HLine);
  mpLine->setFrameShadow(QFrame::Sunken);
  mpLine->setFrameShape(QFrame::HLine);

  mpGridLayout->addMultiCellWidget(mpLine, 1, 1, 0, 1);
  CQMCAWidgetLayout->addLayout(mpGridLayout);
  languageChange();
  resize(QSize(293, 53).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpCheckSteadyState, SIGNAL(clicked()), this, SLOT(slotSteadyStateChecked()));

  // tab order
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMCAWidget::~CQMCAWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMCAWidget::languageChange()
{
  setCaption(tr("CQMCAWidget"));
  mpCheckSteadyState->setText(tr("perform Steady State Analysis"));
}
