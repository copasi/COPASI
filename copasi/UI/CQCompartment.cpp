// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/06 10:25:05 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQCompartment.ui'
 **
 ** Created: Fri Jun 6 12:23:43 2008
 **      by: The User Interface Compiler ($Id: CQCompartment.cpp,v 1.8 2008/06/06 10:25:05 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQCompartment.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qframe.h>
#include <qcheckbox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQExpressionMmlWidget.h"
#include "CQExpressionWidget.h"
#include "CQCompartment.ui.h"

/*
 *  Constructs a CQCompartment which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCompartment::CQCompartment(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("CQCompartment");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  CQCompartmentLayout = new QGridLayout(this, 1, 1, 11, 6, "CQCompartmentLayout");

  mpBtnLayout = new QHBoxLayout(0, 0, 6, "mpBtnLayout");

  mpBtnCommit = new QPushButton(this, "mpBtnCommit");
  mpBtnLayout->addWidget(mpBtnCommit);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");
  mpBtnLayout->addWidget(mpBtnRevert);

  mpBtnNew = new QPushButton(this, "mpBtnNew");
  mpBtnLayout->addWidget(mpBtnNew);

  mpBtnDelete = new QPushButton(this, "mpBtnDelete");
  mpBtnLayout->addWidget(mpBtnDelete);

  CQCompartmentLayout->addMultiCellLayout(mpBtnLayout, 11, 11, 0, 2);

  mpComboBoxType = new QComboBox(FALSE, this, "mpComboBoxType");
  mpComboBoxType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxType->sizePolicy().hasHeightForWidth()));

  CQCompartmentLayout->addWidget(mpComboBoxType, 1, 1);

  mpEditName = new QLineEdit(this, "mpEditName");
  mpEditName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpEditName->sizePolicy().hasHeightForWidth()));
  mpEditName->setFrameShape(QLineEdit::LineEditPanel);
  mpEditName->setFrameShadow(QLineEdit::Sunken);

  CQCompartmentLayout->addMultiCellWidget(mpEditName, 0, 0, 1, 2);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQCompartmentLayout->addWidget(mpLblType, 1, 0);

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblName->sizePolicy().hasHeightForWidth()));
  mpLblName->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQCompartmentLayout->addWidget(mpLblName, 0, 0);

  mpLblMetabolites = new QLabel(this, "mpLblMetabolites");
  mpLblMetabolites->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblMetabolites->sizePolicy().hasHeightForWidth()));
  mpLblMetabolites->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQCompartmentLayout->addMultiCellWidget(mpLblMetabolites, 8, 9, 0, 0);

  mpLblRate = new QLabel(this, "mpLblRate");
  mpLblRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblRate->sizePolicy().hasHeightForWidth()));
  mpLblRate->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQCompartmentLayout->addWidget(mpLblRate, 7, 0);

  mpEditRate = new QLineEdit(this, "mpEditRate");
  mpEditRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditRate->sizePolicy().hasHeightForWidth()));
  mpEditRate->setFrameShape(QLineEdit::LineEditPanel);
  mpEditRate->setFrameShadow(QLineEdit::Sunken);
  mpEditRate->setReadOnly(TRUE);

  CQCompartmentLayout->addWidget(mpEditRate, 7, 1);

  mpLblVolume = new QLabel(this, "mpLblVolume");
  mpLblVolume->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblVolume->sizePolicy().hasHeightForWidth()));
  mpLblVolume->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQCompartmentLayout->addWidget(mpLblVolume, 6, 0);

  mpEditCurrentVolume = new QLineEdit(this, "mpEditCurrentVolume");
  mpEditCurrentVolume->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditCurrentVolume->sizePolicy().hasHeightForWidth()));
  mpEditCurrentVolume->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentVolume->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentVolume->setReadOnly(TRUE);

  CQCompartmentLayout->addWidget(mpEditCurrentVolume, 6, 1);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQCompartmentLayout->addWidget(mpLblExpression, 2, 0);

  mpLine1 = new QFrame(this, "mpLine1");
  mpLine1->setFrameShape(QFrame::HLine);
  mpLine1->setFrameShadow(QFrame::Sunken);
  mpLine1->setFrameShape(QFrame::HLine);

  CQCompartmentLayout->addMultiCellWidget(mpLine1, 5, 5, 0, 2);

  mpLblInitialValue = new QLabel(this, "mpLblInitialValue");
  mpLblInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblInitialValue->sizePolicy().hasHeightForWidth()));
  mpLblInitialValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQCompartmentLayout->addWidget(mpLblInitialValue, 3, 0);

  mpEditInitialVolume = new QLineEdit(this, "mpEditInitialVolume");
  mpEditInitialVolume->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialVolume->sizePolicy().hasHeightForWidth()));
  mpEditInitialVolume->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialVolume->setFrameShadow(QLineEdit::Sunken);

  CQCompartmentLayout->addWidget(mpEditInitialVolume, 3, 1);

  mpBoxUseInitialExpression = new QCheckBox(this, "mpBoxUseInitialExpression");

  CQCompartmentLayout->addWidget(mpBoxUseInitialExpression, 3, 2);

  mpLblInitialExpression = new QLabel(this, "mpLblInitialExpression");
  mpLblInitialExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblInitialExpression->sizePolicy().hasHeightForWidth()));
  mpLblInitialExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQCompartmentLayout->addWidget(mpLblInitialExpression, 4, 0);

  mpInitialExpressionEMW = new CQExpressionMmlWidget(this, "mpInitialExpressionEMW");
  mpInitialExpressionEMW->setMinimumSize(QSize(300, 30));

  CQCompartmentLayout->addMultiCellWidget(mpInitialExpressionEMW, 4, 4, 1, 2);

  mpExpressionEMW = new CQExpressionMmlWidget(this, "mpExpressionEMW");
  mpExpressionEMW->setMinimumSize(QSize(300, 30));

  CQCompartmentLayout->addMultiCellWidget(mpExpressionEMW, 2, 2, 1, 2);

  mpLine2 = new QFrame(this, "mpLine2");
  mpLine2->setFrameShape(QFrame::HLine);
  mpLine2->setFrameShadow(QFrame::Sunken);
  mpLine2->setFrameShape(QFrame::HLine);

  CQCompartmentLayout->addMultiCellWidget(mpLine2, 10, 10, 0, 2);

  mpMetaboliteTable = new QListView(this, "mpMetaboliteTable");
  mpMetaboliteTable->addColumn(tr("Name"));
  mpMetaboliteTable->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpMetaboliteTable->sizePolicy().hasHeightForWidth()));

  CQCompartmentLayout->addMultiCellWidget(mpMetaboliteTable, 8, 8, 1, 2);
  mpSpacer = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQCompartmentLayout->addItem(mpSpacer, 9, 1);
  languageChange();
  resize(QSize(460, 364).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnCommit, SIGNAL(clicked()), this, SLOT(slotBtnCommit()));
  connect(mpBtnDelete, SIGNAL(clicked()), this, SLOT(slotBtnDelete()));
  connect(mpBtnNew, SIGNAL(clicked()), this, SLOT(slotBtnNew()));
  connect(mpBtnRevert, SIGNAL(clicked()), this, SLOT(slotBtnRevert()));
  connect(mpComboBoxType, SIGNAL(activated(int)), this, SLOT(slotTypeChanged(int)));
  connect(mpMetaboliteTable, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(slotMetaboliteTableCurrentChanged(QListViewItem*)));
  connect(mpBoxUseInitialExpression, SIGNAL(toggled(bool)), this, SLOT(slotInitialTypeChanged(bool)));
  connect(mpEditName, SIGNAL(lostFocus()), this, SLOT(slotNameLostFocus()));

  // tab order
  setTabOrder(mpEditName, mpComboBoxType);
  setTabOrder(mpComboBoxType, mpEditInitialVolume);
  setTabOrder(mpEditInitialVolume, mpBoxUseInitialExpression);
  setTabOrder(mpBoxUseInitialExpression, mpEditRate);
  setTabOrder(mpEditRate, mpMetaboliteTable);
  setTabOrder(mpMetaboliteTable, mpBtnCommit);
  setTabOrder(mpBtnCommit, mpBtnRevert);
  setTabOrder(mpBtnRevert, mpBtnNew);
  setTabOrder(mpBtnNew, mpBtnDelete);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQCompartment::~CQCompartment()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQCompartment::languageChange()
{
  setCaption(tr("Compartment"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
  mpLblType->setText(tr("Simulation Type"));
  mpLblName->setText(tr("Compartment Name"));
  mpLblMetabolites->setText(tr("Contained Metabolites"));
  mpLblRate->setText(tr("Rate"));
  mpLblVolume->setText(tr("Volume"));
  mpLblExpression->setText(tr("Expression"));
  mpLblInitialValue->setText(tr("Initial Volume"));
  mpBoxUseInitialExpression->setText(tr("Use Initial Expression"));
  mpLblInitialExpression->setText(tr("Initial Expression"));
  mpMetaboliteTable->header()->setLabel(0, tr("Name"));
}
