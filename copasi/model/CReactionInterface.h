// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CREACTIONINTERFACE_H
#define CREACTIONINTERFACE_H

#include <vector>
#include <string>
#include "copasi/copasi.h"
//#include "copasi/model/CChemEq.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CChemEqInterface.h"
#include "copasi/function/CFunction.h"

//class CFunction;
class CModel;
class CReaction;
class CUndoData;

/**
 * This class provides an interface for dealing with reactions.
 * For representing the parameter mappings it uses object names.
 * A CReactionInterface allows editing a reaction while trying to
 * keep everything consistent.
 *
 * Note: Many of the methods need to be provided with a model.
 * While handling of the metabolites is completely independent of the
 * model (they are handled by name, and they don't need to exist),
 * the mapping of Compartments and global parameters is done with
 * the entities that exist in the model. This may seem inconsistent,
 * but the idea is that metabolites can be created from the gui by entering
 * them into the reaction equation. Compartments and global parameters
 * can only be chosen from the list of existing objects.
 */
class CReactionInterface
{
private:
  const CReaction * mpReaction;

  mutable const CModel * mpModel;

  /**
   * A copy of the chemical equation of the reaction
   */
  CChemEqInterface mChemEqI;

  /**
   * A pointer to the kinetic function of the reaction
   */
  const CFunction* mpFunction;
  mutable CFunction mMassAction;

  /**
   * A pointer of the function parameters
   */
  const CFunctionParameters * mpFunctionParameters;

  CCopasiParameterGroup mLocalParameters;

  /**
   * what metabolite for what function parameter
   */
  std::map< std::string, std::vector< std::string > > mNameMap;
  std::vector< std::vector< std::string > * > mIndexMap;

  /**
   * values of the kinetic parameters
   */
  std::vector< C_FLOAT64 > mValues;

  /**
   * values of the kinetic parameters
   */
  std::vector<bool> mIsLocal;

  bool mHasNoise;

  std::string mNoiseExpression;
  CReaction::KineticLawUnit mKineticLawUnitType;

  std::string mScalingCompartment;

public:
  CReactionInterface();

  ~CReactionInterface();

  /**
   * set a new chemical equation.
   * newFunction suggests a new kinetic function which is only used if adequate.
   */
  void setChemEqString(const std::string & eq, const std::string & newFunction);

  /**
   * internal function that temporarily removes the equation
   */
  void clearChemEquation();

  std::string getChemEqString() const;

  const CChemEqInterface & getChemEqInterface() const;

  bool isReversible() const;

  /**
   * this method tries to find out if the REACTION involves several compartments
   * It only takes into account the metabolites that
   * actually exist in the model. A non existing metabolite is assumed
   * not to be in a different compartment
   */
  bool isMulticompartment() const;

  /**
   * set the reversibility.
   * newFunction suggests a new kinetic function which is only used if adequate.
   */
  void setReversibility(bool rev, const std::string & newFunction);

  /**
   * reverse the reaction and set the reversibility.
   * newFunction suggests a new kinetic function which is only used if adequate.
   */
  void reverse(bool rev, const std::string & newFunction);

  /**
   * This produces a list of metabolite names (from the chem eq) for use in
   * the combo boxes. The role must be given like a usage, e.g. "SUBSTRATE".
   */
  const std::vector<std::string> & getListOfMetabs(CFunctionParameter::Role role) const;

  /**
   * set the function. an empty mapping is created
   */
  void setFunctionWithEmptyMapping(const std::string & fn);

  /**
   * set the function.
   * a new mapping is created that tries to preserve as much information as
   * possible from the old mapping. Then a default mapping is set from
   * the chemical equation and the model (if possible).
   */
  void setFunctionAndDoMapping(const std::string & fn);

  /**
   * @return the function name
   */
  std::string getFunctionName() const;

  /**
  * @return the function description
  */
  std::string getFunctionDescription() const;

  /**
   * @return the function
   */
  const CFunction & getFunction() const;

  /**
   * @return a vector of possible functions for the specified number substrates / products and reversibility
   */
  std::vector< std::string > getListOfPossibleFunctions() const;

