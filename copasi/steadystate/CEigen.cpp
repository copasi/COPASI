/**
 *  File name: CEigen.cpp
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .cpp file for the class CEigen. 
 *           It is to calculate eigenvalues and eigenvectors of a matrix.
 *
 */


#include "CEigen.h"

/**
 * Defaulut constructor
 */
CEigen::CEigen()
{   }

/**
 * User defined constructor
 * @param rows is the max row number of Matrix
 * @param cols is the max column number of Matrix
 */
CEigen::CEigen(int rows, int cols)
{

  mMatrix.newsize(rows, cols);
}

/**
 * Deconstructor
 */
CEigen::~CEigen()
{
}


/**
 * return the matrix
 */
TNT::Matrix < C_FLOAT64 > CEigen::getMatrix()
{
  return mMatrix;
}

/**
 * Set the Matrix
 */
void CEigen::setMatrix(int rows, int cols)
{
  mMatrix.newsize(rows, cols);
}
	
/**
 * Set the Work
 */
void CEigen::setWork(C_FLOAT64 * aWork)
{
  mWork = aWork;
}

/**
 * Get the Work
 */
C_FLOAT64 * CEigen::getWork() const
{
  return mWork;
}

// eigenvalue calculations
void CEigen::CalcEigenvalues( void )
{

  /* 
 int res;
 char jobvs = 'N';
 char sort = 'N';

 long int lda;
 long int sdim;
 int n, pz, mx, mn;        // YH: don't use "long" any more
 long int ldvs = 1;
 double *work;
 long int lwork = 4096;
 long int info;
 int i, j;
 double distt, maxt, tott;

 // the dimension of the matrix
 n = Model.IndMetab;
 lda = n>1 ? n : 1;

 // create the matrices
 work = new double[lwork];

 // copy the jacobian into J
 for( i=0; i<n; i++ )
  for( j=0; j<n; j++ )
   eigen_jacob[i*n+j] = ss_jacob[i+1][j+1];

 // calculate the eigenvalues
 res = dgees_( &jobvs,                     //ok
              &sort,                       //ok
                          NULL,            //ok
                          &n,              //ok
                  eigen_jacob,             //ok
                          &lda,            //ok
                          &sdim,           //ok
                          eigen_r,         //????? 8
                  eigen_i,                 //????? 9
                          NULL,            //ok
                          &ldvs,           //ok
                          work,            //ok
                  &lwork,                  //ok
                          NULL,            //ok
                          &info);          //ok

 // release the work array
 delete [] work;
 // initialise variables
 eigen_nreal = eigen_nimag = eigen_nposreal = eigen_nnegreal =
 eigen_nzero = eigen_ncplxconj = 0.0;

 // sort the eigenvalues
 qsort( eigen_r, eigen_i, 0, n-1 );
 // search for the number of positive real parts
 for( pz=0; pz<n; pz++ )
  if( eigen_r[pz] < 0.0 ) break;
 // calculate various eigenvalue statistics
 eigen_maxrealpart = eigen_r[0];
 eigen_maximagpart = fabs(eigen_i[0]);
 for( i=0; i<n; i++ )
 {
  // for the largest real part
  if( eigen_r[i] > eigen_maxrealpart ) eigen_maxrealpart = eigen_r[i];
  // for the largest imaginary part
  if( fabs(eigen_i[i]) > eigen_maximagpart ) eigen_maximagpart = fabs(eigen_i[i]);
  if( fabs(eigen_r[i]) > SSRes )
  {
   // positive real part
   if( eigen_r[i]>=SSRes ) eigen_nposreal += 1.0;
   // negative real part
   if( eigen_r[i]<=-SSRes ) eigen_nnegreal += 1.0;
   if( fabs(eigen_i[i]) > SSRes )
   {
    // complex
    eigen_ncplxconj += 1.0;
   }
   else
   {
    // pure real
        eigen_nreal += 1.0;
   }
  }
  else
  {
   if( fabs(eigen_i[i]) > SSRes )
   {
    // pure imaginary
    eigen_nimag += 1.0;
   }
   else
   {
    // zero
        eigen_nzero += 1.0;
   }
  }
 }
 if( pz > 0 )
 {
  if( eigen_r[0] > fabs( eigen_r[n] ) ) mx = 0; else mx = n-1;
  if( eigen_r[pz-1] < fabs( eigen_r[pz] ) ) mn = 0; else mn = pz;
 }
 else
 {
  mx = n-1; // index of the largest absolute real part
  mn = 0; // index of the smallest absolute real part
 }
 eigen_stiffness = fabs( eigen_r[mx] ) / fabs( eigen_r[mn] );
 maxt = tott = fabs( 1/eigen_r[mn] );
 distt = 0.0;
 for( i=1; i<n; i++ )
  if( i!=mn )
  {
   distt += maxt - fabs( 1/eigen_r[i] );
   tott += fabs( 1/eigen_r[i] );
  }
 eigen_hierarchy = distt / tott / (n-1);

  */

}











