// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/MIRIAM/CRDFGraphConverter.h"
#include "copasi/MIRIAM/CModified.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"

#include <sbml/SBMLDocument.h>
#include <sbml/Model.h>
#include <sbml/Compartment.h>
#include <sbml/annotation/CVTerm.h>
#include <sbml/annotation/ModelHistory.h>
#include <sbml/xml/XMLNode.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLNamespaces.h>

#include "copasi/core/CRootContainer.h"

#include "test000092.h"

CDataModel* test000092::pCOPASIDATAMODEL = NULL;

void test000092::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000092::tearDown()
{
  CRootContainer::destroy();
}

void test000092::test_miriam_export_1()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000092::MODEL_STRING1);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  std::string content = pDataModel->exportSBMLToString(NULL, 2, 4);
  CPPUNIT_ASSERT(content.empty() == false);
  // now we convert the content into an XMLNode and check if everything is there that needs to be there
  XMLInputStream inputstream(content.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pModelNode = &node.getChild(0);
  CPPUNIT_ASSERT(pModelNode != NULL);
  CPPUNIT_ASSERT(pModelNode->getName() == "model");
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pModelAnnotation = &pModelNode->getChild(0);
  CPPUNIT_ASSERT(pModelAnnotation != NULL);
  CPPUNIT_ASSERT(pModelAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pModelAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 2);
  const XMLNode* pMIRIAM1 = NULL, *pMIRIAM2 = NULL;
  pMIRIAM1 = &pModelAnnotation->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);

  // make sure the libsbml annotation is stored in pMIRIAM1
  if (pMIRIAM1->getName() != "RDF")
    {
      pMIRIAM2 = pMIRIAM1;
      pMIRIAM1 = &pModelAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM1 != NULL);
      CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
    }
  else
    {
      pMIRIAM2 = &pModelAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM2 != NULL);
      CPPUNIT_ASSERT(pMIRIAM2->getName() == "COPASI");
    }

  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  const XMLNamespaces* ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  int index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // there are actually more namespace attributes in the libsbml annotation, but that is enough to make sure
  // that everything should be OK
  //
  // Right now, we don't care about the content of the annotations as long as they are there
  //
  // Find the compartment node
  iMax = pModelNode->getNumChildren();
  const XMLNode* pListOfCompartments = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "listOfCompartments")
        {
          pListOfCompartments = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfCompartments != NULL);
  iMax = pListOfCompartments->getNumChildren();
  // we have only one compartment
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pCompartment = &pListOfCompartments->getChild(0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getName() == "compartment");
  iMax = pCompartment->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pAnnotation = &pCompartment->getChild(0);
  CPPUNIT_ASSERT(pAnnotation != NULL);
  CPPUNIT_ASSERT(pAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 2);
  pMIRIAM1 = &pAnnotation->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);

  // make sure the libsbml annotation is stored in pMIRIAM1
  if (pMIRIAM1->getName() != "RDF")
    {
      pMIRIAM2 = pMIRIAM1;
      pMIRIAM1 = &pAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM1 != NULL);
      CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
    }
  else
    {
      pMIRIAM2 = &pAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM2 != NULL);
      CPPUNIT_ASSERT(pMIRIAM2->getName() == "COPASI");
    }

  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // try to reimport the stuff to make sure it is valid SBML
  result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
}

void test000092::test_miriam_export_2()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000092::MODEL_STRING2);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  std::string content = pDataModel->exportSBMLToString(NULL, 2, 4);
  CPPUNIT_ASSERT(content.empty() == false);
  // now we convert the content into an XMLNode and check if everything is there that needs to be there
  XMLInputStream inputstream(content.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pModelNode = &node.getChild(0);
  CPPUNIT_ASSERT(pModelNode != NULL);
  CPPUNIT_ASSERT(pModelNode->getName() == "model");
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pModelAnnotation = &pModelNode->getChild(0);
  CPPUNIT_ASSERT(pModelAnnotation != NULL);
  CPPUNIT_ASSERT(pModelAnnotation->getName() == "annotation");
  // since the MIRIAM information is incomplete , we should have one or two children
  // depending on the version of libsbml we are using
  iMax = pModelAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1 || iMax == 2);
  const XMLNode* pMIRIAM1 = NULL, *pMIRIAM2 = NULL;
  pMIRIAM1 = &pModelAnnotation->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);

  // make sure the libsbml annotation is stored in pMIRIAM1
  if (pMIRIAM1->getName() != "RDF")
    {
      pMIRIAM2 = pMIRIAM1;
      pMIRIAM1 = NULL;

      if (iMax == 2)
        {
          pMIRIAM1 = &pModelAnnotation->getChild(1);
          CPPUNIT_ASSERT(pMIRIAM1 != NULL);
          CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
        }
    }
  else
    {
      if (iMax == 2)
        {
          pMIRIAM2 = &pModelAnnotation->getChild(1);
          CPPUNIT_ASSERT(pMIRIAM2 != NULL);
          CPPUNIT_ASSERT(pMIRIAM2->getName() == "COPASI");
        }
    }

  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  const XMLNamespaces* ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  int index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");

  // same checks for the libsbml MIRIAM annotation
  if (pMIRIAM1 != NULL)
    {
      CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
      CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
      ns = &pMIRIAM1->getNamespaces();
      CPPUNIT_ASSERT(ns != NULL);
      index = ns->getIndex("http://purl.org/dc/terms/");
      CPPUNIT_ASSERT(index != -1);
      CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
      index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
      CPPUNIT_ASSERT(index != -1);
      CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
      index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
      CPPUNIT_ASSERT(index != -1);
      CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
    }

  // there are actually more namespace attributes in the libsbml annotation, but that is enough to make sure
  // that everything should be OK
  //
  // Right now, we don't care about the content of the annotations as long as they are there
  //
  // Find the compartment node
  iMax = pModelNode->getNumChildren();
  const XMLNode* pListOfCompartments = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "listOfCompartments")
        {
          pListOfCompartments = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfCompartments != NULL);
  iMax = pListOfCompartments->getNumChildren();
  // we have only one compartment
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pCompartment = &pListOfCompartments->getChild(0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getName() == "compartment");
  iMax = pCompartment->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pAnnotation = &pCompartment->getChild(0);
  CPPUNIT_ASSERT(pAnnotation != NULL);
  CPPUNIT_ASSERT(pAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 2);
  pMIRIAM1 = &pAnnotation->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);

  // make sure the libsbml annotation is stored in pMIRIAM1
  if (pMIRIAM1->getName() != "RDF")
    {
      pMIRIAM2 = pMIRIAM1;
      pMIRIAM1 = &pAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM1 != NULL);
      CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
    }
  else
    {
      pMIRIAM2 = &pAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM2 != NULL);
      CPPUNIT_ASSERT(pMIRIAM2->getName() == "COPASI");
    }

  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // try to reimport the stuff to make sure it is valid SBML
  result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
}

void test000092::test_miriam_export_3()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000092::MODEL_STRING3);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  std::string content = pDataModel->exportSBMLToString(NULL, 2, 4);
  CPPUNIT_ASSERT(content.empty() == false);
  // now we convert the content into an XMLNode and check if everything is there that needs to be there
  XMLInputStream inputstream(content.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pModelNode = &node.getChild(0);
  CPPUNIT_ASSERT(pModelNode != NULL);
  CPPUNIT_ASSERT(pModelNode->getName() == "model");
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  // So since we don't expect any annotations for this model,
  // the first node should not be an annotation node
  const XMLNode* pModelAnnotation = &pModelNode->getChild(0);
  CPPUNIT_ASSERT(pModelAnnotation != NULL);
  CPPUNIT_ASSERT(pModelAnnotation->getName() != "annotation");
  // Find the compartment node
  iMax = pModelNode->getNumChildren();
  const XMLNode* pListOfCompartments = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "listOfCompartments")
        {
          pListOfCompartments = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfCompartments != NULL);
  iMax = pListOfCompartments->getNumChildren();
  // we have only one compartment
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pCompartment = &pListOfCompartments->getChild(0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getName() == "compartment");
  iMax = pCompartment->getNumChildren();
  // there should be no annotation to the compartment
  CPPUNIT_ASSERT(iMax == 0);
  // try to reimport the stuff to make sure it is valid SBML
  result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
}

