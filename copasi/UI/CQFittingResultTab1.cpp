// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingResultTab1.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/06/07 14:01:52 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQFittingResultTab1.h"
#include "copasi.h"

#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CFitItem.h"
#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"

#include "UI/qtUtilities.h"

/*
 *  Constructs a CQFittingResultTab1 which is a child of 'parent', with the
 *  name 'name'.'
 */
CQFittingResultTab1::CQFittingResultTab1(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingResultTab1::~CQFittingResultTab1()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingResultTab1::languageChange()
{
  retranslateUi(this);
}

void CQFittingResultTab1::load(const CFitProblem * pProblem)
{
  mpEditObjectiveValue->setText(QString::number(pProblem->getSolutionValue()));
  mpEditRMS->setText(QString::number(pProblem->getRMS()));
  mpEditStdDeviation->setText(QString::number(pProblem->getStdDeviation()));

#ifdef COPASI_CROSSVALIDATION
  bool Enable = (pProblem->getCrossValidationSet().getExperimentCount() > 0);

  mpLblCVObjectiveValue->setEnabled(Enable);
  mpEditCVObjectiveValue->setEnabled(Enable);
  mpLblCVRMS->setEnabled(Enable);
  mpEditCVRMS->setEnabled(Enable);
  mpLblCVStdDeviation->setEnabled(Enable);
  mpEditCVStdDeviation->setEnabled(Enable);

  if (Enable)
    {
      mpEditCVObjectiveValue->setText(QString::number(pProblem->getCrossValidationSolutionValue()));
      mpEditCVRMS->setText(QString::number(pProblem->getCrossValidationRMS()));
      mpEditCVStdDeviation->setText(QString::number(pProblem->getCrossValidationSD()));
    }
  else
    {
      mpEditCVObjectiveValue->setText("");
      mpEditCVRMS->setText("");
      mpEditCVStdDeviation->setText("");
    }

#endif // COPASI_CROSSVALIDATION

#ifndef COPASI_CROSSVALIDATION
  mpLblCVObjectiveValue->hide();
  mpEditCVObjectiveValue->hide();
  mpLblCVRMS->hide();
  mpEditCVRMS->hide();
  mpLblCVStdDeviation->hide();
  mpEditCVStdDeviation->hide();
#endif // not COPASI_CROSSVALIDATION

  const unsigned C_INT32 & FunctionEvaluations = pProblem->getFunctionEvaluations();
  mpEditEvaluations->setText(QString::number(FunctionEvaluations));
  const C_FLOAT64 & ExecutionTime = pProblem->getExecutionTime();
  mpEditCPUTime->setText(QString::number(ExecutionTime));
  mpEditSpeed->setText(QString::number(FunctionEvaluations / ExecutionTime));
}

void CQFittingResultTab1::init()
{}
