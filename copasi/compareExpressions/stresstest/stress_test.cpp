// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/stresstest/stress_test.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/02/19 19:50:17 $
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

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/compareExpressions/CNormalFraction.h"
#include "copasi/compareExpressions/CNormalTranslation.h"

#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CMassAction.h"

#include "copasi/model/CModel.h"

/**
 * Constructor.
 */
stress_test::stress_test(): mNumFunctionDefinitions(0),
    mNumExceededFunctions(0),
    mNumFailedFunctions(0),
    mNumExpressions(0),
    mNumExceeded(0),
    mNumFailed(0),
    mNumCOPASIFunctions(0),
    mNumExceededCOPASIFunctions(0),
    mNumFailedCOPASIFunctions(0),
    mNumKineticFunctions(0),
    mNumMassActionsKinetics(0),
    mNumConstantFluxKinetics(0),
    mNumMappedKineticExpressions(0),
    mNumUnmappedKineticExpressions(0),
    mDifferentNormalform(0),
    mNumSBO(0),
    mpDataModel(NULL)
{
  // Create the root container.
  CCopasiRootContainer::init(false, 0, NULL);
  // Create the global data model.
  this->mpDataModel = CCopasiRootContainer::addDatamodel();
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
  std::vector<std::pair<std::string, CNormalFraction*> >::iterator it2 = mNormalizedFunctionDefinitions.begin(), endit2 = mNormalizedFunctionDefinitions.end();
  while (it2 != endit2)
    {
      delete it2->second;
      ++it2;
    }
  // delete normalforms of COPASI function definitions
  std::multimap<std::string, CNormalFraction*>::iterator it5 = mNormalizedCOPASIFunctionDefinitions.begin(), endit5 = mNormalizedCOPASIFunctionDefinitions.end();
  while (it5 != endit5)
    {
      delete it5->second;
      ++it5;
    }
  delete CCopasiRootContainer::Root;
  CCopasiRootContainer::Root = NULL;
}

/**
 * Goes through the list of files, loads each file and normalizes the
 * mathematical expressions in the contained model.
 */
void stress_test::run(const std::vector<std::string>& filenames)
{
  // first normalize the COPASIm function database
  // these normalized functions are later ued to compare
  // against kinetic expressions and function definitions
  normalizeFunctionDB();

  std::vector<std::string>::const_iterator it = filenames.begin(), endit = filenames.end();
  while (it != endit)
    {
      std::cout << "Processing " << *it << std::endl;
      this->normalizeMath(*it);
      ++it;
    }
  // output some statistics
  std::cout << "number of COPASI function definitions: " << mNumCOPASIFunctions << std::endl;
  std::cout << "number of exceeded COPASI function definitions: " << mNumExceededCOPASIFunctions << std::endl;
  std::cout << "number of failed COPASI function definitions: " << mNumFailedCOPASIFunctions << std::endl;
  if (!mUnreadableFiles.empty())
    {

      std::cout << "the following " << mUnreadableFiles.size() << " files could not be read: " << std::endl;
      std::vector<std::string>::const_iterator it = mUnreadableFiles.begin(), endit = mUnreadableFiles.end();
      while (it != endit)
        {
          std::cout << *it << std::endl;
          ++it;
        }
    }
  std::cout << mNumFiles << " files have been processed." << std::endl;
  std::cout << "number of function definitions: " << mNumFunctionDefinitions << std::endl;
  std::cout << "number of exceeded function definitions: " << mNumExceededFunctions << std::endl;
  std::cout << "number of failed function definitions: " << mNumFailedFunctions << std::endl;
  std::cout << "number of expressions: " << mNumExpressions << std::endl;
  std::cout << "number of exceeded expressions: " << mNumExceeded << std::endl;
  std::cout << "number of failed expressions: " << mNumFailed << std::endl;
  // now we compare the normalized function definitons from all files to the
  // normalized function definitions from the COPASI fucntion database
  std::multimap<std::string, CNormalFraction*>::iterator it2 = mNormalizedCOPASIFunctionDefinitions.begin(), endit2 = mNormalizedCOPASIFunctionDefinitions.end();
  --endit;
  while (it2 != endit2)
    {
      std::multimap<std::string, CNormalFraction*>::iterator it3 = it2, endit3 = mNormalizedCOPASIFunctionDefinitions.end();
      ++it3;
      while (it3 != endit3)
        {
          if (are_equal(it2->second, it3->second))
            {
              std::cout << "The functions \"" << it2->first << "\" and \"" << it3->first << "\" in the COPASI database are equal." << std::endl;
            }
          ++it3;
        }
      ++it2;
    }
  std::vector<std::pair<std::string, CNormalFraction*> >::iterator it5 = mNormalizedFunctionDefinitions.begin(), endit5 = mNormalizedFunctionDefinitions.end();
  unsigned int numClassified = 0;
  unsigned int numDubious = 0;
  while (it5 != endit5)
    {
      std::multimap<std::string, CNormalFraction*>::iterator it3 = mNormalizedCOPASIFunctionDefinitions.begin(), endit3 = mNormalizedCOPASIFunctionDefinitions.end();
      bool found = false;
      while (it3 != endit3)
        {
          if (are_equal(it5->second, it3->second))
            {
              if (found == true)
                {
                  ++numDubious;
                  --numClassified;
                  break;
                }
              else
                {
                  found = true;
                  ++numClassified;
                }
            }
          ++it3;
        }
      ++it5;
    }
  std::cout << "Number of function definitons that could be classified: " << numClassified << std::endl;
  std::cout << "Number of function definitons that were classified incorrectly: " << numDubious << std::endl;
  std::cout << "Number of function definitons that could not be classified: " << mNormalizedFunctionDefinitions.size() - numClassified - numDubious << std::endl;
  std::cout << "Number of kinetic expressions: " << mNumKineticFunctions << std::endl;
  std::cout << "Number of kinetic expressions that could be mapped to a function definition: " << mNumMappedKineticExpressions << std::endl;
  std::cout << "Number of kinetic expressions that could not be mapped to a function definition: " << mNumUnmappedKineticExpressions << std::endl;
  std::cout << "List of the number of expressions mapped to a certain function definition: " << std::endl;
  std::map<std::string, unsigned int>::iterator it6 = mExpressionMappings.begin(), endit6 = mExpressionMappings.end();
  while (it6 != endit6)
    {
      std::cout << it6->first << " : " << it6->second << std::endl;
      ++it6;
    }
  std::cout << "There are " << mSBOMap.size() << " different SBO Terms." << std::endl;
  std::map<int, std::vector<CNormalFraction*> >::iterator sboIt = mSBOMap.begin(), sboEndit = mSBOMap.end();
  while (sboIt != sboEndit)
    {
      std::cout << "There are " << sboIt->second.size() << " expressions for SBO term " << sboIt->first << "." << std::endl;
      ++sboIt;
    }
  std::cout << "Number of kinetic expressions with sbo terms: " << mNumSBO << std::endl;
  std::cout << "Number of kinetic expressions with sbo terms that could not be normalized to the same normalform: " << mDifferentNormalform << std::endl;
  std::cout << "The expressions that could not be mapped are divided into " << mUnknownCategories.size() << " different expressions." << std::endl;
}

