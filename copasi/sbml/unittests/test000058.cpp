// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000058.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CFunctionDB.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/Rule.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/math/ASTNode.h"

#include "copasi/core/CRootContainer.h"

CDataModel* test000058::pCOPASIDATAMODEL = NULL;

void test000058::setUp()
{
  // Create the root container.
  CRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CRootContainer::addDatamodel();
}

void test000058::tearDown()
{
  CRootContainer::destroy();
}

bool test000058::checkIfIdsUnique(const Model* pSBMLModel)
{
  bool result = true;
  std::set<std::string> ids;

  if (pSBMLModel != NULL)
    {
      // the model itself
      const SBase* pSBase = NULL;
      std::string id;

      if (pSBMLModel->isSetId())
        {
          id = pSBMLModel->getId();

          if (ids.find(id) == ids.end())
            {
              ids.insert(id);
            }
          else
            {
              result = false;
            }
        }

      // ListOfFunctionDefinitions
      pSBase = pSBMLModel->getListOfFunctionDefinitions();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }

          unsigned int i, iMax = pSBMLModel->getListOfFunctionDefinitions()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pSBMLModel->getListOfFunctionDefinitions()->get(i);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(id);
                    }
                  else
                    {
                      result = false;
                    }
                }
            }
        }

      // ListOfCompartmentTypes
      pSBase = pSBMLModel->getListOfCompartmentTypes();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }

          // each compartment type
          unsigned int i, iMax = pSBMLModel->getListOfCompartmentTypes()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pSBMLModel->getCompartmentType(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(id);
                    }
                  else
                    {
                      result = false;
                    }
                }
            }
        }

      // ListOfSpeciesTypes
      pSBase = pSBMLModel->getListOfSpeciesTypes();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }

          // each species type
          unsigned int i, iMax = pSBMLModel->getListOfSpeciesTypes()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pSBMLModel->getSpeciesType(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(id);
                    }
                  else
                    {
                      result = false;
                    }
                }
            }
        }

      // ListOfCompartments
      pSBase = pSBMLModel->getListOfCompartments();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }

          // all compartments
          unsigned int i, iMax = pSBMLModel->getListOfCompartments()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pSBMLModel->getCompartment(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(id);
                    }
                  else
                    {
                      result = false;
                    }
                }
            }
        }

      // ListOfSpecies
      pSBase = pSBMLModel->getListOfSpecies();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }

          // all species
          unsigned int i, iMax = pSBMLModel->getListOfSpecies()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pSBMLModel->getSpecies(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(id);
                    }
                  else
                    {
                      result = false;
                    }
                }
            }
        }

      // ListOfParameters
      pSBase = pSBMLModel->getListOfParameters();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }

          // each parameter
          unsigned int i, iMax = pSBMLModel->getListOfParameters()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pSBMLModel->getParameter(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(id);
                    }
                  else
                    {
                      result = false;
                    }
                }
            }
        }

      // ListOfInitialAssignments
      pSBase = pSBMLModel->getListOfInitialAssignments();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }
        }

      // ListOfRules
      pSBase = pSBMLModel->getListOfRules();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }
        }

      // ListOfConstraints
      pSBase = pSBMLModel->getListOfConstraints();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }
        }

      // ListOfReactions
      pSBase = pSBMLModel->getListOfReactions();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }

          // all reactions
          unsigned int i, iMax = pSBMLModel->getListOfReactions()->size();

          for (i = 0; i < iMax; ++i)
            {
              const Reaction* pReaction = pSBMLModel->getReaction(i);
              assert(pReaction != NULL);

              if (pReaction->isSetId())
                {
                  id = pReaction->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(id);
                    }
                  else
                    {
                      result = false;
                    }
                }

              // for each reaction: ListOfSubstrates, each substrate, ListOfProducts, each
              // Product, ListOfModifieres, each modifier, KineticLaw, ListOfparameters,
              // each parameter
              if (pReaction->getListOfReactants() != NULL)
                {
                  pSBase = pReaction->getListOfReactants();
                  unsigned int j, jMax = pReaction->getListOfReactants()->size();

                  for (j = 0; j < jMax; ++j)
                    {
                      pSBase = pReaction->getReactant(j);
                      assert(pSBase != NULL);

                      // since L2V2 species references can have ids
                      if (pSBase->isSetId())
                        {
                          id = pSBase->getId();

                          if (ids.find(id) == ids.end())
                            {
                              ids.insert(id);
                            }
                          else
                            {
                              result = false;
                            }
                        }
                    }
                }

              if (pReaction->getListOfProducts() != NULL)
                {
                  pSBase = pReaction->getListOfProducts();
                  unsigned int j, jMax = pReaction->getListOfProducts()->size();

                  for (j = 0; j < jMax; ++j)
                    {
                      pSBase = pReaction->getProduct(j);
                      assert(pSBase != NULL);

                      // since L2V2 species references can have ids
                      if (pSBase->isSetId())
                        {
                          id = pSBase->getId();

                          if (ids.find(id) == ids.end())
                            {
                              ids.insert(id);
                            }
                          else
                            {
                              result = false;
                            }
                        }
                    }
                }

              if (pReaction->getListOfModifiers() != NULL)
                {
                  pSBase = pReaction->getListOfModifiers();
                  unsigned int j, jMax = pReaction->getListOfModifiers()->size();

                  for (j = 0; j < jMax; ++j)
                    {
                      pSBase = pReaction->getModifier(j);
                      assert(pSBase != NULL);

                      // since L2V2 species references can have ids
                      if (pSBase->isSetId())
                        {
                          id = pSBase->getId();

                          if (ids.find(id) == ids.end())
                            {
                              ids.insert(id);
                            }
                          else
                            {
                              result = false;
                            }
                        }
                    }
                }
            }
        }

      // ListOfEvents
      pSBase = pSBMLModel->getListOfEvents();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(id);
                }
              else
                {
                  result = false;
                }
            }
        }
    }

  /*
  std::cout << "number of ids: " << ids.size() << std::endl;
  std::set<std::string>::iterator it=ids.begin();
  while(it!=ids.end())
  {
      std::cout << "id: " << *it << std::endl;
      ++it;
  }
  */
  return result;
}

