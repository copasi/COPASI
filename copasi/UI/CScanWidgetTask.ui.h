/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CScanWidgetTask.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/22 15:54:51 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include <qvalidator.h>
#include <CCopasiSelectionDialog.h>

void CScanWidgetTask::init()
{
  //no validators to be set in this widget
}

#include "report/CCopasiObjectName.h"
bool CScanWidgetTask::initFromScanProblem(CScanProblem * pg, const CModel* model)
{
  if (!model) return false;
  mpModel = model;

  CCopasiTask::Type type = pg->getSubtask();
  switch (type)
    {
    case CCopasiTask::steadyState :
      comboType->setCurrentItem(0);
      break;
    case CCopasiTask::timeCourse :
      comboType->setCurrentItem(1);
      break;
    case CCopasiTask::mca :
      comboType->setCurrentItem(2);
      break;
    default :
      std::cout << "unknown subtask in scan. Should not happen." << std::endl;
      comboType->setCurrentItem(0);
    }

  checkInitialConditions->setChecked(!(pg->getAdjustInitialConditions()));

  checkOutput->setChecked(pg->getOutputInSubtask());

  return true;
}

bool CScanWidgetTask::saveToScanProblem(CScanProblem * pg) const
  {
    int type = comboType->currentItem();
    switch (type)
      {
      case 0 :
        pg->setSubtask(CCopasiTask::steadyState);
        break;
      case 1 :
        pg->setSubtask(CCopasiTask::timeCourse);
        break;
      case 2 :
        pg->setSubtask(CCopasiTask::mca);
        break;
      default :
        std::cout << "unknown subtask in scan. Should not happen." << std::endl;
        pg->setSubtask(CCopasiTask::steadyState);
      }

    pg->setAdjustInitialConditions(!(checkInitialConditions->isChecked()));

    pg->setOutputInSubtask(checkOutput->isChecked());

    return true;
  }
