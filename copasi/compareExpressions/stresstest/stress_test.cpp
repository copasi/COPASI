// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/stresstest/stress_test.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/12/01 13:58:04 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "stress_test.h"

#include <iostream>

#define COPASI_MAIN

#include "copasi/compareExpressions/compare_utilities.h"

#include "sbml/SBMLDocument.h"
#include "sbml/Model.h"
#include "sbml/FunctionDefinition.h"
#include "sbml/Rule.h"
#include "sbml/InitialAssignment.h"
#include "sbml/Reaction.h"
#include "sbml/KineticLaw.h"
#include "sbml/SpeciesReference.h"
#include "sbml/Event.h"
#include "sbml/Delay.h"
#include "sbml/Trigger.h"
#include "sbml/EventAssignment.h"
#include "sbml/StoichiometryMath.h"
#include "sbml/math/ASTNode.h"
#include "sbml/math/MathML.h"

#include "copasi/report/CCopasiContainer.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/compareExpressions/CNormalFraction.h"
#include "copasi/compareExpressions/CNormalTranslation.h"

/**
 * Constructor.
 */
stress_test::stress_test(): mNumFunctionDefinitions(0), mNumExpressions(0), mNumCOPASIFunctionDefinitions(0)
{
  // Create the root container.
  CCopasiContainer::init();
  // Create the global data model.
  CCopasiDataModel::Global = new CCopasiDataModel;
}

/**
 * Destructor.
 */
stress_test::~stress_test()
{
  // delete normalforms of expressions
  std::vector<CNormalFraction*>::iterator it = mNormalizedExpressions.begin(), endit = mNormalizedExpressions.end();
  while (it != endit)
    {
      delete *it;
      ++it;
    }
  // delete normalforms of function definitions
  it = mNormalizedFunctionDefinitions.begin();
  endit = mNormalizedFunctionDefinitions.end();
  while (it != endit)
    {
      delete *it;
      ++it;
    }
  // delete normalforms of COPASI function definitions
  it = mNormalizedCOPASIFunctionDefinitions.begin();
  endit = mNormalizedCOPASIFunctionDefinitions.end();
  while (it != endit)
    {
      delete *it;
      ++it;
    }
  // delete the COPASI data structures
  delete CCopasiDataModel::Global;
  CCopasiDataModel::Global = NULL;
  delete CCopasiContainer::Root;
  CCopasiContainer::Root = NULL;
}

/**
 * Goes through the list of files, loads each file and normalizes the
 * mathematical expressions in the contained model.
 */
void stress_test::run(const std::vector<std::string>& filenames)
{
  std::vector<std::string>::const_iterator it = filenames.begin(), endit = filenames.end();
  while (it != endit)
    {
      std::cout << "Processing " << *it << std::endl;
      this->normalizeMath(*it);
      ++it;
    }
  // output some statistics
  std::cout << "number of function definitions: " << mNumFunctionDefinitions << std::endl;
  std::cout << "number of COPASI function definitions: " << mNumCOPASIFunctionDefinitions << std::endl;
  std::cout << "number of expressions: " << mNumExpressions << std::endl;
}

/**
 * Loads an sbml model from the given file and
 * normalized all mathematical expressions in the SBML model.
 */
void stress_test::normalizeMath(const std::string& filename)
{
  if (CCopasiDataModel::Global != NULL)
    {
      bool result = CCopasiDataModel::Global->importSBML(filename);
      if (result == true)
        {
          const SBMLDocument* pDocument = CCopasiDataModel::Global->getCurrentSBMLDocument();
          if (pDocument != NULL)
            {
              const Model* pModel = pDocument->getModel();
              if (pModel != NULL)
                {
                  //this->normalizeFunctionDefinitions(pModel);
                  //this->normalizeExpressions(pModel);
                  this->normalizeAndSimplifyFunctionDefinitions(pModel);
                  this->normalizeAndSimplifyExpressions(pModel);
                }
            }
        }
    }
}

/**
 * Normalizes all expressions but the function definitions in the given
 * model.
 */
