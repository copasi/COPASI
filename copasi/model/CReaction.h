// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
 *  CReaction class.
 *  Derived from Gepasi's cstep.cpp. (C) Pedro Mendes 1995-2000.
 *
 *  Converted for COPASI by Stefan Hoops 2001
 */

#ifndef COPASI_CReaction
#define COPASI_CReaction

#include <string>
#include <vector>

#include "copasi/model/CAnnotation.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CChemEq.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/model/CCompartment.h"

#include "copasi/utilities/CCopasiVector.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CCallParameters.h"
#include "copasi/function/CFunctionParameters.h"

class CReadConfig;
class SBase;
class CFunctionDB;

class CReaction : public CCopasiContainer, public CAnnotation
{
public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CReaction(const std::string & name = "NoName",
            const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CReaction &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CReaction(const CReaction & src,
            const CCopasiContainer * pParent = NULL);

private:
  CReaction & operator= (const CReaction &);

public:
  /**
   *  Destructor
   */
  virtual ~CReaction();

  /**
   * Retrieve the units of the child object.
   * @return std::string units
   */
  virtual std::string getChildObjectUnits(const CCopasiObject * pObject) const;

  /**
   * Delete
   */
  void cleanup();

  /**
   * Overload display name. Special treatment for reaction to
   * provide a shorter display
   */
  virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

  /**
   * Loads an object with data coming from a CReadConfig object.
   * (CReadConfig object reads an input stream)
   * @param pconfigbuffer reference to a CReadConfig object.
   * @return mFail
   * @see mFail
   */
  C_INT32 load(CReadConfig & configbuffer);

  /**
   * Sets the parent of the metabolite;
   * @param const CCopasiContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CCopasiContainer * pParent);

  /**
   * Retrieve the list of deleted numeric child objects;
   * @return std::set< const CCopasiObject * > deletedObjects
   */
  virtual std::set< const CCopasiObject * > getDeletedObjects() const;

  /**
   * Check whether an object must be deleted because its prerequisites can
   * no longer be fulfilled due to the given deleted objects
   * @param const DataObjectSet & deletedObjects
   * @return bool mustBeDeleted
   */
  virtual bool mustBeDeleted(const DataObjectSet & deletedObjects) const;

  /**
   *  Retrieves the key of the reaction
   *  @return std::string key
   */
  virtual const std::string & getKey() const;

  /**
   * Retrieves the chemical equation of the reaction
   * @return const CChemEq & chemEq
   */
  const CChemEq & getChemEq() const;

  /**
   * Retrieves the chemical equation of the reaction
   * @return CChemEq & chemEq
   */
  CChemEq & getChemEq();

  /**
   * Retrieves the rate function of the reaction
   * @return "CBaseFunction &"
   */
  const CFunction * getFunction() const;

  /**
   * Retrieves the flux of the reaction
   * @return const C_FLOAT64 & flux
   */
  const C_FLOAT64 & getFlux() const;

  /**
   * Retrieves the scaled flux of the reaction
   * @return const C_FLOAT64 & scaledFlux
   */
  const C_FLOAT64 & getParticleFlux() const;

  /**
   * Retrieves whether the reaction is reversible
   * @return bool
   */
  bool isReversible() const;

  /**
   * Add a substrate to the reaction
   * @param std::string & metabKey
   * @param const C_FLOAT64 & multiplicity (Default 1.0)
   * @return bool success
   */
  bool addSubstrate(const std::string & metabKey,
                    const C_FLOAT64 & multiplicity = 1.0);

  /**
   * Add a product to the reaction
   * @param std::string & metabKey
   * @param const C_FLOAT64 & multiplicity (Default 1.0)
   * @return bool success
   */
  bool addProduct(const std::string & metabKey,
                  const C_FLOAT64 & multiplicity = 1.0);

  /**
   * Add a modifier to the reaction
   * @param std::string & metabKey
   * @param const C_FLOAT64 & multiplicity (Default 1.0)
   * @return bool success
   */
  bool addModifier(const std::string & metabKey,
                   const C_FLOAT64 & multiplicity = 1.0);

  /**
   * Sets the rate function of the reaction
   * @param const string & functionName
   * @return bool success
   */
  bool setFunction(const std::string & functionName);

  /**
   * Sets the rate function of the reaction
   * @param CFunction * pFunction
   * @return bool success
   */
  bool setFunction(CFunction * pFunction);

  //****************************************************************************************

  /**
   * Retrieve the index of the given parameter name in the function call. If pType is not
   * NULL the type of the parameter is returned
   * @param const std::string & parameterName
   * @param CFunctionParameter::DataType * pType (default: NULL)
   * @return size_t index;
   */
  size_t getParameterIndex(const std::string & parameterName, CFunctionParameter::DataType * pType = NULL) const;

  /**
   * Sets a parameter value
   * if updateStatus==true the status is also updated to make sure
   * the value is actually used (instead of a global value that may
   * have been used before).
   * if updateStatus==false only the value of the local parameter is
   * set, even if it is not used
   * @param const std::string & parameterName
   * @param const C_FLOAT64 & value
   * @param const bool & updateStatus (default: true(
   */
  void setParameterValue(const std::string & parameterName,
                         const C_FLOAT64 & value,
                         const bool & updateStatus = true);

  /**
   * Retrieves a parameter value
   */
  const C_FLOAT64 & getParameterValue(const std::string & parameterName) const;

  /**
   * Sets a parameter mapping for the indexed parameter.
   * @param const size_t & index
   * @param const std::string & key
   */
  void setParameterMapping(const size_t & index, const std::string & key);

  /**
   * Add a parameter mapping for the indexed parameter.
   * @param const size_t & index
   * @param const std::string & key
   */
  void addParameterMapping(const size_t & index, const std::string & key);

  /**
   * Sets a parameter mapping for the named parameter.
   * @param const std::string & parameterName
   * @param const std::string & key
   * @return bool success
   */
  bool setParameterMapping(const std::string & parameterName, const std::string & key);

  /**
   * Add a parameter mapping for the named parameter.
   * @param const std::string & parameterName
   * @param const std::string & key
   */
  void addParameterMapping(const std::string & parameterName, const std::string & key);

  /**
   * Set the mapping for the name parameter which must be of type vector
   * @param const std::string & parameterName
   * @param const std::vector<std::string> & keys
   */
  void setParameterMappingVector(const std::string & parameterName,
                                 const std::vector<std::string> & keys);

  /**
   * Clear the parameter mapping for the named parameter.
   * @param const size_t & index
   */
  void clearParameterMapping(const std::string & parameterName);

  /**
   * Clear the parameter mapping for the indexed parameter.
   * @param const size_t & index
   */
  void clearParameterMapping(const size_t & index);

  /**
   * Retrieve the mappings of kinetic function parameters.
   */
  const std::vector< std::vector<std::string> > & getParameterMappings() const
  {return mMetabKeyMap;}

  std::vector< std::vector<std::string> > & getParameterMappings()
  {return mMetabKeyMap;}

  const std::vector<std::string> & getParameterMapping(const std::string & parameterName) const;

  /**
   *  Gets the list of kinetic parameter objects of the reaction/function
   */
  const CCopasiParameterGroup & getParameters() const;

  /**
   *  Gets the list of kinetic parameter objects of the reaction/function
   */
  CCopasiParameterGroup & getParameters();

  /**
   * Check whether the indexed parameter is a local parameter.
   * @param const size_t & index
   * @return bool isLocal
   */
  bool isLocalParameter(const size_t & index) const;

  /**
   * Check whether the named parameter is a local parameter.
   * @param const std::string & parameterName
   * @return bool isLocal
   */
  bool isLocalParameter(const std::string & parameterName) const;

  /**
   * We are hiding local reaction parameter which are covered by global quantities.
   * @param const CCopasiObjectName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObject(const CCopasiObjectName & cn) const;

  /**
   *  Gets the description of what parameters the function expects.
   */
  const CFunctionParameters & getFunctionParameters() const;

  /**
   *  Sets whether the reaction is reversible
   *  @param bool reversible
   */
  void setReversible(bool reversible);

  /**
   *  Compile the reaction, i.e., links the metabolites and parameters with the
   *  rate function. The connection of the reaction and the function parameter mapping
   *  to the actual metabolites is established (before compile() the chemical equation
   *  and the reaction only hold the names of the metabolites).
   *  @param "CCopasiVectorNS < CCompartment > &" compartments
   */
  void compile();

  /**
   * Calculate the kinetic function and returns the flux
   * @return const C_FLOAT64 & Flux
   */
  const C_FLOAT64 & calculateFlux();

  /**
   * Calculates the kinetic function and returns the particle flux
   * @return const C_FLOAT64 & ParticleFlux
   */
  const C_FLOAT64 & calculateParticleFlux();

  /**
   * Retrieve object referencing the particle flux
   * @return CCopasiObject * particleFluxReference
   */
  CCopasiObject * getParticleFluxReference();

  /**
   * Retrieve const object referencing the particle flux
   * @return CCopasiObject * particleFluxReference
   */
  const CCopasiObject * getParticleFluxReference() const;

  /**
   * Retrieve object referencing the flux
   * @return CCopasiObject * fluxReference
   */
  CCopasiObject * getFluxReference();

  /**
   * Retrieve const object referencing the flux
   * @return CCopasiObject * fluxReference
   */
  const CCopasiObject * getFluxReference() const;

  /**
   * Retrieve object referencing the propensity
   * @return CCopasiObject * propensityReference
   */
  CCopasiObject * getPropensityReference();

  /**
   * Retrieve the call parameter given to the kinetic function.
   * @return const CCallParameters< C_FLOAT64 > & callParameters
   */
  const CCallParameters< C_FLOAT64 > & getCallParameters() const;

private:
  /**
   * Calculate the kinetic function
   */
  void calculate();

public:
  /**
   * Calculate partial derivative of the flux
   * @param C_FLOAT64 * pXi
   * @param const C_FLOAT64 & derivationFactor
   * @param const C_FLOAT64 & resolution (unscaled resolution)
   * @return C_FLOAT64 partial
   */
  C_FLOAT64 calculatePartialDerivative(C_FLOAT64 * pXi,
                                       const C_FLOAT64 & derivationFactor,
                                       const C_FLOAT64 & resolution);

  /**
   *  Retrieves the number of compartments the reaction is acting in.
   *  @return "size_t" the compartment number
   */
  size_t getCompartmentNumber() const;

  /**
   *  get the largest (smallest) compartment that the reaction touches.
   */
  const CCompartment & getLargestCompartment() const;

  /**
   * Converts an expression tree into a CFunction object
   * and sets the mapping for the reaction.
   */
  bool setFunctionFromExpressionTree(CEvaluationTree* tree,
                                     std::map<CCopasiObject*, SBase*> & copasi2sbmlmap,
                                     CFunctionDB* pFunctionDB);

  /**
   * Converts the function tree into the corresponding expression tree.
   * All variable nodes are replaced by object nodes.
   */
  CEvaluationNode* getExpressionTree();

  /**
   * Sets the SBMLId.
   */
  void setSBMLId(const std::string& id);

  /**
   * Returns a reference to the SBML Id.
   */
  const std::string& getSBMLId() const;

  /**
   * Friend declaration for ostream operator
   * @param std::ostream & os
   * @param const CReaction & d
   * @return std::ostream & os
   */
  friend std::ostream & operator<<(std::ostream & os, const CReaction & d);

  void printDebug() const;

private:

  /**
   * Loads a reaction from a Gepasi file
   */
  C_INT32 loadOld(CReadConfig & configbuffer);

  /**
   * Used for loading Gepasi files. Loads the mapping for one role
   */
  bool loadOneRole(CReadConfig & configbuffer,
                   CFunctionParameter::Role role, C_INT32 n,
                   const std::string & prefix);

  /**
   * Sets the scaling factor of the for the fluxes
   */
  void setScalingFactor();

  void initObjects();

  /**
   * creates the mParamters List of CParameter objects.
   * mMap needs to be initialized before.
   */
  void initializeParameters();

  /**
   * Initializes the mMetabNameMap vectors to the right size.
   */
  void initializeMetaboliteKeyMap();

  /**
   * Replaces all object nodes in an expression tree by variable nodes.
   * The usage term of the variable nodes is recorded in terms
   * of CFunctionParameters that are stored in the replacementMap.
   * On failure a NULL pointer is returned.
   */
  CEvaluationNode* objects2variables(const CEvaluationNode* expression,
                                     std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >& replacementMap,
                                     std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

  /**
   * Converts a single object node to a variable node.
   * The usage term of the variable nodes is recorded in terms
   * of CFunctionParameters that are stored in the replacementMap.
   * On failure a NULL pointer is returned.
   */
  CEvaluationNodeVariable* object2variable(const CEvaluationNodeObject* objectNode,
      std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >& replacementMap,
      std::map<CCopasiObject*, SBase*>& copasi2sbmlmap);

  /**
   * Replaces all variable nodes in a function tree by object nodes.
   * On failure a NULL pointer is returned.
   */
  CEvaluationNode* variables2objects(CEvaluationNode* expression);

  /**
   * Converts a single variable node to an object node.
   * On failure a NULL pointer is returned.
   */
  CEvaluationNodeObject* variable2object(CEvaluationNodeVariable* pVariableNode);

  /**
   * Escapes double quotes and backslashes in a string and puts strings with
   * tabs and spaces in double quotes.
   */
  std::string escapeId(const std::string& id);

  // Attributes
private:
  /**
   *  The default scaling factor of a reaction which is 1.
   */
  static C_FLOAT64 mDefaultScalingFactor;

  /**
   *  The key of the reaction
   */
  std::string mKey;

  /**
   *  The chemical equation
   */
  CChemEq mChemEq;

  /**
   *  A pointer to the rate function of the reaction
   */
  CFunction * mpFunction;

  /**
   *  The flux of the reaction, as amount of substance/time
   */
  C_FLOAT64 mFlux;
  CCopasiObjectReference<C_FLOAT64> *mpFluxReference;

  /**
   *  The scaled flux of the reaction, as particle number/time
   */
  C_FLOAT64 mParticleFlux;
  CCopasiObjectReference<C_FLOAT64> *mpParticleFluxReference;

  /**
   *  The propensity of the reaction
   */
  C_FLOAT64 mPropensity;
  CCopasiObjectReference<C_FLOAT64> *mpPropensityReference;

  /**
   *  A pointer to the scaling factor for the flux to calculate the particle number
   *  changes. For a single compartment reaction this is the volume of
   *  the compartment
   */
  const C_FLOAT64 * mScalingFactor;

  /**
   *  The unit conversion factor
   */
  const C_FLOAT64 * mUnitScalingFactor;

  /**
   *  This describes the mapping of the species and parameters to the function parameters.
   *  Here are the pointers to the actual objects and values.
   */
  CFunctionParameterMap mMap;

  /**
   *  This describes the mapping of the species to the function parameters. Here the
   *  keys of the metabolites (as in the chemical equation) are stored.
   */
  std::vector< std::vector< std::string > > mMetabKeyMap;

  /**
   *  This is a list of parameter objects.
   */
  CCopasiParameterGroup mParameters;

  /**
   * The id of the corresponding reaction in an SBML file.
   * This value is either set upon importing an SBML file,
   * or when the object is first exported to an SBML file.
   */
  std::string mSBMLId;
};

#endif // COPASI_CReaction