void test000058::test_bug1025_1()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000058::MODEL_STRING));
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  // now we add a new reaction
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CReaction* pReaction = pModel->createReaction("influx");
  CPPUNIT_ASSERT(pReaction != NULL);
  pReaction->addProduct(pModel->getMetabolites()[0]->getKey());
  pReaction->setFunction("Constant flux (irreversible)");
  pReaction->setParameterValue("v", 1.0, true);
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  changedObjects.insert(pReaction->getParameters().getParameter(0)->getValueReference());
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

void test000058::test_bug1025_2()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000058::MODEL_STRING));
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  // now we add a new compartment
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CCompartment* pCompartment = pModel->createCompartment("compartment_2");
  CPPUNIT_ASSERT(pCompartment != NULL);
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  const CDataObject* pObject = pCompartment->getInitialValueReference();
  CPPUNIT_ASSERT(pObject != NULL);
  changedObjects.insert(pObject);
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

void test000058::test_bug1025_3()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000058::MODEL_STRING));
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  // now we add a new species
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CMetab* pMetabolite = pModel->createMetabolite("species_2", "compartment_1", 1.0, CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(pMetabolite != NULL);
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  const CDataObject* pObject = pMetabolite->getInitialConcentrationReference();
  CPPUNIT_ASSERT(pObject != NULL);
  changedObjects.insert(pObject);
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

void test000058::test_bug1025_4()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000058::MODEL_STRING));
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  // now we add a new parameter
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CModelValue* pModelValue = pModel->createModelValue("parameter_2");
  CPPUNIT_ASSERT(pModelValue != NULL);
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  const CDataObject* pObject = pModelValue->getInitialValueReference();
  CPPUNIT_ASSERT(pObject != NULL);
  changedObjects.insert(pObject);
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 2);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

