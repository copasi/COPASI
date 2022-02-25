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
#include <map>

#include "copasi/model/CAnnotation.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CChemEq.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/model/CCompartment.h"

#include "copasi/core/CDataVector.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CCallParameters.h"
#include "copasi/function/CFunctionParameters.h"

class CReadConfig;
LIBSBML_CPP_NAMESPACE_BEGIN
class SBase;
LIBSBML_CPP_NAMESPACE_END
class CFunctionDB;

class CReaction : public CDataContainer, public CAnnotation
{
public:
  enum struct KineticLawUnit
  {
    Default,
    AmountPerTime,
    ConcentrationPerTime,
    __SIZE
  };

  static CEnumAnnotation< std::string, KineticLawUnit > KineticLawUnitTypeName;

  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CReaction * pDataObject
   */
  static CReaction * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const;

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CReaction(const std::string & name = "NoName",
            const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CReaction &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CReaction(const CReaction & src,
            const CDataContainer * pParent);

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
  virtual std::string getChildObjectUnits(const CDataObject * pObject) const;

  /**
   * Overload display name. Special treatment for reaction to
   * provide a shorter display
   */
  virtual std::string getObjectDisplayName() const;

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
   * @param const CDataContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CDataContainer * pParent);

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
   * Creates a kinetic function and sets it for the reaction
   * @param const string & infix
   * @return CFunction * pFunction
   */
  CFunction * createFunctionFromExpression(const std::string & infix);

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
   * @param const CFunctionParameter ** ppFunctionParameter (default: NULL)
   * @return size_t index;
   */
  size_t getParameterIndex(const std::string & parameterName,
                           const CFunctionParameter ** ppFunctionParameter = NULL) const;

  /**
   * Sets a parameter value
  * @param const std::string & parameterName
   * @param const C_FLOAT64 & value
   */
  void setParameterValue(const std::string & parameterName,
                         const C_FLOAT64 & value);

  /**
   * Retrieves a parameter value
   */
  const C_FLOAT64 & getParameterValue(const std::string & parameterName) const;

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
   * @param const CCommonName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObject(const CCommonName & cn) const;

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
   *  @return bool success
   */
  CIssue compile();

  /**
   * Retrieve object referencing the particle flux
   * @return CDataObject * particleFluxReference
   */
  CDataObject * getParticleFluxReference();

  /**
   * Retrieve const object referencing the particle flux
   * @return CDataObject * particleFluxReference
   */
  const CDataObject * getParticleFluxReference() const;

  /**
   * Retrieve object referencing the flux
   * @return CDataObject * fluxReference
   */
  CDataObject * getFluxReference();

  /**
   * Retrieve const object referencing the flux
   * @return CDataObject * fluxReference
   */
  const CDataObject * getFluxReference() const;

  /**
   * Retrieve object referencing the particle noise
   * @return const CDataObject * particleNoiseReference
   */
  const CDataObject * getParticleNoiseReference() const;

  /**
   * Retrieve object referencing the noise
   * @return const CDataObject * noiseReference
   */
  const CDataObject * getNoiseReference() const;

  /**
   * Retrieve object referencing the propensity
   * @return CDataObject * propensityReference
   */
  CDataObject * getPropensityReference();

  /**
   * Retrieve object referencing the propensity
   * @return CDataObject * propensityReference
   */
  const CDataObject * getPropensityReference() const;

  /**
   * Retrieve the call parameter given to the kinetic function.
   * @return const CCallParameters< C_FLOAT64 > & callParameters
   */
  const CCallParameters< C_FLOAT64 > & getCallParameters() const;

  /**
   * Retrieve the default expression for the noise.
   * @return std::string expression
   */
  std::string getDefaultNoiseExpression() const;

  /**
   * Set the expression expression for the noise
   * @param const std::string & expression
   * @return bool success
   */
  bool setNoiseExpression(const std::string & expression);

  /**
   * Retrieve the expression for the noise.
   * @return std::string expression
   */
  std::string getNoiseExpression() const;

  /**
   * Set the noise expression for ODE model values
   * @param CExpression*
   * @return bool success
   */
  bool setNoiseExpressionPtr(CExpression* pExpression);

  /**
   * Retrieve the pointer to the expression for ODE model values.
   * @return CExpression*
   */
  const CExpression* getNoiseExpressionPtr() const;

  /**
   * Retrieve the pointer to the expression for ODE model values.
   * @return CExpression*
   */
  CExpression* getNoiseExpressionPtr();

