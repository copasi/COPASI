/**
 *  CSteb class.
 *  Derived from Gepasi's cstep.cpp. (C) Pedro Mendes 1995-2000.
 *
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CStep
#define COPASI_CSteb

#include <string>
#include <vector>
#include <utility>

#include "CKinFunction.h"
#include "CFunctionDB.h"
#include "CMetab.h"

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
        double mValue;

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
    double mFlux;

    /**
     *  The reversibility of the step
     */
    short mReversible;

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
    long mFail;
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
    void Init();
    
    /**
     *  Destructor
     */
    ~CStep();

    /**
     *  Delete
     */
    void Delete();
    
    /**
     *  Assignement operator
     */
    CStep & operator=(const CStep & rhs);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    long Load(CReadConfig & configbuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    long Save(CWriteConfig & configbuffer);

    /**
     *  Retrieves the vector of substrates
     *  @return "vector < CId2Metab > &"
     */
    vector < CId2Metab > &Substrates();

    /**
     *  Retrieves the vector of products
     *  @return "vector < CId2Metab > &"
     */
    vector < CId2Metab > &Products();

    /**
     *  Retrieves the vector of modifiers
     *  @return "vector < CId2Metab > &"
     */
    vector < CId2Metab > &Modifiers();

    /**
     *  Retrieves the vector of parameters
     *  @return "vector < CId2Param > &"
     */
    vector < CId2Param > &Parameters();

    /**
     *  Retrieves the name of the step
     *  @return string
     */
    string GetName();

    /**
     *  Retrieves the chemical equation of the step
     *  @return string
     */
    string GetChemEq();

    /**
     *  Retrieves the rate function of the step
     *  @return "CBaseFunction &"
     */
    CBaseFunction & GetFunction();

    /**
     *  Retrieves the flux of the step
     *  @return double
     */
    double GetFlux();

    /**
     *  Retrieves whether the step is reversible
     *  @return short
     */
    short IsReversible();

    /**
     *  Sets the name of the step
     *  @param "const string &" name
     */
    void SetName(const string & name);

    /**
     *  Sets the chemical equation of the step
     *  @param "const string &" chemEq
     */
    void SetChemEq(const string & chemEq);

    /**
     *  Sets the rate function of the step
     *  @param "const string &" functionName
     */
    void SetFunction(const string & functionName);

    /**
     *  Sets the flux of the step
     *  @param double flux
     */
    void SetFlux(double flux);

    /**
     *  Sets whether the step is reversible
     *  @param short reversible
     */
    void SetReversible(short reversible);

    /**
     *  Compile the step, i.e., links the metabolites and parameters with the
     *  rate function.
     *  @param "CCopasiVector < CMetab * > &" metabolites
     */
    void Compile(CCopasiVector < CMetab * > & metabolites);

private:
    /**
     *
     */
    long LoadNew(CReadConfig & configbuffer);

    /**
     *
     */
    long LoadOld(CReadConfig & configbuffer);

    /**
     *
     */
    void InitIdentifiers();

    /**
     *
     */
    void SetIdentifiers();

    /**
     *
     */
    void CheckIdentifiers();

};

#endif // COPASI_CSteb
