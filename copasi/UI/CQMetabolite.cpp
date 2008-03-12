// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:32:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Tue Nov 13 09:42:52 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.cpp,v 1.12 2008/03/12 00:32:58 shoops Exp $)
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
    0x2b, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0x95, 0x93, 0xbf, 0x6b, 0x14,
    0x41, 0x14, 0xc7, 0x3f, 0x0b, 0x53, 0xbc, 0xc0, 0x15, 0xb3, 0x90, 0xe2,
    0x06, 0x14, 0x6e, 0x21, 0x82, 0x1b, 0x92, 0x62, 0x45, 0x8b, 0x04, 0x8b,
    0xc4, 0x32, 0x9d, 0x82, 0xff, 0xa1, 0xb6, 0x16, 0x22, 0xb1, 0x50, 0x72,
    0x85, 0x24, 0x27, 0x89, 0x71, 0x03, 0x09, 0x4c, 0xa1, 0xb0, 0x01, 0x0f,
    0x66, 0x8b, 0xc0, 0x0e, 0xe4, 0x20, 0xaf, 0x58, 0x18, 0x8b, 0xe4, 0xf2,
    0xc3, 0x68, 0x61, 0xf5, 0xe5, 0x0d, 0xef, 0xf1, 0xbe, 0xef, 0xcb, 0x67,
    0xb2, 0xc3, 0xfd, 0x43, 0xe8, 0x01, 0x03, 0xda, 0x2b, 0x62, 0xe4, 0xbf,
    0x6a, 0x33, 0x7f, 0xfc, 0x9b, 0xda, 0x81, 0x26, 0xd5, 0x0e, 0xd5, 0x48,
    0x13, 0x02, 0x76, 0x01, 0xf2, 0xe1, 0x7a, 0x76, 0xbb, 0xcf, 0xdc, 0x2e,
    0xe8, 0x41, 0x8c, 0x20, 0x12, 0x12, 0x33, 0x18, 0x8f, 0x3d, 0x61, 0x0a,
    0x18, 0xc5, 0x0d, 0x05, 0x5b, 0x2c, 0xe0, 0x16, 0x35, 0x85, 0x33, 0xb2,
    0x79, 0xff, 0x3d, 0x07, 0x98, 0x98, 0x7c, 0x1d, 0x99, 0x1c, 0x35, 0xd8,
    0x81, 0x50, 0xad, 0xe5, 0x94, 0x4b, 0x25, 0xaa, 0x1d, 0x22, 0x10, 0xce,
    0xe4, 0xbe, 0x83, 0xf9, 0xe6, 0x70, 0xd6, 0xa4, 0xfa, 0xa0, 0xa5, 0x99,
    0x76, 0x3c, 0x79, 0x2c, 0x8c, 0x4a, 0x87, 0x5b, 0x2c, 0x33, 0x9d, 0x01,
    0xc6, 0x11, 0x67, 0x77, 0x9d, 0xde, 0xc9, 0xc0, 0xfb, 0x3a, 0xed, 0x1d,
    0x05, 0x72, 0x11, 0xb6, 0x36, 0x4a, 0x5c, 0xe1, 0xb2, 0x7f, 0x65, 0x73,
    0xcf, 0x81, 0xf7, 0x75, 0xf2, 0x27, 0x1d, 0xcb, 0x4b, 0x39, 0x9b, 0x6b,
    0x15, 0x51, 0x6f, 0x6e, 0x14, 0x23, 0x48, 0x5f, 0xa7, 0x1c, 0xa1, 0x3b,
    0xae, 0x61, 0x76, 0x81, 0xda, 0x05, 0xca, 0xd5, 0x4d, 0x1a, 0x75, 0x99,
    0x69, 0xa6, 0x75, 0xda, 0xfb, 0x16, 0x58, 0x5e, 0xca, 0x59, 0xab, 0x46,
    0xd7, 0xc3, 0xda, 0x2b, 0x0e, 0x9f, 0xc2, 0x69, 0x43, 0x38, 0xf6, 0x9c,
    0x9e, 0x2a, 0xdd, 0xb9, 0x25, 0xf6, 0x60, 0x4d, 0x4b, 0x38, 0xf2, 0xac,
    0xbf, 0x7e, 0x95, 0x8c, 0xaf, 0x3d, 0xb9, 0x15, 0xaa, 0xd5, 0x21, 0x4a,
    0x7e, 0xbd, 0xd9, 0xb6, 0x3b, 0x69, 0xef, 0xa0, 0xa6, 0x99, 0x5a, 0x18,
    0x58, 0x8a, 0xa7, 0x8e, 0xea, 0x51, 0x81, 0xb5, 0x16, 0x6d, 0x5b, 0x26,
    0x1f, 0x77, 0xf0, 0x5f, 0xde, 0x61, 0x9a, 0x36, 0xb0, 0xbe, 0x52, 0x82,
    0xdc, 0xdc, 0x6c, 0x7f, 0xec, 0xa4, 0xf1, 0xe7, 0x09, 0xdd, 0x60, 0x48,
    0xf1, 0xbc, 0xa0, 0xaa, 0xd6, 0x89, 0xfd, 0x65, 0xfa, 0xb1, 0x57, 0xc4,
    0x4a, 0x0a, 0x2a, 0x8c, 0x62, 0x77, 0xc5, 0x01, 0x37, 0xe9, 0x96, 0x56,
    0xd3, 0xf6, 0xd7, 0x09, 0xd8, 0x21, 0x5b, 0x2f, 0xb7, 0x60, 0x50, 0x64,
    0xf1, 0x16, 0x27, 0x36, 0xfa, 0xb4, 0xfd, 0xc9, 0x63, 0x8d, 0xe0, 0x9e,
    0x6d, 0x61, 0x72, 0x2b, 0x84, 0x16, 0x42, 0x5b, 0x27, 0x37, 0xac, 0xb2,
    0x38, 0x6b, 0xd0, 0xd9, 0x05, 0x32, 0x52, 0x72, 0x13, 0x41, 0x27, 0x49,
    0x8c, 0xd0, 0x9d, 0x05, 0xda, 0xda, 0xe3, 0x4f, 0x02, 0x6a, 0x1c, 0xd5,
    0x46, 0x05, 0x0f, 0x5e, 0x64, 0xd9, 0x87, 0xf7, 0x6f, 0xd2, 0x78, 0xdc,
    0x30, 0x5c, 0x84, 0xa2, 0x74, 0x14, 0x16, 0xfc, 0xe4, 0x2d, 0xf1, 0x67,
    0xcb, 0xc5, 0x2f, 0x81, 0x28, 0xa8, 0x51, 0x18, 0x58, 0xa2, 0x38, 0x8a,
    0x55, 0xc7, 0xa8, 0x2a, 0x70, 0xa3, 0xb5, 0x4c, 0x7b, 0x25, 0xdb, 0xdd,
    0xdb, 0x85, 0x3e, 0xa4, 0xba, 0xae, 0xf9, 0x7e, 0x22, 0xa0, 0xa0, 0xaa,
    0xe8, 0x79, 0x87, 0x46, 0x10, 0x60, 0xf8, 0x10, 0x96, 0x57, 0x16, 0x28,
    0x57, 0x4b, 0x64, 0x51, 0x10, 0x29, 0xb3, 0x39, 0x07, 0xd9, 0xe1, 0xfe,
    0xe1, 0x65, 0x70, 0xd2, 0x25, 0x55, 0x85, 0x39, 0x24, 0x08, 0xf4, 0x0a,
    0x26, 0x07, 0x11, 0xc4, 0x28, 0x3a, 0xb3, 0xd9, 0x9f, 0xbf, 0xf2, 0x9a,
    0xc4, 0xa8, 0xf9, 0x7d, 0xf2, 0xe4, 0x4a, 0x7b, 0x21, 0x2a, 0xc8, 0xad,
    0xe1, 0xb9, 0xfe, 0x06, 0x04, 0xb4, 0x64, 0xe5, 0xb5, 0x8c, 0xd0, 0x3a,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
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

  mpHBoxLayoutInitialExpression = new QHBoxLayout(0, 0, 6, "mpHBoxLayoutInitialExpression");

  mpEditInitialExpression = new CQExpressionWidget(this, "mpEditInitialExpression");
  mpEditInitialExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialExpression->sizePolicy().hasHeightForWidth()));
  mpHBoxLayoutInitialExpression->addWidget(mpEditInitialExpression);

  mpVBoxLayoutInitialExpression = new QVBoxLayout(0, 0, 6, "mpVBoxLayoutInitialExpression");

  mpBtnObjectInitialExpression = new QToolButton(this, "mpBtnObjectInitialExpression");
  mpBtnObjectInitialExpression->setMaximumSize(QSize(20, 20));
  mpBtnObjectInitialExpression->setIconSet(QIconSet(image0));
  mpVBoxLayoutInitialExpression->addWidget(mpBtnObjectInitialExpression);
  mpSpacerObjectInitialExpression = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpVBoxLayoutInitialExpression->addItem(mpSpacerObjectInitialExpression);
  mpHBoxLayoutInitialExpression->addLayout(mpVBoxLayoutInitialExpression);

  CQMetaboliteLayout->addMultiCellLayout(mpHBoxLayoutInitialExpression, 5, 5, 1, 2);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblExpression, 3, 0);

  mpHBoxLayoutExpression = new QHBoxLayout(0, 0, 6, "mpHBoxLayoutExpression");

  mpEditExpression = new CQExpressionWidget(this, "mpEditExpression");
  mpEditExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpEditExpression->sizePolicy().hasHeightForWidth()));
  mpHBoxLayoutExpression->addWidget(mpEditExpression);

  mpVBoxLayoutExpression = new QVBoxLayout(0, 0, 6, "mpVBoxLayoutExpression");

  mpBtnObjectExpression = new QToolButton(this, "mpBtnObjectExpression");
  mpBtnObjectExpression->setMaximumSize(QSize(20, 20));
  mpBtnObjectExpression->setIconSet(QIconSet(image0));
  mpVBoxLayoutExpression->addWidget(mpBtnObjectExpression);
  mpSpacerObjectExpression = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpVBoxLayoutExpression->addItem(mpSpacerObjectExpression);
  mpHBoxLayoutExpression->addLayout(mpVBoxLayoutExpression);

  CQMetaboliteLayout->addMultiCellLayout(mpHBoxLayoutExpression, 3, 3, 1, 2);

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
  mpSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQMetaboliteLayout->addItem(mpSpacer, 11, 1);

  mpLine2 = new QFrame(this, "mpLine2");
  mpLine2->setFrameShape(QFrame::HLine);
  mpLine2->setFrameShadow(QFrame::Sunken);
  mpLine2->setFrameShape(QFrame::HLine);

  CQMetaboliteLayout->addMultiCellWidget(mpLine2, 12, 12, 0, 2);
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
  connect(mpBtnObjectExpression, SIGNAL(clicked()), mpEditExpression, SLOT(slotSelectObject()));
  connect(mpEditExpression, SIGNAL(valid(bool)), this, SLOT(slotExpressionValid(bool)));
  connect(mpEditInitialExpression, SIGNAL(valid(bool)), this, SLOT(slotInitialExpressionValid(bool)));
  connect(mpEditInitialValue, SIGNAL(lostFocus()), this, SLOT(slotInitialValueLostFocus()));
  connect(mpReactionTable, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(slotReactionTableCurrentChanged(QListViewItem*)));
  connect(mpBoxUseInitialExpression, SIGNAL(toggled(bool)), this, SLOT(slotInitialTypeChanged(bool)));
  connect(mpBtnObjectInitialExpression, SIGNAL(pressed()), mpEditInitialExpression, SLOT(slotSelectObject()));
  connect(mpEditName, SIGNAL(lostFocus()), this, SLOT(slotNameLostFocus()));

  // tab order
  setTabOrder(mpEditName, mpComboBoxCompartment);
  setTabOrder(mpComboBoxCompartment, mpComboBoxType);
  setTabOrder(mpComboBoxType, mpEditExpression);
  setTabOrder(mpEditExpression, mpBtnObjectExpression);
  setTabOrder(mpBtnObjectExpression, mpEditInitialValue);
  setTabOrder(mpEditInitialValue, mpBoxUseInitialExpression);
  setTabOrder(mpBoxUseInitialExpression, mpEditInitialExpression);
  setTabOrder(mpEditInitialExpression, mpBtnObjectInitialExpression);
  setTabOrder(mpBtnObjectInitialExpression, mpEditCurrentValue);
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
  setCaption(tr("Species"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
  mpLblType->setText(tr("Simulation Type"));
  mpLblCompartment->setText(tr("Compartment"));
  mpLblName->setText(tr("Species Name"));
  mpLblInitialExpression->setText(tr("Initial Expression"));
  mpBoxUseInitialExpression->setText(tr("Use Initial Expression"));
  mpLblInitialValue->setText(tr("Initial Value"));
  mpBtnObjectInitialExpression->setText(QString::null);
  mpBtnObjectInitialExpression->setTextLabel(tr("select"));
  mpLblExpression->setText(tr("Expression"));
  mpBtnObjectExpression->setText(QString::null);
  mpBtnObjectExpression->setTextLabel(tr("select"));
  mpLblReactions->setText(tr("Involved in Reactions"));
  mpReactionTable->header()->setLabel(0, tr("Name"));
  mpReactionTable->header()->setLabel(1, tr("Equation"));
  mpLblValue->setText(tr("Concentration"));
  mpLblTransitionTime->setText(tr("Transition Time"));
  mpLblRate->setText(tr("Rate"));
}
