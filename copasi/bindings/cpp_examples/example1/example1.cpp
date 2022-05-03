// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/**
 * This is an example on how to build models with the COPASI backend API.
 */
#include <iostream>
#include <vector>
#include <string>
#include <set>

#define COPASI_MAIN

#include "copasi/copasi.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CChemEq.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CEvaluationTree.h"

int main()
{
  // initialize the backend library
  // since we are not interested in the arguments
  // that are passed to main, we pass 0 and NULL to
  // init
  CRootContainer::init(0, NULL);
  assert(CRootContainer::getRoot() != NULL);
  // create a new datamodel
  CDataModel* pDataModel = CRootContainer::addDatamodel();
  assert(CRootContainer::getDatamodelList()->size() == 1);
  // get the model from the datamodel
  CModel* pModel = pDataModel->getModel();
  assert(pModel != NULL);
  // set the units for the model
  // we want seconds as the time unit
  // microliter as the volume units
  // and nanomole as the substance units
  pModel->setTimeUnit("s");
  pModel->setVolumeUnit("ul");
  pModel->setQuantityUnit("nmol", CCore::Framework::ParticleNumbers);

  // we have to keep a set of all the initial values that are changed during
  // the model building process
  // They are needed after the model has been built to make sure all initial
  // values are set to the correct initial value
  std::set<const CDataObject*> changedObjects;

  // create a compartment with the name cell and an initial volume of 5.0
  // microliter
  CCompartment* pCompartment = pModel->createCompartment("cell", 5.0);
  const CDataObject* pObject = pCompartment->getInitialValueReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pCompartment != NULL);
  assert(pModel->getCompartments().size() == 1);
  // create a new metabolite with the name glucose and an inital
  // concentration of 10 nanomol
  // the metabolite belongs to the compartment we created and is is to be
  // fixed
  CMetab* pGlucose = pModel->createMetabolite("glucose", pCompartment->getObjectName(), 10.0, CModelEntity::Status::FIXED);
  pObject = pGlucose->getInitialValueReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pCompartment != NULL);
  assert(pGlucose != NULL);
  assert(pModel->getMetabolites().size() == 1);
  // create a second metabolite called glucose-6-phosphate with an initial
  // concentration of 0. This metabolite is to be changed by reactions
  CMetab* pG6P = pModel->createMetabolite("glucose-6-phosphate", pCompartment->getObjectName(), 0.0, CModelEntity::Status::REACTIONS);
  assert(pG6P != NULL);
  pObject = pG6P->getInitialValueReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pModel->getMetabolites().size() == 2);
  // another metabolite for ATP, also fixed
  CMetab* pATP = pModel->createMetabolite("ATP", pCompartment->getObjectName(), 10.0, CModelEntity::Status::FIXED);
  assert(pATP != NULL);
  pObject = pATP->getInitialConcentrationReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pModel->getMetabolites().size() == 3);
  // and one for ADP
  CMetab* pADP = pModel->createMetabolite("ADP", pCompartment->getObjectName(), 0.0, CModelEntity::Status::REACTIONS);
  assert(pADP != NULL);
  pObject = pADP->getInitialConcentrationReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pModel->getMetabolites().size() == 4);
  // now we create a reaction
  CReaction* pReaction = pModel->createReaction("hexokinase");
  assert(pReaction != NULL);
  assert(pModel->getReactions().size() == 1);
  // hexokinase converts glucose and ATP to glucose-6-phosphate and ADP
  // we can set these on the chemical equation of the reaction
  CChemEq* pChemEq = &pReaction->getChemEq();
  // glucose is a substrate with stoichiometry 1
  pChemEq->addMetabolite(pGlucose->getKey(), 1.0, CChemEq::SUBSTRATE);
  // ATP is a substrate with stoichiometry 1
  pChemEq->addMetabolite(pATP->getKey(), 1.0, CChemEq::SUBSTRATE);
  // glucose-6-phosphate is a product with stoichiometry 1
  pChemEq->addMetabolite(pG6P->getKey(), 1.0, CChemEq::PRODUCT);
  // ADP is a product with stoichiometry 1
  pChemEq->addMetabolite(pADP->getKey(), 1.0, CChemEq::PRODUCT);
  assert(pChemEq->getSubstrates().size() == 2);
  assert(pChemEq->getProducts().size() == 2);
  // this reaction is to be irreversible
  pReaction->setReversible(false);
  assert(pReaction->isReversible() == false);
  // now we ned to set a kinetic law on the reaction
  // maybe constant flux would be OK
  // we need to get the function from the function database
  CFunctionDB* pFunDB = CRootContainer::getFunctionList();
  assert(pFunDB != NULL);
  // it should be in the list of suitable functions
  // lets get all suitable functions for an irreversible reaction with  2 substrates
  // and 2 products
  std::vector<CFunction*> suitableFunctions = pFunDB->suitableFunctions(2, 2, TriFalse);
  assert(!suitableFunctions.empty());
  std::vector<CFunction*>::iterator it = suitableFunctions.begin(), endit = suitableFunctions.end();

  while (it != endit)
    {
      // we just assume that the only suitable function with Constant in
      // it's name is the one we want
      if ((*it)->getObjectName().find("Constant") != std::string::npos)
        {
          break;
        }

      ++it;
    }

  if (it != endit)
    {
      // we set the function
      // the method should be smart enough to associate the reaction entities
      // with the correct function parameters
      pReaction->setFunction(*it);
      assert(pReaction->getFunction() != NULL);
      // constant flux has only one function parameter
      assert(pReaction->getFunctionParameters().size() == 1);
      // so there should be only one entry in the parameter mapping as well
      assert(pReaction->getParameterCNs().size() == 1);
      CCopasiParameterGroup* pParameterGroup = &pReaction->getParameters();
      assert(pParameterGroup->size() == 1);
      CCopasiParameter* pParameter = pParameterGroup->getParameter(0);
      // make sure the parameter is a local parameter
      assert(pReaction->isLocalParameter(pParameter->getObjectName()));
      // now we set the value of the parameter to 0.5
      pParameter->setValue(0.5);
      pObject = pParameter->getValueReference();
      assert(pObject != NULL);
      changedObjects.insert(pObject);
    }
  else
    {
      std::cerr << "Error. Could not find irreversible michaelis menten." << std::endl;
      return 1;
    }

  // now we also create a separate reaction for the backwards reaction and
  // set the kinetic law to irreversible mass action
  // now we create a reaction
  pReaction = pModel->createReaction("hexokinase-backwards");
  assert(pReaction != NULL);
  assert(pModel->getReactions().size() == 2);
  pChemEq = &pReaction->getChemEq();
  // glucose is a product with stoichiometry 1
  pChemEq->addMetabolite(pGlucose->getKey(), 1.0, CChemEq::PRODUCT);
  // ATP is a product with stoichiometry 1
  pChemEq->addMetabolite(pATP->getKey(), 1.0, CChemEq::PRODUCT);
  // glucose-6-phosphate is a substrate with stoichiometry 1
  pChemEq->addMetabolite(pG6P->getKey(), 1.0, CChemEq::SUBSTRATE);
  // ADP is a substrate with stoichiometry 1
  pChemEq->addMetabolite(pADP->getKey(), 1.0, CChemEq::SUBSTRATE);
  assert(pChemEq->getSubstrates().size() == 2);
  assert(pChemEq->getProducts().size() == 2);
  // this reaction is to be irreversible
  pReaction->setReversible(false);
  assert(pReaction->isReversible() == false);
  // now we ned to set a kinetic law on the reaction
  CFunction* pMassAction = dynamic_cast<CFunction*>(pFunDB->findFunction("Mass action (irreversible)"));
  assert(pMassAction != NULL);
  // we set the function
  // the method should be smart enough to associate the reaction entities
  // with the correct function parameters
  pReaction->setFunction(pMassAction);
  assert(pReaction->getFunction() != NULL);

  assert(pReaction->getFunctionParameters().size() == 2);
  // so there should be two entries in the parameter mapping as well
  assert(pReaction->getParameterCNs().size() == 2);
  // mass action is a special case since the parameter mappings for the
  // substrates (and products) are in a vector

  // Let us create a global parameter that is determined by an assignment
  // and that is used as the rate constant of the mass action kinetics
  // it gets the name rateConstant and an initial value of 1.56
  CModelValue* pModelValue = pModel->createModelValue("rateConstant", 1.56);
  assert(pModelValue != NULL);
  pObject = pModelValue->getInitialValueReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pModel->getModelValues().size() == 1);
  // set the status to assignment
  pModelValue->setStatus(CModelEntity::Status::ASSIGNMENT);
  // the assignment does not have to make sense
  pModelValue->setExpression("1.0 / 4.0 + 2.0");

  // now we have to adjust the parameter mapping in the reaction so
  // that the kinetic law uses the global parameter we just created instead
  // of the local one that is created by default
  // The first parameter is the one for the rate constant, so we point it to
  // the key of out model value
  pReaction->setParameterObject(0, pModelValue);

  // now we have to set the parameter mapping for the substrates
  //pReaction->setParameterObjects("substrate", {pG6P, pADP });
  pReaction->addParameterObject("substrate", pG6P);
  pReaction->addParameterObject("substrate", pADP);

  // finally compile the model
  // compile needs to be done before updating all initial values for
  // the model with the refresh sequence
  pModel->compileIfNecessary(NULL);

  // now that we are done building the model, we have to make sure all
  // initial values are updated according to their dependencies
  pModel->updateInitialValues(changedObjects);

  // save the model to a COPASI file
  // we save to a file named example1.cps, we don't want a progress report
  // and we want to overwrite any existing file with the same name
  // Default tasks are automatically generated and will always appear in cps
  // file unless they are explicitly deleted before saving.
  pDataModel->saveModel("example1.cps", NULL, true);

  // export the model to an SBML file
  // we save to a file named example1.xml, we want to overwrite any
  // existing file with the same name and we want SBML L2V3
  pDataModel->exportSBML("example1.xml", true, 2, 3);

  // destroy the root container once we are done
  CRootContainer::destroy();

  return 0;
}
