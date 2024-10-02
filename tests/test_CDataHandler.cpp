// Copyright (C) 2021 - 2024 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>
#include <copasi/report/CDataHandler.h>
#include <copasi/output/COutputHandler.h>

TEST_CASE("1: load model, simulate, collect data", "[copasi][datahandler]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  SECTION("brusselator example")
  {

    REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);

    // change the initial time
    dm->getModel()->setInitialTime(20);
    dm->getModel()->updateInitialValues(dm->getModel()->getInitialValueReference());
    dm->getModel()->forceCompile(NULL);
    dm->getModel()->applyInitialValues();

    CCopasiMessage::clearDeque();

    CDataHandler inv_handler;
    inv_handler.addDuringName({"CN=Root,Model=The Brusselator", dm});  // this should not work and give a warning during compile, and stop it

    REQUIRE(inv_handler.compile({dm}) == false);

    auto text = CCopasiMessage::getAllMessageText();
    REQUIRE(text.find("CN=Root,Model=The Brusselator") != std::string::npos);

    CCopasiMessage::clearDeque();

    CDataHandler handler;
    handler.addDuringName({"CN=Root,Model=The Brusselator,Reference=Time", dm});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[X],Reference=Concentration", dm});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[Y],Reference=Concentration", dm});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Reactions[R1],Reference=Flux", dm});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Reactions[R2],Reference=Flux", dm});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Reactions[R3],Reference=Flux", dm});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Reactions[R4],Reference=Flux", dm});

    // add test to verify that array element references can be correctly resolved
    handler.addDuringName({"CN=Root,Vector=TaskList[Metabolic Control Analysis],Method=MCA Method (Reder),Array=Scaled elasticities[(R1)][X]", dm});

    auto& task = dynamic_cast<CTrajectoryTask&>((*dm->getTaskList())["Time-Course"]);
    REQUIRE(task.initialize(CCopasiTask::OUTPUT_DURING, &handler, NULL) == true);
    REQUIRE(task.process(true) == true);
    REQUIRE(task.restore());

    auto & data = handler.getDuringData();

    REQUIRE(data.size() > 0);
    REQUIRE(data[0].size() == 8);

    {
      REQUIRE(task.initialize(CCopasiTask::ONLY_TIME_SERIES, dm, NULL) == true);
      REQUIRE(task.process(true) == true);
      REQUIRE(task.restore());

      auto & ts = task.getTimeSeries();
      REQUIRE(data.size() > 0);
      REQUIRE(ts.getTitle(0) == "Time");
      REQUIRE(ts.getData(0, 0) == data[0][0]);
    }
  }
  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("ensure that data handler with function evaluations can be compiled", "[copasi][datahandler]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);

  CDataHandler handler;
  handler.addDuringName({"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations", dm});
  handler.addDuringName({"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value", dm});

  REQUIRE(handler.compile({dm}) == true);

  // lets try whether it works now

  auto& task = (*dm->getTaskList())["Optimization"];
  task.setMethodType(CTaskEnum::Method::LevenbergMarquardt);

  auto * problem = dynamic_cast< COptProblem * >(task.getProblem());

  {
    auto & item = problem->addOptItem(
    {"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=InitialConcentration", dm});
    item.setLowerBound(0.0001);
    item.setUpperBound(100);
    item.setStartValue(0.5);
  }

  {
    auto & item = problem->addOptItem({"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[B],Reference=InitialConcentration", dm});
    item.setLowerBound(0.0001);
    item.setUpperBound(100);
    item.setStartValue(3);
  }

  std::stringstream exp;
  exp << "<"
      << (dm->getModel()->getMetabolites()[0]).getConcentrationRateReference()->getStringCN()
      << ">";

  problem->setObjectiveFunction(exp.str());
  problem->setRandomizeStartValues(false);
  problem->setSubtaskType(CTaskEnum::Task::timeCourse);

  REQUIRE(task.initialize(CCopasiTask::OUTPUT_DURING, &handler, NULL));
  REQUIRE(task.process(true));

  auto data = handler.getDuringData();
  dm->saveModel("opt.cps", NULL, true);
  CRootContainer::removeDatamodel(dm);
}


TEST_CASE("Test resolving of reactions with )", "[copasi][datahandler]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);

  auto * model = dm->getModel();
  auto* reaction = model->createReaction("Reaction with spaces and (steps)");
  reaction->setReactionScheme("A -> D");
  model->compileIfNecessary(NULL);

  // try and retrieve the reaction by display name: 
  auto fluxName = reaction->getFluxReference()->getObjectDisplayName();
  auto* obj = dm->findObjectByDisplayName(fluxName);
  REQUIRE(obj != nullptr);

  CRootContainer::removeDatamodel(dm);
}
