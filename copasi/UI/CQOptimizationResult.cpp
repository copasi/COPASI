// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationResult.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/14 19:47:24 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQOptimizationResult.ui'
 **
 ** Created: Tue Oct 14 15:30:23 2008
 **      by: The User Interface Compiler ($Id: CQOptimizationResult.cpp,v 1.1.2.1 2008/10/14 19:47:24 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQOptimizationResult.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQOptimizationResult.ui.h"

/*
 *  Constructs a CQOptimizationResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQOptimizationResult::CQOptimizationResult(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("CQOptimizationResult");
  CQOptimizationResultLayout = new QVBoxLayout(this, 11, 6, "CQOptimizationResultLayout");

  mpHBox = new QHBoxLayout(0, 0, 6, "mpHBox");

  mpLblResult = new QLabel(this, "mpLblResult");
  mpLblResult->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpLblResult->sizePolicy().hasHeightForWidth()));
  mpHBox->addWidget(mpLblResult);

  mpBtnUpdateModel = new QPushButton(this, "mpBtnUpdateModel");
  mpHBox->addWidget(mpBtnUpdateModel);

  mpBtnSave = new QPushButton(this, "mpBtnSave");
  mpHBox->addWidget(mpBtnSave);
  CQOptimizationResultLayout->addLayout(mpHBox);

  mpGrid = new QGridLayout(0, 1, 1, 0, 6, "mpGrid");

  mpEditCPUTime = new QLineEdit(this, "mpEditCPUTime");
  mpEditCPUTime->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCPUTime->setFrameShadow(QLineEdit::Sunken);
  mpEditCPUTime->setReadOnly(TRUE);

  mpGrid->addWidget(mpEditCPUTime, 3, 1);

  mpEditEvaluations = new QLineEdit(this, "mpEditEvaluations");
  mpEditEvaluations->setReadOnly(TRUE);

  mpGrid->addWidget(mpEditEvaluations, 3, 0);

  mpEditSpeed = new QLineEdit(this, "mpEditSpeed");
  mpEditSpeed->setReadOnly(TRUE);

  mpGrid->addWidget(mpEditSpeed, 3, 2);

  mpLblSpeed = new QLabel(this, "mpLblSpeed");

  mpGrid->addWidget(mpLblSpeed, 2, 2);

  mpLblEvaluations = new QLabel(this, "mpLblEvaluations");

  mpGrid->addWidget(mpLblEvaluations, 2, 0);

  mpLblCPUTime = new QLabel(this, "mpLblCPUTime");

  mpGrid->addWidget(mpLblCPUTime, 2, 1);

  mpLblObjectiveValue = new QLabel(this, "mpLblObjectiveValue");

  mpGrid->addWidget(mpLblObjectiveValue, 0, 0);

  mpEditObjectiveValue = new QLineEdit(this, "mpEditObjectiveValue");
  mpEditObjectiveValue->setReadOnly(TRUE);

  mpGrid->addWidget(mpEditObjectiveValue, 1, 0);
  CQOptimizationResultLayout->addLayout(mpGrid);

  mpParameters = new QTable(this, "mpParameters");
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Parameter"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Value"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Gradient"));
  mpParameters->setNumRows(0);
  mpParameters->setNumCols(0);
  CQOptimizationResultLayout->addWidget(mpParameters);
  mpSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQOptimizationResultLayout->addItem(mpSpacer);
  languageChange();
  resize(QSize(568, 306).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnSave, SIGNAL(clicked()), this, SLOT(slotSave()));
  connect(mpBtnUpdateModel, SIGNAL(clicked()), this, SLOT(slotUpdateModel()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQOptimizationResult::~CQOptimizationResult()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQOptimizationResult::languageChange()
{
  setCaption(tr("Fitting Result"));
  mpLblResult->setText(tr("<h2>Optimization Result</h2>"));
  mpBtnUpdateModel->setText(tr("Update Model"));
  mpBtnSave->setText(tr("save data"));
  mpLblSpeed->setText(tr("Evaluations/second [1/s]"));
  mpLblEvaluations->setText(tr("Function Evaluations"));
  mpLblCPUTime->setText(tr("CPU Time [s]"));
  mpLblObjectiveValue->setText(tr("Objective Value"));
  mpParameters->horizontalHeader()->setLabel(0, tr("Parameter"));
  mpParameters->horizontalHeader()->setLabel(1, tr("Value"));
  mpParameters->horizontalHeader()->setLabel(2, tr("Gradient"));
}
