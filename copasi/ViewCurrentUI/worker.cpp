// Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QThread>
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "UI/CWindowInterface.h"

#include <arguments.h>
#include <QString>
#include <QList>
#include <QMutex>
#include <QWaitCondition>

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
      case CCopasiTask::steadyState:
        return reinterpret_cast<TaskWidget*>(views->getSteadyStateWidget());

      case CCopasiTask::timeCourse:
        return reinterpret_cast<TaskWidget*>(views->getTrajectoryWidget());

      case CCopasiTask::scan:
        return reinterpret_cast<TaskWidget*>(views->getScanWidget());

      case CCopasiTask::optimization:
        return reinterpret_cast<TaskWidget*>(views->getOptimizationWidget());

      case CCopasiTask::parameterFitting:
        return reinterpret_cast<TaskWidget*>(views->getFittingWidget());

      case CCopasiTask::mca:
        return reinterpret_cast<TaskWidget*>(views->getMCAWidget());

      case CCopasiTask::lna:
        return reinterpret_cast<TaskWidget*>(views->getLNAWidget());

      case CCopasiTask::lyap:
      case CCopasiTask::fluxMode:
      case CCopasiTask::tssAnalysis:
      case CCopasiTask::sens:
      case CCopasiTask::moieties:
      case CCopasiTask::crosssection:
      case CCopasiTask::unset:
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
      case CCopasiTask::steadyState:
        return 21;

      case CCopasiTask::timeCourse:
        return 23;

      case CCopasiTask::scan:
        return 31;

      case CCopasiTask::optimization:
        return 32;

      case CCopasiTask::parameterFitting:
        return 33;

      case CCopasiTask::mca:
        return 24;

      case CCopasiTask::lna:
        return 35;

      case CCopasiTask::lyap:
      case CCopasiTask::fluxMode:
      case CCopasiTask::tssAnalysis:
      case CCopasiTask::sens:
      case CCopasiTask::moieties:
      case CCopasiTask::crosssection:
      case CCopasiTask::unset:
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
