// Copyright (C) 2021 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>
#include <copasi/report/CDataHandler.h>
#include <copasi/output/COutputHandler.h>

TEST_CASE("1: load model, simulate, collect data", "[copasi, datahandler]")
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
    inv_handler.addDuringName({"CN=Root,Model=The Brusselator"});  // this should not work and give a warning during compile, and stop it

    REQUIRE(inv_handler.compile({dm}) == false);

    auto text = CCopasiMessage::getAllMessageText();
    REQUIRE(text.find("CN=Root,Model=The Brusselator") != std::string::npos);

    CCopasiMessage::clearDeque();

    CDataHandler handler;
    handler.addDuringName({"CN=Root,Model=The Brusselator,Reference=Time"});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[X],Reference=Concentration"});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[Y],Reference=Concentration"});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Reactions[R1],Reference=Flux"});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Reactions[R2],Reference=Flux"});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Reactions[R3],Reference=Flux"});
    handler.addDuringName({"CN=Root,Model=The Brusselator,Vector=Reactions[R4],Reference=Flux"});

    auto& task = dynamic_cast<CTrajectoryTask&>((*dm->getTaskList())["Time-Course"]);
    REQUIRE(task.initialize(CCopasiTask::OUTPUT_DURING, &handler, NULL) == true);
    REQUIRE(task.process(true) == true);
    REQUIRE(task.restore());

    auto & data = handler.getDuringData();

    REQUIRE(data.size() > 0);
    REQUIRE(data[0].size() == 7);

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

TEST_CASE("ensure that data handler with function evaluations can be compiled", "[copasi, datahandler]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);

  CDataHandler handler;
  handler.addDuringName({"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Function Evaluations"});
  handler.addDuringName({"CN=Root,Vector=TaskList[Optimization],Problem=Optimization,Reference=Best Value"});

  REQUIRE(handler.compile({dm}) == true);

  // lets try whether it works now

  auto& task = (*dm->getTaskList())["Optimization"];
  task.setMethodType(CTaskEnum::Method::LevenbergMarquardt);

  auto * problem = dynamic_cast< COptProblem * >(task.getProblem());

  {
    auto & item = problem->addOptItem(
    {"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=InitialConcentration"});
    item.setLowerBound({"0.0001"});
    item.setUpperBound({"100"});
    item.setStartValue(0.5);
  }

  {
    auto & item = problem->addOptItem({"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[B],Reference=InitialConcentration"});
    item.setLowerBound({"0.0001"});
    item.setUpperBound({"100"});
    item.setStartValue(3);
  }

  std::stringstream exp;
  exp << "<"
      << (dm->getModel()->getMetabolites()[0]).getConcentrationRateReference()->getCN()
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
