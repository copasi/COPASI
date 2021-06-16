// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This examples demonstrates how to read in a copasi file, change its
 * parameters and run a parameter scan while changing the report filename
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define COPASI_MAIN

#include "copasi/CopasiTypes.h"

using namespace std;

int main(int argc, char** argv)
{
  // initialize the backend library
  CRootContainer::init(argc, argv);
  assert(CRootContainer::getRoot() != NULL);
  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(CRootContainer::getDatamodelList()->size() == 1);

  // the only argument to the main routine should be the name of an SBML file
  if (argc != 4)
    {
      std::cerr << "Usage: runScan <copasi file> <parameter set> <report name>" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string parameterSet = argv[2];
  std::string reportName = argv[3];

  bool result = false;

  try
    {
      // load the model without progress report
      result = pDataModel->loadFromFile(filename);
    }
  catch (...)
    {
    }

  if (!result)
    {
      std::cerr << "Error while opening the file named \"" << filename << "\"." << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  // changeParameters
  pDataModel->reparameterizeFromIniFile(parameterSet);

  // change the filename
  CScanTask* scanTask = dynamic_cast<CScanTask*>(&(*pDataModel->getTaskList())["Scan"]);
  scanTask->getReport().setTarget(reportName);

  scanTask->setScheduled(true);

  // save to ensure that the model is right
  pDataModel->saveModel("temp.cps", NULL, true);

  // run the task
  try
    {
      scanTask->initialize(CCopasiTask::OUTPUT_SE, pDataModel, NULL);
      scanTask->process(true);
    }
  catch (...)
    {
      std::cerr << "Error. Running the scan failed." << std::endl;

      // check if there are additional error messages
      if (CCopasiMessage::size() > 0)
        {
          // print the messages in chronological order
          std::cerr << CCopasiMessage::getAllMessageText(true);
        }

      CRootContainer::destroy();
      return 1;
    }

  // clean up the library
  CRootContainer::destroy();
  return 0;
}
