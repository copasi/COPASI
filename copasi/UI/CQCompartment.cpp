// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/08/22 12:59:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQCompartment.ui'
 **
 ** Created: Wed Aug 22 08:41:00 2007
 **      by: The User Interface Compiler ($Id: CQCompartment.cpp,v 1.1 2007/08/22 12:59:17 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQCompartment.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qheader.h>
#include <qlistview.h>
#include <qframe.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "CQExpressionWidget.h"
#include "CQCompartment.ui.h"
static const unsigned char image0_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x8c, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0x9d, 0x93, 0x3f, 0x88, 0x23,
    0x65, 0x18, 0xc6, 0x7f, 0xdf, 0x72, 0xc5, 0x04, 0xb6, 0xb8, 0x85, 0x15,
    0x66, 0x60, 0x8a, 0x0c, 0x6c, 0x91, 0x2c, 0xd7, 0x64, 0x50, 0xb8, 0xfd,
    0xb0, 0xd0, 0xc0, 0x82, 0xcc, 0x61, 0x61, 0xb6, 0xd2, 0xed, 0xdc, 0x72,
    0xb9, 0xca, 0x34, 0xe2, 0x95, 0x67, 0xe5, 0x5e, 0x25, 0xd1, 0x42, 0xf7,
    0x2c, 0x24, 0x5a, 0xe8, 0xc5, 0x6a, 0x63, 0x71, 0x90, 0x14, 0xcb, 0x7e,
    0x07, 0xca, 0x7d, 0x59, 0x30, 0x66, 0x2c, 0x84, 0x09, 0x61, 0x30, 0x29,
    0x02, 0x33, 0x45, 0x60, 0xa6, 0x08, 0xbc, 0x16, 0xc7, 0xde, 0x9f, 0x15,
    0x04, 0xad, 0x5e, 0x1e, 0xde, 0x07, 0x9e, 0x97, 0x1f, 0xcf, 0x8b, 0xcc,
    0x04, 0x31, 0x82, 0xcc, 0x84, 0xa7, 0xe6, 0x29, 0xff, 0x55, 0x6f, 0x98,
    0xd4, 0x80, 0x0f, 0x26, 0x35, 0x84, 0x7e, 0xc8, 0x2b, 0x7a, 0xc7, 0x13,
    0xbb, 0x38, 0x93, 0x6c, 0x73, 0x22, 0xdd, 0xf3, 0x13, 0xd9, 0xa2, 0x94,
    0xeb, 0x7e, 0x25, 0x33, 0xc1, 0xa6, 0x96, 0xd0, 0x0f, 0x21, 0x05, 0x7c,
    0x98, 0xac, 0xce, 0x64, 0xd7, 0x09, 0xe9, 0xfc, 0xdc, 0xc5, 0x2d, 0x43,
    0x46, 0x4b, 0x43, 0xd4, 0xd0, 0x64, 0x4e, 0xc2, 0x9d, 0xb7, 0x5a, 0xd8,
    0x71, 0xa2, 0xae, 0xfc, 0x1b, 0xd7, 0x93, 0xed, 0x72, 0x20, 0x8c, 0x3c,
    0xda, 0x9f, 0x9f, 0x52, 0x5d, 0x84, 0x10, 0x24, 0xdc, 0xbf, 0xfb, 0x11,
    0x4e, 0xb5, 0xe0, 0xce, 0xed, 0x08, 0x33, 0x8e, 0xd5, 0xcb, 0x7e, 0x25,
    0x33, 0x79, 0x9e, 0x7c, 0x36, 0x7e, 0x24, 0x24, 0x1e, 0xfd, 0xf1, 0x80,
    0xc3, 0x37, 0x35, 0xe5, 0x6b, 0x73, 0x9a, 0xb5, 0x43, 0x75, 0xb5, 0xbf,
    0x7e, 0xa9, 0x4d, 0xed, 0x0b, 0x06, 0xdd, 0xe1, 0xa9, 0x0c, 0x1f, 0x27,
    0x3c, 0x49, 0x0d, 0xed, 0xf7, 0x5b, 0x10, 0x38, 0xaa, 0x59, 0x3b, 0x54,
    0xff, 0xca, 0xe8, 0x8a, 0x41, 0x77, 0xd8, 0x15, 0x67, 0xe9, 0x91, 0x3b,
    0x31, 0x47, 0xef, 0x7d, 0x88, 0x9d, 0xc6, 0xea, 0x15, 0x26, 0x8b, 0xae,
    0xec, 0x6e, 0x37, 0x28, 0xce, 0x1f, 0x52, 0x56, 0xea, 0x24, 0x45, 0x4c,
    0xb8, 0x7f, 0x0c, 0xd3, 0x40, 0xa9, 0x1f, 0x7b, 0x5f, 0xcb, 0x93, 0xf3,
    0x8c, 0xa0, 0x5a, 0xe1, 0xf8, 0xdd, 0x08, 0xb3, 0x98, 0x2b, 0xed, 0x6b,
    0x4c, 0x6a, 0xd0, 0xdb, 0x8e, 0x98, 0xcb, 0x1e, 0xde, 0x6f, 0x31, 0xfd,
    0x29, 0x54, 0x4b, 0x87, 0x61, 0x01, 0x6e, 0xa5, 0x24, 0xf0, 0x4b, 0x0e,
    0xee, 0x7e, 0xc2, 0x0d, 0x67, 0xee, 0xe0, 0x6c, 0xe6, 0x7c, 0xb0, 0x7f,
    0x80, 0x5d, 0x64, 0x4a, 0xfb, 0x1a, 0x52, 0xd0, 0x64, 0xd2, 0xfd, 0xe6,
    0x3b, 0x6e, 0xae, 0x35, 0x83, 0x55, 0x46, 0xeb, 0x9d, 0x26, 0xf9, 0x56,
    0xce, 0x49, 0xad, 0x49, 0x71, 0xd9, 0x67, 0x34, 0xca, 0x18, 0xfc, 0xf0,
    0x80, 0x8d, 0xde, 0x65, 0x9f, 0xc8, 0xdd, 0x23, 0xce, 0xe7, 0x2f, 0xe8,
    0x26, 0x8f, 0xa4, 0xf3, 0xe5, 0x17, 0xcc, 0x73, 0x87, 0x7c, 0x27, 0xe3,
    0xde, 0xc7, 0xf7, 0xc9, 0x03, 0x4f, 0xe9, 0x5b, 0x47, 0xca, 0x2c, 0xe6,
    0xaa, 0x52, 0x8b, 0xe8, 0x4f, 0x63, 0x82, 0x3c, 0xe3, 0x86, 0x76, 0x35,
    0xa3, 0xf5, 0x88, 0x63, 0xff, 0xde, 0xb3, 0xe4, 0x5a, 0x20, 0xdd, 0x6f,
    0x3f, 0xa5, 0x51, 0x8b, 0xd0, 0x7b, 0x2e, 0xec, 0x1c, 0x28, 0x9b, 0x5a,
    0x9e, 0x5f, 0xe6, 0x38, 0x72, 0xf2, 0x55, 0x87, 0xa6, 0xaf, 0x71, 0xdf,
    0x28, 0xd8, 0x48, 0xd6, 0x13, 0xe6, 0xcb, 0x92, 0xb3, 0xcb, 0x53, 0xc1,
    0x87, 0xe4, 0xcf, 0x3e, 0xf5, 0xb2, 0x20, 0x2e, 0x0d, 0xb8, 0x1e, 0xc9,
    0xb4, 0x23, 0xe1, 0x76, 0x29, 0x93, 0xf1, 0x89, 0xcc, 0xcf, 0x8f, 0xa4,
    0xf3, 0x59, 0x1b, 0x96, 0x19, 0xc5, 0x4e, 0x41, 0xe5, 0xf5, 0xb6, 0x52,
    0x7f, 0xfd, 0xf2, 0xbb, 0x3c, 0xf8, 0xbe, 0x47, 0x74, 0xab, 0x41, 0xb6,
    0xb5, 0x20, 0xaa, 0x35, 0xe8, 0xfd, 0xd4, 0x26, 0x58, 0xe5, 0x98, 0x5f,
    0x21, 0x5c, 0xed, 0x61, 0x19, 0x51, 0xdf, 0x6c, 0x32, 0xdc, 0x4c, 0x68,
    0xbd, 0x1d, 0x51, 0xf7, 0x72, 0xb6, 0x6e, 0x1f, 0x2b, 0x9b, 0x5a, 0xd4,
    0x85, 0xb9, 0xa0, 0x71, 0xd3, 0x93, 0x87, 0x8f, 0x4f, 0x99, 0xfc, 0xe1,
    0x50, 0xae, 0x80, 0x75, 0x9d, 0x3c, 0x1b, 0xc0, 0x0a, 0x58, 0x43, 0x2b,
    0x80, 0xbc, 0x56, 0xa1, 0xb5, 0xdf, 0x22, 0x59, 0x27, 0xe8, 0xea, 0xb3,
    0x7e, 0x68, 0x5f, 0xbf, 0xf4, 0x0b, 0x55, 0x4f, 0x98, 0x5a, 0x70, 0x43,
    0xcc, 0xc2, 0xa2, 0xdd, 0x90, 0x22, 0xb5, 0x54, 0x7c, 0xcd, 0x24, 0x8f,
    0xd9, 0x75, 0x03, 0x98, 0x7a, 0xea, 0x1f, 0x8d, 0xbc, 0x30, 0x17, 0xc8,
    0x4c, 0xfe, 0xf7, 0xfc, 0x1b, 0xc5, 0x25, 0xb1, 0x70, 0x5d, 0x12, 0x2b,
    0x83, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
    0x82
  };

