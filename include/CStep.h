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
    friend CStep;
    // Attributes
    private:
        string mIdentifierName;
        string mMetaboliteName;
        string mCompartmentName;
        CMetab *mpMetabolite;
    };
    
    class CId2Param
    {
    friend CStep;
    // Attributes
    private:
        string mIdentifierName;
        double mValue;
    };
    
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
    vector < CId2Metab > mSubstrates;

    /**
     *
     */
    vector < CId2Metab > mProducts;

    /**
     *
     */
    vector < CId2Metab > mModifiers;

    /**
     *
     */
    vector < CId2Param > mParameters;

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
    vector < CId2Metab > &Substrates();

    /**
     *
     */
    vector < CId2Metab > &Products();

    /**
     *
     */
    vector < CId2Metab > &Modifiers();

    /**
     *
     */
    vector < CId2Param > &Parameters();

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
    void SetName(const string & name);

    /**
     *
     */
    void SetChemEq(const string & chemEq);

    /**
     *
     */
    void SetFunction(const string & functionName);

    /**
     *
     */
    void SetFlux(double flux);

    /**
     *
     */
    void SetReversible(short reversible);

    /**
     *
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
