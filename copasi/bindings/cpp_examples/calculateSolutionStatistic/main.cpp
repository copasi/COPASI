// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This examples reads a copasi file and changes an active
 * (i.e. scheduled) optimization or parameter estimation task, such that:
 *
 *   - randomize start values is disabled
 *   - update model is disabled
 *   - the active report target is unset (so that a previous report is
       overwritten)
 *   - current solution statistic is selected
 *   - a plot for the parameter estimation result is enabled.
 */

#include <iostream>
#include <string>

#define COPASI_MAIN

#include <copasi/CopasiTypes.h>

using namespace std;

/**
 * This method changes the given opt task (if it is scheduled)
 * such that:
 *  - update model is disabled
 *  - randomize start values is disabled
 *  - the method is set to current solution statistic
 */
void
changeTaskIfScheduled(COptTask* pTask)
{
  if (pTask == NULL || !pTask->isScheduled())
    return;

  cout << " ... updating: " << pTask->getObjectName() << endl;
  // no longer update the model
  pTask->setUpdateModel(false);
  // unset the report
  pTask->getReport().setTarget("");

  // disable randomize start values
  COptProblem* pFitProblem = dynamic_cast<COptProblem*>(pTask->getProblem());
  pFitProblem->setRandomizeStartValues(false);

  pTask->setMethodType(CTaskEnum::Method::Statistics);
}

/**
 * Utility function that looks through all plots in a model to see
 * whether a plot with a given name is already present
 */
bool
havePlotWithName(CDataModel* pDataModel, const std::string& name)
{
  if (pDataModel == NULL || name.empty())
    return false;

  COutputDefinitionVector& plots =
    *pDataModel->getPlotDefinitionList();
  COutputDefinitionVector::iterator it = plots.begin();
  COutputDefinitionVector::iterator end = plots.end();

  bool havePlot = false;

  for (; it != end; ++it)
    {
      if (it->getTitle() != name)
        continue;

      havePlot = true;
      break;
    }

  return havePlot;
}

/**
 * Utility function that adds a a parameter estimation result
 * plot, if it is not already present in the model
 */
void addParameterEstimationPlotIfNotPresent(CFitTask* pFitTask)
{
  if (pFitTask == NULL || pFitTask->getObjectDataModel() == NULL)
    return;

  CDataModel* pDataModel = pFitTask->getObjectDataModel();

  // check if we have a result plot already, if so do nothing
  if (havePlotWithName(pDataModel, "Parameter Estimation Result"))
    {
      cout << " ... parameter estimation result plot present already"
           << endl;
      return;
    }

  // create plot
  COutputAssistant::getListOfDefaultOutputDescriptions();
  cout << " ... added parameter estimation result plot" << endl;
  COutputAssistant::createDefaultOutput(910, pFitTask, pDataModel);
}

int main(int argc, char** argv)
{
  // initialize COPASI
  CRootContainer::init(0, NULL);

  // create a new data model
  CDataModel* pDataModel = CRootContainer::addDatamodel();

  // The function takes two arguments, an input and an output copasi file
  // if the COPASI file has not been given, then the input file will be
  // overwritten
  if (argc < 2)
    {
      std::cerr << "Usage: calculateSolutionStatistic <copasi file> [<output file>]" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string outputFile = argc > 2 ? argv[2] : argv[1];

  bool result = false;
  // load model
  cout << " ... Loading COPASI file" << endl;

  try
    {
      // load the model without progress report
      result = pDataModel->loadFromFile(filename);
    }
  catch (...)
    {
      cerr << "could not load the model. Error was: " << endl;
      cerr << CCopasiMessage::getAllMessageText();
      CRootContainer::destroy();
      return 2;
    }

  // get the optimization task
  COptTask* pOptTask = dynamic_cast<COptTask*>(&(*pDataModel->getTaskList())[CTaskEnum::TaskName[CTaskEnum::Task::optimization]]);
  changeTaskIfScheduled(pOptTask);

  // get the fitTask
  CFitTask* pFitTask = dynamic_cast<CFitTask*>(&(*pDataModel->getTaskList())[CTaskEnum::TaskName[CTaskEnum::Task::parameterFitting]]);

  changeTaskIfScheduled(pFitTask);

  // create plot for fit task if scheduled and not present
  if (pFitTask->isScheduled())
    addParameterEstimationPlotIfNotPresent(pFitTask);

  // save the file
  cout << " ... Saving COPASI file" << endl;
  pDataModel->saveModel(outputFile, NULL, true);

  // clean up the library
  CRootContainer::destroy();
}
