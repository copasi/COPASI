/**
 *  CMetab class.
 *  Derived from Gepasi's cmetab.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CMetab
#define COPASI_CMetab

#include <string>

#include "copasi.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CCopasiVector.h"

class CCompartment;

//constants for use with Status
#define METAB_FIXED	0
#define METAB_VARIABLE	1
#define METAB_DEPENDENT	2
#define METAB_MOIETY	7

class CMetabOld;


class CMetab
{
// Attributes
private:
    /**
     *  Name of the metabolite
     */
    string mName;

    /**
     *  Concentration of the metabolite.
     */
    C_FLOAT64 mConc;

    /**
     * Initial concentration of the metabolite
     */
    C_FLOAT64 mIConc;

    /**
     *  Rate of production of this metaboLite
     *  (here used for rate constant).
     */
    C_FLOAT64 mRate; 

    /**
     *  Transition time of the metabolite
     */
    C_FLOAT64 mTT;

    /**
     *  Status of the metabolite.  
     *  One of (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     */
    C_INT16 mStatus;

    /**
     *  pointer to the compartment the metabolite is located in.
     */
    CCompartment  * mCompartment;

// Operations
public:
    /**
     *  Default constructor
     */
    CMetab();

    /**
     *  Specific constructor. 
     *  @param name name of the metabolite.
     */
    CMetab(const string & name);

    /**
     *  Specific constructor.
     *  @param name name of the metabolite.
     *  @param status status of the metabolite 
     *     (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     *  @param compartment name of the compartment the metabolite
     *     is located in.
     */
    // CMetab(const string & compartment, C_INT16 status, CCompartment & name);

    /**
     *  Destructor.
     */
    ~CMetab();

    /**
     *  Assignment operator.
     */
    CMetab & operator=(const CMetab & rhs);

    /**
     *  Assignment operator.
     */
    CMetab & operator=(const CMetabOld & rhs);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 Load(CReadConfig & configbuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 Save(CWriteConfig & configbuffer);

    /**
     *  Retrieve the name of the metabolite.
     */
    string GetName() const;

    /**
     *
     */
    C_FLOAT64 * GetConcentration() {return &mConc;}

    /**
     *
     */
    CCompartment * GetCompartment() {return mCompartment;} 

    /**
     *
     */
    void SetName(const string & name) {mName = name;}

    /**
     *
     */
    void SetConcentration(C_FLOAT64 concentration) {mConc = concentration;}
    
    /**
     *
     */
    void SetCompartment(CCompartment * compartment) {mCompartment = compartment;} 

    /**
     *  Reset the values of a metabolite as if CMetab(string name) was called.
     *  @return Fail
     */
    C_INT32 Reset(const string & name);

private:

    /*
     *
     */
    C_INT16 IsValidName();
};

class CMetabOld
{
    friend class CMetab;
    
// Attributes
private:
    /**
     *  Name of the metabolite
     */
    string mName;

    /**
     *  Concentration of the metabolite.
     */
    C_FLOAT64 mIConc;

    /**
     *  Status of the metabolite.  
     *  One of (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     */
    C_INT16 mStatus;

    /**
     *  pointer to the compartment the metabolite is located in.
     */
    C_INT32  mCompartment;

// Operations
public:
    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 Load(CReadConfig & configbuffer);

    C_INT32 GetIndex();

    string GetName() const;
};

class CMetabolitesOld: public CCopasiVector < CMetabOld >
{
private:
    C_INT16 IsInsertAllowed(const CMetabOld & src) {return TRUE;}
};
  
#endif // COPASI_CMetab
