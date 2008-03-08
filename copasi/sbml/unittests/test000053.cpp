// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000053.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/08 19:38:09 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000053.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

void test000053::setUp()
{
  // Create the root container.
  CCopasiContainer::init();

  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel();
}

void test000053::tearDown()
{
  delete CCopasiDataModel::Global;
  CCopasiDataModel::Global = NULL;
  delete CCopasiContainer::Root;
  CCopasiContainer::Root = NULL;
}

void test000053::test1_bug1000()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = CCopasiDataModel::Global;
  std::istringstream iss(test000053::MODEL_STRING_1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // assert that there is only one compartment and
  // assert the compartment is constant
  CPPUNIT_ASSERT(pModel->getNumCompartments() == 1);
  Compartment* pCompartment = pModel->getCompartment(0);
  CPPUNIT_ASSERT(pCompartment->getConstant() == true);
  CPPUNIT_ASSERT(pModel->getNumParameters() == 0);
  CPPUNIT_ASSERT(pModel->getNumSpecies() == 1);
  const Species* pSpecies = pModel->getSpecies(0);
  std::string idSpeciesA = pSpecies->getId();
  CPPUNIT_ASSERT(pSpecies->getHasOnlySubstanceUnits() == false);
  CPPUNIT_ASSERT(pModel->getNumRules() == 1);
  AssignmentRule* pRule = dynamic_cast<AssignmentRule*>(pModel->getRule(0));
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getVariable() == idSpeciesA);
  const ASTNode* pMath = pRule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // make sure the mathematical expression contains a piecewise
  // function definition
  CPPUNIT_ASSERT(pMath->getType() == AST_FUNCTION_PIECEWISE);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 3);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getChild(0)->getReal() - 0.5) / 0.5) < 1e-6);
  CPPUNIT_ASSERT(pMath->getChild(2) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(2)->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getChild(2)->getReal() - 1.5) / 1.5) < 1e-6);
  pMath = pMath->getChild(1);
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_RELATIONAL_GT);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getChild(1)->getReal() - 3.0) / 3.0) < 1e-6);
  CPPUNIT_ASSERT(pMath->getChild(1) != NULL);
  CPPUNIT_ASSERT(pMath->getChild(1)->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pMath->getChild(1)->getReal() - 4.0) / 4.0) < 1e-6);
  CPPUNIT_ASSERT(pModel->getNumReactions() == 0);
}

const char* test000053::MODEL_STRING_1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <gt/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <otherwise>\n"
  "              <cn> 1.5 </cn>\n"
  "            </otherwise>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;

const char* test000053::MODEL_STRING_2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;

const char* test000053::MODEL_STRING_3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <gt/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;

const char* test000053::MODEL_STRING_4 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "            <otherwise>\n"
  "              <cn> 1.5 </cn>\n"
  "            </otherwise>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;

const char* test000053::MODEL_STRING_5 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\" boundaryCondition=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"species_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <piecewise>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <ge/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <gt/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <le/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <piece>\n"
  "              <cn> 0.5 </cn>\n"
  "              <apply>\n"
  "                <eq/>\n"
  "                <cn> 3 </cn>\n"
  "                <cn> 4 </cn>\n"
  "              </apply>\n"
  "            </piece>\n"
  "            <otherwise>\n"
  "              <cn> 1.5 </cn>\n"
  "            </otherwise>\n"
  "          </piecewise>\n"
  "        </math>\n"
  "      </assignmentRule>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
;
