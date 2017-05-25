// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000060.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CFunctionDB.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Species.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000060::pCOPASIDATAMODEL = NULL;

void test000060::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000060::tearDown()
{
  CRootContainer::destroy();
}

void test000060::test_bug_1026()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000060::MODEL_STRING1));
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 0);
  // check if the species is constant and has boundaryCondition set to true
  const Species* pSpecies = pSBMLModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies != NULL);
  CPPUNIT_ASSERT(pSpecies->getConstant() == true);
  CPPUNIT_ASSERT(pSpecies->getBoundaryCondition() == true);
  // now change the status of the species in the underlying COPASI model
  CPPUNIT_ASSERT(pDataModel->getModel()->getMetabolites().size() == 1);
  CMetab* pMetab = pDataModel->getModel()->getMetabolites()[0];
  pMetab->setStatus(CModelEntity::Status::REACTIONS);
  std::set<const CDataObject*> changedObjects;
  changedObjects.insert(pMetab);
  std::vector<Refresh*> refreshes = pDataModel->getModel()->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 0);
  // check if the species is constant and has boundaryCondition set to false
  pSpecies = pSBMLModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies != NULL);
  CPPUNIT_ASSERT(pSpecies->getConstant() == false);
  CPPUNIT_ASSERT(pSpecies->getBoundaryCondition() == false);
}

const char* test000060::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" metaid=\"_000000\" level=\"2\" version=\"1\">\n"
  "  <model metaid=\"_000001\" id=\"bug_1026\" name=\"bug_1026\">\n"
  "    <listOfCompartments>\n"
  "      <compartment metaid=\"_000005\" id=\"compartment_1\" name=\"compartment_1\" size=\"1e-16\">\n"
  "      </compartment>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species metaid=\"_000006\" id=\"species_1\" name=\"species_1\" compartment=\"compartment_1\" initialAmount=\"1.0\" constant=\"true\" boundaryCondition=\"true\" />\n"
  "    </listOfSpecies>  \n"
  "  </model>\n"
  "</sbml>\n"
  ;
