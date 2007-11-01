// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/01 19:28:34 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Thu Nov 1 15:25:49 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.cpp,v 1.7 2007/11/01 19:28:34 shoops Exp $)
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
    0x80, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x95, 0x93, 0x31, 0x68, 0x53,
    0x61, 0x14, 0x85, 0xbf, 0x5f, 0x1c, 0x5e, 0x21, 0x43, 0xbb, 0xa5, 0x90,
    0xa1, 0x85, 0x37, 0x98, 0xa2, 0x90, 0x84, 0x2e, 0x3e, 0x1c, 0x24, 0x20,
    0x68, 0xa4, 0x83, 0xad, 0x0e, 0x4d, 0xb7, 0x66, 0xcc, 0x54, 0xaa, 0x83,
    0xd8, 0x0e, 0x52, 0x9c, 0x5a, 0x71, 0x7a, 0x38, 0xd8, 0x22, 0x62, 0x5f,
    0x5c, 0xda, 0x38, 0xd8, 0xd6, 0x41, 0xcc, 0x60, 0xc9, 0xdf, 0x52, 0x9a,
    0x17, 0x50, 0x9b, 0x04, 0x09, 0xbe, 0x0c, 0x92, 0x94, 0x50, 0x9a, 0x20,
    0x21, 0xcd, 0x50, 0xb8, 0x0e, 0x55, 0xab, 0xad, 0x22, 0x4e, 0x87, 0xcb,
    0x39, 0xdc, 0x73, 0xee, 0xe5, 0x5e, 0xa4, 0x2e, 0x88, 0x16, 0xa4, 0x2e,
    0xe4, 0x74, 0x8e, 0xff, 0xad, 0xc9, 0xea, 0x2c, 0x52, 0x97, 0x3f, 0xe3,
    0xd7, 0xb6, 0xe4, 0xb6, 0x56, 0x44, 0x3e, 0x55, 0x65, 0xd1, 0x99, 0x95,
    0x7d, 0x77, 0x47, 0x4e, 0xea, 0x94, 0xd4, 0x05, 0xb7, 0xec, 0x12, 0x31,
    0x23, 0x50, 0x06, 0x4c, 0x28, 0xec, 0xad, 0xca, 0x40, 0x77, 0x14, 0xfb,
    0xa5, 0x4d, 0x90, 0x28, 0x99, 0x2f, 0x6b, 0xc4, 0x2f, 0xc6, 0xf0, 0xc8,
    0x73, 0xfd, 0x6a, 0x02, 0x77, 0xdb, 0x55, 0x3f, 0xf5, 0x27, 0x3b, 0xe6,
    0xdc, 0xb7, 0x52, 0x75, 0x3e, 0xcb, 0xe4, 0xc4, 0x8c, 0x64, 0xa7, 0x73,
    0xb2, 0x94, 0x9e, 0x17, 0xd9, 0x97, 0xa3, 0x24, 0x5f, 0xdb, 0x7f, 0x4e,
    0xf0, 0xc3, 0x79, 0x75, 0x7b, 0x59, 0x7a, 0x6a, 0x41, 0x9c, 0xed, 0x34,
    0xc9, 0x2b, 0x31, 0x76, 0x7d, 0x45, 0xa2, 0xa1, 0x31, 0xf5, 0x83, 0x3f,
    0x99, 0xd4, 0x2d, 0xbb, 0xc7, 0x09, 0x16, 0x9f, 0xcd, 0xcb, 0xe4, 0xc4,
    0xac, 0xdc, 0xbb, 0x3b, 0x2b, 0xfb, 0x5b, 0xd5, 0x53, 0x4e, 0x7f, 0x43,
    0x25, 0x75, 0xc1, 0x79, 0xed, 0x48, 0x6f, 0x2b, 0x88, 0xc7, 0x06, 0x89,
    0xd1, 0x24, 0x6e, 0xe9, 0x97, 0x19, 0x4d, 0x28, 0x54, 0x1c, 0x19, 0x08,
    0x44, 0xe1, 0xcd, 0x43, 0xe8, 0xb9, 0x88, 0xdb, 0xd8, 0x20, 0x32, 0x74,
    0x0f, 0x4a, 0x3d, 0x4a, 0x2d, 0xa5, 0xe7, 0x65, 0x63, 0xbd, 0x41, 0x7f,
    0x5f, 0x17, 0xc9, 0x5b, 0x71, 0x74, 0xa5, 0xa8, 0x2c, 0xd3, 0x42, 0x97,
    0x35, 0x56, 0xa0, 0x57, 0xf4, 0xe6, 0x02, 0xc1, 0x0f, 0x45, 0x52, 0x15,
    0x08, 0x77, 0x0c, 0xd2, 0x07, 0xe0, 0xef, 0xea, 0xd0, 0x1f, 0xe8, 0x30,
    0x72, 0x67, 0x96, 0xb3, 0xbd, 0x0d, 0x3f, 0x86, 0xcf, 0x23, 0x39, 0x94,
    0xc0, 0xad, 0x78, 0xca, 0x32, 0x2d, 0x28, 0x83, 0x65, 0x20, 0xce, 0xe3,
    0x29, 0xfa, 0xcf, 0xc6, 0xb0, 0xf7, 0x1a, 0x24, 0x6e, 0x8c, 0xe0, 0x19,
    0x1e, 0x73, 0xa1, 0x61, 0xd8, 0x4c, 0x51, 0x28, 0x42, 0xe6, 0xf9, 0x34,
    0x67, 0x16, 0x36, 0x53, 0xc4, 0xfd, 0x31, 0xf4, 0x6e, 0x51, 0x45, 0xcc,
    0x08, 0xba, 0xac, 0xc1, 0xcb, 0x88, 0xfd, 0xe8, 0x01, 0xb5, 0xa6, 0x81,
    0x17, 0xf0, 0x98, 0xba, 0x6f, 0xe3, 0xf9, 0x0d, 0x65, 0x0d, 0x26, 0x94,
    0xae, 0x14, 0x15, 0xa1, 0x38, 0xa9, 0x92, 0x26, 0xdc, 0x6c, 0xa0, 0x96,
    0x1e, 0x2c, 0xca, 0xae, 0xcf, 0x23, 0x39, 0x3a, 0x75, 0xb4, 0xed, 0xd0,
    0x81, 0x38, 0x93, 0x37, 0x09, 0x9b, 0x71, 0x06, 0xc2, 0x06, 0x9c, 0x1f,
    0x51, 0xbf, 0x6d, 0xbf, 0xdb, 0x93, 0xb9, 0x27, 0x36, 0xd1, 0xee, 0x30,
    0x91, 0x0b, 0x35, 0xce, 0xe4, 0x5b, 0x9a, 0xda, 0x5e, 0x87, 0xd5, 0xcd,
    0x05, 0xc1, 0x04, 0xef, 0x63, 0x0a, 0xab, 0x73, 0xc0, 0x46, 0x73, 0x0d,
    0xfa, 0x82, 0x78, 0x25, 0x5b, 0x22, 0x01, 0x43, 0x0a, 0xdb, 0x73, 0x72,
    0xb0, 0x9e, 0x10, 0x7b, 0x26, 0x01, 0x7b, 0x0d, 0x6a, 0x81, 0x1a, 0x5c,
    0xba, 0xad, 0x54, 0xfb, 0x7d, 0x55, 0xa6, 0x9f, 0x2e, 0x10, 0x1f, 0x8c,
    0xe2, 0x75, 0x15, 0x19, 0x09, 0x45, 0x71, 0x5e, 0x24, 0x08, 0x1f, 0x36,
    0x59, 0x5b, 0x87, 0x68, 0x2b, 0x46, 0x86, 0x0c, 0x96, 0x6f, 0x98, 0xb4,
    0x2f, 0xcf, 0xf8, 0xb5, 0x38, 0x03, 0x3d, 0x15, 0xb8, 0x9c, 0x54, 0x6e,
    0xd9, 0x45, 0x65, 0x75, 0x16, 0xcb, 0x1f, 0x14, 0xfb, 0xd5, 0x43, 0x0a,
    0x25, 0x83, 0x4e, 0x0b, 0x38, 0xb4, 0x68, 0x36, 0x96, 0xa1, 0x05, 0x1c,
    0xc2, 0x78, 0x3f, 0x54, 0xce, 0x75, 0x31, 0x3e, 0x34, 0x4e, 0xbe, 0x95,
    0xc7, 0x3a, 0x37, 0xa6, 0x74, 0x59, 0x63, 0x99, 0x16, 0xc7, 0x5f, 0xb6,
    0xdf, 0x16, 0xd1, 0x2b, 0x22, 0xd5, 0xb6, 0x64, 0xbf, 0xa3, 0xbc, 0x5b,
    0x11, 0xa9, 0x8a, 0xec, 0xb8, 0x59, 0x39, 0xe2, 0x4f, 0x7f, 0xe5, 0x3f,
    0x2f, 0xed, 0x5f, 0xf8, 0x0d, 0xa8, 0xa7, 0x05, 0xd9, 0x07, 0x13, 0x99,
    0x9e, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
    0x82
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

  mpBtnToggle = new QPushButton(this, "mpBtnToggle");

  layout7->addMultiCellWidget(mpBtnToggle, 4, 5, 0, 0);

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
  setTabOrder(mpComboBoxType, mpBtnToggle);
  setTabOrder(mpBtnToggle, mpComboBoxInitialType);
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
  mpBtnToggle->setText(tr("Particle Numbers"));
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