/**
 * Loads an sbml model from the given file and
 * normalized all mathematical expressions in the SBML model.
 */
void stress_test::normalizeMath(const std::string& filename)
{
  bool result = false;
  if (this->mpDataModel != NULL)
    {
      try
        {
          result = this->mpDataModel->importSBML(filename);
          ++mNumFiles;
        }
      catch (...)
        {
          mUnreadableFiles.push_back(filename);
        }
      if (result == true)
        {
          const SBMLDocument* pDocument = this->mpDataModel->getCurrentSBMLDocument();
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
              ++mNumExceeded;
            }
          catch (...)
            {
              std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
              ++mNumFailed;
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
              ++mNumExceeded;
            }
          catch (...)
            {
              std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
              ++mNumFailed;
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
      int sboTerm = pLaw->getSBOTerm();
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
                  ++mNumKineticFunctions;
                  // find the COPASI Reaction that corresponds to this reaction
                  std::string id = pReaction->getId();
                  const CReaction* pCOPASIReaction = NULL;
                  unsigned int z = 0, zMax = this->mpDataModel->getModel()->getReactions().size();
                  while (z < zMax)
                    {
                      if (this->mpDataModel->getModel()->getReactions()[z]->getSBMLId() == id)
                        {
                          pCOPASIReaction = this->mpDataModel->getModel()->getReactions()[z];
                          break;
                        }
                      ++z;
                    }
                  assert(pCOPASIReaction != NULL);
                  if (dynamic_cast<const CMassAction*>(pCOPASIReaction->getFunction()) == NULL)
                    {
                      if (pCOPASIReaction->getFunction()->getObjectName().find("Constant flux") != std::string::npos)
                        {
                          ++mNumMappedKineticExpressions;
                          if (mExpressionMappings.find("Constant Flux") == mExpressionMappings.end())
                            {
                              mExpressionMappings["Constant Flux"] = 1;
                            }
                          else
                            {
                              mExpressionMappings["Constant Flux"] = mExpressionMappings["Constant Flux"] + 1;
                            }
                        }
                      else
                        {
                          // compare with the normalized expressions from the
                          // function definitions
                          std::multimap<std::string, CNormalFraction*>::iterator it = mNormalizedCOPASIFunctionDefinitions.begin(), endit = mNormalizedCOPASIFunctionDefinitions.end();
                          bool found = false;
                          while (it != endit)
                            {
                              if (are_equal(pFraction, it->second))
                                {
                                  // we found a match
                                  found = true;
                                  if (mExpressionMappings.find(it->first) == mExpressionMappings.end())
                                    {
                                      mExpressionMappings[it->first] = 1;
                                    }
                                  else
                                    {
                                      mExpressionMappings[it->first] = mExpressionMappings[it->first] + 1;
                                    }
                                  break;
                                }
                              ++it;
                            }
                          if (found)
                            {
                              ++mNumMappedKineticExpressions;
                            }
                          else
                            {
                              ++mNumUnmappedKineticExpressions;
                              // compare against the other unmapped functions
                              std::map<CNormalFraction*, int>::iterator catIt = mUnknownCategories.begin(), catEndit = mUnknownCategories.end();
                              found = false;
                              while (catIt != catEndit)
                                {
                                  if (are_equal(pFraction, catIt->first))
                                    {
                                      found = true;
                                      ++(catIt->second);
                                    }
                                  ++catIt;
                                }
                              if (!found)
                                {
                                  mUnknownCategories[pFraction] = 1;
                                }
                            }
                        }
                    }
                  else
                    {
                      ++mNumMappedKineticExpressions;
                      if (mExpressionMappings.find("Mass Action") == mExpressionMappings.end())
                        {
                          mExpressionMappings["Mass Action"] = 1;
                        }
                      else
                        {
                          mExpressionMappings["Mass Action"] = mExpressionMappings["Mass Action"] + 1;
                        }
                    }
                  //                this->mNormalizedExpressions.push_back(pFraction);
                  if (sboTerm != -1)
                    {
                      ++mNumSBO;
                      if (mSBOMap.find(sboTerm) == mSBOMap.end())
                        {
                          std::vector<CNormalFraction*> v;
                          v.push_back(pFraction);
                          mSBOMap[sboTerm] = v;
                        }
                      else
                        {
                          if (!are_equal(pFraction, mSBOMap[sboTerm][0]))
                            {
                              std::cout << "Some expressions for SBO term " << sboTerm << " can not be normalized to the same normal form." << std::endl;
                              ++mDifferentNormalform;
                            }
                          mSBOMap[sboTerm].push_back(pFraction);
                        }
                    }
                  //delete pFraction;
                }
              catch (recursion_limit_exception e)
                {
                  std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewMath) << "\"." << std::endl;
                  ++mNumExceeded;
                }
              catch (...)
                {
                  std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                  ++mNumFailed;
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
                      ++mNumExceeded;
                    }
                  catch (...)
                    {
                      std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                      ++mNumFailed;
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
                      ++mNumExceeded;
                    }
                  catch (...)
                    {
                      std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                      ++mNumFailed;
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
              ++mNumExceeded;
            }
          catch (...)
            {
              std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
              ++mNumFailed;
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
                  ++mNumExceeded;
                }
              catch (...)
                {
                  std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                  ++mNumFailed;
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
                  ++mNumExceeded;
                }
              catch (...)
                {
                  std::cerr << "expression \"" << writeMathMLToString(pNewMath) << "\" could not be normalized." << std::endl;
                  ++mNumFailed;
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
              mNormalizedFunctionDefinitions.push_back(std::pair<std::string, CNormalFraction*>(pFunDef->getId(), pFraction));
            }
          catch (recursion_limit_exception e)
            {
              std::cerr << "recursion limit exceeded for expression \"" << writeMathMLToString(pNewRoot) << "\"." << std::endl;
              ++mNumExceededFunctions;
            }
          catch (...)
            {
              std::cerr << "expression \"" << writeMathMLToString(pNewRoot) << "\" could not be normalized." << std::endl;
              ++mNumFailedFunctions;
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
{
  CFunctionDB* pFunctionDB = CCopasiRootContainer::getFunctionList();
  assert(pFunctionDB != NULL);
  CCopasiVectorN< CEvaluationTree > & loadedFunctions = pFunctionDB->loadedFunctions();
  unsigned int i = 0, iMax = loadedFunctions.size();
  while (i < iMax)
    {
      CEvaluationTree* pTree = loadedFunctions[i];
      assert(pTree != NULL);
      if (dynamic_cast<const CFunction*>(pTree) != NULL && dynamic_cast<const CMassAction*>(pTree) == NULL)
        {
          // make sure it is not mass action
          try
            {
              CEvaluationNode* pExpanded = expand_function_calls(pTree->getRoot(), pFunctionDB);
              assert(pExpanded != NULL);
              CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pExpanded);
              delete pExpanded;
              assert(pFraction != NULL);
              mNormalizedCOPASIFunctionDefinitions.insert(std::pair<const std::string, CNormalFraction*>(pTree->getObjectName(), pFraction));
              ++mNumCOPASIFunctions;
            }
          catch (recursion_limit_exception e)
            {
              std::cerr << "recursion limit exceeded for expression:" << std::endl;
              pTree->getRoot()->printRecursively();
              ++mNumExceededCOPASIFunctions;
            }
          catch (...)
            {
              std::cerr << "expression could not be normalized: " << std::endl;
              pTree->getRoot()->printRecursively();
              ++mNumFailedCOPASIFunctions;
            }
        }
      ++i;
    }
}

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
