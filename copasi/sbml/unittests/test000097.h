// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef TEST_000097_H__
#define TEST_000097_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Tests for dealing with render information
 */

class CDataModel;

class test000097 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000097);
  CPPUNIT_TEST(test_import_local_render_information);
  CPPUNIT_TEST(test_import_global_render_information);
  CPPUNIT_TEST(test_export_local_render_information);
  CPPUNIT_TEST(test_export_global_render_information);
  CPPUNIT_TEST(test_save_local_render_information);
  CPPUNIT_TEST(test_save_global_render_information);
  CPPUNIT_TEST(test_read_local_render_information);
  CPPUNIT_TEST(test_read_global_render_information);
  CPPUNIT_TEST(test_readexport_local_render_information);
  CPPUNIT_TEST(test_readexport_global_render_information);
  CPPUNIT_TEST(test_importexport_local_render_information);
  CPPUNIT_TEST(test_importexport_global_render_information);
  CPPUNIT_TEST(test_readwrite_local_render_information);
  CPPUNIT_TEST(test_readwrite_global_render_information);
  CPPUNIT_TEST(test_importwrite_local_render_information);
  CPPUNIT_TEST(test_importwrite_global_render_information);
  CPPUNIT_TEST_SUITE_END();

protected:
  // SBML model with local render information
  static const char* SBML_MODEL_1;
  // SBML model with global render information
  static const char* SBML_MODEL_2;
  // COPASI model with local render information
  static const char* CPS_MODEL_1;
  // COPASI model with global render information
  static const char* CPS_MODEL_2;

  CDataModel* pDataModel;

  // method the create a model with a single compartment
  // and a small layout
  void createModel();

  // method to add a local render information object
  // to the given model
  void addLocalRenderInformation();

  // method to add a global render information object
  // to the given model
  void addGlobalRenderInformation();

public:
  void setUp();

  void tearDown();

  // tests whether we are importing local render information
  void test_import_local_render_information();

  // tests whether we are importing global render information
  void test_import_global_render_information();

  // tests whether we are exporting local render information
  void test_export_local_render_information();

  // tests whether we are exporting global render information
  void test_export_global_render_information();

  // tests whether we are exporting local render information
  // that has been read
  void test_readexport_local_render_information();

  // tests whether we are exporting global render information
  // that has been read
  void test_readexport_global_render_information();

  // tests whether we are exporting local render information
  // that has been import
  void test_importexport_local_render_information();

  // tests whether we are exporting global render information
  // that has been import
  void test_importexport_global_render_information();

  // tests whether we are saving local render information
  void test_save_local_render_information();

  // tests whether we are saving global render information
  void test_save_global_render_information();

  // test whether we are reading local render information
  void test_read_local_render_information();

  // test whether we are reading global render information
  void test_read_global_render_information();

  // test whether we are writing local render information
  // that has been read
  void test_readwrite_local_render_information();

  // test whether we are writing global render information
  // that has been read
  void test_readwrite_global_render_information();

  // test whether we are writing local render information
  // that has been imported
  void test_importwrite_local_render_information();

  // test whether we are writing global render information
  // that has been importer
  void test_importwrite_global_render_information();
};

#endif /* TEST000097_H__ */
