/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingWidget.ui.h,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/02 15:47:22 $
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
              mpChanged = true;
            }

          DealtWith.insert(pExperiment);
        }
      else
        {
          mKeyMap.erase(pExperimentSet->getExperiment(i)->CCopasiParameter::getKey());
          pExperimentSet->removeParameter(i);
          mpChanged = true;
        }
    }

  for (i = 0, imax = mpExperimentSet->size(); i < imax; i++)
    {
      pExperiment = mpExperimentSet->getExperiment(i);
      if (DealtWith.count(pExperiment)) continue;

      pExperiment = pExperimentSet->addExperiment(*pExperiment);
      mKeyMap[pExperiment->CCopasiParameter::getKey()] =
        mpExperimentSet->getExperiment(i)->CCopasiParameter::getKey();
      mpChanged = true;
    }

  // We need to invert the key map for saving!
  std::map<std::string, std::string>::iterator it = mKeyMap.begin();
  std::map<std::string, std::string>::iterator end = mKeyMap.end();
  std::map<std::string, std::string>::iterator found;

  std::map<std::string, std::string> KeyMap;
  for (; it != end; ++it)
    KeyMap[it->second] = it->first;

  // Save parameters
  CCopasiParameterGroup * pGroup = pProblem->getGroup("OptimizationItemList");

  std::vector< CFitItem * > * pVector =
    static_cast<std::vector< CFitItem * > *>(pGroup->CCopasiParameter::getValue().pVOID);

  imax = std::min<unsigned C_INT32>(pVector->size(), mpParameters->numRows());
  for (i = 0; i < imax; i++)
    if (static_cast<CQFittingItemWidget *>(mpParameters->getWidgetList()[i])->save(*(*pVector)[i]))
      mpChanged = true;

  // Remove exceeding parameters
  imax = pVector->size();
  if (i < imax)
    {
      mpChanged = true;

      for (; i < imax; i++)
        pGroup->removeParameter(i);
    }

  // Add missing parameters
  imax = mpParameters->numRows();
  if (i < imax)
    {
      mpChanged = true;

      CFitItem * pFitItem;

      for (; i < imax; i++)
        {
          pFitItem = new CFitItem();
          static_cast<CQFittingItemWidget *>(mpParameters->getWidgetList()[i])->save(*pFitItem);
          pGroup->addParameter(pFitItem);
        }
    }

  // Change the affected experiments keys
  std::vector<CCopasiParameter *> * pExp;
  std::vector<CCopasiParameter *>::iterator itExp;
  std::vector<CCopasiParameter *>::iterator endExp;

  for (i = 0, imax = pGroup->size(); i < imax; i++)
    {
      pExp = (*pVector)[i]->getGroup("Affected Experiments")->CCopasiParameter::getValue().pGROUP;

      for (itExp = pExp->begin(), endExp = pExp->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(KeyMap[*(*itExp)->getValue().pKEY]);
    }

  // Save constraints
  pGroup = pProblem->getGroup("OptimizationConstraintList");
  pVector =
    static_cast<std::vector< CFitItem * > *>(pGroup->CCopasiParameter::getValue().pVOID);

  imax =
    std::min<unsigned C_INT32>(pVector->size(), mpConstraints->numRows());

  for (i = 0; i < imax; i++)
    if (static_cast<CQFittingItemWidget *>(mpConstraints->getWidgetList()[i])->save(*(*pVector)[i]))
      mpChanged = true;

  // Remove exceeding constraints
  imax = pVector->size();
  if (i < imax)
    {
      mpChanged = true;

      for (; i < imax; i++)
        pGroup->removeParameter(i);
    }

  // Add missing constraints
  imax = mpConstraints->numRows();
  if (i < imax)
    {
      mpChanged = true;

      CFitItem * pFitItem;

      for (; i < imax; i++)
        {
          pFitItem = new CFitItem();
          static_cast<CQFittingItemWidget *>(mpConstraints->getWidgetList()[i])->save(*pFitItem);
          pGroup->addParameter(pFitItem);
        }
    }

  // Change the affected experiments keys
  for (i = 0, imax = pGroup->size(); i < imax; i++)
    {
      pExp = (*pVector)[i]->getGroup("Affected Experiments")->CCopasiParameter::getValue().pGROUP;

      for (itExp = pExp->begin(), endExp = pExp->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(KeyMap[*(*itExp)->getValue().pKEY]);
    }

  if (mpChanged) CCopasiDataModel::Global->changed();

  mpChanged = false;
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

  CQFittingItemWidget * pFitItemWidget;

  std::vector< COptItem * >::const_iterator it =
    pProblem->getOptItemList().begin();
  std::vector< COptItem * >::const_iterator end =
    pProblem->getOptItemList().end();

  mpParameters->clearWidgetList();
  for (; it != end; ++it)
    {
      pFitItemWidget = new CQFittingItemWidget(mpParameters);
      pFitItemWidget->enableFitItem(true);
      pFitItemWidget->setExperimentSet(mpExperimentSet);
      pFitItemWidget->load(*static_cast<const CFitItem *>(*it));
      mpParameters->addWidget(pFitItemWidget);
    }

  QString TabLabel = "Parameters (" + QString::number(mpParameters->numRows()) + ")";
  mpTabWidget->setTabLabel(mpParametersPage, TabLabel);

  it = pProblem->getConstraintList().begin();
  end = pProblem->getConstraintList().end();

  mpConstraints->clearWidgetList();
  for (; it != end; ++it)
    {
      pFitItemWidget = new CQFittingItemWidget(mpConstraints);
      pFitItemWidget->enableFitItem(true);
      pFitItemWidget->setExperimentSet(mpExperimentSet);
      pFitItemWidget->load(*static_cast<const CFitItem *>(*it));
      mpConstraints->addWidget(pFitItemWidget);
    }

  TabLabel = "Constraints (" + QString::number(mpConstraints->numRows()) + ")";
  mpTabWidget->setTabLabel(mpConstraintsPage, TabLabel);

  mpChanged = false;

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

  pTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);

  try
    {
      if (!pTask->process(true))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      mProgressBar->finish();
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

void CQFittingWidget::slotBtnAdd()
{
  CQFittingItemWidget * tmp = new CQFittingItemWidget(mpCurrentList);
  tmp->enableFitItem(true);
  tmp->setExperimentSet(mpExperimentSet);
  mpCurrentList->addWidget(tmp);

  int totalRows = mpCurrentList->numRows();
  mpCurrentList->ensureCellVisible(totalRows - 1, 0);
  tmp->mpBtnObject->setFocus();

  QString TabLabel = mpTabWidget->tabLabel(mpTabWidget->currentPage());
  TabLabel.replace(QString::number(totalRows - 1), QString::number(totalRows));
  mpTabWidget->setTabLabel(mpTabWidget->currentPage(), TabLabel);

  return;
}

void CQFittingWidget::slotExperimentData()
{
  CQExperimentData * pDialog = new CQExperimentData(this);
  pDialog->load(mpExperimentSet);

  if (pDialog->exec () == QDialog::Accepted)
    {
      unsigned C_INT32 i, imax;

      for (i = 0, imax = mpParameters->numRows(); i < imax; i++)
        static_cast<CQFittingItemWidget *>(mpParameters->getWidgetList()[i])->update();

      for (i = 0, imax = mpConstraints->numRows(); i < imax; i++)
        static_cast<CQFittingItemWidget *>(mpConstraints->getWidgetList()[i])->update();
    }

  pdelete(pDialog);
}

void CQFittingWidget::slotPageChange(QWidget * currentPage)
{
  if (mpTabWidget->tabLabel(currentPage).contains("Parameters", true))
    {
      mpBtnAdd->setText("Add Parameter");
      mpCurrentList = mpParameters;
    }
  else
    {
      mpBtnAdd->setText("Add Constraint");
      mpCurrentList = mpConstraints;
    }
}

void CQFittingWidget::slotItemDeleted()
{
  int totalRows = mpCurrentList->numRows();

  QString TabLabel = mpTabWidget->tabLabel(mpTabWidget->currentPage());
  TabLabel.replace(QString::number(totalRows + 1), QString::number(totalRows));
  mpTabWidget->setTabLabel(mpTabWidget->currentPage(), TabLabel);
}

void CQFittingWidget::slotCopyItemWidget(int index)
{
  CQFittingItemWidget * tmp =
    static_cast<CQFittingItemWidget *>(mpCurrentList->getWidgetList()[index])->copy();

  mpCurrentList->insertWidget(tmp, index + 1);

  int totalRows = mpCurrentList->numRows();
  mpCurrentList->ensureCellVisible(index + 1, 0);
  tmp->mpBtnObject->setFocus();

  QString TabLabel = mpTabWidget->tabLabel(mpTabWidget->currentPage());
  TabLabel.replace(QString::number(totalRows - 1), QString::number(totalRows));
  mpTabWidget->setTabLabel(mpTabWidget->currentPage(), TabLabel);
}

void CQFittingWidget::init()
{
  mpHeaderWidget->setTaskName("Parameter Fitting");

  CQFittingWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQFittingWidgetLayout->addWidget(mpBtnWidget);

  addMethodSelectionBox(CFitTask::ValidMethods);
  addMethodParameterTable();

  mpParameterPageLayout = new QHBoxLayout(mpParametersPage, 0, 6, "mpParameterPageLayout");
  mpParameters = new CScanContainerWidget(mpParametersPage);
  mpParameters->enableCopy(true);
  mpParameterPageLayout->addWidget(mpParameters);
  connect(mpParameters, SIGNAL(itemDeleted()), this, SLOT(slotItemDeleted()));
  connect(mpParameters, SIGNAL(copyWidget(int)), this, SLOT(slotCopyItemWidget(int)));

  mpConstraintPageLayout = new QHBoxLayout(mpConstraintsPage, 0, 6, "mpConstraintsPageLayout");
  mpConstraints = new CScanContainerWidget(mpConstraintsPage);
  mpConstraints->enableCopy(true);
  mpConstraintPageLayout->addWidget(mpConstraints);
  connect(mpConstraints, SIGNAL(itemDeleted()), this, SLOT(slotItemDeleted()));
  connect(mpConstraints, SIGNAL(copyWidget(int)), this, SLOT(slotCopyItemWidget(int)));

  mpCurrentList = mpParameters;
  mpExperimentSet = NULL;
}
