// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000097.h"

#include <sstream>
#include "utilities.hpp"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/xml/XMLNode.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"

// layout objects
#include "copasi/layout/CLBase.h"
#include "copasi/layout/CLGlyphs.h"
#include "copasi/layout/CLayout.h"
#include "copasi/layout/CListOfLayouts.h"

// render objects
#include "copasi/layout/CLLocalRenderInformation.h"
#include "copasi/layout/CLGlobalRenderInformation.h"
#include "copasi/layout/CLColorDefinition.h"

#include <sbml/xml/XMLInputStream.h>

#include <string>
#include <map>
#include <vector>

void test000097::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  pDataModel = CRootContainer::addDatamodel();
}

void test000097::tearDown()
{
  CRootContainer::destroy();
}

// tests whether we are importing local render information
void test000097::test_import_local_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // import the file and check if we find the
  // local render information
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(SBML_MODEL_1));
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  const CLayout* pLayout = (*pDataModel->getListOfLayouts())[0];
  CPPUNIT_ASSERT(pLayout != NULL);
  CPPUNIT_ASSERT(pLayout->getListOfLocalRenderInformationObjects().size() == 1);
  const CLLocalRenderInformation* pRI = pLayout->getListOfLocalRenderInformationObjects()[0];
  CPPUNIT_ASSERT(pRI != NULL);
  CPPUNIT_ASSERT(pRI->getListOfColorDefinitions()->size() == 2);
}

// tests whether we are importing global render information
void test000097::test_import_global_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // import the file and check if we find the
  // global render information
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(SBML_MODEL_2));
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  const CListOfLayouts* pLayouts = pDataModel->getListOfLayouts();
  CPPUNIT_ASSERT(pLayouts != NULL);
  CPPUNIT_ASSERT(pLayouts->size() == 1);
  CPPUNIT_ASSERT(pLayouts->getListOfGlobalRenderInformationObjects().size() == 1);
  const CLGlobalRenderInformation* pRI = pLayouts->getListOfGlobalRenderInformationObjects()[0];
  CPPUNIT_ASSERT(pRI != NULL);
  CPPUNIT_ASSERT(pRI->getListOfColorDefinitions()->size() == 2);
}

