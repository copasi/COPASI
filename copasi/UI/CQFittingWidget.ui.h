/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingWidget.ui.h,v $
   $Revision: 1.21 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/14 16:30:16 $
   End CVS Header */

#include <qlabel.h>
#include <qtoolbutton.h>
#include <qmessagebox.h>

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQFittingItemWidget.h"
#include "CProgressBar.h"
#include "CQExperimentData.h"

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

  // Save experiment set
  CExperimentSet * pExperimentSet =
    dynamic_cast<CExperimentSet *>(pProblem->getGroup("Experiment Set"));

  std::string Name;
  CExperiment * pExperiment;
  unsigned C_INT32 i, imax;

  std::set<CExperiment *> DealtWith;

  for (i = pExperimentSet->size() - 1; i != C_INVALID_INDEX; i--)
    {
      pExperiment =
        dynamic_cast<CExperiment *>(GlobalKeys.get(mKeyMap[pExperimentSet->getExperiment(i)->CCopasiParameter::getKey()]));

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
          mKeyMap.erase(pExperimentSet->getExperiment(i)->CCopasiParameter::getKey());
          pExperimentSet->removeParameter(i);
          mChanged = true;
        }
    }

  for (i = 0, imax = mpExperimentSet->size(); i < imax; i++)
    {
      pExperiment = mpExperimentSet->getExperiment(i);
      if (DealtWith.count(pExperiment)) continue;

      pExperiment = pExperimentSet->addExperiment(*pExperiment);
      mKeyMap[pExperiment->CCopasiParameter::getKey()] =
        mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey();
      mChanged = true;
    }

  // We need to invert the key map for saving!
  std::map<std::string, std::string>::iterator it = mKeyMap.begin();
  std::map<std::string, std::string>::iterator end = mKeyMap.end();
  std::map<std::string, std::string>::iterator found;

  std::map<std::string, std::string> KeyMap;
  for (; it != end; ++it)
    KeyMap[it->second] = it->first;

  mChanged |= mpParameters->save(&KeyMap);
  mChanged |= mpConstraints->save(&KeyMap);

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

  mKeyMap.clear();
  unsigned C_INT32 i, imax = mpExperimentSet->size();

  for (i = 0; i < imax; i++)
    mKeyMap[pExperimentSet->getExperiment(i)->CCopasiParameter::getKey()] =
      mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey();

  mpParameters->load(pProblem->getGroup("OptimizationItemList"), &mKeyMap);
  mpParameters->setExperimentSet(const_cast<const CExperimentSet *&>(mpExperimentSet));

  mpConstraints->load(pProblem->getGroup("OptimizationConstraintList"), &mKeyMap);
  mpConstraints->setExperimentSet(const_cast<const CExperimentSet *&>(mpExperimentSet));

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

  try
    {
      if (!pTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL))
        throw CCopasiException(CCopasiMessage::peekLastMessage());

      if (!pTask->process(true))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::warning(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  pTask->restore();

  commonAfterRunTask();

  return true;
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
  mpParameters->setItemType(FIT_ITEM);
  mpParameterPageLayout->addWidget(mpParameters);
  connect(mpParameters, SIGNAL(numberChanged(int)), this, SLOT(slotParameterNumberChanged(int)));

  mpConstraintPageLayout = new QHBoxLayout(mpConstraintsPage, 0, 6, "mpConstraintsPageLayout");
  mpConstraints = new CQFittingItemWidget(mpConstraintsPage);
  mpConstraints->setItemType(FIT_CONSTRAINT);
  mpConstraintPageLayout->addWidget(mpConstraints);
  connect(mpConstraints, SIGNAL(numberChanged(int)), this, SLOT(slotConstraintNumberChanged(int)));

  mpCurrentList = mpParameters;
  mpExperimentSet = NULL;
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
}
