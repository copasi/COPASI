/**
 *  CSS_Solution.cpp
 *
 */

#include "CSS_Solution.h"

//extern "C" int idamax( int n, double *dx, int incx );
extern ss_nfunction;
//default constructor
CSS_Solution::CSS_Solution()
{
  mNewton = NULL;
  mModel = NULL;
  mTraj = NULL;
  mOption = NEWTON;
}


//copy constructor 
CSS_Solution::CSS_Solution(const CSS_Solution& source)
{
  mNewton = source.mNewton;
  mModel = source.mModel;
  mTraj = source.mTraj;
  mOption = source.mOption;
}

    
// Object assignment overloading 
CSS_Solution& CSS_Solution::operator=(const CSS_Solution& source)
{
  if(this != &source)
    {
      mNewton = source.mNewton;
      mModel = source.mModel;
      mTraj = source.mTraj;
      mOption = source.mOption;
    }
  return *this;
}



//destructor
CSS_Solution::~CSS_Solution()
{
  cout << "~CSS_Solution " << endl;
}
  
//set mOption
void CSS_Solution::SetOption(C_INT32 anOption)
{
  mOption = anOption;
}

// get option 
C_INT32 CSS_Solution::GetOption() const
{
  return mOption;
}


//set mNewton
void CSS_Solution::SetNewton(CNewton * aNewton)
{
  mNewton = aNewton;
}


//get mNewton
CNewton * CSS_Solution::GetNewton() const
{
  return mNewton;
}

//set mModel
void CSS_Solution:: SetModel(CModel * aModel)
{
  mModel = aModel;
}


//get mNewton
CModel * CSS_Solution::GetModel() const
{
  return mModel;
}

//set mTraj
void CSS_Solution::SetTrajectory(CTrajectory * aTraj)
{ 
  mTraj = aTraj;
}


//get mTraj
CTrajectory *  CSS_Solution::GetTrajectory() const
{
  return mTraj;
}



void CSS_Solution::Process(void)
{
  C_FLOAT64 t = 0.1;

  mNewton->ProcessNewton();

  while (t < pow(10,10))
  {
    if(IsSteadyState())
      return;

    t *= 10;
    mTraj -> process();
  }

  //Backward trajectory until -10^10


}


// returns the largest value in a vector
//double CSS_Solution::SS_XNorn( double *mtx )
//{
// int i;

 // get the index of the element with the largest magnitude
 //Yongqun: idamax is a extern fn that returns a int. Find it out
// i = idamax( mModel.IntMetab, mtx, 1 );
 //i = lsoda_idamax( mModel.IntMetab, mtx, 1 ); //can't use private fn

// return fabs( mtx[i] );
//}


//Yongqun: change SSStrategy to mOption
//

