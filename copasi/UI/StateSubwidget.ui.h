// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/StateSubwidget.ui.h,v $
//   $Revision: 1.30.2.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/02/08 14:39:47 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include <sstream>

#include "copasi.h"

#include "UI/qtUtilities.h"
#include "UI/listviews.h"

#include "model/CChemEqInterface.h"
#include "model/CModel.h"
#include "model/CMetabNameInterface.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "steadystate/CEigen.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "optimization/COptProblem.h"
#include "optimization/COptTask.h"

void StateSubwidget::init()
{
  topLabel->setText("");
  displayOptimizationTab(false);
  //bla
}

void StateSubwidget::displayOptimizationTab(bool displayOptTab)
{
  if (displayOptTab)
    {
      tabWidget->insertTab(TabPage, "OptimizationResults", 0);
      tabWidget->setCurrentPage(0);
    }
  else
    tabWidget->removePage(TabPage);
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
      numbersTable->setText(i, 1, QString::number(metabs[i]->getValue()));
      numbersTable->setText(i, 2, QString::number(metabs[i]->getRate()));
      numbersTable->setText(i, 3, QString::number(metabs[i]->getTransitionTime()));
    }

  return true;
}

bool StateSubwidget::loadReactions(CModel * model)
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

void StateSubwidget::loadModelValues(const CModel * model)
{

  CCopasiVectorN< CModelValue >::const_iterator it = model->getModelValues().begin();
  CCopasiVectorN< CModelValue >::const_iterator end = model->getModelValues().end();
  C_INT32 i = 0;

  mpModelValueTable->setNumRows(model->getModelValues().size());
  for (; it != end; ++it)
    if ((*it)->isUsed())
      {
        mpModelValueTable->setText(i, 0, FROM_UTF8((*it)->getObjectName()));
        mpModelValueTable->setText(i, 1, FROM_UTF8(CModelEntity::StatusName[(*it)->getStatus()]));
        mpModelValueTable->setText(i, 2, QString::number((*it)->getValue()));
        mpModelValueTable->setText(i, 3, QString::number((*it)->getRate()));
        i++;
      }

  mpModelValueTable->setNumRows(i);
  return;
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

  for (j = 0; j < jmax; ++j)
    tableJacobian->adjustColumn(j);

  QString name;
  CStateTemplate & StateTemplate = task->getProblem()->getModel()->getStateTemplate();
  CModelEntity **ppEntities = StateTemplate.getEntities();
  const unsigned C_INT32 * pUserOrder = StateTemplate.getUserOrder().array();
  const unsigned C_INT32 * pUserOrderEnd = pUserOrder + StateTemplate.getUserOrder().size();
  CMetab * pMetab;

  pUserOrder++; // We skip the time which is the first.

  for (i = 0; i < imax && pUserOrder != pUserOrderEnd; pUserOrder++)
    {
      const CModelEntity::Status & Status = ppEntities[*pUserOrder]->getStatus();
      if (Status == CModelEntity::ODE || Status == CModelEntity::REACTIONS)
        {
          if ((pMetab = dynamic_cast<CMetab *>(ppEntities[*pUserOrder])) != NULL)
            name = FROM_UTF8(CMetabNameInterface::getDisplayName(task->getProblem()->getModel(), *pMetab));
          else
            name = FROM_UTF8(ppEntities[*pUserOrder]->getObjectDisplayName());

          tableJacobian->horizontalHeader()->setLabel(i, name);
          tableJacobian->verticalHeader()->setLabel(i, name);

          i++;
        }
    }

  //Eigenvalues...
  const CVector< C_FLOAT64 > & eigen_i = task->getEigenValues().getI();
  const CVector< C_FLOAT64 > & eigen_r = task->getEigenValues().getR();

  imax = eigen_i.size();
  tableEigenValues->setNumRows(imax);
  for (i = 0; i < imax; ++i)
    {
      tableEigenValues->setText(i, 0, QString::number(eigen_r[i]));
      tableEigenValues->setText(i, 1, QString::number(eigen_i[i]));
    }

  for (j = 0; j < 2; ++j)
    tableEigenValues->adjustColumn(j);

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

  ppEntities = StateTemplate.beginIndependent();

  for (i = 0; i < imax; ++i, ++ppEntities)
    {
      if ((pMetab = dynamic_cast<CMetab *>(*ppEntities)) != NULL)
        name = FROM_UTF8(CMetabNameInterface::getDisplayName(task->getProblem()->getModel(), *pMetab));
      else
        name = FROM_UTF8((*ppEntities)->getObjectDisplayName());

      tableJacobianX->horizontalHeader()->setLabel(i, name);
      tableJacobianX->verticalHeader()->setLabel(i, name);
    }

  for (j = 0; j < jmax; ++j)
    tableJacobianX->adjustColumn(j);

  //Eigenvalues...
  const CVector< C_FLOAT64 > & eigen_iX = task->getEigenValuesReduced().getI();
  const CVector< C_FLOAT64 > & eigen_rX = task->getEigenValuesReduced().getR();

  imax = eigen_iX.size();
  tableEigenValuesX->setNumRows(imax);
  for (i = 0; i < imax; ++i)
    {
      tableEigenValuesX->setText(i, 0, QString::number(eigen_rX[i]));
      tableEigenValuesX->setText(i, 1, QString::number(eigen_iX[i]));
    }

  for (j = 0; j < 2; ++j)
    tableEigenValuesX->adjustColumn(j);

  //stability report
  stabilityTextEdit->setReadOnly(true);

  std::ostringstream ss;
  ss << task->getEigenValuesReduced();

  stabilityTextEdit->setText(FROM_UTF8(ss.str()));
  return;
}

