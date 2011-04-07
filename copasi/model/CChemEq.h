/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEq.h,v $
 $Revision: 1.42 $
 $Name:  $
 $Author: shoops $
 $Date: 2011/04/07 12:27:19 $
 End CVS Header */

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
 *  CChemEq class.
 *  Describing a chemical equation.
 *  The CChemEq class handles everything a reaction has to do with metabolites.
 *
 *  Created for COPASI by Stefan Hoops 2001
 */

#ifndef COPASI_CChemEq
#define COPASI_CChemEq

#include <string>

#include "model/CChemEqElement.h"
#include "utilities/CCopasiVector.h"

class CCompartment;

class CChemEq : public CCopasiContainer
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
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CChemEq(const std::string & name = "NoName",
          const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CChemEq &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CChemEq(const CChemEq & src,
          const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor
   */
  ~CChemEq();

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
  const CCopasiVector < CChemEqElement > & getSubstrates() const;

  /**
   * Retrieves the vector of products and their multiplicity
   * in the chemical reaction.
   * @return "vector < CChemEqElement * > &" products
   */
  const CCopasiVector < CChemEqElement > & getProducts() const;

  /**
   * Retrieves the vector of Modifiers and their multiplicity
   */
  const CCopasiVector < CChemEqElement > & getModifiers() const;

  /**
   * Retrieves the vector of metabolites and their total balance
   * in the chemical reaction.
   * @return "vector < CChemEqElement * > &" balances
   */
  const CCopasiVector < CChemEqElement > & getBalances() const;

  /**
   * Returns the number of compartments the chemical equation is associated
   * with.
   */
  size_t getCompartmentNumber() const;

  /**
   * Retrieve the largest compartment that the reaction touches.
   * @return const CCompartment & compartment
   */
  const CCompartment & getLargestCompartment() const;

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
   *  @param "CCopasiVector < CChemEqElement > &" structure
   *  @param "const CChemEqElement &" element
   *  @param "CChemEq::MetaboliteRole" role (
   */
  void addElement(CCopasiVector < CChemEqElement > & structure,
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
  CCopasiVector < CChemEqElement > mSubstrates;

  /**
   * A vector of products and their multiplicity in the chemical reaction
   * @supplierCardinality 0..*
   * @label Products
   */
  CCopasiVector < CChemEqElement > mProducts;

  /**
   * A vector of modifiers in the chemical reaction.
   */
  CCopasiVector < CChemEqElement > mModifiers;

  /**
   * A vector of metabolites and their total balance in the chemical reaction
   * @supplierCardinality 0..*
   * @label Stoichiometry
   */
  CCopasiVector < CChemEqElement > mBalances;
};

#endif // COPASI_CChemEq
