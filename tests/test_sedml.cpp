// Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>
#include <sbml/SBMLTypes.h>
#include <sedml/SedTypes.h>

TEST_CASE("exporting sedml file with non-zero initial time", "[copasi,sedml]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  dm->newModel(NULL, true);

  auto * model = dm->getModel();

  auto * r = model->createReaction("R1");
  r->setReactionScheme("A -> B");

  model->setInitialTime(10.0);
  model->updateInitialValues(model->getInitialValueReference());

  auto & task = dynamic_cast<CTrajectoryTask&>((*dm->getTaskList())["Time-Course"]);
  task.setScheduled(true);
  auto * problem = dynamic_cast< CTrajectoryProblem * >(task.getProblem());
  REQUIRE(problem != NULL);

  problem->setDuration(10);
  problem->setStepNumber(100);

  std::string sedml = dm->exportSEDMLToString(NULL, 1, 4);

  REQUIRE(sedml.find("<uniformTimeCourse id=\"sim1\" initialTime=\"10") != std::string::npos);

  // now lets try and read it back in ensuring that the initial time is being set.
  model->setInitialTime(0.0);
  model->updateInitialValues(model->getInitialValueReference());
  // also reset the task values, to see that hey are updated correctly
  problem->setDuration(1);
  problem->setStepNumber(10);

  auto * doc = readSedMLFromString(sedml.c_str());
  REQUIRE(doc->getNumErrors(LIBSEDML_SEV_ERROR) == 0);

  auto * sim = dynamic_cast<SedUniformTimeCourse*>(doc->getSimulation(0));
  REQUIRE(sim != NULL);

  SEDMLImporter imp;
  imp.setSEDMLDocument(doc);
  imp.setDataModel(dm);
  imp.updateCopasiTaskForSimulation(sim);

  REQUIRE(problem->getDuration() == 10);
  REQUIRE(problem->getStepNumber() == 100);

  delete doc;

  CRootContainer::removeDatamodel(dm);
}


TEST_CASE("convert sedml types and colors", "[copasi,sedml]")
{
  REQUIRE(SEDMLUtils::argbToRgba("112233") == "112233");
  REQUIRE(SEDMLUtils::argbToRgba("#F0C800") == "#F0C800");
  REQUIRE(SEDMLUtils::argbToRgba("#FFF0C800") == "#F0C800FF");
  REQUIRE(SEDMLUtils::argbToRgba("FFF0C800") == "#F0C800FF");
  REQUIRE(SEDMLUtils::argbToRgba("FFF0C800", false) == "F0C800FF");

  REQUIRE(SEDMLUtils::rgbaToArgb("112233") == "112233");
  REQUIRE(SEDMLUtils::rgbaToArgb("#F0C800") == "#F0C800");
  REQUIRE(SEDMLUtils::rgbaToArgb("#F0C800FF") == "#FFF0C800");
  REQUIRE(SEDMLUtils::rgbaToArgb("F0C800FF") == "#FFF0C800");
  REQUIRE(SEDMLUtils::rgbaToArgb("F0C800FF", false) == "FFF0C800");

  REQUIRE(SEDMLUtils::lineTypeFromSed(SEDML_LINETYPE_SOLID) == (int) CPlotItem::LineStyle::Solid);
  REQUIRE(SEDMLUtils::lineTypeFromSed(SEDML_LINETYPE_DASH) == (int) CPlotItem::LineStyle::Dashed);
  REQUIRE(SEDMLUtils::lineTypeFromSed(SEDML_LINETYPE_DOT) == (int) CPlotItem::LineStyle::Dotted);

  REQUIRE(SEDMLUtils::lineTypeToSed((int) CPlotItem::LineStyle::Solid) == SEDML_LINETYPE_SOLID);
  REQUIRE(SEDMLUtils::lineTypeToSed((int) CPlotItem::LineStyle::Dashed) == SEDML_LINETYPE_DASH);
  REQUIRE(SEDMLUtils::lineTypeToSed((int) CPlotItem::LineStyle::Dotted) == SEDML_LINETYPE_DOT);

  REQUIRE(SEDMLUtils::symbolFromSed(SEDML_MARKERTYPE_CIRCLE) == (int) CPlotItem::SymbolType::Circle);
  REQUIRE(SEDMLUtils::symbolFromSed(SEDML_MARKERTYPE_STAR) == (int) CPlotItem::SymbolType::Star);

  REQUIRE(SEDMLUtils::symbolToSed((int) CPlotItem::SymbolType::Circle) == SEDML_MARKERTYPE_CIRCLE);
  REQUIRE(SEDMLUtils::symbolToSed((int) CPlotItem::SymbolType::Star) == SEDML_MARKERTYPE_STAR);
  REQUIRE(SEDMLUtils::symbolToSed((int) CPlotItem::SymbolType::LargeCross) == SEDML_MARKERTYPE_PLUS);
  REQUIRE(SEDMLUtils::symbolToSed((int) CPlotItem::SymbolType::SmallCross) == SEDML_MARKERTYPE_PLUS);
  REQUIRE(SEDMLUtils::symbolToSed((int) CPlotItem::SymbolType::Plus) == SEDML_MARKERTYPE_PLUS);
}


TEST_CASE("importing new curves and plots", "[copasi,sedml]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  REQUIRE(dm->importSEDML(getTestFile("test-data/test_shaded_area_overlap_order.sedml")) == true);

  auto* plots = dm->getPlotDefinitionList();
  REQUIRE(plots->size() == 1);


  CRootContainer::removeDatamodel(dm);
}
