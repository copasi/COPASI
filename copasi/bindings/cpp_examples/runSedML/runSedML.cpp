// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * This is an example on how to import a sedml file
 * and run it
 */

#include <iostream>
#include <string>

#define COPASI_MAIN

#include "copasi/copasi.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/report/CReport.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/trajectory/CTimeSeries.h"
#include "copasi/function/CFunctionDB.h"

int runTaskIfScheduled(CCopasiTask* pTask, const std::string& outdir)
{
  if (pTask == NULL ||
      !pTask->isScheduled() ||
      pTask->getReport().getTarget().empty())
    return 1;

  // found a time course task with report
  // run it
  try
    {
      pTask->getReport().setTarget(outdir + "/" + pTask->getReport().getTarget());
      pTask->initialize(CCopasiTask::OUTPUT_UI, pTask->getObjectDataModel(), NULL);
      pTask->process(true);
    }
  catch (...)
    {
      std::cerr << "Error. Running the simulation failed." << std::endl;

      // check if there are additional error messages
      if (CCopasiMessage::size() > 0)
        {
          // print the messages in chronological order
          std::cerr << CCopasiMessage::getAllMessageText(true);
        }

      CCopasiRootContainer::destroy();
      return 1;
    }

  return 0;
}

int main(int argc, char** argv)
{
  // initialize the backend library
  CCopasiRootContainer::init(argc, argv);
  assert(CCopasiRootContainer::getRoot() != NULL);
  // create a new datamodel
  CCopasiDataModel* pDataModel = CCopasiRootContainer::addDatamodel();
  assert(CCopasiRootContainer::getDatamodelList()->size() == 1);

  // the only argument to the main routine should be the name of an SBML file
  if (argc != 3)
    {
      std::cerr << "Usage: runSedML <SED-ML file> <outdir>" << std::endl;
      CCopasiRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string outDir = argv[2];

  try
    {
      // load the model without progress report
      pDataModel->importSEDML(filename, NULL);
    }
  catch (...)
    {
      std::cerr << "Error while importing the Simulation experiment from file named \"" << filename << "\"." << std::endl;
      CCopasiRootContainer::destroy();
      return 1;
    }

  // get the task list
  CCopasiVectorN< CCopasiTask > & TaskList = * pDataModel->getTaskList();

  // run supported tasks, when scheduled
  runTaskIfScheduled(TaskList["Time-Course"], outDir);
  runTaskIfScheduled(TaskList["Scan"], outDir);

  // clean up the library
  CCopasiRootContainer::destroy();
}
