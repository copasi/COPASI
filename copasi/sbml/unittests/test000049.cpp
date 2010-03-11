// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/test000049.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/11 11:52:00 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000049.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/report/CCopasiRootContainer.h"

CCopasiDataModel* test000049::pCOPASIDATAMODEL = NULL;

void test000049::setUp()
{
  // Create the root container.
  CCopasiRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CCopasiRootContainer::addDatamodel();
}

void test000049::tearDown()
{
  CCopasiRootContainer::destroy();
}

void test000049::test_bug894()
{
  // load the CPS file
  // export to SBML
  // check the resulting SBML model
  CCopasiDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000049::MODEL_STRING);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);

  try
    {
      CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 3).empty() == true);
    }
  catch (...)
    {
      // check if the correct error message has been created
      CPPUNIT_ASSERT(pDataModel->getCurrentSBMLDocument() == NULL);
      // last message should be an exception
      CCopasiMessage message = CCopasiMessage::getLastMessage();
      CPPUNIT_ASSERT(message.getType() == CCopasiMessage::EXCEPTION);
      // see if the incompatibility message is there
      bool found = false;

      while (CCopasiMessage::size() > 0)
        {
          message = CCopasiMessage::getLastMessage();

          if (message.getType() == CCopasiMessage::RAW)
            {
              std::string s = message.getText();

              if (s.find(std::string("Call to function \"normal\" used in mathematical expression for initial expression for object named \"K\" which can not be exported to SBML")) != std::string::npos)
                {
                  found = true;
                  break;
                }
            }
        }

      CPPUNIT_ASSERT_MESSAGE("Error message not found.", found == true);
      return;
    }

  // we should not get this far
  CPPUNIT_ASSERT(false);
}

const char* test000049::MODEL_STRING =
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
  "          normal(4.0,0.5)\n"
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
