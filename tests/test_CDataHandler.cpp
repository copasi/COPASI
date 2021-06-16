// Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>
#include <copasi/report/CDataHandler.h>

TEST_CASE("1: load model, simulate, collect data", "[copasi, datahandler]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  SECTION("brusselator example")
  {

    REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);

    CCopasiMessage::clearDeque();

    CDataHandler inv_handler;
    inv_handler.addDuringName( {"CN=Root,Model=The Brusselator"}); // this should not work and give a warning during compile, and stop it

    REQUIRE(inv_handler.compile( {dm}) == false);

    auto text = CCopasiMessage::getAllMessageText();
    REQUIRE(text.find("CN=Root,Model=The Brusselator") != std::string::npos);

    CCopasiMessage::clearDeque();

    CDataHandler handler;
    handler.addDuringName( {"CN=Root,Model=The Brusselator,Reference=Time"});
    handler.addDuringName( {"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[X],Reference=Concentration"});
    handler.addDuringName( {"CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[Y],Reference=Concentration"});
    handler.addDuringName( {"CN=Root,Model=The Brusselator,Vector=Reactions[R1],Reference=Flux"});
    handler.addDuringName( {"CN=Root,Model=The Brusselator,Vector=Reactions[R2],Reference=Flux"});
    handler.addDuringName( {"CN=Root,Model=The Brusselator,Vector=Reactions[R3],Reference=Flux"});
    handler.addDuringName( {"CN=Root,Model=The Brusselator,Vector=Reactions[R4],Reference=Flux"});

    auto& task = (*dm->getTaskList())["Time-Course"];
    REQUIRE(task.initialize(CCopasiTask::OUTPUT_DURING, &handler, NULL) == true);
    REQUIRE(task.process(true) == true);
    REQUIRE(task.restore());

    auto & data = handler.getDuringData();

    REQUIRE(data.size() > 0);
    REQUIRE(data[0].size() == 7);

  }
  CRootContainer::removeDatamodel(dm);
}
