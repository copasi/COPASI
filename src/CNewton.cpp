/**
 *  CNewton.cpp
 *  Note: modified by Yongqun He from GepasiDoc class of the gepasi.
 *
 */

#include "CNewton.h"


//default constructor
CNewton::CNewton()
{
  mModel = NULL;
  mNewtonLimit = DefaultNewtonLimit;
  mSs_nfunction=0;

  mSs_solution = 0;

  mSs_x = NULL;
  mSs_xnew = NULL;
  mSs_dxdt = NULL;
  mSs_h = NULL;
  mSs_jacob = NULL;
  mSs_ipvt = NULL;

  // initialize();
}



// constructor
CNewton::CNewton(C_INT32 anInt)
{
  mModel = NULL;
  mNewtonLimit = anInt;
  mSs_nfunction = 0;
  mSs_solution = 0;

  //initialize();
}


// copy constructor
CNewton::CNewton(const CNewton& source)
{
  mModel = source.mModel;
  mNewtonLimit = source.mNewtonLimit;
  mSs_nfunction = source.mSs_nfunction;
  mSs_solution = source.mSs_solution;

  mSs_x = source.mSs_x;
  mSs_xnew = source.mSs_xnew;
  mSs_dxdt =source.mSs_dxdt;
  mSs_h = source.mSs_h;
  mSs_jacob = source.mSs_jacob;
  mSs_ipvt = source.mSs_ipvt;
}


// initialize pointers
void CNewton::initialize()
{  
  cleanup();

  mSs_x = new double[mModel->getTotMetab()+1];
  mSs_xnew = new double[mModel->getTotMetab()+1];
  mSs_dxdt = new double[mModel->getTotMetab()+1];
  mSs_h = new double[mModel->getTotMetab()+1];
  mSs_ipvt = new C_INT32[mModel->getIndMetab()+1];
  mSs_jacob = new double *[mModel->getTotMetab()+1];
  for( int i=0; i<mModel->getTotMetab()+1; i++ )
    mSs_jacob[i] = new double[mModel->getTotMetab()+1];

}



//Y.H.
//set up mSs_x and mSs_x's default values
//they should come from steady state class, though
void CNewton::init_Ss_x_new(void)
{
  // we start with initial concentrations as the guess (modify from Gepasi)
  for( int i=0; i<mModel->getTotMetab(); i++ )
    //    mSs_x[i+1] = mSs_xnew[i+1] = mModel->Metabolite[mModel.Row[i]].IConc *
    //                         mModel->Compartment[mModel.Metabolite[mModel.Row[i]].Compart].Volume;

    //YH
    {
      double tmp = mModel->getMetabolitesInd()[i]->getInitialNumber();
      mSs_x[i+1] = tmp;
      mSs_xnew[i+1] = tmp;
    }

}

  
//Object assignment overloading
CNewton& CNewton::operator=(const CNewton& source)
{
  if(this != &source)
    {
      mModel = source.mModel;
      mNewtonLimit = source.mNewtonLimit;
      mSs_nfunction = source.mSs_nfunction;
      mSs_solution = source.mSs_solution;

      mSs_x = source.mSs_x;
      mSs_xnew = source.mSs_xnew;
      mSs_dxdt =source.mSs_dxdt;
      mSs_h = source.mSs_h;
      mSs_jacob = source.mSs_jacob;
      mSs_ipvt = source.mSs_ipvt;
    }

  return *this;
}


//destructor
CNewton::~CNewton()
{
  cout << "~CNewton " << endl;
}

//set mModel
void CNewton::setModel(CModel * aModel)
{
  mModel = aModel;
}


//get mModel
CModel * CNewton::getModel() const
{
  return mModel;
}


// set mSSRes
void CNewton::setSSRes(C_FLOAT64 aDouble)
{
  mSSRes = aDouble;
}

//get mSSRes
C_FLOAT64 CNewton::getSSRes() const
{
  return mSSRes;
}


// get mSs_xnew
C_FLOAT64 * CNewton::getSs_xnew() const
{
  return mSs_xnew;
}

   
// get mSs_dxdt
C_FLOAT64 * CNewton::getSs_dxdt() const
{
  return mSs_dxdt;
}


// set mDerivFactor
void CNewton::setDerivFactor(C_FLOAT64 aDouble)
{
  mDerivFactor = aDouble;
}

// get mDerivFactor
C_FLOAT64 CNewton::getDerivFactor() const
{
  return mDerivFactor;
}

// set mSs_nfunction
void CNewton::setSs_nfunction(C_INT32 aInt)
{
  mSs_nfunction = aInt;
}

// get mDerivFactor
C_INT32 CNewton::getSs_nfunction() const
{
  return mSs_nfunction;
}



// finds out if current state is a valid steady state
C_INT32 CNewton::isSteadyState( void )
{
 int i;
 double maxrate;
 mSs_solution = SS_NOT_FOUND;
 for( i=0; i<mModel->getIntMetab(); i++ )
  if( mSs_x[i+1] < 0.0 ) return SS_NOT_FOUND;

 //FEval( 0, 0, mSs_x, ss_dxdt );
 mModel->lSODAEval( 0, 0, mSs_xnew, mSs_dxdt );
 mSs_nfunction++;
 // maxrate = SS_XNorn( ss_dxdt );
 maxrate = xNorm(mModel->getIntMetab(),mSs_dxdt, 1);
 
 if( maxrate < mSSRes ) mSs_solution = SS_FOUND;
 return mSs_solution;
}



