// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "StateSubwidget.h"

#include <sstream>
#include <qmath.h>

#include "copasi/copasi.h"
#include "CQArrayAnnotationsWidget.h"

#include "qtUtilities.h"
#include "listviews.h"
#include "CopasiFileDialog.h"

#include "copasi/model/CChemEqInterface.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CSteadyStateProblem.h"
#include "copasi/steadystate/CEigen.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/optimization/COptTask.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include <copasi/commandline/CConfigurationFile.h>

/*
 *  Constructs a StateSubwidget which is a child of 'parent', with the
 *  name 'name'.'
 */
StateSubwidget::StateSubwidget(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
  , mpModel(NULL)
  , mpTask(NULL)
{
  setupUi(this);

  topLabel->setText("");

  mpJacobianAnnotationWidget->setSortingEnabled(true);
  mpJacobianXAnnotationWidget->setSortingEnabled(true);

  setFramework(mFramework);
}

/*
 *  Destroys the object and frees any allocated resources
 */
StateSubwidget::~StateSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void StateSubwidget::loadMetabolites()
{
  // Fill the table
  CDataVectorN< CMetab >::const_iterator it = mpModel->getMetabolites().begin();
  CDataVectorN< CMetab >::const_iterator end = mpModel->getMetabolites().end();
  int i = 0;

  mpTblMetabolites->setRowCount((int) mpModel->getMetabolites().size());

  QTableWidgetItem * pItem;  // for use with setData method, to set numerical sorting of appropriate columns

  mpTblMetabolites->setSortingEnabled(false);

  for (; it != end; ++it)
    if (it->getStatus() == CModelEntity::Status::ODE ||
        (it->getStatus() == CModelEntity::Status::REACTIONS && it->isUsed()))
      {
        mpTblMetabolites->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(CMetabNameInterface::getDisplayName(mpModel, *it, false))));

        mpTblMetabolites->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(CModelEntity::StatusName[it->getStatus()])));

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, it->getConcentration());
        mpTblMetabolites->setItem(i, 2, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, it->getValue());
        mpTblMetabolites->setItem(i, 3, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, it->getConcentrationRate());
        mpTblMetabolites->setItem(i, 4, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, it->getRate());
        mpTblMetabolites->setItem(i, 5, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, it->getTransitionTime());
        mpTblMetabolites->setItem(i, 6, pItem);

        i++;
      }

  mpTblMetabolites->setRowCount(i);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblMetabolites->resizeColumnsToContents();
      mpTblMetabolites->resizeRowsToContents();
    }

  mpTblMetabolites->setSortingEnabled(true);
}

void StateSubwidget::loadCompartments()
{
  CDataVectorN< CCompartment >::const_iterator it = mpModel->getCompartments().begin();
  CDataVectorN< CCompartment >::const_iterator end = mpModel->getCompartments().end();
  C_INT32 i = 0;

  mpTblCompartments->setRowCount((int) mpModel->getCompartments().size());

  mpTblCompartments->setSortingEnabled(false);

  QTableWidgetItem * pItem;

  for (; it != end; ++it)
    if (it->getStatus() == CModelEntity::Status::ODE)
      {
        mpTblCompartments->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(it->getObjectName())));
        mpTblCompartments->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(CModelEntity::StatusName[it->getStatus()])));

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, it->getValue());
        mpTblCompartments->setItem(i, 2, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, it->getRate());
        mpTblCompartments->setItem(i, 3, pItem);

        i++;
      }

  mpTblCompartments->setRowCount(i);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblCompartments->resizeColumnsToContents();
      mpTblCompartments->resizeRowsToContents();
    }

  mpTblCompartments->setSortingEnabled(true);
}

void StateSubwidget::loadReactions()
{
  // Fill the table
  CDataVectorN< CReaction >::const_iterator it = mpModel->getReactions().begin();
  CDataVectorN< CReaction >::const_iterator end = mpModel->getReactions().end();
  C_INT32 i = 0;

  mpTblReactions->setRowCount((int) mpModel->getReactions().size());

  QTableWidgetItem * pItem;

  mpTblReactions->setSortingEnabled(false);

  for (; it != end; ++it)
    {
      mpTblReactions->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(it->getObjectName())));

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, it->getFlux());
      mpTblReactions->setItem(i, 1, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);

      if (it->getScalingCompartment() != NULL)
        pItem->setData(Qt::DisplayRole, it->getFlux() / it->getScalingCompartment()->getValue());
      else
        pItem->setData(Qt::DisplayRole, std::numeric_limits< C_FLOAT64 >::quiet_NaN());

      mpTblReactions->setItem(i, 2, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, it->getParticleFlux());
      mpTblReactions->setItem(i, 3, pItem);

      mpTblReactions->setItem(i, 4, new QTableWidgetItem(FROM_UTF8(CChemEqInterface::getChemEqString(*it, false))));

      i++;
    }

  mpTblReactions->setRowCount(i);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblReactions->resizeColumnsToContents();
      mpTblReactions->resizeRowsToContents();
    }

  mpTblReactions->setSortingEnabled(true);
}

