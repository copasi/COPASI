/**
 *  CNewton.cpp
 *
 */

#include "CNewton.h"

 // BLAS
//these 3 functions can be found from "Clsoda.h" but are private. How????
//extern "C" int idamax( int n, double *dx, int incx );
//extern "C" int dgefa( double **a, int n, int *ipvt, int *info );
//extern "C" int dgesl( double **a, int n, int *ipvt, double *b, int job );
//extern "C" int invertm( double **A, int npar );

//default constructor
CNewton::CNewton()
{
  mModel = NULL;
  mNewtonLimit = DefaultNewtonLimit;
  ss_nfunction=0;
}



// constructor
CNewton::CNewton(C_INT32 anInt)
{
  mModel = NULL;
  mNewtonLimit = anInt;
  ss_nfunction = 0;
}


// copy constructor
CNewton::CNewton(const CNewton& source)
{
  mModel = source.mModel;
  mNewtonLimit = source.mNewtonLimit;
  ss_nfunction = source.ss_nfunction;
}

  
//Object assignment overloading
CNewton& CNewton::operator=(const CNewton& source)
{
  if(this != &source)
    {
      mModel = source.mModel;
      mNewtonLimit = source.mNewtonLimit;
      ss_nfunction = source.ss_nfunction;
    }

  return *this;
}


//destructor
CNewton::~CNewton()
{
  cout << "~CNewton " << endl;
}

//set mModel
void CNewton::SetModel(CModel * aModel)
{
  mModel = aModel;
}


//get mModel
CModel * CNewton::GetModel() const
{
  return mModel;
}


// set mSSRes
void CNewton::SetSSRes(C_FLOAT64 aDouble)
{
  mSSRes = aDouble;
}

//get mSSRes
C_FLOAT64 CNewton::GetSSRes() const
{
  return mSSRes;
}


// set mDerivFactor
void CNewton::SetDerivFactor(C_FLOAT64 aDouble)
{
  mDerivFactor = aDouble;
}

// get mDerivFactor
C_FLOAT64 CNewton::GetDerivFactor() const
{
  return mDerivFactor;
}


// returns the largest value in a vector
C_FLOAT64 CNewton::SS_XNorn( C_FLOAT64 * mtx )
{
 int i;

 // get the index of the element with the largest magnitude
 //Yongqun: idamax is an extern fn that returns a int. Find it out
 //orig: i = idamax( mModel.IntMetab, mtx, 1 );
 i = idamax( mModel->getIntMetab(), mtx, 1 );

 return fabs( mtx[i] );
}


//similar to SS_Newton() in gepasi except a few modification
//
void CNewton::ProcessNewton(void)
{
  //new from Yongqun
  // variables for steady-state solution
  double	*ss_x;
  double	*ss_dxdt;
  double	*ss_xnew;
  double	*ss_h;
  double	**ss_jacob;
  int		*ss_ipvt;
  int		ss_solution;
  int		ss_unstable;

  //new from Yongqun
  // Newton variables
  ss_x = new double[mModel->getTotMetab()+1];
  ss_xnew = new double[mModel->getTotMetab()+1];
  ss_dxdt = new double[mModel->getTotMetab()+1];
  ss_h = new double[mModel->getTotMetab()+1];
  ss_ipvt = new int[mModel->getIndMetab()+1];
  ss_jacob = new double *[mModel->getTotMetab()+1];
  for( int i=0; i<mModel->getTotMetab()+1; i++ )
    ss_jacob[i] = new double[mModel->getTotMetab()+1];

  int i,j,k,l,m;
  double maxrate, nmaxrate;
  int info;
  ss_solution = SS_NOT_FOUND;

  //  try
  // {
    //note from Yongqun: this fn should be from CModel::ls...
    FEval( 0, 0, ss_x, ss_dxdt );

    ss_nfunction++;
    maxrate = SS_XNorn( ss_dxdt );
    if( maxrate < mSSRes )
    ss_solution = SS_FOUND;
    if( ss_solution == SS_FOUND )
    {
      for( i=0; i<mModel->getIntMetab(); i++ )
      if( ss_x[i+1] < 0.0 )
      {
        ss_solution = SS_NOT_FOUND;
	break;
      }
    }
    // }
 // finally
 // {
 //}
  if( ss_solution==SS_FOUND ) return;
  for( k=0; k<mNewtonLimit; k++ )
  {
    //  try
    //{
    JEval( ss_x, ss_jacob );

    // LU decomposition of Jacobian
    //Yongqun: dgefa() is a extern fn, find it out...........
    dgefa( ss_jacob, mModel->getIndMetab(), ss_ipvt, &info);

    if( info!=0 )
    {
       // jacobian is singular
      ss_solution = SS_SINGULAR_JACOBIAN;

      // from Yongqun
    Cleanup(ss_x,ss_xnew,ss_dxdt,ss_h,ss_ipvt,ss_jacob);

      return;
    }
    // solve ss_jacob . x = ss_h for x (result in ss_dxdt)
    //Yongqun: dgesl() is a extern fn, find it out...........
    dgesl( ss_jacob, mModel->getIndMetab(), ss_ipvt, ss_dxdt, 0 );
    // }
  //finally
  //{
  //}
  nmaxrate = maxrate * 1.001;
  // copy values of increment to ss_h
  for(i=0;i<mModel->getIndMetab();i++) ss_h[i+1] = ss_dxdt[i+1];
  for( i=0; (i<32) && (nmaxrate>maxrate) ; i++ )
  {
   for( j=0; j<mModel->getIndMetab(); j++ )
   {
    ss_xnew[j+1] = ss_x[j+1] - ss_h[j+1];
    ss_h[j+1] /= 2;
   }
   mModel->setConcentrations(ss_xnew);
   // update the dependent metabolites
   //  try
   //{
    FEval( 0, 0, ss_xnew, ss_dxdt );
    ss_nfunction++;
    nmaxrate = SS_XNorn( ss_dxdt );
    //}
  //finally
  //{
  //}
  }
  if( i==32 )
  {
    if( maxrate < mSSRes )
    {
    ss_solution = SS_FOUND;
	// check if solution is valid
    for( i=0; i<mModel->getIntMetab(); i++ )
     if( ss_x[i+1] < 0.0 )
     {
      ss_solution = SS_NOT_FOUND;
 	  break;
     }

     // from Yongqun
    Cleanup(ss_x,ss_xnew,ss_dxdt,ss_h,ss_ipvt,ss_jacob);

     return;
    }
    else
    {
     ss_solution = SS_DAMPING_LIMIT;

     // from Yongqun
    Cleanup(ss_x,ss_xnew,ss_dxdt,ss_h,ss_ipvt,ss_jacob);

     return;
    }
   }
   for(i=0;i<mModel->getIntMetab();i++) ss_x[i+1] = ss_xnew[i+1];
   maxrate = nmaxrate;
  }
  if( maxrate < mSSRes )
  {
  ss_solution = SS_FOUND;
  // check if solution is valid
  for( i=0; i<mModel->getIntMetab(); i++ )
   if( ss_x[i+1] < 0.0 )
   {
    ss_solution = SS_NOT_FOUND; 
    break;
   }

   // from Yongqun
    Cleanup(ss_x,ss_xnew,ss_dxdt,ss_h,ss_ipvt,ss_jacob);

   return;
  }
  else
  {
    ss_solution = SS_ITERATION_LIMIT;

    // from Yongqun
    Cleanup(ss_x,ss_xnew,ss_dxdt,ss_h,ss_ipvt,ss_jacob);

    return;
  }

  // from Yongqun
    Cleanup(ss_x,ss_xnew,ss_dxdt,ss_h,ss_ipvt,ss_jacob);
}



