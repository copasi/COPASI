/**
 *  CSteb class.
 *  Derived from Gepasi's cstep.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CStep
#define COPASI_CSteb

#include <string>

#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CKinFunction.h"

class CStep
{
public:
    CStep();
    CStep(string &stepname, long subs, long prods);
    ~CStep();
    CStep &operator=(const CStep &);    // overloaded assignment operator
    long Assign(string &stepname, 
                string &chemeq, 
                string &ktype, 
                long subs, long prods, long mods, 
                double flux, 
                short rev);
    long Save(CWriteConfig &configbuffer);
    long Load(CReadConfig &configbuffer);
    void AddSubstrate(long index);
    void AddProduct(long index);
    void AddModifier(long index);
    void AddParameter(double constant);
    void EraseSubstrates(long index);
    void EraseProducts(long index);
    void EraseModifiers(long index);
    void EraseParameters(double constant);
    string GetChemEq(void);
    long SubstrateNo(void);
    CNodeK Substrate(long index);
    

private:
    void DeAlloc(void);
    void AllocStep(long subs, long prods);
    string mName;                   // step (enzyme) name
    string mChemEq;                 // chemical equation
    CKinFunction *mKinetics;        // kinetic function of this step
    string mKinType;                // name of the kinetic type
    double mFlux;                   // net rate through this step
    short mReversible;              // 1 if reaction is reversible
    vector < long > mSubstrates;    // dynamic array of indexes to substrates
    vector < long > mProducts;      // dynamic array of indexes to products
    vector < long > mModifiers;     // dynamic array of indexes to modifiers
    vector < double > mParameters;  // dynamic array of kinetic parameter values
};
#endif // COPASI_CSteb