void test000092::test_miriam_export_4()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000092::MODEL_STRING4);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  std::string content = pDataModel->exportSBMLToString(NULL, 2, 4);
  CPPUNIT_ASSERT(content.empty() == false);
  // now we convert the content into an XMLNode and check if everything is there that needs to be there
  XMLInputStream inputstream(content.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pModelNode = &node.getChild(0);
  CPPUNIT_ASSERT(pModelNode != NULL);
  CPPUNIT_ASSERT(pModelNode->getName() == "model");
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pModelAnnotation = &pModelNode->getChild(0);
  CPPUNIT_ASSERT(pModelAnnotation != NULL);
  CPPUNIT_ASSERT(pModelAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pModelAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 3);
  const XMLNode* pMIRIAM1 = NULL, *pMIRIAM2 = NULL, *pLayout = NULL;

  // make sure the libsbml annotation is stored in pMIRIAM1
  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pModelAnnotation->getChild(i).getName() == "COPASI")
        {
          pMIRIAM2 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "RDF")
        {
          pMIRIAM1 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "listOfLayouts")
        {
          pLayout = &pModelAnnotation->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pLayout != NULL);
  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  const XMLNamespaces* ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  int index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // there are actually more namespace attributes in the libsbml annotation, but that is enough to make sure
  // that everything should be OK
  //
  // Right now, we don't care about the content of the annotations as long as they are there
  //
  // Find the compartment node
  iMax = pModelNode->getNumChildren();
  const XMLNode* pListOfCompartments = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "listOfCompartments")
        {
          pListOfCompartments = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfCompartments != NULL);
  iMax = pListOfCompartments->getNumChildren();
  // we have only one compartment
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pCompartment = &pListOfCompartments->getChild(0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getName() == "compartment");
  iMax = pCompartment->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pAnnotation = &pCompartment->getChild(0);
  CPPUNIT_ASSERT(pAnnotation != NULL);
  CPPUNIT_ASSERT(pAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 2);
  pMIRIAM1 = NULL;
  pMIRIAM2 = NULL;
  pMIRIAM1 = &pAnnotation->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);

  // make sure the libsbml annotation is stored in pMIRIAM1
  if (pMIRIAM1->getName() != "RDF")
    {
      pMIRIAM2 = pMIRIAM1;
      pMIRIAM1 = &pAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM1 != NULL);
      CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
    }
  else
    {
      pMIRIAM2 = &pAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM2 != NULL);
      CPPUNIT_ASSERT(pMIRIAM2->getName() == "COPASI");
    }

  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // try to reimport the stuff to make sure it is valid SBML
  result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
}

void test000092::test_miriam_export_5()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000092::MODEL_STRING5);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  std::string content = pDataModel->exportSBMLToString(NULL, 2, 4);
  CPPUNIT_ASSERT(content.empty() == false);
  // now we convert the content into an XMLNode and check if everything is there that needs to be there
  XMLInputStream inputstream(content.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pModelNode = &node.getChild(0);
  CPPUNIT_ASSERT(pModelNode != NULL);
  CPPUNIT_ASSERT(pModelNode->getName() == "model");
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pModelAnnotation = &pModelNode->getChild(0);
  CPPUNIT_ASSERT(pModelAnnotation != NULL);
  CPPUNIT_ASSERT(pModelAnnotation->getName() == "annotation");
  // since the MIRIAM information is incomplete , we should have one or two children
  // depending on the version of libsbml we are using
  iMax = pModelAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 2 || iMax == 3);
  const XMLNode* pMIRIAM1 = NULL, *pMIRIAM2 = NULL, *pLayout;

  for (unsigned i = 0; i < iMax; ++i)
    {
      if (pModelAnnotation->getChild(i).getName() == "COPASI")
        {
          pMIRIAM2 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "RDF")
        {
          pMIRIAM1 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "listOfLayouts")
        {
          pLayout = &pModelAnnotation->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pLayout != NULL);

  if (iMax == 3)
    {
      CPPUNIT_ASSERT(pMIRIAM1 != NULL);
    }

  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  const XMLNamespaces* ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  int index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");

  // same checks for the libsbml MIRIAM annotation
  if (pMIRIAM1 != NULL)
    {
      CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
      CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
      ns = &pMIRIAM1->getNamespaces();
      CPPUNIT_ASSERT(ns != NULL);
      index = ns->getIndex("http://purl.org/dc/terms/");
      CPPUNIT_ASSERT(index != -1);
      CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
      index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
      CPPUNIT_ASSERT(index != -1);
      CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
      index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
      CPPUNIT_ASSERT(index != -1);
      CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
    }

  // there are actually more namespace attributes in the libsbml annotation, but that is enough to make sure
  // that everything should be OK
  //
  // Right now, we don't care about the content of the annotations as long as they are there
  //
  // Find the compartment node
  iMax = pModelNode->getNumChildren();
  const XMLNode* pListOfCompartments = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "listOfCompartments")
        {
          pListOfCompartments = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfCompartments != NULL);
  iMax = pListOfCompartments->getNumChildren();
  // we have only one compartment
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pCompartment = &pListOfCompartments->getChild(0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getName() == "compartment");
  iMax = pCompartment->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pAnnotation = &pCompartment->getChild(0);
  CPPUNIT_ASSERT(pAnnotation != NULL);
  CPPUNIT_ASSERT(pAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 2);
  pMIRIAM1 = NULL;
  pMIRIAM2 = NULL;
  pMIRIAM1 = &pAnnotation->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);

  // make sure the libsbml annotation is stored in pMIRIAM1
  if (pMIRIAM1->getName() != "RDF")
    {
      pMIRIAM2 = pMIRIAM1;
      pMIRIAM1 = &pAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM1 != NULL);
      CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
    }
  else
    {
      pMIRIAM2 = &pAnnotation->getChild(1);
      CPPUNIT_ASSERT(pMIRIAM2 != NULL);
      CPPUNIT_ASSERT(pMIRIAM2->getName() == "COPASI");
    }

  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // try to reimport the stuff to make sure it is valid SBML
  result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
}

void test000092::test_miriam_export_6()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000092::MODEL_STRING6);
  bool result = load_cps_model_from_stream(iss, *pDataModel);
  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  std::string content = pDataModel->exportSBMLToString(NULL, 2, 4);
  CPPUNIT_ASSERT(content.empty() == false);
  // now we convert the content into an XMLNode and check if everything is there that needs to be there
  XMLInputStream inputstream(content.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pModelNode = &node.getChild(0);
  CPPUNIT_ASSERT(pModelNode != NULL);
  CPPUNIT_ASSERT(pModelNode->getName() == "model");
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pModelAnnotation = &pModelNode->getChild(0);
  CPPUNIT_ASSERT(pModelAnnotation != NULL);
  CPPUNIT_ASSERT(pModelAnnotation->getName() == "annotation");
  CPPUNIT_ASSERT(pModelAnnotation->getNumChildren() == 1);
  CPPUNIT_ASSERT(pModelAnnotation->getChild(0).getName() == "listOfLayouts");
  // Find the compartment node
  iMax = pModelNode->getNumChildren();
  const XMLNode* pListOfCompartments = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "listOfCompartments")
        {
          pListOfCompartments = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfCompartments != NULL);
  iMax = pListOfCompartments->getNumChildren();
  // we have only one compartment
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pCompartment = &pListOfCompartments->getChild(0);
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getName() == "compartment");
  iMax = pCompartment->getNumChildren();
  // there should be no annotation to the compartment
  CPPUNIT_ASSERT(iMax == 0);
  // try to reimport the stuff to make sure it is valid SBML
  result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
}