/*
 *  Constructs a CQCompartment which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCompartment::CQCompartment(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  QImage img;
  img.loadFromData(image0_data, sizeof(image0_data), "PNG");
  image0 = img;
  if (!name)
    setName("CQCompartment");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)4, 0, 0, sizePolicy().hasHeightForWidth()));
  CQCompartmentLayout = new QVBoxLayout(this, 11, 6, "CQCompartmentLayout");

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpLblVolume = new QLabel(this, "mpLblVolume");
  mpLblVolume->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblVolume->sizePolicy().hasHeightForWidth()));
  mpLblVolume->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblVolume, 5, 0);

  mpComboBoxType = new QComboBox(FALSE, this, "mpComboBoxType");
  mpComboBoxType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxType->sizePolicy().hasHeightForWidth()));

  mpGridLayout->addWidget(mpComboBoxType, 2, 1);

  mpEditName = new QLineEdit(this, "mpEditName");
  mpEditName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpEditName->sizePolicy().hasHeightForWidth()));
  mpEditName->setFrameShape(QLineEdit::LineEditPanel);
  mpEditName->setFrameShadow(QLineEdit::Sunken);

  mpGridLayout->addMultiCellWidget(mpEditName, 0, 0, 1, 2);

  mpLblMetabolites = new QLabel(this, "mpLblMetabolites");
  mpLblMetabolites->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblMetabolites->sizePolicy().hasHeightForWidth()));
  mpLblMetabolites->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblMetabolites, 10, 0);

  mpMetaboliteTable = new QListView(this, "mpMetaboliteTable");
  mpMetaboliteTable->addColumn(tr("Name"));
  mpMetaboliteTable->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpMetaboliteTable->sizePolicy().hasHeightForWidth()));

  mpGridLayout->addMultiCellWidget(mpMetaboliteTable, 10, 10, 1, 2);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblType, 2, 0);

  mpEditCurrentVolume = new QLineEdit(this, "mpEditCurrentVolume");
  mpEditCurrentVolume->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditCurrentVolume->sizePolicy().hasHeightForWidth()));
  mpEditCurrentVolume->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentVolume->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentVolume->setReadOnly(TRUE);

  mpGridLayout->addWidget(mpEditCurrentVolume, 5, 2);

  mpLine1 = new QFrame(this, "mpLine1");
  mpLine1->setFrameShape(QFrame::HLine);
  mpLine1->setFrameShadow(QFrame::Sunken);
  mpLine1->setFrameShape(QFrame::HLine);

  mpGridLayout->addMultiCellWidget(mpLine1, 3, 3, 0, 2);

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblName->sizePolicy().hasHeightForWidth()));
  mpLblName->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblName, 0, 0);

  mpLblRate = new QLabel(this, "mpLblRate");
  mpLblRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblRate->sizePolicy().hasHeightForWidth()));
  mpLblRate->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblRate, 8, 0);

  mpLayoutInitialVolume = new QVBoxLayout(0, 0, 6, "mpLayoutInitialVolume");

  mpEditInitialVolume = new QLineEdit(this, "mpEditInitialVolume");
  mpEditInitialVolume->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialVolume->sizePolicy().hasHeightForWidth()));
  mpEditInitialVolume->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialVolume->setFrameShadow(QLineEdit::Sunken);
  mpLayoutInitialVolume->addWidget(mpEditInitialVolume);

  mpComboBoxInitialSelection = new QComboBox(FALSE, this, "mpComboBoxInitialSelection");
  mpComboBoxInitialSelection->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxInitialSelection->sizePolicy().hasHeightForWidth()));
  mpLayoutInitialVolume->addWidget(mpComboBoxInitialSelection);

  mpGridLayout->addLayout(mpLayoutInitialVolume, 5, 1);

  mpEditRate = new QLineEdit(this, "mpEditRate");
  mpEditRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpEditRate->sizePolicy().hasHeightForWidth()));
  mpEditRate->setFrameShape(QLineEdit::LineEditPanel);
  mpEditRate->setFrameShadow(QLineEdit::Sunken);
  mpEditRate->setReadOnly(TRUE);

  mpGridLayout->addWidget(mpEditRate, 8, 2);

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
  CQCompartmentLayout->addLayout(mpGridLayout);
  mpSpacer = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQCompartmentLayout->addItem(mpSpacer);

  mpLine2 = new QFrame(this, "mpLine2");
  mpLine2->setFrameShape(QFrame::HLine);
  mpLine2->setFrameShadow(QFrame::Sunken);
  mpLine2->setFrameShape(QFrame::HLine);
  CQCompartmentLayout->addWidget(mpLine2);

  mpBtnLayout = new QHBoxLayout(0, 0, 6, "mpBtnLayout");

  mpBtnCommit = new QPushButton(this, "mpBtnCommit");
  mpBtnLayout->addWidget(mpBtnCommit);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");
  mpBtnLayout->addWidget(mpBtnRevert);

  mpBtnNew = new QPushButton(this, "mpBtnNew");
  mpBtnLayout->addWidget(mpBtnNew);

  mpBtnDelete = new QPushButton(this, "mpBtnDelete");
  mpBtnLayout->addWidget(mpBtnDelete);
  CQCompartmentLayout->addLayout(mpBtnLayout);
  languageChange();
  resize(QSize(483, 363).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnCommit, SIGNAL(clicked()), this, SLOT(slotBtnCommit()));
  connect(mpBtnDelete, SIGNAL(clicked()), this, SLOT(slotBtnDelete()));
  connect(mpBtnNew, SIGNAL(clicked()), this, SLOT(slotBtnNew()));
  connect(mpBtnRevert, SIGNAL(clicked()), this, SLOT(slotBtnRevert()));
  connect(mpComboBoxType, SIGNAL(activated(int)), this, SLOT(slotTypeChanged(int)));
  connect(mpComboBoxInitialType, SIGNAL(activated(int)), this, SLOT(slotInitialTypeChanged(int)));
  connect(mpComboBoxInitialSelection, SIGNAL(activated(int)), this, SLOT(slotInitialAssignment(int)));
  connect(mpBtnObject, SIGNAL(clicked()), mpEditExpression, SLOT(slotSelectObject()));
  connect(mpEditExpression, SIGNAL(valid(bool)), this, SLOT(slotExpressionValid(bool)));
  connect(mpMetaboliteTable, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(slotMetaboliteTableCurrentChanged(QListViewItem*)));

  // tab order
  setTabOrder(mpEditName, mpComboBoxType);
  setTabOrder(mpComboBoxType, mpComboBoxInitialType);
  setTabOrder(mpComboBoxInitialType, mpEditInitialVolume);
  setTabOrder(mpEditInitialVolume, mpComboBoxInitialSelection);
  setTabOrder(mpComboBoxInitialSelection, mpEditCurrentVolume);
  setTabOrder(mpEditCurrentVolume, mpEditRate);
  setTabOrder(mpEditRate, mpEditExpression);
  setTabOrder(mpEditExpression, mpBtnObject);
  setTabOrder(mpBtnObject, mpMetaboliteTable);
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
  setCaption(tr("Form1"));
  mpLblVolume->setText(tr("Volume"));
  mpLblMetabolites->setText(tr("Contained Metabolites"));
  mpMetaboliteTable->header()->setLabel(0, tr("Name"));
  mpLblType->setText(tr("Type"));
  mpLblName->setText(tr("Compartment Name"));
  mpLblRate->setText(tr("Rate"));
  mpBtnObject->setText(QString::null);
  mpBtnObject->setTextLabel(tr("select"));
  mpLblInitialValue->setText(tr("Initial Values"));
  mpLblTransientValue->setText(tr("Transient Values"));
  mpLblExpression->setText(tr("Expression"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
}
