// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/StateSubwidget.ui.h,v $
//   $Revision: 1.37 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/27 11:54:24 $
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

#include <qfileinfo.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qpainter.h>
#include <qpicture.h>

#include <sstream>

#include "copasi.h"

#include "UI/qtUtilities.h"
#include "UI/listviews.h"

#include "CQPrintAsDialog.h"
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

  mpModel = NULL;
  mpTask = NULL;

  setFramework(mFramework);
}

void StateSubwidget::displayOptimizationTab(bool displayOptTab)
{
  if (displayOptTab)
    {
      mpTabWidget->insertTab(mpOptimizationPage, "OptimizationResults", 0);
      mpTabWidget->setCurrentPage(0);
    }
  else
    mpTabWidget->removePage(mpOptimizationPage);
}

void StateSubwidget::loadMetabolites()
{
  // Fill the table
  CCopasiVectorN< CMetab >::const_iterator it = mpModel->getMetabolites().begin();
  CCopasiVectorN< CMetab >::const_iterator end = mpModel->getMetabolites().end();
  C_INT32 i = 0;

  mpTblMetabolites->setNumRows(mpModel->getMetabolites().size());

  for (; it != end; ++it)
    if ((*it)->getStatus() == CModelEntity::ODE ||
        ((*it)->getStatus() == CModelEntity::REACTIONS && (*it)->isUsed()))
      {
        mpTblMetabolites->setText(i, 0, FROM_UTF8(CMetabNameInterface::getDisplayName(mpModel, **it)));
        mpTblMetabolites->setText(i, 1, FROM_UTF8(CModelEntity::StatusName[(*it)->getStatus()]));

        switch (mFramework)
          {
          case 0:
            mpTblMetabolites->setText(i, 2, QString::number((*it)->getConcentration()));
            mpTblMetabolites->setText(i, 3, QString::number((*it)->getConcentrationRate()));
            break;

          case 1:
            mpTblMetabolites->setText(i, 2, QString::number((*it)->getValue()));
            mpTblMetabolites->setText(i, 3, QString::number((*it)->getRate()));
            break;
          }

        mpTblMetabolites->setText(i, 4, QString::number((*it)->getTransitionTime()));
        i++;
      }

  mpTblMetabolites->setNumRows(i);

  mpTblMetabolites->adjustColumn(0);
  mpTblMetabolites->adjustColumn(1);
  mpTblMetabolites->adjustColumn(2);
  mpTblMetabolites->adjustColumn(3);
  mpTblMetabolites->adjustColumn(4);
}

void StateSubwidget::loadCompartments()
{
  CCopasiVectorN< CCompartment >::const_iterator it = mpModel->getCompartments().begin();
  CCopasiVectorN< CCompartment >::const_iterator end = mpModel->getCompartments().end();
  C_INT32 i = 0;

  mpTblCompartments->setNumRows(mpModel->getCompartments().size());

  for (; it != end; ++it)
    if ((*it)->getStatus() == CModelEntity::ODE)
      {
        mpTblCompartments->setText(i, 0, FROM_UTF8((*it)->getObjectName()));
        mpTblCompartments->setText(i, 1, FROM_UTF8(CModelEntity::StatusName[(*it)->getStatus()]));
        mpTblCompartments->setText(i, 2, QString::number((*it)->getValue()));
        mpTblCompartments->setText(i, 3, QString::number((*it)->getRate()));
        i++;
      }

  mpTblCompartments->setNumRows(i);

  mpTblCompartments->adjustColumn(0);
  mpTblCompartments->adjustColumn(1);
  mpTblCompartments->adjustColumn(2);
  mpTblCompartments->adjustColumn(3);
}

void StateSubwidget::loadReactions()
{
  // Fill the table
  CCopasiVectorN< CReaction >::const_iterator it = mpModel->getReactions().begin();
  CCopasiVectorN< CReaction >::const_iterator end = mpModel->getReactions().end();
  C_INT32 i = 0;

  mpTblReactions->setNumRows(mpModel->getReactions().size());

  for (; it != end; ++it)
    {
      mpTblReactions->setText(i, 0, FROM_UTF8((*it)->getObjectName()));

      switch (mFramework)
        {
        case 0:
          mpTblReactions->setText(i, 1, QString::number((*it)->getFlux()));
          break;

        case 1:
          mpTblReactions->setText(i, 1, QString::number((*it)->getParticleFlux()));
          break;
        }

      mpTblReactions->setText(i, 2, FROM_UTF8(CChemEqInterface::getChemEqString(mpModel, **it, false)));
      i++;
    }

  mpTblReactions->adjustColumn(0);
  mpTblReactions->adjustColumn(1);
  mpTblReactions->adjustColumn(2);
}