  /**
   * Set whether to add noise to the reaction rate
   * @param const bool & hasNoise
   */
  void setHasNoise(const bool & hasNoise);

  /**
   * Check whether noise is added to the reaction rate
   * @return const bool & hasNoise
   */
  const bool & hasNoise() const;

  /**
   * @return the reaction scheme of this reaction
   */
  std::string getReactionScheme() const;

  /**
   * Initializes this reaction from the specified reaction scheme
   *
   * @param scheme the new reaction scheme to be used
   * @param newFunction a candidate function to be used
   * @param createMetaboliets if true, new metabolites will be created
   * @param createOther if true, additional elements will be created as well
   *
   * @return success / failure
   */
  bool setReactionScheme(const std::string& scheme,
                         const std::string& newFunction = "",
                         bool createMetabolites = true,
                         bool createOther = true);

private:
  /**
   * Calculate the kinetic function
   */
  void calculate();

  CIssue compileFunctionParameters(std::set< const CDataObject * > & Dependencies);

public:
  /**
   *  Retrieves the number of compartments the reaction is acting in.
   *  @return "size_t" the compartment number
   */
  size_t getCompartmentNumber() const;

  /**
   * Retrieve the largest compartment that the reaction touches.
   * This is time dependent it can only be called after update initial values
   * has been called. Note for an empty reaction a NULL pointer is returned.
   * @return const CCompartment * pCompartment
   */
  const CCompartment * getLargestCompartment() const;

  /**
   * Converts an expression tree into a CFunction object
   * and sets the mapping for the reaction.
   */
  CFunction * setFunctionFromExpressionTree(const CExpression & tree,
      std::map<const CDataObject*, SBase*> & copasi2sbmlmap);

  /**
   * Converts the function tree into the corresponding expression tree.
   * All variable nodes are replaced by object nodes.
   */
  CEvaluationNode* getExpressionTree();

  /**
   * Sets the SBMLId.
   */
  void setSBMLId(const std::string& id) const;

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

  const CFunctionParameterMap & getMap() const;

  /**
   * Set whether the reaction is to be treated as fast
   * @param const bool & fast
   */
  void setFast(const bool & fast);

  /**
   * Check whether the reaction needs to be treated as fast
   * @ return const bool & fast
   */
  const bool & isFast() const;

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
  void initializeParameterMapping();

  /**
   * Convert SBML to a valid COPASI infix identifier
   *
   * @param const std::string & id
   * @return std::string
   */
  static std::string sanitizeSBMLId(const std::string & id);

