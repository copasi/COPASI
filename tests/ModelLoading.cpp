// Copyright (C) 2021 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// BEGIN: Copyright
// END: Copyright

// BEGIN: License
// Licensed under the Artistic License 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//   https://opensource.org/licenses/Artistic-2.0
// END: License

#include "catch.hpp"
#include <limits>

#include <copasi/core/CRootContainer.h>
#include <copasi/CopasiDataModel/CDataModel.h>
#include <copasi/utilities/CDirEntry.h>

#include <copasi/CopasiTypes.h>

extern std::string getTestFile(const std::string & fileName);

TEST_CASE("Load model", "[COPASI]")
{
  CDataModel * pDataModel = CRootContainer::addDatamodel();
  REQUIRE(pDataModel != nullptr);

  // Loading from file
  REQUIRE(pDataModel->loadFromFile(getTestFile("test-data/brusselator.gps")) == true);
  REQUIRE(pDataModel->loadFromFile(getTestFile("test-data/brusselator.cps")) == true);
  REQUIRE(pDataModel->loadFromFile(getTestFile("test-data/brusselator.xml")) == true);
  REQUIRE(pDataModel->loadFromFile(getTestFile("test-data/brusselator.sedml")) == true);
  REQUIRE(pDataModel->loadFromFile(getTestFile("test-data/brusselator.omex")) == true);

  std::stringstream FileContent;

  {
    FileContent.str("");
    std::ifstream File(getTestFile("test-data/brusselator.gps"));
    FileContent << File.rdbuf();
  }
  REQUIRE(pDataModel->loadFromString(FileContent.str()) == true);

  {
    FileContent.str("");
    std::ifstream File(getTestFile("test-data/brusselator.cps"));
    FileContent << File.rdbuf();
  }
  REQUIRE(pDataModel->loadFromString(FileContent.str(), CDirEntry::dirName(getTestFile("test-data/brusselator.cps"))) == true);

  {
    FileContent.str("");
    std::ifstream File(getTestFile("test-data/brusselator.xml"));
    FileContent << File.rdbuf();
  }
  REQUIRE(pDataModel->loadFromString(FileContent.str()) == true);

  {
    FileContent.str("");
    std::ifstream File(getTestFile("test-data/brusselator.sedml"));
    FileContent << File.rdbuf();
  }
  REQUIRE(pDataModel->loadFromString(FileContent.str(), CDirEntry::dirName(getTestFile("test-data/brusselator.sedml"))) == true);

  {
    FileContent.str("");
    std::ifstream File(getTestFile("test-data/brusselator.omex"));
    FileContent << File.rdbuf();
  }
#ifndef WIN32
  // this test fails on Windows as the archive created is invalid
  // so skipping this test there for now
  REQUIRE(pDataModel->loadFromString(FileContent.str()) == true);
#endif

  CRootContainer::removeDatamodel(pDataModel);
}

TEST_CASE("Update Model", "[COPASI]")
{
  CDataModel * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  std::string test_file = getTestFile("test-data/Issue3050.cps");

  REQUIRE(dm->loadModel(test_file, NULL) == true);

  auto * model = dm->getModel();
  model->applyInitialValues();

  auto& x = model->getModelValues()["x"];
  auto & y = model->getModelValues()["y"];
  REQUIRE(x.getInitialValue() == 1);
  REQUIRE(y.getInitialValue() == 1);

  auto & optimization = (*dm->getTaskList())["Optimization"];
  REQUIRE(optimization.isUpdateModel());
  // executing the optimization task should set x and y to the specified values

  auto * optProblem = dynamic_cast< COptProblem * >(optimization.getProblem());
  REQUIRE(optProblem->getOptItem(0).getStartValue() == 2);
  REQUIRE(optProblem->getOptItem(1).getStartValue() == 2);

  optimization.initialize(CCopasiTask::OUTPUT_SE, NULL, NULL);
  optimization.process(true);
  optimization.restore();

  REQUIRE(x.getInitialValue() == 2);
  REQUIRE(y.getInitialValue() == 2);

  // reset the values again
  x.setInitialValue(1);
  y.setInitialValue(1);
  model->updateInitialValues(CCore::Framework::Concentration);
  model->applyInitialValues();

  REQUIRE(x.getInitialValue() == 1);
  REQUIRE(y.getInitialValue() == 1);

  auto & scan = (*dm->getTaskList())["Scan"];
  REQUIRE(scan.isUpdateModel());

  scan.initialize(CCopasiTask::OUTPUT_SE, NULL, NULL);
  scan.process(true);
  scan.restore();

  // now this should also be 2
  REQUIRE(x.getInitialValue() == 2);
  REQUIRE(y.getInitialValue() == 2);

  CRootContainer::removeDatamodel(dm);
}
