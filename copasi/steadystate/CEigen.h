/**
 *  File name: CEigen.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .h file for the class CEigen. 
 *           It is to calculate eigenvalues and eigenvectors of a matrix.
 *           It mainly uses the dgees_() subroutine of CLAPACK
 *
 */

#ifndef COPASI_CEigen
#define COPASI_CEigen

#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include "copasi.h"
#include <cmath>
//#include "clapack.h"

//include clapack.h for eigenvalue calculations0
extern "C" {
  //#ifdef __cplusplus
  //#define __old__cplusplus __cplusplus
  //#undef __cplusplus
  //#endif
#include "clapack.h"       //use CLAPACK
  //#ifdef __old__cplusplus
  //#define __cplusplus __old__cplusplus
  //#undef __old__cplusplus
  //#endif
}

/*
extern "C" void DGEES(char *JOBVS, char *SORT, int *SELECT, int *N, double *A, int *LDA, int *SDIM, double *WR, double *WI, double *VS, int *LDVS, double *WORK, int *LWORK, int *BWORK, int *INFO);
*/

/*
extern "C" int dgees_(char *jobvs, char *sort, L_fp select, long int *n,
        double *a, long int *lda, long int *sdim, double *wr,
        double *wi, double *vs, long int *ldvs, double *work,
        long int *lwork, long int *bwork, long int *info);
*/

class CEigen {

 private:
  /**
   * A Matrix, 
   * If input is a TNT matrix, a transformation of it to arrays will 
   * be performed
   */
  //TNT::Matrix <C_FLOAT64> mMatrix;
 
 // variables for stability analysis
 
 /**
  * the real part of the maximum eigenvalue
  */
 C_FLOAT64 mEigen_maxrealpart;

/**
  * the imaginary part of the maximum eigenvalue
  */
 C_FLOAT64  mEigen_maximagpart;

/**
  * the number of eigenvalues with positive real part
  */
 C_FLOAT64  mEigen_nposreal;

/**
  * the number of eigenvalues with negative real part
  */
 C_FLOAT64  mEigen_nnegreal;

/**
  * the number of real eigenvalues
  */
 C_FLOAT64  mEigen_nreal;

/**
  * the number of imaginary eigenvalue numbers
  */
 C_FLOAT64  mEigen_nimag;

/**
  * 
  */
 C_FLOAT64 mEigen_ncplxconj;

/**
  * the number of eigenvalues with value of zero
  */
 C_FLOAT64  mEigen_nzero;

/**
  * the stiffness of eigenvalues
  */
 C_FLOAT64  mEigen_stiffness;

/**
  * the hierary of the eigenvalues
  */
 C_FLOAT64  mEigen_hierarchy;


  //there are 15 parameters in the dgees() subroutine

  /**
   * #1: (input) characer*1
   * = 'N': Schur vectors are not computed
   * = 'V': Schur vectors are computed
   */
  char mJobvs;

 /**
   * #2: (input) characer*1
   * = 'N': Eigenvalues are not ordered  
   * = 'S': Eigenvalues are ordered 
   */
  char mSort;
 

  /**
   * #3: (input) Logical function of two double precision arguments
   * It must be declared external
   * = 'S': Select is used to select eigenvalues to sort to the top left
   * of the Schur form 
   * = 'N': Eigenvalues are ordered Select is not refereced.
   */
  //char mSelect;
  C_INT32 * mSelect;

  /**
   * #4: (input) The order of the matrix A 
   */
  C_INT32 mN;

 
  /**
   * #5: (input/output) The double precision array, dimension (LDA,N)
   * On entry, the N-by-N matrix A
   * On exit, A has been overwritten by its real Schur form T
   * Use a pointer variable here instead of array since we don't know
   * the dimension yet.
   */
  C_FLOAT64 * mA;


  /**
   * #6: (input) The leading dimension of the array A. LDA >= max(1,N)
   */
  C_INT32 mLDA;

  /**
   * #7: (output) an integer
   * if Sort = 'N', its value is 0
   * if Sort = 'S', its value = number of eigenvalues (after sorting)
   *                for which mSelect is true.
   */
  C_INT32 mSdim;

