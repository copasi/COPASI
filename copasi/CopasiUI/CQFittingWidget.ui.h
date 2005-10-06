/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingWidget.ui.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/06 20:35:05 $
   End CVS Header */

#include <qlabel.h>

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"

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

  mpConstraintPageLayout = new QHBoxLayout(mpConstraintsPage, 0, 6, "mpParameterPageLayout");
  mpConstraints = new CScanContainerWidget(mpConstraintsPage);
  mpConstraintPageLayout->addWidget(mpConstraints);
}
