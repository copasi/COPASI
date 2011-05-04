// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/stresstest/stress_test.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/05/04 17:35:52 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef STRESS_TEST_H__
#define STRESS_TEST_H__

#include <string>
#include <vector>
#include <map>
#include <set>
#include <sys/time.h>

class CNormalFraction;
class Model;
class CCopasiDataModel;
class ASTNode;
class Reaction;

// This test reads all models from the biomodels database and normalizes all
// mathematical expressions it finds in there.
// Later on, it will do the same for the functions in COPASIs function database
// and compare the expressions from the model to those in the function database
// in order to find out if they are the same.
class stress_test
{
public:
  /**
   * Constructor.
   */
  stress_test();

  /**
   * Destructor.
   */
  virtual ~stress_test();

  /**
   * Goes through the list of files, loads each file and normalizes the
   * mathematical expressions in the contained model.
   */
  void run(const std::vector<std::string>& filenames);

protected:
  /**
   * Loads an sbml model from the given file and
   * normalized all mathematical expressions in the SBML model.
   */
  void normalizeMath(const std::string& filename);

  /**
   * Normalizes all expressions but the function definitions in the given
   * model.
  void normalizeExpressions(const Model* pModel);
   */

  /**
   * Normalizes the function definitions in the given model.
  void normalizeFunctionDefinitions(const Model* pModel);
   */

  /**
   * Normalizes all expressions but the function definitions in the given
   * model.
   */
  void normalizeAndSimplifyExpressions(const Model* pModel);

  /**
   * Normalizes the function definitions in the given model.
   */
  void normalizeAndSimplifyFunctionDefinitions(const Model* pModel);

  /**
   * Normalizes COPASIs function database.
   */
  void normalizeFunctionDB();

  static bool normalize_names(ASTNode* pNode, const Reaction* pReaction, const Model* pModel);

protected:
  unsigned int mNumFunctionDefinitions;
  unsigned int mNumExceededFunctions;
  unsigned int mNumFailedFunctions;
  unsigned int mNumExpressions;
  unsigned int mNumExceeded;
  unsigned int mNumFailed;
  unsigned int mNumCOPASIFunctions;
  unsigned int mNumExceededCOPASIFunctions;
  unsigned int mNumFailedCOPASIFunctions;
  unsigned int mNumFiles;
  unsigned int mNumKineticFunctions;
  unsigned int mNumMassActionsKinetics;
  unsigned int mNumConstantFluxKinetics;
  unsigned int mNumMappedKineticExpressions;
  unsigned int mNumUnmappedKineticExpressions;
  std::vector<CNormalFraction*> mNormalizedExpressions;
  std::vector<std::pair<std::string, CNormalFraction*> > mNormalizedFunctionDefinitions;
  std::multimap<std::string, CNormalFraction*> mNormalizedCOPASIFunctionDefinitions;
  std::vector<std::string> mUnreadableFiles;
  std::map<std::string, unsigned int> mExpressionMappings;
  std::map<int, std::vector<CNormalFraction*> > mSBOMap;
  std::map<CNormalFraction*, int> mUnknownCategories;
  unsigned int mDifferentNormalform;
  unsigned int mNumSBO;
  CCopasiDataModel* mpDataModel;
  struct timeval mTV1;
  struct timezone mTZ1;
  struct timeval mTV2;
  struct timezone mTZ2;
  std::set<double> mProcessTimes;
};

#endif // STRESS_TEST_H__
