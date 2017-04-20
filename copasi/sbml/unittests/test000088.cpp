// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000088.h"

#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CEvent.h"

// test for Bug 1411

CDataModel* test000088::pCOPASIDATAMODEL = NULL;

void test000088::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000088::tearDown()
{
  CRootContainer::destroy();
}

void test000088::test_import_assignment_without_expression()
{
  CPPUNIT_ASSERT(pCOPASIDATAMODEL->importSBMLFromString(test000088::MODEL_STRING1));
  // check if we have the correct warning message on the stack
  // there should be a warning (MCSBML + 58)
  unsigned int i, iMax = CCopasiMessage::size();
  CCopasiMessage message;
  bool found58 = false;

  for (i = 0; i < iMax; ++i)
    {
      message = CCopasiMessage::getLastMessage();

      if (message.getNumber() == MCSBML + 58)
        {
          found58 = true;
          break;
        }
    }

  CPPUNIT_ASSERT(found58 == true);
  // check if the model contains one parameter and that this parameter does not
  // have an expression
  const CModel* pModel = pCOPASIDATAMODEL->getModel();
  CPPUNIT_ASSERT(pModel !=  NULL);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pMV = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pMV != NULL);
  CPPUNIT_ASSERT(pMV->getExpression().empty());
}

void test000088::test_import_initialassignment_without_expression()
{
  bool result = pCOPASIDATAMODEL->importSBMLFromString(test000088::MODEL_STRING2);
  CPPUNIT_ASSERT(result == true);
  // check if we have the correct warning message on the stack
  // there should be a warning (MCSBML + 58)
  unsigned int i, iMax = CCopasiMessage::size();
  CCopasiMessage message;
  bool found58 = false;

  for (i = 0; i < iMax; ++i)
    {
      message = CCopasiMessage::getLastMessage();

      if (message.getNumber() == MCSBML + 58)
        {
          found58 = true;
          break;
        }
    }

  CPPUNIT_ASSERT(found58 == true);
  // check if the model contains one parameter and that this parameter does not
  // have an expression
  const CModel* pModel = pCOPASIDATAMODEL->getModel();
  CPPUNIT_ASSERT(pModel !=  NULL);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pMV = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pMV != NULL);
  CPPUNIT_ASSERT(pMV->getInitialExpression().empty());
  // since the parameter does not set an initial value, it's value should be 1.0
  CPPUNIT_ASSERT(fabs(pMV->getInitialValue() - 1.0) < 1e-6);
}

void test000088::test_import_eventassignment_without_expression()
{
  CPPUNIT_ASSERT(pCOPASIDATAMODEL->importSBMLFromString(test000088::MODEL_STRING3));
  // check if we have the correct warning message on the stack
  // there should be a warning (MCSBML + 58)
  unsigned int i, iMax = CCopasiMessage::size();
  CCopasiMessage message;
  bool found58 = false;

  for (i = 0; i < iMax; ++i)
    {
      message = CCopasiMessage::getLastMessage();

      if (message.getNumber() == MCSBML + 58)
        {
          found58 = true;
          break;
        }
    }

  CPPUNIT_ASSERT(found58 == true);
  // check if the model contains one parameter and that this parameter does not
  // have an expression
  const CModel* pModel = pCOPASIDATAMODEL->getModel();
  CPPUNIT_ASSERT(pModel !=  NULL);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 1);
  const CModelValue* pMV = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pMV != NULL);
  // since the parameter does not set an initial value, it's value should be 1
  CPPUNIT_ASSERT(fabs(pMV->getInitialValue() - 1.0) < 1e-6);

  // check if there is one event and that this event does not have an event
  // assignment
  CPPUNIT_ASSERT(pModel->getEvents().size() == 1);
  const CEvent* pEvent = pModel->getEvents()[0];
  CPPUNIT_ASSERT(pEvent != NULL);
  CPPUNIT_ASSERT(pEvent->getAssignments().size() == 0);
}

const char* test000088::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"model_1\" name=\"model\">\n"
  "    <listOfParameters>\n"
  "      <parameter constant=\"false\" id=\"parameter_1\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "      <assignmentRule variable=\"parameter_1\" />\n"
  "    </listOfRules>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000088::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n"
  "  <model id=\"model_1\" name=\"model\">\n"
  "    <listOfParameters>\n"
  "      <parameter constant=\"false\" id=\"parameter_1\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfInitialAssignments>\n"
  "      <initialAssignment symbol=\"parameter_1\" />\n"
  "    </listOfInitialAssignments>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000088::MODEL_STRING3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"model_1\" name=\"model\">\n"
  "    <listOfParameters>\n"
  "      <parameter constant=\"false\" id=\"parameter_1\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfEvents>\n"
  "      <event>\n"
  "        <trigger>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <geq/>\n"
  "              <ci> parameter_1 </ci>\n"
  "              <cn> 3.0 </cn>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </trigger>\n"
  "        <listOfEventAssignments>\n"
  "          <eventAssignment variable=\"parameter_1\" />\n"
  "        </listOfEventAssignments>\n"
  "      </event>\n"
  "    </listOfEvents>\n"
  "  </model>\n"
  "</sbml>\n";
