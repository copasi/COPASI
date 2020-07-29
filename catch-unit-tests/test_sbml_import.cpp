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

    unit = sbml_mod->getUnitDefinition("unit_2");
    REQUIRE(unit != NULL);
    expression = importer.createUnitExpressionFor(unit);
    REQUIRE(expression == "d");

    unit = sbml_mod->getUnitDefinition("unit_3");
    REQUIRE(unit != NULL);
    expression = importer.createUnitExpressionFor(unit);
    REQUIRE((expression == "1/(#*d)" || expression == "1/(d*#)"));


    delete sbml_doc;

  }

  SECTION("unit export")
  {
    REQUIRE(dm->newModel(NULL, true) == true);

    auto * mod = dm->getModel();
    REQUIRE(mod != NULL);
    auto * p = mod->createModelValue("p1");
    REQUIRE(p != NULL);
    p->setValue(1);
    p->setUnitExpression("d");

    p = mod->createModelValue("p2");
    REQUIRE(p != NULL);
    p->setValue(1);
    p->setUnitExpression("1/(#*d)");

    CSBMLExporter exp;
    auto sbml = exp.exportModelToString(*dm, 2, 4);

    auto * doc = readSBMLFromString(sbml.c_str());
    REQUIRE(doc != NULL);
    auto * sbml_mod = doc->getModel();
    REQUIRE(sbml_mod != NULL);

    auto * unitdef = sbml_mod->getUnitDefinition("unit_0");
    REQUIRE(unitdef != NULL);
    REQUIRE(unitdef->getNumUnits() == 1);
    auto * unit = unitdef->getUnit(0);
    REQUIRE(unit != NULL);
    REQUIRE(unit->getScale() == 0);
    REQUIRE(unit->getMultiplier() == 86400);
    REQUIRE(unit->getExponent() == 1);
    REQUIRE(unit->getKind() == UNIT_KIND_SECOND);

    unitdef = sbml_mod->getUnitDefinition("unit_1");
    REQUIRE(unitdef != NULL);
    REQUIRE(unitdef->getNumUnits() == 2);
    unit = unitdef->getUnit(0);
    REQUIRE(unit != NULL);
    REQUIRE(unit->getScale() == 0);
    REQUIRE(unit->getMultiplier() == 86400);
    REQUIRE(unit->getExponent() == -1);
    REQUIRE(unit->getKind() == UNIT_KIND_SECOND);

    unit = unitdef->getUnit(1);
    REQUIRE(unit != NULL);
    REQUIRE(unit->getScale() == 0);
    REQUIRE(unit->getMultiplier() == 1);
    REQUIRE(unit->getExponent() == -1);
    REQUIRE(unit->getKind() == UNIT_KIND_ITEM);

  }


  CRootContainer::destroy();
}
