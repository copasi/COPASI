/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/output/Attic/CDatum.h,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:25:54 $
   End CVS Header */

/*****************************************************************************
 * PROGRAM NAME: CDatum.h
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Define the basic output object for Copasi
 *****************************************************************************/

#ifndef COPASI_CDatum
#define COPASI_CDatum

#include <string>
#include "copasi.h" 
//#include "utilities/CReadConfig.h"
//#include "utilities/CWriteConfig.h"
//#include "model/CModel.h"
#include "report/CCopasiContainer.h"

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

class CModel;
class CState;
class CSteadyStateTask;
class CReadConfig;
class CWriteConfig;

class CDatum : public CCopasiContainer
  {
  private:
    /**
     *  Title of the object.
     */
    std::string mTitle;

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
    std::string mObjectName;

    /**
     *  Transfers the Type to the associated member data in each class
     *  @Type object constant reference to a type of the datum, for example,D_TCONC
     */
    std::string transferType(C_INT32 Type);

    /**
     *  Get the object I string part
     *  @object reference to CDatum object
     */
    std::string getObjectIStr(std::string object, C_INT16 HasJStr);

    /**
     *  Get the object J string part
     *  @object reference to CDatum object
     */
    std::string getObjectJStr(std::string object);

  public:

    /**
     * Default constructor. 
     * Creates an empty object with C_INT32 type
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CDatum(const std::string & name = "NoName",
           const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor. 
     * @param const CDatum & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CDatum(const CDatum & src,
           const CCopasiContainer * pParent = NULL);

    /**
     * User Defined constructor. 
     * Creates an object with contents passed as arguments
     * @param title: title of the object.
     * @param value: pointer to the memeory location containing the value of the object.
     * @param type: type of the object (e.g. C_INT32).
     * @param object: the name of this object 
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CDatum(const std::string& title,
           void* value, C_INT32 type,
           const std::string& object,
           const CCopasiContainer * pParent = NULL);

    /**
     *  cleanup 
     */
    void cleanup();

    /**
     *  Creates the mObject
     *  @param object constant reference to a string specifing the name of the
     *  model this datum is in, IStr, JStr, the type of this data, such as D_TCONC.
     */
    void createObjectString(const std::string& model, const std::string& IStr, const std::string& JStr, C_INT32 Type);

    /**
     *  Returns a string with the title of this object.
     *  @return mTitle
     *  @see mTitle
     */
    std::string getTitle() const;

    /**
     *  Sets the title of this object
     *  @param title constant reference to a string.
     *  @see mTitle
     */
    void setTitle(const std::string& title);

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
    std::string getObject() const;

    /**
     *  Sets the name of this object
     *  @param object constant reference to a string specifing the type of this object.
     *  @see mobject
     */
    void setObject(const std::string& object);

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
    const std::string & getName() const;

    /**
     *  Complie the mpValue in each CDatum
     */
    void compileDatum(CModel *Model, CState *state, CSteadyStateTask *soln);

    /**
     * Returns the index of a user defined function
     */
    int FindUDFunct(std::string title);
    /**
     * Dynamically calculate the value of user defined function
     */
    void calcFunc();
    /**
     *  Transfers the associated member data to the Type to  in each class
     *  @Type object constant reference to a type of the datum, for example,D_TCONC
     */
    C_INT32 getObjectType(std::string Object);
  };

#endif // CDatum
