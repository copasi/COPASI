/**
 *  CSteb class.
 *  Derived from Gepasi's cstep.cpp. (C) Pedro Mendes 1995-2000.
 *
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CStep
#define COPASI_CStep

#include <string>
#include <vector>
#include <utility>

#include "CKinFunction.h"
#include "CFunctionDB.h"
#include "CMetab.h"

/**
 * CStepMetab class 
 *
 * Collects the properties of each participating metabolite in a
 * reaction step. CStep stores a vector of these.
 */
class CStepMetab
{
// Attributes
 private:
    /**
     * A pointer to the metabolite
     */
    CMetab *mMetabolite;
    /**
     * The number of identical educts of this type present in the
     * reaction. This has value 0 if the metabolite is only present as
     * a product.
     */
    C_INT32 mNumIdent;
    /**
     * The number by which this metabolite changes in each reaction of
     * this type.
     */
    C_INT32 mNumChange;
 public:
// Lifecycle   
    /**
     * Default constructor
     */
    CStepMetab();
    /**
     * Named constructor
     * @param metab A pointer to a CMetab
     * @param num_ident The identical number of these elements reacting
     * @param num_change The number by which this metabolite changes in this reaction.
     */
    CStepMetab(CMetab *metab, C_INT32 num_ident, C_INT32 num_change);
    /**
     * Destructor
     */
    ~CStepMetab();
// Operations   
    /**
     * Retrieve a pointer to the metabolite
     * @return mMetabolite
     */
    CMetab *GetMetab();
    /**
     * Get the identical number of this metabolite reacting
     * @return mNumIdent
     */
    C_INT32 GetNumIdent();
    /**
     * Get the number by which this metabolite changes in a reaction
     * @return mNumChange
     */
    C_INT32 GetNumChange();
};


class CStep
{
// Attributes
private:
    class CId2Metab
        {
            friend class CStep;
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
             *  Default Constructor
             */
            CId2Metab();

            /**
             *  Destructor
             */
            ~CId2Metab();
        };

    class CId2Param
        {
            friend class CStep;
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
             *  Default Constructor
             */
            CId2Param();

            /**
             *  Destructor
             */
            ~CId2Param();
        };

    /**
     *  The name of the step
     */
    string mName;

    /**
     *  The chemical equation
     */
    string mChemEq;

    /**
     *  A pointer to the rate function of the step
     */
    CBaseFunction * mFunction;

    /**
     *  The flux of the step
     */
    C_FLOAT64 mFlux;

    /**
     *  The reversibility of the step
     */
    C_INT16 mReversible;

    /**
     *  A pointer to the substrates of the step
     */
    vector < CId2Metab > * mSubstrates;

    /**
     *  A pointer to the products of the step 
     */
    vector < CId2Metab > * mProducts;

    /**
     *  A pointer to the modifiers of the step
     */
    vector < CId2Metab > * mModifiers;

    /**
     *  A pointer to the parameters of the step
     */
    vector < CId2Param > * mParameters;

    /**
     *  A pointer to the  call parameters of the rate function of the step
     */
    vector < CCallParameter > * mCallParameters;

    /**
     *
     */
    C_INT32 mFail;
// Operations
public:
    /**
     *  Default constructor
     */
    CStep();

    /**
     *  Named constructor
     *  @param "const string &" name
     */
    CStep(const string & name);

    /**
     *  Init
     */
    void initialize();
    
    /**
     *  Destructor
     */
    ~CStep();

    /**
     *  Delete
     */
    void cleanup();
    
    /**
     *  Assignment operator
     */
    CStep & operator=(const CStep & rhs);

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
     *  @return "vector < CId2Metab > &"
     */
    vector < CId2Metab > &substrates();

    /**
     *  Retrieves the vector of products
     *  @return "vector < CId2Metab > &"
     */
    vector < CId2Metab > &products();

    /**
     *  Retrieves the vector of modifiers
     *  @return "vector < CId2Metab > &"
     */
    vector < CId2Metab > &modifiers();

    /**
     *  Retrieves the vector of parameters
     *  @return "vector < CId2Param > &"
     */
    vector < CId2Param > &parameters();

    /**
     *  Retrieves the name of the step
     *  @return string
     */
    string getName() const;

    /**
     *  Retrieves the chemical equation of the step
     *  @return string
     */
    string getChemEq() const;

    /**
     *  Retrieves the chemical structure of the step
     *  @return vector < ELEMENT >
     */
    typedef struct ELEMENT {C_FLOAT64 mValue; string mName;};
    vector < ELEMENT > getChemStructure() const;

    /**
     *  Retrieves the rate function of the step
     *  @return "CBaseFunction &"
     */
    CBaseFunction & getFunction();

    /**
     *  Retrieves the flux of the step
     *  @return C_FLOAT64
     */
    C_FLOAT64 getFlux() const;

    /**
     *  Retrieves whether the step is reversible
     *  @return C_INT16
     */
    C_INT16 isReversible() const;

    /**
     *  Sets the name of the step
     *  @param "const string &" name
     */
    void setName(const string & name);

    /**
     *  Sets the chemical equation of the step
     *  @param "const string &" chemEq
     */
    void setChemEq(const string & chemEq);

    /**
     *  Sets the rate function of the step
     *  @param "const string &" functionName
     */
    void setFunction(const string & functionName);

    /**
     *  Sets the flux of the step
     *  @param C_FLOAT64 flux
     */
    void setFlux(C_FLOAT64 flux);

    /**
     *  Sets whether the step is reversible
     *  @param C_INT16 reversible
     */
    void setReversible(C_INT16 reversible);

    /**
     *  Compile the step, i.e., links the metabolites and parameters with the
     *  rate function.
     *  @param "CCopasiVector < CMetab * > &" metabolites
     */
    void compile(const CCopasiVector < CCompartment > * compartments);

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
    void initIdentifiers();

    /**
     *
     */
    void setIdentifiers();

    /**
     *
     */
    void checkIdentifiers();

    /**
     *
     */
    ELEMENT extractElement(const string & input, 
                           string::size_type & pos) const;

    /**
     *
     */
    void addElement(const ELEMENT & element,
                    vector < ELEMENT > & structure) const;

};

#endif // COPASI_CStep
