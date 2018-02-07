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

/*
 *  CQFittingResult.cpp
 *  Created by Paul on 4/2/10.
 */

#include "CQFittingResult.h"

#include "copasi.h"

#include "CopasiFileDialog.h"
#include "CQMessageBox.h"

#include "CopasiDataModel/CDataModel.h"
#include "parameterFitting/CFitTask.h"
#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CFitItem.h"
#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"

#include "copasi/core/CRootContainer.h"

#include "optimization/COptMethod.h"
#include "optimization/COptLog.h"

#include "commandline/CLocaleString.h"
#include "model/CModel.h"
#include "math/CMathContainer.h"

#include "UI/qtUtilities.h"

#include <QSortFilterProxyModel>
#include <copasi/UI/CQParameterResultItemModel.h>

/*
 *  Constructs a CQFittingResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQFittingResult::CQFittingResult(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingResult::~CQFittingResult()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQFittingResult::init()
{
  mpCorrelations->setLegendEnabled(false);
  mpFisherInformationMatrix->setLegendEnabled(false);
  mpFisherInformationEigenvalues->setLegendEnabled(false);
  mpFisherInformationEigenvalues->setControlsEnabled(false);
  mpFisherInformationEigenvalues->setMaximumHeight(80);
  mpFisherInformationEigenvectors->setLegendEnabled(false);
  mpFisherInformationScaledMatrix->setLegendEnabled(false);
  mpFisherInformationScaledEigenvalues->setLegendEnabled(false);
  mpFisherInformationScaledEigenvalues->setControlsEnabled(false);
  mpFisherInformationScaledEigenvalues->setMaximumHeight(80);
  mpFisherInformationScaledEigenvectors->setLegendEnabled(false);
}

bool CQFittingResult::update(ListViews::ObjectType objectType,
                             ListViews::Action action,
                             const std::string & /* key */)
{
  if (objectType == ListViews::MODEL && action == ListViews::DELETE)
    {
      // need to clear annotated matrices, as otherwise they will hold pointers to non-existing things.
      mpCorrelations->setArrayAnnotation(NULL);
      mpFisherInformationMatrix->setArrayAnnotation(NULL);
      mpFisherInformationEigenvalues->setArrayAnnotation(NULL);
      mpFisherInformationEigenvectors->setArrayAnnotation(NULL);
      mpFisherInformationScaledMatrix->setArrayAnnotation(NULL);
      mpFisherInformationScaledEigenvalues->setArrayAnnotation(NULL);
      mpFisherInformationScaledEigenvectors->setArrayAnnotation(NULL);
      mpParameters->setModel(NULL);
    }

  // :TODO:
  return true;
}

bool CQFittingResult::leave()
{
  // :TODO:
  return true;
}

void CQFittingResult::loadCrossValidationTab()
{
  if (!mpProblem)
    return;

  loadExperimentSetIntoTree(
    mpProblem->getCrossValidationSet(),
    mpCrossValidations);
}

void CQFittingResult::loadExperimentTab()
{
  if (!mpProblem)
    return;

  loadExperimentSetIntoTree(
    mpProblem->getExperimentSet(),
    mpExperiments);
}

void CQFittingResult::loadExperimentSetIntoTree(const CExperimentSet& Experiments, QTreeWidget* pTreeWidget)
{
  QTreeWidgetItem* pItem = NULL;
  size_t i = 0;

  size_t imax = Experiments.getExperimentCount();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  pTreeWidget->clear();

  QTreeWidgetItem* pRoot = pTreeWidget->invisibleRootItem();

  for (i = 0; i != imax; i++)
    {

      //first the experiment summary
      const CExperiment & Experiment = * Experiments.getExperiment(i);

      QString validValueCount = QString::number(Experiment.getValidValueCount());

      if (Experiment.getValidValueCount() != Experiment.getTotalValueCount())
        {
          validValueCount += " (of ";
          validValueCount += QString::number(Experiment.getTotalValueCount());
          validValueCount += ")";
        }

      QTreeWidgetItem* pExperimentItem = new QTreeWidgetItem(pRoot, QStringList()
          << FROM_UTF8(Experiment.getObjectName())
          << validValueCount
          << convertToQString(Experiment.getObjectiveValue())
          << convertToQString(Experiment.getRMS())
          << convertToQString(Experiment.getErrorMean())
          << convertToQString(Experiment.getErrorMeanSD())
                                                            );

      //now the data sets in the experiment

      const CObjectInterface * const * ppObject = Experiments.getDependentObjects().array();
      const CObjectInterface * const * ppEnd = ppObject + Experiments.getDependentObjects().size();

      for (; ppObject != ppEnd; ++ppObject)
        {
          size_t Count = Experiment.getColumnValidValueCount(*ppObject);

          if (Count)
            {
              pItem = new QTreeWidgetItem(pExperimentItem, QStringList()
                                          << FROM_UTF8((*ppObject)->getObjectDisplayName())
                                          << QString::number((unsigned int)Count)
                                          << convertToQString(Experiment.getObjectiveValue(*ppObject))
                                          << convertToQString(Experiment.getRMS(*ppObject))
                                          << convertToQString(Experiment.getErrorSum(*ppObject) / Count)
                                          << ""//convertToQString(Experiment.getErrorMeanSD(*ppObject))
                                         );
            }
        }
    }
}

