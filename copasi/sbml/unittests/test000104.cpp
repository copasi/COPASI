// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000104.h"

#include <string>
#include <iostream>

#include <copasi/report/CRootContainer.h>
#include <copasi/CopasiDataModel/CDataModel.h>

#include "sbml/xml/XMLNode.h"
#include "sbml/xml/XMLAttributes.h"
#include "sbml/xml/XMLInputStream.h"

// libsbml will not add units to unit definitions of Level 3 documents
// if not all attributes are explicitely set.
// Prior versions of the exporter did not set the multiplier on all units and therefore
// most units were not exported correctly to Level 3.

void test000104::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  pDataModel = CRootContainer::addDatamodel();
}

void test000104::tearDown()
{
  CRootContainer::destroy();
}

void test000104::test_bug1744()
{
  try
    {
      bool result = pDataModel->importSBMLFromString(SBML_STRING);
      CPPUNIT_ASSERT(result == true);
    }
  catch (...)
    {
      CPPUNIT_ASSERT_MESSAGE("Importing the model string failed with an exception.", false);
    }

  // the actual test was if the import leads to a crash, the rest is just sugar coating

  // check the error messages
  // since there are 6 unit ids used on the model, but none of these is defined as
  // a unit definiton, we should have at least 6 warnings and one should be MCSBML + 66
  unsigned int i, iMax = CCopasiMessage::size();
  CPPUNIT_ASSERT(iMax >= 6);
  CPPUNIT_ASSERT(CCopasiMessage::checkForMessage(MCSBML + 66) == true);
}

const char* test000104::SBML_STRING = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                      "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" xmlns:comp=\"http://www.sbml.org/sbml/level3/version1/comp/version1\" level=\"3\" version=\"1\" xmlns:html=\"http://www.w3.org/1999/xhtml\" xmlns:jigcell=\"http://www.sbml.org/2001/ns/jigcell\" xmlns:math=\"http://www.w3.org/1998/Math/MathML\">\n"
                                      "<comp:listOfModelDefinitions>\n"
                                      "</comp:listOfModelDefinitions>\n"
                                      "<model areaUnits=\"area\" extentUnits=\"substance\" id=\"Model_1\" lengthUnits=\"length\" metaid=\"COPASI1\" name=\"RootModel\" substanceUnits=\"substance\" timeUnits=\"time\" volumeUnits=\"volume\">\n"
                                      "  </model>\n"
                                      "</sbml>";
