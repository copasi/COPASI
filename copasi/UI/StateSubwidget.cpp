// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "StateSubwidget.h"

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

void StateSubwidget::init()
{
  topLabel->setText("");

  mpModel = NULL;
  mpTask = NULL;

  setFramework(mFramework);
}

void StateSubwidget::loadMetabolites()
{
  // Fill the table
  CCopasiVectorN< CMetab >::const_iterator it = mpModel->getMetabolites().begin();
  CCopasiVectorN< CMetab >::const_iterator end = mpModel->getMetabolites().end();
  int i = 0;

  mpTblMetabolites->setRowCount((int) mpModel->getMetabolites().size());

  QTableWidgetItem * pItem;  // for use with setData method, to set numberical sorting of appropriate columns

  for (; it != end; ++it)
    if ((*it)->getStatus() == CModelEntity::ODE ||
        ((*it)->getStatus() == CModelEntity::REACTIONS && (*it)->isUsed()))
      {
        mpTblMetabolites->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(CMetabNameInterface::getDisplayName(mpModel, **it, false))));

        mpTblMetabolites->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(CModelEntity::StatusName[(*it)->getStatus()])));

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*it)->getConcentration());
        mpTblMetabolites->setItem(i, 2, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*it)->getValue());
        mpTblMetabolites->setItem(i, 3, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*it)->getConcentrationRate());
        mpTblMetabolites->setItem(i, 4, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*it)->getRate());
        mpTblMetabolites->setItem(i, 5, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*it)->getTransitionTime());
        mpTblMetabolites->setItem(i, 6, pItem);

        i++;
      }

  mpTblMetabolites->setRowCount(i);
  mpTblMetabolites->resizeColumnsToContents();
  mpTblMetabolites->resizeRowsToContents();
}

void StateSubwidget::loadCompartments()
{
  CCopasiVectorN< CCompartment >::const_iterator it = mpModel->getCompartments().begin();
  CCopasiVectorN< CCompartment >::const_iterator end = mpModel->getCompartments().end();
  C_INT32 i = 0;

  mpTblCompartments->setRowCount((int) mpModel->getCompartments().size());

  QTableWidgetItem * pItem;

  for (; it != end; ++it)
    if ((*it)->getStatus() == CModelEntity::ODE)
      {
        mpTblCompartments->setItem(i, 0, new QTableWidgetItem(FROM_UTF8((*it)->getObjectName())));
        mpTblCompartments->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(CModelEntity::StatusName[(*it)->getStatus()])));

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*it)->getValue());
        mpTblCompartments->setItem(i, 2, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*it)->getRate());
        mpTblCompartments->setItem(i, 3, pItem);

        i++;
      }

  mpTblCompartments->setRowCount(i);
  mpTblCompartments->resizeColumnsToContents();
  mpTblCompartments->resizeRowsToContents();
}

void StateSubwidget::loadReactions()
{
  // Fill the table
  CCopasiVectorN< CReaction >::const_iterator it = mpModel->getReactions().begin();
  CCopasiVectorN< CReaction >::const_iterator end = mpModel->getReactions().end();
  C_INT32 i = 0;

  mpTblReactions->setRowCount((int) mpModel->getReactions().size());

  QTableWidgetItem * pItem;

  for (; it != end; ++it)
    {
      mpTblReactions->setItem(i, 0, new QTableWidgetItem(FROM_UTF8((*it)->getObjectName())));

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, (*it)->getFlux());
      mpTblReactions->setItem(i, 1, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, (*it)->getParticleFlux());
      mpTblReactions->setItem(i, 2, pItem);

      mpTblReactions->setItem(i, 3, new QTableWidgetItem(FROM_UTF8(CChemEqInterface::getChemEqString(mpModel, **it, false))));

      i++;
    }

  mpTblReactions->resizeColumnsToContents();
  mpTblReactions->resizeRowsToContents();
}

