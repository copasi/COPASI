/**
 *  CNewton.cpp
 *
 */

#include "CNewton.h"

 // BLAS
//these 3 functions can be found from "Clsoda.h" but are private. How????
extern "C" int idamax( int n, double *dx, int incx );
extern "C" int dgefa( double **a, int n, int *ipvt, int *info );
extern "C" int dgesl( double **a, int n, int *ipvt, double *b, int job );
//extern "C" int invertm( double **A, int npar );

//default constructor
CNewton::CNewton()
{
  mModel = NULL;
  mNewtonLimit = DefaultNewtonLimit;
}



// constructor
CNewton::CNewton(C_INT32 anInt)
{
  mModel = NULL;
  mNewtonLimit = anInt;
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


// returns the largest value in a vector
double CNewton::SS_XNorn( double *mtx )
{
 int i;

 // get the index of the element with the largest magnitude
 //Yongqun: idamax is an extern fn that returns a int. Find it out
 //orig: i = idamax( mModel.IntMetab, mtx, 1 );
 i = idamax( mModel->getDepMetab(), mtx, 1 );

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

  try
  {
    //note from Yongqun: this fn should be from CModel::ls...
    FEval( 0, 0, ss_x, ss_dxdt );

    ss_nfunction++;
    maxrate = SS_XNorn( ss_dxdt );
    if( maxrate < SSRes )
    ss_solution = SS_FOUND;
    if( ss_solution == SS_FOUND )
    {
      for( i=0; i<mModel->getDepMetab(); i++ )
      if( ss_x[i+1] < 0.0 )
      {
        ss_solution = SS_NOT_FOUND;
	break;
      }
    }
  }
 // finally
 // {
 //}
  if( ss_solution==SS_FOUND ) return;
  for( k=0; k<mNewtonLimit; k++ )
  {
  try
  {
    JEval( ss_x, ss_jacob );

    // LU decomposition of Jacobian
    //Yongqun: dgefa() is a extern fn, find it out...........
    dgefa( ss_jacob, mModel->getIndMetab(), ss_ipvt, &info);

    if( info!=0 )
    {
       // jacobian is singular
      ss_solution = SS_SINGULAR_JACOBIAN;

      // from Yongqun
    Cleanup();

      return;
    }
    // solve ss_jacob . x = ss_h for x (result in ss_dxdt)
    //Yongqun: dgesl() is a extern fn, find it out...........
    dgesl( ss_jacob, mModel->getIndMetab(), ss_ipvt, ss_dxdt, 0 );
   }
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
   // update the dependent metabolites
   for( m=0; j<mModel->getDepMetab(); j++, m++)
   {
    ss_xnew[j+1] = mModel.Moiety[m].IConc;
    for( l=0; l<mModel->getIndMetab(); l++)
     ss_xnew[j+1] -= mModel.ConsRel[j][l] * ss_xnew[l+1];
   }
  try
  {
    FEval( 0, 0, ss_xnew, ss_dxdt );
    ss_nfunction++;
    nmaxrate = SS_XNorn( ss_dxdt );
  }
  //finally
  //{
  //}
  }
  if( i==32 )
  {
    if( maxrate < SSRes )
    {
    ss_solution = SS_FOUND;
	// check if solution is valid
    for( i=0; i<mModel->getDepMetab(); i++ )
     if( ss_x[i+1] < 0.0 )
     {
      ss_solution = SS_NOT_FOUND;
 	  break;
     }

     // from Yongqun
    Cleanup();

     return;
    }
    else
    {
     ss_solution = SS_DAMPING_LIMIT;

     // from Yongqun
    Cleanup();

     return;
    }
   }
   for(i=0;i<mModel->getDepMetab();i++) ss_x[i+1] = ss_xnew[i+1];
   maxrate = nmaxrate;
  }
  if( maxrate < SSRes )
  {
  ss_solution = SS_FOUND;
  // check if solution is valid
  for( i=0; i<mModel->getDepMetab(); i++ )
   if( ss_x[i+1] < 0.0 )
   {
    ss_solution = SS_NOT_FOUND; 
    break;
   }

   // from Yongqun
    Cleanup();

   return;
  }
  else
  {
    ss_solution = SS_ITERATION_LIMIT;

    // from Yongqun
    Cleanup();

    return;
  }

  // from Yongqun
    Cleanup();
}



// Clean up internal pointer variables
void CNewton::Cleanup(void)
{
  //copy from void CGepasiDoc::CleanupEngine( void )
  // Newton variables
  delete [] ss_x;
  delete [] ss_xnew;
  delete [] ss_dxdt;
  delete [] ss_h;
  delete [] ss_ipvt;
  for( i=0; i<mModel->getTotMetab()+1; i++ ) delete [] ss_jacob[i];
  delete [] ss_jacob;
}


// this function evaluates the balance equations
void CNewton::FEval(int num, double time, double *y, double *ydot )
{
 register int i, j, k;
 for(i=0;i<Mdl->IndMetab;i++)
 {
  ydot[i+1] = 0.0;
  for( j=0; j<Mdl->TotStep; j++ )
  {
   if( Mdl->Stoichiometry[Mdl->Row[i]][Mdl->Col[j]] != 0.0 )
      ydot[i+1] += Mdl->Stoichiometry[Mdl->Row[i]][Mdl->Col[j]]
	  * (*(Mdl->Step[Mdl->Col[j]].Kinetics->Function))((void *)Mdl, &y[1], Mdl->Col[j]);
  }
//  ydot[i+1] *= Mdl->Compartment[Mdl->Metabolite[Mdl->Row[i]].Compart].Volume;
 }
 for( k=0; i<Mdl->IntMetab; i++, k++)
 {
  ydot[i+1] = 0.0;
  for( j=0; j<Mdl->IndMetab; j++)
   ydot[i+1] -= Mdl->ConsRel[i][j] * ydot[j+1];
//  y[i+1] = Mdl->Moiety[k].IConc;
//  for( j=0; j<Mdl->IndMetab; j++)
//   y[i+1] -= Mdl->ConsRel[i][j] * y[j+1];
 }
}


// evaluates the Jacobian matrix
void CNewton::JEval( double *y, double **ydot )
{
 register int i, j;
 double store, temp, *f1, *f2;
 double K1, K2, K3;
 // constants for differentiation by finite differences
 K1 = 1 + DerivFactor;
 K2 = 1 - DerivFactor;
 K3 = 2 * DerivFactor;
 // arrays to store function values
 f1 = new double[mModel->getDepMetab()+1];
 f2 = new double[mModel->getDepMetab()+1];
 // iterate over all metabolites
 for( i=1; i<mModel->getIndMetab()+1; i++ )
 {
  // if y[i] is zero, the derivative will be calculated at a small
  // positive value (no point in considering negative values!).
  // let's stick with SSRes*(1.0+DerivFactor)
  store = y[i];
  if( store < SSRes ) temp = SSRes*K1;
  else temp = store;
  y[i] = temp*K1;
  FEval( 0, 0, y, f1 );
  ss_nfunction++;
  y[i] = temp*K2;
  FEval( 0, 0, y, f2 );
  ss_nfunction++;
  for( j=1; j<mModel.getIndMetab()+1; j++ )
   ydot[j][i] = (f1[j]-f2[j])/(temp*K3);
  y[i] = store;
 }
 delete [] f1;
 delete [] f2;
 ss_njacob++;
}











