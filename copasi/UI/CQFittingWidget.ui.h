/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingWidget.ui.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/07 13:49:24 $
   End CVS Header */

#include <qlabel.h>

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "OptimizationItemWidget.h"

#include "report/CKeyFactory.h"
#include "parameterFitting/CFitTask.h"
#include "parameterFitting/CFitMethod.h"
#include "CopasiDataModel/CCopasiDataModel.h"

bool CQFittingWidget::saveTask()
{
  CFitTask * pTask =
    dynamic_cast< CFitTask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  saveCommon();
  saveMethod();

  // :TODO: implement me!
  if (mpChanged) CCopasiDataModel::Global->changed();

  mpChanged = false;
  return true;
}

bool CQFittingWidget::loadTask()
{
  CFitTask * pTask =
    dynamic_cast< CFitTask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  loadCommon();
  loadMethod();

  // :TODO: implement me!

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
  OptimizationItemWidget * tmp;
  tmp = new OptimizationItemWidget(mpCurrentList);
  mpCurrentList->addWidget(tmp);

  int totalRows = mpCurrentList->numRows();
  mpCurrentList->ensureCellVisible(totalRows - 1, 0);
  tmp->ObjectName->setFocus();

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
