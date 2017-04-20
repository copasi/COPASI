// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "test000080.h"

#include "utilities.hpp"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CReaction.h"

/**
 * This is a test for a bug where some kinetics were wrongly recognized as
 * mass action.
 * This kind of kinetic is used in the sbml testsuite in test 65, 121, 250,
 * 253, 256 and 600.
 */
CDataModel* test000080::pCOPASIDATAMODEL = NULL;

void test000080::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000080::tearDown()
{
  CRootContainer::destroy();
}

void test000080::test_mass_action_recognition_bug()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;

  try
    {
      CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000080::MODEL_STRING1));
    }
  catch (...)
    {
      // there should not be an exception
      CPPUNIT_ASSERT(false);
    }

  const CModel* pModel = pDataModel->getModel();

  CPPUNIT_ASSERT(pModel != NULL);

  CPPUNIT_ASSERT(pModel->getReactions().size() == 1);

  const CReaction* pReaction = pModel->getReactions()[0];

  CPPUNIT_ASSERT(pReaction != NULL);

  const CFunction* pFun = pReaction->getFunction();

  CPPUNIT_ASSERT(pFun != NULL);

  CPPUNIT_ASSERT(pFun->getType() == CEvaluationTree::UserDefined);
}

const char* test000080::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"model_1\" name=\"Model_1\">\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment\" name=\"compartment\" size=\"1\" units=\"volume\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"S1\" name=\"S1\" compartment=\"compartment\" initialAmount=\"1\" substanceUnits=\"substance\"/>\n"
  "      <species id=\"S2\" name=\"S2\" compartment=\"compartment\" initialAmount=\"1\" substanceUnits=\"substance\"/>\n"
  "      <species id=\"S3\" name=\"S3\" compartment=\"compartment\" initialAmount=\"1\" substanceUnits=\"substance\"/>\n"
  "      <species id=\"S4\" name=\"S4\" compartment=\"compartment\" initialAmount=\"1\" substanceUnits=\"substance\"/>\n"
  "      <species id=\"S5\" name=\"S5\" compartment=\"compartment\" initialAmount=\"1\" substanceUnits=\"substance\" constant=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter id=\"k1\" name=\"k1\" value=\"1\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction1\" name=\"reaction1\" reversible=\"false\" fast=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"S1\"/>\n"
  "          <speciesReference species=\"S2\"/>\n"
  "        </listOfReactants>\n"
  "        <listOfProducts>\n"
  "          <speciesReference species=\"S3\"/>\n"
  "          <speciesReference species=\"S4\"/>\n"
  "        </listOfProducts>\n"
  "        <listOfModifiers>\n"
  "          <modifierSpeciesReference species=\"S5\"/>\n"
  "        </listOfModifiers>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> compartment </ci>\n"
  "              <ci> k1 </ci>\n"
  "              <ci> S1 </ci>\n"
  "              <ci> S2 </ci>\n"
  "              <apply>\n"
  "                <power/>\n"
  "                <ci> S5 </ci>\n"
  "                <cn type=\"integer\"> -1 </cn>\n"
  "              </apply>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n";
