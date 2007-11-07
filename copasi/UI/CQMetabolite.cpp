// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/07 17:05:36 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Wed Nov 7 11:06:12 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.cpp,v 1.8 2007/11/07 17:05:36 shoops Exp $)
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
#include <qtoolbutton.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "CQExpressionWidget.h"
#include "CQMetabolite.ui.h"
static const unsigned char image0_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x61, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0x95, 0x93, 0x4f, 0x48, 0x93,
    0x71, 0x18, 0xc7, 0xbf, 0x3f, 0xf1, 0x30, 0xc1, 0x0e, 0x81, 0x87, 0x1d,
    0x3c, 0x38, 0xe8, 0x30, 0xa3, 0x20, 0xc7, 0x0e, 0xed, 0x3d, 0x85, 0x74,
    0x69, 0xd1, 0x21, 0x3d, 0xd5, 0xe8, 0xb2, 0xd1, 0xa1, 0xde, 0x43, 0xc8,
    0xbc, 0x88, 0x4a, 0x07, 0xf3, 0x10, 0xd3, 0x9b, 0x2f, 0x21, 0x6d, 0xc1,
    0x68, 0xb3, 0xcb, 0x5a, 0x20, 0x6b, 0x87, 0xc0, 0x05, 0xb9, 0xf7, 0x67,
    0x08, 0xef, 0xbb, 0x28, 0xb7, 0xf7, 0x85, 0x64, 0xaf, 0x07, 0xc9, 0x10,
    0x79, 0x1d, 0x22, 0x73, 0x07, 0xe1, 0xdb, 0x61, 0x16, 0xa2, 0x86, 0x75,
    0xfa, 0xf0, 0xf0, 0xfc, 0xf9, 0x7e, 0x79, 0x78, 0x1e, 0xd0, 0x25, 0x28,
    0x09, 0xba, 0x84, 0x21, 0x0d, 0xfc, 0x6f, 0x0c, 0x5d, 0xea, 0xa0, 0xcb,
    0xb3, 0xd9, 0x24, 0x8d, 0xd5, 0x02, 0x59, 0x77, 0x99, 0xc9, 0x26, 0xd8,
    0xfc, 0x5a, 0xe7, 0xc9, 0xba, 0x33, 0x27, 0x57, 0x6b, 0x05, 0x72, 0x9b,
    0x9c, 0xd3, 0x12, 0xd4, 0xe7, 0xab, 0x1c, 0x1f, 0x9b, 0x62, 0xbd, 0x58,
    0x65, 0x61, 0x31, 0x49, 0x92, 0x3c, 0x5e, 0x7f, 0x4a, 0xd9, 0x30, 0x97,
    0xe8, 0x66, 0x7f, 0x30, 0x3e, 0x32, 0x45, 0x63, 0xb2, 0xca, 0x5c, 0x3e,
    0x49, 0xee, 0x1d, 0x39, 0x69, 0xf2, 0x6c, 0x07, 0xbf, 0x95, 0x0b, 0xc5,
    0x1c, 0x8d, 0x74, 0x9d, 0x8f, 0x1f, 0x4d, 0xb1, 0xbe, 0x58, 0xe5, 0xd2,
    0x87, 0x0c, 0xff, 0x79, 0x07, 0x99, 0x74, 0x92, 0xf1, 0x91, 0x04, 0xc7,
    0xc7, 0x12, 0x6c, 0x9a, 0xee, 0x29, 0xa5, 0xbf, 0xf1, 0xa8, 0x39, 0x43,
    0x7d, 0xbe, 0xca, 0xa4, 0x36, 0xd7, 0xb6, 0x7b, 0x72, 0x27, 0xab, 0x19,
    0x72, 0xdb, 0x25, 0xd3, 0x71, 0xb2, 0x58, 0xa0, 0x91, 0x8e, 0x93, 0x7b,
    0x4d, 0x52, 0x12, 0x22, 0x97, 0x4f, 0x72, 0x65, 0x79, 0x17, 0xbe, 0xbe,
    0x2e, 0xa8, 0xf7, 0xa2, 0x90, 0xeb, 0x15, 0xa1, 0xf8, 0x15, 0x48, 0x5b,
    0x42, 0xe9, 0xf3, 0x51, 0x96, 0x35, 0x0c, 0x7c, 0xb3, 0xf0, 0x6a, 0x03,
    0x08, 0xb5, 0x3c, 0x58, 0x38, 0x00, 0xbc, 0x5d, 0x2d, 0xf8, 0x7a, 0x5b,
    0x18, 0x1e, 0x9b, 0x83, 0x30, 0xd2, 0x4b, 0xcc, 0xaf, 0x97, 0xf0, 0xec,
    0xe1, 0x38, 0xcc, 0x4d, 0x4b, 0x04, 0xfc, 0x01, 0xc0, 0x06, 0xd0, 0x6d,
    0x32, 0xfb, 0x66, 0x16, 0xfd, 0x9e, 0x21, 0x14, 0x7f, 0x96, 0xa0, 0xde,
    0x8a, 0xc0, 0xea, 0xb4, 0xa0, 0x04, 0xef, 0x03, 0xe5, 0x57, 0x70, 0xbe,
    0x7b, 0xe0, 0xa0, 0x88, 0x0e, 0xad, 0x9c, 0x42, 0xcc, 0x3b, 0x04, 0xb9,
    0x59, 0x11, 0x01, 0x7f, 0x00, 0xd2, 0x96, 0x80, 0x23, 0xa9, 0x25, 0x26,
    0xb1, 0xd5, 0xf0, 0xc0, 0xf2, 0x5a, 0x98, 0x98, 0xd6, 0x60, 0xf5, 0x40,
    0x28, 0xd7, 0x63, 0x42, 0xae, 0x57, 0x04, 0x82, 0x51, 0xa4, 0xd6, 0x4a,
    0x08, 0x35, 0x76, 0x21, 0x0a, 0xcf, 0x73, 0xdc, 0xf0, 0x58, 0x50, 0x1f,
    0x4c, 0x08, 0xd8, 0x00, 0x82, 0x60, 0xf6, 0xc9, 0x6d, 0x28, 0xfe, 0x28,
    0x7c, 0x57, 0x01, 0x5c, 0x1b, 0x16, 0xa6, 0x6d, 0xe2, 0x8f, 0xb3, 0x9e,
    0x2d, 0xce, 0xbc, 0x98, 0x45, 0xb8, 0x27, 0x84, 0xcb, 0xfd, 0x0e, 0x3a,
    0x56, 0x1a, 0x25, 0x6c, 0xed, 0xb4, 0xf0, 0xbe, 0x9c, 0x22, 0xfc, 0x80,
    0xf3, 0x25, 0x85, 0xc1, 0xd6, 0x01, 0x4a, 0x3b, 0x79, 0xe0, 0x52, 0x00,
    0xce, 0x9a, 0xc6, 0x40, 0xdf, 0x45, 0xd6, 0x3e, 0xcf, 0x10, 0xcb, 0x31,
    0x6a, 0x4f, 0x23, 0xc0, 0xce, 0x2e, 0x1c, 0xaf, 0x03, 0xdc, 0x18, 0x15,
    0x82, 0x35, 0x97, 0xa3, 0x2f, 0x35, 0x44, 0x43, 0x61, 0x58, 0x9d, 0x15,
    0x0c, 0x07, 0xc3, 0xc8, 0xbe, 0x8e, 0x40, 0x41, 0x03, 0x6f, 0x3f, 0x02,
    0xe1, 0xfd, 0x21, 0x14, 0x51, 0xc4, 0x60, 0x77, 0x04, 0x0b, 0xdd, 0x12,
    0xea, 0x9d, 0x18, 0x7c, 0x17, 0x2c, 0xe0, 0xa6, 0x2a, 0x4c, 0xdb, 0x84,
    0xd0, 0xa5, 0x0e, 0xa5, 0x77, 0x80, 0xda, 0xbb, 0x69, 0xd4, 0x6c, 0x0f,
    0x5a, 0xfb, 0x00, 0x0e, 0x07, 0xd1, 0xd8, 0xcd, 0x02, 0xfb, 0x00, 0x0e,
    0x01, 0xd5, 0x07, 0x58, 0xfe, 0x2e, 0xa8, 0x77, 0x55, 0xc8, 0x86, 0x84,
    0x72, 0x25, 0x22, 0xa4, 0x2d, 0xa1, 0xf8, 0x95, 0x63, 0xbf, 0xb0, 0x47,
    0x52, 0xb6, 0x7f, 0x40, 0x3f, 0x22, 0x3f, 0xb5, 0x59, 0x35, 0x75, 0xb6,
    0xf3, 0xa7, 0x2f, 0xf2, 0xdc, 0x4b, 0x3b, 0x8f, 0xbf, 0x00, 0xa2, 0x81,
    0x53, 0x0f, 0xab, 0x7c, 0xd1, 0xff, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
    0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
  };

