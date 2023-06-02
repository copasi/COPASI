// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/copasi.h"

#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/parameterFitting/CFitItem.h"
#include "copasi/parameterFitting/CExperimentSet.h"
#include "copasi/parameterFitting/CExperiment.h"

#include "copasi/UI/qtUtilities.h"

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
  mpEditObjectiveValue->setText(convertToQString(pProblem->getSolutionValue()));
  mpEditRMS->setText(convertToQString(pProblem->getRMS()));
  mpEditStdDeviation->setText(convertToQString(pProblem->getStdDeviation()));

  size_t validValueCount = pProblem->getExperimentSet().getValidValueCount();
  size_t totalValueCount = pProblem->getExperimentSet().getDataPointCount();

  if (validValueCount != totalValueCount)
    mpEditNumValidDataPoints->setText(QString("%1 (of %2)").arg(
                                        QString::number(validValueCount),
                                        QString::number(totalValueCount)));
  else
    mpEditNumValidDataPoints->setText(QString::number(validValueCount));

  bool Enable = (pProblem->getCrossValidationSet().getExperimentCount() > 0);

  mpLblCVObjectiveValue->setEnabled(Enable);
  mpEditCVObjectiveValue->setEnabled(Enable);
  mpLblCVRMS->setEnabled(Enable);
  mpEditCVRMS->setEnabled(Enable);
  mpLblCVStdDeviation->setEnabled(Enable);
  mpEditCVStdDeviation->setEnabled(Enable);
  mpLabelCVNumValidDataPoints->setEnabled(Enable);
  mpEditCVNumValidDataPoints->setEnabled(Enable);

  if (Enable)
    {
      mpEditCVObjectiveValue->setText(convertToQString(pProblem->getCrossValidationSolutionValue()));
      mpEditCVRMS->setText(convertToQString(pProblem->getCrossValidationRMS()));
      mpEditCVStdDeviation->setText(convertToQString(pProblem->getCrossValidationSD()));
      validValueCount = pProblem->getCrossValidationSet().getValidValueCount();
      totalValueCount = pProblem->getCrossValidationSet().getDataPointCount();

      if (validValueCount != totalValueCount)
        mpEditCVNumValidDataPoints->setText(QString("%1 (of %2)").arg(
                                              QString::number(validValueCount),
                                              QString::number(totalValueCount)));
      else
        mpEditCVNumValidDataPoints->setText(QString::number(validValueCount));
    }
  else
    {
      mpEditCVObjectiveValue->setText("");
      mpEditCVRMS->setText("");
      mpEditCVStdDeviation->setText("");
      mpEditCVNumValidDataPoints->setText("");
    }

  const unsigned C_INT32 & FunctionEvaluations = pProblem->getFunctionEvaluations();

  mpEditEvaluations->setText(QString::number(FunctionEvaluations));

  const C_FLOAT64 & ExecutionTime = pProblem->getExecutionTime();

  mpEditCPUTime->setText(convertToQString(ExecutionTime));

  mpEditSpeed->setText(convertToQString(FunctionEvaluations / ExecutionTime));
  const unsigned C_INT32 & FailedEvaluationsExc = pProblem->getFailedEvaluationsExc();
  mpEditFailedEvaluationsExc->setText(QString::number(FailedEvaluationsExc));
  const unsigned C_INT32 & FailedEvaluationsNaN = pProblem->getFailedEvaluationsNaN();
  mpEditFailedEvaluationsNaN->setText(QString::number(FailedEvaluationsNaN));

  mpEditConstraint->setText(QString::number(pProblem->getConstraintEvaluations()));
  mpEditFailedConstraint->setText(QString::number(pProblem->geFailedConstraintCounter()));
}

void CQFittingResultTab1::init()
{}
