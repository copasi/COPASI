// Copyright (C) 2011 - 2012 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "test000103.h"

#include <string>

#include <copasi/report/CCopasiRootContainer.h>
#include <copasi/CopasiDataModel/CCopasiDataModel.h>
#include <copasi/model/CModel.h>

// in earlier version of COPASI, setting the SBML id on a model prior to exporting it
// had no effect (bug 1743)

void test000103::setUp()
{
  // Create the root container.
  CCopasiRootContainer::init(0, NULL, false);
  pDataModel = CCopasiRootContainer::addDatamodel();
}

void test000103::tearDown()
{
  CCopasiRootContainer::destroy();
}


void test000103::test_bug1743_l2()
{
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  std::string id("MyTestModel");
  pModel->setSBMLId(id);
  CPPUNIT_ASSERT(pModel->getSBMLId() == id);
  // export to l2v4
  std::string model_string = pDataModel->exportSBMLToString(NULL, 2, 4);
  pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getSBMLId() == id);
  pDataModel->newModel(NULL, true);
  pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getSBMLId() != id);

  try
    {
      bool result = pDataModel->importSBMLFromString(model_string);
      CPPUNIT_ASSERT(result == true);
    }
  catch (...)
    {
      CPPUNIT_ASSERT_MESSAGE("Exception while importing the exported model string.", false);
    }

  pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getSBMLId() == id);
}

void test000103::test_bug1743_l3()
{
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  std::string id("MyTestModel");
  pModel->setSBMLId(id);
  CPPUNIT_ASSERT(pModel->getSBMLId() == id);
  // export to l3v1
  std::string model_string = pDataModel->exportSBMLToString(NULL, 3, 1);
  pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getSBMLId() == id);
  pDataModel->newModel(NULL, true);
  pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getSBMLId() != id);

  try
    {
      bool result = pDataModel->importSBMLFromString(model_string);
      CPPUNIT_ASSERT(result == true);
    }
  catch (...)
    {
      CPPUNIT_ASSERT_MESSAGE("Exception while importing the exported model string.", false);
    }

  pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getSBMLId() == id);
}

