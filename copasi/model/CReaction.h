/**
 *  CReaction class.
 *  Derived from Gepasi's cstep.cpp. (C) Pedro Mendes 1995-2000.
 *
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CReaction
#define COPASI_CReaction

#include <string>
#include <vector>
#include <utility>


#include "utilities/utilities.h"
#include "function/function.h"
#include "CMetab.h"
#include "CChemEq.h"
#include "CChemEqElement.h"

class CReaction
{
  
  // Attributes
 private:
  class CId2Metab
    {
      friend class CReaction;
      // Attributes
    private:
      /**
       *  The name of the identifier as defined by the called function
       */
      string mIdentifierName;

      /**
       *  The name of the metabolite
       */
      string mMetaboliteName;

      /**
       *  The name of the compartment the metabolite is located in
       */
      string mCompartmentName;

      /**
       *  A pointer to the metabolite
       */
      CMetab *mpMetabolite;

    public:
      // Operations
      /**
       *  Default constructor
       */
      CId2Metab();

      /**
       *  Copy constructor
       *  @param "const CId2Metab &" src
       */
      CId2Metab(const CId2Metab & src);

      /**
       *  Destructor
       */
      ~CId2Metab();
      
      /**
       *  cleanup();
       */
      void cleanup();
    };

  class CId2Param
    {
      friend class CReaction;
      // Attributes
    private:
      /**
       *  The name of the parameter as defined by the called function
       */
      string mIdentifierName;

      /**
       *  The value of the parameter
       */
      C_FLOAT64 mValue;

    public:
      // Operations
      /**
       *  Default constructor
       */
      CId2Param();

      /**
       *  Copy constructor
       *  @param "const CId2Param &" src
       */
      CId2Param(const CId2Param & src);

      /**
       *  Destructor
       */
      ~CId2Param();

      /**
       *  cleanup();
       */

      void cleanup();
      /**
       *	Return Identifier Name		Wei Sun		
       */
      string getIdentifierName() const;

      /**
       *	Retun the value of the pararmeter	
       */
      C_FLOAT64 getValue() const;

      /**
       *	Returns the address of mValue
       */
      void * getValueAddr();

    };

  /**
   *  The name of the reaction
   */
  string mName;

  /**
   *  The chemical equation
   */
  CChemEq mChemEq;

  /**
   *  A pointer to the rate function of the reaction
   */
  CFunction * mFunction;

  /**
   *  The description of the function parameters
   */
  CFunctionParameters mParameterDescription;

  /**
   *  The flux of the reaction
   */
  C_FLOAT64 mFlux;

  /**
   *  The reversibility of the reaction
   */
  C_INT16 mReversible;

  /**
   *  A vector of links between the substrates of the reaction 
   *  and function parameters
   */
  CCopasiVector < CId2Metab > mId2Substrates;

  /**
   *  A vector of links between the products of the reaction 
   *  and function parameters
   */
  CCopasiVector < CId2Metab > mId2Products;

  /**
   *  A vector of links between the modifiers of the reaction 
   *  and function parameters
   */
  CCopasiVector < CId2Metab > mId2Modifiers;

  /**
   *  A vector of links between the kinetic parameters of the reaction 
   *  and function parameters
   */
  CCopasiVector < CId2Param > mId2Parameters;

  /**
   *  A pointer to the  call parameters of the rate function of the reaction
   */
  CCallParameters mCallParameters;

  /**
   *
   */
  C_INT32 mFail;

  // Operations
 public:
  /**
   *  Default constructor
   */
  CReaction();

  /**
   *  Copy constructor
   *  @param "const CReaction &" src
   */
  CReaction(const CReaction & src);

  /**
   *  Named constructor
   *  @param "const string &" name
   */
  CReaction(const string & name);

  /**
   *  Destructor
   */
  ~CReaction();

  /**
   *  Delete
   */
  void cleanup();
    
  /**
   *  Assignment operator
   */
  CReaction & operator=(const CReaction & rhs);

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return mFail
   *  @see mFail
   */
  C_INT32 load(CReadConfig & configbuffer);

  /**
   *  Saves the contents of the object to a CWriteConfig object.
   *  (Which usually has a file attached but may also have socket)
   *  @param pconfigbuffer reference to a CWriteConfig object.
   *  @return mFail
   *  @see mFail
   */
  C_INT32 save(CWriteConfig & configbuffer);

  /**
   *  Retrieves the vector of substrates
   *  @return "CCopasiVector < CId2Metab > &"
   */
  CCopasiVector < CId2Metab > &getId2Substrates();

  /**
   *  Retrieves the vector of products
   *  @return "CCopasiVector < CId2Metab > &"
   */
  CCopasiVector < CId2Metab > &getId2Products();

  /**
   *  Retrieves the vector of modifiers
   *  @return "CCopasiVector < CId2Metab > &"
   */
  CCopasiVector < CId2Metab > &getId2Modifiers();

  /**
   *  Retrieves the vector of parameters
   *  @return "CCopasiVector < CId2Param > &"
   */
  CCopasiVector < CId2Param > &getId2Parameters();

  /**
   *  Retrieves the name of the reaction
   *  @return string
   */
  string getName() const;

  /**
   *  Retrieves the chemical equation of the reaction
   *  @return string
   */
  CChemEq & getChemEq();

  /**
   *  Retrieves the chemical structure of the reaction
   *  @return vector < ELEMENT >
   */
  // typedef struct ELEMENT {C_FLOAT64 mValue; string mName;};
  // vector < ELEMENT > getChemStructure() const;

  /**
   *  Retrieves a vector of substrates and their multiplicity
   *  in the chemical reaction.
   *  @return "vector < CChemEqElement * > &" substrates
   */
  vector < CChemEqElement * > & getSubstrates();
  
  /**
   *  Retrieves a vector of products and their multiplicity.
   *  in the chemical reaction.
   *  @return "vector < CChemEqElement * > &" products
   */
  vector < CChemEqElement * > & getProducts();

  /**
   *  Retrieves a vector of metabolites and their total balance.
   *  in the chemical reaction.
   *  @return "vector < CChemEqElement * > &" products
   */
  vector < CChemEqElement * > & getBalances();

  /**
   *  Retrieves the rate function of the reaction
   *  @return "CBaseFunction &"
   */
  CFunction & getFunction();

  /**
   *  Retrieves the flux of the reaction
   *  @return C_FLOAT64
   */
  C_FLOAT64 getFlux() const;

  /**
   *  Retrieves whether the reaction is reversible
   *  @return C_INT16
   */
  C_INT16 isReversible() const;

  /**
   *  Sets the name of the reaction
   *  @param "const string &" name
   */
  void setName(const string & name);

  /**
   *  Sets the chemical equation of the reaction
   *  @param "const string &" chemEq
   */
  void setChemEq(const string & chemEq);

  /**
   *  Sets the rate function of the reaction
   *  @param "const string &" functionName
   */
  void setFunction(const string & functionName);

  /**
   *  Sets the flux of the reaction
   *  @param C_FLOAT64 flux
   */
  void setFlux(C_FLOAT64 flux);

  /**
   *  Sets whether the reaction is reversible
   *  @param C_INT16 reversible
   */
  void setReversible(C_INT16 reversible);

  /**
   *  Compile the reaction, i.e., links the metabolites and parameters with the
   *  rate function.
   *  @param "CCopasiVectorNS < CCompartment > &" compartments
   */
  void compile(CCopasiVectorNS < CCompartment > & compartments);

  /**
   *  Calculate the kinetic function
   *  @return C_FLOAT64 velocity
   */
  C_FLOAT64 calculate();

  /**
   *  Retrieves the Compartment Name for substrates, products, and modifiers
   *  @param "vector < CMetab* > &" Metabolites 
   */
  void old2New(const vector < CMetab* > & metabolites);
    
  /**
   *	Returns the address of mFlux		Wei Sun
   */
  void * getFluxAddr();

  /**
   *	Returns the index of the parameter
   */
  C_INT32 findPara(string &Target);

  /**
   * Find an pointer to a substrate corresponding to the given identifier name.
   * @param ident_name The identifier name to search by
   * @return A pointer to the metabolite corresponding to this identifier name
   */
  CMetab * findSubstrate(string ident_name);

  /**
   * Find an pointer to a modifier corresponding to the given identifier name.
   * @param ident_name The identifier name to search by
   * @return A pointer to the metabolite corresponding to this identifier name
   */
  CMetab * findModifier(string ident_name);

 private:
  /**
   *
   */
  C_INT32 loadNew(CReadConfig & configbuffer);

  /**
   *
   */
  C_INT32 loadOld(CReadConfig & configbuffer);

  /**
   *
   */
  void cleanupCallParameters();

  /**
   *
   */
  void initCallParameters();

  /**
   *
   */
  void setCallParameters();

  /**
   *
   */
  void checkCallParameters();

  /**
   *
   */
  unsigned C_INT32 findParameter(const string & name,
                                 CFunctionParameter::DataType & dataType);

  /**
   *  Returns the max number of elements for the specified usage
   *  @param "const string" & usage
   *  @return unsigned C_INT32 size
   */
  unsigned C_INT32 usageRangeSize(const string & usage);
  
#ifdef XXXX
  /**
   *
   */
  void initIdentifiers();

  /**
   *
   */
  void setIdentifiers();

  /**
   *
   */
  void checkIdentifiers();
#endif // XXXX

};

#endif // COPASI_CReaction
