// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This examples reads a copasi file, assigns a parameter set with given name
 * and saves the resulting document.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#define COPASI_MAIN

#include <copasi/CopasiTypes.h>

#include <sstream>
#include <fstream>

using namespace std;

bool applyParameterSetByName(CDataModel* pDataModel, std::string parameterSet)
{
  // obtain parameter set
  CDataVectorN< CModelParameterSet > & sets = pDataModel->getModel()->getModelParameterSets();
  CDataVectorN< CModelParameterSet >::iterator it = sets.begin();

  for (; it != sets.end(); ++it)
    {
      if (it->getName() == parameterSet)
        {
          it->updateModel();
          return true;
        }
    }

  return false;
}

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
      std::cerr << "Usage: assignParameterSet <input copasi file> <parameter set> <output copasi file>" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string parameterSet = argv[2];
  std::string outputFile = argv[3];

  cout << "assignParameterSet invoked with: " << endl
       << " model: " << filename << endl
       << " parameter set: " << parameterSet << endl
       << " output: " << outputFile << endl
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

  bool assigned = applyParameterSetByName(pDataModel, parameterSet);

  // write the result
  if (assigned)
    {
      cout << "Saving COPASI file ... " << endl;
      pDataModel->saveModel(outputFile, NULL, true);
    }
  else
    {
      cout << "No parameter set with name '" << parameterSet << "'" << endl;
    }

  // clean up the library
  CRootContainer::destroy();
}
