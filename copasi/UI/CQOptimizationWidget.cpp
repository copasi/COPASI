// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.cpp,v $
//   $Revision: 1.10.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/04 16:22:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Thu Dec 4 11:12:42 2008
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.cpp,v 1.10.4.1 2008/12/04 16:22:38 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQOptimizationWidget.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "TaskWidget.h"
#include "CQExpressionMmlWidget.h"
#include "CQOptimizationWidget.ui.h"

/*
 *  Constructs a CQOptimizationWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQOptimizationWidget::CQOptimizationWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  if (!name)
    setName("CQOptimizationWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  setMinimumSize(QSize(0, 0));
  CQOptimizationWidgetLayout = new QVBoxLayout(this, 11, 6, "CQOptimizationWidgetLayout");

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignLeft));

  mpGridLayout->addWidget(mpLblType, 2, 0);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignLeft));

  mpGridLayout->addWidget(mpLblExpression, 0, 0);

  mpExpressionEMW = new CQExpressionMmlWidget(this, "mpExpressionEMW");
  mpExpressionEMW->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpExpressionEMW->sizePolicy().hasHeightForWidth()));
  mpExpressionEMW->setMinimumSize(QSize(420, 70));

  mpGridLayout->addMultiCellWidget(mpExpressionEMW, 0, 1, 1, 2);

  mpBoxSubtask = new QComboBox(FALSE, this, "mpBoxSubtask");
  mpBoxSubtask->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, 0, 0, mpBoxSubtask->sizePolicy().hasHeightForWidth()));

  mpGridLayout->addWidget(mpBoxSubtask, 2, 1);

  mpBtnGroup = new QButtonGroup(this, "mpBtnGroup");
  mpBtnGroup->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)3, 0, 0, mpBtnGroup->sizePolicy().hasHeightForWidth()));
  mpBtnGroup->setFrameShape(QButtonGroup::NoFrame);
  mpBtnGroup->setFrameShadow(QButtonGroup::Plain);
  mpBtnGroup->setLineWidth(0);
  mpBtnGroup->setFlat(TRUE);
  mpBtnGroup->setProperty("selectedId", 1);

  mpBtnMaximize = new QRadioButton(mpBtnGroup, "mpBtnMaximize");
  mpBtnMaximize->setGeometry(QRect(0, 20, 90, 22));
  mpBtnMaximize->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, mpBtnMaximize->sizePolicy().hasHeightForWidth()));

  mpBtnMinimize = new QRadioButton(mpBtnGroup, "mpBtnMinimize");
  mpBtnMinimize->setGeometry(QRect(0, 0, 90, 22));
  mpBtnMinimize->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, mpBtnMinimize->sizePolicy().hasHeightForWidth()));
  mpBtnMinimize->setChecked(TRUE);

  mpGridLayout->addWidget(mpBtnGroup, 1, 0);
  mpSpacer = new QSpacerItem(214, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpGridLayout->addItem(mpSpacer, 2, 2);
  CQOptimizationWidgetLayout->addLayout(mpGridLayout);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");
  mpTabWidget->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, mpTabWidget->sizePolicy().hasHeightForWidth()));

  mpParametersPage = new QWidget(mpTabWidget, "mpParametersPage");
  mpTabWidget->insertTab(mpParametersPage, QString::fromLatin1(""));

  mpConstraintsPage = new QWidget(mpTabWidget, "mpConstraintsPage");
  mpTabWidget->insertTab(mpConstraintsPage, QString::fromLatin1(""));
  CQOptimizationWidgetLayout->addWidget(mpTabWidget);
  languageChange();
  resize(QSize(550, 222).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpTabWidget, SIGNAL(currentChanged(QWidget*)), this, SLOT(slotPageChange(QWidget*)));
  connect(mpBoxSubtask, SIGNAL(activated(const QString&)), this, SLOT(slotSubtaskChanged(const QString&)));

  // tab order
  setTabOrder(mpBoxSubtask, mpTabWidget);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQOptimizationWidget::~CQOptimizationWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQOptimizationWidget::languageChange()
{
  setCaption(tr("Optimization"));
  mpLblType->setText(tr("Subtask"));
  mpLblExpression->setText(tr("Expression"));
  mpBtnGroup->setTitle(QString::null);
  mpBtnMaximize->setText(tr("maximize"));
  mpBtnMinimize->setText(tr("minimize"));
  mpTabWidget->changeTab(mpParametersPage, tr("Parameters (0)"));
  mpTabWidget->changeTab(mpConstraintsPage, tr("Constraints (0)"));
}