void StateSubwidget::showUnits()
{
  //CCopasiDataModel::Global->getModel()->getVolumeUnit();

  concentrationsTable->horizontalHeader()->setLabel(concentrationsTable->numCols() - 1, tr("Transition Time\n("\
      + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnitName()) + ")"));

  concentrationsTable->horizontalHeader()->setLabel(concentrationsTable->numCols() - 2, tr("Rate\n(per "\
      + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnitName()) + ")"));

  concentrationsTable->horizontalHeader()->setLabel(concentrationsTable->numCols() - 3, tr("Concentration\n("\
      + FROM_UTF8(CCopasiDataModel::Global->getModel()->getConcentrationUnitName()) + ")"));

  numbersTable->horizontalHeader()->setLabel(numbersTable->numCols() - 1, tr("Transition Time\n("\
      + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnitName()) + ")"));
  numbersTable->horizontalHeader()->setLabel(numbersTable->numCols() - 2, tr("Rate\n(per "\
      + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnitName()) + ")"));

  tableFlux->horizontalHeader()->setLabel(numbersTable->numCols() - 3, tr("Flux\n("\
                                          + FROM_UTF8(CCopasiDataModel::Global->getModel()->getQuantityRateUnitName()) + ")"));

  tableFlux->horizontalHeader()->setLabel(numbersTable->numCols() - 2, tr("Particle flux\n(particle/"\
                                          + FROM_UTF8(CCopasiDataModel::Global->getModel()->getTimeUnitName()) + ")"));
}

bool StateSubwidget::loadAll(const CSteadyStateTask * task)
{
  CState * pState = const_cast<CState *>(task->getState());
  CModel * pModel = task->getProblem()->getModel();

  pModel->setState(*pState);
  pModel->updateSimulatedValues();

  pModel->updateNonSimulatedValues();

  // editing units here

  if (task->getResult() == CSteadyStateMethod::found)
    topLabel->setText("A steady state with given resolution was found.");
  else if (task->getResult() == CSteadyStateMethod::notFound)
    topLabel->setText("No steady state with given resolution was found!");
  else if (task->getResult() == CSteadyStateMethod::foundEquilibrium)
    topLabel->setText("An equilibrium steady state (zero fluxes) was found.");
  else if (task->getResult() == CSteadyStateMethod::foundNegative)
    topLabel->setText("An invalid steady state (negative concentrations) was found.");

  else
    topLabel->setText("A steady state with given resolution couldn't be found.");

  if (!loadMetabolites(pModel)) return false;
  if (!loadReactions(pModel)) return false;

  loadModelValues(pModel);

  const CSteadyStateProblem* pProblem =
    dynamic_cast<const CSteadyStateProblem *>(task->getProblem());
  assert(pProblem);

  int Last = tabWidget->count() - 1;

  // jacobian and stability
  if (pProblem->isJacobianRequested() ||
      pProblem->isStabilityAnalysisRequested())
    {
      tabWidget->setTabEnabled(tabWidget->page(Last - 3), true);
      tabWidget->setTabEnabled(tabWidget->page(Last - 2), true);
      tabWidget->setTabEnabled(tabWidget->page(Last - 1), true);
      loadJacobian(task);
    }

  else
    {
      tabWidget->setTabEnabled(tabWidget->page(Last - 3), false);
      tabWidget->setTabEnabled(tabWidget->page(Last - 2), false);
      tabWidget->setTabEnabled(tabWidget->page(Last - 1), false);
    }

  // protocol
  if (true /*pProblem->isJacobianRequested() ||
            pProblem->isStabilityAnalysisRequested()*/)
    {
      tabWidget->setTabEnabled(tabWidget->page(Last), true);

      //stabilityTextEdit->setReadOnly(true);

      //std::ostringstream ss;
      //ss << task->getEigenValuesReduced();
      const CSteadyStateMethod * pMethod =
        dynamic_cast<const CSteadyStateMethod *>(task->getMethod());
      assert(pMethod);
      protocolTextEdit->setText(FROM_UTF8(pMethod->getMethodLog()));
    }

  else
    {
      tabWidget->setTabEnabled(tabWidget->page(Last), false);
    }

  return true;
}

bool StateSubwidget::clear()
{
  topLabel->setText("No result available, please execute the steady-state task.");

  concentrationsTable->setNumRows(0);
  numbersTable->setNumRows(0);

  tableFlux->setNumRows(0);

  tableJacobian->setNumRows(0);
  tableJacobian->setNumCols(0);

  tableEigenValues->setNumRows(0);

  tableJacobianX->setNumRows(0);
  tableJacobianX->setNumCols(0);

  tableEigenValuesX->setNumRows(0);

  stabilityTextEdit->setText("");

  return true;
}
