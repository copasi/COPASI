// CCompartment
// 
// Derived from Gepasi's ccompart.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#ifndef COPASI_CComparment
#define COPASI_CComparment

class CCompartment
{
public:
    /**
     *  Default constructor. 
     *  Creates an empty object with mName="compartment" and mVolume=1
     */
    CCompartment();

    /**
     *  Specified constructor. 
     *  Creates an object with contents passed as arguments
     *  @param name name of the comnpartment.
     *  @param volume volume of the compartment.
     */
    CCompartment(string name, double volume);

    /**
     *  Destructor. 
     *  The destructor does nothing.
     */
    ~CCompartment();

    /**
     *  Assignement operator. 
     *  Copies the contents from one CCompartment object to another.
     *  @param ptRHS reference to the recipient object.
     */
    CCompartment &operator=(const CCompartment &);

    /**
     *  Returns a string with the name of this compartment.
     *  @return mName
     *  @see mName
     */
    string GetName(void);

    /**
     *  Sets the name of this compartment.
     *  @param name string with the name of the compartment.
     *  @see mName
     */
    void SetName(string& name);

    /**
     *  Returns a double with the volume of this compartment.
     *  @return mVolume
     *  @see mVolume
     */
    double GetVolume(void);

    /**
     *  Sets the volume of this compartment.
     *  @param volume the volume of the compartment.
     *  @see mVolume
     */
    void SetVolume(double volume);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    int Save(CWriteConfig &configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    int Load(CReadConfig &configbuffer);

    /**
     *  Returns the failure code.
     *  @return mFail
     *  @see mFail
     */
    int Fail();

private:
    /**
     *  Name of the compartment.
     */
    string mName;

    /**
     *  Volume of the compartment.
     */
    double mVolume;

    /**
     *  Failure code.
     */
    int    mFail;
};

class CCompartmentVector : public vector< CCompartment >
{
public:
    /**
     *  Default constructor. 
     *  Creates an empty vector with size 0.
     */
    CCompartmentVector();

    /**
     *  Specific constructor. 
     *  Creates a vector with size CCompartment.
     *  @param size number of CCompartment objectss in the vector.
     */
    CCompartmentVector(int size);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    int Save(CWriteConfig &configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    int Load(CReadConfig &configbuffer);
    
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
#endif // COPASI_CComparment

