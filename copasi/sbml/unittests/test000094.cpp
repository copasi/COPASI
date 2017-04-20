// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiException.h"

#include <sbml/SBMLDocument.h>
#include <sbml/Model.h>

#include "copasi/core/CRootContainer.h"

#include "test000094.h"

// these are testcases for handling SBML models with required and non-required packages

CDataModel* test000094::pCOPASIDATAMODEL = NULL;

void test000094::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000094::tearDown()
{
  CRootContainer::destroy();
}

void test000094::test_required_package()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  bool failed = false;

  try
    {
      pDataModel->importSBMLFromString(test000094::MODEL_STRING1);
    }
  catch (const CCopasiException& e)
    {

      failed = true;
    }

  CPPUNIT_ASSERT_MESSAGE("The model should have failed loading because it contains a required package.", failed == true);
  // check for the error message in the COPASI message stack
}

void test000094::test_notrequired_package()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  bool result = pDataModel->importSBMLFromString(test000094::MODEL_STRING2);
  CPPUNIT_ASSERT(result == true);
  CModel *pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pDataModel->getCurrentSBMLDocument() != NULL);
}

/**
 * This model contains a required package which COPASI does not understand, so
 * we refuse to load the model.
 */
const char* test000094::MODEL_STRING1 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\"\n"
                                        "      xmlns:ppp=\"http://www.sbml.org/sbml/level3/version1/some_package/version1\"\n"
                                        "      ppp:required=\"true\">\n"
                                        "  <model id=\"Model_1\" name=\"New Model\">\n"
                                        "  <ppp:some_package>\n"
                                        "  </ppp:some_package>\n"
                                        "  </model>\n"
                                        "</sbml>\n";

/**
 * This model contains a package that is not required, so COPASI should just
 * ignore it and load the model.
 */
const char* test000094::MODEL_STRING2 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\"\n"
                                        "      xmlns:ppp=\"http://www.sbml.org/sbml/level3/version1/some_package/version1\"\n"
                                        "      ppp:required=\"false\">\n"
                                        "  <model id=\"Model_1\" name=\"New Model\">\n"
                                        "  <ppp:element>\n"
                                        "  </ppp:element>\n"
                                        "  </model>\n"
                                        "</sbml>\n";
