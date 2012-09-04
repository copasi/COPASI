#include "arguments.h"
#include "string.h"

#include <QString>
#include <QFile>

#include "CopasiDataModel/CCopasiDataModel.h"

#include "optimization/COptTask.h"
#include "optimization/COptProblem.h"


#include "report/CCopasiRootContainer.h"
#include "report/COutputAssistant.h"
#include "plot/CPlotSpecification.h"
#include "plot/COutputDefinitionVector.h"

#include "utilities/CCopasiMethod.h"


Arguments::Arguments(int argc, char* argv[])
  : mFilename("")
  , mTask("")
  , mReportFile("")
  , mRunScheduled(false)
  , mSetSolutionStatistic(false)
  , mDisableStatistic(false)
  , mDisablePlots(false)
  , mDisableRandomizeStartValues(false)
  , mHideWindow(false)
  , mClearTargets(false)
  , mSwitchToTask(-1)
  , mGenerateOutput(-1)
  , mArgc(argc)
  , mArgv(argv)
{
  parseArgs(argc, argv);
}

CCopasiTask* Arguments::getFirstScheduledTask()
{
  CCopasiVectorN<CCopasiTask> &taskList = *(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList();
  for(size_t i = 0; i < taskList.size(); ++i)
  {
    CCopasiTask *current = taskList[i];
    if (current->isScheduled())
      return current;
  }
  return NULL;
}


CCopasiTask* Arguments::getTaskForName(const std::string& name) const
{
  CCopasiVectorN<CCopasiTask> &taskList = *(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList();
  for(size_t i = 0; i < taskList.size(); ++i)
  {
    CCopasiTask *current = taskList[i];
    if (current->getObjectName() == name)
      return current;
  }
  return NULL;
}

CCopasiTask* Arguments::getTask() const
{
  if (haveTaskName())
    return getTaskForName(mTask);
  return getFirstScheduledTask();
}

bool Arguments::isGenerateOutput() const
{
  return mGenerateOutput != -1;
}

int Arguments::getOutputToGenerate() const
{
  return mGenerateOutput;
}

bool Arguments::haveReportFile() const
{
  return !mReportFile.empty();
}

const std::string& Arguments::getReportFile() const
{
  return mReportFile;
}

void Arguments::parseArgs(int argc, char* argv[])
{
  for (int i = 1; i < argc; ++i )
  {
    QString current(argv[i]);
    QString lower = current.toLower();

    if (lower == "-r" || lower == "--run-scheduled" )
    {
      mRunScheduled = true;
    }
    else if (i+1 < argc && (lower == "--switch-to-task"))
    {
      mSwitchToTask = QString(argv[i+1]).toInt();
      ++i;
    }
    else if (i+1 < argc && (lower == "--task"))
    {
      mTask = argv[i+1];
      ++i;
    }
    else if (lower == "--set-solution-statistic")
    {
      mSetSolutionStatistic=true;
    }
    else if (lower == "--disable-calculate-statistic")
    {
      mDisableStatistic=true;
    }
    else if (lower == "--disable-other-plots")
    {
      mDisablePlots=true;
    }
    else if (lower == "--hide")
    {
      mHideWindow=true;
    }
    else if (lower == "--clear-targets")
    {
      mClearTargets=true;
    }
    else if (lower == "--disable-randomize-startvalues")
    {
      mDisableRandomizeStartValues=true;
    }
    else if (i+1 < argc && (lower == "-g" || lower == "--generate-output"))
    {
      mGenerateOutput = QString(argv[i+1]).toInt();
      ++i;
    }
    else if (i+1 < argc && (lower == "-f" || lower == "--set-report-file"))
    {
      mReportFile = argv[i+1];
      ++i;
    }
    else if (QFile(current).exists() && mFilename.empty())
    {
      // only if we don't have a file yet, we assume this to be the copasi file
      mFilename = current.ascii();
    }
  }
}

bool Arguments::isSwitchToTask() const
{
  return mSwitchToTask != -1;
}

int Arguments::getTaskToSwitchTo() const
{
  return mSwitchToTask;
}

char** Arguments::getInitArgs() const
{
  char ** result = (char**)malloc(sizeof(char*)*2);
  result[0] = strdup(mArgv[0]);
  result[1] = strdup((mFilename + ".view.cps").c_str() );
  return result;
}

const std::string& Arguments::getFilename() const
{
  return mFilename;
}

bool Arguments::haveFile() const
{
  return mFilename.empty();
}

bool Arguments::isRunScheduled() const
{
  return mRunScheduled;
}

bool Arguments::haveTaskName() const
{
  return !mTask.empty();
}

const std::string& Arguments::getTaskName() const
{
  return mTask;
}

bool Arguments::isSolutionStatistic() const
{
  return mSetSolutionStatistic;
}

bool Arguments::isDisableStatistic() const
{
  return mDisableStatistic;
}

bool Arguments::isDisableRandomizeStartValues() const
{
  return mDisableRandomizeStartValues;
}

bool Arguments::isDisablePlots() const
{
  return mDisablePlots;
}

  bool Arguments::isHideWindow() const
  {
    return mHideWindow;
  }

  bool Arguments::isValid() const
  {
  	if (!haveFile()) return false;
  	if (!QFile(mFilename.c_str()).exists()) return false;
  	return true;
  }


std::string Arguments::prepareModel() const
{
  if (!isValid()) return "";

  CCopasiDataModel* model = (*CCopasiRootContainer::getDatamodelList())[0];
  model->loadModel(getFilename(), NULL);

  if (mDisablePlots)
  {
    for(size_t index = 0; index < model->getPlotDefinitionList()->size(); ++index)
    {
      (*model->getPlotDefinitionList())[index]->setActive(false);
    }
  }

  if (mClearTargets)
  {
    for(size_t index = 0; index < model->getTaskList()->size(); ++index)
    {
      (*model->getTaskList())[index]->getReport().setTarget("");
    }
  }

  CCopasiTask *task = getTask();
  if (task != NULL)
  {
    if (isGenerateOutput())
    {
      // calls initialize which is private
      COutputAssistant::getListOfDefaultOutputDescriptions();

      // generate the output
      COutputAssistant::createDefaultOutput(mGenerateOutput, task, model);
    }

    if (haveReportFile())
      task->getReport().setTarget(mReportFile);

    COptTask* optTask = dynamic_cast<COptTask*>(task);
    if (optTask != NULL)
    {
      COptProblem *problem = (COptProblem *)optTask->getProblem();
      if (mSetSolutionStatistic)
        optTask->setMethodType(CCopasiMethod::Statistics);
      if (isDisableRandomizeStartValues())
        problem->setRandomizeStartValues(false);
      if (isDisableStatistic())
        problem->setCalculateStatistics(false);

    }
  }

  model->saveModel(getFilename() + ".view.cps", NULL, true);
  return getFilename() + ".view.cps";
}
