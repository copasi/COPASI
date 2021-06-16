// Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>

TEST_CASE("1: loading example files, and resolve name", "[copasi]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  SECTION("brusselator example")
  {

    REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);
    auto * mv = dm->getModel()->createModelValue("mv_1", 1.0);
    dm->getModel()->compileIfNecessary(NULL);
    dm->getModel()->applyInitialValues();


    // species
    auto * object = dm->findObjectByDisplayName("[X]");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("X.ParticleNumber");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("[X]_0");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("X.InitialParticleNumber");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("X.Rate");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("X.ParticleNumberRate");
    REQUIRE(object != NULL);


    // compartments
    object = dm->findObjectByDisplayName("Compartments[compartment].InitialVolume");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("Compartments[compartment].Volume");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("Compartments[compartment].Rate");
    REQUIRE(object != NULL);


    // reactions
    object = dm->findObjectByDisplayName("(R1).k1");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("(R1).Flux");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("(R1).ParticleFlux");
    REQUIRE(object != NULL);


    // parameters
    object = dm->findObjectByDisplayName("Values[mv_1].InitialValue");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("Values[mv_1]");
    REQUIRE(object != NULL);

    object = dm->findObjectByDisplayName("Values[mv_1].Rate");
    REQUIRE(object != NULL);


    // time
    object = dm->findObjectByDisplayName("Time");
    REQUIRE(object != NULL);

  }

  CRootContainer::removeDatamodel(dm);
}
