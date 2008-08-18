// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMatrixDialog.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/08/18 09:08:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMatrixDialog.ui'
 **
 ** Created: Fri Aug 8 13:10:01 2008
 **      by: The User Interface Compiler ($Id: CQMatrixDialog.cpp,v 1.2 2008/08/18 09:08:58 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQMatrixDialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "utilities/CAnnotatedMatrix.h"
#include "CQMatrixDialog.ui.h"

/*
 *  Constructs a CQMatrixDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CQMatrixDialog::CQMatrixDialog(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("CQMatrixDialog");
  CQMatrixDialogLayout = new QVBoxLayout(this, 11, 6, "CQMatrixDialogLayout");

  mpLabelRow = new QLabel(this, "mpLabelRow");
  CQMatrixDialogLayout->addWidget(mpLabelRow);

  mpCBRow = new QComboBox(FALSE, this, "mpCBRow");
  CQMatrixDialogLayout->addWidget(mpCBRow);

  mpLabelColumn = new QLabel(this, "mpLabelColumn");
  CQMatrixDialogLayout->addWidget(mpLabelColumn);

  mpCBColumn = new QComboBox(FALSE, this, "mpCBColumn");
  CQMatrixDialogLayout->addWidget(mpCBColumn);

  mpLabelDim3 = new QLabel(this, "mpLabelDim3");
  CQMatrixDialogLayout->addWidget(mpLabelDim3);

  mpCBDim3 = new QComboBox(FALSE, this, "mpCBDim3");
  CQMatrixDialogLayout->addWidget(mpCBDim3);
  spacer1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQMatrixDialogLayout->addItem(spacer1);

  line1 = new QFrame(this, "line1");
  line1->setFrameShape(QFrame::HLine);
  line1->setFrameShadow(QFrame::Sunken);
  line1->setFrameShape(QFrame::HLine);
  CQMatrixDialogLayout->addWidget(line1);

  layout1 = new QHBoxLayout(0, 0, 6, "layout1");

  mpOKBtn = new QPushButton(this, "mpOKBtn");
  layout1->addWidget(mpOKBtn);

  mpCancelBtn = new QPushButton(this, "mpCancelBtn");
  layout1->addWidget(mpCancelBtn);
  CQMatrixDialogLayout->addLayout(layout1);
  languageChange();
  resize(QSize(425, 211).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpOKBtn, SIGNAL(clicked()), this, SLOT(accept()));
  connect(mpCancelBtn, SIGNAL(clicked()), this, SLOT(close()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMatrixDialog::~CQMatrixDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMatrixDialog::languageChange()
{
  setCaption(tr("Cell Matrix Selection Dialog"));
  mpLabelRow->setText(tr("Row :"));
  mpLabelColumn->setText(tr("Column :"));
  mpLabelDim3->setText(tr("Dimension 3 :"));
  mpOKBtn->setText(tr("OK"));
  mpCancelBtn->setText(tr("Cancel"));
}
