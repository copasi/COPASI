/**
 *  File name: CSS_Solution.cpp
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .cpp file for the class CSS_Solution. 
 *           It is to solve the steady state solution problem with different approaches,
 *           e.g., (1) Newton, (2) Integration (Trajectory), (3) Newton + Integration,
 *           (4) Backward Integration, (5) Backward integration if all else fails.
 */


#include <cmath>

#include "CSS_Solution.h"
#include "model/CModel.h"


//default constructor
CSS_Solution::CSS_Solution()
{
  mNewton = NULL;
  mModel = NULL;
  mTraj = NULL;
  mOption = NEWTON;

  mSs_nfunction = 0;
  //  mSs_x = NULL;
  //mSs_xnew = NULL;

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
void CSS_Solution::setOption(C_INT32 anOption)
{
  mOption = anOption;
}

// get option 
C_INT32 CSS_Solution::getOption() const
{
  return mOption;
}


//set mNewton
void CSS_Solution::setNewton(CNewton * aNewton)
{
  mNewton = aNewton;
}


//get mNewton
CNewton * CSS_Solution::getNewton() const
{
  return mNewton;
}

//set mModel
void CSS_Solution:: setModel(CModel * aModel)
{
  mModel = aModel;
}


//get mNewton
CModel * CSS_Solution::getModel() const
{
  return mModel;
}

//set mTraj
void CSS_Solution::setTrajectory(CTrajectory * aTraj)
{ 
  mTraj = aTraj;
}


//get mTraj
CTrajectory *  CSS_Solution::getTrajectory() const
{
  return mTraj;
}



void CSS_Solution::process(void)
{
  C_FLOAT64 t = 0.1;

  mNewton->process();

  while (t < pow(10,10))
    {
      if(mNewton->isSteadyState())
	return;

      t *= 10;
      mTraj -> process();
    }

  //Backward trajectory until -10^10


}

#ifdef XXXXXX

//Yongqun: change SSStrategy to mOption
//
void CSS_Solution::steadyState( void )
{
  int i,j;
  int temp_points;
  BOOL tt_infinity;
  double jtot, ftot;
  // set the number of function and jacobian evaluations to zero
  mNjeval = jtot = 0.0;
  mNfeval = ftot = 0.0;
  lsoda_state = 1;
  mSs_njacob = mSs_nfunction = 0;
  // use the damped Newton method
  // if( (SSStrategy==0) || (SSStrategy==2) )
  //Yongqun: my substitution, replace SSStrategy with mOption
  if((mOption==0) || (mOption==2)) 
    {
      // we start with initial concentrations as the guess
      for( i=0; i<mModel->getTotMetab(); i++ )
	mSs_x[i+1] = mSs_xnew[i+1] = mModel.Metabolite[mModel.Row[i]].IConc * 
	  mModel.Compartment[mModel.Metabolite[mModel.Row[i]].Compart].Volume;
      // first attempt a solution by the newton method
      //SS_Newton();
      mNewton->ProcessNewton();
      ftot += (double) mSs_nfunction;
      jtot += (double) mSs_njacob;
    }
  // use forward integration
  if( ( (mOption==0) && (ss_solution!=SS_FOUND) ) // if newton failed
      || (mOption==1) // or forward integration only
      )
    {
      // load array with the metabolite initial concentrations
      for( i=0; i<mModel->getTotMetab(); i++ )
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
	  jtot += mNjeval;
	  ftot += mNfeval;
	  // now take the end concentrations as guess for Newton
	  for( j=1; j<=mModel.TotMetab; j++ )
	    mSs_x[j] = lsoda_y[j];
	  if( IsSteadyState()==SS_FOUND ) break;
	  if( mOption==0 ) // newton+integration (we use newton before recycling)
	    {
	      mSs_njacob = mSs_nfunction = 0;
	      SS_Newton();
	      // update count of function and jacobian evaluations
	      ftot += (double) mSs_nfunction;
	      jtot += (double) mSs_njacob;
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
	  jtot += mNjeval;
	  ftot += mNfeval;
	  // copy the end concentrations to mSs_x to test for steady state
	  for( j=1; j<=mModel.TotMetab; j++ )
	    mSs_x[j] = lsoda_y[j];
	  if( IsSteadyState()==SS_FOUND ) break;
	}
      // restore Points
      Points = temp_points;
    }
  // store the counters in mNfeval & mNjeval
  mNfeval = ftot;
  mNjeval = jtot;
  if( ss_solution == SS_FOUND )
    {
      try
	{
	  // evaluate the jacobian
	  JEval( mSs_x, ss_jacob );
	  // calculate the eigenvalues of the jacobian
	  CalcEigenvalues();
	  // copy the concentrations back to the model
	  for( i=0; i<mModel.TotMetab; i++ )
	    mModel.Metabolite[mModel.Row[i]].Conc = mSs_x[i+1] / 
	      mModel.Compartment[mModel.Metabolite[mModel.Row[i]].Compart].Volume;
	  // calculate the fluxes
	  for( i=0; i<mModel.TotStep; i++ )
	    mModel.Step[i].Flux = (*(mModel.Step[i].Kinetics->Function))((void *) &mModel, &mSs_x[1], i);
	  //   mModel.Step[i].Flux = (*(mModel.Step[mModel.Col[i]].Kinetics->Function))((void *) &mModel, &mSs_x[1], mModel.Col[i]);
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
			+= fabs( (*(mModel.Step[mModel.Col[j]].Kinetics->Function))((void *)&mModel, &mSs_x[1], mModel.Col[j]) );
		  // if no positive fluxes into this metabolite
		  if( mModel.Metabolite[mModel.Row[i]].TT == 0.0 )
		    {
		      // sum the negative fluxes into this metabolite
		      for( j=0; j<mModel.TotStep; j++ )
			if( mModel.Stoichiometry[mModel.Row[i]][mModel.Col[j]] < 0.0 )
			  mModel.Metabolite[mModel.Row[i]].TT
			    += fabs( (*(mModel.Step[mModel.Col[j]].Kinetics->Function))((void *)&mModel, &mSs_x[1], mModel.Col[j]) );
		    }
		  // if the sum of fluxes is non-negative
		  if( mModel.Metabolite[mModel.Row[i]].TT != 0.0 )
		    {
		      mModel.Metabolite[mModel.Row[i]].TT = mSs_x[i+1] / mModel.Metabolite[mModel.Row[i]].TT;
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
C_INT32 CSS_Solution::isSteadyState( void )
{
  int i;
  double maxrate;
  mSs_solution = SS_NOT_FOUND;
  for( i=0; i<mModel->getIntMetab(); i++ )
    // if( mSs_x[i+1] < 0.0 ) return SS_NOT_FOUND;
    if( mSs_x[i+1] < 0.0 ) return SS_NOT_FOUND;
  //try
  //{
  //FEval( 0, 0, mSs_x, ss_dxdt );
  mModel->lSODAEval( 0, 0, mNewton->getSs_xnew(), mNewton->getSs_dxdt() );
  mSs_nfunction++;
  // maxrate = SS_XNorn( ss_dxdt );
  maxrate = xNorm(mModel->getIntMetab(),mNewton->getSs_dxdt(), 1);
  //}
  //__finally
  //{
  //}
  // if( maxrate < SSRes ) mSs_solution = SS_FOUND;
  if( maxrate < mNewton->getSSRes() ) mSs_solution = SS_FOUND;
  return mSs_solution;
}

#endif //XXXXXX
