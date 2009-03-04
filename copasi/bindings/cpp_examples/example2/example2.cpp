// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/cpp_examples/example2/example2.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/03/04 08:16:15 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/**
 * This is an example on how to load a cps file
 * and output some information on the model
 */

#include <iostream>
#include <string>

#define COPASI_MAIN

#include "copasi/copasi.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"

int main(int argc, char** argv)
{
  // initialize the backend library
  CCopasiRootContainer::init(argc, argv);
  assert(CCopasiRootContainer::getRoot() != NULL);
  // create a new datamodel
  CCopasiDataModel* pDataModel = CCopasiRootContainer::addDatamodel();
  assert(CCopasiRootContainer::getDatamodelList()->size() == 1);
  // the only argument to the main routine should be the name of a CPS file
  if (argc == 2)
    {
      std::string filename = argv[1];
      try
        {
          // load the model without progress report
          pDataModel->loadModel(filename, NULL);
        }
      catch (...)
        {
          std::cerr << "Error while loading the model from file named \"" << filename << "\"." << std::endl;
          CCopasiRootContainer::destroy();
          return 1;
        }
      CModel* pModel = pDataModel->getModel();
      assert(pModel != NULL);
      std::cout << "Model statistics for model \"" << pModel->getObjectName() << "\"." << std::endl;

      // output number and names of all compartments
      unsigned int i, iMax = pModel->getCompartments().size();
      std::cout << "Number of Compartments: " << iMax << std::endl;
      std::cout << "Compartments: " << std::endl;
      for (i = 0;i < iMax;++i)
        {
          CCompartment* pCompartment = pModel->getCompartments()[i];
          assert(pCompartment != NULL);
          std::cout << "\t" << pCompartment->getObjectName() << std::endl;
        }

      // output number and names of all metabolites
      iMax = pModel->getMetabolites().size();
      std::cout << "Number of Metabolites: " << iMax << std::endl;
      std::cout << "Metabolites: " << std::endl;
      for (i = 0;i < iMax;++i)
        {
          CMetab* pMetab = pModel->getMetabolites()[i];
          assert(pMetab != NULL);
          std::cout << "\t" << pMetab->getObjectName() << std::endl;
        }

      // output number and names of all reactions
      iMax = pModel->getReactions().size();
      std::cout << "Number of Reactions: " << iMax << std::endl;
      std::cout << "Reactions: " << std::endl;
      for (i = 0;i < iMax;++i)
        {
          CReaction* pReaction = pModel->getReactions()[i];
          assert(pReaction != NULL);
          std::cout << "\t" << pReaction->getObjectName() << std::endl;
        }
    }
  else
    {
      std::cerr << "Usage: example2 CPSFILE" << std::endl;
      CCopasiRootContainer::destroy();
      return 1;
    }

  // clean up the library
  CCopasiRootContainer::destroy();
}
