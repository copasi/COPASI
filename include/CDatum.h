// CDatum
// 
// Derived from Gepasi's CDatum.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

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
#define D_T		14	// simulation time
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

// CDatum objects reference a variable of type double
class CDatum
{
// Implementation
public:
    CDatum();
    CDatum(const string& title, int type, const string& i, const string& j,
           double *pval);
    CDatum& operator=(CDatum &ptRHS);
    int Save(ostream* pfout);
    int Load(CReadConfig* pconfigbuffer);
    void CDatum::SetValue(double* pvalue);
    double CDatum::GetValue();
    void CDatum::SetI(const string& str);
    string CDatum::GetI();
    void CDatum::SetJ(const string& str);
    string CDatum::GetJ();
    void CDatum::SetType(int type);
    int CDatum::GetType();
    void CDatum::SetTitle(const string& str);
    string CDatum::GetTitle();

private:
    string mTitle;  // string to be written as column title
    int mType;      // type of object
    string mI;      // (name of) first object
    string mJ;      // (name of) second object
    double *mpValue; // pointer to the variable with the value
    int    mFail;   // failure status
};

#endif // COPASI_CDatum