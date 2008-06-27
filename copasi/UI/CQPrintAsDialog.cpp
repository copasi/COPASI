// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQPrintAsDialog.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/27 12:02:43 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQPrintAsDialog.ui'
 **
 ** Created: Thu Jun 26 14:26:46 2008
 **      by: The User Interface Compiler ($Id: CQPrintAsDialog.cpp,v 1.1 2008/06/27 12:02:43 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQPrintAsDialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a CQPrintAsDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CQPrintAsDialog::CQPrintAsDialog(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("CQPrintAsDialog");
  CQPrintAsDialogLayout = new QVBoxLayout(this, 11, 6, "CQPrintAsDialogLayout");

  mpFrame = new QFrame(this, "mpFrame");
  mpFrame->setFrameShape(QFrame::Box);
  mpFrame->setFrameShadow(QFrame::Sunken);
  mpFrameLayout = new QGridLayout(mpFrame, 1, 1, 11, 6, "mpFrameLayout");

  mpLabelType = new QLabel(mpFrame, "mpLabelType");

  mpFrameLayout->addWidget(mpLabelType, 1, 0);

  layout3 = new QHBoxLayout(0, 0, 6, "layout3");

  mpEditFileName = new QLineEdit(mpFrame, "mpEditFileName");
  layout3->addWidget(mpEditFileName);

  mpBtnBrowse = new QPushButton(mpFrame, "mpBtnBrowse");
  layout3->addWidget(mpBtnBrowse);

  mpFrameLayout->addLayout(layout3, 0, 1);

  mpLabelFileName = new QLabel(mpFrame, "mpLabelFileName");

  mpFrameLayout->addWidget(mpLabelFileName, 0, 0);

  layout5 = new QHBoxLayout(0, 0, 6, "layout5");

  mpCBPNG = new QCheckBox(mpFrame, "mpCBPNG");
  layout5->addWidget(mpCBPNG);

  mpCBSVG = new QCheckBox(mpFrame, "mpCBSVG");
  layout5->addWidget(mpCBSVG);
  spacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout5->addItem(spacer3);

  mpFrameLayout->addLayout(layout5, 1, 1);
  CQPrintAsDialogLayout->addWidget(mpFrame);

  layout6 = new QHBoxLayout(0, 0, 6, "layout6");

  mpBtnConfirm = new QPushButton(this, "mpBtnConfirm");
  layout6->addWidget(mpBtnConfirm);

  mpBtnCancel = new QPushButton(this, "mpBtnCancel");
  layout6->addWidget(mpBtnCancel);
  CQPrintAsDialogLayout->addLayout(layout6);
  languageChange();
  resize(QSize(562, 159).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnConfirm, SIGNAL(clicked()), this, SLOT(accept()));
  connect(mpBtnCancel, SIGNAL(clicked()), this, SLOT(reject()));
  connect(mpBtnBrowse, SIGNAL(clicked()), this, SLOT(openFileDialog()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQPrintAsDialog::~CQPrintAsDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQPrintAsDialog::languageChange()
{
  setCaption(tr("Print As Image"));
  mpLabelType->setText(tr("as type of:"));
  mpBtnBrowse->setText(tr("browse"));
  mpLabelFileName->setText(tr("File Name:"));
  mpCBPNG->setText(tr("png"));
  mpCBSVG->setText(tr("svg"));
  mpBtnConfirm->setText(tr("Confirm"));
  mpBtnCancel->setText(tr("Cancel"));
}

void CQPrintAsDialog::openFileDialog()
{
  qWarning("CQPrintAsDialog::openFileDialog(): Not implemented yet");
}
