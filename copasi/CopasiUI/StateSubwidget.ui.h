/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/StateSubwidget.ui.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/06 10:01:00 $
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

#include "model/CChemEqInterface.h"
#include "qtUtilities.h"
#include "steadystate/CSteadyStateProblem.h"
#include "steadystate/CEigen.h"
#include <sstream>

void StateSubwidget::init()
{
  //bla
}

bool StateSubwidget::loadMetabolites(const CModel* model)
{
  const CCopasiVector<CMetab>& metabs = model->getMetabolites();
  C_INT32 i, imax = metabs.size();

  concentrationsTable->setNumRows(imax);
  numbersTable->setNumRows(imax);

  QString name;
  for (i = 0; i < imax; ++i)
    {
      name = FROM_UTF8(CMetabNameInterface::getDisplayName(model, *metabs[i]));

      concentrationsTable->setText(i, 0, name);
      concentrationsTable->setText(i, 1, QString::number(metabs[i]->getConcentration()));
      concentrationsTable->setText(i, 2, QString::number(metabs[i]->getConcentrationRate()));
      concentrationsTable->setText(i, 3, QString::number(metabs[i]->getTransitionTime()));

      numbersTable->setText(i, 0, name);
      numbersTable->setText(i, 1, QString::number(metabs[i]->getNumber()));
      numbersTable->setText(i, 2, QString::number(metabs[i]->getNumberRate()));
      numbersTable->setText(i, 3, QString::number(metabs[i]->getTransitionTime()));
    }

  return true;
}

bool StateSubwidget::loadReactions(const CModel * model)
{
  const CCopasiVector<CReaction>& reacs = model->getReactions();
  C_INT32 i, imax = reacs.size();

  tableFlux->setNumRows(imax);

  for (i = 0; i < imax; ++i)
    {
      tableFlux->setText(i, 0, FROM_UTF8(reacs[i]->getObjectName()));
      tableFlux->setText(i, 1, QString::number(reacs[i]->getFlux()));
      tableFlux->setText(i, 2, QString::number(reacs[i]->getParticleFlux()));
      tableFlux->setText(i, 3, FROM_UTF8(CChemEqInterface::getChemEqString(model, *reacs[i], false)));
    }
  return true;
}

void StateSubwidget::loadJacobian(const CSteadyStateTask * task)
{
  const CMatrix< C_FLOAT64 > & jacobian = task->getJacobian();

  tableJacobian->setNumRows(jacobian.numRows());
  tableJacobian->setNumCols(jacobian.numCols());

  C_INT32 i, imax = jacobian.numRows();
  C_INT32 j, jmax = jacobian.numCols();
  for (i = 0; i < imax; ++i)
    for (j = 0; j < jmax; ++j)
      {
        tableJacobian->setText(i, j, QString::number(jacobian(i, j)));
      }

  QString name;
  const CCopasiVector<CMetab>& metabs = task->getProblem()->getModel()->getMetabolites();
  for (i = 0; i < imax; ++i)
    {
      name = FROM_UTF8(CMetabNameInterface::getDisplayName(task->getProblem()->getModel(), *metabs[i]));
      tableJacobian->horizontalHeader()->setLabel(i, name);
      tableJacobian->verticalHeader()->setLabel(i, name);
    }

  //Eigenvalues...
  const CVector< C_FLOAT64 > & eigen_i = task->getEigenValues()->getEigen_i();
  const CVector< C_FLOAT64 > & eigen_r = task->getEigenValues()->getEigen_r();

  imax = eigen_i.size();
  tableEigenValues->setNumRows(imax);
  for (i = 0; i < imax; ++i)
    {
      tableEigenValues->setText(i, 0, QString::number(eigen_r[i]));
      tableEigenValues->setText(i, 1, QString::number(eigen_i[i]));
    }

  //JacobianX
  const CMatrix< C_FLOAT64 > & jacobianX = task->getJacobianReduced();

  tableJacobianX->setNumRows(jacobianX.numRows());
  tableJacobianX->setNumCols(jacobianX.numCols());

  imax = jacobianX.numRows();
  jmax = jacobianX.numCols();
  for (i = 0; i < imax; ++i)
    for (j = 0; j < jmax; ++j)
      {
        tableJacobianX->setText(i, j, QString::number(jacobianX(i, j)));
      }

  const CCopasiVector<CMetab>& metabsX = task->getProblem()->getModel()->getMetabolitesInd();
  for (i = 0; i < imax; ++i)
    {
      name = FROM_UTF8(CMetabNameInterface::getDisplayName(task->getProblem()->getModel(), *metabsX[i]));
      tableJacobianX->horizontalHeader()->setLabel(i, name);
      tableJacobianX->verticalHeader()->setLabel(i, name);
    }

  //Eigenvalues...
  const CVector< C_FLOAT64 > & eigen_iX = task->getEigenValuesReduced()->getEigen_i();
  const CVector< C_FLOAT64 > & eigen_rX = task->getEigenValuesReduced()->getEigen_r();

  imax = eigen_iX.size();
  tableEigenValuesX->setNumRows(imax);
  for (i = 0; i < imax; ++i)
    {
      tableEigenValuesX->setText(i, 0, QString::number(eigen_rX[i]));
      tableEigenValuesX->setText(i, 1, QString::number(eigen_iX[i]));
    }

  //stability report
  stabilityTextEdit->setReadOnly(true);

  std::ostringstream ss;
  ss << *task->getEigenValuesReduced();

  stabilityTextEdit->setText(FROM_UTF8(ss.str()));
}

bool StateSubwidget::loadAll(const CSteadyStateTask * task)
{
  const CState * pState = task->getState();
  const_cast<CModel *>(pState->getModel())->setState(pState);
  const_cast<CModel *>(pState->getModel())->updateRates();

  if (!loadMetabolites(pState->getModel())) return false;
  if (!loadReactions(pState->getModel())) return false;

  const CSteadyStateProblem* pProblem =
    dynamic_cast<const CSteadyStateProblem *>(task->getProblem());
  assert(pProblem);

  if (pProblem->isJacobianRequested() ||
      pProblem->isStabilityAnalysisRequested())
    {
      tabWidget->setTabEnabled(tabWidget->page(3), true);
      tabWidget->setTabEnabled(tabWidget->page(4), true);
      tabWidget->setTabEnabled(tabWidget->page(5), true);
      loadJacobian(task);
    }
  else
    {
      tabWidget->setTabEnabled(tabWidget->page(3), false);
      tabWidget->setTabEnabled(tabWidget->page(4), false);
      tabWidget->setTabEnabled(tabWidget->page(5), false);
    }

  return true;
}
