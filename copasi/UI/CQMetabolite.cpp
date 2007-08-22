// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/08/22 19:52:19 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMetabolite.ui'
 **
 ** Created: Wed Aug 22 15:41:07 2007
 **      by: The User Interface Compiler ($Id: CQMetabolite.cpp,v 1.4 2007/08/22 19:52:19 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQMetabolite.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qtoolbutton.h>
#include <qheader.h>
#include <qlistview.h>
#include <qframe.h>
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
    0x88, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x95, 0x93, 0x31, 0x68, 0x13,
    0x71, 0x14, 0xc6, 0x7f, 0xff, 0xd2, 0xa1, 0x81, 0x14, 0x22, 0x28, 0xa4,
    0xd0, 0xe1, 0x0e, 0x1c, 0x1a, 0xc9, 0x60, 0x03, 0x82, 0x1e, 0x2e, 0x06,
    0x1d, 0x5a, 0x27, 0x53, 0x5c, 0x52, 0x9d, 0x3a, 0xc6, 0x45, 0x14, 0x1c,
    0xac, 0x83, 0x88, 0xb8, 0xd4, 0x49, 0x32, 0x08, 0xad, 0x0e, 0x7a, 0x2e,
    0xd6, 0x38, 0xd8, 0xd4, 0xa1, 0x34, 0x05, 0x25, 0xff, 0x82, 0xb4, 0x97,
    0x82, 0xd8, 0x73, 0x28, 0xbd, 0xa3, 0x86, 0x5c, 0x90, 0x92, 0x3b, 0xb0,
    0x98, 0x1b, 0x0a, 0xcf, 0xa1, 0xda, 0xd2, 0x0a, 0x82, 0xd3, 0xc7, 0xe3,
    0x7d, 0xf0, 0xde, 0xfb, 0xf1, 0x3e, 0xa4, 0x25, 0x88, 0x16, 0xa4, 0x25,
    0xac, 0xea, 0x55, 0xfe, 0xb7, 0xee, 0xd1, 0xbe, 0x06, 0x03, 0xb4, 0xaf,
    0xc9, 0x19, 0x39, 0x0e, 0xd5, 0x43, 0xa6, 0x38, 0xcd, 0xaa, 0x74, 0x53,
    0x9e, 0xd8, 0x4b, 0x53, 0x32, 0xd0, 0x8b, 0x1c, 0xf5, 0x2b, 0x69, 0x09,
    0x8e, 0xef, 0x90, 0x33, 0x72, 0xe0, 0x03, 0x06, 0xac, 0x47, 0x55, 0x39,
    0x95, 0xb4, 0x28, 0xbf, 0x9b, 0xc1, 0xd8, 0xb5, 0x58, 0x6e, 0xd7, 0x28,
    0x9c, 0xc9, 0x13, 0xf4, 0xba, 0x5c, 0xbe, 0x58, 0xc4, 0x59, 0x73, 0xd5,
    0xbe, 0xbf, 0xae, 0xeb, 0x48, 0x4b, 0xf6, 0x75, 0xd5, 0x59, 0x94, 0x4d,
    0xfb, 0x8b, 0xdc, 0xba, 0xf9, 0x40, 0x16, 0xef, 0xd5, 0x65, 0xb6, 0x32,
    0x2d, 0xf2, 0x5d, 0x64, 0xf5, 0xd3, 0x9c, 0x48, 0xa7, 0x23, 0x47, 0xfd,
    0x4a, 0x5a, 0xb2, 0x3f, 0xb9, 0xba, 0xf6, 0x46, 0x12, 0xdf, 0x4c, 0xde,
    0xac, 0xcd, 0x33, 0x71, 0x21, 0x4f, 0x94, 0xf2, 0xc8, 0x67, 0xc7, 0xd5,
    0x9f, 0xfe, 0xd1, 0x4d, 0x1d, 0xdf, 0x39, 0x60, 0x60, 0x2f, 0xcc, 0xc8,
    0xd2, 0x82, 0x47, 0xcd, 0xaf, 0x31, 0x79, 0x7d, 0x9c, 0x78, 0x10, 0x95,
    0xcf, 0x8e, 0xab, 0x7f, 0x32, 0xfa, 0xc3, 0xc0, 0x5e, 0xb0, 0x25, 0x15,
    0x99, 0xb4, 0x7b, 0x1b, 0x4c, 0x5c, 0x2d, 0xe1, 0x6c, 0x38, 0xea, 0x10,
    0x93, 0xa6, 0x2d, 0xa7, 0xd2, 0x16, 0x2c, 0x95, 0xe9, 0xf6, 0x0f, 0xe3,
    0xfe, 0x68, 0x90, 0x1b, 0xb9, 0x05, 0x1b, 0x03, 0x4a, 0xcd, 0x56, 0xa6,
    0x65, 0xf9, 0x63, 0x88, 0x69, 0x24, 0x28, 0x5d, 0x29, 0xa0, 0x9b, 0x9e,
    0xb2, 0x0c, 0x0b, 0xed, 0x6b, 0xac, 0x74, 0x4a, 0xf4, 0xca, 0x2b, 0xcc,
    0xcf, 0x2e, 0x15, 0x1f, 0x32, 0x71, 0x1f, 0xf3, 0x5d, 0x48, 0x27, 0x62,
    0xcc, 0xc1, 0x98, 0xb1, 0x9b, 0x0f, 0x50, 0x8b, 0x4f, 0x67, 0xa5, 0xd6,
    0x6c, 0x70, 0xf7, 0x7a, 0x09, 0x77, 0x3b, 0x38, 0x98, 0xdc, 0x5b, 0x13,
    0xfb, 0xed, 0x0c, 0x03, 0xe4, 0xd1, 0x91, 0xc3, 0xf8, 0x85, 0x51, 0x82,
    0x64, 0x1b, 0x2b, 0x3b, 0x0a, 0x2b, 0x15, 0x9c, 0xcf, 0x5d, 0xa2, 0xbe,
    0x65, 0x7a, 0xec, 0x95, 0x0a, 0x85, 0x74, 0x9e, 0xc6, 0xb6, 0xa7, 0xf6,
    0x6f, 0xf4, 0xaa, 0x52, 0x7e, 0xf2, 0x98, 0x20, 0xea, 0x23, 0x30, 0x02,
    0x26, 0xef, 0x4d, 0x11, 0x0c, 0x1e, 0x53, 0xd6, 0xe9, 0x09, 0xa5, 0x9b,
    0x9e, 0x22, 0x5b, 0xa0, 0xb2, 0xd1, 0x20, 0x13, 0x85, 0xa8, 0x97, 0xf7,
    0xa7, 0x25, 0x4a, 0x05, 0x94, 0xae, 0x4e, 0xee, 0xd1, 0xce, 0x86, 0x62,
    0xdf, 0xb9, 0x46, 0xc6, 0x28, 0x90, 0x3b, 0x93, 0x82, 0xa1, 0x31, 0x75,
    0x88, 0x7e, 0x72, 0x5d, 0xa6, 0x9e, 0x3f, 0xc3, 0x4a, 0x66, 0xb0, 0x86,
    0x43, 0x7a, 0xdc, 0xd8, 0x21, 0xd8, 0x8e, 0xa9, 0xae, 0xcc, 0x08, 0x06,
    0x78, 0x5f, 0x2b, 0x0c, 0xc7, 0x5d, 0x1a, 0x3b, 0x35, 0x18, 0x34, 0xf1,
    0x36, 0xca, 0x92, 0x4b, 0x23, 0xeb, 0x6b, 0x53, 0x12, 0x7e, 0x9c, 0x90,
    0xf2, 0xa3, 0x1b, 0xb0, 0x1d, 0x12, 0x1a, 0x21, 0x9c, 0xbd, 0xad, 0x54,
    0xc7, 0xd9, 0x94, 0x87, 0x2f, 0x6c, 0x0a, 0xa7, 0x2d, 0x82, 0x7e, 0x8f,
    0xb1, 0xec, 0x39, 0xec, 0xd7, 0x37, 0xc8, 0xc4, 0x11, 0xb5, 0x65, 0xb0,
    0x76, 0xf2, 0x68, 0x34, 0xb9, 0xe4, 0x28, 0xf3, 0x49, 0x97, 0xe2, 0xa5,
    0x02, 0x99, 0x13, 0x6d, 0x12, 0xe7, 0x4b, 0xca, 0xf1, 0x1d, 0x54, 0x5d,
    0xd7, 0xb1, 0x8e, 0x9b, 0x52, 0x7e, 0x5f, 0x66, 0xfd, 0x6b, 0x1f, 0xf1,
    0x0e, 0xb0, 0x3b, 0x4c, 0x14, 0xce, 0xc3, 0x0e, 0xb0, 0x0b, 0x45, 0x13,
    0xda, 0x43, 0x09, 0x8a, 0x23, 0x45, 0xdc, 0xd8, 0xc5, 0x3a, 0xb9, 0xf7,
    0x1f, 0x96, 0x61, 0x71, 0x90, 0xb2, 0xef, 0x1d, 0x11, 0x3d, 0x27, 0xb2,
    0xd5, 0x91, 0xfa, 0x6f, 0x95, 0x0f, 0x73, 0x22, 0x5b, 0x3f, 0xe5, 0x8b,
    0x53, 0x97, 0xbd, 0xfe, 0xdf, 0xa9, 0xfc, 0x2b, 0x0b, 0xff, 0xab, 0xbf,
    0x00, 0xdc, 0xb5, 0xe7, 0xb3, 0xf4, 0x1c, 0xc6, 0x09, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
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

  mpEditName = new QLineEdit(this, "mpEditName");
  mpEditName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpEditName->sizePolicy().hasHeightForWidth()));
  mpEditName->setFrameShape(QLineEdit::LineEditPanel);
  mpEditName->setFrameShadow(QLineEdit::Sunken);

  CQMetaboliteLayout->addMultiCellWidget(mpEditName, 0, 0, 1, 2);

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblName->sizePolicy().hasHeightForWidth()));
  mpLblName->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblName, 0, 0);

  mpComboBoxCompartment = new QComboBox(FALSE, this, "mpComboBoxCompartment");
  mpComboBoxCompartment->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxCompartment->sizePolicy().hasHeightForWidth()));

  CQMetaboliteLayout->addMultiCellWidget(mpComboBoxCompartment, 1, 1, 1, 2);

  mpLblCompartment = new QLabel(this, "mpLblCompartment");
  mpLblCompartment->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblCompartment->sizePolicy().hasHeightForWidth()));
  mpLblCompartment->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblCompartment, 1, 0);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblType, 2, 0);

  mpComboBoxType = new QComboBox(FALSE, this, "mpComboBoxType");
  mpComboBoxType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxType->sizePolicy().hasHeightForWidth()));

  CQMetaboliteLayout->addWidget(mpComboBoxType, 2, 1);

  mpLayoutInitialValues = new QHBoxLayout(0, 0, 6, "mpLayoutInitialValues");

  mpLblInitialValue = new QLabel(this, "mpLblInitialValue");
  mpLblInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblInitialValue->sizePolicy().hasHeightForWidth()));
  mpLblInitialValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignLeft));
  mpLayoutInitialValues->addWidget(mpLblInitialValue);

  mpComboBoxInitialType = new QComboBox(FALSE, this, "mpComboBoxInitialType");
  mpComboBoxInitialType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxInitialType->sizePolicy().hasHeightForWidth()));
  mpLayoutInitialValues->addWidget(mpComboBoxInitialType);

  CQMetaboliteLayout->addLayout(mpLayoutInitialValues, 4, 1);

  mpLblTransientValue = new QLabel(this, "mpLblTransientValue");
  mpLblTransientValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpLblTransientValue->sizePolicy().hasHeightForWidth()));
  mpLblTransientValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignLeft));

  CQMetaboliteLayout->addWidget(mpLblTransientValue, 4, 2);

  mpLblConcentration = new QLabel(this, "mpLblConcentration");
  mpLblConcentration->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblConcentration->sizePolicy().hasHeightForWidth()));
  mpLblConcentration->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblConcentration, 5, 0);

  mpEditCurrentConcentration = new QLineEdit(this, "mpEditCurrentConcentration");
  mpEditCurrentConcentration->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditCurrentConcentration->sizePolicy().hasHeightForWidth()));
  mpEditCurrentConcentration->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentConcentration->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentConcentration->setReadOnly(TRUE);

  CQMetaboliteLayout->addWidget(mpEditCurrentConcentration, 5, 2);

  mpLayoutInitialConcentration = new QVBoxLayout(0, 0, 6, "mpLayoutInitialConcentration");

  mpEditInitialConcentration = new QLineEdit(this, "mpEditInitialConcentration");
  mpEditInitialConcentration->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialConcentration->sizePolicy().hasHeightForWidth()));
  mpEditInitialConcentration->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialConcentration->setFrameShadow(QLineEdit::Sunken);
  mpLayoutInitialConcentration->addWidget(mpEditInitialConcentration);

  mpComboBoxInitialSelection = new QComboBox(FALSE, this, "mpComboBoxInitialSelection");
  mpComboBoxInitialSelection->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxInitialSelection->sizePolicy().hasHeightForWidth()));
  mpLayoutInitialConcentration->addWidget(mpComboBoxInitialSelection);

  CQMetaboliteLayout->addLayout(mpLayoutInitialConcentration, 5, 1);

  mpLblNumber = new QLabel(this, "mpLblNumber");
  mpLblNumber->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblNumber->sizePolicy().hasHeightForWidth()));
  mpLblNumber->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblNumber, 6, 0);

  mpEditInitialNumber = new QLineEdit(this, "mpEditInitialNumber");
  mpEditInitialNumber->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialNumber->sizePolicy().hasHeightForWidth()));
  mpEditInitialNumber->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialNumber->setFrameShadow(QLineEdit::Sunken);

  CQMetaboliteLayout->addWidget(mpEditInitialNumber, 6, 1);

  mpEditCurrentNumber = new QLineEdit(this, "mpEditCurrentNumber");
  mpEditCurrentNumber->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditCurrentNumber->sizePolicy().hasHeightForWidth()));
  mpEditCurrentNumber->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentNumber->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentNumber->setReadOnly(TRUE);

  CQMetaboliteLayout->addWidget(mpEditCurrentNumber, 6, 2);

  mpEditTransitionTime = new QLineEdit(this, "mpEditTransitionTime");
  mpEditTransitionTime->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditTransitionTime->sizePolicy().hasHeightForWidth()));
  mpEditTransitionTime->setFrameShape(QLineEdit::LineEditPanel);
  mpEditTransitionTime->setFrameShadow(QLineEdit::Sunken);
  mpEditTransitionTime->setReadOnly(TRUE);

  CQMetaboliteLayout->addWidget(mpEditTransitionTime, 7, 2);

  mpLblTransitionTime = new QLabel(this, "mpLblTransitionTime");
  mpLblTransitionTime->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblTransitionTime->sizePolicy().hasHeightForWidth()));
  mpLblTransitionTime->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblTransitionTime, 7, 0);

  mpEditConcentrationRate = new QLineEdit(this, "mpEditConcentrationRate");
  mpEditConcentrationRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditConcentrationRate->sizePolicy().hasHeightForWidth()));
  mpEditConcentrationRate->setFrameShape(QLineEdit::LineEditPanel);
  mpEditConcentrationRate->setFrameShadow(QLineEdit::Sunken);
  mpEditConcentrationRate->setReadOnly(TRUE);

  CQMetaboliteLayout->addWidget(mpEditConcentrationRate, 8, 2);

  mpLblConcentrationRate = new QLabel(this, "mpLblConcentrationRate");
  mpLblConcentrationRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblConcentrationRate->sizePolicy().hasHeightForWidth()));
  mpLblConcentrationRate->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblConcentrationRate, 8, 0);

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

  CQMetaboliteLayout->addMultiCellLayout(mpHBoxLayout, 9, 9, 1, 2);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblExpression, 9, 0);

  mpLblReactions = new QLabel(this, "mpLblReactions");
  mpLblReactions->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblReactions->sizePolicy().hasHeightForWidth()));
  mpLblReactions->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQMetaboliteLayout->addWidget(mpLblReactions, 10, 0);

  mpReactionTable = new QListView(this, "mpReactionTable");
  mpReactionTable->addColumn(tr("Name"));
  mpReactionTable->addColumn(tr("Equation"));
  mpReactionTable->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpReactionTable->sizePolicy().hasHeightForWidth()));

  CQMetaboliteLayout->addMultiCellWidget(mpReactionTable, 10, 10, 1, 2);
  mpSpacer = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQMetaboliteLayout->addItem(mpSpacer, 11, 1);

  mpLine2 = new QFrame(this, "mpLine2");
  mpLine2->setFrameShape(QFrame::HLine);
  mpLine2->setFrameShadow(QFrame::Sunken);
  mpLine2->setFrameShape(QFrame::HLine);

  CQMetaboliteLayout->addMultiCellWidget(mpLine2, 12, 12, 0, 2);

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

  mpLine1 = new QFrame(this, "mpLine1");
  mpLine1->setFrameShape(QFrame::HLine);
  mpLine1->setFrameShadow(QFrame::Sunken);
  mpLine1->setFrameShape(QFrame::HLine);

  CQMetaboliteLayout->addMultiCellWidget(mpLine1, 3, 3, 0, 2);
  languageChange();
  resize(QSize(474, 447).expandedTo(minimumSizeHint()));
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
  connect(mpEditInitialConcentration, SIGNAL(lostFocus()), this, SLOT(slotInitialConcentrationLostFocus()));
  connect(mpEditInitialNumber, SIGNAL(lostFocus()), this, SLOT(slotInitialNumberLostFocus()));
  connect(mpReactionTable, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(slotReactionTableCurrentChanged(QListViewItem*)));

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
  setTabOrder(mpBtnObject, mpBtnCommit);
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
  mpLblName->setText(tr("Metobolite Name"));
  mpLblCompartment->setText(tr("Compartment"));
  mpLblType->setText(tr("Type"));
  mpLblInitialValue->setText(tr("Initial Values"));
  mpLblTransientValue->setText(tr("Transient Values"));
  mpLblConcentration->setText(tr("Concentration"));
  mpLblNumber->setText(tr("Particle Number"));
  mpLblTransitionTime->setText(tr("Transition Time"));
  mpLblConcentrationRate->setText(tr("Concentration Rate"));
  mpBtnObject->setText(QString::null);
  mpBtnObject->setTextLabel(tr("select"));
  mpLblExpression->setText(tr("Expression"));
  mpLblReactions->setText(tr("Involved in Reactions"));
  mpReactionTable->header()->setLabel(0, tr("Name"));
  mpReactionTable->header()->setLabel(1, tr("Equation"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
}
