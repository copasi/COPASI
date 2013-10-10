// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
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
  : QWidget(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
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

void CQFittingResultTab1::load(const CFitProblem * pProblem)
{
  mpEditObjectiveValue->setText(QString::number(pProblem->getSolutionValue()));
  mpEditRMS->setText(QString::number(pProblem->getRMS()));
  mpEditStdDeviation->setText(QString::number(pProblem->getStdDeviation()));

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

  const unsigned C_INT32 & FunctionEvaluations = pProblem->getFunctionEvaluations();

  mpEditEvaluations->setText(QString::number(FunctionEvaluations));

  const C_FLOAT64 & ExecutionTime = pProblem->getExecutionTime();

  mpEditCPUTime->setText(QString::number(ExecutionTime));

  mpEditSpeed->setText(QString::number(FunctionEvaluations / ExecutionTime));
}

void CQFittingResultTab1::init()
{}
