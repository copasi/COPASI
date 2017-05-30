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

#include "test000061.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CExpression.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Species.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000061::pCOPASIDATAMODEL = NULL;

void test000061::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000061::tearDown()
{
  CRootContainer::destroy();
}

void test000061::test_bug_1044()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000061::MODEL_STRING1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // check if the model has been loaded correctly
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getObjectName() == "A");
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::Status::ASSIGNMENT);
  CPPUNIT_ASSERT(pModelValue->getExpressionPtr() != NULL);
  const CEvaluationNode* pRoot = pModelValue->getExpressionPtr()->getRoot();
  CPPUNIT_ASSERT(pRoot != NULL);
  CPPUNIT_ASSERT(pRoot->mainType() == CEvaluationNode::MainType::INVALID);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  // export the model to SBML
  bool exception = false;

  try
    {
      CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == true);
    }
  catch (...)
    {
      exception = true;
    }

  CPPUNIT_ASSERT(exception == true);
  CPPUNIT_ASSERT(pDataModel->getCurrentSBMLDocument() == NULL);
  // check if the correct error message has been created.
  const CCopasiMessage& message = CCopasiMessage::getLastMessage();
  CPPUNIT_ASSERT(message.getNumber() == MCSBML + 70);
  CPPUNIT_ASSERT(message.getType() == CCopasiMessage::EXCEPTION);
  CPPUNIT_ASSERT(CCopasiMessage::size() == 0);
}

const char* test000061::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<!-- generated with COPASI 4.4.26 (Debug) (http://www.copasi.org) at 2008-06-09 07:46:05 UTC -->"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"26\">"
  "  <Model key=\"Model_0\" name=\"Bug 1044\" timeUnit=\"s\" volumeUnit=\"ml\" quantityUnit=\"mmol\" type=\"deterministic\">"
  "    <Comment>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        "
  "      </body>"
  "    </Comment>"
  "    <ListOfModelValues>"
  "      <ModelValue key=\"ModelValue_0\" name=\"A\" simulationType=\"assignment\">"
  "      </ModelValue>"
  "    </ListOfModelValues>"
  "    <StateTemplate>"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>"
  "    </StateTemplate>"
  "    <InitialState type=\"initialState\">"
  "      0 0"
  "    </InitialState>"
  "  </Model>"
  "</COPASI>"
  ;