void test000092::test_miriam_export_7()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  bool result = pDataModel->importSBMLFromString(test000092::MODEL_STRING7);
  CPPUNIT_ASSERT(result == true);
  CModel *pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // now we have to add some miriam annotation to the model
  std::string miriamString = \
                             "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                             "      <rdf:Description rdf:about=\"#COPASI1\">\n"
                             "        <dc:creator rdf:parseType=\"Resource\">\n"
                             "          <rdf:Bag>\n"
                             "            <rdf:li rdf:parseType=\"Resource\">\n"
                             "              <vCard:N rdf:parseType=\"Resource\">\n"
                             "                <vCard:Family>Gauges</vCard:Family>\n"
                             "                <vCard:Given>Ralph</vCard:Given>\n"
                             "              </vCard:N>\n"
                             "            </rdf:li>\n"
                             "          </rdf:Bag>\n"
                             "        </dc:creator>\n"
                             "        <dcterms:created rdf:parseType=\"Resource\">\n"
                             "          <dcterms:W3CDTF>2005-02-02T14:56:11Z</dcterms:W3CDTF>\n"
                             "        </dcterms:created>\n"
                             "        <dcterms:modified rdf:parseType=\"Resource\">\n"
                             "          <dcterms:W3CDTF>2009-06-05T11:40:04Z</dcterms:W3CDTF>\n"
                             "        </dcterms:modified>\n"
                             "      </rdf:Description>\n"
                             "    </rdf:RDF>\n";
  const SBMLDocument* pSBMLDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pSBMLDocument != NULL);
  const Model* pSBMLModel = pDataModel->getCurrentSBMLDocument()->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->isSetMetaId() == true);
  CRDFGraphConverter::SBML2Copasi(miriamString);
  pModel->setMiriamAnnotation(miriamString, pModel->getKey(), pSBMLModel->getMetaId());
  // set some MIRIAM annotation on the compartment as well
  miriamString = \
                 "        <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                 "          <rdf:Description rdf:about=\"#COPASI2\">\n"
                 "            <bqbiol:is>\n"
                 "              <rdf:Bag>\n"
                 "                <rdf:li rdf:resource=\"urn:miriam:obo.go:GO%3A0031594\"/>\n"
                 "              </rdf:Bag>\n"
                 "            </bqbiol:is>\n"
                 "          </rdf:Description>\n"
                 "        </rdf:RDF>\n";
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  const Compartment* pSBMLCompartment = pSBMLModel->getCompartment(0);
  CPPUNIT_ASSERT(pSBMLCompartment != NULL);
  CPPUNIT_ASSERT(pSBMLCompartment->isSetMetaId() == true);
  CRDFGraphConverter::SBML2Copasi(miriamString);
  pCompartment->setMiriamAnnotation(miriamString, pCompartment->getKey(), pSBMLCompartment->getMetaId());
  //
  std::string content = pDataModel->exportSBMLToString(NULL, 2, 4);
  CPPUNIT_ASSERT(content.empty() == false);
  // now we convert the content into an XMLNode and check if everything is there that needs to be there
  XMLInputStream inputstream(content.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pModelNode = &node.getChild(0);
  CPPUNIT_ASSERT(pModelNode != NULL);
  CPPUNIT_ASSERT(pModelNode->getName() == "model");
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pModelAnnotation = &pModelNode->getChild(0);
  CPPUNIT_ASSERT(pModelAnnotation != NULL);
  CPPUNIT_ASSERT(pModelAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pModelAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 3);
  const XMLNode* pMIRIAM1 = NULL, *pMIRIAM2 = NULL, *pOther = NULL;

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pModelAnnotation->getChild(i).getName() == "RDF")
        {
          pMIRIAM1 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "COPASI")
        {
          pMIRIAM2 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "SOMEANNOTATION")
        {
          pOther = &pModelAnnotation->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pOther != NULL);
  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  const XMLNamespaces* ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  int index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // there are actually more namespace attributes in the libsbml annotation, but that is enough to make sure
  // that everything should be OK
  //
  // Right now, we don't care about the content of the annotations as long as they are there
  //
  // Find the compartment node
  iMax = pModelNode->getNumChildren();
  const XMLNode* pListOfCompartments = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "listOfCompartments")
        {
          pListOfCompartments = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfCompartments != NULL);
  iMax = pListOfCompartments->getNumChildren();
  // we have only one compartment
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pCompartmentNode = &pListOfCompartments->getChild(0);
  CPPUNIT_ASSERT(pCompartmentNode != NULL);
  CPPUNIT_ASSERT(pCompartmentNode->getName() == "compartment");
  iMax = pCompartmentNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pAnnotation = &pCompartmentNode->getChild(0);
  CPPUNIT_ASSERT(pAnnotation != NULL);
  CPPUNIT_ASSERT(pAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 3);
  pMIRIAM1 = NULL;
  pMIRIAM2 = NULL;
  pOther = NULL;

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pAnnotation->getChild(i).getName() == "RDF")
        {
          pMIRIAM1 = &pAnnotation->getChild(i);
        }
      else if (pAnnotation->getChild(i).getName() == "COPASI")
        {
          pMIRIAM2 = &pAnnotation->getChild(i);
        }
      else if (pAnnotation->getChild(i).getName() == "SOMEANNOTATION")
        {
          pOther = &pAnnotation->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pOther != NULL);
  // check if the top level element for the COPASI annotation
  // has all necessary namespaces
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // try to reimport the stuff to make sure it is valid SBML
  result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
}

void test000092::test_miriam_export_8()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  bool result = pDataModel->importSBMLFromString(test000092::MODEL_STRING8);
  CPPUNIT_ASSERT(result == true);
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // we need to modify the imported MIRIAM annotation,
  // e.g. the add a modified date
  std::string miriamString = pModel->getMiriamAnnotation();
  CPPUNIT_ASSERT(!miriamString.empty());
  CMIRIAMInfo miriamInfo;
  miriamInfo.load(pModel->getKey());
  // check the modified date
  const CDataVector<CModification>* pModifications = &miriamInfo.getModifications();
  CPPUNIT_ASSERT(pModifications != NULL);
  // there should be only one modification date
  CPPUNIT_ASSERT(pModifications->size() == 1);
  const CModification* pModification = (*pModifications)[0];
  CPPUNIT_ASSERT(pModification != NULL);
  std::string dateTime = pModification->getDate();
  CPPUNIT_ASSERT(dateTime == "2007-06-05T11:40:04Z");
  // now we add a new modification date
  dateTime = "2008-06-05T11:40:04Z";
  CModification* pNewModification = miriamInfo.createModification(dateTime);
  CPPUNIT_ASSERT(pNewModification != NULL);
  CPPUNIT_ASSERT(pNewModification->getDate() == dateTime);
  CPPUNIT_ASSERT(miriamInfo.save() == true);

  // now we do the same for the compartment
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  miriamInfo.load(pCompartment->getKey());
  const CDataVector<CBiologicalDescription>* pDescriptions = &miriamInfo.getBiologicalDescriptions();
  CPPUNIT_ASSERT(pDescriptions != NULL);
  CPPUNIT_ASSERT(pDescriptions->size() == 1);
  CBiologicalDescription* pDescription = (*pDescriptions)[0];
  CPPUNIT_ASSERT(pDescription != NULL);
  std::string predicate = pDescription->getPredicate();
  CPPUNIT_ASSERT(predicate == "is version of");
  std::string resource = pDescription->getResource();
  CPPUNIT_ASSERT(resource == "Gene Ontology");
  std::string id = pDescription->getId();
  CPPUNIT_ASSERT(id == "GO:0005623");
  id = "GO:0001111";
  CBiologicalDescription* pNewDescription = miriamInfo.createBiologicalDescription();
  pNewDescription->setPredicate(predicate);
  pNewDescription->setResource(resource);
  pNewDescription->setId(id);
  CPPUNIT_ASSERT(pNewDescription != NULL);
  CPPUNIT_ASSERT(pNewDescription->getPredicate() == "is version of");
  CPPUNIT_ASSERT(pNewDescription->getResource() == "Gene Ontology");
  CPPUNIT_ASSERT(pNewDescription->getId() == "GO:0001111");
  CPPUNIT_ASSERT(miriamInfo.save() == true);

  std::string content = pDataModel->exportSBMLToString(NULL, 2, 4);
  CPPUNIT_ASSERT(content.empty() == false);
  // now we convert the content into an XMLNode and check if everything is there that needs to be there
  XMLInputStream inputstream(content.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pModelNode = &node.getChild(0);
  CPPUNIT_ASSERT(pModelNode != NULL);
  CPPUNIT_ASSERT(pModelNode->getName() == "model");
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pModelAnnotation = &pModelNode->getChild(0);
  CPPUNIT_ASSERT(pModelAnnotation != NULL);
  CPPUNIT_ASSERT(pModelAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have three children
  // depending on the version of libsbml we are using
  iMax = pModelAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 3);
  const XMLNode* pMIRIAM1 = NULL, *pMIRIAM2 = NULL, *pOther = NULL;

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pModelAnnotation->getChild(i).getName() == "RDF")
        {
          pMIRIAM1 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "COPASI")
        {
          pMIRIAM2 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "SOMEANNOTATION")
        {
          pOther = &pModelAnnotation->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pOther != NULL);
  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  const XMLNamespaces* ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  int index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // make sure the there are two modification dates
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "Description");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pMIRIAM2->getChild(i).getName() == "modified")
        {
          pMIRIAM2 = &pMIRIAM2->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM2->getName() == "modified");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "Bag");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 2);

  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");

  // there are actually more namespace attributes in the libsbml annotation, but that is enough to make sure
  // that everything should be OK
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "Description");
  iMax = pMIRIAM1->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pMIRIAM1->getChild(i).getName() == "modified")
        {
          pMIRIAM1 = &pMIRIAM1->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM1->getName() == "modified");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "W3CDTF");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getCharacters() == "2008-06-05T11:40:04Z");

  //
  // Find the compartment node
  iMax = pModelNode->getNumChildren();
  const XMLNode* pListOfCompartments = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "listOfCompartments")
        {
          pListOfCompartments = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfCompartments != NULL);
  iMax = pListOfCompartments->getNumChildren();
  // we have only one compartment
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pCompartmentNode = &pListOfCompartments->getChild(0);
  CPPUNIT_ASSERT(pCompartmentNode != NULL);
  CPPUNIT_ASSERT(pCompartmentNode->getName() == "compartment");
  iMax = pCompartmentNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pAnnotation = &pCompartmentNode->getChild(0);
  CPPUNIT_ASSERT(pAnnotation != NULL);
  CPPUNIT_ASSERT(pAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 3);
  pMIRIAM1 = NULL;
  pMIRIAM2 = NULL;
  pOther = NULL;

  // make sure the libsbml annotation is stored in pMIRIAM1
  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pAnnotation->getChild(i).getName() == "RDF")
        {
          pMIRIAM1 = &pAnnotation->getChild(i);
        }
      else if (pAnnotation->getChild(i).getName() == "COPASI")
        {
          pMIRIAM2 = &pAnnotation->getChild(i);
        }
      else if (pAnnotation->getChild(i).getName() == "SOMEANNOTATION")
        {
          pOther = &pAnnotation->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pOther != NULL);
  // check if the top level element for the COPASI annotation
  // has all necessary namespaces
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  // check if there are two biological descriptions
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "Description");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "isVersionOf");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "Bag");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMIRIAM2->getChild(0).getName() == "li");
  CPPUNIT_ASSERT(pMIRIAM2->getChild(1).getName() == "li");

  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // check if there are two biological descriptions
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "Description");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "isVersionOf");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "Bag");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMIRIAM1->getChild(0).getName() == "li");
  CPPUNIT_ASSERT(pMIRIAM1->getChild(1).getName() == "li");
  // try to reimport the stuff to make sure it is valid SBML
  result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
}

