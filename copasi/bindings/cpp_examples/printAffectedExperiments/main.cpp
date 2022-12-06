// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This examples reads a copasi file and prints for the parameter estimation
 * for each fit item the experiments it is applied to.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#define COPASI_MAIN

#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiTask.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include <copasi/parameterFitting/CFitTask.h>
#include <copasi/parameterFitting/CFitProblem.h>
#include <copasi/parameterFitting/CFitItem.h>
#include <copasi/optimization/COptItem.h>

//// uncomment to test for memory leaks in visual studio
//// (uses visual leak detector)
//#include <vld.h>

#include <sstream>
#include <fstream>

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
  if (argc != 2)
    {
      std::cerr << "Usage: printAffectedExperiments <copasi file>" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];

  cout << "printAffectedExperiments invoked with: " << endl
       << " model: " << filename << endl
       << endl;

  bool result = false;
  // load model
  cout << "Loading COPASI file ... " << endl;

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

  // get the fitTask
  CFitTask* pFitTask = dynamic_cast<CFitTask*>(&(*pDataModel->getTaskList())[CTaskEnum::TaskName[CTaskEnum::Task::parameterFitting]]);

  if (pFitTask == NULL)
    {
      cerr << "No parameter fitting task defined, quitting" << endl;
      CRootContainer::destroy();
      return 2;
    }

  CFitProblem* pFitProblem = dynamic_cast<CFitProblem*>(pFitTask->getProblem());

  size_t numFitItems = pFitProblem->getOptItemSize();
  cout << "Number of fit items: " << numFitItems << endl << endl;

  for (size_t i = 0; i < numFitItems; ++i)
    {
      CFitItem* pFitItem = dynamic_cast<CFitItem*>(&pFitProblem->getOptItem(i));
      cout << "parameter: " << pFitItem->getObjectCN() << " is affected by: " << endl;

      size_t numAffected = pFitItem->getExperimentCount();

      if (numAffected == 0)
        {
          cout << "\tall experiments" << endl;
        }

      for (size_t j = 0; j < numAffected; ++j)
        {
          cout << "\t" << pFitItem->getExperiment(j) << endl;
        }

      cout << endl;
    }

  // clean up the library
  CRootContainer::destroy();
}
