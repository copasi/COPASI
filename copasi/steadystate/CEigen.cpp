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
{ 
  // initialise variables
  mEigen_nreal = mEigen_nimag = mEigen_nposreal = mEigen_nnegreal =
    mEigen_nzero = mEigen_ncplxconj = 0.0;


  // 15 parameters for DGEES_()
  // #1: (input) characer*1
  mJobvs = 'N';
  // #2: (input) characer*1
  mSort = 'N';
  // #3: (input) Logical function of two double precision arguments
  mSelect = NULL;            
  // #4: (input) The order of the matrix A 
  mN = 0;
  // #5: (input/output) The double precision array, dimension (LDA,N)
  mA = NULL;    //initialize later
  // #6: (input) The leading dimension of the array A. LDA >= max(1,N)
  //C_INT32 mLDA;
  // #7: (output) an integer
  //C_INT32 mSdim;
  // #8: array with dimension (mN)
  mEigen_r = NULL;       //mWR;
  // #9: array with dimension (mN)
  mEigen_i = NULL;       //mWI;
  // #10: (output) array with dimension (mLdvs, mN)
  mVS = NULL;
  // #11: an integer, the leading dimension of the array VS. mLdvs >= 1;
  mLdvs = 1;
  // #12: (workspace/output) double precision array, dimension (mLWork)
  mWork = NULL;
  // #13: (input) Dimension of array Work, its value >= max(1,3*mN).
  mLWork = 4096;
  // #14: (workspace) Logical array, dimension (N)
  mBWork = NULL;
  // #15: (output) an integer
  //C_INT32 mInfo;

  //initialize();
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
//TNT::Matrix < C_FLOAT64 > CEigen::getMatrix()
//{
//  return mMatrix;
//}

/**
 * Set the Matrix
 */
//void CEigen::setMatrix(C_INT32 rows, C_INT32 cols)
//{
//  mMatrix.newsize(rows, cols);
//}
	
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

/**
 * #: Set the mN
 */
void CEigen::setN(C_INT32  aN)
{
  mN = aN;
}




//Get the max eigenvalue real part
C_FLOAT64  CEigen::getEigen_maxrealpart()
{
  return mEigen_maxrealpart;
}


//Get the max eigenvalue imaginary  part
C_FLOAT64 CEigen::getEigen_maximagpart()
{
  return mEigen_maximagpart;
}

  
// Get the number of zero eigenvalues
C_FLOAT64 CEigen::getEigen_nzero()
{
  return mEigen_nzero;
}
 
//Get the eigenvalue stiffness  
C_FLOAT64 CEigen::getEigen_stiffness()
{
  return mEigen_stiffness;
}
  
//Get the eigenvalue hierarchy  
C_FLOAT64 CEigen::getEigen_hierarchy()
{
  return mEigen_hierarchy;
}


//initialize variables for eigenvalue calculations
//
void CEigen::initialize()
{

  // distribute memory for Eigenvalue variables
  //mEigen_r = new double[Model.TotMetab];
  //mEigen_i = new double[Model.TotMetab];
  //mA = new double[Model.TotMetab*Model.TotMetab];

  //different from the original initialization ????
  mEigen_r = new double[mN];
  mEigen_i = new double[mN];
  mA = new double[mN*mN];

} 


// eigenvalue calculatiosn
void CEigen::CalcEigenvalues(C_FLOAT64 SSRes, TNT::Matrix<C_FLOAT64>  ss_jacob)
{ 

  //int res;
  //char jobvs = 'N';        //#1
  //char sort = 'N';         //#2

  //C_INT32 lda;
  C_INT32 mLDA;            //#6
  //C_INT32 sdim;
  C_INT32 mSdim;           //#7
  // int n, pz, mx, mn;      // YH: don't use "long" any more
  C_INT32 pz, mx, mn;            // YH: n is the 4th parameter, not here
  //C_INT32 ldvs = 1;       //#11
  //double *work;            //#12
  //C_INT32 lwork = 4096;   //#13
  //C_INT32 info;    //#15
  C_INT32 i, j;
  double distt, maxt, tott;

  // the dimension of the matrix
  //n = Model.IndMetab;
  //lda = n>1 ? n : 1;
  //mN = Model.IndMetab;     //mModel->getIndMetab(); //been set outside
  mLDA = mN>1 ? mN : 1;

  // create the matrices
  mWork = new double[mLWork];

  // copy the jacobian into J
  // for( i=0; i<n; i++ )
  // for( j=0; j<n; j++ )
  //  eigen_jacob[i*n+j] = ss_jacob[i+1][j+1];
  for( i=0; i<mN; i++ )
    for( j=0; j<mN; j++ )
      //mA[i*mN+j] = ss_jacob[i+1][j+1];
      mA[i*mN+j] = ss_jacob[i][j];

  // calculate the eigenvalues
  //res = dgees_( &mJobvs,                     
  dgees_( &mJobvs,                 
          &mSort,                      
          NULL, // mSelect,           //NULL,   
          &mN,                //&n,    
          mA,                    
          & mLDA,            
          & mSdim,        // output
          mEigen_r,         
          mEigen_i,               
          mVS,              
          & mLdvs,       
          mWork,            
          & mLWork,               
          mBWork,            //NULL
          &mInfo);            //output

  // release the work array
  delete [] mWork;
  // initialise variables
  //mEigen_nreal = mEigen_nimag = mEigen_nposreal = mEigen_nnegreal =
  //mEigen_nzero = mEigen_ncplxconj = 0.0;

  // sort the eigenvalues
  quicksort( mEigen_r, mEigen_i, 0, mN-1 );
  // search for the number of positive real parts
  for( pz=0; pz<mN; pz++ )
    if( mEigen_r[pz] < 0.0 ) break;
  // calculate various eigenvalue statistics
  mEigen_maxrealpart = mEigen_r[0];
  mEigen_maximagpart = fabs(mEigen_i[0]);
  for( i=0; i<mN; i++ )
    {
      // for the largest real part
      if( mEigen_r[i] > mEigen_maxrealpart ) mEigen_maxrealpart = mEigen_r[i];
      // for the largest imaginary part
      if( fabs(mEigen_i[i]) > mEigen_maximagpart ) mEigen_maximagpart = fabs(mEigen_i[i]);
      if( fabs(mEigen_r[i]) > SSRes )
        {
          // positive real part
          if( mEigen_r[i]>=SSRes ) mEigen_nposreal += 1.0;
          // negative real part
          if( mEigen_r[i]<=-SSRes ) mEigen_nnegreal += 1.0;
          if( fabs(mEigen_i[i]) > SSRes )
            {
              // complex
              mEigen_ncplxconj += 1.0;
            }
          else
            {
              // pure real
              mEigen_nreal += 1.0;
            }
        }
      else
	{
	  mx = mN-1; // index of the largest absolute real part
	  mn = 0; // index of the smallest absolute real part
	}
      mEigen_stiffness = fabs( mEigen_r[mx] ) / fabs( mEigen_r[mn] );
      maxt = tott = fabs( 1/mEigen_r[mn] );
      distt = 0.0;
      for( i=1; i<mN; i++ )
	if( i!=mn )
	  {
	    distt += maxt - fabs( 1/mEigen_r[i] );
	    tott += fabs( 1/mEigen_r[i] );
	  }
      mEigen_hierarchy = distt / tott / (mN-1);
    }
 
  maxt = tott = fabs( 1/mEigen_r[mn] );
  distt = 0.0;
  for( i=1; i<mN; i++ )
    if( i!=mn )
      {
        distt += maxt - fabs( 1/mEigen_r[i] );
        tott += fabs( 1/mEigen_r[i] );
      }
  mEigen_hierarchy = distt / tott / (mN-1);
}

// routines for sorting one matrix taking along another one
// useful to sort complex numbers by their real or imaginary parts
C_INT32 CEigen::qs_partition(double *A, double *B, C_INT32 p, C_INT32 r)
{
  C_INT32 done=0, i=p, j=r;
  double a, b, x=A[p];
  while (!done)
    {
      while( (A[j] <= x) && (j > p) ) j--;
      while( (A[i] > x) && (i < r) ) i++;
      if( i < j )
        {
          a = A[i];
          A[i] = A[j];
          A[j] = a;
          b = B[i];
          B[i] = B[j];
          B[j] = b;
        }
      else
        {
          done = 1;
          return j;
        }
    }
  return 0;
}
 
void CEigen::quicksort(double *A, double *B, C_INT32 p, C_INT32 r)
{
  C_INT32 q;
  if( p < r )
    {
      q = qs_partition( A, B, p, r );
      quicksort( A, B, p, q );
      quicksort( A, B, q+1, r );
    }
}

/**
 * Return number of real eigenvalues	WeiSun 3/28/02
 */
C_FLOAT64 CEigen::getEigen_nreal()
{
	return mEigen_nreal;
}

/**
 * Return the number of imaginary eigenvalue numbers
 */
C_FLOAT64 CEigen::getEigen_nimag()
{
	return mEigen_nimag;
}

C_FLOAT64 CEigen::getEigen_ncplxconj()
{
	return mEigen_ncplxconj;
}

/**
 * Return the number of eigenvalues with positive real part
 */
C_FLOAT64 CEigen::getEigen_nposreal()
{
	return mEigen_nposreal;
}

/**
 * Return the number of eigenvalues with negative real part
 */
C_FLOAT64 CEigen::getEigen_nnegreal()
{
	return mEigen_nnegreal;
}

C_FLOAT64 * CEigen::getEigen_i()
{
	return mEigen_i;
}

C_FLOAT64 * CEigen::getEigen_r()
{
	return mEigen_r;
}

