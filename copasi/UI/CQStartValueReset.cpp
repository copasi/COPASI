/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQStartValueReset.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/18 16:33:59 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQStartValueReset.ui'
 **
 ** Created: Fri Aug 18 12:29:47 2006
 **      by: The User Interface Compiler ($Id: CQStartValueReset.cpp,v 1.1 2006/08/18 16:33:59 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQStartValueReset.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQStartValueReset.ui.h"

/*
 *  Constructs a CQStartValueReset as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CQStartValueReset::CQStartValueReset(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("CQStartValueReset");
  setSizeGripEnabled(TRUE);
  CQStartValueResetLayout = new QVBoxLayout(this, 11, 6, "CQStartValueResetLayout");

  mpBtnModel = new QPushButton(this, "mpBtnModel");
  mpBtnModel->setAutoDefault(TRUE);
  mpBtnModel->setDefault(TRUE);
  CQStartValueResetLayout->addWidget(mpBtnModel);

  mpBtnSolution = new QPushButton(this, "mpBtnSolution");
  mpBtnSolution->setAutoDefault(TRUE);
  CQStartValueResetLayout->addWidget(mpBtnSolution);

  mpBtnRandom = new QPushButton(this, "mpBtnRandom");
  mpBtnRandom->setAutoDefault(TRUE);
  CQStartValueResetLayout->addWidget(mpBtnRandom);

  mpBtnCancel = new QPushButton(this, "mpBtnCancel");
  mpBtnCancel->setAutoDefault(TRUE);
  CQStartValueResetLayout->addWidget(mpBtnCancel);
  mpSpace = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQStartValueResetLayout->addItem(mpSpace);
  languageChange();
  resize(QSize(120, 151).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnCancel, SIGNAL(clicked()), this, SLOT(reject()));
  connect(mpBtnRandom, SIGNAL(clicked()), this, SLOT(slotRandom()));
  connect(mpBtnModel, SIGNAL(clicked()), this, SLOT(slotModel()));
  connect(mpBtnSolution, SIGNAL(clicked()), this, SLOT(slotSolution()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQStartValueReset::~CQStartValueReset()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQStartValueReset::languageChange()
{
  setCaption(tr("Start Value Reset"));
  mpBtnModel->setText(tr("Model Value"));
  mpBtnModel->setAccel(QKeySequence(QString::null));
  mpBtnSolution->setText(tr("Current Solution"));
  mpBtnSolution->setAccel(QKeySequence(QString::null));
  mpBtnRandom->setText(tr("Random"));
  mpBtnRandom->setAccel(QKeySequence(QString::null));
  mpBtnCancel->setText(tr("Cancel"));
  mpBtnCancel->setAccel(QKeySequence(QString::null));
}
