// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingWidget.ui.h,v $
//   $Revision: 1.36.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/05/01 13:10:58 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlabel.h>
#include <qtoolbutton.h>

#include "UI/CQTaskBtnWidget.h"
#include "UI/CQTaskHeaderWidget.h"
#include "UI/CQFittingItemWidget.h"
#include "UI/CProgressBar.h"
#include "UI/CQExperimentData.h"

#include "report/CKeyFactory.h"
#include "parameterFitting/CFitTask.h"
#include "parameterFitting/CFitItem.h"
#include "parameterFitting/CFitMethod.h"
#include "parameterFitting/CFitProblem.h"
#include "parameterFitting/CExperimentSet.h"
#include "parameterFitting/CExperiment.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiException.h"

bool CQFittingWidget::saveTask()
{
  CFitTask * pTask =
    dynamic_cast< CFitTask * >(mpTask);
  if (!pTask) return false;

  saveCommon();
  saveMethod();

  CFitProblem * pProblem =
    dynamic_cast<CFitProblem *>(mpTask->getProblem());
  if (!pProblem) return false;

  std::map<std::string, std::string> ExperimentMap;
  std::map<std::string, std::string> CrossValidationMap;

  // Save experiment set
  CExperimentSet * pExperimentSet =
    dynamic_cast<CExperimentSet *>(pProblem->getGroup("Experiment Set"));

  std::string Name;
  CExperiment * pExperiment;
  unsigned C_INT32 i, imax;

  std::set<CExperiment *> DealtWith;

  for (i = pExperimentSet->getExperimentCount() - 1; i != C_INVALID_INDEX; i--)
    {
      pExperiment =
        dynamic_cast<CExperiment *>(GlobalKeys.get(mExperimentKeyMap[pExperimentSet->getExperiment(i)->CCopasiParameter::getKey()]));

      if (pExperiment && pExperiment == mpExperimentSet->getExperiment(pExperiment->getObjectName()))
        {
          if (!(*pExperimentSet->getExperiment(i) == *pExperiment))
            {
              *pExperimentSet->getExperiment(i) = *pExperiment;
              mChanged = true;
            }

          DealtWith.insert(pExperiment);
        }
      else
        {
          mExperimentKeyMap.erase(pExperimentSet->getExperiment(i)->CCopasiParameter::getKey());
          pExperimentSet->removeExperiment(i);
          mChanged = true;
        }
    }

  for (i = 0, imax = mpExperimentSet->getExperimentCount(); i < imax; i++)
    {
      pExperiment = mpExperimentSet->getExperiment(i);
      if (DealtWith.count(pExperiment)) continue;

      pExperiment = pExperimentSet->addExperiment(*pExperiment);
      mExperimentKeyMap[pExperiment->CCopasiParameter::getKey()] =
        mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey();
      mChanged = true;
    }

  // We need to invert the key map for saving!
  std::map<std::string, std::string>::iterator it = mExperimentKeyMap.begin();
  std::map<std::string, std::string>::iterator end = mExperimentKeyMap.end();

  for (; it != end; ++it)
    ExperimentMap[it->second] = it->first;

#ifdef COPASI_CROSSVALIDATION
  // Save cross validation experiment set
  CCrossValidationSet * pCrossValidationSet =
    dynamic_cast<CCrossValidationSet *>(pProblem->getGroup("Cross Validation Set"));

  if (pCrossValidationSet->getWeight() != mpCrossValidationSet->getWeight())
    {
      pCrossValidationSet->setWeight(mpCrossValidationSet->getWeight());
      mChanged = true;
    }

  if (pCrossValidationSet->getThreshold() != mpCrossValidationSet->getThreshold())
    {
      pCrossValidationSet->setThreshold(mpCrossValidationSet->getThreshold());
      mChanged = true;
    }

  DealtWith.clear();

  for (i = pCrossValidationSet->getExperimentCount() - 1; i != C_INVALID_INDEX; i--)
    {
      pExperiment =
        dynamic_cast<CExperiment *>(GlobalKeys.get(mCrossValidationKeyMap[pCrossValidationSet->getExperiment(i)->CCopasiParameter::getKey()]));

      if (pExperiment && pExperiment == mpCrossValidationSet->getExperiment(pExperiment->getObjectName()))
        {
          if (!(*pCrossValidationSet->getExperiment(i) == *pExperiment))
            {
              *pCrossValidationSet->getExperiment(i) = *pExperiment;
              mChanged = true;
            }

          DealtWith.insert(pExperiment);
        }
      else
        {
          mCrossValidationKeyMap.erase(pCrossValidationSet->getExperiment(i)->CCopasiParameter::getKey());
          pCrossValidationSet->removeExperiment(i);
          mChanged = true;
        }
    }

  for (i = 0, imax = mpCrossValidationSet->getExperimentCount(); i < imax; i++)
    {
      pExperiment = mpCrossValidationSet->getExperiment(i);
      if (DealtWith.count(pExperiment)) continue;

      pExperiment = pCrossValidationSet->addExperiment(*pExperiment);
      mCrossValidationKeyMap[pExperiment->CCopasiParameter::getKey()] =
        mpCrossValidationSet->getExperiment(i)->CCopasiParameter::getKey();
      mChanged = true;
    }

  // We need to invert the key map for saving!
  it = mCrossValidationKeyMap.begin();
  end = mCrossValidationKeyMap.end();
  for (; it != end; ++it)
    CrossValidationMap[it->second] = it->first;
#endif // COPASI_CROSSVALIDATION

  mChanged |= mpParameters->save(&ExperimentMap, &CrossValidationMap);
  mChanged |= mpConstraints->save(&ExperimentMap, &CrossValidationMap);

  if (mChanged) CCopasiDataModel::Global->changed();

  mChanged = false;
  return true;
}