  /**
   * #8: array with dimension (mN)
   */
  C_FLOAT64 * mEigen_r;


  /**
   * #9: array with dimension (mN)
   */
  C_FLOAT64 * mEigen_i;

  /**
   * #10: (output) array with dimension (mLdvs, mN)
   * If mJobvs='V', mVS contains the orthogoanl matrix Z of Schur vectors
   * If mJobvs='N', mVS is not referenced
   */
  C_FLOAT64 * mVS;

  /**
   * #11: an integer, the leading dimension of the array VS. mLdvs >= 1;
   * if mJobvs='V', mLdvs >= N.
   */
  C_INT32 mLdvs;

  /**
   * #12: (workspace/output) double precision array, dimension (mLWork)
   * On exit, if mInfo=0; mWork(1) contains the optimal mLWork
   */
  C_FLOAT64 * mWork;

  /**
   * #13: (input) Dimension of array Work, its value >= max(1,3*mN).
   * For good performance, it must generally be larger
   */
  C_INT32 mLWork;

  /**
   * #14: (workspace) Logical array, dimension (N)
   * Not referenced if mSort = 'N'
   */
  C_INT32 * mBWork;


  /**
   * #15: (output) an integer
   * =0: successful exit
   * <0: if mInfo=-i, the ith argument had an illegal value
   * >0: if mInfo=i, and i is
   *     <=N: the QR algorithm failed to compute all the eigenvalues;
   *     =N+1: the eigenvalues could not be reordered because some 
   *           eigenvalues were too close to separate (ill-conditioned)
   *     =N+2: after reordering, roundoff changed values of some 
   *           complex eigenvalues so that leading eigenvalues in the
   *           Schur form no longer satisfy mSelect=.True. This could
   *           caused by underflow due to scaling
   */
  C_INT32 mInfo;


  /** 
   * sorts two arrays using one as the criterion for sorting 
   */
  C_INT32 qs_partition(double *A, double *B, C_INT32 p, C_INT32 r);

  /** 
   * Do quicksort with 2 arrays of double. 
   * One is the array of the real part of the eigenvalues.
   * another is the array of the imaginary part of the eigenvalues
   */
  void quicksort(double *A, double *B, C_INT32 p, C_INT32 r);


 public:
  /**
   * Defaulut constructor
   */ 
  CEigen();

  /**
   * User defined constructor
   * @param rows is the max row number of the Matrix
   * @param cols is the max column number of the Matrix
   */
  //CEigen(C_INT32 rows, C_INT32 cols);

  /**
   * Destructor
   */

  ~CEigen();


 /**
   * initialize variables for eigenvalue calculations
   */

  void initialize();

 
  /**
   * return the matrix
   */
  //TNT::Matrix < C_FLOAT64 > getMatrix();

  /**
   * Set the Matrix
   */
  //void setMatrix(C_INT32 rows, C_INT32 cols);


  /**
   * #12: Set the Work
   */
  void setWork(C_FLOAT64 * aWork);

  /**
   * #12: Get the Work
   */
  C_FLOAT64 * getWork() const;


  /**
   * #: Set the mN
   */
  void setN(C_INT32  aN);


  /**
   * Eigenvalue calculations
   * @param SSRes the steady state resolution.
   */
  void CalcEigenvalues(C_FLOAT64 SSRes, TNT::Matrix<C_FLOAT64> ss_jacob);


  /**
   * Get the max eigenvalue real part
   */
  C_FLOAT64  getEigen_maxrealpart();


  /**
   * Get the max eigenvalue imaginary  part
   */
  C_FLOAT64 getEigen_maximagpart();


  /**
   * Get the number of zero eigenvalues
   */
  C_FLOAT64 getEigen_nzero();

  /**
   * Get the eigenvalue stiffness
   */
  C_FLOAT64 getEigen_stiffness();

  /**
   * Get the eigenvalue hierarchy
   */
  C_FLOAT64 getEigen_hierarchy();


};

#endif









