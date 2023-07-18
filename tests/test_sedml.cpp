// Copyright (C) 2021 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>
#include <copasi/utilities/CCopasiException.h>
#include <sbml/SBMLTypes.h>
#include <sedml/SedTypes.h>

TEST_CASE("exporting sedml file with non-zero initial time", "[copasi,sedml]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  dm->newModel(NULL, true);

  auto * model = dm->getModel();

  auto * r = model->createReaction("R1");
  r->setReactionScheme("A -> B");

  model->setInitialTime(10.0);
  model->updateInitialValues(model->getInitialValueReference());

  auto & task = dynamic_cast<CTrajectoryTask&>((*dm->getTaskList())["Time-Course"]);
  task.setScheduled(true);
  auto * problem = dynamic_cast< CTrajectoryProblem * >(task.getProblem());
  REQUIRE(problem != nullptr);

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
  REQUIRE(sim != nullptr);

  SEDMLImporter imp;
  imp.setDataModel(dm);
  imp.initializeContent();
  imp.setSEDMLDocument(doc);
  imp.setCopasiModel(model);
  imp.updateCopasiTaskForSimulation(sim, dm->getTaskList());

  REQUIRE(problem->getDuration() == 10);
  REQUIRE(problem->getStepNumber() == 100);

  delete doc;

  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("convert sedml types and colors", "[copasi,sedml]")
{
  REQUIRE(SEDMLUtils::argbToRgba("112233") == "#112233");
  REQUIRE(SEDMLUtils::argbToRgba("#F0C800") == "#F0C800");
  REQUIRE(SEDMLUtils::argbToRgba("#FFF0C800") == "#F0C800FF");
  REQUIRE(SEDMLUtils::argbToRgba("FFF0C800") == "#F0C800FF");
  REQUIRE(SEDMLUtils::argbToRgba("FFF0C800", false) == "F0C800FF");
  REQUIRE(SEDMLUtils::argbToRgba("#FF0000", false) == "FF0000");

  REQUIRE(SEDMLUtils::rgbaToArgb("112233") == "#112233");
  REQUIRE(SEDMLUtils::rgbaToArgb("#F0C800") == "#F0C800");
  REQUIRE(SEDMLUtils::rgbaToArgb("#F0C800FF") == "#FFF0C800");
  REQUIRE(SEDMLUtils::rgbaToArgb("F0C800FF") == "#FFF0C800");
  REQUIRE(SEDMLUtils::rgbaToArgb("F0C800FF", false) == "FFF0C800");
  REQUIRE(SEDMLUtils::rgbaToArgb("#FF0000", false) == "FF0000");

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
  REQUIRE(dm != nullptr);

  REQUIRE(
    dm->importSEDML(
      getTestFile("test-data/test_shaded_area_overlap_order.sedml")
    ) == true);

  auto* plots = dm->getPlotDefinitionList();
  REQUIRE(plots->size() == 1);

  // test that we can export it again
  std::string sedml = dm->exportSEDMLToString(NULL, 1, 4);

  // export with sbml namespaces
  CSEDMLExporter exp;
  exp.setSBMLNamespaces(3, 1);
  std::string sedmlwith_ns =
    exp.exportModelAndTasksToString(*dm, "model.xml", 1, 4);

  REQUIRE(sedmlwith_ns.find("http://www.sbml.org/sbml/level3/version1/core") != std::string::npos);

  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("importing variables with terms", "[copasi,sedml]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  REQUIRE(dm->importSEDML(getTestFile("test-data/concentration_amount.sedml")) == true);

  auto * plots = dm->getPlotDefinitionList();
  REQUIRE(plots->size() == 3);

  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("export / import nested scan", "[copasi,sedml]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  REQUIRE(dm->loadModel(getTestFile("test-data/NestedScan.cps"), NULL) == true);

  auto sedml = dm->exportSEDMLToString(NULL, 1, 4);

  auto * doc = readSedMLFromString(sedml.c_str());

  REQUIRE(doc->getNumErrors(LIBSEDML_SEV_ERROR) == 0);

  REQUIRE(doc->getDataGenerator("Rtot_1_task3") == NULL);
  REQUIRE(doc->getDataGenerator("Rtot_1_task5") != NULL);

  // the model has a timecourse, and a steady state scan with 3 variables, as such it should not be complex
  REQUIRE(SedmlInfo(doc).isComplex() == false);

  // if we had another time course then it should be complex
  {
    auto * task = doc->getTask(0)->clone();
    task->setId("anotherTaks");
    doc->getListOfTasks()->appendAndOwn(task);
    REQUIRE(SedmlInfo(doc).isComplex() == true);
  }

  delete doc;

  // now import
  SedmlImportOptions opts;
  opts.setSkipModelImport(true);
  dm->importSEDMLFromString(sedml, "", NULL, true, &opts);
  REQUIRE(dynamic_cast< CScanProblem * >(dm->getTaskList()->operator[]("Scan").getProblem())->getNumberOfScanItems() == 3);

  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("Export different plot styles", "[copasi,sedml]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);

  auto * m = dm->getModel();
  REQUIRE(m != NULL);

  // export sbml so we have sbml ids
  std::string sbml = dm->exportSBMLToString(NULL, 3, 1);

  // export sedml
  std::string sedml = dm->exportSEDMLToString(NULL, 1, 4);

  auto * doc = readSedMLFromString(sedml.c_str());

  REQUIRE(doc->getNumErrors(LIBSEDML_SEV_ERROR) == 0);

  delete doc;

  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("generating variables with terms", "[copasi,sedml]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);

  auto * m = dm->getModel();

  auto * pMV = m->createModelValue("g_mv", 1);

  // export to sbml so we have sbml ids for everything
  std::string sbml = dm->exportSBMLToString(NULL, 3, 1);

  {
    REQUIRE(VariableInfo(m).getSymbol() == SEDML_TIME_URN);
    REQUIRE(VariableInfo(m->getValueReference()).getSymbol() == SEDML_TIME_URN);
  }

  {
    REQUIRE(VariableInfo(&m->getCompartments()[0]).getXpath() == "/sbml:sbml/sbml:model/sbml:listOfCompartments/sbml:compartment[@id='compartment']");
    REQUIRE(VariableInfo(m->getCompartments()[0].getRateReference()).getTerm() == SEDML_KISAO_RATE);
  }

  {
    REQUIRE(VariableInfo(&m->getMetabolites()[0]).getXpath() == "/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id='X']");
    REQUIRE(VariableInfo(m->getMetabolites()[0].getConcentrationReference()).getTerm() == SEDML_KISAO_CONCENTRATION);
    REQUIRE(VariableInfo(m->getMetabolites()[0].getValueReference()).getTerm() == SEDML_KISAO_PARTICLENUMBER);
    REQUIRE(VariableInfo(m->getMetabolites()[0].getConcentrationRateReference()).getTerm() == SEDML_KISAO_CONCENTRATION_RATE);
    REQUIRE(VariableInfo(m->getMetabolites()[0].getRateReference()).getTerm() == SEDML_KISAO_PARTICLE_RATE);
  }

  {
    REQUIRE(VariableInfo(&m->getModelValues()[0]).getXpath() == "/sbml:sbml/sbml:model/sbml:listOfParameters/sbml:parameter[@id='g_mv']");
    REQUIRE(VariableInfo(m->getModelValues()[0].getRateReference()).getTerm() == SEDML_KISAO_RATE);
  }

  {
    REQUIRE(VariableInfo(&m->getReactions()[0]).getXpath() == "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id='R1']");
    REQUIRE(VariableInfo(m->getReactions()[0].getFluxReference()).getTerm() == SEDML_KISAO_FLUX);
    REQUIRE(VariableInfo(m->getReactions()[0].getParameterObjects("k1").at(0)).getXpath() == "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id='R1']/sbml:kineticLaw/sbml:listOfParameters/sbml:parameter[@id='k1']");
  }

  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("importing document with remote model should fail", "[copasi,sedml]")
{
  // generate sedml

  auto* doc = new SedDocument(1, 4);
  auto* model = doc->createModel();
  model->setId("model");
  model->setLanguage("urn:sedml:language:sbml");
  model->setSource("urn:miriam:biomodels.db:BIOMD0000000005");
  auto sedml = writeSedMLToStdString(doc);
  delete doc;


  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  try
    {
      dm->importSEDMLFromString(sedml, "", NULL, true);
    }
  catch (const CCopasiException& e)
    {
      REQUIRE(e.getMessage().getText().find("remote") != std::string::npos);
    }

  CRootContainer::removeDatamodel(dm);
}