void stress_test::normalizeAndSimplifyExpressions(const Model* pModel)
{
  // expressions can occur in assignments, initial assignments, kinetic laws event triggers,
  // event delays, event assignments and stiochiometric expressions
  const InitialAssignment* pInitialAssignment = NULL;
  const ASTNode* pMath = NULL;
  ASTNode* pNewMath = NULL;
  CNormalFraction* pFraction = NULL;
  // initial assignments
  unsigned int i, iMax = pModel->getListOfInitialAssignments()->size();
  for (i = 0;i < iMax;++i)
    {
      pInitialAssignment = pModel->getInitialAssignment(i);
      assert(pInitialAssignment != NULL);
      pMath = pInitialAssignment->getMath();
      if (pMath != NULL)
        {
          pNewMath = create_expression(pMath, pModel);
          assert(pNewMath != NULL);
          try
            {
              pFraction = create_simplified_normalform(pNewMath);
            }
          catch (recursion_limit_exception e)
            {
              std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewMath) << "\"." << std::endl;
            }
          catch (...)
            {
              std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
            }
          ++mNumExpressions;
          delete pNewMath;
          assert(pFraction != NULL);
          //            this->mNormalizedExpressions.push_back(pFraction);
        }
    }
  // rules
  const Rule* pRule = NULL;
  iMax = pModel->getListOfRules()->size();
  for (i = 0;i < iMax;++i)
    {
      pRule = pModel->getRule(i);
      assert(pRule != NULL);
      pMath = pRule->getMath();
      if (pMath != NULL)
        {
          pNewMath = create_expression(pMath, pModel);
          assert(pNewMath != NULL);
          try
            {
              pFraction = create_simplified_normalform(pNewMath);
              assert(pFraction != NULL);
              //            this->mNormalizedExpressions.push_back(pFraction);
            }
          catch (recursion_limit_exception e)
            {
              std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewMath) << "\"." << std::endl;
            }
          catch (...)
            {
              std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
            }
          ++mNumExpressions;
          delete pNewMath;
        }
    }
  // kinetic laws + stoichiometric expressions
  const Reaction* pReaction = NULL;
  iMax = pModel->getListOfReactions()->size();
  for (i = 0;i < iMax;++i)
    {
      pReaction = pModel->getReaction(i);
      assert(pReaction != NULL);
      const KineticLaw* pLaw = pReaction->getKineticLaw();
      if (pLaw != NULL)
        {
          pMath = pLaw->getMath();
          if (pMath != NULL)
            {
              pNewMath = create_expression(pMath, pModel);
              assert(pNewMath != NULL);
              try
                {
                  pFraction = create_simplified_normalform(pNewMath);
                  assert(pFraction != NULL);
                  //                this->mNormalizedExpressions.push_back(pFraction);
                }
              catch (recursion_limit_exception e)
                {
                  std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewMath) << "\"." << std::endl;
                }
              catch (...)
                {
                  std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                }
              delete pNewMath;
              ++mNumExpressions;
            }
        }
      const SpeciesReference* pSpeciesReference = NULL;
      // substrates
      unsigned j, jMax = pReaction->getListOfReactants()->size();
      for (j = 0;j < jMax;++j)
        {
          pSpeciesReference = pReaction->getReactant(j);
          assert(pSpeciesReference != NULL);
          if (pSpeciesReference->isSetStoichiometryMath())
            {
              const StoichiometryMath* pSMath = pSpeciesReference->getStoichiometryMath();
              assert(pSMath != NULL);
              pMath = pSMath->getMath();
              if (pMath != NULL)
                {
                  pNewMath = create_expression(pMath, pModel);
                  assert(pNewMath != NULL);
                  try
                    {
                      pFraction = create_simplified_normalform(pNewMath);
                      assert(pFraction != NULL);
                      //                    this->mNormalizedExpressions.push_back(pFraction);
                    }
                  catch (recursion_limit_exception e)
                    {
                      std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewMath) << "\"." << std::endl;
                    }
                  catch (...)
                    {
                      std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                    }
                  ++mNumExpressions;
                  delete pNewMath;
                }
            }
        }
      // products
      jMax = pReaction->getListOfProducts()->size();
      for (j = 0;j < jMax;++j)
        {
          pSpeciesReference = pReaction->getProduct(j);
          assert(pSpeciesReference != NULL);
          if (pSpeciesReference->isSetStoichiometryMath())
            {
              const StoichiometryMath* pSMath = pSpeciesReference->getStoichiometryMath();
              assert(pSMath != NULL);
              pMath = pSMath->getMath();
              if (pMath != NULL)
                {
                  pNewMath = create_expression(pMath, pModel);
                  assert(pNewMath != NULL);
                  try
                    {
                      pFraction = create_simplified_normalform(pNewMath);
                      assert(pFraction != NULL);
                      //                    this->mNormalizedExpressions.push_back(pFraction);
                    }
                  catch (recursion_limit_exception e)
                    {
                      std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewMath) << "\"." << std::endl;
                    }
                  catch (...)
                    {
                      std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                    }
                  ++mNumExpressions;
                  delete pNewMath;
                }
            }
        }
    }
  // events
  const Event* pEvent = NULL;
  const Trigger* pTrigger = NULL;
  const Delay* pDelay = NULL;
  iMax = pModel->getListOfEvents()->size();
  for (i = 0;i < iMax;++i)
    {
      pEvent = pModel->getEvent(i);
      assert(pEvent != NULL);
      // trigger
      pTrigger = pEvent->getTrigger();
      assert(pTrigger != NULL);
      pMath = pTrigger->getMath();
      if (pMath != NULL)
        {
          pNewMath = create_expression(pMath, pModel);
          assert(pNewMath != NULL);
          try
            {
              pFraction = create_simplified_normalform(pNewMath);
              assert(pFraction != NULL);
              //            this->mNormalizedExpressions.push_back(pFraction);
            }
          catch (recursion_limit_exception e)
            {
              std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewMath) << "\"." << std::endl;
            }
          catch (...)
            {
              std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
            }
          ++mNumExpressions;
          delete pNewMath;
        }

      // delay
      if (pEvent->isSetDelay())
        {
          pDelay = pEvent->getDelay();
          assert(pDelay != NULL);
          pMath = pDelay->getMath();
          if (pMath != NULL)
            {
              pNewMath = create_expression(pMath, pModel);
              assert(pNewMath != NULL);
              try
                {
                  pFraction = create_simplified_normalform(pNewMath);
                  assert(pFraction != NULL);
                  //                this->mNormalizedExpressions.push_back(pFraction);
                }
              catch (recursion_limit_exception e)
                {
                  std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewMath) << "\"." << std::endl;
                }
              catch (...)
                {
                  std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                }
              ++mNumExpressions;
              delete pNewMath;
            }
        }

      // event assignments
      unsigned int j, jMax = pEvent->getListOfEventAssignments()->size();
      const EventAssignment* pEventAssignment = NULL;
      for (j = 0;j < jMax;++j)
        {
          pEventAssignment = pEvent->getEventAssignment(j);
          assert(pEventAssignment != NULL);
          pMath = pEventAssignment->getMath();
          if (pMath != NULL)
            {
              pNewMath = create_expression(pMath, pModel);
              assert(pNewMath != NULL);
              try
                {
                  pFraction = create_simplified_normalform(pNewMath);
                  assert(pFraction != NULL);
                  //                this->mNormalizedExpressions.push_back(pFraction);
                }
              catch (recursion_limit_exception e)
                {
                  std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewMath) << "\"." << std::endl;
                }
              catch (...)
                {
                  std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                }
              ++mNumExpressions;
              delete pNewMath;
            }
        }
    }
}

