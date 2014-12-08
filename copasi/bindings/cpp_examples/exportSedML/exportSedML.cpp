// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * This is an example on how to export a COPASI file as SED-ML
 */

#include <iostream>
#include <string>

#define COPASI_MAIN

#include "copasi/copasi.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"

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
      std::cerr << "Usage: exportSedML <copasi file> <sedML file>" << std::endl;
      CCopasiRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string sedmlFile = argv[2];
  bool result = false;

  try
    {
      // load the model without progress report
      result = pDataModel->loadModel(filename, NULL);
    }
  catch (...)
    {
    }

  if (!result)
    {
      std::cerr << "Error while opening the file named \"" << filename << "\"." << std::endl;
      CCopasiRootContainer::destroy();
      return 1;
    }

  // export the file
  pDataModel->exportSEDML(sedmlFile, true, 1, 2, true, true, NULL);

  // clean up the library
  CCopasiRootContainer::destroy();
}
