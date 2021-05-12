// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CDataVector.h"

int main(int argc, char** argv)
{
  // initialize the backend library
  CRootContainer::init(argc, argv);
  assert(CRootContainer::getRoot() != NULL);
  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(CRootContainer::getDatamodelList()->size() == 1);

  // the only argument to the main routine should be the name of an SBML file
  if (argc != 3)
    {
      std::cerr << "Usage: exportSedML <copasi file> <sedML file>" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];
  std::string sedmlFile = argv[2];
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

  // export the file
  pDataModel->exportSEDML(sedmlFile, true, 1, 2, true, true, NULL);

  // clean up the library
  CRootContainer::destroy();
}
