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
//C_FLOAT64 CNewton::SS_XNorn( C_FLOAT64 * mtx )
//{
// int i;

 // get the index of the element with the largest magnitude
 //Yongqun: idamax is an extern fn that returns a int. Find it out
 //orig: i = idamax( mModel.IntMetab, mtx, 1 );
// i = idamax( mModel->getIntMetab(), mtx, 1 );

// return fabs( mtx[i] );
//}


//similar to SS_Newton() in gepasi except a few modification
//
void CNewton::ProcessNewton(void)
{
  //new from Yongqun
  // variables for steady-state solution
  double        *ss_x;
  double        *ss_dxdt;
  double        *ss_xnew;
  double        *ss_h;
  double        **ss_jacob;
  C_INT32        *ss_ipvt;
  int                ss_solution;
  int                ss_unstable;

  //new from Yongqun
  // Newton variables
  ss_x = new double[mModel->getTotMetab()+1];
  ss_xnew = new double[mModel->getTotMetab()+1];
  ss_dxdt = new double[mModel->getTotMetab()+1];
  ss_h = new double[mModel->getTotMetab()+1];
  ss_ipvt = new C_INT32[mModel->getIndMetab()+1];
  ss_jacob = new double *[mModel->getTotMetab()+1];
  for( int i=0; i<mModel->getTotMetab()+1; i++ )
    ss_jacob[i] = new double[mModel->getTotMetab()+1];

  int i,j,k,l,m;
  C_FLOAT64 maxrate, nmaxrate;
  C_INT32 info;
  ss_solution = SS_NOT_FOUND;

  //  try
  // {
    //note from Yongqun: this fn should be from CModel::ls...
  //FEval( 0, 0, ss_x, ss_dxdt );
    mModel->lSODAEval(0, 0, ss_x, ss_dxdt );

    ss_nfunction++;
    maxrate =xNorm(mModel->getIntMetab(), ss_dxdt,1);
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
   //FEval( 0, 0, ss_xnew, ss_dxdt );
    mModel->lSODAEval( 0, 0, ss_xnew, ss_dxdt );
    ss_nfunction++;
    nmaxrate = xNorm(mModel->getIntMetab(), ss_dxdt,1);
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
                       double * ss_h, C_INT32 * ss_ipvt, double ** ss_jacob)
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