void test000092::test_miriam_export_9()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  bool result = pDataModel->importSBMLFromString(test000092::MODEL_STRING9);
  CPPUNIT_ASSERT(result == true);
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // we need to modify the imported MIRIAM annotation,
  // e.g. the add a modified date
  std::string miriamString = pModel->getMiriamAnnotation();
  CPPUNIT_ASSERT(!miriamString.empty());
  CMIRIAMInfo miriamInfo;
  miriamInfo.load(pModel->getKey());
  // check the modified date
  const CDataVector<CModification>* pModifications = &miriamInfo.getModifications();
  CPPUNIT_ASSERT(pModifications != NULL);
  // there should be only one modification date
  CPPUNIT_ASSERT(pModifications->size() == 1);
  const CModification* pModification = (*pModifications)[0];
  CPPUNIT_ASSERT(pModification != NULL);
  std::string dateTime = pModification->getDate();
  CPPUNIT_ASSERT(dateTime == "2007-06-05T11:40:04Z");
  // now we add a new modification date
  dateTime = "2008-06-05T11:40:04Z";
  CModification* pNewModification = miriamInfo.createModification(dateTime);
  CPPUNIT_ASSERT(pNewModification != NULL);
  CPPUNIT_ASSERT(pNewModification->getDate() == dateTime);
  CPPUNIT_ASSERT(miriamInfo.save() == true);

  // now we do the same for the compartment
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  miriamInfo.load(pCompartment->getKey());
  const CDataVector<CBiologicalDescription>* pDescriptions = &miriamInfo.getBiologicalDescriptions();
  CPPUNIT_ASSERT(pDescriptions != NULL);
  CPPUNIT_ASSERT(pDescriptions->size() == 1);
  CBiologicalDescription* pDescription = (*pDescriptions)[0];
  CPPUNIT_ASSERT(pDescription != NULL);
  std::string predicate = pDescription->getPredicate();
  CPPUNIT_ASSERT(predicate == "is version of");
  std::string resource = pDescription->getResource();
  CPPUNIT_ASSERT(resource == "Gene Ontology");
  std::string id = pDescription->getId();
  CPPUNIT_ASSERT(id == "GO:0005623");
  id = "GO:0001111";
  CBiologicalDescription* pNewDescription = miriamInfo.createBiologicalDescription();
  pNewDescription->setPredicate(predicate);
  pNewDescription->setResource(resource);
  pNewDescription->setId(id);
  CPPUNIT_ASSERT(pNewDescription != NULL);
  CPPUNIT_ASSERT(pNewDescription->getPredicate() == "is version of");
  CPPUNIT_ASSERT(pNewDescription->getResource() == "Gene Ontology");
  CPPUNIT_ASSERT(pNewDescription->getId() == "GO:0001111");
  CPPUNIT_ASSERT(miriamInfo.save() == true);

  std::string content = pDataModel->exportSBMLToString(NULL, 2, 4);
  CPPUNIT_ASSERT(content.empty() == false);
  // now we convert the content into an XMLNode and check if everything is there that needs to be there
  XMLInputStream inputstream(content.c_str(), false);
  XMLNode node(inputstream);
  CPPUNIT_ASSERT(node.getName() == "sbml");
  unsigned int i, iMax = node.getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pModelNode = &node.getChild(0);
  CPPUNIT_ASSERT(pModelNode != NULL);
  CPPUNIT_ASSERT(pModelNode->getName() == "model");
  iMax = pModelNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pModelAnnotation = &pModelNode->getChild(0);
  CPPUNIT_ASSERT(pModelAnnotation != NULL);
  CPPUNIT_ASSERT(pModelAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have three children
  // depending on the version of libsbml we are using
  iMax = pModelAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 3);
  const XMLNode* pMIRIAM1 = NULL, *pMIRIAM2 = NULL, *pOther = NULL;

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pModelAnnotation->getChild(i).getName() == "RDF")
        {
          pMIRIAM1 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "COPASI")
        {
          pMIRIAM2 = &pModelAnnotation->getChild(i);
        }
      else if (pModelAnnotation->getChild(i).getName() == "SOMEANNOTATION")
        {
          pOther = &pModelAnnotation->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pOther != NULL);
  // check if the top level element for the libsbml annotation
  // has all necessary namespaces
  const XMLNamespaces* ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  int index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // make sure the there are two modification dates
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "Description");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pMIRIAM2->getChild(i).getName() == "modified")
        {
          pMIRIAM2 = &pMIRIAM2->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM2->getName() == "modified");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "Bag");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 2);

  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");

  // there are actually more namespace attributes in the libsbml annotation, but that is enough to make sure
  // that everything should be OK
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "Description");
  iMax = pMIRIAM1->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);

  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pMIRIAM1->getChild(i).getName() == "modified")
        {
          pMIRIAM1 = &pMIRIAM1->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM1->getName() == "modified");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "W3CDTF");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getCharacters() == "2008-06-05T11:40:04Z");
  //
  // Find the compartment node
  iMax = pModelNode->getNumChildren();
  const XMLNode* pListOfCompartments = NULL;

  for (i = 0; i < iMax; ++i)
    {
      if (pModelNode->getChild(i).getName() == "listOfCompartments")
        {
          pListOfCompartments = &pModelNode->getChild(i);
          break;
        }
    }

  CPPUNIT_ASSERT(pListOfCompartments != NULL);
  iMax = pListOfCompartments->getNumChildren();
  // we have only one compartment
  CPPUNIT_ASSERT(iMax == 1);
  const XMLNode* pCompartmentNode = &pListOfCompartments->getChild(0);
  CPPUNIT_ASSERT(pCompartmentNode != NULL);
  CPPUNIT_ASSERT(pCompartmentNode->getName() == "compartment");
  iMax = pCompartmentNode->getNumChildren();
  CPPUNIT_ASSERT(iMax > 0);
  // the annotation to the model should always be the first child
  const XMLNode* pAnnotation = &pCompartmentNode->getChild(0);
  CPPUNIT_ASSERT(pAnnotation != NULL);
  CPPUNIT_ASSERT(pAnnotation->getName() == "annotation");
  // since the MIRIAM information is complete , we should have two children
  // one with the libsbml MIRIAM annotation and one with the COPASI MIRIAM annotation
  iMax = pAnnotation->getNumChildren();
  CPPUNIT_ASSERT(iMax == 3);
  pMIRIAM1 = NULL;
  pMIRIAM2 = NULL;
  pOther = NULL;

  // make sure the libsbml annotation is stored in pMIRIAM1
  for (unsigned int i = 0; i < iMax; ++i)
    {
      if (pAnnotation->getChild(i).getName() == "RDF")
        {
          pMIRIAM1 = &pAnnotation->getChild(i);
        }
      else if (pAnnotation->getChild(i).getName() == "COPASI")
        {
          pMIRIAM2 = &pAnnotation->getChild(i);
        }
      else if (pAnnotation->getChild(i).getName() == "SOMEANNOTATION")
        {
          pOther = &pAnnotation->getChild(i);
        }
    }

  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pOther != NULL);
  // check if the top level element for the COPASI annotation
  // has all necessary namespaces
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.copasi.org/static/sbml");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "");
  iMax = pMIRIAM2->getNumChildren();
  CPPUNIT_ASSERT(iMax == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM2->getPrefix() == "rdf");
  ns = &pMIRIAM2->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  // check if there are two biological descriptions
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "Description");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "isVersionOf");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 1);
  pMIRIAM2 = &pMIRIAM2->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM2 != NULL);
  CPPUNIT_ASSERT(pMIRIAM2->getName() == "Bag");
  CPPUNIT_ASSERT(pMIRIAM2->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMIRIAM2->getChild(0).getName() == "li");
  CPPUNIT_ASSERT(pMIRIAM2->getChild(1).getName() == "li");

  // same checks for the libsbml MIRIAM annotation
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "RDF");
  CPPUNIT_ASSERT(pMIRIAM1->getPrefix() == "rdf");
  ns = &pMIRIAM1->getNamespaces();
  CPPUNIT_ASSERT(ns != NULL);
  index = ns->getIndex("http://purl.org/dc/terms/");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "dcterms");
  index = ns->getIndex("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "rdf");
  index = ns->getIndex("http://www.w3.org/2001/vcard-rdf/3.0#");
  CPPUNIT_ASSERT(index != -1);
  CPPUNIT_ASSERT(ns->getPrefix(index) == "vCard");
  // check if there are two biological descriptions
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "Description");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "isVersionOf");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 1);
  pMIRIAM1 = &pMIRIAM1->getChild(0);
  CPPUNIT_ASSERT(pMIRIAM1 != NULL);
  CPPUNIT_ASSERT(pMIRIAM1->getName() == "Bag");
  CPPUNIT_ASSERT(pMIRIAM1->getNumChildren() == 2);
  CPPUNIT_ASSERT(pMIRIAM1->getChild(0).getName() == "li");
  CPPUNIT_ASSERT(pMIRIAM1->getChild(1).getName() == "li");
  // try to reimport the stuff to make sure it is valid SBML
  result = pDataModel->importSBMLFromString(content);
  CPPUNIT_ASSERT(result == true);
}

