// CMetab
// 
// Derived from Gepasi's cmetab.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops

#ifndef COPASI_CMetap
#define COPASI_CMetab

//constants for use with Status
#define METAB_FIXED	0
#define METAB_VARIABLE	1
#define METAB_DEPENDENT	2
#define METAB_MOIETY	7

class CMetab
{
public:
    /**
     *  Default constructor
     */
    CMetab();

    /**
     *  Specific constructor. 
     *  @param name name of the metabolite.
     */
    CMetab(string name);

    /**
     *  Specific constructor.
     *  @param name name of the metabolite.
     *  @param status status of the metabolite 
     *     (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     *  @param compartment reference to the compartment the metabolite
     *     is located.
     */
    CMetab(string name, short status, CCompartment &compartment);

    /**
     *  Assignment operator.
     */
    CMetab &operator=( const CMetab & );          // overloaded assignment operator

    /**
     *  Reset the values of a metabolite as if CMetab(string name) was called.
     */
    int Reset(string name);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    int Save(CWriteConfig &configbuffer, 
             CCompartmentVector &list);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    int Load(CReadConfig &configbuffer, 
             CCompartmentVector &list);

    /**
     *  Returns the failure code.
     *  @return mFail
     *  @see mFail
     */
    int Fail();

private:
    /**
     *  Name of the metabolite
     */
    string mName;        // metabolite name

    /**
     *  Concentration of the metabolite.
     */
    double mConc;        // concentration of the metabolite

    /**
     * Initial concentration of the metabolite
     */
    double mIConc;       // initial concentration of the metabolite

    /**
     *  Rate of production of this metaboLite
     */
    double mRate;        // rate of production of this metaboLite 
                         // (HERE USED FOR RATE CONSTANT)

    /**
     *  Transition time of the metabolite
     */
    double mTT;          // transition time of the metabolite

    /**
     *  Status of the metabolite 
     *     (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
     */
    short  mStatus;       // if external, variable, dependent, etc.

    /**
     *  Pointer to the compartment the metabolite is located.
     */
    CCompartment *Compartment;        // the compartment of this metabolite
                        // special variables only for ModEx
    /**
     *  Failure code.
     */
    int    mFail;
};

class CMetabVector : public vector< CMetab >
{
public:
    /**
     *  Default constructor. 
     *  Creates an empty vector with size 0.
     */
    CMetabVector();

    /**
     *  Specific constructor. 
     *  Creates a vector with size CMetab.
     *  @param size number of CMetab objects in the vector.
     */
    CMetabVector(int size);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    int Save(CWriteConfig &configbuffer,
             CCompartmentVector &list);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    int Load(CReadConfig &configbuffer,
             CCompartmentVector &list);
    
    /**
     *  Returns the failure code.
     *  @return mFail
     *  @see mFail
     */
    int Fail();

private:

    /**
     *  Failure code.
     */
    int    mFail;
};
#endif // COPASI_CMetab