// tests whether we are exporting local render information
void test000097::test_export_local_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // create a model with local render information and export it
  this->createModel();
  this->addLocalRenderInformation();
  // to an SBML string.
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::string s;

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!s.empty());
  XMLInputStream inputstream(s.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pModelNode = NULL;
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoLRINode = NULL;
  const XMLNode* pLRINode = NULL;
  const XMLNode* pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "model")
        {
          pModelNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pModelNode != NULL);
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfLayouts")
        {
          pListOfLayoutsNode = &pAnnotationNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the layout node should have an annotation node
  pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pLayoutNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pLayoutNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  // the annotation node should have an listOfRenderInformation node
  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfRenderInformation")
        {
          pLoLRINode = &pAnnotationNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLoLRINode != NULL);
  iMax = pLoLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoLRINode->getChild(i).getName() == "renderInformation")
        {
          pLRINode = &pLoLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLRINode != NULL);
  iMax = pLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pLRINode->getChild(i).getName() == "listOfColorDefinitions")
        {
          pLoCDNode = &pLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "colorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// tests whether we are exporting global render information
void test000097::test_export_global_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // create a model with local render infromation and export it
  this->createModel();
  this->addGlobalRenderInformation();
  // to an SBML string.
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::string s;

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!s.empty());
  XMLInputStream inputstream(s.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pModelNode = NULL;
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoGRINode = NULL;
  const XMLNode* pGRINode = NULL;
  const XMLNode* pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "model")
        {
          pModelNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pModelNode != NULL);
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfLayouts")
        {
          pListOfLayoutsNode = &pAnnotationNode->getChild(i);
          break;
        }
      else if (pAnnotationNode->getChild(i).getName() == "listOfGlobalRenderInformation")
        {
          pLoGRINode = &pAnnotationNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
        }
      else if (pListOfLayoutsNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pListOfLayoutsNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfGlobalRenderInformation")
        {
          pLoGRINode = &pAnnotationNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoGRINode != NULL);
  iMax = pLoGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoGRINode->getChild(i).getName() == "renderInformation")
        {
          pGRINode = &pLoGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pGRINode != NULL);
  iMax = pGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pGRINode->getChild(i).getName() == "listOfColorDefinitions")
        {
          pLoCDNode = &pGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "colorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// tests whether we are saving local render information
void test000097::test_save_local_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // create a model with local render infromation and export it
  this->createModel();
  this->addLocalRenderInformation();
  // to an SBML string.
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::ostringstream os;
  save_cps_model_to_stream(os, pDataModel);
  CPPUNIT_ASSERT(!os.str().empty());
  XMLInputStream inputstream(os.str().c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "COPASI");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoLRINode = NULL;
  const XMLNode* pLRINode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "ListOfLayouts")
        {
          pListOfLayoutsNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "Layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLayoutNode->getChild(i).getName() == "ListOfRenderInformation")
        {
          pLoLRINode = &pLayoutNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoLRINode != NULL);
  iMax = pLoLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoLRINode->getChild(i).getName() == "RenderInformation")
        {
          pLRINode = &pLoLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLRINode != NULL);
  iMax = pLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pLRINode->getChild(i).getName() == "ListOfColorDefinitions")
        {
          pLoCDNode = &pLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "ColorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// tests whether we are saving global render information
void test000097::test_save_global_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // create a model with local render infromation and export it
  this->createModel();
  this->addGlobalRenderInformation();
  // to an SBML string.
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::ostringstream os;
  save_cps_model_to_stream(os, pDataModel);
  CPPUNIT_ASSERT(!os.str().empty());
  XMLInputStream inputstream(os.str().c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "COPASI");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoGRINode = NULL;
  const XMLNode* pGRINode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "ListOfLayouts")
        {
          pListOfLayoutsNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "Layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
        }
      else if (pListOfLayoutsNode->getChild(i).getName() == "ListOfGlobalRenderInformation")
        {
          pLoGRINode = &pListOfLayoutsNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  CPPUNIT_ASSERT(pLoGRINode != NULL);
  iMax = pLoGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoGRINode->getChild(i).getName() == "RenderInformation")
        {
          pGRINode = &pLoGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pGRINode != NULL);
  iMax = pGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pGRINode->getChild(i).getName() == "ListOfColorDefinitions")
        {
          pLoCDNode = &pGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "ColorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// test whether we are reading local render information
void test000097::test_read_local_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  std::istringstream iss(test000097::CPS_MODEL_1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  const CLayout* pLayout = (*pDataModel->getListOfLayouts())[0];
  CPPUNIT_ASSERT(pLayout != NULL);
  CPPUNIT_ASSERT(pLayout->getListOfLocalRenderInformationObjects().size() == 1);
  const CLLocalRenderInformation* pRI = pLayout->getListOfLocalRenderInformationObjects()[0];
  CPPUNIT_ASSERT(pRI != NULL);
  CPPUNIT_ASSERT(pRI->getListOfColorDefinitions()->size() == 2);
}

// test whether we are reading global render information
void test000097::test_read_global_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  std::istringstream iss(test000097::CPS_MODEL_2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  const CListOfLayouts* pLayouts = pDataModel->getListOfLayouts();
  CPPUNIT_ASSERT(pLayouts != NULL);
  CPPUNIT_ASSERT(pLayouts->size() == 1);
  CPPUNIT_ASSERT(pLayouts->getListOfGlobalRenderInformationObjects().size() == 1);
  const CLGlobalRenderInformation* pRI = pLayouts->getListOfGlobalRenderInformationObjects()[0];
  CPPUNIT_ASSERT(pRI != NULL);
  CPPUNIT_ASSERT(pRI->getListOfColorDefinitions()->size() == 2);
}

// method the create a model with a single compartment
// and a small layout
void test000097::createModel()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // get the model from the datamodel
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  pModel->setTimeUnit(CUnit::s);
  pModel->setVolumeUnit(CUnit::microl);
  pModel->setQuantityUnit(CUnit::nMol);

  // add a compartment
  std::set<const CDataObject*> changedObjects;
  CCompartment* pCompartment = pModel->createCompartment("cell", 5.0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  const CDataObject* pObject = pCompartment->getInitialValueReference();
  CPPUNIT_ASSERT(pObject != NULL);
  changedObjects.insert(pObject);

  // finally compile the model
  // compile needs to be done before updating all initial values for
  // the model with the refresh sequence
  pModel->compileIfNecessary(NULL);

  // now that we are done building the model, we have to make sure all
  // initial values are updated according to their dependencies
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator it2 = refreshes.begin(), endit2 = refreshes.end();

  while (it2 != endit2)
    {
      // call each refresh
      (**it2)();
      ++it2;
    }

  // add a layout
  CLayout* pLayout = new CLayout();
  pLayout->setDimensions(CLDimensions(100.0, 100.0));
  // with a compartment glyph
  CLCompartmentGlyph* pGlyph = new CLCompartmentGlyph();
  pGlyph->setModelObjectKey(pCompartment->getKey());
  pGlyph->setBoundingBox(CLBoundingBox(CLPoint(20.0, 20.0), CLDimensions(60.0, 60.0)));
  pLayout->addCompartmentGlyph(pGlyph);
  // the map is not used right now so we pass an empty map
  pDataModel->getListOfLayouts()->addLayout(pLayout, std::map<std::string, std::string>());
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  CPPUNIT_ASSERT((*pDataModel->getListOfLayouts())[0]->getListOfCompartmentGlyphs().size() == 1);
}

// method to add a local render information object
// to the given model
void test000097::addLocalRenderInformation()
{
  CLLocalRenderInformation* pLRI = new CLLocalRenderInformation();
  CPPUNIT_ASSERT(pLRI != NULL);
  pLRI->setName("my_local_render_info");
  CLColorDefinition* pCDef = pLRI->createColorDefinition();
  CPPUNIT_ASSERT(pCDef != NULL);
  pCDef->setId("black");
  pCDef->setRGBA(0, 0, 0, 255);
  pCDef = pLRI->createColorDefinition();
  CPPUNIT_ASSERT(pCDef != NULL);
  pCDef->setId("red");
  pCDef->setRGBA(255, 0, 0, 255);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  CLayout* pLayout = (*pDataModel->getListOfLayouts())[0];
  CPPUNIT_ASSERT(pLayout != NULL);
  pLayout->addLocalRenderInformation(pLRI);
  CPPUNIT_ASSERT(pLayout->getListOfLocalRenderInformationObjects().size() == 1);
  CPPUNIT_ASSERT(pLayout->getListOfLocalRenderInformationObjects()[0]->getListOfColorDefinitions()->size() == 2);
}

// method to add a global render information object
// to the given model
void test000097::addGlobalRenderInformation()
{
  CLGlobalRenderInformation* pGRI = new CLGlobalRenderInformation();
  CPPUNIT_ASSERT(pGRI != NULL);
  pGRI->setName("my_global_render_info");
  CLColorDefinition* pCDef = pGRI->createColorDefinition();
  CPPUNIT_ASSERT(pCDef != NULL);
  pCDef->setId("black");
  pCDef->setRGBA(0, 0, 0, 255);
  pCDef = pGRI->createColorDefinition();
  CPPUNIT_ASSERT(pCDef != NULL);
  pCDef->setId("red");
  pCDef->setRGBA(255, 0, 0, 255);
  pDataModel->getListOfLayouts()->addGlobalRenderInformation(pGRI);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects().size() == 1);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->getListOfGlobalRenderInformationObjects()[0]->getListOfColorDefinitions()->size() == 2);
}

