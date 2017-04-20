// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000102.h"

#include <string>

#include <copasi/report/CRootContainer.h>
#include <copasi/CopasiDataModel/CDataModel.h>

#include "sbml/xml/XMLNode.h"
#include "sbml/xml/XMLAttributes.h"
#include "sbml/xml/XMLInputStream.h"

// libsbml will not add units to unit definitions of Level 3 documents
// if not all attributes are explicitely set.
// Prior versions of the exporter did not set the multiplier on all units and therefore
// most units were not exported correctly to Level 3.

void test000102::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  pDataModel = CRootContainer::addDatamodel();
}

void test000102::tearDown()
{
  CRootContainer::destroy();
}

void test000102::test_bug1741()
{
  pDataModel->importSBMLFromString(SBML_STRING);
  std::string s = pDataModel->exportSBMLToString(NULL, 3, 1);
  // we have to check that the string contains all the units
  // and that all units are declared on the model element
  XMLInputStream inputstream(s.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pModelNode = NULL;
  const XMLNode* pUnitDefinitionsNode = NULL;
  const XMLNode* pLengthNode = NULL;
  const XMLNode* pAreaNode = NULL;
  const XMLNode* pVolumeNode = NULL;
  const XMLNode* pTimeNode = NULL;
  const XMLNode* pSubstanceNode = NULL;
  const XMLNode* pListOfUnitsNode = NULL;
  const XMLNode* pUnitNode = NULL;
  const XMLNode* pChild = NULL;
  const XMLAttributes* pAttr = NULL;

  // get the model node and check that all unit
  // attributes are set
  for (unsigned int i = 0; i < iMax; ++i)
    {
      pChild = &node.getChild(i);

      if (pChild->getName() == "model")
        {
          pModelNode = pChild;
          pChild = NULL;
          break;
        }
    }

  assert(pModelNode != NULL);
  pAttr = &pModelNode->getAttributes();
  int index = pAttr->getIndex("lengthUnits");
  CPPUNIT_ASSERT(index != -1);
  std::string v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "length");

  index = pAttr->getIndex("areaUnits");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "area");

  index = pAttr->getIndex("volumeUnits");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "volume");

  index = pAttr->getIndex("timeUnits");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "time");

  index = pAttr->getIndex("substanceUnits");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "substance");

  index = pAttr->getIndex("extentUnits");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "substance");

  // find the list of UnitDefinitions
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pModelNode->getChild(i);

      if (pChild->getName() == "listOfUnitDefinitions")
        {
          pUnitDefinitionsNode = pChild;
          pChild = NULL;
          break;
        }
    }

  CPPUNIT_ASSERT(pUnitDefinitionsNode != NULL);

  iMax = pUnitDefinitionsNode->getNumChildren();
  // there have to be at least 5 unit definitions
  CPPUNIT_ASSERT(iMax > 4);

  // find the length unit
  // find the area unit
  // find the volume unit
  // find the time unit
  // find the substance unit
  for (i = 0; i < iMax; ++i)
    {
      pChild = &pUnitDefinitionsNode->getChild(i);

      if (pChild->getName() == "unitDefinition")
        {
          pAttr = &pChild->getAttributes();
          index = pAttr->getIndex("id");
          CPPUNIT_ASSERT(index != -1);
          v = pAttr->getValue(index);

          if (v == "area")
            {
              pAreaNode = pChild;
              continue;
            }
          else if (v == "length")
            {
              pLengthNode = pChild;
              continue;
            }
          else if (v == "volume")
            {
              pVolumeNode = pChild;
              continue;
            }
          else if (v == "time")
            {
              pTimeNode = pChild;
              continue;
            }
          else if (v == "substance")
            {
              pSubstanceNode = pChild;
              continue;
            }
        }
    }

  unsigned int numUnitChildren = 0;
  CPPUNIT_ASSERT(pAreaNode != NULL);
  iMax = pAreaNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pAreaNode->getChild(i);

      if (pChild->getName() == "listOfUnits")
        {
          pListOfUnitsNode = pChild;
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfUnitsNode != NULL);
  iMax = pListOfUnitsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pListOfUnitsNode->getChild(i);

      if (pChild->getName() == "unit")
        {
          ++numUnitChildren;
          pUnitNode = pChild;
        }
    }

  // check the unit(s)
  // TODO the numbers should be tested after
  // TODO conversion to a numerical value
  // TODO but for now the string comparison will do
  CPPUNIT_ASSERT(numUnitChildren == 1);
  CPPUNIT_ASSERT(pUnitNode != NULL);
  pAttr = &pUnitNode->getAttributes();
  // kind should be square metre
  index = pAttr->getIndex("kind");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "metre");
  // multiplier = 1
  index = pAttr->getIndex("multiplier");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "1");
  // scale =-3
  index = pAttr->getIndex("scale");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "-3");
  // exponent = 2
  index = pAttr->getIndex("exponent");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "2");

  CPPUNIT_ASSERT(pLengthNode != NULL);
  iMax = pLengthNode->getNumChildren();
  numUnitChildren = 0;
  CPPUNIT_ASSERT(iMax > 0);
  pListOfUnitsNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pLengthNode->getChild(i);

      if (pChild->getName() == "listOfUnits")
        {
          pListOfUnitsNode = pChild;
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfUnitsNode != NULL);
  iMax = pListOfUnitsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pListOfUnitsNode->getChild(i);

      if (pChild->getName() == "unit")
        {
          ++numUnitChildren;
          pUnitNode = pChild;
        }
    }

  // check the unit(s)
  CPPUNIT_ASSERT(numUnitChildren == 1);
  CPPUNIT_ASSERT(pUnitNode != NULL);
  pAttr = &pUnitNode->getAttributes();
  // kind should be square metre
  index = pAttr->getIndex("kind");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "metre");
  // multiplier = 1
  index = pAttr->getIndex("multiplier");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "1");
  // scale = 0
  index = pAttr->getIndex("scale");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "0");
  // exponent = 1
  index = pAttr->getIndex("exponent");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "1");

  CPPUNIT_ASSERT(pVolumeNode != NULL);
  iMax = pVolumeNode->getNumChildren();
  numUnitChildren = 0;
  CPPUNIT_ASSERT(iMax > 0);
  pListOfUnitsNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pVolumeNode->getChild(i);

      if (pChild->getName() == "listOfUnits")
        {
          pListOfUnitsNode = pChild;
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfUnitsNode != NULL);
  iMax = pListOfUnitsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pListOfUnitsNode->getChild(i);

      if (pChild->getName() == "unit")
        {
          ++numUnitChildren;
          pUnitNode = pChild;
        }
    }

  // check the unit(s)
  CPPUNIT_ASSERT(numUnitChildren == 1);
  CPPUNIT_ASSERT(pUnitNode != NULL);
  pAttr = &pUnitNode->getAttributes();
  // kind should be square metre
  index = pAttr->getIndex("kind");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "litre");
  // multiplier = 1
  index = pAttr->getIndex("multiplier");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "1");
  // scale = 0
  index = pAttr->getIndex("scale");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "0");
  // exponent = 1
  index = pAttr->getIndex("exponent");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "1");

  CPPUNIT_ASSERT(pTimeNode != NULL);
  iMax = pTimeNode->getNumChildren();
  numUnitChildren = 0;
  CPPUNIT_ASSERT(iMax > 0);
  pListOfUnitsNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pTimeNode->getChild(i);

      if (pChild->getName() == "listOfUnits")
        {
          pListOfUnitsNode = pChild;
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfUnitsNode != NULL);
  iMax = pListOfUnitsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pListOfUnitsNode->getChild(i);

      if (pChild->getName() == "unit")
        {
          ++numUnitChildren;
          pUnitNode = pChild;
        }
    }

  // check the unit(s)
  CPPUNIT_ASSERT(numUnitChildren == 1);
  CPPUNIT_ASSERT(pUnitNode != NULL);
  pAttr = &pUnitNode->getAttributes();
  // kind should be square metre
  index = pAttr->getIndex("kind");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "second");
  // multiplier = 1
  index = pAttr->getIndex("multiplier");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "1");
  // scale = 0
  index = pAttr->getIndex("scale");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "0");
  // exponent = 1
  index = pAttr->getIndex("exponent");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "1");

  CPPUNIT_ASSERT(pSubstanceNode != NULL);
  iMax = pSubstanceNode->getNumChildren();
  numUnitChildren = 0;
  CPPUNIT_ASSERT(iMax > 0);
  pListOfUnitsNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pSubstanceNode->getChild(i);

      if (pChild->getName() == "listOfUnits")
        {
          pListOfUnitsNode = pChild;
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfUnitsNode != NULL);
  iMax = pListOfUnitsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      pChild = &pListOfUnitsNode->getChild(i);

      if (pChild->getName() == "unit")
        {
          ++numUnitChildren;
          pUnitNode = pChild;
        }
    }

  // check the unit(s)
  CPPUNIT_ASSERT(numUnitChildren == 1);
  CPPUNIT_ASSERT(pUnitNode != NULL);
  pAttr = &pUnitNode->getAttributes();
  // kind should be square mole
  index = pAttr->getIndex("kind");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "mole");
  // multiplier = 1
  index = pAttr->getIndex("multiplier");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "1");
  // scale = 0
  index = pAttr->getIndex("scale");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "0");
  // exponent = 1
  index = pAttr->getIndex("exponent");
  CPPUNIT_ASSERT(index != -1);
  v = pAttr->getValue(index);
  CPPUNIT_ASSERT(v == "1");
}