void test000058::test_bug1025_5()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(test000058::MODEL_STRING));
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  // now we add a new parameter
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // add a new function definition
  CFunction* pFunctionDefinition = new CFunction("function_2");
  CPPUNIT_ASSERT(pFunctionDefinition != NULL);
  CPPUNIT_ASSERT(pFunctionDefinition->setInfix("3 * 5") == true);
  pFunctionDefinition->compile();
  // add the function definition to the function database
  CRootContainer::getFunctionList()->addAndAdaptName(pFunctionDefinition);
  CModelValue* pModelValue = pModel->createModelValue("parameter_2");
  CPPUNIT_ASSERT(pModelValue != NULL);
  pModelValue->setStatus(CModelEntity::Status::ASSIGNMENT);
  CPPUNIT_ASSERT(pModelValue->setExpression(std::string(pFunctionDefinition->getObjectName() + "()")) == true);
  // now create a rule for the parameter
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  const CDataObject* pObject = pModelValue->getInitialValueReference();
  CPPUNIT_ASSERT(pObject != NULL);
  changedObjects.insert(pObject);
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 2);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

void test000058::test_bug1025_6()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000058::MODEL_STRING2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  // now we add a new reaction
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CReaction* pReaction = pModel->createReaction("influx");
  CPPUNIT_ASSERT(pReaction != NULL);
  pReaction->addProduct(pModel->getMetabolites()[0]->getKey());
  pReaction->setFunction("Constant flux (irreversible)");
  pReaction->setParameterValue("v", 1.0, true);
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  changedObjects.insert(pReaction->getParameters().getParameter(0)->getValueReference());
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

void test000058::test_bug1025_7()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000058::MODEL_STRING2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  // now we add a new compartment
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CCompartment* pCompartment = pModel->createCompartment("compartment_2");
  CPPUNIT_ASSERT(pCompartment != NULL);
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  const CDataObject* pObject = pCompartment->getInitialValueReference();
  CPPUNIT_ASSERT(pObject != NULL);
  changedObjects.insert(pObject);
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

void test000058::test_bug1025_8()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000058::MODEL_STRING2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  // now we add a new species
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CMetab* pMetabolite = pModel->createMetabolite("species_2", "compartment_1", 1.0, CModelEntity::Status::FIXED);
  CPPUNIT_ASSERT(pMetabolite != NULL);
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  const CDataObject* pObject = pMetabolite->getInitialConcentrationReference();
  CPPUNIT_ASSERT(pObject != NULL);
  changedObjects.insert(pObject);
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 1);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

void test000058::test_bug1025_9()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000058::MODEL_STRING2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  // now we add a new parameter
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CModelValue* pModelValue = pModel->createModelValue("parameter_2");
  CPPUNIT_ASSERT(pModelValue != NULL);
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  const CDataObject* pObject = pModelValue->getInitialValueReference();
  CPPUNIT_ASSERT(pObject != NULL);
  changedObjects.insert(pObject);
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 0);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 2);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

