/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CEigen.h,v $
   $Revision: 1.24 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/03 19:28:20 $
   End CVS Header */

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

#include <iostream>
#include <iomanip>

#include "utilities/CMatrix.h"
#include "utilities/CVector.h"

class CEigen
  {
  private:
    // variables for stability analysis

    /**
     * the real part of the maximum eigenvalue
     */
    C_FLOAT64 mEigen_maxrealpart;

    /**
     * the imaginary part of the maximum eigenvalue
     */
    C_FLOAT64 mEigen_maximagpart;

    /**
     * the number of eigenvalues with positive real part
     */
    C_INT32 mEigen_nposreal;

    /**
     * the number of eigenvalues with negative real part
     */
    C_INT32 mEigen_nnegreal;

    /**
     * the number of real eigenvalues
     */
    C_INT32 mEigen_nreal;

    /**
     * the number of imaginary eigenvalue numbers
     */
    C_INT32 mEigen_nimag;

    /**
     *
     */
    C_INT32 mEigen_ncplxconj;

    /**
     * the number of eigenvalues with value of zero
     */
    C_INT32 mEigen_nzero;

    /**
     * the stiffness of eigenvalues
     */
    C_FLOAT64 mEigen_stiffness;

    /**
     * the hierary of the eigenvalues
     */
    C_FLOAT64 mEigen_hierarchy;

    /**
     * The resolution of needed for the stability analysis
     */
    C_FLOAT64 mResolution;

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
    C_INT mN;

    /**
     * #5: (input/output) The double precision array, dimension (LDA,N)
     * On entry, the N-by-N matrix A
     * On exit, A has been overwritten by its real Schur form T
     * Use a pointer variable here instead of array since we don't know
     * the dimension yet.
     */
    CMatrix< C_FLOAT64 > mA;

    /**
     * #6: (input) The leading dimension of the array A. LDA >= max(1,N)
     */
    C_INT mLDA;

    /**
     * #7: (output) an integer
     * if Sort = 'N', its value is 0
     * if Sort = 'S', its value = number of eigenvalues (after sorting)
     *                for which mSelect is true.
     */
    C_INT mSdim;

    /**
     * #8: array with dimension (mN)
     */
    CVector< C_FLOAT64 > mEigen_r;

    /**
     * #9: array with dimension (mN)
     */
    CVector< C_FLOAT64 > mEigen_i;

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
    C_INT mLdvs;

    /**
     * #12: (workspace/output) double precision array, dimension (mLWork)
     * On exit, if mInfo=0; mWork(1) contains the optimal mLWork
     */
    C_FLOAT64 * mWork;

    /**
     * #13: (input) Dimension of array Work, its value >= max(1,3*mN).
     * For good performance, it must generally be larger
     */
    C_INT mLWork;

    /**
     * #14: (workspace) Logical array, dimension (N)
     * Not referenced if mSort = 'N'
     */
    C_INT * mBWork;

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
    C_INT mInfo;

    /**
     * sorts two arrays using one as the criterion for sorting
     */
    C_INT32 qs_partition(CVector< C_FLOAT64 > & A, CVector< C_FLOAT64 > & B,
                         C_INT32 p, C_INT32 r);

    /**
     * Do quicksort with 2 arrays of double.
     * One is the array of the real part of the eigenvalues.
     * another is the array of the imaginary part of the eigenvalues
     */
    void quicksort(CVector< C_FLOAT64 > & A, CVector< C_FLOAT64 > & B,
                   C_INT32 p, C_INT32 r);

  public:
    /**
     * Defaulut constructor
     */
    CEigen();

    /**
     * Destructor
     */
    ~CEigen();

    /**
     * initialize variables for eigenvalue calculations
     */
    void initialize();

    /**
     * cleanup()
     */
    void cleanup();

    /**
     * Eigenvalue calculations
     * @param const C_FLOAT64 * matrix
     * @param const unsigned C_INT32 & dim
     */
    void calcEigenValues(const CMatrix< C_FLOAT64 > & matrix);

    /**
     *  Calculate various eigenvalue statistics
     */
    void stabilityAnalysis(const C_FLOAT64 & resolution);

    /**
     * Get the max eigenvalue real part
     */
    const C_FLOAT64 & getEigen_maxrealpart() const;

    /**
     * Get the max eigenvalue imaginary  part
     */
    const C_FLOAT64 & getEigen_maximagpart() const;

    /**
     * Get the number of zero eigenvalues
     */
    const C_INT32 & getEigen_nzero() const;

    /**
     * Get the eigenvalue stiffness
     */
    const C_FLOAT64 & getEigen_stiffness() const;

    /**
     * Get the eigenvalue hierarchy
     */
    const C_FLOAT64 & getEigen_hierarchy() const;

    /**
     * Return number of real eigenvalues WeiSun 3/28/02
     */
    const C_INT32 & getEigen_nreal() const;

    /**
     * Return the number of imaginary eigenvalue numbers
     */
    const C_INT32 & getEigen_nimag() const;

    const C_INT32 & getEigen_ncplxconj() const;

    /**
     * Return the number of eigenvalues with positive real part
     */
    const C_INT32 & getEigen_nposreal() const;

    /**
     * Return the number of eigenvalues with negative real part
     */
    const C_INT32 & getEigen_nnegreal() const;

    const CVector< C_FLOAT64 > & getEigen_i() const;

    const CVector< C_FLOAT64 > & getEigen_r() const;

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os, const CEigen &A);
  };

