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

#include "test000021.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CExpression.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000021::pCOPASIDATAMODEL = NULL;

void test000021::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000021::tearDown()
{
  CRootContainer::destroy();
}

void test000021::test_hasOnlySubstanceUnits()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::Status::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::Status::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::Status::ASSIGNMENT);
  const CExpression* pExpr = pModelValue->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCommonName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  CObjectInterface::ContainerList listOfContainers;
  listOfContainers.push_back(pModel);
  const CDataObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->getObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->hasFlag(CDataObject::Reference) == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("Concentration"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pA);

  CPPUNIT_ASSERT(pModel->getReactions().size() == 2);
  const CReaction* pReaction1 = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction1 != NULL);
  CPPUNIT_ASSERT(pReaction1->isReversible() == false);
  // check the kinetic law
  const CFunction* pKineticFunction = pReaction1->getFunction();
  CPPUNIT_ASSERT(pKineticFunction != NULL);
  const CMassAction* pMassAction = dynamic_cast<const CMassAction*>(pKineticFunction);
  CPPUNIT_ASSERT(pMassAction != NULL);
  const CChemEq* pChemEq = &pReaction1->getChemEq();
  CPPUNIT_ASSERT(pChemEq != NULL);
  CPPUNIT_ASSERT(pChemEq->getCompartmentNumber() == 1);
  CPPUNIT_ASSERT(pChemEq->getSubstrates().size() == 1);
  const CChemEqElement* pElement = pChemEq->getSubstrates()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pA);
  CPPUNIT_ASSERT(pChemEq->getProducts().size() == 0);
  CPPUNIT_ASSERT(pChemEq->getModifiers().size() == 0);

  const CReaction* pReaction2 = pModel->getReactions()[1];
  CPPUNIT_ASSERT(pReaction2 != NULL);
  CPPUNIT_ASSERT(pReaction2->isReversible() == false);
  // check the kinetic law
  pKineticFunction = pReaction2->getFunction();
  CPPUNIT_ASSERT(pKineticFunction != NULL);
  CPPUNIT_ASSERT(pKineticFunction->getObjectName() == std::string("Henri-Michaelis-Menten (irreversible)"));
  // check the function parameters one should be the reference to the substrate
  pChemEq = &pReaction2->getChemEq();
  CPPUNIT_ASSERT(pChemEq != NULL);
  CPPUNIT_ASSERT(pChemEq->getCompartmentNumber() == 1);
  CPPUNIT_ASSERT(pChemEq->getSubstrates().size() == 1);
  pElement = pChemEq->getSubstrates()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pA);
  CPPUNIT_ASSERT(pChemEq->getProducts().size() == 1);
  pElement = pChemEq->getProducts()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pB);
  CPPUNIT_ASSERT(pChemEq->getModifiers().size() == 0);
  const std::vector<std::vector<std::string> > parameterMappings = pReaction2->getParameterMappings();
  CPPUNIT_ASSERT(parameterMappings.size() == 3);
  CPPUNIT_ASSERT(parameterMappings[0].size() == 1);
  const std::string parameterKey = parameterMappings[0][0];
  CPPUNIT_ASSERT(parameterKey == pA->getKey());
}

const char* test000021::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>Model with fixed compartment volume, two species with hasOnlySubstanceUnits flag set to false. The units are set to ml and mMol. There is an assignment ruile for the global parameter that contains a reference to species A.</p>"
  "        <p>The imported model should contain an assignment for the global parameter that consists of the reference to species A. The species references in the reactions should be imported unmodified.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfFunctionDefinitions>"
  "      <functionDefinition id=\"function_1\" name=\"Henri-Michaelis-Menten (irreversible)\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <lambda>"
  "            <bvar>"
  "              <ci> substrate </ci>"
  "            </bvar>"
  "            <bvar>"
  "              <ci> Km </ci>"
  "            </bvar>"
  "            <bvar>"
  "              <ci> V </ci>"
  "            </bvar>"
  "            <apply>"
  "              <divide/>"
  "              <apply>"
  "                <times/>"
  "                <ci> V </ci>"
  "                <ci> substrate </ci>"
  "              </apply>"
  "              <apply>"
  "                <plus/>"
  "                <ci> Km </ci>"
  "                <ci> substrate </ci>"
  "              </apply>"
  "            </apply>"
  "          </lambda>"
  "        </math>"
  "      </functionDefinition>"
  "    </listOfFunctionDefinitions>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"volume\">"
  "        <listOfUnits>"
  "          <unit kind=\"litre\" scale=\"-3\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "      <unitDefinition id=\"substance\">"
  "        <listOfUnits>"
  "          <unit kind=\"mole\" scale=\"-3\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>"
  "    </listOfCompartments>"
  "    <listOfSpecies>"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialConcentration=\"1\"/>"
  "    </listOfSpecies>"
  "    <listOfParameters>"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>"
  "    </listOfParameters>"
  "    <listOfRules>"
  "      <assignmentRule variable=\"parameter_1\">"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "          <ci> species_1 </ci>"
  "        </math>"
  "      </assignmentRule>"
  "    </listOfRules>"
  "    <listOfReactions>"
  "      <reaction id=\"reaction_1\" name=\"reaction_0\" reversible=\"false\">"
  "        <listOfReactants>"
  "          <speciesReference species=\"species_1\"/>"
  "        </listOfReactants>"
  "        <kineticLaw>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <times/>"
  "              <ci> compartment_1 </ci>"
  "              <ci> k1 </ci>"
  "              <ci> species_1 </ci>"
  "            </apply>"
  "          </math>"
  "          <listOfParameters>"
  "            <parameter id=\"k1\" value=\"0.1\"/>"
  "          </listOfParameters>"
  "        </kineticLaw>"
  "      </reaction>"
  "      <reaction id=\"reaction_2\" name=\"reaction_1\" reversible=\"false\">"
  "        <listOfReactants>"
  "          <speciesReference species=\"species_1\"/>"
  "        </listOfReactants>"
  "        <listOfProducts>"
  "          <speciesReference species=\"species_2\"/>"
  "        </listOfProducts>"
  "        <kineticLaw>"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
  "            <apply>"
  "              <times/>"
  "              <ci> compartment_1 </ci>"
  "              <apply>"
  "                <ci> function_1 </ci>"
  "                <ci> species_1 </ci>"
  "                <ci> Km </ci>"
  "                <ci> V </ci>"
  "              </apply>"
  "            </apply>"
  "          </math>"
  "          <listOfParameters>"
  "            <parameter id=\"Km\" value=\"0.1\"/>"
  "            <parameter id=\"V\" value=\"0.1\"/>"
  "          </listOfParameters>"
  "        </kineticLaw>"
  "      </reaction>"
  "    </listOfReactions>"
  "  </model>"
  "</sbml>"
  ;
