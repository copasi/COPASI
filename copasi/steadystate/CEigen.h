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

class CEigen {

 private:
  /**
   * A Matrix
   */

  TNT::Matrix <C_FLOAT64> mMatrix;


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
   * Eigenvalue calculations
   */
  void CalcEigenvalues();




};

#endif