bool CQFittingWidget::loadTask()
{
  CFitTask * pTask =
    dynamic_cast< CFitTask * >(mpTask);
  if (!pTask) return false;

  loadCommon();
  loadMethod();

  CFitProblem * pProblem =
    dynamic_cast<CFitProblem *>(mpTask->getProblem());
  if (!pProblem) return false;

  pdelete(mpExperimentSet)
  CExperimentSet * pExperimentSet =
    dynamic_cast<CExperimentSet *>(pProblem->getGroup("Experiment Set"));
  mpExperimentSet = new CExperimentSet(*pExperimentSet);

  mExperimentKeyMap.clear();
  unsigned C_INT32 i, imax = mpExperimentSet->getExperimentCount();

  for (i = 0; i < imax; i++)
    mExperimentKeyMap[pExperimentSet->getExperiment(i)->CCopasiParameter::getKey()] =
      mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey();

#ifdef COPASI_CROSSVALIDATION
  pdelete(mpCrossValidationSet)
  CCrossValidationSet * pCrossValidationSet =
    dynamic_cast<CCrossValidationSet *>(pProblem->getGroup("Cross Validation Set"));
  mpCrossValidationSet = new CCrossValidationSet(*pCrossValidationSet);

  mCrossValidationKeyMap.clear();
  imax = mpCrossValidationSet->getExperimentCount();

  for (i = 0; i < imax; i++)
    mCrossValidationKeyMap[pCrossValidationSet->getExperiment(i)->CCopasiParameter::getKey()] =
      mpCrossValidationSet->getExperiment(i)->CCopasiParameter::getKey();
#endif // COPASI_CROSSVALIDATION

  mpParameters->load(pProblem->getGroup("OptimizationItemList"), &mExperimentKeyMap, &mCrossValidationKeyMap);
  mpParameters->setExperimentSet(const_cast<const CExperimentSet *&>(mpExperimentSet));
  mpParameters->setCrossValidationSet(const_cast<const CCrossValidationSet *&>(mpCrossValidationSet));

  mpConstraints->load(pProblem->getGroup("OptimizationConstraintList"), &mExperimentKeyMap, &mCrossValidationKeyMap);
  mpConstraints->setExperimentSet(const_cast<const CExperimentSet *&>(mpExperimentSet));
  mpConstraints->setCrossValidationSet(const_cast<const CCrossValidationSet *&>(mpCrossValidationSet));

  mChanged = false;

  return true;
}

