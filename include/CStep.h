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
#include "CKinetics.h"

class CStep
{
public:
    CStep &operator=(CStep &);    // overloaded assignment operator
    CStep();
    CStep(string &stepname, int subs, int prods);
    ~CStep();
    int Assign(string &stepname, 
               string &chemeq, 
               string &ktype, 
               int subs, int prods, int mods, 
               double flux, 
               short rev);
//    void SizeParam(int howmany);
//    void SizeModifier(int howmany);
    int Save(CWriteConfig &configbuffer);
    int Load(CReadConfig &configbuffer);
    void AddSubstrate(int index);
    void AddProduct(int index);
    void AddModifier(int index);
    void AddParameter(double constant);
    void EraseSubstrates(int index);
    void EraseProducts(int index);
    void EraseModifiers(int index);
    void EraseParameters(double constant);

private:
    void DeAlloc(void);
    void AllocStep(int subs, int prods);
    string mName;                   // step (enzyme) name
    string mChemEq;                 // chemical equation
    CKinetics *mKinetics;           // kinetic function of this step
    string mKinType;                // name of the kinetic type
    double mFlux;                   // net rate through this step
    short mReversible;              // 1 if reaction is reversible
    vector < int > mSubstrates;    // dynamic array of indexes to substrates
    vector < int > mProducts;      // dynamic array of indexes to products
    vector < int > mModifiers;     // dynamic array of indexes to modifiers
    vector < double > mParameters; // dynamic array of kinetic parameter values
};
#endif // COPASI_CSteb
