/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQTaskHeaderWidget.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/06 19:19:18 $
   End CVS Header */

#include "qtUtilities.h"

#include "utilities/CCopasiTask.h"

bool CQTaskHeaderWidget::setTaskName(const std::string & name)
{
  mpLblName->setText("<h2>" + FROM_UTF8(name) + "</h2>");
  return true;
}