std::ostream &operator<<(std::ostream &os, const CEigen &A)
{
  os << std::endl;
  os << "KINETIC STABILITY ANALYSIS";
  os << std::endl;
  os << "The linear stability analysis based on the eigenvalues" << std::endl;
  os << "of the Jacobian matrix is only valid for steady states." << std::endl;
  os << std::endl;
  os << "Summary:" << std::endl;
  os << "This steady state ";

  // Output statistics

  if (A.mEigen_maxrealpart > A.mResolution)
    os << "is unstable";
  else if (A.mEigen_maxrealpart < -A.mResolution)
    os << "is asymptotically stable";
  else
    os << "stability is undetermined";

  if (A.mEigen_maximagpart > A.mResolution)
    {
      os << "," << std::endl;
      os << "transient states in its vicinity have oscillatory components";
    }

  os << std::endl;
  os << std::endl;

  os << "Eigenvalue statistics:" << std::endl;
  // Output Max Real Part
  os << " Largest real part: ";
  os << std::setprecision(6) << A.mEigen_maxrealpart << std::endl;
  // Output Max imaginary Part
  os << " Largest absolute imaginary part:  ";
  os << std::setprecision(6) << A.mEigen_maximagpart << std::endl;
  // Output Eigen-nreal
  os.unsetf(std::ios_base::scientific);
  os.unsetf(std::ios_base::showpoint);
  os << " " << A.mEigen_nreal;
  os << " are purely real" << std::endl;
  // Output Eigen-nimage
  os << " " << A.mEigen_nimag;
  os << " are purely imaginary" << std::endl;
  // Output Eigen-ncplxconj
  os << " " << A.mEigen_ncplxconj;
  os << " are complex" << std::endl;
  // Output Eigen-nzero
  os << " " << A.mEigen_nzero;
  os << " are equal to zero" << std::endl;
  // Output Eigen-nposreal
  os << " " << A.mEigen_nposreal;
  os << " have positive real part" << std::endl;
  // Output Eigen-nnegreal
  os << " " << A.mEigen_nnegreal;
  os << " have negative real part" << std::endl;

  // Set point manipulators
  os.setf(std::ios_base::showpoint);
  // Output Eigne-stiffness
  os << " stiffness = " << A.mEigen_stiffness << std::endl;
  os << " time hierarchy = " << A.mEigen_hierarchy << std::endl;

  return os;
}

#endif