/**
 * Normalizes the function definitions in the given model.
 */
void stress_test::normalizeAndSimplifyFunctionDefinitions(const Model* pModel)
{
  const FunctionDefinition* pFunDef = NULL;
  const ASTNode* pRoot = NULL;
  ASTNode* pNewRoot = NULL;
  CNormalFraction* pFraction = NULL;
  unsigned int i, iMax = pModel->getListOfFunctionDefinitions()->size();
  for (i = 0;i < iMax;++i)
    {
      pFunDef = pModel->getFunctionDefinition(i);
      pRoot = pFunDef->getMath();
      // the actual function is the last child
      if (pRoot != NULL && pRoot->getNumChildren() > 0)
        {
          // function definitons have to be expanded
          const ASTNode* pMath = pRoot->getChild(pRoot->getNumChildren() - 1);
          assert(pMath != NULL);
          pNewRoot = expand_function_calls(pMath, pModel);
          assert(pNewRoot != NULL);
          try
            {
              pFraction = create_simplified_normalform(pNewRoot);
              assert(pFraction != NULL);
              //          mNormalizedFunctionDefinitions.push_back(pFraction);
            }
          catch (recursion_limit_exception e)
            {
              std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewRoot) << "\"." << std::endl;
            }
          catch (...)
            {
              std::cerr << "expression \"" << writeMathMLToString(pNewRoot) << "\" could not be normalized." << std::endl;
            }
          ++mNumFunctionDefinitions;
        }
    }
}