  /**
   * Replaces all object nodes in an expression tree by variable nodes.
   * The usage term of the variable nodes is recorded in terms
   * of CFunctionParameters that are stored in the replacementMap.
   * On failure a NULL pointer is returned.
   */
  CEvaluationNode* objects2variables(const CEvaluationNode* expression,
                                     std::map<std::string, std::pair<CDataObject*, CFunctionParameter*> >& replacementMap,
                                     std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * Converts a single object node to a variable node.
   * The usage term of the variable nodes is recorded in terms
   * of CFunctionParameters that are stored in the replacementMap.
   * On failure a NULL pointer is returned.
   */
  CEvaluationNodeVariable* object2variable(const CEvaluationNodeObject* objectNode,
      std::map<std::string, std::pair<CDataObject*, CFunctionParameter*> >& replacementMap,
      std::map<const CDataObject*, SBase*>& copasi2sbmlmap);

  /**
   * @returns the first non-null CModel from the map or the default one
   */
  const CModel* getFirstCModelOrDefault(std::map< const CDataObject *, SBase * > & copasi2sbmlmap);

  /**
   * @param pModel the model in which to resolve the cn
   * @param cn the common name, primary parts before model will be dropped
   *
   * @return the data object for the given cn
   */
  CDataObject * resolveCN(const CModel* pModel, CCommonName cn);

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

public:
  /**
   * Set the kinetic law unit type;
   * @param const KineticLawUnit & kineticLawUnit
   */
  void setKineticLawUnitType(const KineticLawUnit & kineticLawUnitType);

  /**
   * Retrieve the kinetic law unit type
   * @return const KineticLawUnit & kineticLawUnitType
   */
  const KineticLawUnit & getKineticLawUnitType() const;

  /**
   * Retrieve the effective kinetic law unit type
   * @return KineticLawUnit kineticLawUnitType
   */
  KineticLawUnit getEffectiveKineticLawUnitType() const;

  /**
   * Retrieve the effective kinetic law unit
   * @return std::string kineticLawUnit
   */
  std::string getKineticLawUnit() const;

  /**
   * Set the CN of the compartment used for scaling the kinetic function
   * @param const std::string & compartmentCN
   */
  void setScalingCompartmentCN(const std::string & compartmentCN);

  /**
   * Retrieve the CN of the scaling compartment.
   * @return const CCommonName & scalingCompartmentCN
   */
  const CCommonName & getScalingCompartmentCN() const;

  /**
   * Set the compartment used for scaling the kinetic function
   * @param const CCompartment * pCompartment
   */
  void setScalingCompartment(const CCompartment * pCompartment);

  /**
   * Retrieve the compartment used for scaling the kinetic function
   * @return const CCompartment * scalingCompartment
   */
  const CCompartment * getScalingCompartment() const;

  const std::vector< CRegisteredCommonName > & getParameterCNs(const size_t & index) const;

  const std::vector< CRegisteredCommonName > & getParameterCNs(const std::string & name) const;

  const std::vector< std::vector< CRegisteredCommonName > > & getParameterCNs() const;

  bool setParameterCNs(const size_t & index, const std::vector< CRegisteredCommonName >& CNs);

  bool setParameterCNs(const std::string & name, const std::vector< CRegisteredCommonName> & CNs);

  const std::vector< const CDataObject * > & getParameterObjects(const size_t & index) const;

  const std::vector< const CDataObject * > & getParameterObjects(const std::string & name) const;

  const std::vector< std::vector< const CDataObject * > > & getParameterObjects() const;

  bool setParameterObjects(const size_t & index, const std::vector< const CDataObject * >& objects);

  bool setParameterObjects(const std::string & name, const std::vector< const CDataObject * >& objects);

  bool setParameterObject(const size_t & index, const CDataObject * object);

  bool setParameterObject(const std::string & name, const CDataObject * object);

  bool addParameterObject(const size_t & index, const CDataObject * object);

  bool addParameterObject(const std::string & name, const CDataObject * object);

  // Attributes
private:
  /**
   *  The chemical equation
   */
  CChemEq mChemEq;

  /**
   *  A pointer to the rate function of the reaction
   */
  CFunction * mpFunction;

  /**
   * Optional noise term
   */
  CExpression * mpNoiseExpression;

  /**
   * A Boolean flag indicating whether to add noise to the reaction
   */
  bool mHasNoise;

  /**
   *  The flux of the reaction, as amount of substance/time
   */
  C_FLOAT64 mFlux;
  CDataObjectReference<C_FLOAT64> *mpFluxReference;

  /**
   *  The scaled flux of the reaction, as particle number/time
   */
  C_FLOAT64 mParticleFlux;
  CDataObjectReference<C_FLOAT64> *mpParticleFluxReference;

  /**
   *  The noise of the reaction
   */
  C_FLOAT64 mNoise;
  CDataObjectReference<C_FLOAT64> *mpNoiseReference;

  /**
   *  The particle noise
   */
  C_FLOAT64 mParticleNoise;
  CDataObjectReference<C_FLOAT64> *mpParticleNoiseReference;

  /**
   *  The propensity of the reaction
   */
  C_FLOAT64 mPropensity;
  CDataObjectReference<C_FLOAT64> *mpPropensityReference;

  /**
   *  This describes the mapping of the species and parameters to the function parameters.
   *  Here are the pointers to the actual objects and values.
   */
  CFunctionParameterMap mMap;

  /**
   *  This describes the mapping of the species to the function parameters. Here the
   *  keys of the metabolites (as in the chemical equation) are stored.
   */
  // std::vector< std::vector< std::string > > mMetabKeyMap;

  std::map< std::string, size_t > mParameterNameToIndex;
  std::vector< std::vector< CRegisteredCommonName > > mParameterIndexToCNs;
  std::vector< std::vector< const CDataObject * > > mParameterIndexToObjects;

  /**
   *  This is a list of parameter objects.
   */
  CCopasiParameterGroup mParameters;

  /**
   * The id of the corresponding reaction in an SBML file.
   * This value is either set upon importing an SBML file,
   * or when the object is first exported to an SBML file.
   */
  mutable std::string mSBMLId;

  /**
   * This flag indicates whether the reaction is treated as fast. The interpretation of fast
   * is up to to the integration algorithm.
   */
  bool mFast;

  /**
   * This indicates what the units of the kinetic law are
   */
  KineticLawUnit mKineticLawUnit;

  /**
   *
   */
  CRegisteredCommonName mScalingCompartmentCN;

  /**
   *
   */
  const CCompartment * mpScalingCompartment;
};

#endif // COPASI_CReaction
