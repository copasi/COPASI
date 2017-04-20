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

#include "test000077.h"

#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiException.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Species.h"

CDataModel* test000077::pCOPASIDATAMODEL = NULL;

/**
 * Test the export of models with references to local parameters in
 * expressions.
 */
void test000077::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000077::tearDown()
{
  CRootContainer::destroy();
}

void test000077::test_import_dimensionless_1()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;

  try
    {
      CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000077::MODEL_STRING1));
    }
  catch (...)
    {
      // there should not be an exception
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->getModel()->getVolumeUnitEnum() == CUnit::dimensionlessVolume);
  CPPUNIT_ASSERT(pDataModel->getModel()->getTimeUnitEnum() == CUnit::dimensionlessTime);
  CPPUNIT_ASSERT(pDataModel->getModel()->getQuantityUnitEnum() == CUnit::dimensionlessQuantity);
}

void test000077::test_import_dimensionless_2()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;

  try
    {
      CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000077::MODEL_STRING2));
    }
  catch (...)
    {
      // there should not be an exception
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  CPPUNIT_ASSERT(pDataModel->getModel()->getVolumeUnitEnum() == CUnit::dimensionlessVolume);
  CPPUNIT_ASSERT(pDataModel->getModel()->getTimeUnitEnum() == CUnit::dimensionlessTime);
  CPPUNIT_ASSERT(pDataModel->getModel()->getQuantityUnitEnum() == CUnit::dimensionlessQuantity);
}

void test000077::test_import_dimensionless_3()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;

  try
    {
      CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000077::MODEL_STRING3));
    }
  catch (...)
    {
      // there shouldn't be any reason for an exception
      CPPUNIT_ASSERT(false);
    }

  // check if a message MCSBML + 66 is on the message stack
  bool found = false;
  CCopasiMessage message;

  while (CCopasiMessage::size() > 0)
    {
      message = CCopasiMessage::getLastMessage();

      if (message.getNumber() == MCSBML + 66)
        {
          found = true;
          break;
        }
    }

  CPPUNIT_ASSERT(found == true);
  CPPUNIT_ASSERT(message.getText().find("volume") != std::string::npos);
}

void test000077::test_import_dimensionless_4()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;

  try
    {
      CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000077::MODEL_STRING4));
    }
  catch (...)
    {
      // there shouldn't be any reason for an exception
      CPPUNIT_ASSERT(false);
    }

  // check if a message MCSBML + 66 is on the message stack
  bool found = false;
  CCopasiMessage message;

  while (CCopasiMessage::size() > 0)
    {
      message = CCopasiMessage::getLastMessage();

      if (message.getNumber() == MCSBML + 66)
        {
          found = true;
          break;
        }
    }

  CPPUNIT_ASSERT(found == true);
  CPPUNIT_ASSERT(message.getText().find("time") != std::string::npos);
}

void test000077::test_import_dimensionless_5()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;

  try
    {
      CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000077::MODEL_STRING5));
    }
  catch (...)
    {
      // there shouldn't be any reason for an exception
      CPPUNIT_ASSERT(false);
    }

  // check if a message MCSBML + 66 is on the message stack
  bool found = false;
  CCopasiMessage message;

  while (CCopasiMessage::size() > 0)
    {
      message = CCopasiMessage::getLastMessage();

      if (message.getNumber() == MCSBML + 66)
        {
          found = true;
          break;
        }
    }

  CPPUNIT_ASSERT(found == true);
  CPPUNIT_ASSERT(message.getText().find("substance") != std::string::npos);
}

