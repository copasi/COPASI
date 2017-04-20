// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "worker.h"

#include "UI/copasiui3window.h"
#include "UI/DataModelGUI.h"
#include "UI/CQFittingWidget.h"
#include "UI/listviews.h"
#include "parameterFitting/CFitTask.h"
#include "parameterFitting/CFitProblem.h"
#include <QtCore/QThread>
#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "UI/CWindowInterface.h"

#include <arguments.h>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

Worker::Worker(CopasiUI3Window *window, Arguments *args) : mTaskStarted(false)
{
  mpArgs = args;
  mpWindow = window;
  mpDataModel = mpWindow->getDataModel();

  // open the newly generated model
  mpWindow->openInitialDocument(QString((args->getFilename() + ".view.cps").c_str()));

  // connect the finish slot, so it will switch to the correct tab
  connect(mpDataModel, SIGNAL(finished(bool)), this, SLOT(finishedLoading(bool)));
  connect(mpDataModel, SIGNAL(notifyView(ListViews::ObjectType, ListViews::Action, std::string)),
          this, SLOT(slotNotify(ListViews::ObjectType, ListViews::Action, std::string)));
}

bool Worker::slotNotify(ListViews::ObjectType objectType, ListViews::Action action, std::string key /*= ""*/)
{

  if (objectType == ListViews::STATE && action == ListViews::CHANGE && mTaskStarted)
    {
      mTaskStarted = false;

      if (mpArgs->haveOutputDir())
        {
          const QList< QPointer<QMainWindow> >& windows = mpWindow->getWindows();

          for (int index = 0; index < windows.count(); ++index)
            {
              const QMainWindow* mainWindow = windows[index];

              if (mainWindow == NULL) continue;

              const CWindowInterface* window = dynamic_cast<const CWindowInterface*>(mainWindow);

              if (window == NULL) continue;

              QString fileName = QString("%1/plot%2.%3")
                                 .arg(mpArgs->getOutputDir().c_str())
                                 .arg(index + 1)
                                 .arg(mpArgs->getFileType().c_str());
              window->saveToFile(fileName);
            }
        }

      if (mpArgs->isQuitAfterTaskExecution())
        {
          // quit
          qApp->quit();
        }
    }

  return true;
}

TaskWidget* Worker::getWidgetForTask(CCopasiTask *task)  const
{
  if (task == NULL) return NULL;

  ListViews* views = mpWindow->getMainWidget();

  switch (task->getType())
    {
      case CTaskEnum::steadyState:
        return reinterpret_cast<TaskWidget*>(views->getSteadyStateWidget());

      case CTaskEnum::timeCourse:
        return reinterpret_cast<TaskWidget*>(views->getTrajectoryWidget());

      case CTaskEnum::scan:
        return reinterpret_cast<TaskWidget*>(views->getScanWidget());

      case CTaskEnum::optimization:
        return reinterpret_cast<TaskWidget*>(views->getOptimizationWidget());

      case CTaskEnum::parameterFitting:
        return reinterpret_cast<TaskWidget*>(views->getFittingWidget());

      case CTaskEnum::mca:
        return reinterpret_cast<TaskWidget*>(views->getMCAWidget());

      case CTaskEnum::lna:
        return reinterpret_cast<TaskWidget*>(views->getLNAWidget());

      case CTaskEnum::lyap:
      case CTaskEnum::fluxMode:
      case CTaskEnum::tssAnalysis:
      case CTaskEnum::sens:
      case CTaskEnum::moieties:
      case CTaskEnum::crosssection:

        //case CTaskEnum::unset:
      default:
        // have no widget for these
        return NULL;
    }
}

int Worker::getIndexForTask(CCopasiTask* task)
{
  if (task == NULL) return -1;

  switch (task->getType())
    {
      case CTaskEnum::steadyState:
        return 21;

      case CTaskEnum::timeCourse:
        return 23;

      case CTaskEnum::scan:
        return 31;

      case CTaskEnum::optimization:
        return 32;

      case CTaskEnum::parameterFitting:
        return 33;

      case CTaskEnum::mca:
        return 24;

      case CTaskEnum::lna:
        return 35;

      case CTaskEnum::lyap:
      case CTaskEnum::fluxMode:
      case CTaskEnum::tssAnalysis:
      case CTaskEnum::sens:
      case CTaskEnum::moieties:
      case CTaskEnum::crosssection:

        //case CTaskEnum::unset:
      default:
        // have no id
        return -1;
    }
}

int Worker::getIndexForWidget(TaskWidget* widget)
{
  if (widget == NULL) return -1;

  CCopasiTask *task = widget->getTask();
  return getIndexForTask(task);
}

void Worker::finishedLoading(bool success)
{

  if (!success)
    return;

  if (mpArgs->isSwitchToTask())
    {
      mpWindow ->getMainWidget()->switchToOtherWidget(mpArgs->getTaskToSwitchTo(), "");
    }

  if (mpArgs->isRunScheduled())
    {
      CCopasiTask *task = Arguments::getFirstScheduledTask();

      if (task == NULL)
        return;

      if (!mpArgs->isSwitchToTask())
        mpWindow ->getMainWidget()->switchToOtherWidget(getIndexForTask(task), "");

      TaskWidget *widget = getWidgetForTask(task);
      mTaskStarted = true;
      widget->runTask();
    }

  if (mpArgs->isHideWindow())
    mpWindow->hide();
}