/**
 * This test will most likely fail until we have a workaround for the SBML one modification limit.
 */
void test000092::test_miriam_import_1()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  bool result = pDataModel->importSBMLFromString(test000092::MODEL_STRING10);
  CPPUNIT_ASSERT(result == true);
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // we need to modify the imported MIRIAM annotation,
  // e.g. the add a modified date
  std::string miriamString = pModel->getMiriamAnnotation();
  CPPUNIT_ASSERT(!miriamString.empty());
  CMIRIAMInfo miriamInfo;
  miriamInfo.load(pModel->getKey());
  // check the modified date
  const CDataVector<CModification>* pModifications = &miriamInfo.getModifications();
  CPPUNIT_ASSERT(pModifications != NULL);
  // there should be only one modification date
  CPPUNIT_ASSERT_MESSAGE("This test will fail until we have a workaround for the one modification date limit in SBML.", pModifications->size() == 2);
  const CModification* pModification = (*pModifications)[0];
  CPPUNIT_ASSERT(pModification != NULL);
  std::string dateTime = pModification->getDate();
  CPPUNIT_ASSERT(dateTime == "2007-06-05T11:40:04Z" || dateTime == "2008-06-05T11:40:04Z");
  const CModification* pModification2 = (*pModifications)[1];
  CPPUNIT_ASSERT(pModification2 != NULL);
  std::string dateTime2 = pModification2->getDate();
  CPPUNIT_ASSERT(dateTime2 == "2007-06-05T11:40:04Z" || dateTime2 == "2008-06-05T11:40:04Z");
  // make sure both dates are not the same
  CPPUNIT_ASSERT(dateTime != dateTime2);
}

/**
 * This model has complete MIRIAM compliant annotation, so of of it should be exported
 * by libsbml and in addition to that as annotation in the COPASI namespace.
 */
