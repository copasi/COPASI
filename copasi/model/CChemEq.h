/**
 *  CChemEq class.
 *  Describing a chemical equation Stefan Hoops 2001
 *
 *  Created for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CChemEq
#define COPASI_CChemEq

#include <string>

#include "CChemEqElement.h"

class CChemEq
  {
  public:
    enum MetaboliteRole
    {
      PRODUCT = 0,
      SUBSTRATE
    };

    // Attributes

  private:
    /**
     *  The chemical equation with multipliers
     */
    string mChemicalEquation;

    /**
     *  The chemical equation without multipliers
     */
    string mChemicalEquationConverted;

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
     *  A vector of metabolites and their total balance in the chemical reaction
     * @supplierCardinality 0..*
     * @label Stoichiometry
     */
    CCopasiVector < CChemEqElement > mBalances;

    // Operations

  public:
    /**
     *  Default constructor
     */
    CChemEq();

    /**
     *  Copy constructor
     *  @param "const CChemEq &" src
     */
    CChemEq(const CChemEq & src);

    /**
     *  Destructor
     */
    ~CChemEq();

    /**
     *  Cleanup
     */
    void cleanup();

    /**
     *  Compile
     *  @param "CCopasiVectorN < CCompartment > &" compartments
     */
    void compile(CCopasiVectorN < CCompartment > & compartments);

    /**
     *  Set the chemical equation
     *  @param "const string &" chemicalEquation (in any form even mixed)
     */
    void setChemicalEquation(const string & chemicalEquation);

    /**
     *  Retrieves the chemical equation with multipliers.
     *  @return "const string &" ChemicalEquation
     */
    const string & getChemicalEquation() const;

    /**
     *  Retrieves the converted form of chemical equation.
     *  This does not contain any multipliers.
     *  @return "const string &" ChemicalEquationConverted
     */
    const string & getChemicalEquationConverted() const;

    /**
     *  Retrieves the vector of substrates and their multiplicity 
     *  in the chemical reaction.
     *  @return "vector < CChemEqElement * > &" substrates
     */
    const CCopasiVector < CChemEqElement > & getSubstrates();

    /**
     *  Retrieves the vector of products and their multiplicity 
     *  in the chemical reaction.
     *  @return "vector < CChemEqElement * > &" products
     */
    const CCopasiVector < CChemEqElement > & getProducts();

    /**
     *  Retrieves the vector of metabolites and their total balance 
     *  in the chemical reaction.
     *  @return "vector < CChemEqElement * > &" balances
     */
    const CCopasiVector < CChemEqElement > & getBalances();

  private:
    /**
     *  Extracts the next element of the input string starting at position pos.
     *  @param "const string &" input (string to parse)
     *  @param "string::size_type &" pos 
     *              (on input:  starting position of the parse)
     *              (on output: starting position for the next parse)
     *  @return "CChemEqElement" element
     */
    CChemEqElement extractElement(const string & input,
                                  string::size_type & pos) const;

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
    void setChemEqElements(CCopasiVector < CChemEqElement > & elements,
                           const string & reaction,
                           CChemEq::MetaboliteRole role =
                             CChemEq::PRODUCT);

    /**
     *  Compile the ChemEqElement, i.e., the pointer to the metabolite
     *  is assigned.
     *  @param "vector < CChemEqElement * > &" elements
     *  @param "vector < CMetab * > &" metabolites
     */
    void compileChemEqElements(CCopasiVector < CChemEqElement > & elements,
                               CCopasiVectorN < CCompartment > & metabolites);

    /**
     *  This function frees a vector of CChemEqElement
     *  @param "vector < CChemEqElement * > &" elements
     */
    void cleanupChemEqElements(vector < CChemEqElement * > & elements);

    /**
     *  This function splits the chemical equation into a left and a right
     *  @param "string &" left (substrate side)
     *  @param "string &" right (product side)
     */
    void splitChemEq(string & left, string & right) const;

    /**
     *  Writes the chemical equation in a form with multipliers.
     */
    void writeChemicalEquation();

    /**
     *  Writes the chemical equation in a form without multipliers.
     */
    void writeChemicalEquationConverted();

    friend ostream & operator<<(ostream &os, const CChemEq & d)
    {
      os << "CChemEq:" << endl;
      os << "   mChemicalEquation:          " << d.mChemicalEquation << endl;
      os << "   mChemicalEquationConverted: " << d.mChemicalEquationConverted << endl;

      os << "   mSubstrates:" << endl;
      os << d.mSubstrates;
      os << "   mProducts:" << endl;
      os << d.mProducts;
      os << "   mBalances:" << endl;
      os << d.mBalances;

      os << "----CChemEq" << endl;
      return os;
    }
  };

#endif // COPASI_CChemEq