// SBML model with local render information
const char* test000097::SBML_MODEL_1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"TestModel\">\n"
  "    <annotation>\n"
  "      <listOfLayouts xmlns=\"http://projects.eml.org/bcb/sbml/level2\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
  "          <layout id=\"Layout_1\">\n"
  "          <annotation>\n"
  "            <listOfRenderInformation xmlns=\"http://projects.eml.org/bcb/sbml/render/level2\">\n"
  "              <renderInformation id=\"highlightGlucose\" programName=\"Ralph Gauges\" programVersion=\"1.0\">\n"
  "                <listOfColorDefinitions>\n"
  "                  <colorDefinition id=\"lightRed\" value=\"#E6ADD8\"/>\n"
  "                  <colorDefinition id=\"white\" value=\"#FFFFFF\"/>\n"
  "                </listOfColorDefinitions>\n"
  "              </renderInformation>\n"
  "            </listOfRenderInformation>\n"
  "          </annotation>\n"
  "          <dimensions width=\"400\" height=\"230\"/>\n"
  "          <listOfCompartmentGlyphs>\n"
  "              <compartmentGlyph id=\"CompartmentGlyph_1\" compartment=\"Yeast\">\n"
  "              <boundingBox id=\"bb1\">\n"
  "                  <position x=\"5\" y=\"5\"/>\n"
  "                  <dimensions width=\"390\" height=\"220\"/>\n"
  "              </boundingBox>\n"
  "              </compartmentGlyph>\n"
  "          </listOfCompartmentGlyphs>\n"
  "          </layout>\n"
  "      </listOfLayouts>\n"
  "    </annotation>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"Yeast\" size=\"1\" />\n"
  "    </listOfCompartments>\n"
  "  </model>\n"
  "</sbml>\n"
  ;

