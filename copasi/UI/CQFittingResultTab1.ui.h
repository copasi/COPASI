/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingResultTab1.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/22 16:52:55 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include "copasi.h"

#include "parameterFitting/CFitProblem.h"
 #include "parameterFitting/CFitItem.h"
 #include "parameterFitting/CExperimentSet.h"
 #include "parameterFitting/CExperiment.h"

#include "qtUtilities.h"

void CQFittingResultTab1::load(const CFitProblem * pProblem)
{
  mpEditObjectiveValue->setText(QString::number(pProblem->getSolutionValue()));
  mpEditRMS->setText(QString::number(pProblem->getRMS()));
  mpEditStdDeviation->setText(QString::number(pProblem->getStdDeviation()));

  const unsigned C_INT32 & FunctionEvaluations = pProblem->getFunctionEvaluations();
  mpEditEvaluations->setText(QString::number(FunctionEvaluations));
  const C_FLOAT64 & ExecutionTime = pProblem->getExecutionTime();
  mpEditCPUTime->setText(QString::number(ExecutionTime));
  mpEditSpeed->setText(QString::number(FunctionEvaluations / ExecutionTime));
}

void CQFittingResultTab1::init()
{
}
