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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCHEMEQINTERFACE_H
#define CCHEMEQINTERFACE_H

#include <string>
#include <vector>
#include <set>

#include "copasi/function/CFunctionParameter.h"

class CChemEq;
class CModel;
class CReaction;
class CCompartment;

/**
 * This class describes a chemical equation based on metabolite names
 * It supports parsing and generating string representations.
 * Note that this class handles only metab names without caring about whether
 * these metabs exist in the model. There is however a method to create
 * the missing metabs.
 */
class CChemEqInterface
{
private:
  const CChemEq * mpChemEq;
  mutable CModel * mpModel;

  std::vector< std::string > mSubstrateNames;
  std::vector< std::string > mProductNames;
  std::vector< std::string > mModifierNames;

  std::vector< C_FLOAT64 > mSubstrateMult;
  std::vector< C_FLOAT64 > mProductMult;
  std::vector< C_FLOAT64 > mModifierMult;

  std::vector< std::string > mSubstrateCompartments;
  std::vector< std::string > mProductCompartments;
  std::vector< std::string > mModifierCompartments;

  std::vector< std::string > mSubstrateDisplayNames;
  std::vector< std::string > mProductDisplayNames;
  std::vector< std::string > mModifierDisplayNames;

  bool mReversibility;

public:
  CChemEqInterface();

  ~CChemEqInterface();

  bool init(const CChemEq & ce);

  std::string getChemEqString(bool expanded) const;

  bool setChemEqString(const std::string & ces);

  bool writeToChemEq(CChemEq * pChemEq = NULL) const;

  std::string toDataValue() const;
  bool fromDataValue(const std::string & dataValue);

  const std::vector<C_FLOAT64> & getListOfMultiplicities(CFunctionParameter::Role role) const;

  const std::vector<std::string> & getListOfSpecies(CFunctionParameter::Role role) const;

  const std::vector<std::string> & getListOfCompartments(CFunctionParameter::Role role) const;

  const std::vector<std::string> & getListOfDisplayNames(CFunctionParameter::Role role) const;

  std::pair< std::string, std::string > displayNameToNamePair(CFunctionParameter::Role role, const std::string displayName) const;
  /**
   * add a modifier to the chemical equation. It is only added if it is not already in there.
   */
  void addModifier(const std::string & name);

  void clearModifiers();

  void clearAll();

  bool getReversibility() const;

  void setReversibility(bool rev);

  /**
   * this method tries to find out if the chemical equation involves several compartments
   * in a given model. It only takes into account the metabs that
   * actually exist in the model. A non existing metabolite is assumed
   * not to be in a different compartment
   */
  bool isMulticompartment() const;

  /**
   * convenience method. If the reaction is single compartment the
   * compartment is returned, else NULL.
   */
  const CCompartment * getCompartment() const;

  std::string getDefaultCompartment() const;

  std::set< std::string > getCompartments() const;

  void reverse();

  size_t getMolecularity(CFunctionParameter::Role role) const;

  std::set<std::string> listOfNonUniqueMetabNames() const;

  std::set< std::pair< std::string, std::string > > listOfNonExistingMetabNames() const;

  /**
   * creates all necessary metabolites (and volumes)
   *
   * @param createdKeys this vector will be filled with keys of
   *        created elements
   *
   * @return true, in case some elements were created, false otherwise
   */
  bool createNonExistingMetabs(std::vector<std::string> &createdKeys);

  //convenience methods:
  static std::string getChemEqString(const CReaction & rea, bool expanded);
  static bool setChemEqFromString(CReaction & rea, const std::string & ces);

  static bool isValidEq(const std::string & eq);

private:

  void buildDisplayNames();

  void completeCompartments();

  static std::string writeElement(const std::string & name, C_FLOAT64 mult, bool expanded);
};

#endif