/*
 *  Constructs a CQMetabolite which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMetabolite::CQMetabolite(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  QImage img;
  img.loadFromData(image0_data, sizeof(image0_data), "PNG");
  image0 = img;
  if (!name)
    setName("CQMetabolite");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  CQMetaboliteLayout = new QVBoxLayout(this, 11, 6, "CQMetaboliteLayout");

  layout7 = new QGridLayout(0, 1, 1, 0, 6, "layout7");

  mpLblReactions = new QLabel(this, "mpLblReactions");
  mpLblReactions->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblReactions->sizePolicy().hasHeightForWidth()));
  mpLblReactions->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  layout7->addWidget(mpLblReactions, 10, 0);

  mpEditTransitionTime = new QLineEdit(this, "mpEditTransitionTime");
  mpEditTransitionTime->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditTransitionTime->sizePolicy().hasHeightForWidth()));
  mpEditTransitionTime->setFrameShape(QLineEdit::LineEditPanel);
  mpEditTransitionTime->setFrameShadow(QLineEdit::Sunken);
  mpEditTransitionTime->setReadOnly(TRUE);

  layout7->addWidget(mpEditTransitionTime, 8, 2);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  layout7->addWidget(mpLblExpression, 9, 0);

  mpLayoutInitialValues = new QHBoxLayout(0, 0, 6, "mpLayoutInitialValues");

  mpLblInitialValue = new QLabel(this, "mpLblInitialValue");
  mpLblInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblInitialValue->sizePolicy().hasHeightForWidth()));
  mpLblInitialValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignLeft));
  mpLayoutInitialValues->addWidget(mpLblInitialValue);

  mpComboBoxInitialType = new QComboBox(FALSE, this, "mpComboBoxInitialType");
  mpComboBoxInitialType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxInitialType->sizePolicy().hasHeightForWidth()));
  mpLayoutInitialValues->addWidget(mpComboBoxInitialType);

  layout7->addLayout(mpLayoutInitialValues, 5, 1);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblType, 2, 0);

  mpEditCurrentValue = new QLineEdit(this, "mpEditCurrentValue");
  mpEditCurrentValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditCurrentValue->sizePolicy().hasHeightForWidth()));
  mpEditCurrentValue->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentValue->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentValue->setReadOnly(TRUE);

  layout7->addWidget(mpEditCurrentValue, 6, 2);

  mpLblRate = new QLabel(this, "mpLblRate");
  mpLblRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblRate->sizePolicy().hasHeightForWidth()));
  mpLblRate->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblRate, 7, 0);

  mpLblValue = new QLabel(this, "mpLblValue");
  mpLblValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblValue->sizePolicy().hasHeightForWidth()));
  mpLblValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblValue, 6, 0);

  mpEditName = new QLineEdit(this, "mpEditName");
  mpEditName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpEditName->sizePolicy().hasHeightForWidth()));
  mpEditName->setFrameShape(QLineEdit::LineEditPanel);
  mpEditName->setFrameShadow(QLineEdit::Sunken);

  layout7->addMultiCellWidget(mpEditName, 0, 0, 1, 2);

  mpLine1 = new QFrame(this, "mpLine1");
  mpLine1->setFrameShape(QFrame::HLine);
  mpLine1->setFrameShadow(QFrame::Sunken);
  mpLine1->setFrameShape(QFrame::HLine);

  layout7->addMultiCellWidget(mpLine1, 3, 3, 0, 2);

  mpComboBoxCompartment = new QComboBox(FALSE, this, "mpComboBoxCompartment");
  mpComboBoxCompartment->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxCompartment->sizePolicy().hasHeightForWidth()));

  layout7->addMultiCellWidget(mpComboBoxCompartment, 1, 1, 1, 2);

  mpEditRate = new QLineEdit(this, "mpEditRate");
  mpEditRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditRate->sizePolicy().hasHeightForWidth()));
  mpEditRate->setFrameShape(QLineEdit::LineEditPanel);
  mpEditRate->setFrameShadow(QLineEdit::Sunken);
  mpEditRate->setReadOnly(TRUE);

  layout7->addWidget(mpEditRate, 7, 2);

  mpHBoxLayout = new QHBoxLayout(0, 0, 6, "mpHBoxLayout");

  mpEditExpression = new CQExpressionWidget(this, "mpEditExpression");
  mpEditExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpEditExpression->sizePolicy().hasHeightForWidth()));
  mpHBoxLayout->addWidget(mpEditExpression);

  mpVBoxLayout = new QVBoxLayout(0, 0, 6, "mpVBoxLayout");

  mpBtnObject = new QToolButton(this, "mpBtnObject");
  mpBtnObject->setMaximumSize(QSize(20, 20));
  mpBtnObject->setIconSet(QIconSet(image0));
  mpVBoxLayout->addWidget(mpBtnObject);
  mpSpacerObject = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpVBoxLayout->addItem(mpSpacerObject);
  mpHBoxLayout->addLayout(mpVBoxLayout);

  layout7->addMultiCellLayout(mpHBoxLayout, 9, 9, 1, 2);

  mpLayoutInitialConcentration = new QVBoxLayout(0, 0, 6, "mpLayoutInitialConcentration");

  mpEditInitialValue = new QLineEdit(this, "mpEditInitialValue");
  mpEditInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialValue->sizePolicy().hasHeightForWidth()));
  mpEditInitialValue->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialValue->setFrameShadow(QLineEdit::Sunken);
  mpLayoutInitialConcentration->addWidget(mpEditInitialValue);

  mpComboBoxInitialSelection = new QComboBox(FALSE, this, "mpComboBoxInitialSelection");
  mpComboBoxInitialSelection->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxInitialSelection->sizePolicy().hasHeightForWidth()));
  mpLayoutInitialConcentration->addWidget(mpComboBoxInitialSelection);

  layout7->addLayout(mpLayoutInitialConcentration, 6, 1);

  mpComboBoxType = new QComboBox(FALSE, this, "mpComboBoxType");
  mpComboBoxType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxType->sizePolicy().hasHeightForWidth()));

  layout7->addWidget(mpComboBoxType, 2, 1);

  mpLblTransientValue = new QLabel(this, "mpLblTransientValue");
  mpLblTransientValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpLblTransientValue->sizePolicy().hasHeightForWidth()));
  mpLblTransientValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignLeft));

  layout7->addWidget(mpLblTransientValue, 5, 2);

  mpLblCompartment = new QLabel(this, "mpLblCompartment");
  mpLblCompartment->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblCompartment->sizePolicy().hasHeightForWidth()));
  mpLblCompartment->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblCompartment, 1, 0);

  mpReactionTable = new QListView(this, "mpReactionTable");
  mpReactionTable->addColumn(tr("Name"));
  mpReactionTable->addColumn(tr("Equation"));
  mpReactionTable->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpReactionTable->sizePolicy().hasHeightForWidth()));

  layout7->addMultiCellWidget(mpReactionTable, 10, 10, 1, 2);

  mpLblTransitionTime = new QLabel(this, "mpLblTransitionTime");
  mpLblTransitionTime->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblTransitionTime->sizePolicy().hasHeightForWidth()));
  mpLblTransitionTime->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblTransitionTime, 8, 0);

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblName->sizePolicy().hasHeightForWidth()));
  mpLblName->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblName, 0, 0);
  CQMetaboliteLayout->addLayout(layout7);
  mpSpacer = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQMetaboliteLayout->addItem(mpSpacer);

  mpLine2 = new QFrame(this, "mpLine2");
  mpLine2->setFrameShape(QFrame::HLine);
  mpLine2->setFrameShadow(QFrame::Sunken);
  mpLine2->setFrameShape(QFrame::HLine);
  CQMetaboliteLayout->addWidget(mpLine2);

  mpBtnLayout = new QHBoxLayout(0, 0, 6, "mpBtnLayout");

  mpBtnCommit = new QPushButton(this, "mpBtnCommit");
  mpBtnLayout->addWidget(mpBtnCommit);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");
  mpBtnLayout->addWidget(mpBtnRevert);

  mpBtnNew = new QPushButton(this, "mpBtnNew");
  mpBtnLayout->addWidget(mpBtnNew);

  mpBtnDelete = new QPushButton(this, "mpBtnDelete");
  mpBtnLayout->addWidget(mpBtnDelete);
  CQMetaboliteLayout->addLayout(mpBtnLayout);
  languageChange();
  resize(QSize(493, 482).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnCommit, SIGNAL(clicked()), this, SLOT(slotBtnCommit()));
  connect(mpBtnDelete, SIGNAL(clicked()), this, SLOT(slotBtnDelete()));
  connect(mpBtnNew, SIGNAL(clicked()), this, SLOT(slotBtnNew()));
  connect(mpBtnRevert, SIGNAL(clicked()), this, SLOT(slotBtnRevert()));
  connect(mpComboBoxCompartment, SIGNAL(activated(int)), this, SLOT(slotCompartmentChanged(int)));
  connect(mpComboBoxType, SIGNAL(activated(int)), this, SLOT(slotTypeChanged(int)));
  connect(mpComboBoxInitialType, SIGNAL(activated(int)), this, SLOT(slotInitialTypeChanged(int)));
  connect(mpComboBoxInitialSelection, SIGNAL(activated(int)), this, SLOT(slotInitialAssignment(int)));
  connect(mpBtnObject, SIGNAL(clicked()), mpEditExpression, SLOT(slotSelectObject()));
  connect(mpEditExpression, SIGNAL(valid(bool)), this, SLOT(slotExpressionValid(bool)));
  connect(mpEditInitialValue, SIGNAL(lostFocus()), this, SLOT(slotInitialValueLostFocus()));
  connect(mpReactionTable, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(slotReactionTableCurrentChanged(QListViewItem*)));

  // tab order
  setTabOrder(mpEditName, mpComboBoxCompartment);
  setTabOrder(mpComboBoxCompartment, mpComboBoxType);
  setTabOrder(mpComboBoxType, mpComboBoxInitialType);
  setTabOrder(mpComboBoxInitialType, mpEditInitialValue);
  setTabOrder(mpEditInitialValue, mpComboBoxInitialSelection);
  setTabOrder(mpComboBoxInitialSelection, mpEditCurrentValue);
  setTabOrder(mpEditCurrentValue, mpEditRate);
  setTabOrder(mpEditRate, mpEditTransitionTime);
  setTabOrder(mpEditTransitionTime, mpEditExpression);
  setTabOrder(mpEditExpression, mpBtnObject);
  setTabOrder(mpBtnObject, mpReactionTable);
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
  mpLblReactions->setText(tr("Involved in Reactions"));
  mpLblExpression->setText(tr("Expression"));
  mpLblInitialValue->setText(tr("Initial Values"));
  mpLblType->setText(tr("Type"));
  mpLblRate->setText(tr("Rate"));
  mpLblValue->setText(tr("Concentration"));
  mpBtnObject->setText(QString::null);
  mpBtnObject->setTextLabel(tr("select"));
  mpLblTransientValue->setText(tr("Transient Values"));
  mpLblCompartment->setText(tr("Compartment"));
  mpReactionTable->header()->setLabel(0, tr("Name"));
  mpReactionTable->header()->setLabel(1, tr("Equation"));
  mpLblTransitionTime->setText(tr("Transition Time"));
  mpLblName->setText(tr("Metobolite Name"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
}
