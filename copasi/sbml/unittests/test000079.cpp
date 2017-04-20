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

#include "test000079.h"

#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/core/CRootContainer.h"

CDataModel* test000079::pCOPASIDATAMODEL = NULL;

void test000079::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000079::tearDown()
{
  CRootContainer::destroy();
}

void test000079::test_import_fast()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;

  try
    {
      CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000079::MODEL_STRING1));
    }
  catch (...)
    {
      // there should not be an exception
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  // there should only be one error message that the fast flag on "reaction3"
  // was ignored.
  CPPUNIT_ASSERT(CCopasiMessage::size() > 0);
  CCopasiMessage message;
  unsigned int i, iMax = CCopasiMessage::size();

  for (i = 0; i < iMax; ++i)
    {
      message = CCopasiMessage::getLastMessage();

      if (message.getNumber() == MCSBML + 29)
        {
          break;
        }
    }

  // check if the message was found
  CPPUNIT_ASSERT(i != iMax);
  // check that only reaction 3 is listed in the message
  std::string text = message.getText();
  CPPUNIT_ASSERT(text.find("reaction1") == std::string::npos);
  CPPUNIT_ASSERT(text.find("reaction2") == std::string::npos);
  CPPUNIT_ASSERT(text.find("reaction3") != std::string::npos);
}

const char* test000079::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"test000079\">\n"
  "    <notes>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <head>\n"
  "          <meta name=\"qrichtext\" content=\"1\"/>\n"
  "        </head>\n"
  "        <body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "          <p>Model to test import the fast flag.</p>\n"
  "        </body>\n"
  "      </html>\n"
  "    </notes>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"S1\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "      <species id=\"species_2\" name=\"S2\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "      <species id=\"species_3\" name=\"S3\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter id=\"parameter_1\" name=\"k\" value=\"1\" units=\"time\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction1\" fast=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_1\"/>\n"
  "        </listOfReactants>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <divide/>\n"
  "              <apply>\n"
  "                <times/>\n"
  "                <ci> compartment_1 </ci>\n"
  "                <ci> species_1 </ci>\n"
  "              </apply>\n"
  "              <ci> parameter_1 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "      <reaction id=\"reaction2\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_2\"/>\n"
  "        </listOfReactants>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <divide/>\n"
  "              <apply>\n"
  "                <times/>\n"
  "                <ci> compartment_1 </ci>\n"
  "                <ci> species_2 </ci>\n"
  "              </apply>\n"
  "              <ci> parameter_1 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "      <reaction id=\"reaction3\" fast=\"true\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_3\"/>\n"
  "        </listOfReactants>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <divide/>\n"
  "              <apply>\n"
  "                <times/>\n"
  "                <ci> compartment_1 </ci>\n"
  "                <ci> species_3 </ci>\n"
  "              </apply>\n"
  "              <ci> parameter_1 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n";