/**
 * Normalizes all expressions but the function definitions in the given
 * model.
 */
void stress_test::normalizeExpressions(const Model* pModel)
{
  // expressions can occur in assignments, initial assignments, kinetic laws event triggers,
  // event delays, event assignments and stiochiometric expressions
  const InitialAssignment* pInitialAssignment = NULL;
  const ASTNode* pMath = NULL;
  ASTNode* pNewMath = NULL;
  CNormalFraction* pFraction = NULL;
  // initial assignments
  unsigned int i, iMax = pModel->getListOfInitialAssignments()->size();
  for (i = 0;i < iMax;++i)
    {
      pInitialAssignment = pModel->getInitialAssignment(i);
      assert(pInitialAssignment != NULL);
      pMath = pInitialAssignment->getMath();
      if (pMath != NULL)
        {
          pNewMath = create_expression(pMath, pModel);
          assert(pNewMath != NULL);
          pFraction = create_normalform(pNewMath);
          delete pNewMath;
          assert(pFraction != NULL);
          //            this->mNormalizedExpressions.push_back(pFraction);
        }
    }
  // rules
  const Rule* pRule = NULL;
  iMax = pModel->getListOfRules()->size();
  for (i = 0;i < iMax;++i)
    {
      pRule = pModel->getRule(i);
      assert(pRule != NULL);
      pMath = pRule->getMath();
      if (pMath != NULL)
        {
          pNewMath = create_expression(pMath, pModel);
          assert(pNewMath != NULL);
          pFraction = create_normalform(pNewMath);
          delete pNewMath;
          assert(pFraction != NULL);
          //            this->mNormalizedExpressions.push_back(pFraction);
        }
    }
  // kinetic laws + stoichiometric expressions
  const Reaction* pReaction = NULL;
  iMax = pModel->getListOfReactions()->size();
  for (i = 0;i < iMax;++i)
    {
      pReaction = pModel->getReaction(i);
      assert(pReaction != NULL);
      const KineticLaw* pLaw = pReaction->getKineticLaw();
      if (pLaw != NULL)
        {
          pMath = pLaw->getMath();
          if (pMath != NULL)
            {
              pNewMath = create_expression(pMath, pModel);
              assert(pNewMath != NULL);
              pFraction = create_normalform(pNewMath);
              delete pNewMath;
              assert(pFraction != NULL);
              //                this->mNormalizedExpressions.push_back(pFraction);
            }
        }
      const SpeciesReference* pSpeciesReference = NULL;
      // substrates
      unsigned j, jMax = pReaction->getListOfReactants()->size();
      for (j = 0;j < jMax;++j)
        {
          pSpeciesReference = pReaction->getReactant(j);
          assert(pSpeciesReference != NULL);
          if (pSpeciesReference->isSetStoichiometryMath())
            {
              const StoichiometryMath* pSMath = pSpeciesReference->getStoichiometryMath();
              assert(pSMath != NULL);
              pMath = pSMath->getMath();
              if (pMath != NULL)
                {
                  pNewMath = create_expression(pMath, pModel);
                  assert(pNewMath != NULL);
                  pFraction = create_normalform(pNewMath);
                  delete pNewMath;
                  assert(pFraction != NULL);
                  //                    this->mNormalizedExpressions.push_back(pFraction);
                }
            }
        }
      // products
      jMax = pReaction->getListOfProducts()->size();
      for (j = 0;j < jMax;++j)
        {
          pSpeciesReference = pReaction->getProduct(j);
          assert(pSpeciesReference != NULL);
          if (pSpeciesReference->isSetStoichiometryMath())
            {
              const StoichiometryMath* pSMath = pSpeciesReference->getStoichiometryMath();
              assert(pSMath != NULL);
              pMath = pSMath->getMath();
              if (pMath != NULL)
                {
                  pNewMath = create_expression(pMath, pModel);
                  assert(pNewMath != NULL);
                  pFraction = create_normalform(pNewMath);
                  delete pNewMath;
                  assert(pFraction != NULL);
                  //                    this->mNormalizedExpressions.push_back(pFraction);
                }
            }
        }
    }
  // events
  const Event* pEvent = NULL;
  const Trigger* pTrigger = NULL;
  const Delay* pDelay = NULL;
  iMax = pModel->getListOfEvents()->size();
  for (i = 0;i < iMax;++i)
    {
      pEvent = pModel->getEvent(i);
      assert(pEvent != NULL);
      // trigger
      pTrigger = pEvent->getTrigger();
      assert(pTrigger != NULL);
      pMath = pTrigger->getMath();
      if (pMath != NULL)
        {
          pNewMath = create_expression(pMath, pModel);
          assert(pNewMath != NULL);
          pFraction = create_normalform(pNewMath);
          delete pNewMath;
          assert(pFraction != NULL);
          //            this->mNormalizedExpressions.push_back(pFraction);
        }

      // delay
      if (pEvent->isSetDelay())
        {
          pDelay = pEvent->getDelay();
          assert(pDelay != NULL);
          pMath = pDelay->getMath();
          if (pMath != NULL)
            {
              pNewMath = create_expression(pMath, pModel);
              assert(pNewMath != NULL);
              pFraction = create_normalform(pNewMath);
              delete pNewMath;
              assert(pFraction != NULL);
              //                this->mNormalizedExpressions.push_back(pFraction);
            }
        }

      // event assignments
      unsigned int j, jMax = pEvent->getListOfEventAssignments()->size();
      const EventAssignment* pEventAssignment = NULL;
      for (j = 0;j < jMax;++j)
        {
          pEventAssignment = pEvent->getEventAssignment(j);
          assert(pEventAssignment != NULL);
          pMath = pEventAssignment->getMath();
          if (pMath != NULL)
            {
              pNewMath = create_expression(pMath, pModel);
              assert(pNewMath != NULL);
              pFraction = create_normalform(pNewMath);
              delete pNewMath;
              assert(pFraction != NULL);
              //                this->mNormalizedExpressions.push_back(pFraction);
            }
        }
    }
}