void StateSubwidget::loadModelValues()
{
  CCopasiVectorN< CModelValue >::const_iterator it = mpModel->getModelValues().begin();
  CCopasiVectorN< CModelValue >::const_iterator end = mpModel->getModelValues().end();
  C_INT32 i = 0;

  mpTblModelValues->setRowCount((int) mpModel->getModelValues().size());

  QTableWidgetItem * pItem;

  for (; it != end; ++it)
    if ((*it)->getStatus() == CModelEntity::ODE)
      {
        mpTblModelValues->setItem(i, 0, new QTableWidgetItem(FROM_UTF8((*it)->getObjectName())));
        mpTblModelValues->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(CModelEntity::StatusName[(*it)->getStatus()])));

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*it)->getValue());
        mpTblModelValues->setItem(i, 2, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*it)->getRate());
        mpTblModelValues->setItem(i, 3, pItem);

        i++;
      }

  mpTblModelValues->setRowCount(i);
  mpTblModelValues->resizeColumnsToContents();
  mpTblModelValues->resizeRowsToContents();
}

void StateSubwidget::loadJacobian()
{
  const CArrayAnnotation * JacAnn = mpTask->getJacobianAnnotated();

  CColorScaleBiLog * tcs = new CColorScaleBiLog();
  mpJacobianAnnotationWidget->setColorCoding(tcs);
  mpJacobianAnnotationWidget->setColorScalingAutomatic(true);
  mpJacobianAnnotationWidget->setLegendEnabled(false);
  mpJacobianAnnotationWidget->setArrayAnnotation(JacAnn);

  QTableWidgetItem * pItem;

  //Eigenvalues...
  const CVector< C_FLOAT64 > & eigen_r = mpTask->getEigenValues().getR();
  const CVector< C_FLOAT64 > & eigen_i = mpTask->getEigenValues().getI();

  size_t i, imax = eigen_i.size();
  tableEigenValues->setRowCount((int) imax);

  for (i = 0; i < imax; ++i)
    {
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, eigen_r[i]);
      tableEigenValues->setItem((int) i, 0, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, eigen_i[i]);
      tableEigenValues->setItem((int) i, 1, pItem);
    }

  tableEigenValues->resizeColumnsToContents();
  tableEigenValues->resizeRowsToContents();

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
  tableEigenValuesX->setRowCount((int) imax);

  for (i = 0; i < imax; ++i)
    {
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, eigen_rX[i]);
      tableEigenValuesX->setItem((int) i, 0, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, eigen_iX[i]);
      tableEigenValuesX->setItem((int) i, 1, pItem);
    }

  tableEigenValuesX->resizeColumnsToContents();
  tableEigenValuesX->resizeRowsToContents();

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

  mpTblCompartments->horizontalHeaderItem(2)->setText("Volume" + VolumeUnits);
  mpTblCompartments->horizontalHeaderItem(3)->setText("Rate" + VolumeRateUnits);

  mpTblMetabolites->horizontalHeaderItem(2)->setText("Concentration" + ConcentrationUnits);
  mpTblMetabolites->horizontalHeaderItem(3)->setText("Particle Numbers");
  mpTblMetabolites->horizontalHeaderItem(4)->setText("Rate" + ConcentrationRateUnits);
  mpTblMetabolites->horizontalHeaderItem(5)->setText("Rate" + FrequencyUnits);
  mpTblMetabolites->horizontalHeaderItem(6)->setText("Transition Time" + TimeUnits);

  mpTblReactions->horizontalHeaderItem(1)->setText("Flux" + QuantityRateUnits);
  mpTblReactions->horizontalHeaderItem(2)->setText("Particle Flux" + FrequencyUnits);
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

  mpTblMetabolites->setRowCount(0);
  mpTblCompartments->setRowCount(0);
  mpTblModelValues->setRowCount(0);
  mpTblReactions->setRowCount(0);

  mpJacobianAnnotationWidget->setArrayAnnotation(NULL);
  mpJacobianXAnnotationWidget->setArrayAnnotation(NULL);

  tableEigenValues->setRowCount(0);
  tableEigenValuesX->setRowCount(0);

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
