/**
 * CODESolver
 * 
 * (C) Pedro Mendes 2001, based on code in Gepasi (C) Pedro Mendes 1990-2000
 */
#ifndef COPASI_CODESolver
#define COPASI_CODESolver

#include "CReadConfig.h"
#include "CWriteConfig.h"

class CODESolver
{
// Attributes
private:
    /**
     *  Name of the ODE solver.
     */
    string mName;
    CVersion mVersion(1,0,101);
    int mMethod;
// Operations
public:
    /**
     *  Default constructor. 
     */
    CODESolver();

    /**
     *  Destructor. 
     *  The destructor does nothing.
     */
    ~CODESolver();

    /**
     *  Loads parameters for this solver with data coming from a 
     *  CReadConfig object. (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    long Load(CReadConfig & configbuffer);

    /**
     *  Saves the parameters of the solver to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    long Save(CWriteConfig & configbuffer);

    /**
     *  Returns a string with the name of this solver.
     *  @return mName
     *  @see mName
     */
    string GetName();

    
private:

};

#endif // CODESolver

