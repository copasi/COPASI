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

#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
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
  mNumFiles(0),
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
  CRootContainer::init(false, 0, NULL);
  // Create the global data model.
  this->mpDataModel = CRootContainer::addDatamodel();
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

  CRootContainer::destroy();
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
  std::map<CNormalFraction*, int>::const_iterator catIt = mUnknownCategories.begin(), catEndit = mUnknownCategories.end();
  unsigned int moreThanOne = 0;
  unsigned int moreThanFive = 0;
  unsigned int moreThanTen = 0;
  unsigned int moreThanTwenty = 0;
  unsigned int numMoreThanOne = 0;
  unsigned int numMoreThanFive = 0;
  unsigned int numMoreThanTen = 0;
  unsigned int numMoreThanTwenty = 0;

  while (catIt != catEndit)
    {
      if (catIt->second > 20)
        {
          ++moreThanTwenty;
          numMoreThanTwenty += catIt->second;
          std::cout << "Expression with more than 20 instances: " << catIt->first->toString() << std::endl;
        }
      else if (catIt->second > 10)
        {
          ++moreThanTen;
          numMoreThanTen += catIt->second;
        }
      else if (catIt->second > 5)
        {
          ++moreThanFive;
          numMoreThanFive += catIt->second;
        }
      else if (catIt->second > 1)
        {
          ++moreThanOne;
          numMoreThanOne += catIt->second;
        }

      ++catIt;
    }

  std::cout << moreThanTwenty << " uncategorized expressions have more than 20 instances (" << numMoreThanTwenty << " total)" << std::endl;
  std::cout << moreThanTen << " uncategorized expressions have more than 10 instances (" << numMoreThanTen << " total)" << std::endl;
  std::cout << moreThanFive << " uncategorized expressions have more than 5 instances (" << numMoreThanFive << " total)" << std::endl;
  std::cout << moreThanOne << " uncategorized expressions have more than 1 instance (" << numMoreThanOne << " total)" << std::endl;
  std::cout << mUnknownCategories.size() - (moreThanTwenty + moreThanTen + moreThanFive + moreThanOne) << " uncategorized expression are unique." << std::endl;
  std::set<double>::reverse_iterator timeIt = mProcessTimes.rbegin(), timeEndit = mProcessTimes.rend();
  unsigned int num = 0;

  while (timeIt != timeEndit && (*timeIt) > 600)
    {
      ++num;
      ++timeIt;
    }

  if (num != 0)
    {
      std::cout << "Number of expression taking more than 10 minutes: " << num << std::endl;
      num = 0;
    }

  while (timeIt != timeEndit && (*timeIt) > 60)
    {
      ++num;
      ++timeIt;
    }

  if (num != 0)
    {
      std::cout << "Number of expression taking more than 1 minute: " << num << std::endl;
    }

  while (timeIt != timeEndit && (*timeIt) > 10)
    {
      ++num;
      ++timeIt;
    }

  if (num != 0)
    {
      std::cout << "Number of expression taking more than 10 seconds: " << num << std::endl;
    }

  while (timeIt != timeEndit && (*timeIt) > 1)
    {
      ++num;
      ++timeIt;
    }

  if (num != 0)
    {
      std::cout << "Number of expression taking more than 1 second: " << num << std::endl;
    }

  while (timeIt != timeEndit && (*timeIt) > 0.1)
    {
      ++num;
      ++timeIt;
    }

  if (num != 0)
    {
      std::cout << "Number of expression taking more than 1/10 seconds: " << num << std::endl;
    }

  while (timeIt != timeEndit && (*timeIt) > 0.01)
    {
      ++num;
      ++timeIt;
    }

  if (num != 0)
    {
      std::cout << "Number of expression taking more than 1/100 seconds: " << num << std::endl;
    }

  while (timeIt != timeEndit)
    {
      ++num;
      ++timeIt;
    }

  if (num != 0)
    {
      std::cout << "Number of expression taking less than 1/100 seconds: " << num << std::endl;
    }
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

  for (i = 0; i < iMax; ++i)
    {
      pInitialAssignment = pModel->getInitialAssignment(i);
      assert(pInitialAssignment != NULL);
      pMath = pInitialAssignment->getMath();

      if (pMath != NULL)
        {
          pNewMath = create_expression(pMath, pModel->getListOfFunctionDefinitions());
          assert(pNewMath != NULL);

          try
            {
              gettimeofday(&mTV1, &mTZ1);
              pFraction = create_simplified_normalform(pNewMath);
              gettimeofday(&mTV2, &mTZ2);
              double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

              if (mTV2.tv_usec < mTV1.tv_usec)
                {
                  timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }
              else
                {
                  timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }

              mProcessTimes.insert(timeDiff);
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

  for (i = 0; i < iMax; ++i)
    {
      pRule = pModel->getRule(i);
      assert(pRule != NULL);
      pMath = pRule->getMath();

      if (pMath != NULL)
        {
          pNewMath = create_expression(pMath, pModel->getListOfFunctionDefinitions());
          assert(pNewMath != NULL);

          try
            {
              gettimeofday(&mTV1, &mTZ1);
              pFraction = create_simplified_normalform(pNewMath);
              assert(pFraction != NULL);
              //            this->mNormalizedExpressions.push_back(pFraction);
              gettimeofday(&mTV2, &mTZ2);
              double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

              if (mTV2.tv_usec < mTV1.tv_usec)
                {
                  timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }
              else
                {
                  timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }

              mProcessTimes.insert(timeDiff);
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

  for (i = 0; i < iMax; ++i)
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
              pNewMath = create_expression(pMath, pModel->getListOfFunctionDefinitions());
              // we normalize the names of all named nodes
              bool result = stress_test::normalize_names(pNewMath, pReaction, pModel);
              assert(result == true);
              assert(pNewMath != NULL);

              try
                {
                  gettimeofday(&mTV1, &mTZ1);
                  pFraction = create_simplified_normalform(pNewMath);
                  gettimeofday(&mTV2, &mTZ2);
                  double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

                  if (mTV2.tv_usec < mTV1.tv_usec)
                    {
                      timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                    }
                  else
                    {
                      timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                    }

                  mProcessTimes.insert(timeDiff);
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

      for (j = 0; j < jMax; ++j)
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
                  pNewMath = create_expression(pMath, pModel->getListOfFunctionDefinitions());
                  assert(pNewMath != NULL);

                  try
                    {
                      gettimeofday(&mTV1, &mTZ1);
                      pFraction = create_simplified_normalform(pNewMath);
                      gettimeofday(&mTV2, &mTZ2);
                      double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

                      if (mTV2.tv_usec < mTV1.tv_usec)
                        {
                          timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                        }
                      else
                        {
                          timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                        }

                      mProcessTimes.insert(timeDiff);
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

      for (j = 0; j < jMax; ++j)
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
                  pNewMath = create_expression(pMath, pModel->getListOfFunctionDefinitions());
                  assert(pNewMath != NULL);

                  try
                    {
                      gettimeofday(&mTV1, &mTZ1);
                      pFraction = create_simplified_normalform(pNewMath);
                      gettimeofday(&mTV2, &mTZ2);
                      double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

                      if (mTV2.tv_usec < mTV1.tv_usec)
                        {
                          timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                        }
                      else
                        {
                          timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                        }

                      mProcessTimes.insert(timeDiff);
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

  for (i = 0; i < iMax; ++i)
    {
      pEvent = pModel->getEvent(i);
      assert(pEvent != NULL);
      // trigger
      pTrigger = pEvent->getTrigger();
      assert(pTrigger != NULL);
      pMath = pTrigger->getMath();

      if (pMath != NULL)
        {
          pNewMath = create_expression(pMath, pModel->getListOfFunctionDefinitions());
          assert(pNewMath != NULL);

          try
            {
              gettimeofday(&mTV1, &mTZ1);
              pFraction = create_simplified_normalform(pNewMath);
              gettimeofday(&mTV2, &mTZ2);
              double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

              if (mTV2.tv_usec < mTV1.tv_usec)
                {
                  timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }
              else
                {
                  timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }

              mProcessTimes.insert(timeDiff);
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
              pNewMath = create_expression(pMath, pModel->getListOfFunctionDefinitions());
              assert(pNewMath != NULL);

              try
                {
                  gettimeofday(&mTV1, &mTZ1);
                  pFraction = create_simplified_normalform(pNewMath);
                  gettimeofday(&mTV2, &mTZ2);
                  double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

                  if (mTV2.tv_usec < mTV1.tv_usec)
                    {
                      timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                    }
                  else
                    {
                      timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                    }

                  mProcessTimes.insert(timeDiff);
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

      for (j = 0; j < jMax; ++j)
        {
          pEventAssignment = pEvent->getEventAssignment(j);
          assert(pEventAssignment != NULL);
          pMath = pEventAssignment->getMath();

          if (pMath != NULL)
            {
              pNewMath = create_expression(pMath, pModel->getListOfFunctionDefinitions());
              assert(pNewMath != NULL);

              try
                {
                  gettimeofday(&mTV1, &mTZ1);
                  pFraction = create_simplified_normalform(pNewMath);
                  gettimeofday(&mTV2, &mTZ2);
                  double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

                  if (mTV2.tv_usec < mTV1.tv_usec)
                    {
                      timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                    }
                  else
                    {
                      timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                    }

                  mProcessTimes.insert(timeDiff);
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

  for (i = 0; i < iMax; ++i)
    {
      pFunDef = pModel->getFunctionDefinition(i);
      pRoot = pFunDef->getMath();

      // the actual function is the last child
      if (pRoot != NULL && pRoot->getNumChildren() > 0)
        {
          // function definitons have to be expanded
          const ASTNode* pMath = pRoot->getChild(pRoot->getNumChildren() - 1);
          assert(pMath != NULL);
          pNewRoot = expand_function_calls(pMath, pModel->getListOfFunctionDefinitions());
          assert(pNewRoot != NULL);

          try
            {
              gettimeofday(&mTV1, &mTZ1);
              pFraction = create_simplified_normalform(pNewRoot);
              gettimeofday(&mTV2, &mTZ2);
              double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

              if (mTV2.tv_usec < mTV1.tv_usec)
                {
                  timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }
              else
                {
                  timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }

              mProcessTimes.insert(timeDiff);
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
 */

/**
 * Normalizes the function definitions in the given model.
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
 */

/**
 * Normalizes COPASIs function database.
 */
void stress_test::normalizeFunctionDB()
{
  CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();
  assert(pFunctionDB != NULL);
  CDataVectorN< CFunction > & loadedFunctions = pFunctionDB->loadedFunctions();
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
              gettimeofday(&mTV1, &mTZ1);
              CNormalFraction* pFraction = CNormalTranslation::normAndSimplifyReptdly(pExpanded);
              gettimeofday(&mTV2, &mTZ2);
              double timeDiff = mTV2.tv_sec - mTV1.tv_sec;

              if (mTV2.tv_usec < mTV1.tv_usec)
                {
                  timeDiff -= (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }
              else
                {
                  timeDiff += (mTV2.tv_usec - mTV1.tv_usec) / 1e6;
                }

              mProcessTimes.insert(timeDiff);
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

bool stress_test::normalize_names(ASTNode* pNode, const Reaction* pReaction, const Model* pModel)
{
  bool result = true;
  std::vector<std::pair<ASTNode*, unsigned int> > nodeStack;
  std::map<std::string, std::string> replacementMap;

  unsigned int compartment_index = 1;
  unsigned int species_index = 1;
  unsigned int reaction_index = 1;
  unsigned int parameter_index = 1;
  std::ostringstream os;
  // first we collect all ids
  ASTNode* pCurrent = pNode;
  unsigned int iMax;
  nodeStack.push_back(std::pair<ASTNode*, unsigned int>(NULL, 0));
  std::map<std::string, std::string>::const_iterator pos;

  while (pCurrent != NULL)
    {
      // if the object is already on the node stack, we go
      // either to the next child or one up
      if (pCurrent == nodeStack.back().first)
        {
          ++nodeStack.back().second;

          if (nodeStack.back().second == pCurrent->getNumChildren())
            {
              // we are done here and we have to go one up
              nodeStack.erase(--nodeStack.end());
              pCurrent = nodeStack.back().first;
            }
          else
            {
              // next child
              pCurrent = pCurrent->getChild(nodeStack.back().second);
            }
        }
      else
        {
          iMax = pCurrent->getNumChildren();

          // if there are children, add the node to
          // the node stack
          if (iMax > 0)
            {
              nodeStack.push_back(std::pair<ASTNode*, unsigned int>(pCurrent, 0));
              pCurrent = pCurrent->getChild(0);
            }
          else
            {
              if (pCurrent->isName())
                {
                  // check if the name is the id of a compartment, a species, a reaction
                  // a global parameter or one of the reaction parameters
                  // if so, we add a new entry to out replacement map
                  // we check in the order parameters, species, compartment and reaction
                  // because that should result in the least tests
                  std::string id = pCurrent->getName();
                  // do we already know this id?
                  pos = replacementMap.find(id);

                  if (pos == replacementMap.end())
                    {
                      // if not, we create a replacement
                      if ((pReaction->getKineticLaw() != NULL && pReaction->getKineticLaw()->getParameter(id) != NULL) || pModel->getParameter(id) != NULL)
                        {
                          os.str("");
                          os << "K_" << parameter_index;
                          replacementMap.insert(std::pair<std::string, std::string>(id, os.str()));
                          pCurrent->setName(os.str().c_str());
                          ++parameter_index;
                        }
                      else if (pModel->getSpecies(id) != NULL)
                        {
                          os.str("");
                          os << "S_" << species_index;
                          replacementMap.insert(std::pair<std::string, std::string>(id, os.str()));
                          pCurrent->setName(os.str().c_str());
                          ++species_index;
                        }
                      else if (pModel->getCompartment(id) != NULL)
                        {
                          os.str("");
                          os << "C_" << compartment_index;
                          replacementMap.insert(std::pair<std::string, std::string>(id, os.str()));
                          pCurrent->setName(os.str().c_str());
                          ++compartment_index;
                        }
                      else if (pModel->getReaction(id) != NULL)
                        {
                          os.str("");
                          os << "R_" << reaction_index;
                          replacementMap.insert(std::pair<std::string, std::string>(id, os.str()));
                          pCurrent->setName(os.str().c_str());
                          ++reaction_index;
                        }
                      else
                        {
                          // lets see if there are any for these
                          assert(false);
                        }
                    }
                  else
                    {
                      pCurrent->setName(pos->second.c_str());
                    }
                }

              // continue with the parent
              pCurrent = nodeStack.back().first;
            }
        }
    }

  return result;
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
