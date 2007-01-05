/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQRegistrationDialog.cpp,v $
   $Revision: 1.1.2.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2007/01/05 15:37:16 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQRegistrationDialog.ui'
 **
 ** Created: Fri Dec 15 16:15:34 2006
 **      by: The User Interface Compiler ($Id: CQRegistrationDialog.cpp,v 1.1.2.1 2007/01/05 15:37:16 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQRegistrationDialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQRegistrationDialog.ui.h"

/*
 *  Constructs a CQRegistrationDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CQRegistrationDialog::CQRegistrationDialog(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("CQRegistrationDialog");
  setSizeGripEnabled(TRUE);
  CQRegistrationDialogLayout = new QVBoxLayout(this, 11, 6, "CQRegistrationDialogLayout");

  mpLayoutValues = new QGridLayout(0, 1, 1, 0, 6, "mpLayoutValues");

  mpLblDate = new QLabel(this, "mpLblDate");
  mpLblDate->setEnabled(TRUE);
  mpLblDate->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpLayoutValues->addWidget(mpLblDate, 5, 0);

  mpLblEmail = new QLabel(this, "mpLblEmail");
  mpLblEmail->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpLayoutValues->addWidget(mpLblEmail, 1, 0);

  mpEditName = new QLineEdit(this, "mpEditName");

  mpLayoutValues->addWidget(mpEditName, 0, 1);

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpLayoutValues->addWidget(mpLblName, 0, 0);

  mpLblCode = new QLabel(this, "mpLblCode");
  mpLblCode->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpLayoutValues->addWidget(mpLblCode, 2, 0);

  mpEditStatus = new QLineEdit(this, "mpEditStatus");
  mpEditStatus->setEnabled(FALSE);

  mpLayoutValues->addWidget(mpEditStatus, 4, 1);

  mpLine = new QFrame(this, "mpLine");
  mpLine->setFrameShape(QFrame::HLine);
  mpLine->setFrameShadow(QFrame::Sunken);
  mpLine->setFrameShape(QFrame::HLine);

  mpLayoutValues->addMultiCellWidget(mpLine, 3, 3, 0, 1);

  mpEditEmail = new QLineEdit(this, "mpEditEmail");

  mpLayoutValues->addWidget(mpEditEmail, 1, 1);

  mpEditDate = new QLineEdit(this, "mpEditDate");
  mpEditDate->setEnabled(FALSE);

  mpLayoutValues->addWidget(mpEditDate, 5, 1);

  mpEditCode = new QLineEdit(this, "mpEditCode");

  mpLayoutValues->addWidget(mpEditCode, 2, 1);

  mpLblStatus = new QLabel(this, "mpLblStatus");
  mpLblStatus->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpLayoutValues->addWidget(mpLblStatus, 4, 0);
  CQRegistrationDialogLayout->addLayout(mpLayoutValues);
  mpSpacerVertical = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQRegistrationDialogLayout->addItem(mpSpacerVertical);

  mpLayoutBtn = new QHBoxLayout(0, 0, 6, "mpLayoutBtn");

  mpBtnValidate = new QPushButton(this, "mpBtnValidate");
  mpBtnValidate->setAutoDefault(TRUE);
  mpLayoutBtn->addWidget(mpBtnValidate);
  mpSpacerBtn = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpLayoutBtn->addItem(mpSpacerBtn);

  mpBtnOk = new QPushButton(this, "mpBtnOk");
  mpBtnOk->setAutoDefault(TRUE);
  mpBtnOk->setDefault(TRUE);
  mpLayoutBtn->addWidget(mpBtnOk);

  mpBtnCancel = new QPushButton(this, "mpBtnCancel");
  mpBtnCancel->setAutoDefault(TRUE);
  mpLayoutBtn->addWidget(mpBtnCancel);
  CQRegistrationDialogLayout->addLayout(mpLayoutBtn);
  languageChange();
  resize(QSize(514, 253).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnOk, SIGNAL(clicked()), this, SLOT(slotBtnOk()));
  connect(mpBtnCancel, SIGNAL(clicked()), this, SLOT(slotBtnCancel()));
  connect(mpBtnValidate, SIGNAL(clicked()), this, SLOT(slotBtnValidate()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQRegistrationDialog::~CQRegistrationDialog()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQRegistrationDialog::languageChange()
{
  setCaption(tr("Registration"));
  mpLblDate->setText(tr("Expiration Date"));
  mpLblEmail->setText(tr("Email"));
  mpLblName->setText(tr("User Name"));
  mpLblCode->setText(tr("Registration Code"));
  mpLblStatus->setText(tr("License Status"));
  mpBtnValidate->setText(tr("Validate"));
  mpBtnValidate->setAccel(QKeySequence(QString::null));
  mpBtnOk->setText(tr("&OK"));
  mpBtnOk->setAccel(QKeySequence(QString::null));
  mpBtnCancel->setText(tr("&Cancel"));
  mpBtnCancel->setAccel(QKeySequence(QString::null));
}
