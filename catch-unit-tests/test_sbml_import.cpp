// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>
#include <sbml/SBMLTypes.h>


TEST_CASE("1: importing sbml files", "[copasi,sbml]")
{

  CRootContainer::init(0, NULL, false);
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  SECTION("unit import")
  {
    std::string test_file = getTestFile("test-data/unit_test.xml");
    auto* sbml_doc = readSBMLFromFile(test_file.c_str());
    REQUIRE(sbml_doc != NULL);
    auto* sbml_mod = sbml_doc->getModel();
    REQUIRE(sbml_mod != NULL);

    auto * unit = sbml_mod->getUnitDefinition("unit_1");
    REQUIRE(unit != NULL);

    SBMLImporter importer;

    std::string expression = importer.createUnitExpressionFor(unit);

    REQUIRE(expression == "l/(nmol*s)");

    delete sbml_doc;

  }



  CRootContainer::destroy();
}