const char* test000102::SBML_STRING = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                      "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" xmlns:comp=\"http://www.sbml.org/sbml/level3/version1/comp/version1\" level=\"3\" version=\"1\" > \n"
                                      "<model id=\"Module_1_1\" name=\"Module_1\" areaUnits=\"area\" substanceUnits=\"mole\" >\n"
                                      "  <listOfUnitDefinitions>\n"
                                      "    <unitDefinition id=\"area\" name=\"area\">\n"
                                      "      <listOfUnits>\n"
                                      "        <unit exponent=\"2\" kind=\"metre\" multiplier=\"1.0\" scale=\"-3\"/>\n"
                                      "      </listOfUnits>\n"
                                      "    </unitDefinition>\n"
                                      "  </listOfUnitDefinitions>\n"
                                      "  <listOfCompartments>\n"
                                      "    <compartment id=\"cell_1\" name=\"cell\" size=\"1.0\" constant=\"false\" spatialDimensions=\"2.0\" />\n"
                                      "  </listOfCompartments>\n"
                                      "  <listOfSpecies>\n"
                                      "    <species id=\"CycB_1\" name=\"CycB\" compartment=\"cell_1\" initialConcentration=\"1.0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" />\n"
                                      "  </listOfSpecies> \n"
                                      " </model>\n"
                                      "</sbml>\n";