void CSS_Solution::SteadyState( void )
{
 int i,j;
 int temp_points;
 BOOL tt_infinity;
 double jtot, ftot;
 // set the number of function and jacobian evaluations to zero
 njeval = jtot = 0.0;
 nfeval = ftot = 0.0;
 lsoda_state = 1;
 ss_njacob = ss_nfunction = 0;
 // use the damped Newton method
 // if( (SSStrategy==0) || (SSStrategy==2) )
 //Yongqun: my substitution, replace SSStrategy with mOption
 if((mOption==0) || (mOption==2)) 
{
  // we start with initial concentrations as the guess
  for( i=0; i<mModel->getTotMetab(); i++ )
   ss_x[i+1] = ss_xnew[i+1] = mModel.Metabolite[mModel.Row[i]].IConc * 
                              mModel.Compartment[mModel.Metabolite[mModel.Row[i]].Compart].Volume;
  // first attempt a solution by the newton method
  //SS_Newton();
  mNewton->ProcessNewton();
  ftot += (double) ss_nfunction;
  jtot += (double) ss_njacob;
 }
 // use forward integration
 if( ( (mOption==0) && (ss_solution!=SS_FOUND) ) // if newton failed
      || (mOption==1) // or forward integration only
   )
 {
  // load array with the metabolite initial concentrations
  for( i=0; i<mModel.TotMetab; i++ )
   lsoda_y[i+1] = mModel.Metabolite[mModel.Row[i]].IConc *
                  mModel.Compartment[mModel.Metabolite[mModel.Row[i]].Compart].Volume;
  // set the integration tolerances
  lsoda_rtol[1] = RelTol;
  lsoda_atol[1] = AbsTol;
  // set points to 1 but keep a copy of the original
  temp_points = Points;
  Points = 1;
  // set the increment to 1 for starters
  lsoda_incr = 1;
  //iterate ten times
  for( i=0; i<10; i++ )
  {
   //set the initial time
   lsoda_time = lsoda_endt = 0;
   // set the state for the first call
   lsoda_state = 1; 
   // the increment is 10 times the previous
   lsoda_incr *= 10;
   // set max iterations to default value
   lsoda_maxiter = 10000;
   // do the integration (no output, no fitting)
   Dynamic( 0, 0 );
   // update count of jacobian evaluations
   jtot += njeval;
   ftot += nfeval;
   // now take the end concentrations as guess for Newton
   for( j=1; j<=mModel.TotMetab; j++ )
    ss_x[j] = lsoda_y[j];
   if( IsSteadyState()==SS_FOUND ) break;
   if( mOption==0 ) // newton+integration (we use newton before recycling)
   {
    ss_njacob = ss_nfunction = 0;
    SS_Newton();
    // update count of function and jacobian evaluations
    ftot += (double) ss_nfunction;
    jtot += (double) ss_njacob;
    if( ss_solution == SS_FOUND ) break;
   }
  }
  // restore Points
  Points = temp_points;
 }
 // use backwards integration
 if( ( (SSBackInt) && (ss_solution!=SS_FOUND) ) // if others failed
      || (mOption==3) // or backwards integration only
   )
 {
  // load array with the metabolite initial concentrations
  for( i=0; i<mModel.TotMetab; i++ )
   lsoda_y[i+1] = mModel.Metabolite[mModel.Row[i]].IConc * 
                  mModel.Compartment[mModel.Metabolite[mModel.Row[i]].Compart].Volume;
  // set the integration tolerances
  lsoda_rtol[1] = RelTol;
  lsoda_atol[1] = AbsTol;
  // set points to 1 but keep a copy of the original
  temp_points = Points;
  Points = 1;
  // set the increment to -1 for starters
  lsoda_incr = -1;
  //iterate ten times
  for( i=0; i<10; i++ )
  {
   //set the initial time
   lsoda_time = lsoda_endt = 0;
   // set the state for the first call
   lsoda_state = 1; 
   // the increment is 10 times the previous
   lsoda_incr *= 10;
   // set max iterations to default value
   lsoda_maxiter = 10000;
   // do the integration (no output, no fitting)
   Dynamic( 0, 0 );
   // update count of jacobian evaluations
   jtot += njeval;
   ftot += nfeval;
   // copy the end concentrations to ss_x to test for steady state
   for( j=1; j<=mModel.TotMetab; j++ )
    ss_x[j] = lsoda_y[j];
   if( IsSteadyState()==SS_FOUND ) break;
  }
  // restore Points
  Points = temp_points;
 }
 // store the counters in nfeval & njeval
 nfeval = ftot;
 njeval = jtot;
 if( ss_solution == SS_FOUND )
 {
try
{
  // evaluate the jacobian
  JEval( ss_x, ss_jacob );
  // calculate the eigenvalues of the jacobian
  CalcEigenvalues();
  // copy the concentrations back to the model
  for( i=0; i<mModel.TotMetab; i++ )
   mModel.Metabolite[mModel.Row[i]].Conc = ss_x[i+1] / 
      mModel.Compartment[mModel.Metabolite[mModel.Row[i]].Compart].Volume;
  // calculate the fluxes
  for( i=0; i<mModel.TotStep; i++ )
   mModel.Step[i].Flux = (*(mModel.Step[i].Kinetics->Function))((void *) &mModel, &ss_x[1], i);
//   mModel.Step[i].Flux = (*(mModel.Step[mModel.Col[i]].Kinetics->Function))((void *) &mModel, &ss_x[1], mModel.Col[i]);
  // calculate the transition times
  tt_infinity = FALSE;
  mModel.TransTime = 0.0;
  for( i=0; i<mModel.TotMetab; i++)
  {
  mModel.Metabolite[mModel.Row[i]].TT = 0.0;                                /* reset trans. time    */
   if( mModel.Metabolite[mModel.Row[i]].Status != METAB_FIXED )
   {
    // sum the positive fluxes into this metabolite
    for( j=0; j<mModel.TotStep; j++ )
     if( mModel.Stoichiometry[mModel.Row[i]][mModel.Col[j]] > 0.0 )
      mModel.Metabolite[mModel.Row[i]].TT
	  += fabs( (*(mModel.Step[mModel.Col[j]].Kinetics->Function))((void *)&mModel, &ss_x[1], mModel.Col[j]) );
	// if no positive fluxes into this metabolite
    if( mModel.Metabolite[mModel.Row[i]].TT == 0.0 )
    {
     // sum the negative fluxes into this metabolite
     for( j=0; j<mModel.TotStep; j++ )
      if( mModel.Stoichiometry[mModel.Row[i]][mModel.Col[j]] < 0.0 )
       mModel.Metabolite[mModel.Row[i]].TT
	   += fabs( (*(mModel.Step[mModel.Col[j]].Kinetics->Function))((void *)&mModel, &ss_x[1], mModel.Col[j]) );
    }
	// if the sum of fluxes is non-negative
    if( mModel.Metabolite[mModel.Row[i]].TT != 0.0 )
    {
     mModel.Metabolite[mModel.Row[i]].TT = ss_x[i+1] / mModel.Metabolite[mModel.Row[i]].TT;
     mModel.TransTime += mModel.Metabolite[mModel.Row[i]].TT;
    }
    else
    {
     mModel.Metabolite[mModel.Row[i]].TT = DBL_MAX;
	 tt_infinity = TRUE;
    }
   }
  }
}
//__finally  
//{
//}
  if( tt_infinity ) Model.TransTime = DBL_MAX;
 }
// else
// {
//  // set the concentrations to minus 1 and TTs to 0
//  for( i=0; i<Model.TotMetab; i++ )
//  {
//   Model.Metabolite[i].Conc = -1.0;
//   Model.Metabolite[i].TT = 0.0;
//  }
// // set the fluxes to zero
//  for( i=0; i<Model.TotStep; i++ )
//   Model.Step[i].Flux = 0.0;
//  // set the overall transition time to zero
//  Model.TransTime = 0.0;
// }
}

// finds out if current state is a valid steady state
// destroys the contents of matrix ss_dxdt
C_INT32 CSS_Solution::IsSteadyState( void )
{
 int i;
 double maxrate;
 ss_solution = SS_NOT_FOUND;
 for( i=0; i<mModel.IntMetab; i++ )
  if( ss_x[i+1] < 0.0 ) return SS_NOT_FOUND;
try
{
 FEval( 0, 0, ss_x, ss_dxdt );
 ss_nfunction++;
 maxrate = SS_XNorn( ss_dxdt );
}
//__finally
//{
//}
 if( maxrate < SSRes ) ss_solution = SS_FOUND;
 return ss_solution;
}



