  /**
   * @return number of function parameter
   */
  size_t size() const;

  /**
   * Tests whether the parameter at the given index is of type vector
   *
   * @param index the index
   * @return true, if the function parameter at the given index is a vector false otherwise
   */
  bool isVector(size_t index) const;

  /**
   * returns the function parameter role for the parameter with given index
   *
   * @param index the index
   * @return the role of that function parameter
   */
  CFunctionParameter::Role getUsage(size_t index) const;

  /**
   * Returns the name of the parameter with given index
   *
   * @param index the index
   * @return the name of the parameter if found, or an empty string
   */

  std::string getParameterName(size_t index) const;

  /**
   * Sets the mapping of the parameter with given index
   *
   * @param index the index
   * @param mn the mapping
   */
  void setMapping(size_t index, std::string mn);

  /**
   * returns all mappings for the given index
   *
   * @param index the index
   * @return the string vector of all mappings for the given index
   */

  const std::vector< std::string > & getMappings(size_t index) const;

  /**
   * return the first mapping for the given index
   *
   * @param index the index
   * @return the first mapping for the given index
   */
  const std::string & getMapping(size_t index) const;

  std::vector< std::string > getUnitVector(size_t index) const;

  std::string getUnit(size_t index) const;

  /**
   * Specifies that the parameter with given index should be a local
   * parameter and specifies the value

   *
   * @param index the index of the parameter
   * @param value the new value of the parameter
   */
  void setLocalValue(size_t index, C_FLOAT64 value);

  /**
   * Specified that the parameter with given index should be a local parameter
   *
   * @param index the index
   */
  void setLocal(size_t index);

  /**
   * Return the local parameter value of the parameter with given index
   *
   * @param index the index of the parameter
   *
   * @return the value of the parameter with given index
   */
  const C_FLOAT64 & getLocalValue(size_t index) const;

  /**
   * tests whether the parameter with given index is a local parameter
   *
   * @param index the index
   * @return true, if the parameter with given index is local, false otherwise
   */
  bool isLocalValue(size_t index) const;

  /*
   *  associate the function parameter referenced by "index" with the global
   *  parameter named pn. Only valid if the role for this function parameter is "PARAMETER".
   *  returns success
   */
  //bool setGlobalParameter(size_t index, std::string pn);

  //const std::string & getGlobalParameter(size_t index) const;

  //bool setCompartment(size_t index, std::string pn);

  //const std::string & getCompartment(size_t index) const;

  void init(const CReaction & reaction);

  /**
   * writes the information back to a CReaction.
   * createMetabolites() and createOtherObjects() should be called before.
   * @param bool compile (default: true)
   */
  bool writeBackToReaction(CReaction * rea = NULL, bool compile = true);

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param const CCore::Framework & framework
   * @return CUndoData undoData
   */
  CUndoData createUndoData(const CCore::Framework & framework) const;

  /**
   * create all metabolites that are needed by the reaction but do
   * not exist in the model yet.
   */
  bool createMetabolites();

  /**
   * create all metabolites that are needed by the reaction but do
   * not exist in the model yet.
   *
   * @param createdKeys vector, that will be filled with the keys
   *        of created elements
   *
   * @return true in case elements were created, false otherwise
   */
  bool createMetabolites(std::vector<std::string>& createdKeys);

  /**
   * create all other objects that are needed by the reaction but do
   * not exist in the model yet.
   */
  bool createOtherObjects() const;

  /**
   * @brief createOtherObjects
   *
   * @param createdKeys vector that will be filled with created keys
   *
   * @return true, in case elements were created, false otherwise
   */
  bool createOtherObjects(std::vector<std::string>& createdKeys) const;

  /**
   * @return boolean indicating whether this reaction is valid
   */
  bool isValid() const;