void test000058::test_bug1025_10()
{
  CDataModel* pDataModel = pCOPASIDATAMODEL;
  std::istringstream iss(test000058::MODEL_STRING2);
  CPPUNIT_ASSERT(load_cps_model_from_stream(iss, *pDataModel) == true);
  CPPUNIT_ASSERT(pDataModel->getModel() != NULL);
  const SBMLDocument* pDocument = pDataModel->getCurrentSBMLDocument();
  CPPUNIT_ASSERT(pDocument == NULL);
  // now we add a new parameter
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  // add a new function definition
  CFunction* pFunctionDefinition = new CFunction("function_2");
  CPPUNIT_ASSERT(pFunctionDefinition != NULL);
  CPPUNIT_ASSERT(pFunctionDefinition->setInfix("3 * 5") == true);
  pFunctionDefinition->compile();
  // add the function definition to the function database
  CRootContainer::getFunctionList()->addAndAdaptName(pFunctionDefinition);
  CModelValue* pModelValue = pModel->createModelValue("parameter_2");
  CPPUNIT_ASSERT(pModelValue != NULL);
  pModelValue->setStatus(CModelEntity::Status::ASSIGNMENT);
  CPPUNIT_ASSERT(pModelValue->setExpression(std::string(pFunctionDefinition->getObjectName() + "()")) == true);
  // now create a rule for the parameter
  pModel->compileIfNecessary(NULL);
  std::set<const CDataObject*> changedObjects;
  const CDataObject* pObject = pModelValue->getInitialValueReference();
  CPPUNIT_ASSERT(pObject != NULL);
  changedObjects.insert(pObject);
  std::vector<Refresh*> refreshes = pModel->buildInitialRefreshSequence(changedObjects);
  std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();

  while (refreshIt != refreshEndit)
    {
      (**refreshIt++)();
    }

  CPPUNIT_ASSERT(pDataModel->exportSBMLToString(NULL, 2, 1).empty() == false);
  pDocument = pDataModel->getCurrentSBMLDocument();
  const Model* pSBMLModel = pDocument->getModel();
  CPPUNIT_ASSERT(pSBMLModel != NULL);
  CPPUNIT_ASSERT(pSBMLModel->getNumFunctionDefinitions() == 2);
  CPPUNIT_ASSERT(pSBMLModel->getNumCompartments() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumSpecies() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumReactions() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumRules() == 1);
  CPPUNIT_ASSERT(pSBMLModel->getNumParameters() == 2);
  CPPUNIT_ASSERT(checkIfIdsUnique(pSBMLModel) == true);
}

const char* test000058::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2\" metaid=\"_000000\" level=\"2\" version=\"1\">\n"
  "  <model metaid=\"_000001\" id=\"model_1\" name=\"model_1\">\n"
  "    <listOfFunctionDefinitions>\n"
  "      <functionDefinition metaid=\"_000004\" id=\"function_1\" name=\"function_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci> k </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> S </ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> k </ci>\n"
  "              <ci> S </ci>\n"
  "            </apply>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "    </listOfFunctionDefinitions>  \n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition metaid=\"_000002\" id=\"time\" name=\"time\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"second\" scale=\"0\" multiplier=\"1\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition metaid=\"_000003\" id=\"unit_2\" name=\"unit_2\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"second\" exponent=\"-1\" scale=\"0\" multiplier=\"1\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>  \n"
  "    <listOfCompartments>\n"
  "      <compartment metaid=\"_000005\" id=\"compartment_1\" name=\"compartment_1\" size=\"1e-16\">\n"
  "      </compartment>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species metaid=\"_000006\" id=\"species_1\" name=\"species_1\" compartment=\"compartment_1\" initialAmount=\"1.0\"/>\n"
  "    </listOfSpecies>  \n"
  "    <listOfParameters>\n"
  "      <parameter metaid=\"_000007\" id=\"parameter_1\" name=\"parameter_1\" value=\"3.0\" constant=\"false\" units=\"unit_2\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfReactions>\n"
  "      <reaction metaid=\"_000008\" id=\"reaction_1\" name=\"reaction_1\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_1\"/>\n"
  "        </listOfReactants>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> compartment_1 </ci>\n"
  "              <apply>\n"
  "                <ci> function_1 </ci>\n"
  "                <ci> parameter_1 </ci>\n"
  "                <ci> species_1 </ci>\n"
  "              </apply>\n"
  "            </apply>\n"
  "          </math>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n"
  ;

