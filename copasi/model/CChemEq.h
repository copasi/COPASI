/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEq.h,v $
   $Revision: 1.32 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/04 20:30:05 $
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
     * The chemical equation 
     */ 
    //std::string mChemicalEquation;

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

    /**
     *  calls compile() for all ChemEqElements
     *  @param "CCopasiVectorN < CCompartment > &" compartments
     */
    void compile(const CCopasiVectorN < CCompartment > & compartments);

    /**
     *  Set the chemical equation
     *  @param "const string &" chemicalEquation (in any form even mixed)
    *  @return "bool" returns reversibility of reaction (TRUE if reversible)
     */ 
    //bool setChemicalEquation(const std::string & chemicalEquation, const CModel & model);

    void setReversibility(bool revers) {mReversible = revers;}
    bool getReversibility() const {return mReversible;}

    /**
     *  Retrieves the chemical equation with multipliers.
     *  @return "const string" ChemicalEquation
     */ 
    //const std::string getChemicalEquation() const;

    /**
     *  Retrieves the converted form of chemical equation.
     *  This does not contain any multipliers.
     *  @return "const string" ChemicalEquationConverted
     */ 
    //const std::string getChemicalEquationConverted() const;

    /**
     * Add a substrate, product, or modifier by name. 
     * The Metabolite need not exist
     * @param const std::string & name
     * @param const C_FLOAT64 mult
     * @param const MetaboliteRole role
     */ 
    //void addMetaboliteByName(const std::string & name, const C_FLOAT64 mult, const MetaboliteRole role);

    /**
     * Add a substrate, product, or modifier. 
     * @param CMetab & metab
     * @param const C_FLOAT64 mult
     * @param const MetaboliteRole role
     * @return bool success
     */ 
    //bool addMetabolite(CMetab * pMetab, const C_FLOAT64 mult, const MetaboliteRole role);
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
     *  Find an element by its metabolite name. if role=NOROLE (default) all three list are
     *  searched. If the chemical equation was compiled before this is the way to get a
     *  pointer to a metabolite from its name.
     */ 
    //const CChemEqElement & findElementByName(const std::string & name,
    //    const MetaboliteRole role = NOROLE) const;

    //const getExpandedMetaboliteList

    /**
     *  Returns true if a chemical equation has already been set
     */ 
    //bool initialized() const;

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
     *  Extracts the next element of the input string starting at position pos.
     *  @param "const string &" input (string to parse)
     *  @param "string::size_type &" pos 
     *              (on input:  starting position of the parse)
     *              (on output: starting position for the next parse)
     *  @return "CChemEqElement" element
     */
    /*CChemEqElement extractElement(const std::string & input,
                                  std::string::size_type & pos,
                                  const CModel & model) const;
    CChemEqElement extractModifier(const std::string & input,
                                   std::string::size_type & pos,
                                   const CModel & model) const;*/

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
     *  This is the called by setSubstrates, setProducts, and setBalances.
     *  It realy does the work.
     *  @param "CCopasiVector < CChemEqElement > &" elements
     *  @param "const string &" reaction
     *  @param "CChemEq::MetaboliteRole" role (default: CChemEq::PRODUCT
     */
    /*void setChemEqElements(const CModel & model,
                           CCopasiVector < CChemEqElement > & elements,
                           const std::string & reaction,
                           CChemEq::MetaboliteRole role = CChemEq::PRODUCT,
                           const bool modif = false);*/

    /**
     *  Compile the ChemEqElement, i.e., the pointer to the metabolite
     *  is assigned.
     *  @param "vector < CChemEqElement * > &" elements
     *  @param "vector < CMetab * > &" metabolites
     */ 
    //void compileChemEqElements(CCopasiVector < CChemEqElement > & elements,
    //                           const CCopasiVectorN < CCompartment > & compartments);

    /**
     *  This function frees a vector of CChemEqElement
     *  @param "vector < CChemEqElement * > &" elements
     */ 
    //void cleanupChemEqElements(std::vector < CChemEqElement * > & elements);

    /**
     *  This function splits the chemical equation into a left and a right
     *  @param "string &" left (substrate side)
     *  @param "string &" right (product side)
     *  @return "bool" returns reversibility of reaction (TRUE if reversible)
     */ 
    //bool splitChemEq(const std::string & input,
    //                 std::string & left, std::string & right, std::string & mod) const;

    friend std::ostream & operator<<(std::ostream &os, const CChemEq & d);
  };

#endif // COPASI_CChemEq
