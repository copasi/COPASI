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

#include "utilities/utilities.h"
#include "function/function.h"
#include "CMetab.h"
#include "CChemEq.h"
#include "CChemEqElement.h"

template < class CType > class CVector;

/** @dia:pos 135.488,75.5337 */
class CReaction : public CCopasiContainer
  {
    // Attributes

  public:

    /** @dia:pos 93.3703,97.2451 */
  class CId2Metab : public CCopasiContainer
      {
        friend class CReaction;
        // Attributes

      private:
        /**
         *  The name of the identifier as defined by the called function
         */
        std::string & mIdentifierName;

        /**
         *  The name of the metabolite
         */
        std::string mMetaboliteName;

        /**
         *  The name of the compartment the metabolite is located in
         */
        std::string mCompartmentName;

        /**
         *  A pointer to the metabolite
         */
        /** @dia:route 97,2; h,117.263,88.8961,131.334,97.2451,126.108 */
        CMetab *mpMetabolite;

      public:
        // Operations
        /**
         * Default constructor
         * @param const std::string & name (default: "NoName")
         * @param const CCopasiContainer * pParent (default: NULL)
         */
        CId2Metab(const std::string & name = "NoName",
                  const CCopasiContainer * pParent = NULL);

        /**
         * Copy constructor
         * @param "const CId2Metab &" src
         * @param const CCopasiContainer * pParent (default: NULL)
         */
        CId2Metab(const CId2Metab & src,
                  const CCopasiContainer * pParent = NULL);

        /**
         *  Destructor
         */
        ~CId2Metab();

        /**
         *  cleanup();
         */
        void cleanup();

        /**
         *  Set the identifier name
         *  @param "const string &" identifierName
         */
        void setIdentifierName(const std::string & identifierName);

        /**
         *  Retrieve the identifier name
         *  @return "const string &" identifierName
         */
        const std::string & getIdentifierName() const;

        /**
         *  Set the metabolite name
         *  @param "const string &" metaboliteName
         */
        void setMetaboliteName(const std::string & metaboliteName);

        /**
         *  Retrieve the metabolite name
         *  @return "const string &" metaboliteName
         */
        const std::string & getMetaboliteName() const;

        /**
         *  Set the compartment name
         *  @param "const string &" compartmentName
         */
        void setCompartmentName(const std::string & compartmentName);

        /**
         *  Retrieve the compartment name
         *  @return "const string &" compartmentName
         */
        const std::string & getCompartmentName() const;

        /**
         *  Retrieve a pointer to the metabolite
         *  @return "CMetab *" pointer to metabolite
         */
        CMetab * getMetabolite() const;

        /**
         * insert operator
         */
        friend std::ostream & operator<<(std::ostream &os, const CId2Metab & d)
        {
          os << "     CId2Metab: Ident " << d.getIdentifierName()
          << " Metab " << d.getMetaboliteName()
          << " Compa " << d.getCompartmentName();

          if (d.mpMetabolite)
            os << " *metab " << d.mpMetabolite->getName() << std::endl;
          else
            os << " metab == 0 " << std::endl;

          return os;
        }
      };

    /** @dia:pos 93.7456,113.598 */
  class CId2Param : public CCopasiContainer
      {
        friend class CReaction;
        // Attributes

      private:
        /**
         *  The name of the parameter as defined by the called function
         */
        std::string & mIdentifierName;

        /**
         *  The value of the parameter
         */
        C_FLOAT64 mValue;

      public:
        // Operations
        /**
         * Default constructor
         * @param const std::string & name (default: "NoName")
         * @param const CCopasiContainer * pParent (default: NULL)
         */
        CId2Param(const std::string & name = "NoName",
                  const CCopasiContainer * pParent = NULL);

        /**
         * Copy constructor
         * @param "const CId2Param &" src
         * @param const CCopasiContainer * pParent (default: NULL)
         */
        CId2Param(const CId2Param & src,
                  const CCopasiContainer * pParent = NULL);

        /**
         *  Destructor
         */
        ~CId2Param();

        /**
         *  cleanup();
         */

        void cleanup();

        /**
         *  Set the identifier name
         *  @param "const string &" identifierName
         */
        void setIdentifierName(const std::string & identifierName);

        /**
         *  Retrieve the identifier name
         *  @return "const string &" identifierName
         */
        const std::string & getIdentifierName() const;

        /**
         *  Set the identifier value
         *  @param "const C_FLOAT64 &" value
         */
        void setValue(const C_FLOAT64 & value);

        /**
         *  Retrieve the identifier value
         *  @return "const C_FLOAT64 &" value
         */
        const C_FLOAT64 & getValue() const;

        /**
         * Returns the address of mValue
         */
        void * getValueAddr();

        /**
         * insert operator
         */
        friend std::ostream & operator<<(std::ostream &os, const CId2Param & d)
        {
          os << "     CId2Param: Ident " << d.getIdentifierName()
          << " Value " << d.getValue() << std::endl;
          return os;
        }
      };

  private:
    /**
     *  The default scaling factor of a reaction which is 1.
     */
    static C_FLOAT64 mDefaultScalingFactor;

    /**
     *  The name of the reaction
     */
    std::string & mName;

    /**
     *  The chemical equation
     */
    /** @dia:route 2,5; h,88.6464,95.1644,91.3136,127.734,135.488 */
    CChemEq mChemEq;

    /**
     *  A pointer to the rate function of the reaction
     */
    CFunction * mpFunction;

    /**
     *  The description of the function parameters.
     *  This is a copy of the information in the CFunction object.
     *  It describes which parameters need to be passed to the function.
     */
    CFunctionParameters mParameterDescription;

    /**
     *  The flux of the reaction
     */
    C_FLOAT64 mFlux;

    /**
     *  The scaled flux of the reaction
     */
    C_FLOAT64 mScaledFlux;

    /**
     *  A Pointer to the scaling factor for the flux to calculate the particle number
     *  changes. For a single compartment reaction this is the volume of
     *  the compartment
     */
    const C_FLOAT64 * mScalingFactor;

    /**
     *  The scaling factor. It is compartment volume times a factor for the unit
     */
    const C_FLOAT64 * mScalingFactor2;

    /**
     *  The number of compartments the reaction takes place in 
     */
    C_INT32 mCompartmentNumber;

    /**
     *  The reversibility of the reaction
     */
    bool mReversible;

    /**
     *  A vector of links between the substrates of the reaction 
     *  and function parameters
     */
    /** @dia:route 20,9; h,135.488,82.2337,133.093,99.1451,126.108 */
    CCopasiVector < CId2Metab > mId2Substrates;

    /**
     *  A vector of links between the products of the reaction 
     *  and function parameters
     */
    /** @dia:route 20,13; h,135.488,82.2337,133.093,100.745,126.108 */
    CCopasiVector < CId2Metab > mId2Products;

    /**
     *  A vector of links between the modifiers of the reaction 
     *  and function parameters
     */
    /** @dia:route 20,17; h,135.488,82.2337,133.093,102.545,126.108 */
    CCopasiVector < CId2Metab > mId2Modifiers;

    /**
     *  A vector of links between the kinetic parameters of the reaction 
     *  and function parameters
     */
    /** @dia:route 84,2; h,135.488,108.034,133.093,113.598,125.427 */
    CCopasiVector < CId2Param > mId2Parameters;

    /**
     *  A pointer to the  call parameters of the rate function of the reaction
     */
    CCallParameters mCallParameters;

    /**
     *  A pointer to the  call parameters of the rate function of the reaction
     */
    CCallParameters mCallParameterNames;

    /**
     *
     */
    C_INT32 mFail;

    // Operations

  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReaction(const std::string & name = "NoName",
              const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CReaction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReaction(const CReaction & src,
              const CCopasiContainer * pParent = NULL);

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
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param CWriteConfig & configbuffer
     *  @param const CCopasiVectorN< CMetab > & metabolites
     *  @return mFail
     *  @see mFail
     */
    C_INT32 saveOld(CWriteConfig & configbuffer,
                    const CCopasiVectorN< CMetab > & metabolites);

    /**
     *  Saves the contents of the object to a ofstream object.
     *  Writes the data in SBML file format
     *  @param "std::ofstream &" fout ofstream that should be already open
     *  @param C_INT32 r the ordinal number of this reaction (to append to parameters)
     */
    void saveSBML(std::ofstream &fout, C_INT32 r = 0);

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
    const std::string & getName() const;

    /**
     *  Retrieves the chemical equation of the reaction
     *  @return string
     */
    CChemEq & getChemEq();

    /**
     *  Retrieves the number of substrates of this reaction
    *  Note: this is the number of different species, not
    *  not the total number of substrate molecules
     *  @return C_INT32
     */
    C_INT32 getSubstrateNumber(void);

    /**
     *  Retrieves the number of substrates of this reaction
    *  Note: this is the number of different species, not
    *  not the total number of substrate molecules
     *  @return C_INT32
     */
    C_INT32 getProductNumber(void);

    /**
     *  Retrieves the chemical structure of the reaction
     *  @return vector < ELEMENT >
     */ 
    // typedef struct ELEMENT {C_FLOAT64 mValue; string mName;};
    // vector < ELEMENT > getChemStructure() const;

    /**
     *  Retrieves the rate function of the reaction
     *  @return "CBaseFunction &"
     */
    CFunction & getFunction();

    /**
     *  Retrieves the flux of the reaction
     *  @return const C_FLOAT64 & flux
     */
    const C_FLOAT64 & getFlux() const;

    /**
     *  Retrieves the scaled flux of the reaction
     *  @return const C_FLOAT64 & scaledFlux
     */
    const C_FLOAT64 & getScaledFlux() const;

    /**
     *  Retrieves whether the reaction is reversible
     *  @return bool
     */
    bool isReversible() const;

    /**
     *  Sets the name of the reaction
     *  @param "const string &" name
     */
    void setName(const std::string & name);

    /**
     *  Sets the chemical equation of the reaction
     *  @param "const string &" chemEq
     */
    void setChemEq(const std::string & chemEq);

    /**
     *  Sets the rate function of the reaction
     *  @param "const string &" functionName
     */
    void setFunction(const std::string & functionName);

    /**
     *  Sets whether the reaction is reversible
     *  @param bool reversible
     */
    void setReversible(bool reversible);

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
     * Calculate partial derivative at xi where i is the it met
     * @param C_FLOAT64 & xi
     * @param const C_FLOAT64 & derivationFactor
     * @param const C_FLOAT64 & resolution (unscaled resolution)
     * @return C_FLOAT64 partial 
     */
    C_FLOAT64 calculatePartialDerivative(C_FLOAT64 & xi,
                                         const C_FLOAT64 & derivationFactor,
                                         const C_FLOAT64 & resolution);

    /**
     *  Retrieves the Compartment Name for substrates, products, and modifiers
     *  @param const CCopasiVector< CMetab > & metabolites
     */
    void old2New(const CCopasiVector< CMetab > & metabolites);

    /**
     * Returns the address of mFlux  Wei Sun
     */
    void * getFluxAddr();

    /**
     * Returns the index of the parameter
     */
    C_INT32 findPara(std::string &Target);

    /**
     * Find an pointer to a substrate corresponding to the given identifier name.
     * @param ident_name The identifier name to search by
     * @return A pointer to the metabolite corresponding to this identifier name or NULL if none found
     */
    CMetab * findSubstrate(std::string ident_name);

    /**
     * Find an pointer to a modifier corresponding to the given identifier name.
     * @param ident_name The identifier name to search by
     * @return A pointer to the metabolite corresponding to this identifier name or NULL if none found
     */
    CMetab * findModifier(std::string ident_name);

    /**
     *  Retrieves the number of compartments the reaction is acting in.
     *  @return "unsigned C_INT32" the compartment number
     */
    unsigned C_INT32 getCompartmentNumber();

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CReaction & d)
    {
      os << "CReaction:  " << d.getName() << std::endl;

      os << "   mChemEq " << std::endl;
      os << d.mChemEq;

      if (d.mpFunction)
        os << "   *mpFunction " << d.mpFunction->getName() << std::endl;
      else
        os << "   mpFunction == 0 " << std::endl;

      os << "   mParameterDescription: " << std::endl << d.mParameterDescription;
      os << "   mFlux: " << d.mFlux << std::endl;

      if (d.mScalingFactor)
        os << "   *mScalingFactor " << *(d.mScalingFactor) << std::endl;
      else
        os << "   mScalingFactor == 0 " << std::endl;

      os << "   mScalingFactor2: " << d.mScalingFactor2 << std::endl;
      os << "   mCompartmentNumber: " << d.mCompartmentNumber << std::endl;
      os << "   mReversible: " << d.mReversible << std::endl;
      os << "   mId2Substrates" << std::endl;
      os << d.mId2Substrates;
      os << "   mId2Products" << std::endl;
      os << d.mId2Products;
      os << "   mId2Modifiers" << std::endl;
      os << d.mId2Modifiers;
      os << "   mId2Parameters" << std::endl;
      os << d.mId2Parameters;
      os << "   mFail: " << d.mFail << std::endl;
      os << "----CReaction" << std::endl;

      return os;
    }

    /**
     *  Sets mId2Substrates and mId2Products from the mChemEq
     *  can be called after setting reaction name and chemical equation
     *  needs metabolites to already have been created
     */
    void setReactantsFromChemEq();

    /**
     *  Forces compilation of Chemical equation object
     */
    void compileChemEq(CCopasiVectorN < CCompartment > & compartments);

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
     *  gets mParameterDescription from mpFunction and then creates the vectors inside
     *  mCallParameters (If needed)
     */
    void initCallParameters();

    /**
     *
     */
    void setCallParameters();

    /**
     *  Checks if all the Pointers in mCallParameters are !=NULL
     */
    void checkCallParameters();

    /**
     *
     */
    void cleanupCallParameterNames();

    /**
     *  gets mParameterDescription from mpFunction and then creates the vectors inside
     *  mCallParameterNames (If needed)
     */
    void initCallParameterNames();

    /**
     *
     */
    void setCallParameterNames();

    /**
     *  Checks if all the Pointers in mCallParameters are !=NULL
     */
    void checkCallParameterNames();

    /**
     *
     */
    unsigned C_INT32 findParameter(const std::string & name,
                                   CFunctionParameter::DataType & dataType);

    /**
     *  Returns the max number of elements for the specified usage
     *  @param "const string" & usage
     *  @return unsigned C_INT32 size
     */
    unsigned C_INT32 usageRangeSize(const std::string & usage);

    /**
     * Sets the scaling factor of the for the fluxes
     */
    void setScalingFactor();
  };

#endif // COPASI_CReaction
