// Copyright (C) 2021 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string& fileName);

#include <copasi/CopasiTypes.h>

bool verify_cn(const CDataModel* dm, const std::string& cn)
{
  auto* ref = dm->getObject({cn });

  if (ref == NULL)
    return false;

  auto resolved = ref->getCN();

  if (resolved.find("not found") != std::string::npos)
    return false;

  return true;
}

TEST_CASE("1: loading example files, and resolve CNs", "[copasi]")
{

  auto* dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  SECTION("brusselator example")
  {

    REQUIRE(dm->loadModel(getTestFile("test-data/brusselator.cps"), NULL) == true);

    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Reference=InitialVolume"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Reference=Rate"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Reference=Volume"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=InitialParticleNumber"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=ParticleNumber"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=ParticleNumberRate"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=Rate"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=Concentration"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Vector=Compartments[compartment],Vector=Metabolites[A],Reference=InitialConcentration"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Array=Stoichiometry(ann)[0][0]"));
    REQUIRE(verify_cn(dm, "CN=Root,Model=The Brusselator,Array=Stoichiometry(ann)[X][(R1)]"));
    REQUIRE(verify_cn(dm, "CN=Root,Vector=TaskList[Sensitivities],Problem=Sensitivities,Array=Sensitivities array[0][0]"));
    REQUIRE(verify_cn(dm, "CN=Root,Vector=TaskList[Sensitivities],Problem=Sensitivities,Array=Sensitivities array[\\[X\\]][(R1).k1]"));
  }

  SECTION("simple_v3_event")
  {
    REQUIRE(dm->loadModel(getTestFile("test-data/simple_v3_event.cps"), NULL) == true);

    REQUIRE(verify_cn(dm, "CN=Root,Model=New Model,Vector=Compartments[compartment],Reference=InitialVolume"));
    REQUIRE(verify_cn(dm, "CN=Root,Vector=TaskList[Sensitivities],Problem=Sensitivities,Array=Sensitivities array[\\[C\\]][Values\\[X\\].InitialValue]"));

    // switch the sensitivity setup
    auto* task = dynamic_cast<CSensTask*>(&((*dm->getTaskList())["Sensitivities"]));
    REQUIRE(task != nullptr);
    auto* prob = dynamic_cast<CSensProblem*>(task->getProblem());
    REQUIRE(prob != nullptr);
    REQUIRE(prob->getNumberOfVariables() == 2);
    prob->setTargetFunctions({CObjectLists::NON_CONST_METAB_NUMBERS });
    prob->changeVariables(0, {CObjectLists::ALL_LOCAL_PARAMETER_VALUES });
    prob->changeVariables(1, {CObjectLists::EMPTY_LIST });
    task->updateMatrices();

    auto* ref = dynamic_cast<const CArrayElementReference*>(dm->getObject(CCommonName("CN=Root,Vector=TaskList[Sensitivities],Problem=Sensitivities,Array=Sensitivities array[A.ParticleNumber][(reaction).k1]")));
    auto* obj = (double*)ref->getValuePointer();
    auto cn = ref->getCN();
    REQUIRE(verify_cn(dm, "CN=Root,Vector=TaskList[Sensitivities],Problem=Sensitivities,Array=Sensitivities array[A.ParticleNumber][(reaction).k1]"));

    auto registeredCN = CRegisteredCommonName(cn);
    registeredCN.sanitizeObjectNames();
    REQUIRE(cn == registeredCN);
  }

  CRootContainer::removeDatamodel(dm);
}
