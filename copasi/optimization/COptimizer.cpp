/**
 *  File name: COptimizer.cpp
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the implementation (.cpp file) of the COptimizer class. 
 *           It contains the designed abstract interaction between a simulation
 *           subsystem and optimization algorithms. This base class defines
 *           methods by which the simulation subsystem accesses several 
 *           optimization algorithms. 
 */
#include <math.h>
#include "COptimizer.h"



// Default constructor
COptimizer::COptimizer()
{

  mParam = NULL;
  //reset numeric parameters
  mParamNum = 0;
  //reset the static character buffer
  //mStatBuffer[0] = '\0';

}

//YOHE: seems virtual cannot be outside of class declaration
COptimizer::~COptimizer()
{ }

// Initialization of private variables
bool COptimizer::Init( string &inifile )
{
  /*
 char buffer[4096];
 int res, i;
 CString TmpStr;
 // check if this object had been initialised before and clear it
 if( DllLoaded ) FreeLibrary( HLib );
 DllLoaded = FALSE;
 if( ArrayCreated && (Param!=NULL) )
 {
//  TRACE("deleting Param member of COptModule\n");
  delete [] Param;
 }
 ArrayCreated = FALSE;
 Param = NULL;
 // store the name of the ini file
 Ini = inifile;
 // get directory of ini filename
 TmpStr = Ini;
 res = TmpStr.ReverseFind('\\');
 TmpStr = TmpStr.Left(res+1);
 // get the DLL name
 GetPrivateProfileString( "MODULE", "DLL", "not found", buffer,(DWORD) 4096, LPCTSTR(Ini) );
 Dll = TmpStr + buffer;
 // get the Help name
 GetPrivateProfileString( "MODULE", "Help", "not found", buffer,(DWORD) 4096, LPCTSTR(Ini) );
 Help = TmpStr + buffer;
 // load the DLL
 if( ( HLib = LoadLibrary( LPCTSTR(Dll) ) ) == NULL ) return FALSE;
 // mark the DLL has been loaded
 DllLoaded = TRUE;
 // point to the DLL functions
 if( (DLLName = ( void (PASCAL *)(char*) ) GetProcAddress(HLib, "OptDLLName") ) == NULL )
  return FALSE;
 if( (DLLParameterName = ( char* (PASCAL *)(int,char*) ) GetProcAddress(HLib, "OptDLLParameterName") ) == NULL )
  return FALSE;
 if( (DLLParameterNumber = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLParameterNumber") ) == NULL )
  return FALSE;
 if( (DLLSetMethodParam = ( void (PASCAL *)(int, double) ) GetProcAddress(HLib, "OptDLLSetMethodParameter") ) == NULL )
  return FALSE;
 if( (DLLCreateArrays = ( int (PASCAL *)(int, int, int) ) GetProcAddress(HLib, "OptDLLCreateArrays") ) == NULL )
  return FALSE;
 if( (DLLSetOptParameter = ( void (PASCAL *)(int, COptParam *) ) GetProcAddress(HLib, "OptDLLSetOptParam") ) == NULL )
  return FALSE;
 if( (DLLSetConstraint = ( void (PASCAL *)(int, COptParam *) ) GetProcAddress(HLib, "OptDLLSetConstr") ) == NULL )
  return FALSE;
 if( (DLLClearMemory = ( void (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLClearMemory") ) == NULL )
  return FALSE;
 if( (DLLGetOptParameterValue = ( double (PASCAL *)(int) ) GetProcAddress(HLib, "OptDLLGetOptParameter") ) == NULL )
  return FALSE;
 if( (DLLGetObjF = ( double (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLGetObjF") ) == NULL )
  return FALSE;
 if( (DLLVersion = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLVersion") ) == NULL )
  return FALSE;
 if( (DLLIsConstrained = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLIsConstrained") ) == NULL )
  return FALSE;
 if( (DLLIsBounded = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLIsBounded") ) == NULL )
  return FALSE;
 if( (DLLRoutines = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLRoutines") ) == NULL )
  return FALSE;
 if( (DLLSetCallback = ( void (PASCAL *)( void(*)(double) ) ) GetProcAddress(HLib, "OptDLLSetCallback") ) == NULL )
  return FALSE;
 if( (DLLInit = ( void (PASCAL *)( void ) ) GetProcAddress(HLib, "OptDLLInit") ) == NULL )
  return FALSE;
 if( (DLLOptimise = ( int (PASCAL *)(double(*)(void)) ) GetProcAddress(HLib, "OptDLLOptimise") ) == NULL )
  return FALSE;
 if( (DLLSolveLsq = ( int (PASCAL *)(double(*)(double *)) ) GetProcAddress(HLib, "OptDLLSolveLsq") ) == NULL )
  return FALSE;

 // store the name of this DLL
 DLLName( buffer );
 Name = buffer;
 // the number of parameters
 nParam = DLLParameterNumber();
 // does it deal with bounds?
 if( DLLIsBounded() ) Bounds = TRUE; else Bounds = FALSE;
 // does it deal with constraints?
 if( DLLIsConstrained() ) Constraints = TRUE; else Constraints = FALSE;
 // create the array for the parameter values
 Param = new double[nParam];
 if( Param!=NULL ) ArrayCreated = TRUE; 
 else ArrayCreated = FALSE;
 // load the default values of the parameters
 for( i=0; i<nParam; i++ )
 {
  // get the default values from the ini file
  TmpStr.Format( "PARAMETER%1d", i );
  GetPrivateProfileString( "PARAMETERS", LPCTSTR( TmpStr ), "0.0", buffer,(DWORD) 4096, LPCTSTR(Ini) );
  sscanf( buffer, "%lf", &(Param[i]) );
 }
 // make the version number
 int nV = DLLVersion();
 float fDV = (float) (1000.0 * ( nV * 0.001 - floor( nV * 0.001 ) ));
 float fV = (float) (nV * 0.00001 - 0.01 * ( nV * 0.001 - floor( nV * 0.001 ) ));
 if( fDV >= 300.0 )
  Version.Format( "%.2f", fV );
 else
 {
  if( fDV<200 )
   Version.Format( "%.2f %s %.0f", fV, "alpha", fDV-100.0 );
  else
   Version.Format( "%.2f %s %.0f", fV, "beta", fDV-200.0 );
 }
 return TRUE;
  */
}

