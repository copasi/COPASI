// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000089.h"

#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/core/CRootContainer.h"

#include <sbml/SBMLDocument.h>
#include <sbml/Model.h>
#include <sbml/Species.h>
#include <sbml/Parameter.h>
#include <sbml/Rule.h>
#include <sbml/math/ASTNode.h>

// test for bug1412

CDataModel* test000089::pCOPASIDATAMODEL = NULL;

void test000089::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000089::tearDown()
{
  CRootContainer::destroy();
}

void test000089::test_bug1412()
{
  try
    {
      std::istringstream iss(test000089::MODEL_STRING1);
      bool result = load_cps_model_from_stream(iss, *pCOPASIDATAMODEL);
      CPPUNIT_ASSERT(result == true);
      CPPUNIT_ASSERT(pCOPASIDATAMODEL->getModel() != NULL);
    }
  catch (...)
    {
      // there should be no exception
      CPPUNIT_ASSERT(false);
    }

  try
    {
      CPPUNIT_ASSERT(pCOPASIDATAMODEL->exportSBMLToString(NULL, 2, 3).empty() == false);
    }
  catch (...)
    {
      // there should be no exception
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(CCopasiMessage::size() == 0);
  const SBMLDocument* pDocument = pCOPASIDATAMODEL->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  CPPUNIT_ASSERT(pDocument->getLevel() == 2);
  CPPUNIT_ASSERT(pDocument->getVersion() == 3);
  const Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getListOfFunctionDefinitions()->size() == 0);
  CPPUNIT_ASSERT(pModel->getListOfCompartments()->size() == 1);
  CPPUNIT_ASSERT(pModel->getListOfSpecies()->size() == 1);
  CPPUNIT_ASSERT(pModel->getListOfParameters()->size() == 1);
  CPPUNIT_ASSERT(pModel->getListOfReactions()->size() == 0);
  CPPUNIT_ASSERT(pModel->getListOfRules()->size() == 1);
  const Rule* pRule = pModel->getRule(0);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  const AssignmentRule* pAssignmentRule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pAssignmentRule != NULL);
  const Species* pSpecies = pModel->getSpecies(0);
  CPPUNIT_ASSERT(pSpecies != NULL);
  CPPUNIT_ASSERT(pSpecies->getName() == "M");
  const Parameter* pParameter = pModel->getParameter(pAssignmentRule->getVariable());
  CPPUNIT_ASSERT(pParameter != NULL);
  CPPUNIT_ASSERT(pParameter->getName() == "MV");
  const ASTNode* pMath = pAssignmentRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_DIVIDE);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs(pChild->getReal() - 1.0) < 1e-6);
  pChild = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getType() == AST_NAME);
  CPPUNIT_ASSERT(pChild->getName() == pSpecies->getId());
}

const char* test000089::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.5.31 (development) (http://www.copasi.org) at 2010-03-01 08:59:11 UTC -->\n"
  "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
  "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"31\">\n"
  "  <Model key=\"Model_1\" name=\"Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"l\" areaUnit=\"µm²\" lengthUnit=\"m\" quantityUnit=\"#\" type=\"deterministic\">\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_1\" name=\"C\" simulationType=\"fixed\" dimensionality=\"3\" />\n"
  "    </ListOfCompartments> \n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_1\" name=\"M\" simulationType=\"fixed\" compartment=\"Compartment_1\" />\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_1\" name=\"MV\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          1/&lt;CN=Root,Model=Model,Vector=Compartments[C],Vector=Metabolites[M],Reference=Concentration&gt;\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_1\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1 2 3 \n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n";
