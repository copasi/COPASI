/**
 *  File name: COptimizer.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the interface (.h file) of the COptimizer class. 
 *           It contains the designed abstract interaction between a simulation
 *           subsystem and optimization algorithms. This base class defines
 *           methods by which the simulation subsystem accesses several 
 *           optimization algorithms.
 *  Note: This is an abstract class
 */

#ifndef COPTIMIZER_H
#define COPTIMIZER_H

// YOHE: this is an abstract class that contains many virtual functions 
// without definitions
//
class COptimizer
{

  //data member
 private:
  
  // YOHE: These data members were originally public,
  // but it's better to use them as private
  String mIni;			// INI filename
  String mHelp;			// Help filename
  String mName;		        // Name (descriptive)
  String mVersion;              // Version string
  double *mParam;               // array for parameter values

  int mParamNum;                // the number of parameters
  //char mStatbuffer[256];	// static character string for function returns
  //BOOL mArrayCreated;		// True if DLL is in memory
  BOOL mBounds;			// True if method accepts bounds on the parameters
  BOOL mConstraints;		// True if method accepts constraints on the variable


 // Implementation
 public:

   /**
    * Default constructor
    */
   COptimizer();

   /**
    * Destructor
    */
   ~COptimizer();

   /**
    * Initialization of private variables
    */
   BOOL Init( CString &inifile );


   /**
    * Set algorithm parameters
    */
   void SetAlgoParameters( void );


   /**
    * Set a parameter value
    */
   void SetParameterValue( int p, double v );


   /**
    * Get a parameter value
    */
   double GetParameterValue( int p );

   /**
    * Return the number of parameters
    */
   int CountParameters( void );


   /**
    * Return the name of a parameter
    */
   char * GetParameterName( int p );


   /**
    * Returns True if this method is capable of handling adjustable parameter 
    * boundary constraints, False otherwise
    */
   virtual BOOL IsBounded( void );

   /**
    * Return True if the method is capable of handling general constraints, 
    * False otherwise
    */
   virtual BOOL IsConstrained( void );


   /**
    * Execute the optimization algorithm calling simulation routine 
    * (passed as argument)when needed. It is noted that this procedure 
    * can give feedback of its progress by the callback function set 
    * with SetCallback.
    */
   //virtual int Optimise( double (*func) (void) );
   virtual int Optimise();


   /**
    *  return TRUE if method can do general optimisation
    */
   BOOL CanOptimise( void );


   /**
    * Stores a reference to the procedure that carries out simiulations and
    * then executes the optimization algorithm to solve the problem. 
    * It is noted that this procedure must periodically call the callback 
    * function set with SetCallback.
    */
   //int SolveLsq( double (*func) (double *) );
   virtual int SolveLsq();


   /**
    * return TRUE if method has specialised least-squares solver
    */
   BOOL SpecialisedLsq( void );


};


#endif  // end of real stuff




// begin old trash

#ifdef XXXX

 
  /*     trash  here

  // data members
  public:
   CString Dll;					// DLL filename
   CString Ini;			      		// INI filename
   CString Help;					// Help filename
   CString Name;				        // Name (descriptive)
   CString Version;				// Version string
   double *Param;					// array for parameter values

   HINSTANCE HLib;	     	// handle to the DLL
   BOOL DllLoaded;  	      	// True if DLL is in memory
   int nParam;   		// the number of parameters
   char statbuffer[256];	// static character string for function returns
   BOOL ArrayCreated;		// True if DLL is in memory
   BOOL Bounds;			// True if method accepts bounds on the parameters
   BOOL Constraints;		// True if method accepts constraints on the variable
 
 */




class COptParam;

class COptModule
{
// data members
public:
 CString Dll;					// DLL filename
 CString Ini;			      		// INI filename
 CString Help;					// Help filename
 CString Name;				        // Name (descriptive)
 CString Version;				// Version string
 double *Param;					// array for parameter values
 // DLL functions
 int (WINAPI *DLLCreateArrays) (int p, int c, int nr );
 void (WINAPI *DLLSetConstraint) (int c, COptParam *ct );
 void (WINAPI *DLLSetOptParameter) (int arg1, COptParam *arg2);
 void (WINAPI *DLLName) (char *arg1);
 char * (WINAPI *DLLParameterName) (int arg1, char *arg2);
 int (WINAPI *DLLParameterNumber) (void);
 void (WINAPI *DLLSetMethodParam) (int n, double p ); 
 void (WINAPI *DLLClearMemory) (void);
 double (WINAPI *DLLGetOptParameterValue) (int i);
 double (WINAPI *DLLGetObjF) (void);
 int (WINAPI *DLLIsConstrained) (void);
 int (WINAPI *DLLIsBounded) (void);
 int (WINAPI *DLLRoutines) (void);
 int (WINAPI *DLLVersion) (void);
 void (WINAPI *DLLInit) (void);
 void (WINAPI *DLLSetCallback) ( void (*cb) (double of) );
 int (WINAPI *DLLOptimise) (double (*feval) (void) );
 int (WINAPI *DLLSolveLsq) (double (*feval) (double *res) );

private:
 HINSTANCE HLib;	     	// handle to the DLL
 BOOL DllLoaded;  	      	// True if DLL is in memory
 int nParam;   			// the number of parameters
 char statbuffer[256];		// static character string for function returns
 BOOL ArrayCreated;		// True if DLL is in memory
 BOOL Bounds;			// True if method accepts bounds on the parameters
 BOOL Constraints;		// True if method accepts constraints on the variables

// Implementation
public:
 COptModule();
 ~COptModule();
 BOOL Init( CString &inifile );
 int CountParameters( void );
 double GetParameterValue( int p );
 void SetParameterValue( int p, double v );
 char * GetParameterName( int p );
 int Optimise( double (*func) (void) );
 void SetAlgoParameters( void );
 int SolveLsq( double (*func) (double *) );
 BOOL IsBounded( void );
 BOOL IsConstrained( void );
 BOOL CanOptimise( void );
 BOOL SpecialisedLsq( void );
};


#endif   // XXXX