const char* test000058::MODEL_STRING2 =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<!-- generated with COPASI 4.3.25 (Debug) (http://www.copasi.org) at 2008-04-29 13:08:40 UTC -->\n"
  "<COPASI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.copasi.org/static/schema.xsd\" versionMajor=\"1\" versionMinor=\"0\" versionDevel=\"25\">\n"
  "  <ListOfFunctions>\n"
  "    <Function key=\"Function_40\" name=\"Function for reaction_1\" type=\"UserDefined\" reversible=\"true\">\n"
  "      <Expression>\n"
  "        parameter_1*species_1\n"
  "      </Expression>\n"
  "      <ListOfParameterDescriptions>\n"
  "        <ParameterDescription key=\"FunctionParameter_250\" name=\"parameter_1\" order=\"0\" role=\"constant\"/>\n"
  "        <ParameterDescription key=\"FunctionParameter_254\" name=\"species_1\" order=\"1\" role=\"substrate\"/>\n"
  "      </ListOfParameterDescriptions>\n"
  "    </Function>\n"
  "  </ListOfFunctions>\n"
  "  <Model key=\"Model_1\" name=\"model_1\" timeUnit=\"s\" volumeUnit=\"l\" quantityUnit=\"mol\" type=\"deterministic\">\n"
  "    <Comment>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        \n"
  "      </body>\n"
  "    </Comment>\n"
  "    <ListOfCompartments>\n"
  "      <Compartment key=\"Compartment_0\" name=\"compartment_1\" simulationType=\"fixed\">\n"
  "      </Compartment>\n"
  "    </ListOfCompartments>\n"
  "    <ListOfMetabolites>\n"
  "      <Metabolite key=\"Metabolite_0\" name=\"species_1\" simulationType=\"reactions\" compartment=\"Compartment_0\">\n"
  "      </Metabolite>\n"
  "    </ListOfMetabolites>\n"
  "    <ListOfModelValues>\n"
  "      <ModelValue key=\"ModelValue_0\" name=\"parameter_1\" simulationType=\"fixed\">\n"
  "      </ModelValue>\n"
  "    </ListOfModelValues>\n"
  "    <ListOfReactions>\n"
  "      <Reaction key=\"Reaction_0\" name=\"reaction_1\" reversible=\"true\">\n"
  "        <ListOfSubstrates>\n"
  "          <Substrate metabolite=\"Metabolite_0\" stoichiometry=\"1\"/>\n"
  "        </ListOfSubstrates>\n"
  "        <ListOfConstants>\n"
  "          <Constant key=\"Parameter_81\" name=\"parameter_1\" value=\"1\"/>\n"
  "        </ListOfConstants>\n"
  "        <KineticLaw function=\"Function_40\">\n"
  "          <ListOfCallParameters>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_250\">\n"
  "              <SourceParameter reference=\"ModelValue_0\"/>\n"
  "            </CallParameter>\n"
  "            <CallParameter functionParameter=\"FunctionParameter_254\">\n"
  "              <SourceParameter reference=\"Metabolite_0\"/>\n"
  "            </CallParameter>\n"
  "          </ListOfCallParameters>\n"
  "        </KineticLaw>\n"
  "      </Reaction>\n"
  "    </ListOfReactions>\n"
  "    <StateTemplate>\n"
  "      <StateTemplateVariable objectReference=\"Model_1\"/>\n"
  "      <StateTemplateVariable objectReference=\"Metabolite_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"ModelValue_0\"/>\n"
  "      <StateTemplateVariable objectReference=\"Compartment_0\"/>\n"
  "    </StateTemplate>\n"
  "    <InitialState type=\"initialState\">\n"
  "      0 6.0221415e+23 3 1e-16\n"
  "    </InitialState>\n"
  "  </Model>\n"
  "  <SBMLReference file=\"test000058.xml\">\n"
  "    <SBMLMap SBMLid=\"compartment_1\" COPASIkey=\"Compartment_0\"/>\n"
  "    <SBMLMap SBMLid=\"parameter_1\" COPASIkey=\"ModelValue_0\"/>\n"
  "    <SBMLMap SBMLid=\"reaction_1\" COPASIkey=\"Reaction_0\"/>\n"
  "    <SBMLMap SBMLid=\"species_1\" COPASIkey=\"Metabolite_0\"/>\n"
  "  </SBMLReference>\n"
  "</COPASI>\n"
  ;
