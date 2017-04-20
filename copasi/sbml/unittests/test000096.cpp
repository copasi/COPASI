// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "test000096.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/xml/XMLNode.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/sbml/CSBMLExporter.h"

#include <string>

void test000096::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
}

void test000096::tearDown()
{
  CRootContainer::destroy();
}

void test000096::test_export_model_notes_1()
{
  XMLNode* pNotes = CSBMLExporter::createSBMLNotes(NOTES_STRING_1);
  CPPUNIT_ASSERT(pNotes != NULL);
  CPPUNIT_ASSERT(pNotes->getName() == "body");
  CPPUNIT_ASSERT(pNotes->getURI() == "http://www.w3.org/1999/xhtml");
  CPPUNIT_ASSERT(pNotes->hasNamespaceURI("http://www.w3.org/1999/xhtml") == true);
  CPPUNIT_ASSERT(pNotes->getNumChildren() == 1);
  XMLNode* pChild = &pNotes->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->getName() == "pre");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("This") != std::string::npos);
  SBMLDocument *pDocument = new SBMLDocument(2, 4);
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->createModel("test_model");
  CPPUNIT_ASSERT(pModel != NULL);
  int set_result = pModel->setNotes(pNotes);
  CPPUNIT_ASSERT(set_result == LIBSBML_OPERATION_SUCCESS);
  delete pDocument;
  delete pNotes;
}

void test000096::test_export_model_notes_2()
{
  XMLNode* pNotes = CSBMLExporter::createSBMLNotes(NOTES_STRING_2);
  CPPUNIT_ASSERT(pNotes != NULL);
  CPPUNIT_ASSERT(pNotes->getName() == "p");
  CPPUNIT_ASSERT(pNotes->getURI() == "http://www.w3.org/1999/xhtml");
  CPPUNIT_ASSERT(pNotes->hasNamespaceURI("http://www.w3.org/1999/xhtml") == true);
  CPPUNIT_ASSERT(pNotes->getNumChildren() == 1);
  XMLNode* pChild = &pNotes->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("This") != std::string::npos);
  SBMLDocument *pDocument = new SBMLDocument(2, 4);
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->createModel("test_model");
  CPPUNIT_ASSERT(pModel != NULL);
  int set_result = pModel->setNotes(pNotes);
  CPPUNIT_ASSERT(set_result == LIBSBML_OPERATION_SUCCESS);
  delete pDocument;
  delete pNotes;
}

void test000096::test_export_model_notes_3()
{
  XMLNode* pNotes = CSBMLExporter::createSBMLNotes(NOTES_STRING_3);
  CPPUNIT_ASSERT(pNotes != NULL);
  CPPUNIT_ASSERT(pNotes->getName() == "body");
  CPPUNIT_ASSERT(pNotes->getURI() == "http://www.w3.org/1999/xhtml");
  CPPUNIT_ASSERT(pNotes->hasNamespaceURI("http://www.w3.org/1999/xhtml") == true);
  CPPUNIT_ASSERT(pNotes->getNumChildren() == 3);
  XMLNode* pChild = &pNotes->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isElement());
  CPPUNIT_ASSERT(pChild->getName() == "p");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("This") != std::string::npos);
  pChild = &pNotes->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isElement());
  CPPUNIT_ASSERT(pChild->getName() == "p");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("several") != std::string::npos);
  pChild = &pNotes->getChild(2);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isElement());
  CPPUNIT_ASSERT(pChild->getName() == "p");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("correctly") != std::string::npos);

  SBMLDocument *pDocument = new SBMLDocument(2, 4);
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->createModel("test_model");
  CPPUNIT_ASSERT(pModel != NULL);
  int set_result = pModel->setNotes(pNotes);
  CPPUNIT_ASSERT(set_result == LIBSBML_OPERATION_SUCCESS);
  delete pDocument;
  delete pNotes;
}

void test000096::test_export_model_notes_4()
{
  XMLNode* pNotes = CSBMLExporter::createSBMLNotes(NOTES_STRING_4);
  CPPUNIT_ASSERT(pNotes != NULL);
  CPPUNIT_ASSERT(pNotes->getName() == "body");
  CPPUNIT_ASSERT(pNotes->getURI() == "http://www.w3.org/1999/xhtml");
  CPPUNIT_ASSERT(pNotes->hasNamespaceURI("http://www.w3.org/1999/xhtml") == true);

  CPPUNIT_ASSERT(pNotes->getNumChildren() == 4);
  XMLNode* pChild = &pNotes->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("This") != std::string::npos);
  pChild = &pNotes->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isElement());
  CPPUNIT_ASSERT(pChild->getName() == "p");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("mixed") != std::string::npos);
  pChild = &pNotes->getChild(2);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("paragraphs") != std::string::npos);
  pChild = &pNotes->getChild(3);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isElement());
  CPPUNIT_ASSERT(pChild->getName() == "p");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("set ") != std::string::npos);

  SBMLDocument *pDocument = new SBMLDocument(2, 4);
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->createModel("test_model");
  CPPUNIT_ASSERT(pModel != NULL);
  int set_result = pModel->setNotes(pNotes);
  CPPUNIT_ASSERT(set_result == LIBSBML_OPERATION_SUCCESS);
  delete pDocument;
  delete pNotes;
}