//similar to SS_Newton() in gepasi except a few modification
//
void CNewton::process(void)
{

  int i,j,k,l,m;
  C_FLOAT64 maxrate, nmaxrate;
  C_INT32 info;
  mSs_solution = SS_NOT_FOUND;

  //by Yongqun He
  //get the dimensions of the matrix
  int dim = mModel->getIndMetab();

  //  try
  // {
  //  mModel->lSODAEval(0, 0, mSs_x, mSs_dxdt );
  //changed by Yongqun He
    mModel->lSODAEval(dim, 0, mSs_x, mSs_dxdt );

    mSs_nfunction++;
    maxrate =xNorm(mModel->getIntMetab(), mSs_dxdt,1);
    if( maxrate < mSSRes )
    mSs_solution = SS_FOUND;
    if( mSs_solution == SS_FOUND )
    {
      for( i=0; i<mModel->getIntMetab(); i++ )
      if( mSs_x[i+1] < 0.0 )
      {
        mSs_solution = SS_NOT_FOUND;
        break;
      }
    }
    // }
 // finally
 // {
 //}
  if( mSs_solution==SS_FOUND ) return;
  for( k=0; k<mNewtonLimit; k++ )
  {
    //  try
    //{
    JEval( mSs_x, mSs_jacob );

    // LU decomposition of Jacobian
    dgefa( mSs_jacob, mModel->getIndMetab(), mSs_ipvt, &info);

    if( info!=0 )
    {
       // jacobian is singular
      mSs_solution = SS_SINGULAR_JACOBIAN;

      return;
    }
    // solve mSs_jacob . x = mSs_h for x (result in mSs_dxdt)
    dgesl( mSs_jacob, mModel->getIndMetab(), mSs_ipvt, mSs_dxdt, 0 );
    // }
  //finally
  //{
  //}
  nmaxrate = maxrate * 1.001;
  // copy values of increment to mSs_h
  for(i=0;i<mModel->getIndMetab();i++) mSs_h[i+1] = mSs_dxdt[i+1];
  for( i=0; (i<32) && (nmaxrate>maxrate) ; i++ )
  {
   for( j=0; j<mModel->getIndMetab(); j++ )
   {
    mSs_xnew[j+1] = mSs_x[j+1] - mSs_h[j+1];
    mSs_h[j+1] /= 2;
   }
   mModel->setConcentrations(mSs_xnew);
   // update the dependent metabolites
   //  try
   //{
   //FEval( 0, 0, mSs_xnew, mSs_dxdt );
    mModel->lSODAEval( 0, 0, mSs_xnew, mSs_dxdt );
    mSs_nfunction++;
    nmaxrate = xNorm(mModel->getIntMetab(), mSs_dxdt,1);
    //}
  //finally
  //{
  //}
  }
  if( i==32 )
  {
    if( maxrate < mSSRes )
    {
    mSs_solution = SS_FOUND;
        // check if solution is valid
    for( i=0; i<mModel->getIntMetab(); i++ )
     if( mSs_x[i+1] < 0.0 )
     {
      mSs_solution = SS_NOT_FOUND;
           break;
     }

     return;
    }
    else
    {
     mSs_solution = SS_DAMPING_LIMIT;

     return;
    }
   }
   for(i=0;i<mModel->getIntMetab();i++) mSs_x[i+1] = mSs_xnew[i+1];
   maxrate = nmaxrate;
  }
  if( maxrate < mSSRes )
  {
  mSs_solution = SS_FOUND;
  // check if solution is valid
  for( i=0; i<mModel->getIntMetab(); i++ )
   if( mSs_x[i+1] < 0.0 )
   {
    mSs_solution = SS_NOT_FOUND; 
    break;
   }

   return;
  }
  else
  {
    mSs_solution = SS_ITERATION_LIMIT;

    return;
  }

}


// Clean up internal pointer variables
void CNewton::cleanup(void)
{
  if(mSs_jacob) delete [] mSs_jacob;
  mSs_jacob = NULL;

  mSs_x = NULL;
  mSs_xnew = NULL;
  mSs_dxdt = NULL;
  mSs_h = NULL;
  mSs_ipvt = NULL;

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
  //FEval( 0, 0, y, f1 );
  mModel->lSODAEval(0, 0, y, f1);
  mSs_nfunction++;
  y[i] = temp*K2;
  //FEval( 0, 0, y, f2 ); 
  mModel->lSODAEval(0, 0, y, f2);
  mSs_nfunction++;
  for( j=1; j<mModel->getIndMetab()+1; j++ )
   ydot[j][i] = (f1[j]-f2[j])/(temp*K3);
  y[i] = store;
 }
 delete [] f1;
 delete [] f2;

 //Yongqun He: no plan to count the JEval() yet. Maybe later. 
 //ss_njacob++;
}



