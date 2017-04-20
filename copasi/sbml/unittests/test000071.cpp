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

#include "test000071.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeVariable.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/FunctionDefinition.h"
#include "sbml/math/ASTNode.h"

#include "copasi/core/CRootContainer.h"

/**
 * This test checks if the workaround for bug 1085 works.
 * Or once libSBML has been fixed, it checks that the bug no longer occurs.
 */
CDataModel* test000071::pCOPASIDATAMODEL = NULL;

void test000071::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000071::tearDown()
{
  CRootContainer::destroy();
}

void test000071::test_bug1085()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000071::MODEL_STRING1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  std::string sbmlString = pDataModel->exportSBMLToString(NULL, 2, 1);
  CPPUNIT_ASSERT(!sbmlString.empty());
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(sbmlString));
  pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  // check if there is one function defintition
  CPPUNIT_ASSERT(pSBMLModel->getListOfFunctionDefinitions()->size() == 1);
  const FunctionDefinition* pFunDef = pSBMLModel->getFunctionDefinition(0);
  CPPUNIT_ASSERT(pFunDef != NULL);
  CPPUNIT_ASSERT(pFunDef->getName() == "sqrt_call");
  const ASTNode* pMath = pFunDef->getMath();
  CPPUNIT_ASSERT(pMath != NULL);
  // the last child should be the actual function expression
  pMath = pMath->getChild(pMath->getNumChildren() - 1);
  CPPUNIT_ASSERT(pMath != NULL);
  // check that the root node is a root function call
  CPPUNIT_ASSERT(pMath->getType() == AST_FUNCTION_ROOT);
  // the root function can have either one or two arguments
  // if there are two arguments the first one is the degree and needs to be 2
  // since we have a sqrt call
  CPPUNIT_ASSERT(pMath->getNumChildren() == 1 || pMath->getNumChildren() == 2);

  if (pMath->getNumChildren() == 2)
    {
      CPPUNIT_ASSERT(pMath->getChild(0) != NULL);
      CPPUNIT_ASSERT(pMath->getChild(0)->getType() == AST_INTEGER);
      CPPUNIT_ASSERT(pMath->getChild(0)->getInteger() == 2);
      pMath = pMath->getChild(1);
      CPPUNIT_ASSERT(pMath != NULL);
      CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getName() == std::string("k"));
    }
  else if (pMath->getNumChildren() == 1)
    {
      pMath = pMath->getChild(0);
      CPPUNIT_ASSERT(pMath != NULL);
      CPPUNIT_ASSERT(pMath->getType() == AST_NAME);
      CPPUNIT_ASSERT(pMath->getName() == std::string("k"));
    }
}

const char* test000071::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.4.27 (Debug) (http://www.copasi.org) at 2008-09-27 14:44:36 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"27\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_47\" name=\"sqrt_call\" type=\"UserDefined\" reversible=\"unspecified\">\n"
  "      <Expression>\n"
  "        sqrt(k)\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_243\" name=\"k\" order=\"0\" role=\"constant\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "  </ListOfFunctions>\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"P\" simulationType=\"assignment\">\n"
  "        <Expression>\n"
  "          sqrt_call(4)\n"
  "        </Expression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 0\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
  ;
