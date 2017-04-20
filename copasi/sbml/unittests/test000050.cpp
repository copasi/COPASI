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

#include "test000050.h"

#include <sstream>
#include "utilities.hpp"

#include <sbml/SBMLDocument.h>
#include <sbml/Model.h>
#include <sbml/Rule.h>
#include <sbml/Species.h>
#include <sbml/FunctionDefinition.h>
#include <sbml/Parameter.h>
#include <sbml/math/ASTNode.h>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/core/CRootContainer.h"

CDataModel* test000050::pCOPASIDATAMODEL = NULL;

void test000050::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000050::tearDown()
{
  CRootContainer::destroy();
}

void test000050::test_bug894()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000050::MODEL_STRING);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);

  std::string sbml = pDataModel->exportSBMLToString(NULL, 2, 3);
  CPPUNIT_ASSERT(sbml.empty() == false);
  SBMLDocument* doc = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(doc != NULL);
  CPPUNIT_ASSERT(doc->getModel() != NULL);
  CPPUNIT_ASSERT(doc->getModel()->getNumFunctionDefinitions() > 0);

  SBase* def = doc->getModel()->getFunctionDefinition(0);
  CPPUNIT_ASSERT(def != NULL);

  FunctionDefinition* fDef = dynamic_cast<FunctionDefinition*>(def);
  CPPUNIT_ASSERT(def != NULL);
  CPPUNIT_ASSERT(def->isSetAnnotation() == true);
  CPPUNIT_ASSERT(def->getAnnotation() != NULL);
  CPPUNIT_ASSERT(def->getAnnotation()->getNumChildren() == 1);
  CPPUNIT_ASSERT(def->getAnnotation()->getChild(0).getURI() == "http://sbml.org/annotations/distribution");
  CPPUNIT_ASSERT(def->getAnnotation()->getChild(0).getAttrValue("definition") == "http://www.uncertml.org/distributions/uniform");
}

const char* test000050::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.3.25 (Debug) (http://www.copasi.org) at 2008-02-27 12:47:16 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"25\">\n"
  "  <Model key=\"Model_0\" name=\"New Model\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"K\" simulationType=\"fixed\">\n"
  "        <InitialExpression>\n"
  "          uniform(4.0,0.5)\n"
  "        </InitialExpression>\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 4.12243135037551\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n"
  ;