void test000096::test_export_model_notes_5()
{
  XMLNode* pNotes = CSBMLExporter::createSBMLNotes(NOTES_STRING_5);
  CPPUNIT_ASSERT(pNotes != NULL);
  CPPUNIT_ASSERT(pNotes->getName() == "body");
  CPPUNIT_ASSERT(pNotes->getURI() == "http://www.w3.org/1999/xhtml");
  CPPUNIT_ASSERT(pNotes->hasNamespaceURI("http://www.w3.org/1999/xhtml") == true);

  CPPUNIT_ASSERT(pNotes->getNumChildren() == 4);
  XMLNode* pChild = &pNotes->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("This") != std::string::npos);
  pChild = &pNotes->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isElement());
  CPPUNIT_ASSERT(pChild->getName() == "p");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("mixed") != std::string::npos);
  pChild = &pNotes->getChild(2);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("paragraphs") != std::string::npos);
  pChild = &pNotes->getChild(3);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isElement());
  CPPUNIT_ASSERT(pChild->getName() == "p");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("set ") != std::string::npos);

  SBMLDocument *pDocument = new SBMLDocument(2, 4);
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->createModel("test_model");
  CPPUNIT_ASSERT(pModel != NULL);
  int set_result = pModel->setNotes(pNotes);
  CPPUNIT_ASSERT(set_result == LIBSBML_OPERATION_SUCCESS);
  delete pDocument;
  delete pNotes;
}

void test000096::test_export_model_notes_6()
{
  XMLNode* pNotes = CSBMLExporter::createSBMLNotes(NOTES_STRING_6);
  CPPUNIT_ASSERT(pNotes != NULL);
  CPPUNIT_ASSERT(pNotes->getName() == "body");
  CPPUNIT_ASSERT(pNotes->getURI() == "http://www.w3.org/1999/xhtml");
  CPPUNIT_ASSERT(pNotes->hasNamespaceURI("http://www.w3.org/1999/xhtml") == true);

  CPPUNIT_ASSERT(pNotes->getNumChildren() == 4);
  XMLNode* pChild = &pNotes->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("This") != std::string::npos);
  pChild = &pNotes->getChild(1);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isElement());
  CPPUNIT_ASSERT(pChild->getName() == "p");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("mixed") != std::string::npos);
  pChild = &pNotes->getChild(2);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("paragraphs") != std::string::npos);
  pChild = &pNotes->getChild(3);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isElement());
  CPPUNIT_ASSERT(pChild->getName() == "p");
  CPPUNIT_ASSERT(pChild->getNumChildren() == 1);
  pChild = &pChild->getChild(0);
  CPPUNIT_ASSERT(pChild != NULL);
  CPPUNIT_ASSERT(pChild->isText());
  CPPUNIT_ASSERT(pChild->getCharacters().find("set ") != std::string::npos);

  SBMLDocument *pDocument = new SBMLDocument(2, 4);
  CPPUNIT_ASSERT(pDocument != NULL);
  Model* pModel = pDocument->createModel("test_model");
  CPPUNIT_ASSERT(pModel != NULL);
  int set_result = pModel->setNotes(pNotes);
  CPPUNIT_ASSERT(set_result == LIBSBML_OPERATION_SUCCESS);
  delete pDocument;
  delete pNotes;
}

const char* test000096::NOTES_STRING_1 =
  "This is a test\n"
  "to see if simple text is\n"
  "set correctly.\n"
  ;

const char* test000096::NOTES_STRING_2 =
  "<p>This is a test\n"
  "to see if a single paragraph is\n"
  "set correctly.</p>\n"
  ;

const char* test000096::NOTES_STRING_3 =
  "<p>This is a test</p>\n"
  "<p>to see if a several paragraphs are</p>\n"
  "<p>set correctly.</p>\n"
  ;

const char* test000096::NOTES_STRING_4 =
  "This is a test\n"
  "<p>to see if text mixed with</p>\n"
  "several paragraphs is\n"
  "<p>set correctly.</p>\n"
  ;

const char* test000096::NOTES_STRING_5 =
  "<body>\n"
  "This is a test\n"
  "<p>to see if body element plus text mixed with</p>\n"
  "several paragraphs is\n"
  "<p>set correctly.</p>\n"
  "</body>\n"
  ;

const char* test000096::NOTES_STRING_6 =
  "<body xmlns=\"http://www.w3.org/1999/xhtml\"> \n"
  "This is a test\n"
  "<p>to see if body element plus text mixed with</p>\n"
  "several paragraphs is\n"
  "<p>set correctly.</p>\n"
  "</body>\n"
  ;
