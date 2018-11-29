// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string& fileName);

#define COPASI_MAIN
#include <copasi/CopasiTypes.h>

TEST_CASE("1: loading example file, and resolve CNs", "[copasi]")
{

  CRootContainer::init(0, NULL, false);
  auto* dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);

  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Reference=InitialVolume")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Reference=Rate")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Reference=Volume")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=InitialParticleNumber")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=ParticleNumber")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=ParticleNumberRate")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=Rate")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=Concentration")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=InitialConcentration")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Array=Stoichiometry(ann)[0][0]")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Model=The Brusselator,Array=Stoichiometry(ann)[X][(R1)]")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Vector=TaskList[Sensitivities],Problem=Sensitivities,Array=Sensitivities array[0][0]")) != NULL);
  REQUIRE(dm->getObject(CCommonName("CN=Root,Vector=TaskList[Sensitivities],Problem=Sensitivities,Array=Sensitivities array[\\[X\\]][(R1).k1]")) != NULL);

}
