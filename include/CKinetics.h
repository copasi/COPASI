// CKinetics
// 
// Derived from Gepasi's ckinetic.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops

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
     *  Default constructor
     */
    CKinetics();

    /**
     *  Specific constructor for built-in kinetic types. This will be obsolete 
     *  in the future. Since builtin types will be implemented as user defined
     *  types.
     */
    CKinetics(const string &kiname, 
               int subs, 
               int prods, 
               int mods, 
               int prm, 
               double (*ratefunc)(void *,double *, int), 
               short rev);

    /**
     *  Specific constructor for user defined function.
     *  @param CKinFunction &funct
     */
    CKinetics(CKinFunction &funct);

    /**
     *  Destructor
     */
    ~CKinetics();

    /**
     *  This sets the name of the parameter with the given index
     *  @param "const string" &name
     *  @param int index
     */
    void SetParameterName(const string &name, int idx);

    /**
     *  This sets the name of the modifier with the given index
     *  @param "const string" &name
     *  @param int index
     */
    void SetModifierName(const string &name, int idx);

    /**
     *  This returns the index of the parameter with the given name
     *  @param "const string" &name
     *  @return int index or -1 if not found
     */
    int FindParameter(const string &name);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    int Save(CWriteConfig &configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    int Load(CReadConfig &configbuffer);
private:

    /**
     *  The name of the kinetc type
     */
    string mName;              // name of this kinetic type

    /**
     *  This indicates whether this kinetic type is reversible
     */
    short mReversible;         // kinetic reversibility

    /**
     *  The pointer to the rate function
     */
    double (*mFunction)(void *, double *, int); // pointer to rate function

    /**
     *  The pointer to a user-defined kinetic type
     */
    CKinFunction *mFunct;      // a pointer to a user-defined kinetic type

    /**
     *  Pointer to vector of substrates
     */
    vector < CNodeK * > *mSubstrates;  // number of substrates

    /**
     *  Pointer to vector of products 
     */
    vector < CNodeK * > *mProducts;  // number of products

    /**
     *  Pointer to vector of modifiers 
     */
    vector < CNodeK * > *mModifiers;    // number of modifiers

    /**
     *  Pointer to vector of parameters 
     */
    vector < CNodeK * > *mParameters;          // number of parameters

    /**
     *  This indicates whether the kinetcs type is user defined
     */
    short mUserDefined;        // 1 if user defined
};

#endif // COPASI_CKinetics