/**
 * Normalizes the function definitions in the given model.
 */
void stress_test::normalizeFunctionDefinitions(const Model* pModel)
{
  const FunctionDefinition* pFunDef = NULL;
  const ASTNode* pRoot = NULL;
  ASTNode* pNewRoot = NULL;
  CNormalFraction* pFraction = NULL;
  unsigned int i, iMax = pModel->getListOfFunctionDefinitions()->size();
  for (i = 0;i < iMax;++i)
    {
      pFunDef = pModel->getFunctionDefinition(i);
      pRoot = pFunDef->getMath();
      // the actual function is the last child
      if (pRoot != NULL && pRoot->getNumChildren() > 0)
        {
          // function definitons have to be expanded
          const ASTNode* pMath = pRoot->getChild(pRoot->getNumChildren() - 1);
          assert(pMath != NULL);
          pNewRoot = expand_function_calls(pMath, pModel);
          assert(pNewRoot != NULL);
          pFraction = create_normalform(pNewRoot);
          assert(pFraction != NULL);
          //          mNormalizedFunctionDefinitions.push_back(pFraction);
        }
    }
}

/**
 * Normalizes COPASIs function database.
 */
void stress_test::normalizeFunctionDB()
{}

int main(int argc, char** argv)
{
  if (argc > 1)
    {
      int i = 1;
      std::vector<std::string> filenames;
      while (i < argc)
        {
          filenames.push_back(argv[i]);
          ++i;
        }
      stress_test test;
      test.run(filenames);
    }
  else
    {
      std::cerr << "Usage: stresstest SBMLFILE1 [SBMLFILE2 ...]" << std::endl;
    }
}
