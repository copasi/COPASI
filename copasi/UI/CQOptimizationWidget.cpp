// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/04/18 09:13:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Fri Apr 18 08:34:12 2008
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.cpp,v 1.9 2008/04/18 09:13:21 pwilly Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQOptimizationWidget.h"

#include <qvariant.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlabel.h>
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

  mpExpressionEMW = new CQExpressionMmlWidget(this, "mpExpressionEMW");
  mpExpressionEMW->setMinimumSize(QSize(420, 70));

  mpGridLayout->addMultiCellWidget(mpExpressionEMW, 0, 0, 1, 2);

  mpBtnGroup = new QButtonGroup(this, "mpBtnGroup");
  mpBtnGroup->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)4, 0, 0, mpBtnGroup->sizePolicy().hasHeightForWidth()));
  mpBtnGroup->setFrameShape(QButtonGroup::NoFrame);
  mpBtnGroup->setAlignment(int(QButtonGroup::WordBreak | QButtonGroup::AlignVCenter | QButtonGroup::AlignBottom | QButtonGroup::AlignTop));
  mpBtnGroup->setColumnLayout(0, Qt::Vertical);
  mpBtnGroup->layout()->setSpacing(6);
  mpBtnGroup->layout()->setMargin(0);
  mpBtnGroupLayout = new QHBoxLayout(mpBtnGroup->layout());
  mpBtnGroupLayout->setAlignment(Qt::AlignTop);

  mpBtnSteadystate = new QRadioButton(mpBtnGroup, "mpBtnSteadystate");
  mpBtnSteadystate->setChecked(TRUE);
  mpBtnGroupLayout->addWidget(mpBtnSteadystate);

  mpBtnTimeCourse = new QRadioButton(mpBtnGroup, "mpBtnTimeCourse");
  mpBtnGroupLayout->addWidget(mpBtnTimeCourse);

  mpGridLayout->addWidget(mpBtnGroup, 1, 1);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblExpression, 0, 0);
  mpSpacer2 = new QSpacerItem(261, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpGridLayout->addItem(mpSpacer2, 1, 2);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblType, 1, 0);
  CQOptimizationWidgetLayout->addLayout(mpGridLayout);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");
  mpTabWidget->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, mpTabWidget->sizePolicy().hasHeightForWidth()));

  mpParametersPage = new QWidget(mpTabWidget, "mpParametersPage");
  mpTabWidget->insertTab(mpParametersPage, QString::fromLatin1(""));

  mpConstraintsPage = new QWidget(mpTabWidget, "mpConstraintsPage");
  mpTabWidget->insertTab(mpConstraintsPage, QString::fromLatin1(""));
  CQOptimizationWidgetLayout->addWidget(mpTabWidget);
  languageChange();
  resize(QSize(627, 412).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpTabWidget, SIGNAL(currentChanged(QWidget*)), this, SLOT(slotPageChange(QWidget*)));
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
  mpBtnGroup->setTitle(QString::null);
  mpBtnSteadystate->setText(tr("Steady State"));
  mpBtnTimeCourse->setText(tr("Time Course"));
  mpLblExpression->setText(tr("Expression"));
  mpLblType->setText(tr("Experiment Type"));
  mpTabWidget->changeTab(mpParametersPage, tr("Parameters (0)"));
  mpTabWidget->changeTab(mpConstraintsPage, tr("Constraints (0)"));
}
