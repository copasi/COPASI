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
    CCompartment &operator=(CCompartment &);

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
     *  Saves the contents of the object to an output stream.
     *  (output stream is usually a file but can also be a socket)
     *  @param pfout pointer to the output stream (ostream).
     *  @return mFail
     *  @see mFail
     */
    int Save(ostream* pfout);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer pointer to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    int Load(CReadConfig* pconfigbuffer);

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
#endif // COPASI_CComparment
