// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/StateSubwidget.cpp,v $
//   $Revision: 1.30.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:13:00 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "StateSubwidget.h"

#include <qvariant.h>

#include <qfileinfo.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qpainter.h>
#include <q3picture.h>
#include <QMessageBox>

#include <sstream>

#include "copasi.h"
#include "CQArrayAnnotationsWidget.h"

#include "UI/qtUtilities.h"
#include "UI/listviews.h"
#include "UI/CopasiFileDialog.h"

#include "model/CChemEqInterface.h"
#include "model/CModel.h"
#include "model/CMetabNameInterface.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "steadystate/CEigen.h"
#include "optimization/COptProblem.h"
#include "optimization/COptTask.h"
#include "report/CCopasiRootContainer.h"

/*
 *  Constructs a StateSubwidget which is a child of 'parent', with the
 *  name 'name'.'
 */
StateSubwidget::StateSubwidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
StateSubwidget::~StateSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void StateSubwidget::languageChange()
{
  retranslateUi(this);
}

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
      mpTabWidget->insertTab(0, mpOptimizationPage, "OptimizationResults");
      mpTabWidget->setCurrentIndex(0);
    }
  else
    mpTabWidget->removeTab(mpTabWidget->indexOf(mpOptimizationPage));
}

void StateSubwidget::loadMetabolites()
{
  // Fill the table
  CCopasiVectorN< CMetab >::const_iterator it = mpModel->getMetabolites().begin();
  CCopasiVectorN< CMetab >::const_iterator end = mpModel->getMetabolites().end();
  C_INT32 i = 0;

  mpTblMetabolites->setNumRows((int) mpModel->getMetabolites().size());

  for (; it != end; ++it)
    if ((*it)->getStatus() == CModelEntity::ODE ||
        ((*it)->getStatus() == CModelEntity::REACTIONS && (*it)->isUsed()))
      {
        mpTblMetabolites->setText(i, 0, FROM_UTF8(CMetabNameInterface::getDisplayName(mpModel, **it)));
        mpTblMetabolites->setText(i, 1, FROM_UTF8(CModelEntity::StatusName[(*it)->getStatus()]));
        mpTblMetabolites->setText(i, 2, QString::number((*it)->getConcentration()));
        mpTblMetabolites->setText(i, 3, QString::number((*it)->getValue()));
        mpTblMetabolites->setText(i, 4, QString::number((*it)->getConcentrationRate()));
        mpTblMetabolites->setText(i, 5, QString::number((*it)->getRate()));
        mpTblMetabolites->setText(i, 6, QString::number((*it)->getTransitionTime()));

        i++;
      }

  mpTblMetabolites->setNumRows(i);

  mpTblMetabolites->adjustColumn(0);
  mpTblMetabolites->adjustColumn(1);
  mpTblMetabolites->adjustColumn(2);
  mpTblMetabolites->adjustColumn(3);
  mpTblMetabolites->adjustColumn(4);
  mpTblMetabolites->adjustColumn(5);
  mpTblMetabolites->adjustColumn(6);
}

void StateSubwidget::loadCompartments()
{
  CCopasiVectorN< CCompartment >::const_iterator it = mpModel->getCompartments().begin();
  CCopasiVectorN< CCompartment >::const_iterator end = mpModel->getCompartments().end();
  C_INT32 i = 0;

  mpTblCompartments->setNumRows((int) mpModel->getCompartments().size());

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

  mpTblReactions->setNumRows((int) mpModel->getReactions().size());

  for (; it != end; ++it)
    {
      mpTblReactions->setText(i, 0, FROM_UTF8((*it)->getObjectName()));
      mpTblReactions->setText(i, 1, QString::number((*it)->getFlux()));
      mpTblReactions->setText(i, 2, QString::number((*it)->getParticleFlux()));
      mpTblReactions->setText(i, 3, FROM_UTF8(CChemEqInterface::getChemEqString(mpModel, **it, false)));

      i++;
    }

  mpTblReactions->adjustColumn(0);
  mpTblReactions->adjustColumn(1);
  mpTblReactions->adjustColumn(2);
  mpTblReactions->adjustColumn(3);
}

