// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/12 21:13:06 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQCompartment.ui'
 **
 ** Created: Mon Nov 12 16:10:33 2007
 **      by: The User Interface Compiler ($Id: CQCompartment.cpp,v 1.2 2007/11/12 21:13:06 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQCompartment.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qheader.h>
#include <qlistview.h>
#include <qcheckbox.h>
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
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x01,
    0xfd, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0xa5, 0x93, 0x3d, 0x6b, 0x1b,
    0x41, 0x14, 0x45, 0xcf, 0xc2, 0x06, 0x9e, 0x61, 0x8b, 0x19, 0x50, 0xa1,
    0x05, 0x07, 0xb4, 0xe0, 0x14, 0x63, 0x2c, 0x88, 0x0c, 0x2e, 0x6c, 0x08,
    0x18, 0x97, 0xea, 0x52, 0xe4, 0xdf, 0xe5, 0x27, 0x24, 0x69, 0x02, 0xae,
    0x82, 0x53, 0x18, 0x49, 0x01, 0x07, 0xaf, 0xc1, 0x86, 0x0d, 0xa8, 0x58,
    0x15, 0x81, 0x59, 0x88, 0x61, 0x07, 0x6c, 0xd0, 0x2b, 0x16, 0x26, 0x85,
    0x88, 0x3f, 0xa2, 0x38, 0x29, 0x32, 0xd5, 0xc0, 0x7d, 0xe7, 0xc2, 0xdc,
    0x77, 0x27, 0x99, 0x4c, 0x27, 0xfc, 0xcf, 0x49, 0xff, 0x26, 0x8a, 0xb4,
    0x91, 0x0e, 0x42, 0x68, 0xf0, 0x3f, 0x5a, 0xe4, 0x19, 0xe4, 0x9b, 0x07,
    0xc9, 0x3f, 0x0d, 0x4c, 0xd6, 0xc6, 0x10, 0x94, 0xd9, 0x69, 0x4d, 0xbd,
    0x50, 0x44, 0xc0, 0xf4, 0xc0, 0xbd, 0xb0, 0x18, 0xd3, 0xc6, 0x10, 0x6c,
    0xf2, 0xa4, 0x81, 0x88, 0xc6, 0xb2, 0x6c, 0x28, 0x2f, 0x3c, 0x92, 0xc1,
    0xfe, 0xab, 0x9c, 0x62, 0x50, 0x40, 0xb7, 0x84, 0x54, 0x79, 0x08, 0xaf,
    0x19, 0xb4, 0xc1, 0xc7, 0xd9, 0xac, 0xc6, 0x37, 0x8a, 0xdb, 0x02, 0x37,
    0x2c, 0xb0, 0xa6, 0x48, 0x54, 0x01, 0x04, 0xba, 0xbf, 0x64, 0x50, 0xcf,
    0xab, 0x38, 0xbd, 0xf0, 0x58, 0x11, 0x8e, 0x0e, 0x0b, 0x8a, 0xa2, 0x48,
    0xd6, 0xc7, 0x9f, 0x30, 0xa8, 0xe7, 0x55, 0x2c, 0x2f, 0x3c, 0xdb, 0x5b,
    0x96, 0xfd, 0x3d, 0x87, 0x76, 0xf2, 0x08, 0x36, 0x54, 0xab, 0x30, 0xe7,
    0x15, 0x1a, 0x5a, 0xa4, 0x67, 0x29, 0xdc, 0x3e, 0x75, 0x97, 0x27, 0xa9,
    0x6f, 0xaa, 0x38, 0xfd, 0xba, 0x82, 0x47, 0xc3, 0xfe, 0x23, 0xd8, 0x74,
    0x65, 0x0c, 0x8d, 0xa7, 0xba, 0xac, 0x68, 0x16, 0x8a, 0xbf, 0x31, 0x68,
    0x07, 0x26, 0xad, 0x71, 0x17, 0x15, 0xbb, 0xaf, 0xc7, 0x31, 0x2d, 0xcf,
    0xce, 0xb1, 0xc6, 0xe2, 0x9c, 0x81, 0x34, 0xbf, 0x83, 0xe5, 0xfb, 0x71,
    0x2c, 0xcb, 0x8a, 0x6a, 0x21, 0x88, 0x31, 0xe4, 0x2f, 0x2d, 0x63, 0xe7,
    0x90, 0x4c, 0xd0, 0xeb, 0xc0, 0xf4, 0xe3, 0x31, 0x76, 0x76, 0x4c, 0xea,
    0xaf, 0x03, 0xbb, 0x3b, 0x16, 0xc9, 0xee, 0xdf, 0x2c, 0xf3, 0xe3, 0x38,
    0xfb, 0x54, 0xd2, 0x66, 0x7d, 0xdc, 0x61, 0x81, 0x1b, 0x8e, 0x50, 0x56,
    0xe9, 0x2b, 0x40, 0xe6, 0x63, 0xe8, 0x0c, 0x6d, 0xf0, 0xeb, 0x6b, 0x2c,
    0xb2, 0x36, 0x9e, 0x7c, 0x29, 0x59, 0x66, 0x86, 0xa3, 0x37, 0x63, 0x90,
    0x3c, 0xd1, 0x07, 0xba, 0x5c, 0x97, 0xf1, 0xe4, 0x73, 0x8d, 0x00, 0xf9,
    0xde, 0x98, 0x34, 0xef, 0x19, 0x7c, 0x03, 0x83, 0xeb, 0x2a, 0xda, 0x9e,
    0x4b, 0x54, 0x1b, 0xc2, 0xed, 0x12, 0x3b, 0x30, 0x18, 0x1a, 0x36, 0xba,
    0x26, 0x02, 0x2c, 0x6f, 0x5b, 0xea, 0xb2, 0x62, 0x71, 0xe5, 0xd1, 0x34,
    0x67, 0x74, 0x38, 0x82, 0xfe, 0x41, 0x92, 0xbc, 0xfb, 0xf0, 0x36, 0xce,
    0x4e, 0x3d, 0xc6, 0x28, 0x6e, 0x58, 0x90, 0x67, 0x4a, 0x7d, 0xf6, 0x1e,
    0xff, 0xad, 0x01, 0x2f, 0x68, 0x58, 0xed, 0x4a, 0x33, 0x83, 0x4a, 0x4e,
    0xdf, 0x19, 0xdc, 0xde, 0x36, 0x76, 0x73, 0x94, 0x00, 0x24, 0x93, 0xe9,
    0x04, 0xd5, 0x3a, 0x56, 0x97, 0x15, 0xe7, 0x57, 0x02, 0x0a, 0xaa, 0x01,
    0xbd, 0x59, 0xa2, 0x01, 0x04, 0xe8, 0x3f, 0x87, 0xed, 0x9d, 0x0d, 0x06,
    0xae, 0xc0, 0xf6, 0x0d, 0xa4, 0xf7, 0x79, 0x25, 0xbf, 0x7e, 0xa3, 0xa4,
    0x3e, 0xea, 0xc3, 0xa6, 0xdd, 0xdd, 0x05, 0xc9, 0x2c, 0xd0, 0xa2, 0x6a,
    0xd7, 0xca, 0x75, 0x17, 0xa2, 0x76, 0x79, 0xf2, 0x67, 0x05, 0x56, 0x55,
    0xb6, 0xbf, 0xb3, 0x00, 0xfc, 0x04, 0x1f, 0x10, 0xec, 0xba, 0xea, 0xbd,
    0x77, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42,
    0x60, 0x82
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
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  CQCompartmentLayout = new QGridLayout(this, 1, 1, 11, 6, "CQCompartmentLayout");

  mpLine2 = new QFrame(this, "mpLine2");
  mpLine2->setFrameShape(QFrame::HLine);
  mpLine2->setFrameShadow(QFrame::Sunken);
  mpLine2->setFrameShape(QFrame::HLine);

  CQCompartmentLayout->addMultiCellWidget(mpLine2, 10, 10, 0, 2);

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
  mpSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQCompartmentLayout->addItem(mpSpacer, 9, 1);

  mpMetaboliteTable = new QListView(this, "mpMetaboliteTable");
  mpMetaboliteTable->addColumn(tr("Name"));
  mpMetaboliteTable->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpMetaboliteTable->sizePolicy().hasHeightForWidth()));

  CQCompartmentLayout->addMultiCellWidget(mpMetaboliteTable, 8, 8, 1, 2);

  mpLblMetabolites = new QLabel(this, "mpLblMetabolites");
  mpLblMetabolites->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, mpLblMetabolites->sizePolicy().hasHeightForWidth()));
  mpLblMetabolites->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  CQCompartmentLayout->addWidget(mpLblMetabolites, 8, 0);

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

  mpHBoxLayoutInitialExpression = new QHBoxLayout(0, 0, 6, "mpHBoxLayoutInitialExpression");

  mpEditInitialExpression = new CQExpressionWidget(this, "mpEditInitialExpression");
  mpEditInitialExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpEditInitialExpression->sizePolicy().hasHeightForWidth()));
  mpHBoxLayoutInitialExpression->addWidget(mpEditInitialExpression);

  mpVBoxLayoutInitialExpression = new QVBoxLayout(0, 0, 6, "mpVBoxLayoutInitialExpression");

  mpBtnInitialExpressionObject = new QToolButton(this, "mpBtnInitialExpressionObject");
  mpBtnInitialExpressionObject->setMaximumSize(QSize(20, 20));
  mpBtnInitialExpressionObject->setIconSet(QIconSet(image0));
  mpVBoxLayoutInitialExpression->addWidget(mpBtnInitialExpressionObject);
  mpSpacerObjectInitialExpression = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpVBoxLayoutInitialExpression->addItem(mpSpacerObjectInitialExpression);
  mpHBoxLayoutInitialExpression->addLayout(mpVBoxLayoutInitialExpression);

  CQCompartmentLayout->addMultiCellLayout(mpHBoxLayoutInitialExpression, 4, 4, 1, 2);

  mpHBoxLayoutExpression = new QHBoxLayout(0, 0, 6, "mpHBoxLayoutExpression");

  mpEditExpression = new CQExpressionWidget(this, "mpEditExpression");
  mpHBoxLayoutExpression->addWidget(mpEditExpression);

  mpVBoxLayoutExpression = new QVBoxLayout(0, 0, 6, "mpVBoxLayoutExpression");

  mpBtnExpressionObject = new QToolButton(this, "mpBtnExpressionObject");
  mpBtnExpressionObject->setMaximumSize(QSize(20, 20));
  mpBtnExpressionObject->setIconSet(QIconSet(image0));
  mpVBoxLayoutExpression->addWidget(mpBtnExpressionObject);
  mpSpacerExpressionObject = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpVBoxLayoutExpression->addItem(mpSpacerExpressionObject);
  mpHBoxLayoutExpression->addLayout(mpVBoxLayoutExpression);

  CQCompartmentLayout->addMultiCellLayout(mpHBoxLayoutExpression, 2, 2, 1, 2);
  languageChange();
  resize(QSize(460, 364).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnCommit, SIGNAL(clicked()), this, SLOT(slotBtnCommit()));
  connect(mpBtnDelete, SIGNAL(clicked()), this, SLOT(slotBtnDelete()));
  connect(mpBtnNew, SIGNAL(clicked()), this, SLOT(slotBtnNew()));
  connect(mpBtnRevert, SIGNAL(clicked()), this, SLOT(slotBtnRevert()));
  connect(mpComboBoxType, SIGNAL(activated(int)), this, SLOT(slotTypeChanged(int)));
  connect(mpBtnExpressionObject, SIGNAL(clicked()), mpEditExpression, SLOT(slotSelectObject()));
  connect(mpEditExpression, SIGNAL(valid(bool)), this, SLOT(slotExpressionValid(bool)));
  connect(mpEditInitialExpression, SIGNAL(valid(bool)), this, SLOT(slotInitialExpressionValid(bool)));
  connect(mpMetaboliteTable, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(slotMetaboliteTableCurrentChanged(QListViewItem*)));
  connect(mpBtnInitialExpressionObject, SIGNAL(clicked()), mpEditInitialExpression, SLOT(slotSelectObject()));
  connect(mpBoxUseInitialExpression, SIGNAL(toggled(bool)), this, SLOT(slotInitialTypeChanged(bool)));

  // tab order
  setTabOrder(mpEditName, mpComboBoxType);
  setTabOrder(mpComboBoxType, mpEditExpression);
  setTabOrder(mpEditExpression, mpBtnExpressionObject);
  setTabOrder(mpBtnExpressionObject, mpEditInitialVolume);
  setTabOrder(mpEditInitialVolume, mpBoxUseInitialExpression);
  setTabOrder(mpBoxUseInitialExpression, mpEditInitialExpression);
  setTabOrder(mpEditInitialExpression, mpBtnInitialExpressionObject);
  setTabOrder(mpBtnInitialExpressionObject, mpEditRate);
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
  setCaption(tr("Form1"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
  mpLblType->setText(tr("Type"));
  mpLblName->setText(tr("Compartment Name"));
  mpMetaboliteTable->header()->setLabel(0, tr("Name"));
  mpLblMetabolites->setText(tr("Contained Metabolites"));
  mpLblRate->setText(tr("Rate"));
  mpLblVolume->setText(tr("Volume"));
  mpLblExpression->setText(tr("Expression"));
  mpLblInitialValue->setText(tr("Initial Volume"));
  mpBoxUseInitialExpression->setText(tr("Use Initial Expression"));
  mpLblInitialExpression->setText(tr("Initial Expression"));
  mpBtnInitialExpressionObject->setText(QString::null);
  mpBtnInitialExpressionObject->setTextLabel(tr("select"));
  mpBtnExpressionObject->setText(QString::null);
  mpBtnExpressionObject->setTextLabel(tr("select"));
}
