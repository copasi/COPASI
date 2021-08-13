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

  auto & task = dynamic_cast<CTrajectoryTask&>( (*dm->getTaskList())["Time-Course"]);
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

  auto * sim = dynamic_cast<SedUniformTimeCourse*> (doc->getSimulation(0));
  REQUIRE(sim != NULL);
  
  SEDMLImporter imp;
  imp.setSEDMLDocument(doc);
  imp.setDataModel(dm);
  imp.updateCopasiTaskForSimulation(sim, dm->getCopasi2SEDMLMap());

  REQUIRE(problem->getDuration() == 10);
  REQUIRE(problem->getStepNumber() == 100);

  delete doc;

  CRootContainer::removeDatamodel(dm);
}
