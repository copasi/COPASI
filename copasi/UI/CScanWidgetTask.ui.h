/* Begin CVS Header
$Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CScanWidgetTask.ui.h,v $
$Revision: 1.14.2.1 $
$Name:  $
$Author: shoops $
$Date: 2008/07/31 23:13:45 $
End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

#include "copasi.h"

#include "UI/CCopasiSelectionDialog.h"

#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

void CScanWidgetTask::init()
{}

#include "report/CCopasiObjectName.h"
bool CScanWidgetTask::initFromScanProblem(CScanProblem * pg, const CModel* model)
{
  if (!model) return false;
  mpModel = model;

  CCopasiTask::Type type = pg->getSubtask();
  int n;
  switch (type)
    {
    case CCopasiTask::steadyState:
      n = 0;
      break;
    case CCopasiTask::timeCourse:
      n = 1;
      break;
    case CCopasiTask::mca:
      n = 2;
      break;
    case CCopasiTask::lyap:
      n = 3;
      break;
    case CCopasiTask::optimization:
      n = 4;
      break;
    case CCopasiTask::parameterFitting:
      n = 5;
      break;
    case CCopasiTask::sens:
      n = 6;
      break;
    default :
      n = 0;
    }
  comboType->setCurrentItem(n);

  checkInitialConditions->setChecked(!(pg->getAdjustInitialConditions()));

  checkOutput->setChecked(pg->getOutputInSubtask());

  return true;
}

bool CScanWidgetTask::saveToScanProblem(CScanProblem * pg) const
  {
    int type = comboType->currentItem();
    switch (type)
      {
      case 0:
        pg->setSubtask(CCopasiTask::steadyState);
        break;
      case 1:
        pg->setSubtask(CCopasiTask::timeCourse);
        break;
      case 2:
        pg->setSubtask(CCopasiTask::mca);
        break;
      case 3:
        pg->setSubtask(CCopasiTask::lyap);
        break;
      case 4:
        pg->setSubtask(CCopasiTask::optimization);
        break;
      case 5:
        pg->setSubtask(CCopasiTask::parameterFitting);
        break;
      case 6:
        pg->setSubtask(CCopasiTask::sens);
        break;
      default :
        pg->setSubtask(CCopasiTask::steadyState);
      }

    pg->setAdjustInitialConditions(!(checkInitialConditions->isChecked()));

    pg->setOutputInSubtask(checkOutput->isChecked());

    return true;
  }

void CScanWidgetTask::typeChanged(int n)
{
  switch (n)
    {
    case 1:
      checkOutput->setChecked(true);
      break;

    default:
      checkOutput->setChecked(false);
      break;
    }
}
