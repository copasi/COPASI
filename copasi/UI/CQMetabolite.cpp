// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/08/03 13:46:40 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Fri Aug 3 09:37:33 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.cpp,v 1.1 2007/08/03 13:46:40 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQMetabolite.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qtable.h>
#include <qframe.h>
#include <qtoolbutton.h>
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
    0x6b, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0x95, 0x93, 0xb1, 0x6b, 0x53,
    0x51, 0x18, 0xc5, 0x7f, 0xb7, 0x64, 0xb8, 0x81, 0x37, 0xbc, 0x40, 0x84,
    0x3c, 0x48, 0xa1, 0x17, 0x2a, 0xf4, 0x49, 0x05, 0x5f, 0xd0, 0x21, 0xc1,
    0xc1, 0x06, 0xba, 0x04, 0x5c, 0xea, 0xd8, 0x49, 0x57, 0xf1, 0x4f, 0xf1,
    0x3f, 0x70, 0x93, 0x76, 0x51, 0xb2, 0x08, 0x71, 0x10, 0x9f, 0x43, 0x69,
    0x32, 0x54, 0xf3, 0x0a, 0x85, 0x3c, 0xc1, 0xc2, 0xcd, 0x94, 0x9b, 0xe1,
    0xc1, 0xbb, 0xc3, 0x83, 0xde, 0x21, 0x70, 0x1d, 0x6a, 0x4b, 0xab, 0x28,
    0x38, 0x7d, 0x1c, 0xbe, 0xc3, 0x39, 0x70, 0x38, 0x47, 0x2c, 0x66, 0x0b,
    0xb0, 0x40, 0x08, 0xc6, 0x1a, 0xa2, 0x30, 0xfa, 0x2f, 0xbc, 0xa6, 0xad,
    0x86, 0x10, 0xb4, 0xd5, 0x44, 0x61, 0xc4, 0x4d, 0xac, 0x5a, 0x78, 0x53,
    0x4d, 0x7d, 0x49, 0xee, 0xd3, 0xec, 0xc0, 0xbb, 0x4a, 0xfb, 0xdf, 0xf9,
    0x62, 0x31, 0x5b, 0xfc, 0xa1, 0x5c, 0x32, 0xf5, 0x8d, 0x55, 0xc4, 0xf0,
    0x28, 0x85, 0x22, 0xc2, 0x38, 0x4d, 0xb2, 0xa9, 0x90, 0x77, 0x1c, 0xfd,
    0x87, 0x5d, 0xf2, 0xb9, 0x13, 0x57, 0x7c, 0x71, 0x3c, 0x3e, 0x46, 0x85,
    0xea, 0xd2, 0x31, 0x54, 0x18, 0x97, 0x7b, 0x9b, 0x5f, 0x30, 0xfa, 0x9a,
    0x11, 0x07, 0x8a, 0x30, 0x71, 0xf4, 0xb7, 0xfb, 0x68, 0x3b, 0x43, 0x35,
    0x23, 0xf2, 0xa5, 0x13, 0x37, 0xf9, 0xe2, 0x66, 0x06, 0xd3, 0xf9, 0xd8,
    0x2f, 0xcf, 0x60, 0x3a, 0xcf, 0xe9, 0x3f, 0x50, 0x34, 0x14, 0xc4, 0xed,
    0xbe, 0xf8, 0x57, 0x06, 0xb5, 0x2b, 0xa5, 0xf4, 0x64, 0xe4, 0xb3, 0xd3,
    0x12, 0x29, 0x61, 0xff, 0x69, 0x0f, 0x42, 0x79, 0xcb, 0xe9, 0x6f, 0x57,
    0x2c, 0x66, 0x0b, 0xd2, 0x93, 0xd4, 0xdb, 0x39, 0xc8, 0xa6, 0x65, 0xb0,
    0x3b, 0xc0, 0x14, 0xa5, 0xb8, 0x95, 0x49, 0x95, 0x7a, 0x25, 0x23, 0x96,
    0xd9, 0x88, 0x8b, 0x55, 0x88, 0xab, 0x59, 0x3a, 0xdd, 0x3d, 0x4c, 0xa1,
    0x84, 0x78, 0x3f, 0x7c, 0xe3, 0x27, 0x47, 0x25, 0x6a, 0xa3, 0xce, 0xde,
    0x4e, 0x82, 0xae, 0xb8, 0x76, 0x8e, 0x65, 0xe9, 0xf3, 0xf3, 0x09, 0x9c,
    0xe5, 0x64, 0x73, 0x90, 0x4e, 0x92, 0x5f, 0x40, 0xab, 0xee, 0x50, 0x6d,
    0xc7, 0xb3, 0xe7, 0x2f, 0xa8, 0xd9, 0x1f, 0x25, 0x32, 0xb0, 0xec, 0x74,
    0x7b, 0x98, 0x4a, 0x0a, 0xf5, 0xcb, 0x39, 0xae, 0x72, 0x3f, 0xfa, 0x90,
    0xe2, 0xac, 0xc2, 0xd0, 0xa2, 0xf7, 0xf8, 0x1e, 0x72, 0x5d, 0xb2, 0xd7,
    0x8e, 0xb1, 0xe7, 0x19, 0xd3, 0xa3, 0x19, 0xe9, 0xc7, 0x43, 0xd6, 0xc6,
    0xe7, 0x19, 0x49, 0x4b, 0x61, 0x57, 0x88, 0xeb, 0x1e, 0xe8, 0xa1, 0x3f,
    0x7c, 0x3b, 0xc4, 0x58, 0x89, 0x7c, 0x20, 0x79, 0xf9, 0xea, 0x25, 0xf2,
    0x7e, 0x22, 0xd4, 0xc6, 0x40, 0xe4, 0x15, 0x42, 0xb6, 0x13, 0xb2, 0xc2,
    0x22, 0x6d, 0x49, 0x4d, 0x05, 0x8a, 0xe5, 0xca, 0xd0, 0x0b, 0x07, 0x60,
    0xa1, 0xd7, 0x96, 0xfe, 0xe0, 0xed, 0x88, 0x56, 0x3b, 0xa1, 0xb7, 0x9b,
    0x40, 0xab, 0x27, 0xb4, 0x35, 0xa8, 0x50, 0x81, 0x05, 0xb5, 0x2a, 0xfd,
    0xc1, 0xbb, 0x2f, 0xc4, 0xa1, 0x22, 0x7a, 0x94, 0x50, 0x73, 0xb2, 0xc4,
    0x14, 0x0d, 0xa6, 0xe7, 0x23, 0xdf, 0xd9, 0x1c, 0x08, 0xbd, 0xcc, 0x08,
    0xdd, 0x05, 0xcb, 0x9a, 0x46, 0x06, 0x09, 0xb6, 0x18, 0xfa, 0x4e, 0xd0,
    0x62, 0x36, 0x4f, 0x71, 0x67, 0x39, 0x93, 0x53, 0x0d, 0x35, 0x45, 0xf8,
    0x24, 0x46, 0x6e, 0xed, 0x0b, 0xf1, 0x2d, 0xfd, 0xec, 0x0f, 0x3f, 0x8c,
    0x49, 0x36, 0x22, 0xe4, 0x3a, 0x74, 0xda, 0x2d, 0xc6, 0x9f, 0x5e, 0x23,
    0x97, 0x16, 0x9d, 0x43, 0x54, 0x29, 0x0c, 0x86, 0x46, 0x10, 0x93, 0x07,
    0x8e, 0xee, 0xa3, 0x84, 0xf8, 0x6e, 0x9d, 0xc6, 0xf6, 0x9e, 0x30, 0xd6,
    0x5c, 0x36, 0x31, 0xaa, 0xe1, 0x47, 0x93, 0x11, 0xb3, 0xef, 0x12, 0x57,
    0x01, 0xab, 0x06, 0xb6, 0x9c, 0x41, 0x05, 0xac, 0xa0, 0xab, 0xa0, 0xbe,
    0x55, 0xa7, 0xdb, 0xed, 0xe2, 0xa4, 0x43, 0x35, 0xfb, 0xe2, 0x56, 0x0f,
    0x8c, 0x35, 0xa8, 0x26, 0xde, 0x15, 0x06, 0x82, 0x08, 0x5d, 0x19, 0x54,
    0x10, 0xe1, 0xac, 0x41, 0x86, 0x8a, 0x72, 0x65, 0x89, 0x02, 0x89, 0x2b,
    0x22, 0xf1, 0x7b, 0x23, 0xd7, 0xae, 0x56, 0x95, 0x17, 0x4e, 0x10, 0x76,
    0x84, 0xae, 0x9c, 0x50, 0xbf, 0xae, 0x6c, 0x76, 0x84, 0xae, 0xac, 0x68,
    0x48, 0x25, 0x2e, 0xff, 0x7f, 0xae, 0xf6, 0x27, 0xba, 0x25, 0x79, 0xd7,
    0xd6, 0x1f, 0xa3, 0x6b, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44,
    0xae, 0x42, 0x60, 0x82
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
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)4, 0, 0, sizePolicy().hasHeightForWidth()));
  CQMetaboliteLayout = new QVBoxLayout(this, 11, 6, "CQMetaboliteLayout");

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpLblConcentration = new QLabel(this, "mpLblConcentration");
  mpLblConcentration->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblConcentration->sizePolicy().hasHeightForWidth()));
  mpLblConcentration->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblConcentration, 5, 0);

  mpComboBoxType = new QComboBox(FALSE, this, "mpComboBoxType");
  mpComboBoxType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxType->sizePolicy().hasHeightForWidth()));

  mpGridLayout->addWidget(mpComboBoxType, 2, 1);

  mpEditName = new QLineEdit(this, "mpEditName");
  mpEditName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpEditName->sizePolicy().hasHeightForWidth()));
  mpEditName->setFrameShape(QLineEdit::LineEditPanel);
  mpEditName->setFrameShadow(QLineEdit::Sunken);

  mpGridLayout->addMultiCellWidget(mpEditName, 0, 0, 1, 2);

  mpLblReactions = new QLabel(this, "mpLblReactions");
  mpLblReactions->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblReactions->sizePolicy().hasHeightForWidth()));
  mpLblReactions->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblReactions, 10, 0);

  mpReactionTable = new QTable(this, "mpReactionTable");
  mpReactionTable->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpReactionTable->sizePolicy().hasHeightForWidth()));
  mpReactionTable->setNumRows(1);
  mpReactionTable->setNumCols(2);
  mpReactionTable->setShowGrid(FALSE);
  mpReactionTable->setReadOnly(TRUE);
  mpReactionTable->setSelectionMode(QTable::NoSelection);

  mpGridLayout->addMultiCellWidget(mpReactionTable, 10, 10, 1, 2);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblType, 2, 0);

  mpEditCurrentConcentration = new QLineEdit(this, "mpEditCurrentConcentration");
  mpEditCurrentConcentration->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditCurrentConcentration->sizePolicy().hasHeightForWidth()));
  mpEditCurrentConcentration->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentConcentration->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentConcentration->setReadOnly(TRUE);

  mpGridLayout->addWidget(mpEditCurrentConcentration, 5, 2);

  mpLblTransitionTime = new QLabel(this, "mpLblTransitionTime");
  mpLblTransitionTime->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblTransitionTime->sizePolicy().hasHeightForWidth()));
  mpLblTransitionTime->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblTransitionTime, 7, 0);

  mpEditInitialNumber = new QLineEdit(this, "mpEditInitialNumber");
  mpEditInitialNumber->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialNumber->sizePolicy().hasHeightForWidth()));
  mpEditInitialNumber->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialNumber->setFrameShadow(QLineEdit::Sunken);

  mpGridLayout->addWidget(mpEditInitialNumber, 6, 1);

  mpLine1 = new QFrame(this, "mpLine1");
  mpLine1->setFrameShape(QFrame::HLine);
  mpLine1->setFrameShadow(QFrame::Sunken);
  mpLine1->setFrameShape(QFrame::HLine);

  mpGridLayout->addMultiCellWidget(mpLine1, 3, 3, 0, 2);

  mpComboBoxCompartment = new QComboBox(FALSE, this, "mpComboBoxCompartment");
  mpComboBoxCompartment->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxCompartment->sizePolicy().hasHeightForWidth()));

  mpGridLayout->addMultiCellWidget(mpComboBoxCompartment, 1, 1, 1, 2);

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblName->sizePolicy().hasHeightForWidth()));
  mpLblName->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblName, 0, 0);

  mpLblCompartment = new QLabel(this, "mpLblCompartment");
  mpLblCompartment->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblCompartment->sizePolicy().hasHeightForWidth()));
  mpLblCompartment->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblCompartment, 1, 0);

  mpLblConcentrationRate = new QLabel(this, "mpLblConcentrationRate");
  mpLblConcentrationRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblConcentrationRate->sizePolicy().hasHeightForWidth()));
  mpLblConcentrationRate->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblConcentrationRate, 8, 0);

  mpLayoutInitialConcentration = new QVBoxLayout(0, 0, 6, "mpLayoutInitialConcentration");

  mpEditInitialConcentration = new QLineEdit(this, "mpEditInitialConcentration");
  mpEditInitialConcentration->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialConcentration->sizePolicy().hasHeightForWidth()));
  mpEditInitialConcentration->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialConcentration->setFrameShadow(QLineEdit::Sunken);
  mpLayoutInitialConcentration->addWidget(mpEditInitialConcentration);

  mpComboBoxInitialSelection = new QComboBox(FALSE, this, "mpComboBoxInitialSelection");
  mpComboBoxInitialSelection->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxInitialSelection->sizePolicy().hasHeightForWidth()));
  mpLayoutInitialConcentration->addWidget(mpComboBoxInitialSelection);

  mpGridLayout->addLayout(mpLayoutInitialConcentration, 5, 1);

  mpEditCurrentNumber = new QLineEdit(this, "mpEditCurrentNumber");
  mpEditCurrentNumber->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditCurrentNumber->sizePolicy().hasHeightForWidth()));
  mpEditCurrentNumber->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentNumber->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentNumber->setReadOnly(TRUE);

  mpGridLayout->addWidget(mpEditCurrentNumber, 6, 2);

  mpEditTransitionTime = new QLineEdit(this, "mpEditTransitionTime");
  mpEditTransitionTime->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditTransitionTime->sizePolicy().hasHeightForWidth()));
  mpEditTransitionTime->setFrameShape(QLineEdit::LineEditPanel);
  mpEditTransitionTime->setFrameShadow(QLineEdit::Sunken);
  mpEditTransitionTime->setReadOnly(TRUE);

  mpGridLayout->addWidget(mpEditTransitionTime, 7, 2);

  mpEditConcentrationRate = new QLineEdit(this, "mpEditConcentrationRate");
  mpEditConcentrationRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditConcentrationRate->sizePolicy().hasHeightForWidth()));
  mpEditConcentrationRate->setFrameShape(QLineEdit::LineEditPanel);
  mpEditConcentrationRate->setFrameShadow(QLineEdit::Sunken);
  mpEditConcentrationRate->setReadOnly(TRUE);

  mpGridLayout->addWidget(mpEditConcentrationRate, 8, 2);

  mpHBoxLayout = new QHBoxLayout(0, 0, 6, "mpHBoxLayout");

  mpEditExpression = new CQExpressionWidget(this, "mpEditExpression");
  mpHBoxLayout->addWidget(mpEditExpression);

  mpVBoxLayout = new QVBoxLayout(0, 0, 6, "mpVBoxLayout");

  mpBtnObject = new QToolButton(this, "mpBtnObject");
  mpBtnObject->setMaximumSize(QSize(20, 20));
  mpBtnObject->setIconSet(QIconSet(image0));
  mpVBoxLayout->addWidget(mpBtnObject);
  mpSpacerObject = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpVBoxLayout->addItem(mpSpacerObject);
  mpHBoxLayout->addLayout(mpVBoxLayout);

  mpGridLayout->addMultiCellLayout(mpHBoxLayout, 9, 9, 1, 2);

  mpLblNumber = new QLabel(this, "mpLblNumber");
  mpLblNumber->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblNumber->sizePolicy().hasHeightForWidth()));
  mpLblNumber->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblNumber, 6, 0);

  mpLayoutInitialValues = new QHBoxLayout(0, 0, 6, "mpLayoutInitialValues");

  mpLblInitialValue = new QLabel(this, "mpLblInitialValue");
  mpLblInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblInitialValue->sizePolicy().hasHeightForWidth()));
  mpLblInitialValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignLeft));
  mpLayoutInitialValues->addWidget(mpLblInitialValue);

  mpComboBoxInitialType = new QComboBox(FALSE, this, "mpComboBoxInitialType");
  mpComboBoxInitialType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxInitialType->sizePolicy().hasHeightForWidth()));
  mpLayoutInitialValues->addWidget(mpComboBoxInitialType);

  mpGridLayout->addLayout(mpLayoutInitialValues, 4, 1);

  mpLblTransientValue = new QLabel(this, "mpLblTransientValue");
  mpLblTransientValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpLblTransientValue->sizePolicy().hasHeightForWidth()));
  mpLblTransientValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignLeft));

  mpGridLayout->addWidget(mpLblTransientValue, 4, 2);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblExpression, 9, 0);
  CQMetaboliteLayout->addLayout(mpGridLayout);
  mpSpacer = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);
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
  resize(QSize(611, 474).expandedTo(minimumSizeHint()));
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
  connect(mpReactionTable, SIGNAL(doubleClicked(int, int, int, const QPoint&)), this, SLOT(slotReactionTableCurrentChanged(int, int, int, const QPoint&)));
  connect(mpEditInitialConcentration, SIGNAL(textChanged(const QString&)), this, SLOT(slotInitialConcentrationChanged(const QString&)));
  connect(mpEditInitialNumber, SIGNAL(textChanged(const QString&)), this, SLOT(slotInitialNumberChanged(const QString&)));

  // tab order
  setTabOrder(mpEditName, mpComboBoxCompartment);
  setTabOrder(mpComboBoxCompartment, mpComboBoxType);
  setTabOrder(mpComboBoxType, mpComboBoxInitialType);
  setTabOrder(mpComboBoxInitialType, mpEditInitialConcentration);
  setTabOrder(mpEditInitialConcentration, mpComboBoxInitialSelection);
  setTabOrder(mpComboBoxInitialSelection, mpEditCurrentConcentration);
  setTabOrder(mpEditCurrentConcentration, mpEditInitialNumber);
  setTabOrder(mpEditInitialNumber, mpEditCurrentNumber);
  setTabOrder(mpEditCurrentNumber, mpEditTransitionTime);
  setTabOrder(mpEditTransitionTime, mpEditConcentrationRate);
  setTabOrder(mpEditConcentrationRate, mpEditExpression);
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
  setCaption(tr("Form1"));
  mpLblConcentration->setText(tr("Concentration"));
  mpLblReactions->setText(tr("Involved in Reactions"));
  mpLblType->setText(tr("Type"));
  mpLblTransitionTime->setText(tr("Transition Time"));
  mpLblName->setText(tr("Metobolite Name"));
  mpLblCompartment->setText(tr("Compartment"));
  mpLblConcentrationRate->setText(tr("Concentration Rate"));
  mpBtnObject->setText(QString::null);
  mpBtnObject->setTextLabel(tr("select"));
  mpLblNumber->setText(tr("Particle Number"));
  mpLblInitialValue->setText(tr("Initial Values"));
  mpLblTransientValue->setText(tr("Transient Values"));
  mpLblExpression->setText(tr("Expression"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
}