void StateSubwidget::loadModelValues()
{
  CDataVectorN< CModelValue >::const_iterator it = mpModel->getModelValues().begin();
  CDataVectorN< CModelValue >::const_iterator end = mpModel->getModelValues().end();
  C_INT32 i = 0;

  mpTblModelValues->setRowCount((int) mpModel->getModelValues().size());

  QTableWidgetItem * pItem;

  mpTblModelValues->setSortingEnabled(false);

  for (; it != end; ++it)
    if (it->getStatus() == CModelEntity::Status::ODE)
      {
        mpTblModelValues->setItem(i, 0, new QTableWidgetItem(FROM_UTF8(it->getObjectName())));
        mpTblModelValues->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(CModelEntity::StatusName[it->getStatus()])));

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, it->getValue());
        mpTblModelValues->setItem(i, 2, pItem);

        pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, it->getRate());
        mpTblModelValues->setItem(i, 3, pItem);

        i++;
      }

  mpTblModelValues->setRowCount(i);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblModelValues->resizeColumnsToContents();
      mpTblModelValues->resizeRowsToContents();
    }

  mpTblModelValues->setSortingEnabled(true);
}

void StateSubwidget::loadJacobian()
{
  const CDataArray * JacAnn = mpTask->getJacobianAnnotated();

  CColorScaleBiLog * tcs = new CColorScaleBiLog();
  mpJacobianAnnotationWidget->setColorCoding(tcs);
  mpJacobianAnnotationWidget->setColorScalingAutomatic(true);
  mpJacobianAnnotationWidget->setLegendEnabled(false);
  mpJacobianAnnotationWidget->setArrayAnnotation(JacAnn);

  QTableWidgetItem * pItem;

  //Eigenvalues...
  const CVector< C_FLOAT64 > & eigen_r = mpTask->getEigenValues().getR();
  const CVector< C_FLOAT64 > & eigen_i = mpTask->getEigenValues().getI();

  tableEigenValues->setSortingEnabled(false);

  size_t i, imax = eigen_i.size();
  tableEigenValues->setRowCount((int) imax);
  tableEigenValues->setColumnCount(5);

  for (i = 0; i < imax; ++i)
    {
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, eigen_r[i]);
      tableEigenValues->setItem((int) i, 0, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, eigen_i[i]);
      tableEigenValues->setItem((int) i, 1, pItem);

      //time scales in 3rd col
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, 1 / eigen_r[i]);

      if (eigen_r[i] > 0)
        pItem->setBackground(QBrush(QColor(255, 200, 200)));

      tableEigenValues->setItem((int) i, 2, pItem);

      //frequency/period of oscillations
      if (fabs(eigen_i[i]) > 1e-12)
        {
          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setData(Qt::DisplayRole, fabs(eigen_i[i] / (2.0 * M_PI)));
          tableEigenValues->setItem((int) i, 3, pItem);

          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setData(Qt::DisplayRole, fabs(1.0 / eigen_i[i] * (2.0 * M_PI)));
          tableEigenValues->setItem((int) i, 4, pItem);
        }
      else
        {
          tableEigenValues->setItem((int) i, 3, NULL);
          tableEigenValues->setItem((int) i, 4, NULL);
        }
    }

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      tableEigenValues->resizeColumnsToContents();
      tableEigenValues->resizeRowsToContents();
    }

  tableEigenValues->setSortingEnabled(true);

  //JacobianX

  const CDataArray * JacXAnn = mpTask->getJacobianXAnnotated();

  tcs = new CColorScaleBiLog();
  mpJacobianXAnnotationWidget->setColorCoding(tcs);
  mpJacobianXAnnotationWidget->setColorScalingAutomatic(true);
  mpJacobianXAnnotationWidget->setLegendEnabled(false);
  mpJacobianXAnnotationWidget->setArrayAnnotation(JacXAnn);

  //Eigenvalues...
  const CVector< C_FLOAT64 > & eigen_iX = mpTask->getEigenValuesReduced().getI();
  const CVector< C_FLOAT64 > & eigen_rX = mpTask->getEigenValuesReduced().getR();

  tableEigenValuesX->setSortingEnabled(false);

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

      //time scales in 3rd col
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, 1 / eigen_rX[i]);

      if (eigen_rX[i] > 0)
        pItem->setBackground(QBrush(QColor(255, 200, 200)));

      tableEigenValuesX->setItem((int) i, 2, pItem);

      //frequency/period of oscillations
      if (fabs(eigen_iX[i]) > 1e-12)
        {
          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setData(Qt::DisplayRole, fabs(eigen_iX[i] / (2 * M_PI)));
          tableEigenValuesX->setItem((int) i, 3, pItem);

          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setData(Qt::DisplayRole, fabs(1 / eigen_iX[i] * (2 * M_PI)));
          tableEigenValuesX->setItem((int) i, 4, pItem);
        }
      else
        {
          tableEigenValuesX->setItem((int) i, 3, NULL);
          tableEigenValuesX->setItem((int) i, 4, NULL);
        }
    }

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      tableEigenValuesX->resizeColumnsToContents();
      tableEigenValuesX->resizeRowsToContents();
    }

  tableEigenValuesX->setSortingEnabled(true);

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

  QString TimeUnits = "\n[" + FROM_UTF8(CUnit::prettyPrint(mpModel->getTimeUnit())) + "]";
  QString FrequencyUnits = "\n[" + FROM_UTF8(CUnit::prettyPrint("1/(" + mpModel->getTimeUnit() + ")")) + "]";
  QString ConcentrationUnits = "\n[" + FROM_UTF8(CUnit::prettyPrint(mpModel->getQuantityUnit() + "/(" + mpModel->getVolumeUnit() + ")")) + "]";
  QString ConcentrationRateUnits = "\n[" + FROM_UTF8(CUnit::prettyPrint(mpModel->getQuantityUnit() + "/(" + mpModel->getVolumeUnit() + "*" + mpModel->getTimeUnit() + ")")) + "]";
  QString VolumeUnits = "\n[" + FROM_UTF8(CUnit::prettyPrint(mpModel->getVolumeUnit())) + "]";
  QString VolumeRateUnits = "\n[" + FROM_UTF8(CUnit::prettyPrint(mpModel->getVolumeUnit() + "/(" + mpModel->getTimeUnit() + ")")) + "]";
  QString QuantityRateUnits = "\n[" + FROM_UTF8(CUnit::prettyPrint(mpModel->getQuantityUnit() + "/(" + mpModel->getTimeUnit() + ")")) + "]";

  mpTblCompartments->horizontalHeaderItem(2)->setText("Volume" + VolumeUnits);
  mpTblCompartments->horizontalHeaderItem(3)->setText("Rate" + VolumeRateUnits);

  mpTblMetabolites->horizontalHeaderItem(2)->setText("Concentration" + ConcentrationUnits);
  mpTblMetabolites->horizontalHeaderItem(3)->setText("Number");
  mpTblMetabolites->horizontalHeaderItem(4)->setText("Rate" + ConcentrationRateUnits);
  mpTblMetabolites->horizontalHeaderItem(5)->setText("Number Rate" + FrequencyUnits);
  mpTblMetabolites->horizontalHeaderItem(6)->setText("Transition Time" + TimeUnits);

  mpTblReactions->horizontalHeaderItem(1)->setText("Flux (extensive)" + QuantityRateUnits);
  mpTblReactions->horizontalHeaderItem(2)->setText("Flux (intensive)" + ConcentrationRateUnits);
  mpTblReactions->horizontalHeaderItem(3)->setText("Number Flux" + FrequencyUnits);
}

bool StateSubwidget::loadAll(const CSteadyStateTask * pTask)
{
  mpTask = pTask;
  assert(mpDataModel != NULL);
  mpModel = mpDataModel->getModel();

  if (mpTask == NULL || mpModel == NULL)
    {
      clear();
      return false;
    }

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
        mpTblReactions->showColumn(2);
        mpTblReactions->hideColumn(3);
        break;

      case 1:
        mpTblMetabolites->hideColumn(2);
        mpTblMetabolites->showColumn(3);
        mpTblMetabolites->hideColumn(4);
        mpTblMetabolites->showColumn(5);
        mpTblReactions->hideColumn(1);
        mpTblReactions->hideColumn(2);
        mpTblReactions->showColumn(3);
        break;
    }

  showUnits();
}

bool StateSubwidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:

        // For a new model we need to remove references to no longer existing metabolites
        switch (action)
          {
            case ListViews::ADD:
            case ListViews::DELETE:
              assert(mpDataModel != NULL);
              mpModel = mpDataModel->getModel();
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
