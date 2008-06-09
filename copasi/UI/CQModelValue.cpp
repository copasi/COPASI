// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.cpp,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/09 06:03:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQModelValue.ui'
 **
 ** Created: Mon Apr 21 11:35:10 2008
 **      by: The User Interface Compiler ($Id: CQModelValue.cpp,v 1.11 2008/06/09 06:03:27 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQModelValue.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQExpressionMmlWidget.h"
#include "CQExpressionWidget.h"
#include "CQModelValue.ui.h"

/*
 *  Constructs a CQModelValue which is a child of 'parent', with the
 *  name 'name'.'
 */
CQModelValue::CQModelValue(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("CQModelValue");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  CQModelValueLayout = new QGridLayout(this, 1, 1, 11, 6, "CQModelValueLayout");

  mpBtnLayout = new QHBoxLayout(0, 0, 6, "mpBtnLayout");

  mpBtnCommit = new QPushButton(this, "mpBtnCommit");
  mpBtnLayout->addWidget(mpBtnCommit);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");
  mpBtnLayout->addWidget(mpBtnRevert);

  mpBtnNew = new QPushButton(this, "mpBtnNew");
  mpBtnLayout->addWidget(mpBtnNew);

  mpBtnDelete = new QPushButton(this, "mpBtnDelete");
  mpBtnLayout->addWidget(mpBtnDelete);

  CQModelValueLayout->addMultiCellLayout(mpBtnLayout, 10, 10, 0, 2);

  mpComboBoxType = new QComboBox(FALSE, this, "mpComboBoxType");
  mpComboBoxType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxType->sizePolicy().hasHeightForWidth()));

  CQModelValueLayout->addWidget(mpComboBoxType, 1, 1);

  mpEditName = new QLineEdit(this, "mpEditName");
  mpEditName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpEditName->sizePolicy().hasHeightForWidth()));
  mpEditName->setFrameShape(QLineEdit::LineEditPanel);
  mpEditName->setFrameShadow(QLineEdit::Sunken);

  CQModelValueLayout->addMultiCellWidget(mpEditName, 0, 0, 1, 2);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQModelValueLayout->addWidget(mpLblType, 1, 0);

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblName->sizePolicy().hasHeightForWidth()));
  mpLblName->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQModelValueLayout->addWidget(mpLblName, 0, 0);

  mpLblRate = new QLabel(this, "mpLblRate");
  mpLblRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblRate->sizePolicy().hasHeightForWidth()));
  mpLblRate->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQModelValueLayout->addMultiCellWidget(mpLblRate, 7, 8, 0, 0);

  mpLblValue = new QLabel(this, "mpLblValue");
  mpLblValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblValue->sizePolicy().hasHeightForWidth()));
  mpLblValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQModelValueLayout->addWidget(mpLblValue, 6, 0);

  mpEditCurrentValue = new QLineEdit(this, "mpEditCurrentValue");
  mpEditCurrentValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditCurrentValue->sizePolicy().hasHeightForWidth()));
  mpEditCurrentValue->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentValue->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentValue->setReadOnly(TRUE);

  CQModelValueLayout->addWidget(mpEditCurrentValue, 6, 1);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQModelValueLayout->addWidget(mpLblExpression, 2, 0);

  mpLblInitialValue = new QLabel(this, "mpLblInitialValue");
  mpLblInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblInitialValue->sizePolicy().hasHeightForWidth()));
  mpLblInitialValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQModelValueLayout->addWidget(mpLblInitialValue, 3, 0);

  mpEditInitialValue = new QLineEdit(this, "mpEditInitialValue");
  mpEditInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialValue->sizePolicy().hasHeightForWidth()));
  mpEditInitialValue->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialValue->setFrameShadow(QLineEdit::Sunken);

  CQModelValueLayout->addWidget(mpEditInitialValue, 3, 1);

  mpBoxUseInitialExpression = new QCheckBox(this, "mpBoxUseInitialExpression");

  CQModelValueLayout->addWidget(mpBoxUseInitialExpression, 3, 2);

  mpLblInitialExpression = new QLabel(this, "mpLblInitialExpression");
  mpLblInitialExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblInitialExpression->sizePolicy().hasHeightForWidth()));
  mpLblInitialExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQModelValueLayout->addWidget(mpLblInitialExpression, 4, 0);

  mpLine1 = new QFrame(this, "mpLine1");
  mpLine1->setFrameShape(QFrame::HLine);
  mpLine1->setFrameShadow(QFrame::Sunken);
  mpLine1->setFrameShape(QFrame::HLine);

  CQModelValueLayout->addMultiCellWidget(mpLine1, 5, 5, 0, 2);

  mpEditRate = new QLineEdit(this, "mpEditRate");
  mpEditRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditRate->sizePolicy().hasHeightForWidth()));
  mpEditRate->setFrameShape(QLineEdit::LineEditPanel);
  mpEditRate->setFrameShadow(QLineEdit::Sunken);
  mpEditRate->setReadOnly(TRUE);

  CQModelValueLayout->addWidget(mpEditRate, 7, 1);
  mpSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQModelValueLayout->addItem(mpSpacer, 8, 1);

  mpLine2 = new QFrame(this, "mpLine2");
  mpLine2->setFrameShape(QFrame::HLine);
  mpLine2->setFrameShadow(QFrame::Sunken);
  mpLine2->setFrameShape(QFrame::HLine);

  CQModelValueLayout->addMultiCellWidget(mpLine2, 9, 9, 0, 2);

  mpInitialExpressionEMW = new CQExpressionMmlWidget(this, "mpInitialExpressionEMW");
  mpInitialExpressionEMW->setMinimumSize(QSize(310, 60));

  CQModelValueLayout->addMultiCellWidget(mpInitialExpressionEMW, 4, 4, 1, 2);

  mpExpressionEMW = new CQExpressionMmlWidget(this, "mpExpressionEMW");
  mpExpressionEMW->setMinimumSize(QSize(310, 60));

  CQModelValueLayout->addMultiCellWidget(mpExpressionEMW, 2, 2, 1, 2);
  languageChange();
  resize(QSize(476, 364).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnCommit, SIGNAL(clicked()), this, SLOT(slotBtnCommit()));
  connect(mpBtnDelete, SIGNAL(clicked()), this, SLOT(slotBtnDelete()));
  connect(mpBtnNew, SIGNAL(clicked()), this, SLOT(slotBtnNew()));
  connect(mpBtnRevert, SIGNAL(clicked()), this, SLOT(slotBtnRevert()));
  connect(mpComboBoxType, SIGNAL(activated(int)), this, SLOT(slotTypeChanged(int)));
  connect(mpBoxUseInitialExpression, SIGNAL(toggled(bool)), this, SLOT(slotInitialTypeChanged(bool)));
  connect(mpEditName, SIGNAL(lostFocus()), this, SLOT(slotNameLostFocus()));

  // tab order
  setTabOrder(mpEditName, mpComboBoxType);
  setTabOrder(mpComboBoxType, mpEditInitialValue);
  setTabOrder(mpEditInitialValue, mpBoxUseInitialExpression);
  setTabOrder(mpBoxUseInitialExpression, mpEditCurrentValue);
  setTabOrder(mpEditCurrentValue, mpEditRate);
  setTabOrder(mpEditRate, mpBtnCommit);
  setTabOrder(mpBtnCommit, mpBtnRevert);
  setTabOrder(mpBtnRevert, mpBtnNew);
  setTabOrder(mpBtnNew, mpBtnDelete);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQModelValue::~CQModelValue()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQModelValue::languageChange()
{
  setCaption(tr("Global Quantity"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
  mpLblType->setText(tr("Simulation Type"));
  mpLblName->setText(tr("Global Quantity Name"));
  mpLblRate->setText(tr("Rate"));
  mpLblValue->setText(tr("Value"));
  mpLblExpression->setText(tr("Expression"));
  mpLblInitialValue->setText(tr("Initial Value"));
  mpBoxUseInitialExpression->setText(tr("Use Initial Expression"));
  mpLblInitialExpression->setText(tr("Initial Expression"));
}
