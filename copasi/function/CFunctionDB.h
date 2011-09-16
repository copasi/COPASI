// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionDB.h,v $
//   $Revision: 1.57 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/16 18:06:53 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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

#include "function/CEvaluationTree.h"

#include "report/CCopasiContainer.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CReadConfig.h"
#include "utilities/CCopasiVector.h"

class CFunction;
class CModel;

/** @dia:pos 106.082,17.0878 */
class CFunctionDB : public CCopasiContainer
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
  CCopasiVectorN < CFunction > mLoadedFunctions;

  // Operations

public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  //CFunctionDB(const std::string & name = "FunctionDB",
  //            const CCopasiContainer * pParent = NULL);
  CFunctionDB(const std::string & name,
              const CCopasiContainer * pParent);

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
  void addAndAdaptName(CFunction * pFunction);

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
   *  @return "CCopasiVectorNS < CFunction > &" loadedFunctions
   */
  CCopasiVectorN < CFunction > & loadedFunctions();

  /**
   *  Retrieves the vector of functions that are suitable for a
   *  number of substrates, products and reversibility status.
   *  Note: The returns CCopasiVector has to be deleted after use!
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
   * @param std::set< const CCopasiObject * > candidates
   * @param std::set< const CCopasiObject * > & dependentFunctions
   * @return bool functionsAppended
   */
  bool appendDependentFunctions(std::set< const CCopasiObject * > candidates,
                                std::set< const CCopasiObject * > & dependentFunctions) const;

  /**
   * Retrieve a list of evaluation trees depending on the tree with the
   * given name.
   * @param const std::string & name
   * @return std::set<std::string> list
   */
  std::set<std::string> listDependentTrees(const std::string & name) const;

  /**
   * Retrieves a list of all functions used in the model
   * @return std::vector< CEvaluationTree * > usedFunctions
   */
  std::vector< CFunction * > getUsedFunctions(const CModel* pModel) const;
};

#endif // COPASI_CFunctionDB
