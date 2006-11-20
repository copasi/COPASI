/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingWidget.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/11/20 16:39:13 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQFittingWidget.ui'
 **
 ** Created: Thu Nov 16 12:12:04 2006
 **      by: The User Interface Compiler ($Id: CQFittingWidget.cpp,v 1.11 2006/11/20 16:39:13 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQFittingWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "TaskWidget.h"
#include "CQFittingWidget.ui.h"

/*
 *  Constructs a CQFittingWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQFittingWidget::CQFittingWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  if (!name)
    setName("CQFittingWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  setMinimumSize(QSize(0, 0));
  CQFittingWidgetLayout = new QVBoxLayout(this, 11, 6, "CQFittingWidgetLayout");

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpBtnCrossValidation = new QPushButton(this, "mpBtnCrossValidation");

  mpGridLayout->addWidget(mpBtnCrossValidation, 0, 2);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");

  mpParametersPage = new QWidget(mpTabWidget, "mpParametersPage");
  mpTabWidget->insertTab(mpParametersPage, QString::fromLatin1(""));

  mpConstraintsPage = new QWidget(mpTabWidget, "mpConstraintsPage");
  mpTabWidget->insertTab(mpConstraintsPage, QString::fromLatin1(""));

  mpGridLayout->addMultiCellWidget(mpTabWidget, 1, 1, 0, 2);

  mpBtnExperiment = new QPushButton(this, "mpBtnExperiment");

  mpGridLayout->addWidget(mpBtnExperiment, 0, 1);
  mpSpacer = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpGridLayout->addItem(mpSpacer, 0, 0);
  CQFittingWidgetLayout->addLayout(mpGridLayout);
  languageChange();
  resize(QSize(324, 114).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnExperiment, SIGNAL(clicked()), this, SLOT(slotExperimentData()));
  connect(mpTabWidget, SIGNAL(currentChanged(QWidget*)), this, SLOT(slotPageChange(QWidget*)));
  connect(mpBtnCrossValidation, SIGNAL(clicked()), this, SLOT(slotCrossValidationData()));

  // tab order
  setTabOrder(mpBtnExperiment, mpBtnCrossValidation);
  setTabOrder(mpBtnCrossValidation, mpTabWidget);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingWidget::~CQFittingWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingWidget::languageChange()
{
  setCaption(tr("Fitting"));
  mpBtnCrossValidation->setText(tr("Cross Validation Data"));
  mpTabWidget->changeTab(mpParametersPage, tr("Parameters (0)"));
  mpTabWidget->changeTab(mpConstraintsPage, tr("Constraints (0)"));
  mpBtnExperiment->setText(tr("Experimental Data"));
}
