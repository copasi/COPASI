// GepasiDoc.cpp : implementation of the CGepasiDoc class
//


#include "Gepasi.h"

#include "except.h"
#include "pmutils.h"
#include "optmod.h"
#include "globals.h"
#include "optparam.h"
#include "GepasiDoc.h"
#include "OptPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
// CGepasiDoc construction/destruction

CGepasiDoc::CGepasiDoc()
{

}

CGepasiDoc::~CGepasiDoc()
{
 
 ClearArrays();
}

// checks if the frame can close this document

BOOL CGepasiDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
 // not if the simulation engine is running
 if( EngineRunning )
 {
  PMMessageBox( IDS_CLOSE_SE_RUNNING, MB_ICONINFORMATION | MB_OK );
  return FALSE;
 }
 return CDocument::CanCloseFrame(pFrame);
}


// resets all variables to their default values
void CGepasiDoc::ResetVariables( void )
{

 // optimisation variables
 OptSign = 1.0;
 OptDyn = TRUE;
 OptObjF.Title = _T("");
 OptObjF.Type = D_UNDEF;
 OptObjF.I = _T("");
 OptObjF.J = _T("");
 OptObjF.Value = NULL;
 OptEnabled = FALSE;
 OptSetModel = FALSE;
 OptIteration = 0;
 OptPV[0] = 
 OptPV[1] = 
 OptPV[2] = 
 OptPV[3] = 
 OptPV[4] = 1.0;
 TempOF = 0.0;

}

// this function clears the various arrays
void CGepasiDoc::ClearArrays( void )
{
 int i;

 for( i=0; i<OptParamSize; i++ )
  delete OptParam[i];

 OptParam.RemoveAll();

}



// this function prepares the various arrays
void CGepasiDoc::PrepareArrays( void )
{

 OptParam.SetSize( 10, 5 );
 OptParamSize = 0;
 
}



// this is the top-level controller of the Simulation Engine
void CGepasiDoc::SimulationEngine( void )
{
 int i, cw;
 CFileException fexcp;
 // signal that the simulation engine is running
 Eng

// allocates memory for several vectors and arrays 
void CGepasiDoc::InitialiseEngine( void )
{

}

// frees the memory allocated for the calculatations
void CGepasiDoc::CleanupEngine( void )
{
 

}

// driver for the optimisation procedure
void CGepasiDoc::Optimise( void )
{
 int i, d, p, c;
 BOOL bounded;
 // check the objective function
 if( !CheckOP( &OptObjF, TRUE ) ) return;
 // find out which optimisation routine we'll use
 for( i=0, d=-1; i<nOptModule; i++ )
 {
  if( OptMethod == OptModule[i].Name )
  {
   d = i;
   break;
  }
 }
 if( d==-1 )
 {
  // no suitable method was chosed!
  PMMessageBox( IDS_ERR_OPT_METH, MB_OK | MB_ICONEXCLAMATION );
  return;
 }
 // count the optimisation parameters and check bounds
 for( bounded=FALSE, i=p=0; i<OptParamSize; i++ )
  if( OptParam[i]->IsParameter )
  {
   p++;
   if( (OptParam[i]->MinType!=3) ||(OptParam[i]->MaxType!=3) )
	bounded = TRUE;
  }
 // count constraints
 for( i=c=0; i<OptParamSize; i++ )
  if( !OptParam[i]->IsParameter ) c++;
 // is the problem constrained?
 if( (c > 0) && !OptModule[d].DLLIsConstrained() )
   PMMessageBox( IDS_OPT_NOT_CONSTR, MB_ICONEXCLAMATION | MB_OK );
 // is the problem bounded?
 if( bounded && !OptModule[d].DLLIsBounded() )
   PMMessageBox( IDS_OPT_NOT_BOUNDED, MB_ICONEXCLAMATION | MB_OK );
 // initialise the module
 OptModule[d].DLLInit();
 // set the parameters of the algorithm
 OptModule[d].SetAlgoParameters();
 // size the arrays
 i = OptModule[d].DLLCreateArrays( p, c, 0 );
 if( i !=0 )
 {
  // clear memory
  if( i==-1 ) PMMessageBox( IDS_OPT_TOO_MANY, MB_ICONEXCLAMATION | MB_OK );
  else PMMessageBox( IDS_OPT_NO_MEM, MB_ICONEXCLAMATION | MB_OK );
  return;
 }
 // pass pointers to parameters
 for( i=p=0; i<OptParamSize; i++ )
  if( OptParam[i]->IsParameter ) 
   OptModule[d].DLLSetOptParameter( p++, OptParam[i] );
 // pass pointers to constraints
 for( i=c=0; i<OptParamSize; i++ )
  if( !OptParam[i]->IsParameter ) 
   OptModule[d].DLLSetConstraint( c++, OptParam[i] );
 // set the pointer to the callback function
//#ifndef _GEPASIX
 OptModule[d].DLLSetCallback( OptimisationCallback );
//#endif
 // reset the iteration counter
 OptIteration = 0;
 // go!
 OptModNum = d;
__try
{
 i=OptModule[d].Optimise( RunSim );
}
__finally
{
}
 // write out the report
 Rep_Opt();
 // leave the best solution in the model
 for( i=p=0; i<OptParamSize; i++ )
  if( OptParam[i]->IsParameter ) 
   *(OptParam[i]->Parameter.Value) = OptModule[d].DLLGetOptParameterValue(p++);
 // clear memory in the DLL
 OptModule[d].DLLClearMemory();
}

// this is a callback routine. the optimisation methods 
// call this to carry out one function evaluation
double CGepasiDoc::OptEvaluate( void )
{
 // carry out the simulation
 Simulate( 0, 0 );
 // return the value of the objective function
 return OptSign * *(OptObjF.Value);
}

// this is a callback routine. the optimisation methods 
// call this to signal one more iteration to the view
void CGepasiDoc::OptSignalIter( double ofv )
{
 // increment the counter
 OptIteration ++;
 // set the value of the objective function
 TempOF = OptSign * ofv;
#ifndef _GEPASIX
 // signal front-end another iteration
 pView->PostMessage( WM_SE_OPTITER, Iteration );
// WaitForSingleObject(Resume, INFINITE);
#endif
}













