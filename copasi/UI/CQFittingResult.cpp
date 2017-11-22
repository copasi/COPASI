// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

/*
 *  Constructs a CQFittingResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQFittingResult::CQFittingResult(QWidget* parent, const char* name):
  CopasiWidget(parent, name)
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
  mpFisherInformationEigenvectors->setLegendEnabled(false);
  mpFisherInformationScaledMatrix->setLegendEnabled(false);
  mpFisherInformationScaledEigenvalues->setLegendEnabled(false);
  mpFisherInformationScaledEigenvectors->setLegendEnabled(false);
}

bool CQFittingResult::update(ListViews::ObjectType /* objectType */,
                             ListViews::Action /* action */,
                             const std::string & /* key */)
{
  // :TODO:
  return true;
}

bool CQFittingResult::leave()
{
  // :TODO:
  return true;
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

  size_t i, imax;
  QTableWidgetItem * pItem;

  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  const CVector< C_FLOAT64 > & Solutions = mpProblem->getSolutionVariables();
  const CVector< C_FLOAT64 > & StdDeviations = mpProblem->getVariableStdDeviations();
  const CVector< C_FLOAT64 > & Gradients = mpProblem->getVariableGradients();

  imax = Items.size();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  //the parameters table
  mpParameters->setRowCount((int) imax);

  QColor BackgroundColor = mpParameters->palette().brush(QPalette::Active, QPalette::Base).color();

  int h, s, v;
  BackgroundColor.getHsv(&h, &s, &v);

  if (s < 20)
    {
      s = 20;
    }

  BackgroundColor.setHsv(0, s, v);

  mpParameters->setSortingEnabled(false);

  for (i = 0; i != imax; i++)
    {
      //1st column: parameter name
      const CDataObject *pObject =
        CObjectInterface::DataObject(mpDataModel->getObjectFromCN(Items[i]->getObjectCN()));

      if (pObject)
        {
          std::string Experiments =
            static_cast<CFitItem *>(Items[i])->getExperiments();

          if (Experiments != "")
            Experiments = "; {" + Experiments + "}";

          pItem = new QTableWidgetItem(FROM_UTF8(pObject->getObjectDisplayName() + Experiments));
        }
      else
        pItem = new QTableWidgetItem("Not Found");

      mpParameters->setItem((int) i, 0, pItem);

      const C_FLOAT64 & Solution = i < Solutions.size() ? Solutions[i] : std::numeric_limits<double>::quiet_NaN();

      //2nd column: lower bound
      const COptItem *current = Items[i];
      pItem = new QTableWidgetItem(FROM_UTF8(current->getLowerBound()));
      mpParameters->setItem((int) i, 1, pItem);

      if (current->getLowerBoundValue() != NULL && 1.01 * *current->getLowerBoundValue() > Solution)
        {
          pItem->setBackgroundColor(BackgroundColor);
        }

      //3rd column: start value
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, current->getLastStartValue());
      pItem->setForeground(QColor(120, 120, 140));
      mpParameters->setItem((int) i, 2, pItem);

      //4th column: solution value
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Solution);
      mpParameters->setItem((int) i, 3, pItem);

      //5th column: upper bound
      pItem = new QTableWidgetItem(FROM_UTF8(current->getUpperBound()));
      mpParameters->setItem((int) i, 4, pItem);

      if (current->getUpperBoundValue() != NULL && 0.99 * *current->getUpperBoundValue() < Solution)
        {
          pItem->setBackgroundColor(BackgroundColor);
        }

      const C_FLOAT64 & StdDeviation = i < StdDeviations.size() ?  StdDeviations[i] : std::numeric_limits<double>::quiet_NaN();

      pItem = new QTableWidgetItem(QVariant::Double);

      pItem->setData(Qt::DisplayRole, StdDeviation);

      mpParameters->setItem((int) i, 5, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);

      pItem->setData(Qt::DisplayRole, fabs(100.0 * StdDeviation / Solution));

      mpParameters->setItem((int) i, 6, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);

      pItem->setData(Qt::DisplayRole, i < Gradients.size() ? Gradients[i] : std::numeric_limits<double>::quiet_NaN());

      mpParameters->setItem((int) i, 7, pItem);
    }

  mpParameters->resizeColumnsToContents();
  mpParameters->resizeRowsToContents();
  mpParameters->setSortingEnabled(true);

  // Results per Experiment tab: Loop over the experiments
  const CExperimentSet & Experiments = mpProblem->getExperimentSet();

  imax = Experiments.getExperimentCount();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  
  size_t rowcount = 0;
  mpExperiments->setRowCount(0);
  
  //mpExperiments->setRowCount((int) imax);
  mpExperiments->setSortingEnabled(false);

  for (i = 0; i != imax; i++)
    {
      //an empty line between experiments
      if (i)
      {
        mpExperiments->setRowCount(rowcount+1);
        pItem = new QTableWidgetItem();
        mpExperiments->setItem(rowcount,0,pItem);
        ++rowcount;
      }
        
      //first the experiment summary
      const CExperiment & Experiment = * Experiments.getExperiment(i);

      mpExperiments->setRowCount(rowcount+1);

      pItem = new QTableWidgetItem(FROM_UTF8(Experiment.getObjectName()));
      mpExperiments->setItem((int) rowcount, 0, pItem);
      
      QString tmpStr = QString::number(Experiment.getValidValueCount());
      if (Experiment.getValidValueCount() != Experiment.getTotalValueCount())
      {
        tmpStr += " (of ";
        tmpStr += QString::number(Experiment.getTotalValueCount());
        tmpStr += ")";
      }
      
      pItem = new QTableWidgetItem(tmpStr);
      //pItem->setData(Qt::DisplayRole, (unsigned int)Experiment.getValidValueCount()  );
      mpExperiments->setItem((int) rowcount, 1, pItem);
      
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiment.getObjectiveValue());
      mpExperiments->setItem((int) rowcount, 2, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayPropertyRole, Experiment.getRMS());
      mpExperiments->setItem((int) rowcount, 3, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiment.getErrorMean());
      mpExperiments->setItem((int) rowcount, 4, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiment.getErrorMeanSD());
      mpExperiments->setItem((int) rowcount, 5, pItem);
      
      ++rowcount;
      
      //now the data sets in the experiment
      
      const CObjectInterface * const * ppObject = Experiments.getDependentObjects().array();
      const CObjectInterface * const * ppEnd = ppObject + Experiments.getDependentObjects().size();
      
      for (; ppObject != ppEnd; ++ppObject)
      {
        size_t Count = Experiment.getColumnValidValueCount(*ppObject);
        
        if (Count)
        {
          mpExperiments->setRowCount(rowcount+1);
          
          pItem = new QTableWidgetItem(FROM_UTF8((*ppObject)->getObjectDisplayName()));
          mpExperiments->setItem((int) rowcount, 0, pItem);
          
          pItem = new QTableWidgetItem(QVariant::UInt);
          pItem->setData(Qt::DisplayRole, (unsigned int)Count);
          mpExperiments->setItem((int) rowcount, 1, pItem);
          
          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setData(Qt::DisplayRole, Experiment.getObjectiveValue(*ppObject));
          mpExperiments->setItem((int) rowcount, 2, pItem);
          
          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setData(Qt::DisplayPropertyRole, Experiment.getRMS(*ppObject));
          mpExperiments->setItem((int) rowcount, 3, pItem);
          
          pItem = new QTableWidgetItem(QVariant::Double);
          pItem->setData(Qt::DisplayRole, Experiment.getErrorSum(*ppObject)/Count);
          mpExperiments->setItem((int) rowcount, 4, pItem);
          
          //pItem = new QTableWidgetItem(QVariant::Double);
          //pItem->setData(Qt::DisplayRole, Experiment.getErrorMeanSD(*ppObject));
          //mpExperiments->setItem((int) rowcount, 5, pItem);
          
          ++rowcount;
          
          
        }
      }
  
        

    }

  mpExperiments->resizeColumnsToContents();
  mpExperiments->resizeRowsToContents();
  //mpExperiments->setSortingEnabled(true);

  // Loop over the dependent objects
  imax = Experiments.getDependentObjects().size();

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
  mpFisherInformationEigenvalues->mpComboRows->setCurrentIndex(1);

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
  mpFisherInformationScaledEigenvalues->mpComboRows->setCurrentIndex(1);

  tcs = new CColorScaleBiLog();
  mpFisherInformationScaledEigenvectors->setColorCoding(tcs);
  mpFisherInformationScaledEigenvectors->setColorScalingAutomatic(true);
  mpFisherInformationScaledEigenvectors->setArrayAnnotation(&mpProblem->getScaledFisherInformationEigenvectors());
  mpFisherInformationScaledEigenvectors->mpComboRows->setCurrentIndex(1);

  bool Enable = (mpProblem->getCrossValidationSet().getExperimentCount() > 0);

  mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCrossValidations), Enable);
  mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpCrossValidationValues), Enable);

  // Loop over the cross validation
  const CCrossValidationSet & CrossValidations = mpProblem->getCrossValidationSet();

  imax = CrossValidations.getExperimentCount();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpCrossValidations->setRowCount(imax);
  mpCrossValidations->setSortingEnabled(false);

  for (i = 0; i != imax; i++)
    {
      const CExperiment & Experiment = * CrossValidations.getExperiment(i);

      pItem = new QTableWidgetItem(FROM_UTF8(Experiment.getObjectName()));
      mpCrossValidations->setItem(i, 0, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiment.getObjectiveValue());
      mpCrossValidations->setItem(i, 1, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiment.getRMS());
      mpCrossValidations->setItem(i, 2, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiment.getErrorMean());
      mpCrossValidations->setItem(i, 3, pItem);

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Experiment.getErrorMeanSD());
      mpCrossValidations->setItem(i, 4, pItem);
    }

  mpCrossValidations->resizeColumnsToContents();
  mpCrossValidations->resizeRowsToContents();
  mpCrossValidations->setSortingEnabled(false);

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
