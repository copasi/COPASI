/*****************************************************************************
 * PROGRAM NAME: CDatum.h
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Define the basic output object for Copasi
 *****************************************************************************/

#ifndef COPASI_CDatum
#define COPASI_CDatum

#include <string>

#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "model/CModel.h"

// symbols for CDatum type
#define D_UNDEF 0 // undefined
#define D_ICONC 1 // initial concentrations
#define D_SCONC 2 // steady-state concentrations
#define D_TCONC 3 // transient concentrations
#define D_SFLUX 4 // steady-state fluxes
#define D_TFLUX 5 // transient fluxes
#define D_KIN 6 // kinetic constants
#define D_ELAST 7 // elasticities
#define D_CCC 8 // concentration-control coefficients
#define D_FCC 9 // flux control coefficients
#define D_TT 10 // transition times
#define D_EIG 11 // eigenvalues of the Jacobian
#define D_VOL 12 // compartment volumes
#define D_MOIT 13 // conservation relations
#define D_T 14 // simulation time
#define D_INTS 15 // counter of integration steps
#define D_FEVAL 16 // counter of function evaluations
#define D_JEVAL 17 // counter of jacobian evaluations
#define D_SSIZE 18 // last step size
#define D_RTOL 19 // relative tolerance
#define D_ATOL 20 // absolute tolerance
#define D_SSRES 21 // steady-state resolution
#define D_DERIV 22 // derivation factor
#define D_RT 23 // real (elapsed) time
#define D_UFUNC 24 // user defined function
#define D_ENDT 25 // integration end time
#define D_POINT 26 // integration sampling points
#define D_EIGMR 27 // largest real part eigenvalues
#define D_EIGMI 28 // largest absolute imag. part
#define D_EIGPR 29 // total pos. real parts
#define D_EIGNR 30 // total neg. real parts
#define D_EIGR  31 // total real eigenvalues
#define D_EIGI  32 // total imaginary eigenvalues
#define D_EIGC  33 // total complex eigenvalues
#define D_EIGZ  34 // total zero eigenvalues
#define D_THIER 35 // Time hierarchy
#define D_STIFF 36 // stiffness (ratio of larger to smaller Re)
#define D_EIGVR 37 // real part of eigenvalues
#define D_EIGVI 38 // imaginary part of eigenvalues

// Symbols for mType
#define CINT16  1
#define CINT32  2
#define CFLOAT32 3
#define CFLOAT64 4

class CState;
class CSteadyStateTask;

class CDatum
  {
  private:
    /**
     *  Title of the object.
     */
    string mTitle;

    /**
     *  Pointer to the memory location that contains the value of this
     *  object 
     */
    const void * mpValue;

    /**
     *  Type of the object value.
     */
    C_INT32 mType;

    /**
     *  Name of the object.
     */
    string mObject;

    /**
     *  Creates the mObject
     *  @param object constant reference to a string specifing the name of the 
     *  model this datum is in, IStr, JStr, the type of this data, such as D_TCONC.
     */
    void createObject(const string& IStr, const string& JStr, C_INT32 Type);

    /**
     *  Transfers the Type to the associated member data in each class
     *  @Type object constant reference to a type of the datum, for example,D_TCONC
     */
    string transferType(C_INT32 Type);

    /**
     *  Get the object I string part
     *  @object reference to CDatum object
     */
    string getObjectIStr(string object, C_INT16 HasJStr);

    /**
     *  Get the object J string part
     *  @object reference to CDatum object
     */
    string getObjectJStr(string object);

  public:

    /**
     *  Default constructor. 
     *  Creates an empty object with C_INT32 type
     */
    CDatum();

    /**
     *  User Defined constructor. 
     *  Creates an object with contents passed as arguments
     *  @param title: title of the object.
     *  @param value: pointer to the memeory location containing the value of the object.
     *  @param type: type of the object (e.g. C_INT32).
     *  @param object: the name of this object 
     */
    CDatum(const string& title, void* value, C_INT32 type, const string& object);

    /**
     *  cleanup 
     */
    void cleanup();

    /**
     *  Assignement operator. 
     *  Copies the contents from one CDatum object to another.
     *  @param source reference to the recipient object.
     */
    CDatum& operator=(const CDatum &source);

    /**
     *  Returns a string with the title of this object.
     *  @return mTitle
     *  @see mTitle
     */
    string getTitle() const;

    /**
     *  Sets the title of this object
     *  @param title constant reference to a string.
     *  @see mTitle
     */
    void setTitle(const string& title);

    /**
     *  Returns the value of this object.
     *  @return *mpValue
     *  @see mpValue
     */
    const void* getValue() const;

    /**
     *  Sets the value of mpValue with a pointer to a memory location that has 
     *  the value of this object.
     *  @param value constant reference to a void pointer.
     *  @see mpValue
     */
    void setValue(void* value);

    /**
     *  Returns the type of this object.
     *  @return mType
     *  @see mType
     */
    C_INT32 getType() const;

    /**
     *  Sets the type of this object
     *  @param type constant reference to a string specifing the type of this object.
     *  @see mType
     */
    void setType(const C_INT32 type);

    /**
     *  Returns a string with the name of this object.
     *  @return mObject
     *  @see mObject
     */
    string getObject() const;

    /**
     *  Sets the name of this object
     *  @param object constant reference to a string specifing the type of this object.
     *  @see mobject
     */
    void setObject(const string& object);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 save(CWriteConfig & configbuffer);

    /**
     *  Dummy method.
     */
    string getName() const {return "";}

    /**
     *  Complie the mpValue in each CDatum
     */
    void compileDatum(CModel *Model, CState *state, CSteadyStateTask *soln);

    /**
     * Returns the index of a user defined function
     */
    int FindUDFunct(string title);
    /**
     * Dynamically calculate the value of user defined function
     */
    void calcFunc();
    /**
     *  Transfers the associated member data to the Type to  in each class
     *  @Type object constant reference to a type of the datum, for example,D_TCONC
     */
    C_INT32 getObjectType(string Object);
  };

#endif // CDatum
