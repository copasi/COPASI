/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingWidget.ui.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/12 13:25:03 $
   End CVS Header */

#include <qlabel.h>
#include <qtoolbutton.h>

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQFittingItemWidget.h"

#include "report/CKeyFactory.h"
#include "parameterFitting/CFitTask.h"
#include "parameterFitting/CFitItem.h"
#include "parameterFitting/CFitMethod.h"
#include "parameterFitting/CFitProblem.h"
#include "CopasiDataModel/CCopasiDataModel.h"

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

  // Save parameters
  CCopasiParameterGroup * pGroup = pProblem->getGroup("OptimizationItemList");

  std::vector< CFitItem * > * pVector =
    static_cast<std::vector< CFitItem * > *>(pGroup->CCopasiParameter::getValue().pVOID);

  unsigned C_INT32 i, imax =
    std::min<unsigned C_INT32>(pVector->size(), mpParameters->numRows());

  for (i = 0; i < imax; i++)
    if (static_cast<CQFittingItemWidget *>(mpParameters->getWidgetList()[i])->saveFitItem(*(*pVector)[i]))
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
          static_cast<CQFittingItemWidget *>(mpParameters->getWidgetList()[i])->saveFitItem(*pFitItem);
          pGroup->addParameter(pFitItem);
        }
    }

  // Save constraints
  pGroup = pProblem->getGroup("OptimizationConstraintList");
  pVector =
    static_cast<std::vector< CFitItem * > *>(pGroup->CCopasiParameter::getValue().pVOID);

  imax =
    std::min<unsigned C_INT32>(pVector->size(), mpConstraints->numRows());

  for (i = 0; i < imax; i++)
    if (static_cast<CQFittingItemWidget *>(mpConstraints->getWidgetList()[i])->saveFitItem(*(*pVector)[i]))
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
          static_cast<CQFittingItemWidget *>(mpConstraints->getWidgetList()[i])->saveFitItem(*pFitItem);
          pGroup->addParameter(pFitItem);
        }
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

  CQFittingItemWidget * pFitItemWidget;

  std::vector< COptItem * >::const_iterator it =
    pProblem->getOptItemList().begin();
  std::vector< COptItem * >::const_iterator end =
    pProblem->getOptItemList().end();

  mpParameters->clearWidgetList();
  for (; it != end; ++it)
    {
      pFitItemWidget = new CQFittingItemWidget(mpParameters);
      pFitItemWidget->loadFitItem(*static_cast<const CFitItem *>(*it));
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
      pFitItemWidget->loadFitItem(*static_cast<const CFitItem *>(*it));
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

  // :TODO: implement me!
  return true;
}

void CQFittingWidget::slotBtnAdd()
{
  CQFittingItemWidget * tmp = new CQFittingItemWidget(mpCurrentList);
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
{}

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

void CQFittingWidget::init()
{
  mpHeaderWidget->setTaskName("Parameter Fitting");

  CQFittingWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQFittingWidgetLayout->addWidget(mpBtnWidget);

  addMethodSelectionBox(CFitTask::ValidMethods);
  addMethodParameterTable();

  mpParameterPageLayout = new QHBoxLayout(mpParametersPage, 0, 6, "mpParameterPageLayout");
  mpParameters = new CScanContainerWidget(mpParametersPage);
  mpParameterPageLayout->addWidget(mpParameters);
  connect(mpParameters, SIGNAL(itemDeleted()), this, SLOT(slotItemDeleted()));

  mpConstraintPageLayout = new QHBoxLayout(mpConstraintsPage, 0, 6, "mpConstraintsPageLayout");
  mpConstraints = new CScanContainerWidget(mpConstraintsPage);
  mpConstraintPageLayout->addWidget(mpConstraints);
  connect(mpConstraints, SIGNAL(itemDeleted()), this, SLOT(slotItemDeleted()));

  mpCurrentList = mpParameters;
}
