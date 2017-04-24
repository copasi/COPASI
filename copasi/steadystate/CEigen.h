// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"

class CEigen: public CDataContainer
{
private:
  // variables for stability analysis

  /**
   * the real part of the maximum eigenvalue
   */
  C_FLOAT64 mMaxrealpart;

  /**
   * the imaginary part of the maximum eigenvalue
   */
  C_FLOAT64 mMaximagpart;

  /**
   * the number of eigenvalues with positive real part
   */
  size_t mNposreal;

  /**
   * the number of eigenvalues with negative real part
   */
  size_t mNnegreal;

  /**
   * the number of real eigenvalues
   */
  size_t mNreal;

  /**
   * the number of imaginary eigenvalue numbers
   */
  size_t mNimag;

  /**
   *
   */
  size_t mNcplxconj;

  /**
   * the number of eigenvalues with value of zero
   */
  size_t mNzero;

  /**
   * the stiffness of eigenvalues
   */
  C_FLOAT64 mStiffness;

  /**
   * the hierary of the eigenvalues
   */
  C_FLOAT64 mHierarchy;

  /**
   * largest real part of a complex eigenvalue.
   * If there is no complex eigenvalue it will be the smallest ev.
   */
  C_FLOAT64 mMaxRealOfComplex;

  /**
   * imaginary part of complex with largest real part
   */
  C_FLOAT64 mImagOfMaxComplex;

  /**
   * frequency of complex with largest real part
   */
  C_FLOAT64 mFreqOfMaxComplex;

  /**
   * An index that is supposed to indicate the presence of oscillations
   */
  C_FLOAT64 mOscillationIndicator;

  /**
  * A heuristical index that is supposed to indicate the presence of oscillations, based on Eigenvalues
  */
  C_FLOAT64 mOscillationIndicator_EV;

  /**
   * A bifurcation test function, it is 0 for a Hopf-bifurcation. Definition according to Kuznetsov.
   * This is only a necessary, not a sufficient condition for a H.-bifurcation
   */
  C_FLOAT64 mBifurcationIndicator_Hopf;

  /**
   * A bifurcation test function, it is 0 for a Fold-type bifurcation.
   */
  C_FLOAT64 mBifurcationIndicator_Fold;

  /**
   * A bifurcation test function, defined according to the "Bifurcation Discovery Tool", Chickarmane et al 2005
   */
  C_FLOAT64 mBifurcationIndicator_Hopf_BDT;

  /**
   * A bifurcation test function, defined according to the "Bifurcation Discovery Tool", Chickarmane et al 2005
   */
  C_FLOAT64 mBifurcationIndicator_Fold_BDT;

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
  C_INT32 * mpSelect;

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
  CVector< C_FLOAT64 > mR;

  /**
   * #9: array with dimension (mN)
   */
  CVector< C_FLOAT64 > mI;

  /**
   * #10: (output) array with dimension (mLdvs, mN)
   * If mJobvs='V', mVS contains the orthogoanl matrix Z of Schur vectors
   * If mJobvs='N', mVS is not referenced
   */
  C_FLOAT64 * mpVS;

  /**
   * #11: an integer, the leading dimension of the array VS. mLdvs >= 1;
   * if mJobvs='V', mLdvs >= N.
   */
  C_INT mLdvs;

  /**
   * #12: (workspace/output) double precision array, dimension (mLWork)
   * On exit, if mInfo=0; mWork(1) contains the optimal mLWork
   */
  CVector< C_FLOAT64 > mWork;

  /**
   * #13: (input) Dimension of array Work, its value >= max(1,3*mN).
   * For good performance, it must generally be larger
   */
  C_INT mLWork;

  /**
   * #14: (workspace) Logical array, dimension (N)
   * Not referenced if mSort = 'N'
   */
  C_LOGICAL * mpBWork;

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

public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CEigen(const std::string & name = "NoName",
         const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CMetab & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CEigen(const CEigen & src,
         const CDataContainer * pParent);
  /**
   * Destructor
   */
  virtual ~CEigen();

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To overide this default behaviour one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

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
  const C_FLOAT64 & getMaxrealpart() const;

  /**
   * Get the max eigenvalue imaginary  part
   */
  const C_FLOAT64 & getMaximagpart() const;

  /**
   * Get the number of zero eigenvalues
   */
  const size_t & getNzero() const;

  /**
   * Get the eigenvalue stiffness
   */
  const C_FLOAT64 & getStiffness() const;

  /**
   * Get the eigenvalue hierarchy
   */
  const C_FLOAT64 & getHierarchy() const;

  /**
   * Return number of real eigenvalues WeiSun 3/28/02
   */
  const size_t & getNreal() const;

  /**
   * Return the number of imaginary eigenvalue numbers
   */
  const size_t & getNimag() const;

  const size_t & getNcplxconj() const;

  /**
   * Return the number of eigenvalues with positive real part
   */
  const size_t & getNposreal() const;

  /**
   * Return the number of eigenvalues with negative real part
   */
  const size_t & getNnegreal() const;

  const CVector< C_FLOAT64 > & getI() const;

  const CVector< C_FLOAT64 > & getR() const;

  // Friend functions
  friend std::ostream &operator<<(std::ostream &os, const CEigen &A);

private:
  /**
   * Initialize the contained CDataObjects
   */
  void initObjects();
};

#endif
