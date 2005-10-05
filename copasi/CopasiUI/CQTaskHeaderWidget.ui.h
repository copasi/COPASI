/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQTaskHeaderWidget.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/05 16:24:07 $
   End CVS Header */

#include "qtUtilities.h"

#include "utilities/CCopasiTask.h"

bool CQTaskHeaderWidget::saveExecutable(CCopasiTask * pTask)
{
  pTask->setScheduled(mpBoxExecutable->isChecked());
  return true;
}

bool CQTaskHeaderWidget::loadExecutable(const CCopasiTask * pTask)
{
  mpBoxExecutable->setChecked(pTask->isScheduled());
  return true;
}

bool CQTaskHeaderWidget::setTaskName(const std::string & name)
{
  mpLblName->setText("<h2>" + FROM_UTF8(name) + "</h2>");
  return true;
}
