// Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>


TEST_CASE("create a reaction with numerically named species", "[copasi,creation]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  REQUIRE(dm->newModel(NULL, true));

  auto * model = dm->getModel();
  REQUIRE(model != NULL);

  auto * reaction = model->createReaction("r1");
  REQUIRE(reaction != NULL);

  REQUIRE(reaction->setReactionScheme("2 \"2\" -> 3 \"3\""));

  const auto& chem = reaction->getChemEq();
  REQUIRE(chem.getSubstrates().size() == 1);
  REQUIRE(chem.getSubstrates()[0].getMetabolite() != NULL);
  REQUIRE(chem.getSubstrates()[0].getMultiplicity() == 2);
  REQUIRE(chem.getSubstrates()[0].getMetabolite()->getObjectName() == "2");
  REQUIRE(chem.getProducts().size() == 1);
  REQUIRE(chem.getProducts()[0].getMetabolite() != NULL);
  REQUIRE(chem.getProducts()[0].getMultiplicity() == 3);
  REQUIRE(chem.getProducts()[0].getMetabolite()->getObjectName() == "3");


  CRootContainer::removeDatamodel(dm);
}


TEST_CASE("create a new model with invalid value", "[copasi,creation]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  REQUIRE(dm->newModel(NULL, true));

  auto * model = dm->getModel();
  REQUIRE(model != NULL);

  auto* exp = new CExpression("expr", dm);
  exp->setInfix("1,1");
  exp->compile();
  auto val = exp->calcValue();
  pdelete(exp);

  CRootContainer::removeDatamodel(dm);
}
