/** 
 *  CDatum class.
 *  Derived from Gepasi's CDatum.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for Copasi by Pedro Mendes.
 */

// CDatum is not yet finished: because all data are now private, we will need 
// to add a few more methods (perhaps not in this class, though - thus it is
// best to wait until we hit the problem in CGepasiDoc.   PEDRO 1/11/01

#ifndef COPASI_CDatum
#define COPASI_CDatum

// symbols for CDatum type
#define D_UNDEF	0	// undefined
#define D_ICONC	1	// initial concentrations
#define D_SCONC 2	// steady-state concentrations
#define D_TCONC	3	// transient concentrations
#define D_SFLUX	4	// steady-state fluxes
#define D_TFLUX 5	// transient fluxes
#define D_KIN	6	// kinetic constants
#define D_ELAST	7	// elasticities
#define D_CCC	8	// concentration-control coefficients
#define D_FCC	9	// flux control coefficients
#define D_TT	10	// transition times
#define D_EIG	11	// eigenvalues of the Jacobian
#define D_VOL	12	// compartment volumes
#define D_MOIT	13	// conservation relations
#define D_T	14	// simulation time
#define D_INTS	15	// counter of integration steps
#define D_FEVAL	16	// counter of function evaluations
#define D_JEVAL	17	// counter of jacobian evaluations
#define D_SSIZE 18	// last step size
#define D_RTOL	19	// relative tolerance
#define D_ATOL	20	// absolute tolerance
#define D_SSRES	21	// steady-state resolution
#define D_DERIV	22	// derivation factor
#define D_RT	23	// real (elapsed) time
#define D_UFUNC	24	// user defined function
#define D_ENDT	25	// integration end time
#define D_POINT	26	// integration sampling points
#define D_EIGMR	27	// largest real part eigenvalues
#define D_EIGMI	28	// largest absolute imag. part
#define D_EIGPR	29	// total pos. real parts
#define D_EIGNR	30	// total neg. real parts
#define D_EIGR 	31	// total real eigenvalues
#define D_EIGI 	32	// total imaginary eigenvalues
#define D_EIGC 	33	// total complex eigenvalues
#define D_EIGZ 	34	// total zero eigenvalues
#define D_THIER 35	// Time hierarchy
#define D_STIFF	36	// stiffness (ratio of larger to smaller Re )
#define D_EIGVR 37	// real part of eigenvalues
#define D_EIGVI 38	// imaginary part of eigenvalues

// CDatum objects reference model objects of type C_FLOAT64
class CDatum
{
// Implementation
public:

    /**
     *  Default constructor. 
     *  Creates an empty object with type D_UNDEF
     */
    CDatum();

    /**
     *  Specified constructor. 
     *  Creates an object with contents passed as arguments
     *  @param title title of the object.
     *  @param type type of the object (e.g. D_ICONC).
     *  @param i first string describing the object.
     *  @param j second string describing the object.
     *  @param pval pointer to C_FLOAT64 containing the value of the object.
     */
    CDatum(const string& title, C_INT32 type, const string& i, const string& j,
           C_FLOAT64 *pval);

    /**
     *  Assignement operator. 
     *  Copies the contents from one CDatum object to another.
     *  @param ptRHS reference to the recipient object.
     */
    CDatum& operator=(const CDatum &RHS);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 Save(CWriteConfig &configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 Load(CReadConfig &configbuffer);

    /**
     *  Sets the value of mpValue with a pointer to a C_FLOAT64 that has 
     *  the value of this object.
     *  @param pvalue pointer to a C_FLOAT64.
     */
    void CDatum::SetValue(C_FLOAT64* pvalue);

    /**
     *  Returns a C_FLOAT64 with the value of this object.
     *  @return *mpValue
     *  @see mpValue
     */
    C_FLOAT64 CDatum::GetValue();

    /**
     *  Sets the value of mI with a string
     *  @param str constant reference to a string.
     *  @see mI
     */
    void CDatum::SetI(const string& str);

    /**
     *  Returns the first string describing this object.
     *  @return mI
     *  @see mI
     */
    string CDatum::GetI();

    /**
     *  Sets the value of mJ with a string
     *  @param str constant reference to a string.
     *  @see mJ
     */
    void CDatum::SetJ(const string& str);

    /**
     *  Returns the second string describing this object.
     *  @return mJ
     *  @see mJ
     */
    string CDatum::GetJ();

    /**
     *  Sets the type of this object
     *  @param type integer code of the type
     *  @see mType
     */
    void CDatum::SetType(C_INT32 type);

    /**
     *  Returns the type code of this object.
     *  @return mType
     *  @see mType
     */
    C_INT32 CDatum::GetType();

    /**
     *  Sets the title of this object
     *  @param str constant reference to a string.
     *  @see mTitle
     */
    void CDatum::SetTitle(const string& str);

    /**
     *  Returns a string with the title of this object.
     *  @return mTitle
     *  @see mTitle
     */
    string CDatum::GetTitle();

private:
    /**
     *  Title of the object.
     */
    string mTitle;

    /**
     *  Type code of the object.
     *  Codes are currently integer constants referenced with
     *  pre-compiler defined symbols of the form D_????? (e.g. D_ICONC).
     *  This could possibly be changed to a enum set (need to think about
     *  portability issues, related with data alignment
     */
    C_INT32 mType;

    /**
     *  First descriptor of the object.
     *  For example: if the object is "control of Hexokinase by Glucose",
     *  mI is set to the string "Hexokinase"
     */
    string mI;


    /**
     *  Second descriptor of the object.
     *  For example: if the object is "control of Hexokinase by Glucose",
     *  mJ is set to the string "Glucose"
     */
    string mJ;


    /**
     *  Pointer to the memory location that contains the value of this
     *  object (a C_FLOAT64)
     */
    C_FLOAT64 *mpValue;

    /**
     *  Failure status:
     *  0 = no error
     *  !0 = error
     */
    C_INT32    mFail;
};

#endif // COPASI_CDatum