// SBML model with global render information
const char* test000097::SBML_MODEL_2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" level=\"2\" version=\"1\">\n"
  "  <model id=\"TestModel\">\n"
  "    <annotation>\n"
  "      <listOfLayouts xmlns=\"http://projects.eml.org/bcb/sbml/level2\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
  "          <annotation>\n"
  "            <listOfGlobalRenderInformation xmlns=\"http://projects.eml.org/bcb/sbml/render/level2\">\n"
  "              <renderInformation id=\"wireFrame\" name=\"wireframe style\" programName=\"Ralph Gauges\" programVersion=\"1.0\">\n"
  "                <listOfColorDefinitions>\n"
  "                  <colorDefinition id=\"white\" value=\"#FFFFFF\"/>\n"
  "                  <colorDefinition id=\"black\" value=\"#000000\"/>\n"
  "                </listOfColorDefinitions>\n"
  "              </renderInformation>\n"
  "            </listOfGlobalRenderInformation>\n"
  "          </annotation>\n"
  "          <layout id=\"Layout_1\">\n"
  "          <dimensions width=\"400\" height=\"230\"/>\n"
  "          <listOfCompartmentGlyphs>\n"
  "              <compartmentGlyph id=\"CompartmentGlyph_1\" compartment=\"Yeast\">\n"
  "              <boundingBox id=\"bb1\">\n"
  "                  <position x=\"5\" y=\"5\"/>\n"
  "                  <dimensions width=\"390\" height=\"220\"/>\n"
  "              </boundingBox>\n"
  "              </compartmentGlyph>\n"
  "          </listOfCompartmentGlyphs>\n"
  "          </layout>\n"
  "      </listOfLayouts>\n"
  "    </annotation>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"Yeast\" size=\"1\" />\n"
  "    </listOfCompartments>\n"
  "  </model>\n"
  "</sbml>\n"
  ;

