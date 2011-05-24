// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetTask.cpp,v $
//   $Revision: 1.18 $
//   $Name:  $
//   $Author: jpahle $
//   $Date: 2011/05/24 17:30:49 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtGui>

#include "copasi.h"

#include "CScanWidgetTask.h"

#include <iostream>

#include <qvalidator.h>

#include "UI/CCopasiSelectionDialog.h"
#include "utilities/CCopasiParameterGroup.h"

/*
 *  Constructs a CScanWidgetTask as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetTask::CScanWidgetTask(QWidget* parent, const char* name, Qt::WindowFlags f)
    : QWidget(parent, name, f)
{
  ui.setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetTask::~CScanWidgetTask()
{
  // no need to delete child widgets, Qt does it all for us
}

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
      case CCopasiTask::lna:
        n = 7;
        break;
      default :
        n = 0;
    }

  ui.comboType->setCurrentItem(n);

  ui.checkInitialConditions->setChecked(!(pg->getAdjustInitialConditions()));

  ui.checkOutput->setChecked(pg->getOutputInSubtask());

  return true;
}

bool CScanWidgetTask::saveToScanProblem(CScanProblem * pg) const
{
  int type = ui.comboType->currentItem();

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
      case 7:
        pg->setSubtask(CCopasiTask::lna);
        break;
      default :
        pg->setSubtask(CCopasiTask::steadyState);
    }

  pg->setAdjustInitialConditions(!(ui.checkInitialConditions->isChecked()));

  pg->setOutputInSubtask(ui.checkOutput->isChecked());

  return true;
}

void CScanWidgetTask::typeChanged(int n)
{
  switch (n)
    {
      case 1:
        ui.checkOutput->setChecked(true);
        break;

      default:
        ui.checkOutput->setChecked(false);
        break;
    }
}
