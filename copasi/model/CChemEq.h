/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEq.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:57 $
   End CVS Header */

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

/** @dia:pos 52.1128,98.3144 */
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
    /** @dia:route 3,17; h,52.1128,99.0144,46.5733,102.331,41.0337 */
    CCopasiVector < CChemEqElement > mSubstrates;

    /**
     *  A vector of products and their multiplicity in the chemical reaction
     * @supplierCardinality 0..*
     * @label Products
     */
    /** @dia:route 3,21; h,52.1128,99.0144,46.5733,103.931,41.0337 */
    CCopasiVector < CChemEqElement > mProducts;

    /**
     *  A vector of modifiers in the chemical reaction. 
     */
    /** @dia:route 3,13; h,52.1128,99.0144,46.5733,100.731,41.0337 */
    CCopasiVector < CChemEqElement > mModifiers;

    /**
     *  A vector of metabolites and their total balance in the chemical reaction
     * @supplierCardinality 0..*
     * @label Stoichiometry
     */
    /** @dia:route 3,25; h,52.1128,99.0144,46.5733,105.531,41.0337 */
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
     *  Checks if it is possible to figure out a compartment from the
     *  information in the chemical equation. If there are substrates and if
     *  all the substrates are in the same compartment this compartment will be
     *  returned. If there are no substrates and there are Products and all Products are in the
     *  same compartment this compartment will be returned, else an exception
     *  will be thrown.
     */
    const CCompartment* CheckAndGetFunctionCompartment() const;

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
