// Copyright (C) 2021 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>

TEST_CASE("1: loading example files, and resolve name", "[copasi]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  SECTION("brusselator example")
  {

    REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);
    auto * mv = dm->getModel()->createModelValue("mv_1", 1.0);
    dm->getModel()->compileIfNecessary(NULL);
    dm->getModel()->applyInitialValues();

    // species
    auto * object = dm->findObjectByDisplayName("[X]");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("X.ParticleNumber");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("[X]_0");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("X.InitialParticleNumber");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("X.Rate");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("X.ParticleNumberRate");
    REQUIRE(object != nullptr);

    // compartments
    object = dm->findObjectByDisplayName("Compartments[compartment].InitialVolume");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("Compartments[compartment].Volume");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("Compartments[compartment].Rate");
    REQUIRE(object != nullptr);

    // reactions
    object = dm->findObjectByDisplayName("(R1).k1");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("(R1).Flux");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("(R1).ParticleFlux");
    REQUIRE(object != nullptr);

    // parameters
    object = dm->findObjectByDisplayName("Values[mv_1].InitialValue");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("Values[mv_1]");
    REQUIRE(object != nullptr);

    object = dm->findObjectByDisplayName("Values[mv_1].Rate");
    REQUIRE(object != nullptr);

    // time
    object = dm->findObjectByDisplayName("Time");
    REQUIRE(object != nullptr);
  }

  CRootContainer::removeDatamodel(dm);
}
