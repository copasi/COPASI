/**
 *  File name: CEigen.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .h file for the class CEigen. 
 *           It is to calculate eigenvalues and eigenvectors of a matrix.
 *
 */

#ifndef COPASI_CEigen
#define COPASI_CEigen

#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include "copasi.h"

//include clapack.h for eigenvalue calculations0
extern "C" {
#include "CLAPACK/clapack.h"
}


/*
extern "C" int dgees_(char *jobvs, char *sort, L_fp select, long int *n,
        double *a, long int *lda, long int *sdim, double *wr,
        double *wi, double *vs, long int *ldvs, double *work,
        long int *lwork, long int *bwork, long int *info);
*/


class CEigen {

 private:
  /**
   * A Matrix
   */

  TNT::Matrix <C_FLOAT64> mMatrix;

  /**
   * Workspace/output
   */
  C_FLOAT64 * mWork;

  /**
   * Dimension of array Work
   */
  C_INT32 mLWork;

  /**
   * 
   */


  /**
   * 
   */


  /**
   * 
   */



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
  CEigen(int rows, int cols);


  /**
   * Destructor
   */

  ~CEigen();

 
  /**
   * return the matrix
   */
  TNT::Matrix < C_FLOAT64 > getMatrix();

  /**
   * Set the Matrix
   */
  void setMatrix(int rows, int cols);


  /**
   * Set the Work
   */
  void CEigen::setWork(C_FLOAT64 * aWork);

  /**
   * Get the Work
   */
  C_FLOAT64 * CEigen::getWork() const;




  /**
   * Eigenvalue calculations
   */
  void CalcEigenvalues();




};

#endif









