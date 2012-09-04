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

#include <arguments.h>
#include <QString>

Worker::Worker(CopasiUI3Window *window, Arguments *args)
{
  mpArgs = args;
  mpWindow = window;
  mpDataModel= mpWindow->getDataModel();  

  // open the newly generated model
  mpWindow->openInitialDocument(QString((args->getFilename() + ".view.cps").c_str()));

  // connect the finish slot, so it will switch to the correct tab
  connect(mpDataModel, SIGNAL(finished(bool)), this, SLOT(finishedLoading(bool)));
}


TaskWidget* Worker::getWidgetForTask(CCopasiTask *task)  const
{
  if (task == NULL) return NULL;

  ListViews* views = mpWindow->getMainWidget();

  switch(task->getType())
  {
  case CCopasiTask::Type::steadyState:
    return reinterpret_cast<TaskWidget*>(views->getSteadyStateWidget());
  case CCopasiTask::Type::timeCourse:
    return reinterpret_cast<TaskWidget*>(views->getTrajectoryWidget());
  case CCopasiTask::Type::scan:
    return reinterpret_cast<TaskWidget*>(views->getScanWidget());
  case CCopasiTask::Type::optimization:
    return reinterpret_cast<TaskWidget*>(views->getOptimizationWidget());
  case CCopasiTask::Type::parameterFitting:
    return reinterpret_cast<TaskWidget*>(views->getFittingWidget());
  case CCopasiTask::Type::mca:
    return reinterpret_cast<TaskWidget*>(views->getMCAWidget());
  case CCopasiTask::Type::lna:
    return reinterpret_cast<TaskWidget*>(views->getLNAWidget());
  case CCopasiTask::Type::lyap:
  case CCopasiTask::Type::fluxMode:
  case CCopasiTask::Type::tssAnalysis:
  case CCopasiTask::Type::sens:
  case CCopasiTask::Type::moieties:
  case CCopasiTask::Type::crosssection:
  case CCopasiTask::Type::unset:
  default:
    // have no widget for these
    return NULL;
  }

}

int Worker::getIndexForTask(CCopasiTask* task) 
{
  if (task == NULL) return -1;

  switch(task->getType())
  {
  case CCopasiTask::Type::steadyState:
    return 21;
  case CCopasiTask::Type::timeCourse:
    return 23;
  case CCopasiTask::Type::scan:
    return 31;
  case CCopasiTask::Type::optimization:
    return 32;
  case CCopasiTask::Type::parameterFitting:
    return 33;
  case CCopasiTask::Type::mca:
    return 24;
  case CCopasiTask::Type::lna:
    return 35;
  case CCopasiTask::Type::lyap:
  case CCopasiTask::Type::fluxMode:
  case CCopasiTask::Type::tssAnalysis:
  case CCopasiTask::Type::sens:
  case CCopasiTask::Type::moieties:
  case CCopasiTask::Type::crosssection:
  case CCopasiTask::Type::unset:
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
    widget->runTask();
  }

  if (mpArgs->isHideWindow())
    mpWindow->hide();

}
