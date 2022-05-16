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
 * This is an example on how to create user defined kinetic functions with the COPASI API
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
  const CDataObject* pObject = pCompartment->getValueReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pCompartment != NULL);
  assert(pModel->getCompartments().size() == 1);
  // create a new metabolite with the name S and an inital
  // concentration of 10 nanomol
  // the metabolite belongs to the compartment we created and is is to be
  // fixed
  CMetab* pS = pModel->createMetabolite("S", pCompartment->getObjectName(), 10.0, CModelEntity::Status::FIXED);
  pObject = pS->getInitialConcentrationReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pCompartment != NULL);
  assert(pS != NULL);
  assert(pModel->getMetabolites().size() == 1);
  // create a second metabolite called P with an initial
  // concentration of 0. This metabolite is to be changed by reactions
  CMetab* pP = pModel->createMetabolite("P", pCompartment->getObjectName(), 0.0, CModelEntity::Status::REACTIONS);
  assert(pP != NULL);
  pObject = pP->getInitialConcentrationReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pModel->getMetabolites().size() == 2);
  // now we create a reaction
  CReaction* pReaction = pModel->createReaction("reaction");
  assert(pReaction != NULL);
  assert(pModel->getReactions().size() == 1);
  // reaction converts S to P
  // we can set these on the chemical equation of the reaction
  CChemEq* pChemEq = &pReaction->getChemEq();
  // S is a substrate with stoichiometry 1
  pChemEq->addMetabolite(pS->getKey(), 1.0, CChemEq::SUBSTRATE);
  // P is a product with stoichiometry 1
  pChemEq->addMetabolite(pP->getKey(), 1.0, CChemEq::PRODUCT);
  assert(pChemEq->getSubstrates().size() == 1);
  assert(pChemEq->getProducts().size() == 1);
  // this reaction is to be irreversible
  pReaction->setReversible(false);
  assert(pReaction->isReversible() == false);

  CModelValue* pMV = pModel->createModelValue("K", 42.0);
  // set the status to FIXED
  pMV->setStatus(CModelEntity::Status::FIXED);
  assert(pMV != NULL);
  pObject = pMV->getInitialValueReference();
  assert(pObject != NULL);
  changedObjects.insert(pObject);
  assert(pModel->getModelValues().size() == 1);

  // now we ned to set a kinetic law on the reaction
  // for this we create a user defined function
  CFunctionDB* pFunDB = CRootContainer::getFunctionList();
  assert(pFunDB != NULL);

  CKinFunction* pFunction = new CKinFunction("My Rate Law");

  pFunDB->add(pFunction, true);
  CFunction* pRateLaw = dynamic_cast<CFunction*>(pFunDB->findFunction("My Rate Law"));

  assert(pRateLaw != NULL);

  // now we create the formula for the function and set it on the function
  std::string formula = "(1-0.4/(EXPONENTIALE^(temp-37)))*0.00001448471257*1.4^(temp-37)*substrate";

  bool result = pFunction->setInfix(formula);
  assert(result == true);
  // make the function irreversible
  pFunction->setReversible(TriFalse);
  // the formula string should have been parsed now
  // and COPASI should have determined that the formula string contained 2 parameters (temp and substrate)
  CFunctionParameters& variables = pFunction->getVariables();
  // per default the usage of those parameters will be set to VARIABLE
  size_t index = pFunction->getVariableIndex("temp");
  assert(index != C_INVALID_INDEX);
  CFunctionParameter* pParam = variables[index];
  assert(pParam->getUsage() == CFunctionParameter::Role::VARIABLE);
  // This is correct for temp, but substrate should get the usage SUBSTRATE in order
  // for us to use the function with the reaction created above
  // So we need to set the usage for "substrate" manually
  index = pFunction->getVariableIndex("substrate");
  assert(index != C_INVALID_INDEX);
  pParam = variables[index];
  pParam->setUsage(CFunctionParameter::Role::SUBSTRATE);

  // set the rate law for the reaction
  pReaction->setFunction(pFunction);
  assert(pReaction->getFunction() != NULL);

  // COPASI also needs to know what object it has to assocuiate with the individual function parameters
  // In our case we need to tell COPASI that substrate is to be replaced by the substrate of the reaction
  // and temp is to be replaced by the global parameter K
  std::vector< const CDataObject * > Objects(1, pS);
  pReaction->setParameterObjects("substrate", Objects);
  Objects.clear();

  Objects.push_back(pMV);
  pReaction->setParameterObjects("temp", Objects);

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
  // file unless they are explicitley deleted before saving.
  pDataModel->saveModel("example7.cps", NULL, true);

  // export the model to an SBML file
  // we save to a file named example1.xml, we want to overwrite any
  // existing file with the same name and we want SBML L2V3
  pDataModel->exportSBML("example7.xml", true, 2, 3);

  // destroy the root container once we are done
  CRootContainer::destroy();
}
