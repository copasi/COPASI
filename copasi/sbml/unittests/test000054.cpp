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

#include "test000054.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000054::pCOPASIDATAMODEL = NULL;

void test000054::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000054::tearDown()
{
  CRootContainer::destroy();
}

void test000054::test_bug1002()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000054::MODEL_STRING);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == false);
  SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumInitialAssignments() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 5);
  const Parameter* pParameter1 = pSBMLModel->getParameter(0);
  CPPUNIT_ASSERT(pParameter1 != NULL);
  CPPUNIT_ASSERT(pParameter1->getConstant() == false);
  const Parameter* pParameter2 = pSBMLModel->getParameter(1);
  CPPUNIT_ASSERT(pParameter2 != NULL);
  CPPUNIT_ASSERT(pParameter2->getConstant() == false);
  const Parameter* pParameter3 = pSBMLModel->getParameter(2);
  CPPUNIT_ASSERT(pParameter3 != NULL);
  CPPUNIT_ASSERT(pParameter3->getConstant() == false);
  const Parameter* pParameter4 = pSBMLModel->getParameter(3);
  CPPUNIT_ASSERT(pParameter4 != NULL);
  CPPUNIT_ASSERT(pParameter4->getConstant() == false);
  const Parameter* pParameter5 = pSBMLModel->getParameter(4);
  CPPUNIT_ASSERT(pParameter5 != NULL);
  CPPUNIT_ASSERT(pParameter5->getConstant() == false);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 5);

  const Rule* pRule = pSBMLModel->getRule(0);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  const AssignmentRule* pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter4->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  const ASTNode* pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_PLUS);
  CPPUNIT_ASSERT(pMath->getNumChildren() == 2);
  const ASTNode* pChild1 = pMath->getChild(0);
  CPPUNIT_ASSERT(pChild1 != NULL);
  CPPUNIT_ASSERT(pChild1->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild1->getReal() - 2.0) / 2.0) < 1e-15);
  const ASTNode* pChild2 = pMath->getChild(1);
  CPPUNIT_ASSERT(pChild2 != NULL);
  CPPUNIT_ASSERT(pChild2->getType() == AST_REAL);
  CPPUNIT_ASSERT(fabs((pChild2->getReal() - 4.0) / 4.0) < 1e-15);

  pRule = pSBMLModel->getRule(1);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter1->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter4->getId());
  CPPUNIT_ASSERT(pMath->getNumChildren() == 0);

  pRule = pSBMLModel->getRule(2);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter3->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter1->getId());
  CPPUNIT_ASSERT(pMath->getNumChildren() == 0);

  pRule = pSBMLModel->getRule(3);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter5->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter3->getId());
  CPPUNIT_ASSERT(pMath->getNumChildren() == 0);

  pRule = pSBMLModel->getRule(4);
  CPPUNIT_ASSERT(pRule != NULL);
  CPPUNIT_ASSERT(pRule->getTypeCode() == SBML_ASSIGNMENT_RULE);
  pARule = dynamic_cast<const AssignmentRule*>(pRule);
  CPPUNIT_ASSERT(pARule != NULL);
  CPPUNIT_ASSERT(pARule->getVariable() == pParameter2->getId());
  CPPUNIT_ASSERT(pARule->isSetMath() == true);
  pMath = pARule->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
  CPPUNIT_ASSERT(pMath->getName() == pParameter5->getId());
  CPPUNIT_ASSERT(pMath->getNumChildren() == 0);
}

const char* test000054::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.3.25 (Debug) (http://www.copasi.org) at 2008-03-08 18:49:47 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"25\">\n"
  "  <Model key=\"Model_1\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"A\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[D],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_1\" name=\"B\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[E],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_2\" name=\"C\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[A],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_3\" name=\"D\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          2+4\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "      <ModelValue key=\"ModelValue_4\" name=\"E\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          &lt;CN=Root,Model=New Model,Vector=Values[C],Reference=Value&gt;\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_2\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_3\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_4\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 NaN NaN NaN 3 7\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
  ;