void StateSubwidget::loadModelValues()
{
  CCopasiVectorN< CModelValue >::const_iterator it = mpModel->getModelValues().begin();
  CCopasiVectorN< CModelValue >::const_iterator end = mpModel->getModelValues().end();
  C_INT32 i = 0;

  mpTblModelValues->setNumRows(mpModel->getModelValues().size());
  for (; it != end; ++it)
    if ((*it)->getStatus() == CModelEntity::ODE)
      {
        mpTblModelValues->setText(i, 0, FROM_UTF8((*it)->getObjectName()));
        mpTblModelValues->setText(i, 1, FROM_UTF8(CModelEntity::StatusName[(*it)->getStatus()]));
        mpTblModelValues->setText(i, 2, QString::number((*it)->getValue()));
        mpTblModelValues->setText(i, 3, QString::number((*it)->getRate()));
        i++;
      }

  mpTblModelValues->setNumRows(i);

  mpTblModelValues->adjustColumn(0);
  mpTblModelValues->adjustColumn(1);
  mpTblModelValues->adjustColumn(2);
  mpTblModelValues->adjustColumn(3);
}

void StateSubwidget::loadJacobian()
{
  const CArrayAnnotation * JacAnn = mpTask->getJacobianAnnotated();

  CColorScaleBiLog * tcs = new CColorScaleBiLog();
  mpJacobianAnnotationWidget->setColorCoding(tcs);
  mpJacobianAnnotationWidget->setColorScalingAutomatic(true);
  mpJacobianAnnotationWidget->setLegendEnabled(false);
  mpJacobianAnnotationWidget->setArrayAnnotation(JacAnn);

  //Eigenvalues...
  const CVector< C_FLOAT64 > & eigen_i = mpTask->getEigenValues().getI();
  const CVector< C_FLOAT64 > & eigen_r = mpTask->getEigenValues().getR();

  unsigned C_INT32 i, imax = eigen_i.size();
  tableEigenValues->setNumRows(imax);
  for (i = 0; i < imax; ++i)
    {
      tableEigenValues->setText(i, 0, QString::number(eigen_r[i]));
      tableEigenValues->setText(i, 1, QString::number(eigen_i[i]));
    }

  unsigned C_INT32 j;
  for (j = 0; j < 2; ++j)
    tableEigenValues->adjustColumn(j);

  //JacobianX

  const CArrayAnnotation * JacXAnn = mpTask->getJacobianXAnnotated();

  tcs = new CColorScaleBiLog();
  mpJacobianXAnnotationWidget->setColorCoding(tcs);
  mpJacobianXAnnotationWidget->setColorScalingAutomatic(true);
  mpJacobianXAnnotationWidget->setLegendEnabled(false);
  mpJacobianXAnnotationWidget->setArrayAnnotation(JacXAnn);

  //Eigenvalues...
  const CVector< C_FLOAT64 > & eigen_iX = mpTask->getEigenValuesReduced().getI();
  const CVector< C_FLOAT64 > & eigen_rX = mpTask->getEigenValuesReduced().getR();

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
  ss << mpTask->getEigenValuesReduced();

  stabilityTextEdit->setText(FROM_UTF8(ss.str()));
  return;
}

void StateSubwidget::showUnits()
{
  if (mpModel == NULL)
    return;

  // Update the column titles

  QString TimeUnits(FROM_UTF8(mpModel->getTimeUnitName()));
  QString ConcentrationUnits(FROM_UTF8(mpModel->getConcentrationUnitName()));
  QString VolumeUnits(FROM_UTF8(mpModel->getVolumeUnitName()));

  mpTblMetabolites->horizontalHeader()
  ->setLabel(4, "Transition Time\n(" + TimeUnits + ")");

  mpTblCompartments->horizontalHeader()
  ->setLabel(2, "Volume\n(" + VolumeUnits + ")");

  mpTblCompartments->horizontalHeader()
  ->setLabel(3, "Rate\n(" + VolumeUnits + "/" + TimeUnits + ")");

  switch (mFramework)
    {
    case 0:
      mpTblMetabolites->horizontalHeader()
      ->setLabel(2, "Concentration\n(" + ConcentrationUnits + ")");

      mpTblMetabolites->horizontalHeader()
      ->setLabel(3, "Rate\n(" + ConcentrationUnits + "/" + TimeUnits + ")");

      mpTblReactions->horizontalHeader()
      ->setLabel(1, "Flux\n(" + FROM_UTF8(mpModel->getQuantityRateUnitName()) + ")");
      break;

    case 1:
      mpTblMetabolites->horizontalHeader()
      ->setLabel(2, "Particle Numbers");

      mpTblMetabolites->horizontalHeader()
      ->setLabel(3, "Rate\n(#/" + TimeUnits + ")");

      mpTblReactions->horizontalHeader()
      ->setLabel(1, "Particle Flux\n(#/" + TimeUnits + ")");
      break;
    }
}

