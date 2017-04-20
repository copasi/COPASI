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

#include "test000084.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Compartment.h"
#include "sbml/UnitDefinition.h"
#include "sbml/Unit.h"
#include "sbml/UnitKind.h"

CDataModel* test000084::pCOPASIDATAMODEL = NULL;

void test000084::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000084::tearDown()
{
  CRootContainer::destroy();
}

void test000084::test_import_compartment_units_1()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING1));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::nm2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();
      // make sure there is no message about units not being consistent
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 24);
      // make sure all units were imported
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 55);
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 66);
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 79);
      ++i;
    }
}

void test000084::test_import_compartment_units_2()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING2));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  unsigned int i = 0, iMax = CCopasiMessage::size();

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // make sure there is a message about the unit not being recognized by
      // COPASI since the scale is off
      if (message.getNumber() == MCSBML + 66)
        {
          break;
        }

      ++i;
    }

  CPPUNIT_ASSERT(i != iMax);
}

void test000084::test_import_compartment_units_3()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING3));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 1);
}

void test000084::test_import_compartment_units_4()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING4));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::mm2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_5()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING5));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::nm2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 1);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_6()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING6));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::nm2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 1);
}

void test000084::test_import_compartment_units_7()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING7));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::nm2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found66 = 0;
  unsigned int found79 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_8()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING8));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found66 = 0;
  unsigned int found79 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_9()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING9));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 1);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_10()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING10));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found66 = 0;
  unsigned int found79 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_11()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING11));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 1);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_12()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING12));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 1);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_13()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING13));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::dimensionlessArea);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();
      // make sure there is no message about units not being consistent
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 24);
      // make sure all units were imported
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 55);
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 66);
      CPPUNIT_ASSERT(message.getNumber() != MCSBML + 79);
      ++i;
    }
}

void test000084::test_import_compartment_units_14()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING14));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 1);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_15()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING15));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 1);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_16()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING16));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 1);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_17()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING17));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found79 = 0;
  unsigned int found66 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 1);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_18()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING18));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 2);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found66 = 0;
  unsigned int found79 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_19()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING19));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 2);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found66 = 0;
  unsigned int found79 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 0);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_20()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING20));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 2);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found66 = 0;
  unsigned int found79 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 1);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 0);
}

void test000084::test_import_compartment_units_21()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING21));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 2);
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getAreaUnitEnum() == CUnit::m2);
  // make sure there is no warning about inconsistent units
  unsigned int i = 0, iMax = CCopasiMessage::size();
  unsigned int found24 = 0;
  unsigned int found55 = 0;
  unsigned int found66 = 0;
  unsigned int found79 = 0;

  while (i < iMax)
    {
      CCopasiMessage message = CCopasiMessage::getLastMessage();

      // check for messages about inconsistent units
      if (message.getNumber() == MCSBML + 24)
        {
          ++found24;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 55)
        {
          ++found55;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 66)
        {
          ++found66;
        }

      // check for import errors
      if (message.getNumber() == MCSBML + 79)
        {
          ++found79;
        }

      ++i;
    }

  CPPUNIT_ASSERT(found55 == 0);
  CPPUNIT_ASSERT(found24 == 1);
  CPPUNIT_ASSERT(found79 == 0);
  CPPUNIT_ASSERT(found66 == 0);
}

const char* test000084::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with global area unit nm^2.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"-9\" exponent=\"2\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\" />"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with global area unit 10e-4* m^2 .</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"-4\" exponent=\"2\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\" />"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with global area unit mole.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"area\">"
  "        <listOfUnits>"
  "          <unit kind=\"mole\" scale=\"0\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\" />"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING4 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with global area unit nm^2</p>"
  "        <p> and a compartment with mm^2 units</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"-9\" exponent=\"2\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "      <unitDefinition id=\"my_area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"-3\" exponent=\"2\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"my_area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING5 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with global area unit nm^2</p>"
  "        <p>and a compartment with mole units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"-9\" exponent=\"2\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "      <unitDefinition id=\"my_area\">"
  "        <listOfUnits>"
  "          <unit kind=\"mole\" scale=\"0\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"my_area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING6 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with global area unit mole</p>"
  "        <p>and a compartment with nm^2 units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"my_area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"-9\" exponent=\"2\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "      <unitDefinition id=\"area\">"
  "        <listOfUnits>"
  "          <unit kind=\"mole\" scale=\"0\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"my_area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING7 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a compartment with nm^2 units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"my_area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"-9\" exponent=\"2\"/>"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"my_area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING8 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a compartment with area units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING9 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a compartment with metre units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"metre\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING10 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a compartment with no units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  />"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING11 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a 2D compartment with volume units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"volume\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING12 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a 2D compartment with length units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"length\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING13 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a 2D compartment with dimensionmess units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"dimensionless\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING14 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a 2D compartment with m^3 units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"my_area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"0\" exponent=\"3\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"my_area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING15 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a 2D compartment with m units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"my_area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"0\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"my_area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING16 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a 2D compartment with mole units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"my_area\">"
  "        <listOfUnits>"
  "          <unit kind=\"mole\" scale=\"0\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"my_area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING17 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and a 2D compartment with substance units.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"substance\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING18 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and two compartments. One has no unit, the other uses area as the unit.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  />"
  "      <compartment id=\"compartment_2\" name=\"compartment_2\" size=\"1\" spatialDimensions=\"2\"  units=\"area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING19 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and two compartments. One has no unit, the other uses metre^2 as the unit.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  />"
  "      <compartment id=\"compartment_2\" name=\"compartment_2\" size=\"1\" spatialDimensions=\"2\"  units=\"area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING20 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and two compartments. One has no unit, the other uses nm^2 as the unit.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"my_area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"-9\" exponent=\"2\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  />"
  "      <compartment id=\"compartment_2\" name=\"compartment_2\" size=\"1\" spatialDimensions=\"2\"  units=\"my_area\"/>"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;

const char* test000084::MODEL_STRING21 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">"
  "  <model id=\"Model_1\" name=\"New Model\">"
  "    <notes>"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">"
  "        <p>L2V1 model with no global area unit</p>"
  "        <p>and two compartments. One has nm^2 as the unit, the other one has no unit.</p>"
  "      </body>"
  "    </notes>"
  "    <listOfUnitDefinitions>"
  "      <unitDefinition id=\"my_area\">"
  "        <listOfUnits>"
  "          <unit kind=\"metre\" scale=\"-9\" exponent=\"2\" />"
  "        </listOfUnits>"
  "      </unitDefinition>"
  "    </listOfUnitDefinitions>"
  "    <listOfCompartments>"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\" spatialDimensions=\"2\"  units=\"my_area\"/>"
  "      <compartment id=\"compartment_2\" name=\"compartment_2\" size=\"1\" spatialDimensions=\"2\"  />"
  "    </listOfCompartments>"
  "  </model>"
  "</sbml>"
  ;
