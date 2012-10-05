// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtGui/QValidator>

#include <iostream>

#include "copasi.h"

#include "CScanWidgetTask.h"
#include "CCopasiSelectionDialog.h"

#include "utilities/CCopasiParameterGroup.h"
#include "report/CCopasiObjectName.h"

/*
 *  Constructs a CScanWidgetTask as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetTask::CScanWidgetTask(QWidget* parent, const char* name, Qt::WindowFlags f)
  : QWidget(parent, f)
{
  setObjectName(QString::fromUtf8(name));
  setupUi(this);
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

// virtual
void CScanWidgetTask::load(const CScanProblem * pg)
{
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

      default:
        n = 0;
        break;
    }

  comboType->setCurrentIndex(n);

  mpCheckContinue->setChecked(pg->getContinueFromCurrentState());

  checkOutput->setChecked(pg->getOutputInSubtask());

  return;
}

// virtual
bool CScanWidgetTask::save(CScanProblem * pg) const
{
  bool changed = false;
  int type = comboType->currentIndex();

  CCopasiTask::Type Type;

  switch (type)
    {
      case 0:
        Type = CCopasiTask::steadyState;
        break;

      case 1:
        Type = CCopasiTask::timeCourse;
        break;

      case 2:
        Type = CCopasiTask::mca;
        break;

      case 3:
        Type = CCopasiTask::lyap;
        break;

      case 4:
        Type = CCopasiTask::optimization;
        break;

      case 5:
        Type = CCopasiTask::parameterFitting;
        break;

      case 6:
        Type = CCopasiTask::sens;
        break;

      case 7:
        Type = CCopasiTask::lna;
        break;

      default :
        Type = CCopasiTask::steadyState;
        break;
    }

  if (Type != pg->getSubtask())
    {
      pg->setSubtask(Type);
      changed = true;
    }

  if (pg->getContinueFromCurrentState() != mpCheckContinue->isChecked())
    {
      pg->setContinueFromCurrentState(mpCheckContinue->isChecked());
      changed = true;
    }

  if (pg->getOutputInSubtask() != checkOutput->isChecked())
    {
      pg->setOutputInSubtask(checkOutput->isChecked());
      changed = true;
    }

  return changed;
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
