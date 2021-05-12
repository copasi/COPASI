// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"

int main(int argc, char** argv)
{
  // initialize the backend library
  CRootContainer::init(argc, argv);
  assert(CRootContainer::getRoot() != NULL);
  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(CRootContainer::getDatamodelList()->size() == 1);

  // the only argument to the main routine should be the name of a CPS file
  if (argc == 2)
    {
      std::string filename = argv[1];

      try
        {
          // load the model without progress report
          pDataModel->loadFromFile(filename);
        }
      catch (...)
        {
          std::cerr << "Error while loading the model from file named \"" << filename << "\"." << std::endl;
          CRootContainer::destroy();
          return 1;
        }

      CModel* pModel = pDataModel->getModel();
      assert(pModel != NULL);
      std::cout << "Model statistics for model \"" << pModel->getObjectName() << "\"." << std::endl;

      // output number and names of all compartments
      size_t i, iMax = pModel->getCompartments().size();
      std::cout << "Number of Compartments: " << iMax << std::endl;
      std::cout << "Compartments: " << std::endl;

      for (i = 0; i < iMax; ++i)
        {
          CCompartment* pCompartment = &pModel->getCompartments()[i];
          assert(pCompartment != NULL);
          std::cout << "\t" << pCompartment->getObjectName() << std::endl;
        }

      // output number and names of all metabolites
      iMax = pModel->getMetabolites().size();
      std::cout << "Number of Metabolites: " << iMax << std::endl;
      std::cout << "Metabolites: " << std::endl;

      for (i = 0; i < iMax; ++i)
        {
          CMetab* pMetab = &pModel->getMetabolites()[i];
          assert(pMetab != NULL);
          std::cout << "\t" << pMetab->getObjectName() << std::endl;
        }

      // output number and names of all reactions
      iMax = pModel->getReactions().size();
      std::cout << "Number of Reactions: " << iMax << std::endl;
      std::cout << "Reactions: " << std::endl;

      for (i = 0; i < iMax; ++i)
        {
          CReaction* pReaction = &pModel->getReactions()[i];
          assert(pReaction != NULL);
          std::cout << "\t" << pReaction->getObjectName() << std::endl;
        }
    }
  else
    {
      std::cerr << "Usage: example2 CPSFILE" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  // clean up the library
  CRootContainer::destroy();
}