  /**
   * Is the mapping of this parameter locked?
   * The behavior of this method is different for different roles:
   * SUBSTRATE, PRODUCT: according to the chemical equation
   * MODIFIER: always unlocked
   * TIME: always locked
   * VOLUME, PARAMETER: according to the model
   *
   * The idea is that in the reaction GUI new species can be entered
   * in the chemical equation that are then created automatically.
   * Compartments and global parameters can only be chosen from those
   * existing in the model.
   *
   * @param index the index of the parameter
   * @return boolean indicating whether the parameter is locked or not
   */
  bool isLocked(size_t index) const;

  /**
   * Is the mapping of this parameter locked?
   * The behavior of this method is different for different roles:
   * SUBSTRATE, PRODUCT: according to the chemical equation
   * MODIFIER: always unlocked
   * TIME: always locked
   * VOLUME, PARAMETER: according to the model
   *
   * The idea is that in the reaction GUI new species can be entered
   * in the chemical equation that are then created automatically.
   * Compartments and global parameters can only be chosen from those
   * existing in the model.
   *
   * @param usage the usage of the parameter
   * @return boolean indicating whether the parameter with given usage should be locked
   */
  bool isLocked(CFunctionParameter::Role usage) const;

  /**
   * Retrieve the list of parameters which will be deleted
   * @return std::set< const CDataObject * > DeletedParameters
   */
  std::set< const CDataObject * > getDeletedParameters() const;

  /**
   * Sets the kinetic law unit type
   * @param kineticLawUnitType the type to set
   */
  void setKineticLawUnitType(const CReaction::KineticLawUnit & kineticLawUnitType);

  /**
   * @return the currently set unit type
   */
  const CReaction::KineticLawUnit & getKineticLawUnitType() const;

  /**
   * @return the effective unit type in case the default is selected
   */
  CReaction::KineticLawUnit getEffectiveKineticLawUnitType() const;

  /**
   * @return the concentration rate unit display name
   */
  std::string getConcentrationRateUnit() const;

  /**
   * @return the amount rate unit display name
   */
  std::string getAmountRateUnit() const;

  /**
   * @return the effective kinetic law unit
   */
  std::string getEffectiveKineticLawUnit() const;

  /**
   * Sets the scaling compartment to be used for this reaction
   * @param scalingCompartment
   */
  void setScalingCompartment(const std::string & scalingCompartment);

  /**
   * @return the specified scaling compartment
   */
  const std::string & getScalingCompartment() const;

  /**
   * @return the default scaling compartment
   */
  std::string getDefaultScalingCompartment() const;

#ifdef COPASI_DEBUG
  void printDebug() const;
#endif // COPASI_DEBUG

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
   * Set the expression for non FIXED model values
   * @param const std::string & expression
   * @return bool success
   */
  bool setNoiseExpression(const std::string & expression);

  /**
   * Retrieve the expression for non FIXED model values.
   * @return const std::string &  expression
   */
  const std::string &  getNoiseExpression() const;

private:

  /**
   * initialize mapping (resize vectors and set names to "unknown").
   * Also initializes mpParameters but doesn't delete the old mpParameters.
   */
  void initMapping();

  /**
   * create new mapping, try to keep as much information from the current
   * mapping. Calls initMapping().
   */
  void copyMapping();

  /**
   * guesses how to connect metabs with parameters for a specific usage
   */
  void connectFromScratch(CFunctionParameter::Role role);

  /**
   * tries to determine the mapping for PARAMETER, VOLUME, TIME
   * only if the current mapping is "unknown".
   * Is typically called after initMapping() and copyMapping()
   */
  void connectNonMetabolites();

  /**
   * updates the modifiers in the chemical equation according to
   * the parameter mapping
   */
  void updateModifiersInChemEq();

  /**
   * checks if newFunction is an valid function for the reaction.
   * If it is not or if newFunction="" another function is chosen.
   */
  void findAndSetFunction(const std::string & newFunction);

  /**
   * returns a list of metabolites (from the chemical equation). Species can occur
   * several times according to the multiplicity
   */
  std::vector<std::string> getExpandedMetabList(CFunctionParameter::Role role) const;

  /**
   * Loads mapping and values from the specified reaction
   * @return true if successful, false otherwise
   */
  bool loadMappingAndValues();
};

#endif
