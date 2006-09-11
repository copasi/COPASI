/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEq.h,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/11 14:24:13 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CChemEq class.
 *  Describing a chemical equation.
 *  The CChemEq class handles everything a reaction has to do with metabolites.
 *
 *  Created for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CChemEq
#define COPASI_CChemEq

#include <string>

#include "CChemEqElement.h"
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

    // Attributes

  private:
    /**
     * Indicates whether the chemical equation is reversible
     */
    bool mReversible;

    /**
     *  A vector of substrates and their multiplicity in the chemical reaction
     * @supplierCardinality 0..*
     * @label Substrates
     */
    CCopasiVector < CChemEqElement > mSubstrates;

    /**
     *  A vector of products and their multiplicity in the chemical reaction
     * @supplierCardinality 0..*
     * @label Products
     */
    CCopasiVector < CChemEqElement > mProducts;

    /**
     *  A vector of modifiers in the chemical reaction.
     */
    CCopasiVector < CChemEqElement > mModifiers;

    /**
     *  A vector of metabolites and their total balance in the chemical reaction
     * @supplierCardinality 0..*
     * @label Stoichiometry
     */
    CCopasiVector < CChemEqElement > mBalances;

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

    void setReversibility(bool revers) {mReversible = revers;}
    bool getReversibility() const {return mReversible;}

    bool addMetabolite(const std::string & key, const C_FLOAT64 mult, const MetaboliteRole role);

    /**
     *  Retrieves the vector of substrates and their multiplicity
     *  in the chemical reaction.
     *  @return "vector < CChemEqElement * > &" substrates
     */
    const CCopasiVector < CChemEqElement > & getSubstrates() const;

    /**
     *  Retrieves the vector of products and their multiplicity
     *  in the chemical reaction.
     *  @return "vector < CChemEqElement * > &" products
     */
    const CCopasiVector < CChemEqElement > & getProducts() const;

    /**
     *  Retrieves the vector of Modifiers and their multiplicity
     */
    const CCopasiVector < CChemEqElement > & getModifiers() const;

    /**
     *  Retrieves the vector of metabolites and their total balance
     *  in the chemical reaction.
     *  @return "vector < CChemEqElement * > &" balances
     */
    const CCopasiVector < CChemEqElement > & getBalances() const;

    /**
     * Returns the number of comparments the chemical equation is associated
     * with.
     */
    unsigned C_INT32 getCompartmentNumber() const;

    /**
     *  get the largest (smallest) compartment that the reaction touches.
     */
    const CCompartment & getLargestCompartment() const;
    const CCompartment & getSmallestCompartment() const;

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
     *  exchanges products and substrates
     */
    void reverse();

    /**
     *  This returns the sum of the multiplicities
     */
    C_INT32 getMolecularity(const MetaboliteRole role) const;

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

    friend std::ostream & operator<<(std::ostream &os, const CChemEq & d);
  };

#endif // COPASI_CChemEq