void test000077::test_export_dimensionless()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000077::MODEL_STRING6);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  std::string sbmlString;

  try
    {
      sbmlString = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      // fail if an uncaught exception occurs during export
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!sbmlString.empty());
  // check if the exported SBML model has two parameters
  pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument != NULL);
  const Model* pModel = pDocument->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getListOfCompartments()->size() == 1);
  CPPUNIT_ASSERT(pModel->getListOfSpecies()->size() == 1);
  const UnitDefinition* pUDef = pModel->getUnitDefinition("time");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getListOfUnits()->size() == 1);
  const Unit* pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_DIMENSIONLESS);
  pUDef = pModel->getUnitDefinition("volume");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getListOfUnits()->size() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_DIMENSIONLESS);
  pUDef = pModel->getUnitDefinition("substance");
  CPPUNIT_ASSERT(pUDef != NULL);
  CPPUNIT_ASSERT(pUDef->getListOfUnits()->size() == 1);
  pUnit = pUDef->getUnit(0);
  CPPUNIT_ASSERT(pUnit != NULL);
  CPPUNIT_ASSERT(pUnit->getScale() == 0);
  CPPUNIT_ASSERT(fabs((pUnit->getMultiplier() - 1.0) / 1.0) < 1e-6);
  CPPUNIT_ASSERT(pUnit->getKind() == UNIT_KIND_DIMENSIONLESS);
}

const char* test000077::MODEL_STRING1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"test000077\">\n"
  "    <notes>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <head>\n"
  "          <meta name=\"qrichtext\" content=\"1\"/>\n"
  "        </head>\n"
  "        <body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "          <p>Model to test import of dimensionless units.</p>\n"
  "        </body>\n"
  "      </html>\n"
  "    </notes>\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"time\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"S\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "    </listOfSpecies>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000077::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"test000077\">\n"
  "    <notes>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <head>\n"
  "          <meta name=\"qrichtext\" content=\"1\"/>\n"
  "        </head>\n"
  "        <body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "          <p>Model to test import of dimensionless units.</p>\n"
  "        </body>\n"
  "      </html>\n"
  "    </notes>\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"0.001\" scale=\"3\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"time\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"10\" scale=\"-1\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"0.01\" scale=\"2\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"S\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "    </listOfSpecies>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000077::MODEL_STRING3 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"test000077\">\n"
  "    <notes>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <head>\n"
  "          <meta name=\"qrichtext\" content=\"1\"/>\n"
  "        </head>\n"
  "        <body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "          <p>Model to test import of dimensionless units.</p>\n"
  "        </body>\n"
  "      </html>\n"
  "    </notes>\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"0.04\" scale=\"-3\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"time\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"10\" scale=\"-1\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"0.01\" scale=\"2\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"S\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "    </listOfSpecies>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000077::MODEL_STRING4 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"test000077\">\n"
  "    <notes>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <head>\n"
  "          <meta name=\"qrichtext\" content=\"1\"/>\n"
  "        </head>\n"
  "        <body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "          <p>Model to test import of dimensionless units.</p>\n"
  "        </body>\n"
  "      </html>\n"
  "    </notes>\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"0.001\" scale=\"3\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"time\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"10\" scale=\"-2\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"0.01\" scale=\"2\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"S\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "    </listOfSpecies>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000077::MODEL_STRING5 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"test000077\">\n"
  "    <notes>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <head>\n"
  "          <meta name=\"qrichtext\" content=\"1\"/>\n"
  "        </head>\n"
  "        <body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "          <p>Model to test import of dimensionless units.</p>\n"
  "        </body>\n"
  "      </html>\n"
  "    </notes>\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"0.001\" scale=\"3\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"time\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"10\" scale=\"-1\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"dimensionless\" multiplier=\"0.1\" scale=\"2\" />\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"S\" compartment=\"compartment_1\" initialConcentration=\"1\"/>\n"
  "    </listOfSpecies>\n"
  "  </model>\n"
  "</sbml>\n";

const char* test000077::MODEL_STRING6 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.5.30 (Debug) (http://www.copasi.org) at 2009-01-27 14:56:07 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"30\">\n"
  "  <Model key=\"Model_0\" name=\"test000077\" timeUnit=\"dimensionless\" volumeUnit=\"dimensionless\" quantityUnit=\"dimensionless\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:13pt;font-family:Lucida Grande\">\n"
  "<p>Model to test export of dimensionless units.</p>\n"
  "</body></html>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"S\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1 1\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "</COPASI>\n";
