// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.cpp,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/04/18 08:38:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Fri Apr 18 09:45:37 2008
 **      by: The User Interface Compiler ($Id: CQMetabolite.cpp,v 1.14 2008/04/18 08:38:30 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQMetabolite.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qcheckbox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQExpressionMmlWidget.h"
#include "CQExpressionWidget.h"
#include "CQMetabolite.ui.h"

/*
 *  Constructs a CQMetabolite which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMetabolite::CQMetabolite(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("CQMetabolite");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  CQMetaboliteLayout = new QGridLayout(this, 1, 1, 11, 6, "CQMetaboliteLayout");

  mpBtnLayout = new QHBoxLayout(0, 0, 6, "mpBtnLayout");

  mpBtnCommit = new QPushButton(this, "mpBtnCommit");
  mpBtnLayout->addWidget(mpBtnCommit);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");
  mpBtnLayout->addWidget(mpBtnRevert);

  mpBtnNew = new QPushButton(this, "mpBtnNew");
  mpBtnLayout->addWidget(mpBtnNew);

  mpBtnDelete = new QPushButton(this, "mpBtnDelete");
  mpBtnLayout->addWidget(mpBtnDelete);

  CQMetaboliteLayout->addMultiCellLayout(mpBtnLayout, 13, 13, 0, 2);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblType, 2, 0);

  mpEditName = new QLineEdit(this, "mpEditName");
  mpEditName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpEditName->sizePolicy().hasHeightForWidth()));
  mpEditName->setFrameShape(QLineEdit::LineEditPanel);
  mpEditName->setFrameShadow(QLineEdit::Sunken);

  CQMetaboliteLayout->addMultiCellWidget(mpEditName, 0, 0, 1, 2);

  mpComboBoxCompartment = new QComboBox(FALSE, this, "mpComboBoxCompartment");
  mpComboBoxCompartment->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxCompartment->sizePolicy().hasHeightForWidth()));

  CQMetaboliteLayout->addMultiCellWidget(mpComboBoxCompartment, 1, 1, 1, 2);

  mpComboBoxType = new QComboBox(FALSE, this, "mpComboBoxType");
  mpComboBoxType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxType->sizePolicy().hasHeightForWidth()));

  CQMetaboliteLayout->addWidget(mpComboBoxType, 2, 1);

  mpLblCompartment = new QLabel(this, "mpLblCompartment");
  mpLblCompartment->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblCompartment->sizePolicy().hasHeightForWidth()));
  mpLblCompartment->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblCompartment, 1, 0);

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblName->sizePolicy().hasHeightForWidth()));
  mpLblName->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblName, 0, 0);

  mpLine1 = new QFrame(this, "mpLine1");
  mpLine1->setFrameShape(QFrame::HLine);
  mpLine1->setFrameShadow(QFrame::Sunken);
  mpLine1->setFrameShape(QFrame::HLine);

  CQMetaboliteLayout->addMultiCellWidget(mpLine1, 6, 6, 0, 2);

  mpEditInitialValue = new QLineEdit(this, "mpEditInitialValue");
  mpEditInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialValue->sizePolicy().hasHeightForWidth()));
  mpEditInitialValue->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialValue->setFrameShadow(QLineEdit::Sunken);

  CQMetaboliteLayout->addWidget(mpEditInitialValue, 4, 1);

  mpLblInitialExpression = new QLabel(this, "mpLblInitialExpression");
  mpLblInitialExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblInitialExpression->sizePolicy().hasHeightForWidth()));
  mpLblInitialExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblInitialExpression, 5, 0);

  mpBoxUseInitialExpression = new QCheckBox(this, "mpBoxUseInitialExpression");

  CQMetaboliteLayout->addWidget(mpBoxUseInitialExpression, 4, 2);

  mpLblInitialValue = new QLabel(this, "mpLblInitialValue");
  mpLblInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblInitialValue->sizePolicy().hasHeightForWidth()));
  mpLblInitialValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblInitialValue, 4, 0);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblExpression, 3, 0);

  mpLblReactions = new QLabel(this, "mpLblReactions");
  mpLblReactions->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblReactions->sizePolicy().hasHeightForWidth()));
  mpLblReactions->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblReactions, 10, 0);

  mpReactionTable = new QListView(this, "mpReactionTable");
  mpReactionTable->addColumn(tr("Name"));
  mpReactionTable->addColumn(tr("Equation"));
  mpReactionTable->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpReactionTable->sizePolicy().hasHeightForWidth()));

  CQMetaboliteLayout->addMultiCellWidget(mpReactionTable, 10, 10, 1, 2);

  mpEditCurrentValue = new QLineEdit(this, "mpEditCurrentValue");
  mpEditCurrentValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditCurrentValue->sizePolicy().hasHeightForWidth()));
  mpEditCurrentValue->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentValue->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentValue->setReadOnly(TRUE);

  CQMetaboliteLayout->addWidget(mpEditCurrentValue, 7, 1);

  mpEditRate = new QLineEdit(this, "mpEditRate");
  mpEditRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditRate->sizePolicy().hasHeightForWidth()));
  mpEditRate->setFrameShape(QLineEdit::LineEditPanel);
  mpEditRate->setFrameShadow(QLineEdit::Sunken);
  mpEditRate->setReadOnly(TRUE);

  CQMetaboliteLayout->addWidget(mpEditRate, 8, 1);

  mpEditTransitionTime = new QLineEdit(this, "mpEditTransitionTime");
  mpEditTransitionTime->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditTransitionTime->sizePolicy().hasHeightForWidth()));
  mpEditTransitionTime->setFrameShape(QLineEdit::LineEditPanel);
  mpEditTransitionTime->setFrameShadow(QLineEdit::Sunken);
  mpEditTransitionTime->setReadOnly(TRUE);

  CQMetaboliteLayout->addWidget(mpEditTransitionTime, 9, 1);

  mpLblValue = new QLabel(this, "mpLblValue");
  mpLblValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblValue->sizePolicy().hasHeightForWidth()));
  mpLblValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblValue, 7, 0);

  mpLblTransitionTime = new QLabel(this, "mpLblTransitionTime");
  mpLblTransitionTime->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblTransitionTime->sizePolicy().hasHeightForWidth()));
  mpLblTransitionTime->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblTransitionTime, 9, 0);

  mpLblRate = new QLabel(this, "mpLblRate");
  mpLblRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblRate->sizePolicy().hasHeightForWidth()));
  mpLblRate->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblRate, 8, 0);
  mpSpacer = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQMetaboliteLayout->addItem(mpSpacer, 11, 1);

  mpLine2 = new QFrame(this, "mpLine2");
  mpLine2->setFrameShape(QFrame::HLine);
  mpLine2->setFrameShadow(QFrame::Sunken);
  mpLine2->setFrameShape(QFrame::HLine);

  CQMetaboliteLayout->addMultiCellWidget(mpLine2, 12, 12, 0, 2);

  mpExpressionEMW = new CQExpressionMmlWidget(this, "mpExpressionEMW");
  mpExpressionEMW->setMinimumSize(QSize(300, 30));

  CQMetaboliteLayout->addMultiCellWidget(mpExpressionEMW, 3, 3, 1, 2);

  mpInitialExpressionEMW = new CQExpressionMmlWidget(this, "mpInitialExpressionEMW");
  mpInitialExpressionEMW->setMinimumSize(QSize(300, 30));

  CQMetaboliteLayout->addMultiCellWidget(mpInitialExpressionEMW, 5, 5, 1, 2);
  languageChange();
  resize(QSize(453, 421).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnCommit, SIGNAL(clicked()), this, SLOT(slotBtnCommit()));
  connect(mpBtnDelete, SIGNAL(clicked()), this, SLOT(slotBtnDelete()));
  connect(mpBtnNew, SIGNAL(clicked()), this, SLOT(slotBtnNew()));
  connect(mpBtnRevert, SIGNAL(clicked()), this, SLOT(slotBtnRevert()));
  connect(mpComboBoxCompartment, SIGNAL(activated(int)), this, SLOT(slotCompartmentChanged(int)));
  connect(mpComboBoxType, SIGNAL(activated(int)), this, SLOT(slotTypeChanged(int)));
  connect(mpEditInitialValue, SIGNAL(lostFocus()), this, SLOT(slotInitialValueLostFocus()));
  connect(mpReactionTable, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(slotReactionTableCurrentChanged(QListViewItem*)));
  connect(mpBoxUseInitialExpression, SIGNAL(toggled(bool)), this, SLOT(slotInitialTypeChanged(bool)));
  connect(mpEditName, SIGNAL(lostFocus()), this, SLOT(slotNameLostFocus()));

  // tab order
  setTabOrder(mpEditName, mpComboBoxCompartment);
  setTabOrder(mpComboBoxCompartment, mpComboBoxType);
  setTabOrder(mpComboBoxType, mpEditInitialValue);
  setTabOrder(mpEditInitialValue, mpBoxUseInitialExpression);
  setTabOrder(mpBoxUseInitialExpression, mpEditCurrentValue);
  setTabOrder(mpEditCurrentValue, mpEditRate);
  setTabOrder(mpEditRate, mpEditTransitionTime);
  setTabOrder(mpEditTransitionTime, mpReactionTable);
  setTabOrder(mpReactionTable, mpBtnCommit);
  setTabOrder(mpBtnCommit, mpBtnRevert);
  setTabOrder(mpBtnRevert, mpBtnNew);
  setTabOrder(mpBtnNew, mpBtnDelete);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMetabolite::~CQMetabolite()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMetabolite::languageChange()
{
  setCaption(tr("Metabolite"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
  mpLblType->setText(tr("Simulation Type"));
  mpLblCompartment->setText(tr("Compartment"));
  mpLblName->setText(tr("Metobolite Name"));
  mpLblInitialExpression->setText(tr("Initial Expression"));
  mpBoxUseInitialExpression->setText(tr("Use Initial Expression"));
  mpLblInitialValue->setText(tr("Initial Value"));
  mpLblExpression->setText(tr("Expression"));
  mpLblReactions->setText(tr("Involved in Reactions"));
  mpReactionTable->header()->setLabel(0, tr("Name"));
  mpReactionTable->header()->setLabel(1, tr("Equation"));
  mpLblValue->setText(tr("Concentration"));
  mpLblTransitionTime->setText(tr("Transition Time"));
  mpLblRate->setText(tr("Rate"));
}