void StateSubwidget::loadModelValues()
{
  CCopasiVectorN< CModelValue >::const_iterator it = mpModel->getModelValues().begin();
  CCopasiVectorN< CModelValue >::const_iterator end = mpModel->getModelValues().end();
  C_INT32 i = 0;

  mpTblModelValues->setNumRows((int) mpModel->getModelValues().size());

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

  size_t i, imax = eigen_i.size();
  tableEigenValues->setNumRows((int) imax);

  for (i = 0; i < imax; ++i)
    {
      tableEigenValues->setText((int) i, 0, QString::number(eigen_r[i]));
      tableEigenValues->setText((int) i, 1, QString::number(eigen_i[i]));
    }

  size_t j;

  for (j = 0; j < 2; ++j)
    tableEigenValues->adjustColumn((int) j);

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
  tableEigenValuesX->setNumRows((int) imax);

  for (i = 0; i < imax; ++i)
    {
      tableEigenValuesX->setText((int) i, 0, QString::number(eigen_rX[i]));
      tableEigenValuesX->setText((int) i, 1, QString::number(eigen_iX[i]));
    }

  for (j = 0; j < 2; ++j)
    tableEigenValuesX->adjustColumn((int) j);

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

  QString TimeUnits = FROM_UTF8(mpModel->getTimeUnitsDisplayString());

  if (!TimeUnits.isEmpty())
    TimeUnits = "\n(" + TimeUnits + ")";

  QString FrequencyUnits = FROM_UTF8(mpModel->getFrequencyUnitsDisplayString());

  if (!FrequencyUnits.isEmpty())
    FrequencyUnits = "\n(" + FrequencyUnits + ")";

  QString ConcentrationUnits = FROM_UTF8(mpModel->getConcentrationUnitsDisplayString());

  if (!ConcentrationUnits.isEmpty())
    ConcentrationUnits = "\n(" + ConcentrationUnits + ")";

  QString ConcentrationRateUnits = FROM_UTF8(mpModel->getConcentrationRateUnitsDisplayString());

  if (!ConcentrationRateUnits.isEmpty())
    ConcentrationRateUnits = "\n(" + ConcentrationRateUnits + ")";

  QString VolumeUnits = FROM_UTF8(mpModel->getVolumeUnitsDisplayString());

  if (!VolumeUnits.isEmpty())
    VolumeUnits = "\n(" + VolumeUnits + ")";

  QString VolumeRateUnits = FROM_UTF8(mpModel->getVolumeRateUnitsDisplayString());

  if (!VolumeRateUnits.isEmpty())
    VolumeRateUnits = "\n(" + VolumeRateUnits + ")";

  QString QuantityRateUnits = FROM_UTF8(mpModel->getQuantityRateUnitsDisplayString());

  if (!QuantityRateUnits.isEmpty())
    QuantityRateUnits = "\n(" + QuantityRateUnits + ")";

  mpTblCompartments->horizontalHeader()->setLabel(2, "Volume" + VolumeUnits);

  mpTblCompartments->horizontalHeader()->setLabel(3, "Rate" + VolumeRateUnits);

  mpTblMetabolites->horizontalHeader()->setLabel(2, "Concentration" + ConcentrationUnits);

  mpTblMetabolites->horizontalHeader()->setLabel(3, "Particle Numbers");

  mpTblMetabolites->horizontalHeader()->setLabel(4, "Rate" + ConcentrationRateUnits);

  mpTblMetabolites->horizontalHeader()->setLabel(5, "Rate" + FrequencyUnits);

  mpTblMetabolites->horizontalHeader()->setLabel(6, "Transition Time" + TimeUnits);

  mpTblReactions->horizontalHeader()->setLabel(1, "Flux" + QuantityRateUnits);

  mpTblReactions->horizontalHeader()->setLabel(2, "Particle Flux" + FrequencyUnits);
}

bool StateSubwidget::loadAll(const CSteadyStateTask * pTask)
{
  mpTask = pTask;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  mpModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

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

  loadMetabolites();
  loadCompartments();
  loadModelValues();
  loadReactions();

  const CSteadyStateProblem* pProblem =
    dynamic_cast<const CSteadyStateProblem *>(mpTask->getProblem());
  assert(pProblem);

  int Last = mpTabWidget->count() - 1;

  // enable/disable tab widgets

  // jacobian and stability
  if (pProblem->isJacobianRequested() ||
      pProblem->isStabilityAnalysisRequested())
    {
      mpTabWidget->setTabEnabled(Last - 3, true);
      mpTabWidget->setTabEnabled(Last - 2, true);
      mpTabWidget->setTabEnabled(Last - 1, true);

      loadJacobian();
    }

  else
    {
      mpTabWidget->setTabEnabled(Last - 3, false);
      mpTabWidget->setTabEnabled(Last - 2, false);
      mpTabWidget->setTabEnabled(Last - 1, false);
    }

  // protocol
  if (true)
    {
      mpTabWidget->setTabEnabled(Last, true);

      const CSteadyStateMethod * pMethod =
        dynamic_cast<const CSteadyStateMethod *>(mpTask->getMethod());
      assert(pMethod);
      protocolTextEdit->setText(FROM_UTF8(pMethod->getMethodLog()));
    }
  else
    {
      mpTabWidget->setTabEnabled(Last, false);
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

  // TODO hide/show columns
  switch (mFramework)
    {
      case 0:
        mpTblMetabolites->showColumn(2);
        mpTblMetabolites->hideColumn(3);
        mpTblMetabolites->showColumn(4);
        mpTblMetabolites->hideColumn(5);
        mpTblReactions->showColumn(1);
        mpTblReactions->hideColumn(2);
        break;

      case 1:
        mpTblMetabolites->hideColumn(2);
        mpTblMetabolites->showColumn(3);
        mpTblMetabolites->hideColumn(4);
        mpTblMetabolites->showColumn(5);
        mpTblReactions->hideColumn(1);
        mpTblReactions->showColumn(2);
        break;
    }

  showUnits();
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
              assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
              mpModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
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

