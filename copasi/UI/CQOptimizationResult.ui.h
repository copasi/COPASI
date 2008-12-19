// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQOptimizationResult.ui.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/14 19:47:24 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

#include "qheader.h"
#include "qregexp.h"

#include "UI/CopasiFileDialog.h"
#include "UI/CQMessageBox.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "optimization/COptTask.h"
#include "optimization/COptProblem.h"
#include "optimization/COptItem.h"

#include "UI/qtUtilities.h"

void CQOptimizationResult::init()
{
  unsigned C_INT32 i, imax;

  // Set up the parameters table
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Parameter"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Value"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Gradient"));
  mpParameters->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, mpParameters->sizePolicy().hasHeightForWidth()));
  mpParameters->setNumRows(0);
  mpParameters->setNumCols(3);
  mpParameters->setReadOnly(TRUE);

  for (i = 0, imax = mpParameters->numCols(); i != imax; i++)
    mpParameters->adjustColumn(i);
}

bool CQOptimizationResult::update(ListViews::ObjectType /* objectType */,
                                  ListViews::Action /* action */,
                                  const std::string & /* key */)
{
  // :TODO:
  return true;
}

bool CQOptimizationResult::leave()
{
  // :TODO:
  return true;
}

bool CQOptimizationResult::enter(const std::string & /* key */)
{
  mpTask =
    dynamic_cast<COptTask *>((*CCopasiDataModel::Global->getTaskList())["Optimization"]);
  if (!mpTask) return false;

  mpProblem = dynamic_cast<const COptProblem *>(mpTask->getProblem());
  if (!mpProblem) return false;

  // Objective Value
  mpEditObjectiveValue->setText(QString::number(mpProblem->getSolutionValue()));

  // Performance Statistics
  const unsigned C_INT32 & FunctionEvaluations = mpProblem->getFunctionEvaluations();
  mpEditEvaluations->setText(QString::number(FunctionEvaluations));
  const C_FLOAT64 & ExecutionTime = mpProblem->getExecutionTime();
  mpEditCPUTime->setText(QString::number(ExecutionTime));
  mpEditSpeed->setText(QString::number(FunctionEvaluations / ExecutionTime));

  unsigned C_INT32 i, imax;

  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  const CVector< C_FLOAT64 > & Solutions = mpProblem->getSolutionVariables();
  const CVector< C_FLOAT64 > & Gradients = mpProblem->getVariableGradients();

  imax = Items.size();
  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpParameters->setNumRows(imax);
  for (i = 0; i != imax; i++)
    {
      const CCopasiObject *pObject =
        RootContainer.getObject(Items[i]->getObjectCN());
      if (pObject)
        mpParameters->setText(i, 0, FROM_UTF8(pObject->getObjectDisplayName()));
      else
        mpParameters->setText(i, 0, "Not Found");

      const C_FLOAT64 & Solution = Solutions[i];
      mpParameters->setText(i, 1, QString::number(Solution));
      mpParameters->setText(i, 2, QString::number(Gradients[i]));
    }

  for (i = 0, imax = mpParameters->numCols(); i != imax; i++)
    mpParameters->adjustColumn(i);

  return true;
}

void CQOptimizationResult::slotSave(void)
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          QString::null, "TEXT Files (*.txt);;All Files (*.*);;", "Save to");

      if (fileName.isEmpty()) return;

      if (!fileName.endsWith(".txt") &&
          !fileName.endsWith(".")) fileName += ".txt";

      fileName = fileName.remove(QRegExp("\\.$"));

      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(utf8ToLocale((const char *) fileName.utf8()).c_str());
  if (file.fail()) return;

  unsigned C_INT32 i, imax;

  // The global result and statistics
  file << "Objective Value" << std::endl;
  file << mpProblem->getSolutionValue() << std::endl;

  file << "Function Evaluations\tCPU Time [s]\tEvaluations/second [1/s]" << std::endl;
  const unsigned C_INT32 & FunctionEvaluations = mpProblem->getFunctionEvaluations();
  const C_FLOAT64 & ExecutionTime = mpProblem->getExecutionTime();
  file << FunctionEvaluations << "\t";
  file << ExecutionTime << "\t";
  file << FunctionEvaluations / ExecutionTime << std::endl;

  // Set up the parameters table
  file << std::endl << "Parameters:" << std::endl;
  file << "Parameter\tValue\tGradient" << std::endl;

  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  const CVector< C_FLOAT64 > & Solutions = mpProblem->getSolutionVariables();
  const CVector< C_FLOAT64 > & Gradients = mpProblem->getVariableGradients();

  imax = Items.size();
  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  for (i = 0; i != imax; i++)
    {
      const CCopasiObject *pObject =
        RootContainer.getObject(Items[i]->getObjectCN());
      if (pObject)
        file << pObject->getObjectDisplayName() << "\t";
      else
        file << "Not Found\t";

      const C_FLOAT64 & Solution = Solutions[i];
      file << Solution << "\t";
      file << Gradients[i] << std::endl;
    }
}

void CQOptimizationResult::slotUpdateModel()
{
  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  std::vector<COptItem * >::const_iterator it = Items.begin();
  std::vector<COptItem * >::const_iterator end = Items.end();

  const C_FLOAT64 * pTmp;

  pTmp = mpProblem->getSolutionVariables().array();

  for (; it != end; ++it, pTmp++)
    {
      (*(*it)->COptItem::getUpdateMethod())(*pTmp);
      (*it)->setStartValue(*pTmp);
    }
}