// Clean up internal pointer variables
void CNewton::Cleanup(double * ss_x, double * ss_xnew, double * ss_dxdt, 
                       double * ss_h, int * ss_ipvt, double ** ss_jacob)
{
  //copy from void CGepasiDoc::CleanupEngine( void )
  // Newton variables
  delete [] ss_x;
  delete [] ss_xnew;
  delete [] ss_dxdt;
  delete [] ss_h;
  delete [] ss_ipvt;
  for( int i=0; i<mModel->getTotMetab()+1; i++ ) delete [] ss_jacob[i];
  delete [] ss_jacob;
}


// this function evaluates the balance equations
void CNewton::FEval(int num, double time, double *y, double *ydot )
{
 register int i, j, k;
 for(i=0;i<mModel->getIndMetab();i++)
 {
  ydot[i+1] = 0.0;
  // for( j=0; j<mModel->TotStep; j++ )
  for( j=0; j<mModel->getTotSteps(); j++   //from Y.H.
   {
   if( mModel->Stoichiometry[mModel->Row[i]][mModel->Col[j]] != 0.0 )
      ydot[i+1] += mModel->Stoichiometry[mModel->Row[i]][mModel->Col[j]]
	  * (*(mModel->Step[mModel->Col[j]].Kinetics->Function))((void *)mModel, &y[1], mModel->Col[j]);
  }
//  ydot[i+1] *= mModel->Compartment[mModel->Metabolite[mModel->Row[i]].Compart].Volume;
 }
 for( k=0; i<mModel->getIntMetab(); i++, k++)
 {
  ydot[i+1] = 0.0;
  for( j=0; j<mModel->getIndMetab(); j++)
   ydot[i+1] -= mModel->ConsRel[i][j] * ydot[j+1];
//  y[i+1] = mModel->Moiety[k].IConc;
//  for( j=0; j<mModel->getIndMetab(); j++)
//   y[i+1] -= mModel->ConsRel[i][j] * y[j+1];
 }
}


// evaluates the Jacobian matrix
void CNewton::JEval( double *y, double **ydot )
{
 register int i, j;
 double store, temp, *f1, *f2;
 double K1, K2, K3;
 // constants for differentiation by finite differences
 K1 = 1 + mDerivFactor;
 K2 = 1 - mDerivFactor;
 K3 = 2 * mDerivFactor;
 // arrays to store function values
 f1 = new double[mModel->getIntMetab()+1];
 f2 = new double[mModel->getIntMetab()+1];
 // iterate over all metabolites
 for( i=1; i<mModel->getIndMetab()+1; i++ )
 {
  // if y[i] is zero, the derivative will be calculated at a small
  // positive value (no point in considering negative values!).
  // let's stick with mSSRes*(1.0+mDerivFactor)
  store = y[i];
  if( store < mSSRes ) temp = mSSRes*K1;
  else temp = store;
  y[i] = temp*K1;
  FEval( 0, 0, y, f1 );
  ss_nfunction++;
  y[i] = temp*K2;
  FEval( 0, 0, y, f2 );
  ss_nfunction++;
  for( j=1; j<mModel->getIndMetab()+1; j++ )
   ydot[j][i] = (f1[j]-f2[j])/(temp*K3);
  y[i] = store;
 }
 delete [] f1;
 delete [] f2;
 ss_njacob++;
}