bool CQFittingResult::enterProtected()
{
  assert(mpDataModel != NULL);
  mpTask =
    dynamic_cast<CFitTask *>(&mpDataModel->getTaskList()->operator[]("Parameter Estimation"));

  if (!mpTask) return false;

  mpProblem = dynamic_cast<const CFitProblem *>(mpTask->getProblem());

  if (!mpProblem) return false;

  mpMain->load(mpProblem);

  if (mpProblem->getCalculateStatistics())
    {
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpExperiments), true);
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpValues), true);
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCorrelations), true);
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpFisherInformationPage), true);

      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCrossValidations), true);
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCrossValidationValues), true);
    }
  else
    {
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpExperiments), false);
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpValues), false);
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCorrelations), false);
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpFisherInformationPage), false);

      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCrossValidations), false);
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCrossValidationValues), false);
    }

  // determine background color for values too close to the bounds
  QColor BackgroundColor = mpParameters->palette().brush(QPalette::Active, QPalette::Base).color();

  int h, s, v;
  BackgroundColor.getHsv(&h, &s, &v);

  if (s < 20)
    {
      s = 20;
    }

  BackgroundColor.setHsv(0, s, v);

  //the parameters table

  mpParameters->setModel(NULL);

  CQParameterResultItemModel *model = new CQParameterResultItemModel(mpProblem, BackgroundColor, this);
  QSortFilterProxyModel*  sortModel = new QSortFilterProxyModel(this);
  sortModel->setSourceModel(model);
  mpParameters->setModel(sortModel);
  mpParameters->resizeColumnsToContents();
  mpParameters->resizeRowsToContents();

  // Results per Experiment tab: Loop over the experiments
  loadExperimentTab();

  size_t i;
  QTableWidgetItem * pItem;

  // Loop over the dependent objects
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  const CVector< C_FLOAT64 > & Solutions = mpProblem->getSolutionVariables();
  const CVector< C_FLOAT64 > & StdDeviations = mpProblem->getVariableStdDeviations();
  const CVector< C_FLOAT64 > & Gradients = mpProblem->getVariableGradients();

  const CExperimentSet & Experiments = mpProblem->getExperimentSet();
  size_t imax = Experiments.getDependentObjects().size();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpValues->setRowCount((int) imax);
  mpValues->setSortingEnabled(false);

  for (i = 0; i != imax; i++)
    {
      const CObjectInterface * pObject = Experiments.getDependentObjects()[i];

      if (pObject)
        pItem = new QTableWidgetItem(FROM_UTF8(pObject->getObjectDisplayName()));
      else
        pItem = new QTableWidgetItem("Not Found");

      mpValues->setItem((int) i, 0, pItem);

      pItem = new QTableWidgetItem(QVariant::UInt);
      pItem->setData(Qt::DisplayRole, (unsigned int)Experiments.getDependentDataCount()[i]);
      mpValues->setItem((int) i, 1, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiments.getDependentObjectiveValues()[i]);
      mpValues->setItem((int) i, 2, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiments.getDependentRMS()[i]);
      mpValues->setItem((int) i, 3, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiments.getDependentErrorMean()[i]);
      mpValues->setItem((int) i, 4, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiments.getDependentErrorMeanSD()[i]);
      mpValues->setItem((int) i, 5, pItem);
    }

  mpValues->resizeColumnsToContents();
  mpValues->resizeRowsToContents();
  mpValues->setSortingEnabled(true);

  // Fill correlation matrix
  imax = Items.size();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  CColorScaleBiLog * tcs = new CColorScaleBiLog();
  mpCorrelations->setColorCoding(tcs);
  mpCorrelations->setColorScalingAutomatic(true);
  mpCorrelations->setArrayAnnotation(&mpProblem->getCorrelations());

  tcs = new CColorScaleBiLog();
  mpFisherInformationMatrix->setColorCoding(tcs);
  mpFisherInformationMatrix->setColorScalingAutomatic(true);
  mpFisherInformationMatrix->setArrayAnnotation(&mpProblem->getFisherInformation());

  tcs = new CColorScaleBiLog();
  mpFisherInformationEigenvalues->setColorCoding(tcs);
  mpFisherInformationEigenvalues->setColorScalingAutomatic(true);
  mpFisherInformationEigenvalues->setArrayAnnotation(&mpProblem->getFisherInformationEigenvalues());
  mpFisherInformationEigenvalues->slotRowSelectionChanged(1);

  tcs = new CColorScaleBiLog();
  mpFisherInformationEigenvectors->setColorCoding(tcs);
  mpFisherInformationEigenvectors->setColorScalingAutomatic(true);
  mpFisherInformationEigenvectors->setArrayAnnotation(&mpProblem->getFisherInformationEigenvectors());
  mpFisherInformationEigenvectors->mpComboRows->setCurrentIndex(1);

  tcs = new CColorScaleBiLog();
  mpFisherInformationScaledMatrix->setColorCoding(tcs);
  mpFisherInformationScaledMatrix->setColorScalingAutomatic(true);
  mpFisherInformationScaledMatrix->setArrayAnnotation(&mpProblem->getScaledFisherInformation());

  tcs = new CColorScaleBiLog();
  mpFisherInformationScaledEigenvalues->setColorCoding(tcs);
  mpFisherInformationScaledEigenvalues->setColorScalingAutomatic(true);
  mpFisherInformationScaledEigenvalues->setArrayAnnotation(&mpProblem->getScaledFisherInformationEigenvalues());
  mpFisherInformationScaledEigenvalues->slotRowSelectionChanged(1);

  tcs = new CColorScaleBiLog();
  mpFisherInformationScaledEigenvectors->setColorCoding(tcs);
  mpFisherInformationScaledEigenvectors->setColorScalingAutomatic(true);
  mpFisherInformationScaledEigenvectors->setArrayAnnotation(&mpProblem->getScaledFisherInformationEigenvectors());
  mpFisherInformationScaledEigenvectors->mpComboRows->setCurrentIndex(1);

  bool Enable = (mpProblem->getCrossValidationSet().getExperimentCount() > 0);

  mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCrossValidations), Enable);
  mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCrossValidationValues), Enable);

  // Loop over the cross validation

  loadCrossValidationTab();
  const CCrossValidationSet & CrossValidations = mpProblem->getCrossValidationSet();

