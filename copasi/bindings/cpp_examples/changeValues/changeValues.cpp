// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This reads a copasi file and a parameter file, assigns those parameters
 * and writes them into a new COPASI file
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define COPASI_MAIN

#include "copasi/CopasiTypes.h"

using namespace std;

/**
 * This function will read in reaction parameters in the form
 *
 *   reaction_id parameterId value
 *
 * and will reparameterize the model with those values
 */
void changeParameters(CDataModel* pDataModel, const std::string& parameterSet)
{
  ifstream ifs(parameterSet.c_str(), std::ios_base::in);

  if (!ifs.good())
    {
      cerr << "Couldn't open file with parameters" << endl;
      exit(1);
    }

  auto& reactions = pDataModel->getModel()->getReactions();

  while (ifs.good())
    {
      string reactionId; string parameterId; double value;
      ifs >> reactionId >> parameterId >> value;

      if (reactionId.empty() || parameterId.empty()) break;

      // find model value ... change value
      try
        {
          reactions[reactionId].setParameterValue(parameterId, value);
          reactions[reactionId].compile();
          pDataModel->getModel()->setCompileFlag();
        }
      catch (...)
        {
          cerr << "Couldn't change parameter '" << reactionId << "." << parameterId << "'." << endl;
          exit(1);
        }
    }

  pDataModel->getModel()->compileIfNecessary(NULL);
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
      std::cerr << "Usage: changeValues <copasi file> <parameter set> <output copasi file>" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string parameterSet = argv[2];
  std::string oututFile = argv[3];

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
  changeParameters(pDataModel, parameterSet);

  // save to output file
  pDataModel->saveModel(oututFile, NULL, true);

  // clean up the library
  CRootContainer::destroy();
  return 0;
}
