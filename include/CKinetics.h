// CKinetics.h : interface of the CKinetics class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPASI_CKinetics
#define COPASI_CKinetics

#include <string>

#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CKinFunction.h"

class CKinetics
{
// Implementation
public:

    /**
     *
     */
    CKinetics();

    /**
     *
     */
    CKinetics(const string &kiname, 
               int subs, 
               int prods, 
               int mods, 
               int prm, 
               double (*ratefunc)(void *,double *, int), 
               short rev);

    /**
     *
     */
    CKinetics(CKinFunction &funct);

    /**
     *
     */
    ~CKinetics();

    /**
     *
     */
    void SetParameterName(const string &name, int idx);

    /**
     *
     */
    void SetModifierName(const string &name, int idx);

    /**
     *
     */
    int FindParameter(const string &name);

    /**
     *
     */
    void Save(CWriteConfig &configbuffer);

    /**
     *
     */
    int CKinetics::Load(CReadConfig &configbuffer);
private:

    /**
     *
     */
    string mName;              // name of this kinetic type

    /**
     *
     */
    short mReversible;         // kinetic reversibility

    /**
     *
     */
    double (*mFunction)(void *, double *, int); // pointer to rate function

    /**
     *
     */
    CKinFunction *mFunct;      // a pointer to a user-defined kinetic type

    /**
     *
     */
    vector < CNodeK * > *mSubstrates;  // number of substrates

    /**
     *
     */
    vector < CNodeK * > *mProducts;  // number of products

    /**
     *
     */
    vector < CNodeK * > *mModifiers;    // number of modifiers

    /**
     *
     */
    vector < CNodeK * > *mParameters;          // number of parameters

    /**
     *
     */
    short mUserDefined;        // 1 if user defined
};

#endif // COPASI_CKinetics