//  imax = CrossValidations.getExperimentCount();

//  if (mpProblem->getFunctionEvaluations() == 0)
//    imax = 0;

//  mpCrossValidations->setRowCount(imax);
//  mpCrossValidations->setSortingEnabled(false);

//  for (i = 0; i != imax; i++)
//    {
//      const CExperiment & Experiment = * CrossValidations.getExperiment(i);

//      pItem = new QTableWidgetItem(FROM_UTF8(Experiment.getObjectName()));
//      mpCrossValidations->setItem(i, 0, pItem);

//      pItem = new QTableWidgetItem(QVariant::Double);
//      pItem->setData(Qt::DisplayRole, Experiment.getObjectiveValue());
//      mpCrossValidations->setItem(i, 1, pItem);

//      pItem = new QTableWidgetItem(QVariant::Double);
//      pItem->setData(Qt::DisplayRole, Experiment.getRMS());
//      mpCrossValidations->setItem(i, 2, pItem);

//      pItem = new QTableWidgetItem(QVariant::Double);
//      pItem->setData(Qt::DisplayRole, Experiment.getErrorMean());
//      mpCrossValidations->setItem(i, 3, pItem);

//      pItem = new QTableWidgetItem(QVariant::Double);
//      pItem->setData(Qt::DisplayRole, Experiment.getErrorMeanSD());
//      mpCrossValidations->setItem(i, 4, pItem);
//}

