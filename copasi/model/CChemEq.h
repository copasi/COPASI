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
   */
  vector < CChemEqElement * > mSubstrates;
  
  /**
   *  A vector of products and their multiplicity in the chemical reaction
   */
  vector < CChemEqElement * > mProducts;

  /**
   *  A vector of metabolites and their total balance in the chemical reaction
   */
  vector < CChemEqElement * > mBalances;

  // Operations
 public:
  /**
   *  Default constructor
   */
  CChemEq();
  
  /**
   *  Copy constructor
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
   *  Set the chemical equation
   *  @param "const string &" chemicalEquation (in any form even mixed)
   */
  void setChemicalEquation(const string & chemicalEquation);
  
  /**
   *  Retrieves the chemical equation with multipliers.
   */
  const string & getChemicalEquation() const;
  
  /**
   *  Retrieves the converted form of chemical equation.
   *  This does not contain any multipliers.
   */
  const string & getChemicalEquationConverted() const;

  /**
   *  Retrieves the vector of substrates and their multiplicity 
   *  in the chemical reaction.
   */
  const vector < CChemEqElement * > & getSubstrates();

  /**
   *  Retrieves the vector of products and their multiplicity 
   *  in the chemical reaction.
   */
  const vector < CChemEqElement * > & getProducts();

  /**
   *  Retrieves the vector of metabolites and their total balance 
   *  in the chemical reaction.
   */
  const vector < CChemEqElement * > & getBalances();

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
   *  @param "vector < CChemEqElement * > &" structure
   *  @param "const CChemEqElement &" element
   *  @param "CChemEq::MetaboliteRole" role (
   */
  void addElement(vector < CChemEqElement * > & structure,
		  const CChemEqElement & element,
		  CChemEq::MetaboliteRole role = CChemEq::PRODUCT);

  /**
   *  This function creates the vector < CChemEqElement * > mSubstrates
   */
  void setSubstrates(const string & eqn);
  
  /**
   *  This function creates the vector < CChemEqElement * > mProducts
   */
  void setProducts(const string & eqn);

  /**
   *  This function creates the vector < CChemEqElement * > mBalances
   */
  void setBalances(const string & left, const string & right);

  /**
   *  This is the called by setSubstrates, setProducts, and setBalances.
   *  It realy does the work.
   */
  void setChemEqElements(vector < CChemEqElement * > & elements,
			 const string & reaction,
			 CChemEq::MetaboliteRole role = 
			 CChemEq::PRODUCT);

  /**
   *  Compile the ChemEqElement, i.e., the pointer to the metabolite
   *  is assigned.
   *  @param "vector < CChemEqElement * > &" elements
   *  @param "vector < CMetab * > &" metabolites
   */
  void compileChemEqElements(vector < CChemEqElement * > & elements,
			     vector < CMetab * > & metabolites);

  /**
   *  This function releases the vector < CChemEqElement * > mSubstrates
   */
  void cleanupChemEqElements(vector < CChemEqElement * > & elements);
  
  /**
   *  This function splits the chemical equation into a left and a right
   */
  void splitChemEq(string & left, string & right) const;
};

#endif // COPASI_CChemEq 
