// Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the
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

extern std::string getTestFile(const std::string & fileName);

TEST_CASE("Load model", "[COPASI]")
{
  CDataModel * pDataModel = CRootContainer::addDatamodel();
  REQUIRE(pDataModel != NULL);

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