const char* test000092::MODEL_STRING1 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<!-- generated with COPASI 4.5.31 (Debug) (http://www.copasi.org) at 2010-04-21 14:00:12 UTC -->\n"
                                        "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
                                        "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"31\">\n"
                                        "  <Model key=\"Model_0\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
                                        "    <MiriamAnnotation>\n"
                                        "<rdf:RDF\n"
                                        "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                        "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                        "   xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "  <rdf:Description rdf:about=\"#Model_0\">\n"
                                        "    <dcterms:created>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:55:08Z</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:created>\n"
                                        "    <dcterms:creator>\n"
                                        "      <rdf:Description>\n"
                                        "        <vCard:N>\n"
                                        "          <rdf:Description>\n"
                                        "            <vCard:Family>Gauges</vCard:Family>\n"
                                        "            <vCard:Given>Ralph</vCard:Given>\n"
                                        "          </rdf:Description>\n"
                                        "        </vCard:N>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:creator>\n"
                                        "    <dcterms:modified>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:59:47</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:modified>\n"
                                        "  </rdf:Description>\n"
                                        "</rdf:RDF>\n"
                                        "\n"
                                        "    </MiriamAnnotation>\n"
                                        "    <ListOfCompartments>\n"
                                        "      <Compartment key=\"Compartment_0\" name=\"Compartment\" simulationType=\"fixed\" dimensionality=\"3\">\n"
                                        "        <MiriamAnnotation>\n"
                                        "<rdf:RDF\n"
                                        "   xmlns:CopasiMT=\"http://www.copasi.org/RDF/MiriamTerms#\"\n"
                                        "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                        "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                        "   xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "  <rdf:Description rdf:about=\"#Compartment_0\">\n"
                                        "    <dcterms:created>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:55:31Z</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:created>\n"
                                        "    <dcterms:creator>\n"
                                        "      <rdf:Description>\n"
                                        "        <vCard:N>\n"
                                        "          <rdf:Description>\n"
                                        "            <vCard:Family>Gauges</vCard:Family>\n"
                                        "            <vCard:Given>Ralph</vCard:Given>\n"
                                        "          </rdf:Description>\n"
                                        "        </vCard:N>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:creator>\n"
                                        "    <CopasiMT:isVersionOf rdf:resource=\"urn:miriam:obo.go:GO:0005623\"/>\n"
                                        "  </rdf:Description>\n"
                                        "</rdf:RDF>\n"
                                        "\n"
                                        "        </MiriamAnnotation>\n"
                                        "      </Compartment>\n"
                                        "    </ListOfCompartments>\n"
                                        "    <StateTemplate>\n"
                                        "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
                                        "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
                                        "    </StateTemplate>\n"
                                        "    <InitialState type=\"initialState\">\n"
                                        "      0 1 \n"
                                        "    </InitialState>\n"
                                        "  </Model>\n"
                                        "</COPASI>\n";

/**
 * In this model the Model history is incomplete because there is no creator
 * and no modified date so libsbml 4 will no longer write the model history. Nevertheless
 * the annotation should be written in the COPASI namespace.
 */
const char* test000092::MODEL_STRING2 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<!-- generated with COPASI 4.5.31 (Debug) (http://www.copasi.org) at 2010-04-21 14:00:12 UTC -->\n"
                                        "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
                                        "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"31\">\n"
                                        "  <Model key=\"Model_0\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
                                        "    <MiriamAnnotation>\n"
                                        "<rdf:RDF\n"
                                        "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                        "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                        "   xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "  <rdf:Description rdf:about=\"#Model_0\">\n"
                                        "    <dcterms:created>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:55:08Z</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:created>\n"
                                        "  </rdf:Description>\n"
                                        "</rdf:RDF>\n"
                                        "\n"
                                        "    </MiriamAnnotation>\n"
                                        "    <ListOfCompartments>\n"
                                        "      <Compartment key=\"Compartment_0\" name=\"Compartment\" simulationType=\"fixed\" dimensionality=\"3\">\n"
                                        "        <MiriamAnnotation>\n"
                                        "<rdf:RDF\n"
                                        "   xmlns:CopasiMT=\"http://www.copasi.org/RDF/MiriamTerms#\"\n"
                                        "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                        "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                        "   xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "  <rdf:Description rdf:about=\"#Compartment_0\">\n"
                                        "    <dcterms:created>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:55:31Z</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:created>\n"
                                        "    <dcterms:creator>\n"
                                        "      <rdf:Description>\n"
                                        "        <vCard:N>\n"
                                        "          <rdf:Description>\n"
                                        "            <vCard:Family>Gauges</vCard:Family>\n"
                                        "            <vCard:Given>Ralph</vCard:Given>\n"
                                        "          </rdf:Description>\n"
                                        "        </vCard:N>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:creator>\n"
                                        "    <CopasiMT:isVersionOf rdf:resource=\"urn:miriam:obo.go:GO:0005623\"/>\n"
                                        "  </rdf:Description>\n"
                                        "</rdf:RDF>\n"
                                        "\n"
                                        "        </MiriamAnnotation>\n"
                                        "      </Compartment>\n"
                                        "    </ListOfCompartments>\n"
                                        "    <StateTemplate>\n"
                                        "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
                                        "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
                                        "    </StateTemplate>\n"
                                        "    <InitialState type=\"initialState\">\n"
                                        "      0 1 \n"
                                        "    </InitialState>\n"
                                        "  </Model>\n"
                                        "</COPASI>\n";

/**
 * In this model the Model there is no MIRIAM annotation.
 * There should be no annotation in the exported SBML model.
 */
const char* test000092::MODEL_STRING3 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<!-- generated with COPASI 4.5.31 (Debug) (http://www.copasi.org) at 2010-04-21 14:00:12 UTC -->\n"
                                        "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
                                        "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"31\">\n"
                                        "  <Model key=\"Model_0\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
                                        "    <ListOfCompartments>\n"
                                        "      <Compartment key=\"Compartment_0\" name=\"Compartment\" simulationType=\"fixed\" dimensionality=\"3\"/>\n"
                                        "    </ListOfCompartments>\n"
                                        "    <StateTemplate>\n"
                                        "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
                                        "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
                                        "    </StateTemplate>\n"
                                        "    <InitialState type=\"initialState\">\n"
                                        "      0 1 \n"
                                        "    </InitialState>\n"
                                        "  </Model>\n"
                                        "</COPASI>\n";

/**
 * This model has complete MIRIAM compliant annotation, so of of it should be exported
 * by libsbml and in addition to that as annotation in the COPASI namespace.
 * In addition there is layout information that should also end up in the annotation to the
 * SBML model
 */
const char* test000092::MODEL_STRING4 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<!-- generated with COPASI 4.5.31 (Debug) (http://www.copasi.org) at 2010-04-21 14:00:12 UTC -->\n"
                                        "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
                                        "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"31\">\n"
                                        "  <Model key=\"Model_0\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
                                        "    <MiriamAnnotation>\n"
                                        "<rdf:RDF\n"
                                        "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                        "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                        "   xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "  <rdf:Description rdf:about=\"#Model_0\">\n"
                                        "    <dcterms:created>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:55:08Z</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:created>\n"
                                        "    <dcterms:creator>\n"
                                        "      <rdf:Description>\n"
                                        "        <vCard:N>\n"
                                        "          <rdf:Description>\n"
                                        "            <vCard:Family>Gauges</vCard:Family>\n"
                                        "            <vCard:Given>Ralph</vCard:Given>\n"
                                        "          </rdf:Description>\n"
                                        "        </vCard:N>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:creator>\n"
                                        "    <dcterms:modified>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:59:47</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:modified>\n"
                                        "  </rdf:Description>\n"
                                        "</rdf:RDF>\n"
                                        "\n"
                                        "    </MiriamAnnotation>\n"
                                        "    <ListOfCompartments>\n"
                                        "      <Compartment key=\"Compartment_0\" name=\"Compartment\" simulationType=\"fixed\" dimensionality=\"3\">\n"
                                        "        <MiriamAnnotation>\n"
                                        "<rdf:RDF\n"
                                        "   xmlns:CopasiMT=\"http://www.copasi.org/RDF/MiriamTerms#\"\n"
                                        "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                        "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                        "   xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "  <rdf:Description rdf:about=\"#Compartment_0\">\n"
                                        "    <dcterms:created>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:55:31Z</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:created>\n"
                                        "    <dcterms:creator>\n"
                                        "      <rdf:Description>\n"
                                        "        <vCard:N>\n"
                                        "          <rdf:Description>\n"
                                        "            <vCard:Family>Gauges</vCard:Family>\n"
                                        "            <vCard:Given>Ralph</vCard:Given>\n"
                                        "          </rdf:Description>\n"
                                        "        </vCard:N>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:creator>\n"
                                        "    <CopasiMT:isVersionOf rdf:resource=\"urn:miriam:obo.go:GO:0005623\"/>\n"
                                        "  </rdf:Description>\n"
                                        "</rdf:RDF>\n"
                                        "\n"
                                        "        </MiriamAnnotation>\n"
                                        "      </Compartment>\n"
                                        "    </ListOfCompartments>\n"
                                        "    <StateTemplate>\n"
                                        "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
                                        "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
                                        "    </StateTemplate>\n"
                                        "    <InitialState type=\"initialState\">\n"
                                        "      0 1 \n"
                                        "    </InitialState>\n"
                                        "  </Model>\n"
                                        "  <ListOfLayouts>\n"
                                        "    <Layout key=\"Layout_2\" name=\"layout_0\">\n"
                                        "      <Dimensions width=\"500.0\" height=\"200.0\"/>\n"
                                        "      <ListOfCompartmentGlyphs>\n"
                                        "        <CompartmentGlyph key=\"Layout_3\" name=\"sGlyph_0\" compartment=\"Compartment_0\">\n"
                                        "          <BoundingBox>\n"
                                        "            <Position x=\"10.0\" y=\"10.0\"/>\n"
                                        "            <Dimensions width=\"480.0\" height=\"180.0\"/>\n"
                                        "          </BoundingBox>\n"
                                        "        </CompartmentGlyph>\n"
                                        "      </ListOfCompartmentGlyphs>\n"
                                        "    </Layout>\n"
                                        "  </ListOfLayouts>\n"
                                        "</COPASI>\n";

/**
 * In this model the Model history is incomplete because there is no creator
 * and no modified date so libsbml 4 will no longer write the model history. Nevertheless
 * the annotation should be written in the COPASI namespace.
 * In addition there is layout information that should also end up in the annotation to the
 * SBML model
 */
const char* test000092::MODEL_STRING5 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<!-- generated with COPASI 4.5.31 (Debug) (http://www.copasi.org) at 2010-04-21 14:00:12 UTC -->\n"
                                        "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
                                        "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"31\">\n"
                                        "  <Model key=\"Model_0\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
                                        "    <MiriamAnnotation>\n"
                                        "<rdf:RDF\n"
                                        "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                        "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                        "   xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "  <rdf:Description rdf:about=\"#Model_0\">\n"
                                        "    <dcterms:created>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:55:08Z</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:created>\n"
                                        "  </rdf:Description>\n"
                                        "</rdf:RDF>\n"
                                        "\n"
                                        "    </MiriamAnnotation>\n"
                                        "    <ListOfCompartments>\n"
                                        "      <Compartment key=\"Compartment_0\" name=\"Compartment\" simulationType=\"fixed\" dimensionality=\"3\">\n"
                                        "        <MiriamAnnotation>\n"
                                        "<rdf:RDF\n"
                                        "   xmlns:CopasiMT=\"http://www.copasi.org/RDF/MiriamTerms#\"\n"
                                        "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                        "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                        "   xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "  <rdf:Description rdf:about=\"#Compartment_0\">\n"
                                        "    <dcterms:created>\n"
                                        "      <rdf:Description>\n"
                                        "        <dcterms:W3CDTF>2010-04-21T15:55:31Z</dcterms:W3CDTF>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:created>\n"
                                        "    <dcterms:creator>\n"
                                        "      <rdf:Description>\n"
                                        "        <vCard:N>\n"
                                        "          <rdf:Description>\n"
                                        "            <vCard:Family>Gauges</vCard:Family>\n"
                                        "            <vCard:Given>Ralph</vCard:Given>\n"
                                        "          </rdf:Description>\n"
                                        "        </vCard:N>\n"
                                        "      </rdf:Description>\n"
                                        "    </dcterms:creator>\n"
                                        "    <CopasiMT:isVersionOf rdf:resource=\"urn:miriam:obo.go:GO:0005623\"/>\n"
                                        "  </rdf:Description>\n"
                                        "</rdf:RDF>\n"
                                        "\n"
                                        "        </MiriamAnnotation>\n"
                                        "      </Compartment>\n"
                                        "    </ListOfCompartments>\n"
                                        "    <StateTemplate>\n"
                                        "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
                                        "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
                                        "    </StateTemplate>\n"
                                        "    <InitialState type=\"initialState\">\n"
                                        "      0 1 \n"
                                        "    </InitialState>\n"
                                        "  </Model>\n"
                                        "  <ListOfLayouts>\n"
                                        "    <Layout key=\"Layout_2\" name=\"layout_0\">\n"
                                        "      <Dimensions width=\"500.0\" height=\"200.0\"/>\n"
                                        "      <ListOfCompartmentGlyphs>\n"
                                        "        <CompartmentGlyph key=\"Layout_3\" name=\"sGlyph_0\" compartment=\"Compartment_0\">\n"
                                        "          <BoundingBox>\n"
                                        "            <Position x=\"10.0\" y=\"10.0\"/>\n"
                                        "            <Dimensions width=\"480.0\" height=\"180.0\"/>\n"
                                        "          </BoundingBox>\n"
                                        "        </CompartmentGlyph>\n"
                                        "      </ListOfCompartmentGlyphs>\n"
                                        "    </Layout>\n"
                                        "  </ListOfLayouts>\n"
                                        "</COPASI>\n";

/**
 * In this model the Model there is no MIRIAM annotation.
 * But the model has a layout, that should be exported as an annotation to the
 * SBML Model,
 */
const char* test000092::MODEL_STRING6 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<!-- generated with COPASI 4.5.31 (Debug) (http://www.copasi.org) at 2010-04-21 14:00:12 UTC -->\n"
                                        "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>\n"
                                        "<COPASI xmlns=\"http://www.copasi.org/static/schema\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"31\">\n"
                                        "  <Model key=\"Model_0\" name=\"New Model\" simulationType=\"time\" timeUnit=\"s\" volumeUnit=\"ml\" areaUnit=\"m²\" lengthUnit=\"m\" quantityUnit=\"mmol\" type=\"deterministic\">\n"
                                        "    <ListOfCompartments>\n"
                                        "      <Compartment key=\"Compartment_0\" name=\"Compartment\" simulationType=\"fixed\" dimensionality=\"3\"/>\n"
                                        "    </ListOfCompartments>\n"
                                        "    <StateTemplate>\n"
                                        "      <StateTemplateVariable objectReference=\"Model_0\"/>\n"
                                        "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
                                        "    </StateTemplate>\n"
                                        "    <InitialState type=\"initialState\">\n"
                                        "      0 1 \n"
                                        "    </InitialState>\n"
                                        "  </Model>\n"
                                        "  <ListOfLayouts>\n"
                                        "    <Layout key=\"Layout_2\" name=\"layout_0\">\n"
                                        "      <Dimensions width=\"500.0\" height=\"200.0\"/>\n"
                                        "      <ListOfCompartmentGlyphs>\n"
                                        "        <CompartmentGlyph key=\"Layout_3\" name=\"sGlyph_0\" compartment=\"Compartment_0\">\n"
                                        "          <BoundingBox>\n"
                                        "            <Position x=\"10.0\" y=\"10.0\"/>\n"
                                        "            <Dimensions width=\"480.0\" height=\"180.0\"/>\n"
                                        "          </BoundingBox>\n"
                                        "        </CompartmentGlyph>\n"
                                        "      </ListOfCompartmentGlyphs>\n"
                                        "    </Layout>\n"
                                        "  </ListOfLayouts>\n"
                                        "</COPASI>\n";

/**
 * This SBML model already contains an annotation.
 * We load it and add some MIRIAM annotation and write it out again to check
 * if MIRIAM annotation is correctly written even if another annotation exists.
 */
const char* test000092::MODEL_STRING7 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n"
                                        "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n"
                                        "    <annotation>\n"
                                        "      <SOMEANNOTATION xmlns=\"http://www.SOMEORGANISATION.org/\" />\n"
                                        "    </annotation>\n"
                                        "    <listOfCompartments>\n"
                                        "     <compartment metaid=\"COPASI2\" id=\"compartment_1\" name=\"Compartment\" size=\"1\">\n"
                                        "       <annotation>\n"
                                        "         <SOMEANNOTATION xmlns=\"http://www.SOMEORGANISATION.org/\" />\n"
                                        "       </annotation>\n"
                                        "     </compartment>\n"
                                        "    </listOfCompartments>\n"
                                        "  </model>\n"
                                        "</sbml>\n";

/**
 * This SBML model already contains RDF annotation and other annotation.
 * We load it and modify the MIRIAM annotation and write it out again to check
 * if MIRIAM annotation is correctly updated
 */
const char* test000092::MODEL_STRING8 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n"
                                        "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n"
                                        "    <annotation>\n"
                                        "      <SOMEANNOTATION xmlns=\"http://www.SOMEORGANISATION.org/\" />\n"
                                        "      <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                        "        <rdf:Description rdf:about=\"#COPASI1\">\n"
                                        "          <dcterms:created rdf:parseType=\"Resource\">\n"
                                        "            <dcterms:W3CDTF>2002-04-21T15:55:08Z</dcterms:W3CDTF>\n"
                                        "          </dcterms:created>\n"
                                        "          <dc:creator>\n"
                                        "            <rdf:Bag>\n"
                                        "              <rdf:li rdf:parseType=\"Resource\">\n"
                                        "                <vCard:N rdf:parseType=\"Resource\">\n"
                                        "                  <vCard:Family>Gauges</vCard:Family>\n"
                                        "                  <vCard:Given>Ralph</vCard:Given>\n"
                                        "                </vCard:N>\n"
                                        "              </rdf:li>\n"
                                        "            </rdf:Bag>\n"
                                        "          </dc:creator>\n"
                                        "          <dcterms:modified rdf:parseType=\"Resource\">\n"
                                        "            <dcterms:W3CDTF>2007-06-05T11:40:04Z</dcterms:W3CDTF>\n"
                                        "          </dcterms:modified>\n"
                                        "        </rdf:Description>\n"
                                        "      </rdf:RDF>\n"
                                        "    </annotation>\n"
                                        "    <listOfUnitDefinitions>\n"
                                        "      <unitDefinition id=\"volume\" name=\"volume\">\n"
                                        "        <listOfUnits>\n"
                                        "          <unit kind=\"litre\" scale=\"-3\"/>\n"
                                        "        </listOfUnits>\n"
                                        "      </unitDefinition>\n"
                                        "      <unitDefinition id=\"substance\" name=\"substance\">\n"
                                        "        <listOfUnits>\n"
                                        "          <unit kind=\"mole\" scale=\"-3\"/>\n"
                                        "        </listOfUnits>\n"
                                        "      </unitDefinition>\n"
                                        "    </listOfUnitDefinitions>\n"
                                        "    <listOfCompartments>\n"
                                        "      <compartment metaid=\"COPASI2\" id=\"compartment_1\" name=\"Compartment\" size=\"1\">\n"
                                        "        <annotation>\n"
                                        "          <SOMEANNOTATION xmlns=\"http://www.SOMEORGANISATION.org/\" />\n"
                                        "          <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                        "            <rdf:Description rdf:about=\"#COPASI2\">\n"
                                        "              <bqbiol:isVersionOf>\n"
                                        "                <rdf:Bag>\n"
                                        "                  <rdf:li rdf:resource=\"urn:miriam:obo.go:GO:0005623\"/>\n"
                                        "                </rdf:Bag>\n"
                                        "              </bqbiol:isVersionOf>\n"
                                        "            </rdf:Description>\n"
                                        "          </rdf:RDF>\n"
                                        "        </annotation>\n"
                                        "      </compartment>\n"
                                        "    </listOfCompartments>\n"
                                        "  </model>\n"
                                        "</sbml>\n";

/**
 * This SBML model already contains RDF annotation and other annotation.
 * It also contains COPASI RDF annotation.
 * We load it and modify the MIRIAM annotation and write it out again to check
 * if MIRIAM annotation is correctly updated and COPASI annotation is correctly replaced.
 */
const char* test000092::MODEL_STRING9 = \
                                        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                        "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n"
                                        "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n"
                                        "    <annotation>\n"
                                        "      <SOMEANNOTATION xmlns=\"http://www.SOMEORGANISATION.org/\" />\n"
                                        "      <COPASI xmlns=\"http://www.copasi.org/static/sbml\">\n"
                                        "        <rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "          <rdf:Description rdf:about=\"#COPASI1\">\n"
                                        "            <dcterms:created>\n"
                                        "              <rdf:Description>\n"
                                        "                <dcterms:W3CDTF>2002-04-21T15:55:08Z</dcterms:W3CDTF>\n"
                                        "              </rdf:Description>\n"
                                        "            </dcterms:created>\n"
                                        "            <dcterms:creator>\n"
                                        "              <rdf:Description>\n"
                                        "                <vCard:N>\n"
                                        "                   <rdf:Description>\n"
                                        "                    <vCard:Family>Gauges</vCard:Family>\n"
                                        "                    <vCard:Given>Ralph</vCard:Given>\n"
                                        "                  </rdf:Description>\n"
                                        "                </vCard:N>\n"
                                        "              </rdf:Description>\n"
                                        "            </dcterms:creator>\n"
                                        "            <dcterms:modified rdf:parseType=\"Resource\">\n"
                                        "              <dcterms:W3CDTF>2007-06-05T11:40:04Z</dcterms:W3CDTF>\n"
                                        "            </dcterms:modified>\n"
                                        "          </rdf:Description>\n"
                                        "        </rdf:RDF>\n"
                                        "      </COPASI>\n"
                                        "      <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                        "        <rdf:Description rdf:about=\"#COPASI1\">\n"
                                        "          <dcterms:created rdf:parseType=\"Resource\">\n"
                                        "            <dcterms:W3CDTF>2002-04-21T15:55:08Z</dcterms:W3CDTF>\n"
                                        "          </dcterms:created>\n"
                                        "          <dc:creator>\n"
                                        "            <rdf:Bag>\n"
                                        "              <rdf:li rdf:parseType=\"Resource\">\n"
                                        "                <vCard:N rdf:parseType=\"Resource\">\n"
                                        "                  <vCard:Family>Gauges</vCard:Family>\n"
                                        "                  <vCard:Given>Ralph</vCard:Given>\n"
                                        "                </vCard:N>\n"
                                        "              </rdf:li>\n"
                                        "            </rdf:Bag>\n"
                                        "          </dc:creator>\n"
                                        "          <dcterms:modified rdf:parseType=\"Resource\">\n"
                                        "            <dcterms:W3CDTF>2007-06-05T11:40:04Z</dcterms:W3CDTF>\n"
                                        "          </dcterms:modified>\n"
                                        "        </rdf:Description>\n"
                                        "      </rdf:RDF>\n"
                                        "    </annotation>\n"
                                        "    <listOfCompartments>\n"
                                        "      <compartment metaid=\"COPASI2\" id=\"compartment_1\" name=\"Compartment\" size=\"1\">\n"
                                        "        <annotation>\n"
                                        "          <SOMEANNOTATION xmlns=\"http://www.SOMEORGANISATION.org/\" />\n"
                                        "          <COPASI xmlns=\"http://www.copasi.org/static/sbml\">\n"
                                        "            <rdf:RDF xmlns:CopasiMT=\"http://www.copasi.org/RDF/MiriamTerms#\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
                                        "              <rdf:Description rdf:about=\"#COPASI2\">\n"
                                        "                <dcterms:created>\n"
                                        "                  <rdf:Description>\n"
                                        "                    <dcterms:W3CDTF>2002-04-21T15:55:31Z</dcterms:W3CDTF>\n"
                                        "                  </rdf:Description>\n"
                                        "                </dcterms:created>\n"
                                        "                <dcterms:creator>\n"
                                        "                  <rdf:Description>\n"
                                        "                    <vCard:N>\n"
                                        "                      <rdf:Description>\n"
                                        "                        <vCard:Family>Gauges</vCard:Family>\n"
                                        "                        <vCard:Given>Ralph</vCard:Given>\n"
                                        "                      </rdf:Description>\n"
                                        "                    </vCard:N>\n"
                                        "                  </rdf:Description>\n"
                                        "                </dcterms:creator>\n"
                                        "                <CopasiMT:isVersionOf rdf:resource=\"urn:miriam:obo.go:GO:0005623\"/>\n"
                                        "              </rdf:Description>\n"
                                        "            </rdf:RDF>\n"
                                        "          </COPASI>\n"
                                        "          <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                        "            <rdf:Description rdf:about=\"#COPASI2\">\n"
                                        "              <bqbiol:isVersionOf>\n"
                                        "                <rdf:Bag>\n"
                                        "                  <rdf:li rdf:resource=\"urn:miriam:obo.go:GO:0005623\"/>\n"
                                        "                </rdf:Bag>\n"
                                        "              </bqbiol:isVersionOf>\n"
                                        "            </rdf:Description>\n"
                                        "          </rdf:RDF>\n"
                                        "        </annotation>\n"
                                        "      </compartment>\n"
                                        "    </listOfCompartments>\n"
                                        "  </model>\n"
                                        "</sbml>\n";

const char* test000092::MODEL_STRING10 = \
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version4\" level=\"2\" version=\"4\">\n"
    "  <model metaid=\"COPASI1\" id=\"Model_1\" name=\"New Model\">\n"
    "    <annotation>\n"
    "      <COPASI xmlns=\"http://www.copasi.org/static/sbml\">\n"
    "        <rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\">\n"
    "          <rdf:Description rdf:about=\"#COPASI1\">\n"
    "            <dcterms:created>\n"
    "              <rdf:Description>\n"
    "                <dcterms:W3CDTF>2002-04-21T15:55:08Z</dcterms:W3CDTF>\n"
    "              </rdf:Description>\n"
    "            </dcterms:created>\n"
    "            <dcterms:creator>\n"
    "              <rdf:Description>\n"
    "                <vCard:N>\n"
    "                  <rdf:Description>\n"
    "                    <vCard:Family>Gauges</vCard:Family>\n"
    "                    <vCard:Given>Ralph</vCard:Given>\n"
    "                  </rdf:Description>\n"
    "                </vCard:N>\n"
    "              </rdf:Description>\n"
    "            </dcterms:creator>\n"
    "            <dcterms:modified>\n"
    "              <rdf:Bag>\n"
    "                <rdf:li>\n"
    "                  <rdf:Description>\n"
    "                    <dcterms:W3CDTF>2007-06-05T11:40:04Z</dcterms:W3CDTF>\n"
    "                  </rdf:Description>\n"
    "                </rdf:li>\n"
    "                <rdf:li>\n"
    "                  <rdf:Description>\n"
    "                    <dcterms:W3CDTF>2008-06-05T11:40:04Z</dcterms:W3CDTF>\n"
    "                  </rdf:Description>\n"
    "                </rdf:li>\n"
    "              </rdf:Bag>\n"
    "            </dcterms:modified>\n"
    "          </rdf:Description>\n"
    "        </rdf:RDF>\n"
    "      </COPASI>\n"
    "      <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
    "        <rdf:Description rdf:about=\"#COPASI1\">\n"
    "          <dc:creator>\n"
    "            <rdf:Bag>\n"
    "              <rdf:li rdf:parseType=\"Resource\">\n"
    "                <vCard:N rdf:parseType=\"Resource\">\n"
    "                  <vCard:Family>Gauges</vCard:Family>\n"
    "                  <vCard:Given>Ralph</vCard:Given>\n"
    "                </vCard:N>\n"
    "              </rdf:li>\n"
    "            </rdf:Bag>\n"
    "          </dc:creator>\n"
    "          <dcterms:created rdf:parseType=\"Resource\">\n"
    "            <dcterms:W3CDTF>2002-04-21T15:55:08Z</dcterms:W3CDTF>\n"
    "          </dcterms:created>\n"
    "          <dcterms:modified rdf:parseType=\"Resource\">\n"
    "            <dcterms:W3CDTF>2008-06-05T11:40:04Z</dcterms:W3CDTF>\n"
    "          </dcterms:modified>\n"
    "        </rdf:Description>\n"
    "      </rdf:RDF>\n"
    "    </annotation>\n"
    "    <listOfCompartments>\n"
    "      <compartment metaid=\"COPASI2\" id=\"compartment_1\" name=\"Compartment\" size=\"1\" />\n"
    "    </listOfCompartments>\n"
    "  </model>\n"
    "</sbml>\n";
