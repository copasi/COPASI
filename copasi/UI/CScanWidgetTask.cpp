// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QValidator>

#include <iostream>

#include "CScanWidgetTask.h"
#include "CCopasiSelectionDialog.h"

#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/scan/CScanProblem.h"

/*
 *  Constructs a CScanWidgetTask as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetTask::CScanWidgetTask(QWidget* parent, const char* name, Qt::WindowFlags f):
  QWidget(parent, f),
  mpObject(NULL),
  mpModel(NULL)

{
  setObjectName(QString::fromUtf8(name));
  setupUi(this);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetTask::~CScanWidgetTask()
{
  // no need to delete child widgets, Qt does it all for us
}

void CScanWidgetTask::init()
{
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  QColor Foreground = Palette.color(QPalette::Active, QPalette::Text);
  QColor Background = Palette.color(QPalette::Active, QPalette::Base);
  QColor Target(255, 210, 210, 255);

  if (Foreground.redF() + Foreground.greenF() + Foreground.blueF() > Background.redF() + Background.greenF() + Background.blueF())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      setStyleSheet("color: " + Target.name(QColor::HexRgb));
#else
      setStyleSheet("color: " + Target.name());
#endif
    }
  else
    {
      QPalette palette;
      QBrush brush(Target);
      brush.setStyle(Qt::SolidPattern);
      palette.setBrush(QPalette::Active, QPalette::Base, brush);
      palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
      QBrush brush1(QColor(33, 36, 39, 255));
      brush1.setStyle(Qt::SolidPattern);
      palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
      frame->setPalette(palette);
    }
}

// virtual
void CScanWidgetTask::load(const CScanProblem * pg)
{
  CTaskEnum::Task type = pg->getSubtask();
  int n;

  switch (type)
    {
      case CTaskEnum::Task::steadyState:
        n = 0;
        break;

      case CTaskEnum::Task::timeCourse:
        n = 1;
        break;

      case CTaskEnum::Task::mca:
        n = 2;
        break;

      case CTaskEnum::Task::lyap:
        n = 3;
        break;

      case CTaskEnum::Task::optimization:
        n = 4;
        break;

      case CTaskEnum::Task::parameterFitting:
        n = 5;
        break;

      case CTaskEnum::Task::sens:
        n = 6;
        break;

      case CTaskEnum::Task::lna:
        n = 7;
        break;

      case CTaskEnum::Task::crosssection:
        n = 8;
        break;

      case CTaskEnum::Task::tssAnalysis:
        n = 9;
        break;

      case CTaskEnum::Task::timeSens:
        n = 10;
        break;

      default:
        n = 0;
        break;
    }

  comboType->setCurrentIndex(n);

  mpCheckContinue->setChecked(pg->getContinueFromCurrentState());

  checkOutput->setChecked(pg->getOutputInSubtask());

  mpContinueOnError->setChecked(pg->getContinueOnError());

  return;
}

// virtual
bool CScanWidgetTask::save(CScanProblem * pg) const
{
  bool changed = false;
  int type = comboType->currentIndex();

  CTaskEnum::Task Type;

  switch (type)
    {
      case 0:
        Type = CTaskEnum::Task::steadyState;
        break;

      case 1:
        Type = CTaskEnum::Task::timeCourse;
        break;

      case 2:
        Type = CTaskEnum::Task::mca;
        break;

      case 3:
        Type = CTaskEnum::Task::lyap;
        break;

      case 4:
        Type = CTaskEnum::Task::optimization;
        break;

      case 5:
        Type = CTaskEnum::Task::parameterFitting;
        break;

      case 6:
        Type = CTaskEnum::Task::sens;
        break;

      case 7:
        Type = CTaskEnum::Task::lna;
        break;

      case 8:
        Type = CTaskEnum::Task::crosssection;
        break;

      case 9:
        Type = CTaskEnum::Task::tssAnalysis;
        break;

      case 10:
        Type = CTaskEnum::Task::timeSens;
        break;

      default :
        Type = CTaskEnum::Task::steadyState;
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

  if (pg->getContinueOnError() != mpContinueOnError->isChecked())
    {
      pg->setContinueOnError(mpContinueOnError->isChecked());
      changed = true;
    }

  return changed;
}

void CScanWidgetTask::typeChanged(int n)
{
  switch (n)
    {
      case 1:
      case 8:
        checkOutput->setChecked(true);
        break;

      default:
        checkOutput->setChecked(false);
        break;
    }
}