//
int COptimizer::CountParameters( void )
{
  return mParamNum;
}

//
double COptimizer::GetParameterValue( int p )
{ 
  return mParam[p];
}

//
void COptimizer::SetParameterValue( int p, double v )
{
 mParam[p] = v;

}

//
char * COptimizer:: GetParameterName( int p )
{
  // old code:
  //  statbuffer[0] = '\0';
  //return DLLParameterName( p, statbuffer );

  //new:  
  return & mStatBuffer[p];             // ???????????????????
}


//
void COptimizer::SetAlgoParameters( void )
{
  //for(int i=0; i<mParamNum; i++ )
   //  DLLSetMethodParam( i, mParam[i] );
}



// Returns True if this method is capable of handling adjustable parameter boundary
// constraints, False otherwise
bool COptimizer::IsBounded( void )
{
  return mBounds;

}

// Return True if the method is capable of handling general constraints, 
// False otherwise
bool COptimizer::IsConstrained( void )
{
  return mConstraints;
}


// YOHE: declare it as abstract function in .h file
//
// Execute the optimization algorithm calling simulation routine (passed as argument)
// when needed. It is noted that this procedure can give feedback of its progress by 
// the callback function set with SetCallback
//virtual int COptimizer::Optimise( double (*func) (void) )
int COptimizer::Optimise(void)
{
  return 0;
}

// return TRUE if method can do general optimisation
bool COptimizer::CanOptimise( void )
{
  if ( Optimise() == 1 )
    return TRUE;
  else
    return FALSE;

}


// Stores a reference to the procedure that carries out simiulations and then executes
// the optimization algorithm to solve the problem. It is noted that this procedure 
// must periodically call the callback function set with SetCallback.
//int COptimizer::SolveLsq( double (*func) (double *) )
int COptimizer::SolveLsq(void)
{
  return 0;
}



//return TRUE if method has specialised least-squares solver
bool COptimizer::SpecialisedLsq( void )
{
  if (SolveLsq() == 1)
    return TRUE;
  else 
    return FALSE;
}


// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#ifdef XXXX

/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "optmod.h"

/////////////////////////////////////////////////////////////////////////////
// COptModul

// create an empty COptModul object
COptModule::COptModule()
{
 // DLL is not yet loaded
 DllLoaded = FALSE;
 // Array is not yet created
 ArrayCreated = FALSE;
 Param = NULL;
 // make sure the strings are empty
 Dll.Empty();
 Ini.Empty();
 Help.Empty();
 Name.Empty();
 Version.Empty();
 // reset numeric parameters
 nParam = 0;
 // reset the static character buffer
 statbuffer[0] = '\0';
}

// destroy a COptModul object
COptModule::~COptModule()
{
// TRACE("destroying COptModule object\n");
 if( DllLoaded ) FreeLibrary( HLib );
 if( ArrayCreated && (Param!=NULL) ) delete [] Param;
}

// create and initialise an COptModul object
BOOL COptModule::Init( CString &inifile )
{
 char buffer[4096];
 int res, i;
 CString TmpStr;
 // check if this object had been initialised before and clear it
 if( DllLoaded ) FreeLibrary( HLib );
 DllLoaded = FALSE;
 if( ArrayCreated && (Param!=NULL) )
 {
//  TRACE("deleting Param member of COptModule\n");
  delete [] Param;
 }
 ArrayCreated = FALSE;
 Param = NULL;
 // store the name of the ini file
 Ini = inifile;
 // get directory of ini filename
 TmpStr = Ini;
 res = TmpStr.ReverseFind('\\');
 TmpStr = TmpStr.Left(res+1);
 // get the DLL name
 GetPrivateProfileString( "MODULE", "DLL", "not found", buffer,(DWORD) 4096, LPCTSTR(Ini) );
 Dll = TmpStr + buffer;
 // get the Help name
 GetPrivateProfileString( "MODULE", "Help", "not found", buffer,(DWORD) 4096, LPCTSTR(Ini) );
 Help = TmpStr + buffer;
 // load the DLL
 if( ( HLib = LoadLibrary( LPCTSTR(Dll) ) ) == NULL ) return FALSE;
 // mark the DLL has been loaded
 DllLoaded = TRUE;
 // point to the DLL functions
 if( (DLLName = ( void (PASCAL *)(char*) ) GetProcAddress(HLib, "OptDLLName") ) == NULL )
  return FALSE;
 if( (DLLParameterName = ( char* (PASCAL *)(int,char*) ) GetProcAddress(HLib, "OptDLLParameterName") ) == NULL )
  return FALSE;
 if( (DLLParameterNumber = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLParameterNumber") ) == NULL )
  return FALSE;
 if( (DLLSetMethodParam = ( void (PASCAL *)(int, double) ) GetProcAddress(HLib, "OptDLLSetMethodParameter") ) == NULL )
  return FALSE;
 if( (DLLCreateArrays = ( int (PASCAL *)(int, int, int) ) GetProcAddress(HLib, "OptDLLCreateArrays") ) == NULL )
  return FALSE;
 if( (DLLSetOptParameter = ( void (PASCAL *)(int, COptParam *) ) GetProcAddress(HLib, "OptDLLSetOptParam") ) == NULL )
  return FALSE;
 if( (DLLSetConstraint = ( void (PASCAL *)(int, COptParam *) ) GetProcAddress(HLib, "OptDLLSetConstr") ) == NULL )
  return FALSE;
 if( (DLLClearMemory = ( void (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLClearMemory") ) == NULL )
  return FALSE;
 if( (DLLGetOptParameterValue = ( double (PASCAL *)(int) ) GetProcAddress(HLib, "OptDLLGetOptParameter") ) == NULL )
  return FALSE;
 if( (DLLGetObjF = ( double (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLGetObjF") ) == NULL )
  return FALSE;
 if( (DLLVersion = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLVersion") ) == NULL )
  return FALSE;
 if( (DLLIsConstrained = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLIsConstrained") ) == NULL )
  return FALSE;
 if( (DLLIsBounded = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLIsBounded") ) == NULL )
  return FALSE;
 if( (DLLRoutines = ( int (PASCAL *)(void) ) GetProcAddress(HLib, "OptDLLRoutines") ) == NULL )
  return FALSE;
 if( (DLLSetCallback = ( void (PASCAL *)( void(*)(double) ) ) GetProcAddress(HLib, "OptDLLSetCallback") ) == NULL )
  return FALSE;
 if( (DLLInit = ( void (PASCAL *)( void ) ) GetProcAddress(HLib, "OptDLLInit") ) == NULL )
  return FALSE;
 if( (DLLOptimise = ( int (PASCAL *)(double(*)(void)) ) GetProcAddress(HLib, "OptDLLOptimise") ) == NULL )
  return FALSE;
 if( (DLLSolveLsq = ( int (PASCAL *)(double(*)(double *)) ) GetProcAddress(HLib, "OptDLLSolveLsq") ) == NULL )
  return FALSE;

 // store the name of this DLL
 DLLName( buffer );
 Name = buffer;
 // the number of parameters
 nParam = DLLParameterNumber();
 // does it deal with bounds?
 if( DLLIsBounded() ) Bounds = TRUE; else Bounds = FALSE;
 // does it deal with constraints?
 if( DLLIsConstrained() ) Constraints = TRUE; else Constraints = FALSE;
 // create the array for the parameter values
 Param = new double[nParam];
 if( Param!=NULL ) ArrayCreated = TRUE; 
 else ArrayCreated = FALSE;
 // load the default values of the parameters
 for( i=0; i<nParam; i++ )
 {
  // get the default values from the ini file
  TmpStr.Format( "PARAMETER%1d", i );
  GetPrivateProfileString( "PARAMETERS", LPCTSTR( TmpStr ), "0.0", buffer,(DWORD) 4096, LPCTSTR(Ini) );
  sscanf( buffer, "%lf", &(Param[i]) );
 }
 // make the version number
 int nV = DLLVersion();
 float fDV = (float) (1000.0 * ( nV * 0.001 - floor( nV * 0.001 ) ));
 float fV = (float) (nV * 0.00001 - 0.01 * ( nV * 0.001 - floor( nV * 0.001 ) ));
 if( fDV >= 300.0 )
  Version.Format( "%.2f", fV );
 else
 {
  if( fDV<200 )
   Version.Format( "%.2f %s %.0f", fV, "alpha", fDV-100.0 );
  else
   Version.Format( "%.2f %s %.0f", fV, "beta", fDV-200.0 );
 }
 return TRUE;
}

// return TRUE if method can do general optimisation
BOOL COptModule::CanOptimise( void )
{
 switch( DLLRoutines() )
 {
 case 1:
 case 3:  return TRUE;
 case 2:  return FALSE;
 default: return FALSE;
 }
}

// return TRUE if method has specialised least-squares solver
BOOL COptModule::SpecialisedLsq( void )
{
 switch( DLLRoutines() )
 {
 case 1:  return FALSE;
 case 2:  
 case 3:  return TRUE;
 default: return FALSE;
 }
}

// return TRUE if method deals with bounds
BOOL COptModule::IsBounded( void )
{
 return Bounds;
}

// return TRUE if method deals with constraints
BOOL COptModule::IsConstrained( void )
{
 return Constraints;
}

// return the number of parameters
int COptModule::CountParameters( void )
{
 return nParam;
}

double COptModule::GetParameterValue( int p )
{
 return Param[p];
}

void COptModule::SetParameterValue( int p, double v )
{
 Param[p] = v;
}

char * COptModule::GetParameterName( int p )
{
 statbuffer[0] = '\0';
 return DLLParameterName( p, statbuffer );
}

int COptModule::Optimise( double (*func) (void) )
{
 __try
 {
  return DLLOptimise( func );
 }
 __finally
 {
 }
}

int COptModule::SolveLsq( double (*func) (double *) )
{
 __try
 {
  return DLLSolveLsq( func );
 }
 __finally
 {
 }
}


void COptModule::SetAlgoParameters( void )
{
 int i;
 for( i=0; i<nParam; i++ )
  DLLSetMethodParam( i, Param[i] );
}


#endif  // XXXX

















