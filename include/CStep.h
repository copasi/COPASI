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
public:
    typedef struct ID2METAB
    {
        string Identifier;
        string Metabolite;
        string Compartment;
        CMetab *pMetabolite;
    };
    
    typedef struct ID2PARAM
    {
        string Identifier;
        double Value;
    };
    
private:
    /**
     *
     */
    string mName;

    /**
     *
     */
    string mChemEq;

    /**
     *
     */
    CKinFunction * mFunction;

    /**
     *
     */
    double mFlux;

    /**
     *
     */
    short mReversible;

    /**
     *
     */
    vector < ID2METAB > mSubstrates;

    /**
     *
     */
    vector < ID2METAB > mProducts;

    /**
     *
     */
    vector < ID2METAB > mModifiers;

    /**
     *
     */
    vector < ID2PARAM > mParameters;

    /**
     *
     */
    vector < double * > mIdentifiers;

    /**
     *
     */
    long mFail;
// Operations
public:
    /**
     *
     */
    CStep();

    /**
     *
     */
    CStep(const string & name);

    /**
     *
     */
    ~CStep();

    /**
     *
     */
    CStep & operator=(const CStep & rhs);

    /**
     *
     */
    long Load(CReadConfig & configbuffer);

    /**
     *
     */
    long Save(CWriteConfig & configbuffer);

    /**
     *
     */
    vector < ID2METAB > &Substrates();

    /**
     *
     */
    vector < ID2METAB > &Products();

    /**
     *
     */
    vector < ID2METAB > &Modifiers();

    /**
     *
     */
    vector < ID2PARAM > &Parameters();

    /**
     *
     */
    string GetName();

    /**
     *
     */
    string GetChemEq();

    /**
     *
     */
    CKinFunction & GetFunction();

    /**
     *
     */
    double GetFlux();

    /**
     *
     */
    short IsReversible();

    /**
     *
     */
    long SetName(const string & name);

    /**
     *
     */
    long SetChemEq(const string & chemEq);

    /**
     *
     */
    long SetFunction(const string & functionName);

    /**
     *
     */
    long SetFlux(double flux);

    /**
     *
     */
    long SetReversible(short reversible);

    /**
     *
     */
    long Compile(CCopasiVector < CMetab * > & metabolites);
    
private:
    /**
     *
     */
    long InitIdentifiers();

    /**
     *
     */
    long SetIdentifiers();

    /**
     *
     */
    long CheckIdentifiers();
};

#endif // COPASI_CSteb
