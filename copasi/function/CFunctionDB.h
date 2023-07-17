// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionDB
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunctionDB
#define COPASI_CFunctionDB

#include "copasi/function/CEvaluationTree.h"

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/core/CDataVector.h"
#include "copasi/math/CMathDependencyGraph.h"

class CFunction;
class CModel;

/** @dia:pos 106.082,17.0878 */
class CFunctionDB : public CDataContainer
{
  // Attributes
private:
  /**
   *  Filename which contains the function database
   */
  std::string mFilename;

  /**
   *  Vector of the currently loaded functions
   */
  CDataVectorN < CFunction > mLoadedFunctions;

  /**
   * The function dependencies
   */
  CMathDependencyGraph mDependencies;

  // Operations

public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CFunctionDB(const std::string & name,
              const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CFunctionDB();

  /**
   *
   */
  void cleanup();

  void initObjects();

  bool load();

  bool load(const std::string& fileName);
  bool save(const std::string& fileName);

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return mFail
   */
  C_INT32 load(CReadConfig & configbuffer);

  /**
   *
   */
  void setFilename(const std::string & filename);

  /**
   *
   */
  std::string getFilename() const;

#ifdef FFFF
  /**
   *  Load the function functionName from the database
   *  @param "const string" &functionName
   *  @return CEvaluationTree * function (NULL if function can not be loaded)
   */
  CEvaluationTree * dBLoad(const std::string & functionName);
#endif // FFFF

  /**
   * Add the function to the database
   * @param CFunction * pFunction
   * @param const bool & adopt (default = false)
   * @return bool success
   */
  bool add(CFunction * pFunction, const bool & adopt);

  /**
   * Add the function to the database, if necessary adapt the name so it
   * is unique.
   */
  CFunction * addAndAdaptName(CFunction * pFunction);

#ifdef FFFF
  /**
   *  Add the function to the database
   *  @param const std::string & name
   *  @param const CEvaluationTree::Type & type (Default: CEvaluationTree::Base)
   *  @return bool success
   */
  CEvaluationTree* createFunction(const std::string &name, const CEvaluationTree::Type & type = CEvaluationTree::Function);
#endif // FFFF

  bool removeFunction(size_t index);

  bool removeFunction(const std::string &key);

  /**
   *  Delete the function functionName from the database
   *  @param "const string" &functionName
   *  @return C_INT32 Fail
   */
  //void dBDelete(const std::string & functionName);

  /**
   *  Search for a function among the loaded functions. If no
   *  function is found NULL is returned
   *  @param "const string" &functionName
   *  @return CFunction *
   */
  CFunction * findFunction(const std::string & functionName);

  /**
   *  Search for a function among the loaded functions. If no
   *  function is found the database is searched and the apropriate
   *  function is loaded.
   *  @param "const string" &functionName
   *  @return CFunction * function (NULL if function is not found)
   */
  CFunction * findLoadFunction(const std::string & functionName);

  /**
   *  Retrieves the vector of loaded functions.
   *  @return "CDataVectorNS < CFunction > &" loadedFunctions
   */
  CDataVectorN < CFunction > & loadedFunctions();

  /**
   *  Retrieves the vector of functions that are suitable for a
   *  number of substrates, products and reversibility status.
   *  Note: The returns CDataVector has to be deleted after use!
   *  @param "const size_t" noSubstrates the number of substrates
   *  @param "const size_t" noProducts the number of products
   *  @param "const TriLogic" reversible the reversibility status
   *  @return "std::vector<CFunction*> " suitableFunctions
   */
  std::vector<CFunction*>
  suitableFunctions(const size_t noSubstrates,
                    const size_t noProducts,
                    const TriLogic reversibility);

  /**
   * Appends pointers to function, which are dependent on any of the candidates
   * to the list dependentFunctions.
   * @param const ObjectSet & candidates
   * @param std::set< const CDataObject * > & dependentFunctions
   * @return bool functionsAppended
   */
  bool appendDependentFunctions(const ObjectSet & candidates,
                                DataObjectSet & dependentFunctions) const;

  /**
   * Retrieves a list of all functions used in the model
   * @return std::vector< const CFunction * > usedFunctions
   */
  std::vector< const CFunction * > getUsedFunctions(const CModel* pModel) const;

  /**
   * Purge all unused user defined functions from the data base
   */
  void purgeUnusedUserDefinedFunctions();
};

#endif // COPASI_CFunctionDB