//  mpCrossValidations->resizeColumnsToContents();
//  mpCrossValidations->resizeRowsToContents();
//  mpCrossValidations->setSortingEnabled(false);

  // Loop over the dependent objects
  imax = CrossValidations.getDependentObjects().size();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpCrossValidationValues->setRowCount(imax);
  mpCrossValidationValues->setSortingEnabled(false);

  for (i = 0; i != imax; i++)
    {
      const CObjectInterface * pObject = CrossValidations.getDependentObjects()[i];

      if (pObject)
        pItem = new QTableWidgetItem(FROM_UTF8(pObject->getObjectDisplayName()));
      else
        pItem = new QTableWidgetItem("Not Found");

      mpCrossValidationValues->setItem(i, 0, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, CrossValidations.getDependentObjectiveValues()[i]);
      mpCrossValidationValues->setItem(i, 1, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, CrossValidations.getDependentRMS()[i]);
      mpCrossValidationValues->setItem(i, 2, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, CrossValidations.getDependentErrorMean()[i]);
      mpCrossValidationValues->setItem(i, 3, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, CrossValidations.getDependentErrorMeanSD()[i]);
      mpCrossValidationValues->setItem(i, 4, pItem);
    }

  mpCrossValidationValues->resizeColumnsToContents();
  mpCrossValidationValues->resizeRowsToContents();
  mpCrossValidationValues->setSortingEnabled(true);

  mpLogTree->clear();

  //preliminary testing code
  /*tcs = new CColorScaleBiLog();
  CQArrayAnnotationsWidget * pJacobianMatrix = new CQArrayAnnotationsWidget(NULL, false);
  pJacobianMatrix->setColorCoding(tcs);
  pJacobianMatrix->setColorScalingAutomatic(true);
  pJacobianMatrix->setArrayAnnotation(&mpProblem->getParameterEstimationJacobian());
  pJacobianMatrix->show();

  tcs = new CColorScaleBiLog();
  CQArrayAnnotationsWidget * pScaledJacobianMatrix = new CQArrayAnnotationsWidget(NULL, false);
  pScaledJacobianMatrix->setColorCoding(tcs);
  pScaledJacobianMatrix->setColorScalingAutomatic(true);
  pScaledJacobianMatrix->setArrayAnnotation(&mpProblem->getScaledParameterEstimationJacobian());
  pScaledJacobianMatrix->show();*/

  return true;
}

void CQFittingResult::loadTab(int index)
{
  if (index != mpTabWidget->indexOf(mpLogPage))
    return;

  const COptMethod* pMethod = dynamic_cast<const COptMethod*>(mpTask->getMethod());

  if (pMethod == NULL)
    return;

  if (mpLogTree->topLevelItemCount() != 0)
    return;

  loadLog(pMethod);
}

void CQFittingResult::loadLog(const COptMethod * pMethod)
{
  mpLogTree->clear();

  if (pMethod == NULL)
    {
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpLogPage), false);
      return;
    }

  mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpLogPage), true);

  const COptLog &log = pMethod->getMethodLog();

  auto it = log.begin();

  for (; it != log.end(); ++it)
    {
      QTreeWidgetItem* item = new QTreeWidgetItem(mpLogTree->invisibleRootItem(), QStringList() << FROM_UTF8(it->getHeader()));

      if (!it->getSubtext().empty())
        {
          QTreeWidgetItem* subTextItem = new QTreeWidgetItem(item, QStringList() << FROM_UTF8(it->getSubtext()));
        }

      if (!it->getStatusDetails().empty())
        {
          QTreeWidgetItem* statusDetailItem = new QTreeWidgetItem(item, QStringList() << FROM_UTF8(it->getStatusDetails()));
        }
    }
}

void CQFittingResult::slotSave(void)
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this,
                                          "Save File Dialog",
                                          "untitled.txt",
                                          "TEXT Files (*.txt)",
                                          "Save to");

      if (fileName.isEmpty()) return;

      if (!fileName.endsWith(".txt") &&
          !fileName.endsWith(".")) fileName += ".txt";

      fileName = fileName.remove(QRegExp("\\.$"));

      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail()) return;

  mpProblem->printResult(&file);

  file.close();
}

void CQFittingResult::slotUpdateModel()
{
  const_cast< CFitProblem * >(mpProblem)->restore(true);

  // We need to notify the GUI to update all values
  protectedNotify(ListViews::STATE, ListViews::CHANGE, mpTask->getMathContainer()->getModel().getKey());
}