bool StateSubwidget::loadAll(const CSteadyStateTask * pTask)
{
  mpTask = pTask;
  mpModel = CCopasiDataModel::Global->getModel();

  if (mpTask == NULL || mpModel == NULL)
    {
      clear();
      return false;
    }

  CState * pState = const_cast<CState *>(mpTask->getState());
  mpModel->setState(*pState);
  mpModel->updateSimulatedValues(true);
  mpModel->updateNonSimulatedValues();

  if (mpTask->getResult() == CSteadyStateMethod::found)
    topLabel->setText("A steady state with given resolution was found.");
  else if (mpTask->getResult() == CSteadyStateMethod::notFound)
    topLabel->setText("No steady state with given resolution was found!");
  else if (mpTask->getResult() == CSteadyStateMethod::foundEquilibrium)
    topLabel->setText("An equilibrium steady state (zero fluxes) was found.");
  else if (mpTask->getResult() == CSteadyStateMethod::foundNegative)
    topLabel->setText("An invalid steady state (negative concentrations) was found.");
  else
    topLabel->setText("A steady state with given resolution couldn't be found.");

  setFramework(mFramework);

  loadCompartments();
  loadModelValues();

  const CSteadyStateProblem* pProblem =
    dynamic_cast<const CSteadyStateProblem *>(mpTask->getProblem());
  assert(pProblem);

  int Last = mpTabWidget->count() - 1;

  // jacobian and stability
  if (pProblem->isJacobianRequested() ||
      pProblem->isStabilityAnalysisRequested())
    {
      mpTabWidget->setTabEnabled(mpTabWidget->page(Last - 3), true);
      mpTabWidget->setTabEnabled(mpTabWidget->page(Last - 2), true);
      mpTabWidget->setTabEnabled(mpTabWidget->page(Last - 1), true);
      loadJacobian();
    }

  else
    {
      mpTabWidget->setTabEnabled(mpTabWidget->page(Last - 3), false);
      mpTabWidget->setTabEnabled(mpTabWidget->page(Last - 2), false);
      mpTabWidget->setTabEnabled(mpTabWidget->page(Last - 1), false);
    }

  // protocol
  if (true)
    {
      mpTabWidget->setTabEnabled(mpTabWidget->page(Last), true);

      const CSteadyStateMethod * pMethod =
        dynamic_cast<const CSteadyStateMethod *>(mpTask->getMethod());
      assert(pMethod);
      protocolTextEdit->setText(FROM_UTF8(pMethod->getMethodLog()));
    }
  else
    {
      mpTabWidget->setTabEnabled(mpTabWidget->page(Last), false);
    }

  return true;
}

void StateSubwidget::clear()
{
  topLabel->setText("No result available, please execute the steady-state task.");

  mpTblMetabolites->setNumRows(0);
  mpTblCompartments->setNumRows(0);
  mpTblModelValues->setNumRows(0);
  mpTblReactions->setNumRows(0);

  mpJacobianAnnotationWidget->setArrayAnnotation(NULL);
  mpJacobianXAnnotationWidget->setArrayAnnotation(NULL);

  tableEigenValues->setNumRows(0);
  tableEigenValuesX->setNumRows(0);

  stabilityTextEdit->setText("");
  protocolTextEdit->setText("");
}

void StateSubwidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  showUnits();

  if (mpModel == NULL)
    return;

  loadMetabolites();
  loadReactions();
}

bool StateSubwidget::update(ListViews::ObjectType objectType,
                            ListViews::Action action,
                            const std::string & /* key */)
{
  switch (objectType)
    {
    case ListViews::MODEL:
      // For a new model we need to remove references to no longer existing metabolites
      switch (action)
        {
        case ListViews::ADD:
          mpModel = CCopasiDataModel::Global->getModel();
          clear();
          showUnits();
          mpTask = NULL;
          break;

        case ListViews::CHANGE:
          showUnits();
          break;

        default:
          break;
        }
      break;

    default:
      break;
    }

  return true;
}

void StateSubwidget::printAsImage()
{
  CQPrintAsDialog *pDialog = new CQPrintAsDialog();

  if (pDialog->exec() == QDialog::Accepted)
    {
      QString sFileName = pDialog->mpEditFileName->text();
      QFileInfo fileInfo(sFileName);
      QString sName = fileInfo.baseName();

      QPixmap pixmap = QPixmap::grabWidget(mpTabWidget->currentPage());

      if (pDialog->mpCBPNG->isChecked()) // true
        {
          QString sNamePNG = sName + ".png";
          pixmap.save(sNamePNG, "PNG");
        }

      if (pDialog->mpCBSVG->isChecked()) // true
        {
          QString sNameSVG = sName + ".svg";

          QPicture pict;
          QPainter paint;
          paint.begin(&pict);
          paint.drawPixmap(0, 0, pixmap);
          paint.end();

          pict.save(sNameSVG, "SVG");
        }
    }
}