// COPASI model with local render information
const char* test000097::CPS_MODEL_1 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.6.34 (Debug) (http://www.copasi.org) at 2011-04-22 10:08:31 UTC -->\n"
  "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
  "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"34\">\n"
  "  <Model key=\"Model_1\" name=\"NoName\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"l\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mol\" type=\"deterministic\" avogadroConstant=\"6.02214179e+23\">\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"Yeast\" simulationType=\"fixed\" dimensionality=\"3\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1 \n"
  "    </InitialState>\n"
  "  </Model>\n"
  "  <ListOfLayouts xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
  "    <Layout key=\"Layout_2\" name=\"Layout_1\">\n"
  "      <Dimensions width=\"400\" height=\"230\"/>\n"
  "      <ListOfCompartmentGlyphs>\n"
  "        <CompartmentGlyph key=\"Layout_3\" name=\"CompartmentGlyph_1\" compartment=\"Compartment_0\">\n"
  "          <BoundingBox>\n"
  "            <Position x=\"5\" y=\"5\"/>\n"
  "            <Dimensions width=\"390\" height=\"220\"/>\n"
  "          </BoundingBox>\n"
  "        </CompartmentGlyph>\n"
  "      </ListOfCompartmentGlyphs>\n"
  "      <ListOfRenderInformation>\n"
  "        <RenderInformation key=\"LocalRenderInformation_0\" backgroundColor=\"#FFFFFFFF\">\n"
  "          <ListOfColorDefinitions>\n"
  "            <ColorDefinition id=\"lightRed\" value=\"#e6add8\"/>\n"
  "            <ColorDefinition id=\"white\" value=\"#ffffff\"/>\n"
  "          </ListOfColorDefinitions>\n"
  "        </RenderInformation>\n"
  "      </ListOfRenderInformation>\n"
  "    </Layout>\n"
  "  </ListOfLayouts>\n"
  "</COPASI>\n"
  ;

// COPASI model with global render information
const char* test000097::CPS_MODEL_2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.6.34 (Debug) (http://www.copasi.org) at 2011-04-22 10:09:16 UTC -->\n"
  "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
  "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"34\">\n"
  "  <Model key=\"Model_1\" name=\"NoName\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"l\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mol\" type=\"deterministic\" avogadroConstant=\"6.02214179e+23\">\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"Yeast\" simulationType=\"fixed\" dimensionality=\"3\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 1 \n"
  "    </InitialState>\n"
  "  </Model>\n"
  "  <ListOfLayouts xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
  "    <Layout key=\"Layout_2\" name=\"Layout_1\">\n"
  "      <Dimensions width=\"400\" height=\"230\"/>\n"
  "      <ListOfCompartmentGlyphs>\n"
  "        <CompartmentGlyph key=\"Layout_3\" name=\"CompartmentGlyph_1\" compartment=\"Compartment_0\">\n"
  "          <BoundingBox>\n"
  "            <Position x=\"5\" y=\"5\"/>\n"
  "            <Dimensions width=\"390\" height=\"220\"/>\n"
  "          </BoundingBox>\n"
  "        </CompartmentGlyph>\n"
  "      </ListOfCompartmentGlyphs>\n"
  "    </Layout>\n"
  "    <ListOfGlobalRenderInformation>\n"
  "      <RenderInformation key=\"GlobalRenderInformation_0\" name=\"wireframe style\" backgroundColor=\"#FFFFFFFF\">\n"
  "        <ListOfColorDefinitions>\n"
  "          <ColorDefinition id=\"white\" value=\"#ffffff\"/>\n"
  "          <ColorDefinition id=\"black\" value=\"#000000\"/>\n"
  "        </ListOfColorDefinitions>\n"
  "      </RenderInformation>\n"
  "    </ListOfGlobalRenderInformation>\n"
  "  </ListOfLayouts>\n"
  "</COPASI>\n"
  ;

// tests whether we are exporting local render information
// that has been read
void test000097::test_readexport_local_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // read a model with local render information and export it
  // to an SBML string.
  std::istringstream iss(test000097::CPS_MODEL_1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::string s;

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!s.empty());
  XMLInputStream inputstream(s.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pModelNode = NULL;
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoLRINode = NULL;
  const XMLNode* pLRINode = NULL;
  const XMLNode* pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "model")
        {
          pModelNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pModelNode != NULL);
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfLayouts")
        {
          pListOfLayoutsNode = &pAnnotationNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the layout node should have an annotation node
  pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pLayoutNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pLayoutNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  // the annotation node should have an listOfRenderInformation node
  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfRenderInformation")
        {
          pLoLRINode = &pAnnotationNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLoLRINode != NULL);
  iMax = pLoLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoLRINode->getChild(i).getName() == "renderInformation")
        {
          pLRINode = &pLoLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLRINode != NULL);
  iMax = pLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pLRINode->getChild(i).getName() == "listOfColorDefinitions")
        {
          pLoCDNode = &pLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "colorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// tests whether we are exporting global render information
// that has been read
void test000097::test_readexport_global_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // read a model with local render infromation and export it
  // to an SBML string.
  std::istringstream iss(test000097::CPS_MODEL_2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::string s;

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!s.empty());
  XMLInputStream inputstream(s.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pModelNode = NULL;
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoGRINode = NULL;
  const XMLNode* pGRINode = NULL;
  const XMLNode* pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "model")
        {
          pModelNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pModelNode != NULL);
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfLayouts")
        {
          pListOfLayoutsNode = &pAnnotationNode->getChild(i);
          break;
        }
      else if (pAnnotationNode->getChild(i).getName() == "listOfGlobalRenderInformation")
        {
          pLoGRINode = &pAnnotationNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
        }
      else if (pListOfLayoutsNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pListOfLayoutsNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfGlobalRenderInformation")
        {
          pLoGRINode = &pAnnotationNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoGRINode != NULL);
  iMax = pLoGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoGRINode->getChild(i).getName() == "renderInformation")
        {
          pGRINode = &pLoGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pGRINode != NULL);
  iMax = pGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pGRINode->getChild(i).getName() == "listOfColorDefinitions")
        {
          pLoCDNode = &pGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "colorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// tests whether we are exporting local render information
// that has been import
void test000097::test_importexport_local_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // import a model with local render information and export it
  // to an SBML string.
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(SBML_MODEL_1));
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::string s;

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!s.empty());
  XMLInputStream inputstream(s.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pModelNode = NULL;
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoLRINode = NULL;
  const XMLNode* pLRINode = NULL;
  const XMLNode* pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "model")
        {
          pModelNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pModelNode != NULL);
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfLayouts")
        {
          pListOfLayoutsNode = &pAnnotationNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the layout node should have an annotation node
  pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pLayoutNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pLayoutNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  // the annotation node should have an listOfRenderInformation node
  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfRenderInformation")
        {
          pLoLRINode = &pAnnotationNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLoLRINode != NULL);
  iMax = pLoLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoLRINode->getChild(i).getName() == "renderInformation")
        {
          pLRINode = &pLoLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLRINode != NULL);
  iMax = pLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pLRINode->getChild(i).getName() == "listOfColorDefinitions")
        {
          pLoCDNode = &pLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "colorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// tests whether we are exporting global render information
// that has been import
void test000097::test_importexport_global_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // import a model with global render infromation and export it
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(SBML_MODEL_2));
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  // to an SBML string.
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::string s;

  try
    {
      s = pDataModel->exportSBMLToString(NULL, 2, 1);
    }
  catch (...)
    {
      CPPUNIT_ASSERT(false);
    }

  CPPUNIT_ASSERT(!s.empty());
  XMLInputStream inputstream(s.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pModelNode = NULL;
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoGRINode = NULL;
  const XMLNode* pGRINode = NULL;
  const XMLNode* pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "model")
        {
          pModelNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pModelNode != NULL);
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfLayouts")
        {
          pListOfLayoutsNode = &pAnnotationNode->getChild(i);
          break;
        }
      else if (pAnnotationNode->getChild(i).getName() == "listOfGlobalRenderInformation")
        {
          pLoGRINode = &pAnnotationNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  pAnnotationNode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
        }
      else if (pListOfLayoutsNode->getChild(i).getName() == "annotation")
        {
          pAnnotationNode = &pListOfLayoutsNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  CPPUNIT_ASSERT(pAnnotationNode != NULL);
  iMax = pAnnotationNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pAnnotationNode->getChild(i).getName() == "listOfGlobalRenderInformation")
        {
          pLoGRINode = &pAnnotationNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoGRINode != NULL);
  iMax = pLoGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoGRINode->getChild(i).getName() == "renderInformation")
        {
          pGRINode = &pLoGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pGRINode != NULL);
  iMax = pGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pGRINode->getChild(i).getName() == "listOfColorDefinitions")
        {
          pLoCDNode = &pGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "colorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// test whether we are writing local render information
// that has been read
void test000097::test_readwrite_local_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // create a model with local render infromation and export it
  std::istringstream iss(test000097::CPS_MODEL_1);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  // to an SBML string.
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::ostringstream os;
  save_cps_model_to_stream(os, pDataModel);
  CPPUNIT_ASSERT(!os.str().empty());
  XMLInputStream inputstream(os.str().c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "COPASI");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoLRINode = NULL;
  const XMLNode* pLRINode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "ListOfLayouts")
        {
          pListOfLayoutsNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "Layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLayoutNode->getChild(i).getName() == "ListOfRenderInformation")
        {
          pLoLRINode = &pLayoutNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoLRINode != NULL);
  iMax = pLoLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoLRINode->getChild(i).getName() == "RenderInformation")
        {
          pLRINode = &pLoLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLRINode != NULL);
  iMax = pLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pLRINode->getChild(i).getName() == "ListOfColorDefinitions")
        {
          pLoCDNode = &pLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "ColorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// test whether we are writing global render information
// that has been read
void test000097::test_readwrite_global_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // create a model with local render infromation and export it
  std::istringstream iss(test000097::CPS_MODEL_2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  // to an SBML string.
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::ostringstream os;
  save_cps_model_to_stream(os, pDataModel);
  CPPUNIT_ASSERT(!os.str().empty());
  XMLInputStream inputstream(os.str().c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "COPASI");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoGRINode = NULL;
  const XMLNode* pGRINode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "ListOfLayouts")
        {
          pListOfLayoutsNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "Layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
        }
      else if (pListOfLayoutsNode->getChild(i).getName() == "ListOfGlobalRenderInformation")
        {
          pLoGRINode = &pListOfLayoutsNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  CPPUNIT_ASSERT(pLoGRINode != NULL);
  iMax = pLoGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoGRINode->getChild(i).getName() == "RenderInformation")
        {
          pGRINode = &pLoGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pGRINode != NULL);
  iMax = pGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pGRINode->getChild(i).getName() == "ListOfColorDefinitions")
        {
          pLoCDNode = &pGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "ColorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// test whether we are writing local render information
// that has been imported
void test000097::test_importwrite_local_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // create a model with local render infromation and export it
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(SBML_MODEL_1));
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  // to an SBML string.
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::ostringstream os;
  save_cps_model_to_stream(os, pDataModel);
  CPPUNIT_ASSERT(!os.str().empty());
  XMLInputStream inputstream(os.str().c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "COPASI");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoLRINode = NULL;
  const XMLNode* pLRINode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "ListOfLayouts")
        {
          pListOfLayoutsNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "Layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLayoutNode->getChild(i).getName() == "ListOfRenderInformation")
        {
          pLoLRINode = &pLayoutNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoLRINode != NULL);
  iMax = pLoLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoLRINode->getChild(i).getName() == "RenderInformation")
        {
          pLRINode = &pLoLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLRINode != NULL);
  iMax = pLRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pLRINode->getChild(i).getName() == "ListOfColorDefinitions")
        {
          pLoCDNode = &pLRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "ColorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}

// test whether we are writing global render information
// that has been importer
void test000097::test_importwrite_global_render_information()
{
  CPPUNIT_ASSERT(pDataModel != NULL);
  // create a model with local render infromation and export it
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(SBML_MODEL_2));
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts() != NULL);
  CPPUNIT_ASSERT(pDataModel->getListOfLayouts()->size() == 1);
  // to an SBML string.
  // Use the XMLNode class to read back the string into an
  // XMLNode tree and check if it contains the render information
  std::ostringstream os;
  save_cps_model_to_stream(os, pDataModel);
  CPPUNIT_ASSERT(!os.str().empty());
  XMLInputStream inputstream(os.str().c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "COPASI");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pListOfLayoutsNode = NULL;
  const XMLNode* pLayoutNode = NULL;
  const XMLNode* pLoGRINode = NULL;
  const XMLNode* pGRINode = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (node.getChild(i).getName() == "ListOfLayouts")
        {
          pListOfLayoutsNode = &node.getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfLayoutsNode != NULL);
  iMax = pListOfLayoutsNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pListOfLayoutsNode->getChild(i).getName() == "Layout")
        {
          pLayoutNode = &pListOfLayoutsNode->getChild(i);
        }
      else if (pListOfLayoutsNode->getChild(i).getName() == "ListOfGlobalRenderInformation")
        {
          pLoGRINode = &pListOfLayoutsNode->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pLayoutNode != NULL);
  iMax = pLayoutNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  CPPUNIT_ASSERT(pLoGRINode != NULL);
  iMax = pLoGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoGRINode->getChild(i).getName() == "RenderInformation")
        {
          pGRINode = &pLoGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pGRINode != NULL);
  iMax = pGRINode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  const XMLNode* pLoCDNode = NULL;
  const XMLNode* pCDNode1 = NULL;
  const XMLNode* pCDNode2 = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pGRINode->getChild(i).getName() == "ListOfColorDefinitions")
        {
          pLoCDNode = &pGRINode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pLoCDNode != NULL);
  iMax = pLoCDNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (i = 0; i < iMax; ++i)
    {
      if (pLoCDNode->getChild(i).getName() == "ColorDefinition")
        {
          if (pCDNode1 == NULL)
            {
              pCDNode1 = &pLoCDNode->getChild(i);
            }
          else
            {
              pCDNode2 = &pLoCDNode->getChild(i);
            }
        }
    }

  CPPUNIT_ASSERT(pCDNode1 != NULL);
  CPPUNIT_ASSERT(pCDNode2 != NULL);
}
