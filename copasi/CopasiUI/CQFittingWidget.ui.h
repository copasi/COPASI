/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingWidget.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/05 16:24:07 $
   End CVS Header */

#include <qlabel.h>

#include "CQTaskBtnWidget.h"
 #include "CQTaskHeaderWidget.h"

#include "report/CKeyFactory.h"
 #include "parameterFitting/CFitTask.h"

bool CQFittingWidget::saveTask()
{
  CFitTask * pTask =
    dynamic_cast< CFitTask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  mpHeaderWidget->saveExecutable(pTask);

  // :TODO: implement me!
  return true;
}

bool CQFittingWidget::loadTask()
{
  CFitTask * pTask =
    dynamic_cast< CFitTask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  mpHeaderWidget->loadExecutable(pTask);

  // :TODO: implement me!
  return true;
}

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
}
