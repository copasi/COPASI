// Copyright (C) 2021 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"
#include <limits>

#include <copasi/core/CRootContainer.h>
#include <copasi/CopasiDataModel/CDataModel.h>
#include <copasi/model/CModel.h>

extern std::string getTestFile(const std::string & fileName);

TEST_CASE("delete brusselator species", "[copasi]")
{
  auto fileName = getTestFile("test-data/brusselator.cps");
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  REQUIRE(dm->loadModel(fileName, NULL) == true);

  auto * model = dm->getModel();
  REQUIRE(model != nullptr);
  REQUIRE(model->getNumMetabs() == 6);

  while (model->getNumMetabs() > 0)
    REQUIRE(model->removeMetabolite(model->getMetabolites()[0].getKey()));

  CRootContainer::removeDatamodel(dm);
}
