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

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CChemEq class.
 *  Describing a chemical equation.
 *  The CChemEq class handles everything a reaction has to do with metabolites.
 *
 *  Created for COPASI by Stefan Hoops 2001
 */

#ifndef COPASI_CChemEq
#define COPASI_CChemEq

#include <string>

#include "copasi/model/CChemEqElement.h"
#include "copasi/core/CDataVector.h"

class CCompartment;

class CChemEq : public CDataContainer
{
public:
  enum MetaboliteRole
  {
    PRODUCT = 0,
    SUBSTRATE,
    MODIFIER,
    NOROLE
  };

  // Operations
public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CChemEq(const std::string & name = "NoName",
          const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CChemEq &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CChemEq(const CChemEq & src,
          const CDataContainer * pParent);

  /**
   *  Destructor
   */
  virtual ~CChemEq();

  /**
   *  Cleanup
   */
  void cleanup();

  /**
   * Set the reversibility of the of the equation
   * @param const bool & const bool & reversible
   */
  void setReversibility(const bool & reversible);

  /**
   * Retrieve the reversibility of the equation
   * @return const bool & reversible
   */
  const bool & getReversibility() const;

  /**
   * Add a species to the equation
   * @param const std::string & speciesKey
   * @param const C_FLOAT64 & multiplicity
   * @param const MetaboliteRole & role
   * @return bool success
   */
  bool addMetabolite(const std::string & key, const C_FLOAT64 multiplicity, const MetaboliteRole & role);

  /**
   * Retrieves the vector of substrates and their multiplicity
   * in the chemical reaction.
   * @return "vector < CChemEqElement * > &" substrates
   */
  const CDataVector < CChemEqElement > & getSubstrates() const;

  /**
   * Retrieves the vector of products and their multiplicity
   * in the chemical reaction.
   * @return "vector < CChemEqElement * > &" products
   */
  const CDataVector < CChemEqElement > & getProducts() const;

  /**
   * Retrieves the vector of Modifiers and their multiplicity
   */
  const CDataVector < CChemEqElement > & getModifiers() const;

  /**
   * Retrieves the vector of metabolites and their total balance
   * in the chemical reaction.
   * @return "vector < CChemEqElement * > &" balances
   */
  const CDataVector < CChemEqElement > & getBalances() const;

  /**
   * Returns the number of compartments the chemical equation is associated
   * with.
   */
  size_t getCompartmentNumber() const;

  /**
   * Retrieves a set of the compartments.
   */
  std::set< const CCompartment * > getCompartments() const;

  /**
   * Retrieve the largest compartment that the reaction touches.
   * This is time dependent it can only be called after update initial values
   * has been called. Note for an empty reaction a NULL pointer is returned.
   * @return const CCompartment * pCompartment
   */
  const CCompartment * getLargestCompartment() const;

  /**
   *  Checks if it is possible to figure out a compartment from the
   *  information in the chemical equation. If there are substrates and if
   *  all the substrates are in the same compartment this compartment will be
   *  returned. If there are no substrates and there are Products and all Products are in the
   *  same compartment this compartment will be returned, else an exception
   *  will be thrown.
   */
  //const CCompartment* CheckAndGetFunctionCompartment() const;

  /**
   *  This returns the sum of the multiplicities
   */
  size_t getMolecularity(const MetaboliteRole role) const;

  /**
   * Sets the stoichiometry of the chemical element that corresponds to the
   * given metabolite and role to the new value.
   * The role has to be either CChemEqElement::SUBSTRATE or
   * CChemEqElement::PRODUCT.
   * If the role is invalid, the multiplicity is negative or zero  or if the element for
   * the metabolite and role can not be found in the chemical equation, false is returned and
   * nothing is changed.
   */
  bool setMultiplicity(const CMetab* pMetab, C_FLOAT64 newMult, MetaboliteRole role);

private:

  /**
   *  Adds an element to the vector given by structure. The element is
   *  either SUBSTRATE or PRODUCT.
   *  @param "CDataVector < CChemEqElement > &" structure
   *  @param "const CChemEqElement &" element
   *  @param "CChemEq::MetaboliteRole" role (
   */
  void addElement(CDataVector < CChemEqElement > & structure,
                  const CChemEqElement & element,
                  CChemEq::MetaboliteRole role = CChemEq::PRODUCT);

  /**
   * Friend declaration for ostream operator
   * @param std::ostream & os
   * @param const CChemEq & d
   * @return std::ostream & os
   */
  friend std::ostream & operator<<(std::ostream & os, const CChemEq & d);

  // Attributes
private:
  /**
   * Indicates whether the chemical equation is reversible
   */
  bool mReversible;

  /**
   * A vector of substrates and their multiplicity in the chemical reaction
   * @supplierCardinality 0..*
   * @label Substrates
   */
  CDataVector < CChemEqElement > mSubstrates;

  /**
   * A vector of products and their multiplicity in the chemical reaction
   * @supplierCardinality 0..*
   * @label Products
   */
  CDataVector < CChemEqElement > mProducts;

  /**
   * A vector of modifiers in the chemical reaction.
   */
  CDataVector < CChemEqElement > mModifiers;

  /**
   * A vector of metabolites and their total balance in the chemical reaction
   * @supplierCardinality 0..*
   * @label Stoichiometry
   */
  CDataVector < CChemEqElement > mBalances;
};

#endif // COPASI_CChemEq
