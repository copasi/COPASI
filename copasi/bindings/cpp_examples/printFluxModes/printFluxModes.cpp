// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This is an example on how to import a sedml file
 * and run it
 */

#include <iostream>
#include <string>

#define COPASI_MAIN

#include "copasi/copasi.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/elementaryFluxModes/CEFMTask.h"
#include "copasi/elementaryFluxModes/CEFMProblem.h"
#include "copasi/elementaryFluxModes/CEFMMethod.h"

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
      std::cerr << "Usage: printFluxModes <COPASI | SBML file>" << std::endl;
      CRootContainer::destroy();
      return 1;
    }

  std::string filename = argv[1];

  // read COPASI file if filename ends with .cps
  if (filename.find(".cps") != std::string::npos)
    {
      if (!pDataModel->loadFromFile(filename))
        {
          std::cerr << "couldn't open COPASI file: " << std::endl
                    << CCopasiMessage::getAllMessageText()
                    << std::endl;
          return 1;
        }
    }
  // otherwise read SBML file
  else
    {
      if (!pDataModel->importSBML(filename))
        {
          std::cerr << "couldn't open SBML file: " << std::endl
                    << CCopasiMessage::getAllMessageText()
                    << std::endl;
          return 1;
        }
    }

  // get EFM task
  CEFMTask* pTask = dynamic_cast<CEFMTask*>(&(*pDataModel->getTaskList())["Elementary Flux Modes"]);
  // mark as executable
  pTask->setScheduled(true);

  // initialize task
  if (!pTask->initialize(CCopasiTask::OutputFlag::OUTPUT_UI, NULL, NULL))
    {
      std::cerr << "couldn't initialize task " << std::endl
                << CCopasiMessage::getAllMessageText()
                << std::endl;
      return 1;
    }

  // run task
  if (!pTask->process(true))
    {
      std::cerr << "couldn't run task " << std::endl
                << CCopasiMessage::getAllMessageText()
                << std::endl;
      return 1;
    }

  // print results
  auto& modes = pTask->getFluxModes(); // get computed flux modes

  size_t numFluxModes = modes.size();
  std::cout << "Found " << numFluxModes << " flux modes" << std::endl;

  // instantiate a reaction interface that will be used to get the
  // reaction scheme from the reactions later on
  CReactionInterface tmp;

  // get hold of re-ordered reactions
  auto& reactions = dynamic_cast<CEFMProblem*>(pTask->getProblem())->getReorderedReactions();

  size_t count = 1;
  auto it = modes.begin();

  for (; it != modes.end(); ++it, ++count)
    {
      auto& current = *it;
      std::cout << "Mode " << count << ": " << (current.isReversible() ? "reversible" : "irreversible") << std::endl;

      std::stringstream reactionString;
      std::stringstream equationStream;

      auto curIt = current.begin();

      // construct reaction string and reaction scheme string
      for (; curIt != current.end(); ++curIt)
        {
          // get current re-ordered reaction
          auto& reaction = *reactions[curIt->first];

          // add multiplier * reaction identifier to reaction string
          reactionString << curIt->second << " * " << reaction.getObjectName() << ", ";

          // initialize reaction interface with reaction key
          tmp.init(reaction);

          // add reaction scheme to equation string
          equationStream << tmp.getChemEqString() << ", ";
        }

      std::cout << "Reactions: " << reactionString.str() << std::endl;
      std::cout << "ChemEqns: " << equationStream.str() << std::endl;

      std::cout << std::endl;
    }

  // clean up chem equation
  tmp.clearChemEquation();

  // clean up the library
  CRootContainer::destroy();
}
