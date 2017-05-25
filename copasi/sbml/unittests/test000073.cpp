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

#include "test000073.h"

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
#include "sbml/Reaction.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000073::pCOPASIDATAMODEL = NULL;

void test000073::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000073::tearDown()
{
  CRootContainer::destroy();
}

void test000073::test_bug1087()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING1));
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->getModel()->getModelValues().size() == 1);
  const CModelValue* pModelValue = pDataModel->getModel()->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getSBMLId() == "parameter_1");
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::Status::ASSIGNMENT);
  std::string formula = pModelValue->getExpression();
  CPPUNIT_ASSERT(formula == "3.1*4.5");
}

const char* test000073::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level1\" level=\"1\" version=\"2\">\n"
  "  <model name=\"Model_1\" >\n"
  "    <notes>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <p>Level 1 model with rule on global parameter.</p>\n"
  "      </body>\n"
  "    </notes>\n"
  "    <listOfParameters>\n"
  "      <parameter name=\"parameter_1\" value=\"1.1\" />\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "      <parameterRule formula=\"3.1 * 4.5\" name=\"parameter_1\"/>\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n"
  ;