CCopasiMethod * CQFittingWidget::createMethod(const CCopasiMethod::SubType & type)
{return CFitMethod::createMethod(type);}

bool CQFittingWidget::runTask()
{
  CFitTask * pTask =
    dynamic_cast< CFitTask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  commonAfterRunTask();

  return success;
}

void CQFittingWidget::slotExperimentData()
{
  CQExperimentData * pDialog = new CQExperimentData(this);
  pDialog->load(mpExperimentSet);

  connect(pDialog, SIGNAL(experimentChanged()), mpParameters, SLOT(slotExperimentChanged()));
  connect(pDialog, SIGNAL(experimentChanged()), mpConstraints, SLOT(slotExperimentChanged()));

  pDialog->exec();

  pdelete(pDialog);
}

void CQFittingWidget::slotPageChange(QWidget * currentPage)
{
  if (mpTabWidget->tabLabel(currentPage).contains("Parameters", true))
    mpCurrentList = mpParameters;
  else
    mpCurrentList = mpConstraints;
}

void CQFittingWidget::init()
{
  mpHeaderWidget->setTaskName("Parameter Estimation");

  CQFittingWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQFittingWidgetLayout->addWidget(mpBtnWidget);

  addMethodSelectionBox(CFitTask::ValidMethods);
  addMethodParameterTable();

  mpParameterPageLayout = new QHBoxLayout(mpParametersPage, 0, 6, "mpParameterPageLayout");
  mpParameters = new CQFittingItemWidget(mpParametersPage);
  mpParameters->setItemType(CQFittingItemWidget::FIT_ITEM);
  mpParameterPageLayout->addWidget(mpParameters);
  connect(mpParameters, SIGNAL(numberChanged(int)), this, SLOT(slotParameterNumberChanged(int)));

  mpConstraintPageLayout = new QHBoxLayout(mpConstraintsPage, 0, 6, "mpConstraintsPageLayout");
  mpConstraints = new CQFittingItemWidget(mpConstraintsPage);
  mpConstraints->setItemType(CQFittingItemWidget::FIT_CONSTRAINT);
  mpConstraintPageLayout->addWidget(mpConstraints);
  connect(mpConstraints, SIGNAL(numberChanged(int)), this, SLOT(slotConstraintNumberChanged(int)));

  mpCurrentList = mpParameters;
  mpExperimentSet = NULL;
  mpCrossValidationSet = NULL;

#ifndef COPASI_CROSSVALIDATION
  mpBtnCrossValidation->hide();
#endif
}

void CQFittingWidget::slotParameterNumberChanged(int number)
{
  QString TabLabel = "Parameters (" + QString::number(number) + ")";
  mpTabWidget->setTabLabel(mpParametersPage, TabLabel);
}

void CQFittingWidget::slotConstraintNumberChanged(int number)
{
  QString TabLabel = "Constraints (" + QString::number(number) + ")";
  mpTabWidget->setTabLabel(mpConstraintsPage, TabLabel);
}

void CQFittingWidget::destroy()
{
  pdelete(mpExperimentSet);

#ifdef COPASI_CROSSVALIDATION
  pdelete(mpCrossValidationSet);
#endif // COPASI_CROSSVALIDATION
}

void CQFittingWidget::slotCrossValidationData()
{
#ifdef COPASI_CROSSVALIDATION
  CQExperimentData * pDialog = new CQExperimentData(this);
  pDialog->load(mpCrossValidationSet);

  connect(pDialog, SIGNAL(experimentChanged()), mpParameters, SLOT(slotCrossValidationChanged()));
  connect(pDialog, SIGNAL(experimentChanged()), mpConstraints, SLOT(slotCrossValidationChanged()));

  pDialog->exec();

  pdelete(pDialog);
#endif // COPASI_CROSSVALIDATION
}
