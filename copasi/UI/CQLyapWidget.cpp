// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLyapWidget.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/12 14:29:14 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQLyapWidget.ui'
 **
 ** Created: Tue Feb 6 16:19:24 2007
 **      by: The User Interface Compiler ($Id: CQLyapWidget.cpp,v 1.6 2007/02/12 14:29:14 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQLyapWidget.h"

#include <qvariant.h>
#include <qframe.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQLyapWidget.ui.h"

/*
 *  Constructs a CQLyapWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQLyapWidget::CQLyapWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  if (!name)
    setName("CQLyapWidget");
  CQLyapWidgetLayout = new QVBoxLayout(this, 11, 6, "CQLyapWidgetLayout");

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpLine = new QFrame(this, "mpLine");
  mpLine->setFrameShape(QFrame::HLine);
  mpLine->setFrameShadow(QFrame::Sunken);
  mpLine->setFrameShape(QFrame::HLine);

  mpGridLayout->addMultiCellWidget(mpLine, 3, 3, 0, 1);

  mpLayoutDelay = new QHBoxLayout(0, 0, 0, "mpLayoutDelay");

  mpCheckDelay = new QCheckBox(this, "mpCheckDelay");
  mpLayoutDelay->addWidget(mpCheckDelay);

  mpEditDelay = new QLineEdit(this, "mpEditDelay");
  mpLayoutDelay->addWidget(mpEditDelay);

  mpGridLayout->addLayout(mpLayoutDelay, 1, 1);

  mpEditExponent = new QLineEdit(this, "mpEditExponent");
  mpEditExponent->setFrameShape(QLineEdit::LineEditPanel);
  mpEditExponent->setFrameShadow(QLineEdit::Sunken);

  mpGridLayout->addWidget(mpEditExponent, 0, 1);

  mpCheckDivergence = new QCheckBox(this, "mpCheckDivergence");

  mpGridLayout->addWidget(mpCheckDivergence, 2, 1);

  mpLblExponents = new QLabel(this, "mpLblExponents");
  mpLblExponents->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblExponents, 0, 0);
  CQLyapWidgetLayout->addLayout(mpGridLayout);
  languageChange();
  resize(QSize(292, 106).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpCheckDelay, SIGNAL(clicked()), this, SLOT(slotDelayChecked()));

  // tab order
  setTabOrder(mpEditExponent, mpCheckDelay);
  setTabOrder(mpCheckDelay, mpEditDelay);
  setTabOrder(mpEditDelay, mpCheckDivergence);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQLyapWidget::~CQLyapWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQLyapWidget::languageChange()
{
  setCaption(tr("CQLyapWidget"));
  mpCheckDelay->setText(tr("start averaging after t ="));
  mpCheckDivergence->setText(tr("calculate Divergence"));
  mpLblExponents->setText(tr("Number of Exponents"));
}
