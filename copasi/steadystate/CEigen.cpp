/**
 *  File name: CEigen.cpp
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .cpp file for the class CEigen.
 *           It is to calculate eigenvalues and eigenvectors of a matrix.
 *
 */

#include <cmath>

#define  COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "utilities/readwrite.h"
#include "utilities/CCopasiMessage.h"

#include "CEigen.h"

#include "clapackwrap.h"        //use CLAPACK

/**
 * Default constructor
 */
CEigen::CEigen()
{
  CONSTRUCTOR_TRACE;
  // initialise variables
  mEigen_nreal = mEigen_nimag = mEigen_nposreal = mEigen_nnegreal =
                                  mEigen_nzero = mEigen_ncplxconj = 0;

  // 15 parameters for DGEES_()
  // #1: (input) characer*1
  mJobvs = 'N';
  // #2: (input) characer*1
  mSort = 'N';
  // #3: (input) Logical function of two double precision arguments
  mSelect = NULL;
  // #4: (input) The order of the matrix A
  mN = 0;
  // #6: (input) The leading dimension of the array A. LDA >= max(1,N)
  //C_INT32 mLDA;
  // #7: (output) an integer
  //C_INT32 mSdim;
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
}

/**
 * Deconstructor
 */
CEigen::~CEigen() {DESTRUCTOR_TRACE;}

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

//Get the max eigenvalue real part
const C_FLOAT64 & CEigen::getEigen_maxrealpart() const
  {
    return mEigen_maxrealpart;
  }

//Get the max eigenvalue imaginary  part
const C_FLOAT64 & CEigen::getEigen_maximagpart() const
  {
    return mEigen_maximagpart;
  }

// Get the number of zero eigenvalues
const C_INT32 & CEigen::getEigen_nzero() const
  {
    return mEigen_nzero;
  }

//Get the eigenvalue stiffness
const C_FLOAT64 & CEigen::getEigen_stiffness() const
  {
    return mEigen_stiffness;
  }

//Get the eigenvalue hierarchy
const C_FLOAT64 & CEigen::getEigen_hierarchy() const
  {
    return mEigen_hierarchy;
  }

//initialize variables for eigenvalue calculations
//
void CEigen::initialize()
{
  cleanup();

  mEigen_nreal = mEigen_nimag = mEigen_nposreal = mEigen_nnegreal =
                                  mEigen_nzero = mEigen_ncplxconj = 0;

  mLDA = mN > 1 ? mN : 1;

  mEigen_r.resize(mN);
  mEigen_i.resize(mN);

  mLWork = mN > 1365 ? mN * 3 : 4096;

  mWork = new C_FLOAT64[mLWork];
}

void CEigen::cleanup()
{
  pdelete(mWork);
}

void CEigen::calcEigenValues(const CMatrix< C_FLOAT64 > & matrix)
{
  assert (matrix.numRows() == matrix.numCols());
  mN = matrix.numRows();
  initialize();

  // copy the jacobian into mA
  mA = matrix;

  // calculate the eigenvalues
  /* int dgees_(char *jobvs,
   *             char *sort,
   *            L_fp select,
   *            integer *n, 
   *            doublereal *a,
   *            integer *lda,
   *            integer *sdim,
   *            doublereal *wr, 
   *            doublereal *wi,
   *            doublereal *vs,
   *            integer *ldvs,
   *            doublereal *work, 
   *            integer *lwork, 
   *            logical *bwork,
   *            integer *info); 
   *  Arguments
   *  =========
   *
   *  JOBVS   (input) CHARACTER*1
   *          = 'N': Schur vectors are not computed;
   *          = 'V': Schur vectors are computed.
   *
   *  SORT    (input) CHARACTER*1
   *          Specifies whether or not to order the eigenvalues on the
   *          diagonal of the Schur form.
   *          = 'N': Eigenvalues are not ordered;
   *          = 'S': Eigenvalues are ordered (see SELECT).
   *
   *  SELECT  (input) LOGICAL FUNCTION of two DOUBLE PRECISION arguments
   *          SELECT must be declared EXTERNAL in the calling subroutine.
   *          If SORT = 'S', SELECT is used to select eigenvalues to sort
   *          to the top left of the Schur form.
   *          If SORT = 'N', SELECT is not referenced.
   *          An eigenvalue WR(j)+sqrt(-1)*WI(j) is selected if
   *          SELECT(WR(j),WI(j)) is true; i.e., if either one of a complex
   *          conjugate pair of eigenvalues is selected, then both complex
   *          eigenvalues are selected.
   *          Note that a selected complex eigenvalue may no longer
   *          satisfy SELECT(WR(j),WI(j)) = .TRUE. after ordering, since
   *          ordering may change the value of complex eigenvalues
   *          (especially if the eigenvalue is ill-conditioned); in this
   *          case INFO is set to N+2 (see INFO below).
   *
   *  N       (input) INTEGER
   *          The order of the matrix A. N >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
   *          On entry, the N-by-N matrix A.
   *          On exit, A has been overwritten by its real Schur form T.
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A.  LDA >= max(1,N).
   *
   *  SDIM    (output) INTEGER
   *          If SORT = 'N', SDIM = 0.
   *          If SORT = 'S', SDIM = number of eigenvalues (after sorting)
   *                         for which SELECT is true. (Complex conjugate
   *                         pairs for which SELECT is true for either
   *                         eigenvalue count as 2.)
   *
   *  WR      (output) DOUBLE PRECISION array, dimension (N)
   *  WI      (output) DOUBLE PRECISION array, dimension (N)
   *          WR and WI contain the real and imaginary parts,
   *          respectively, of the computed eigenvalues in the same order
   *          that they appear on the diagonal of the output Schur form T.
   *          Complex conjugate pairs of eigenvalues will appear
   *          consecutively with the eigenvalue having the positive
   *          imaginary part first.
   *
   *  VS      (output) DOUBLE PRECISION array, dimension (LDVS,N)
   *          If JOBVS = 'V', VS contains the orthogonal matrix Z of Schur
   *          vectors.
   *          If JOBVS = 'N', VS is not referenced.
   *
   *  LDVS    (input) INTEGER
   *          The leading dimension of the array VS.  LDVS >= 1; if
   *          JOBVS = 'V', LDVS >= N.
   *
   *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK)
   *          On exit, if INFO = 0, WORK(1) contains the optimal LWORK.
   *
   *  LWORK   (input) INTEGER
   *          The dimension of the array WORK.  LWORK >= max(1,3*N).
   *          For good performance, LWORK must generally be larger.
   *
   *          If LWORK = -1, then a workspace query is assumed; the routine
   *          only calculates the optimal size of the WORK array, returns
   *          this value as the first entry of the WORK array, and no error
   *          message related to LWORK is issued by XERBLA.
   *
   *  BWORK   (workspace) LOGICAL array, dimension (N)
   *          Not referenced if SORT = 'N'.
   *
   *  INFO    (output) INTEGER
   *          = 0: successful exit
   *          < 0: if INFO = -i, the i-th argument had an illegal value.
   *          > 0: if INFO = i, and i is
   *             <= N: the QR algorithm failed to compute all the
   *                   eigenvalues; elements 1:i-1 and i+1:N of WR and WI
   *                   contain those eigenvalues which have converged; if
   *                   JOBVS = 'V', VS contains the matrix which reduces A
   *                   to its partially converged Schur form.
   *             = N+1: the eigenvalues could not be reordered because some
   *                   eigenvalues were too close to separate (the problem
   *                   is very ill-conditioned);
   *             = N+2: after reordering, roundoff changed values of some
   *                   complex eigenvalues so that leading eigenvalues in
   *                   the Schur form no longer satisfy SELECT=.TRUE.  This
   *                   could also be caused by underflow due to scaling.
   *
   */
  dgees_(&mJobvs,
         &mSort,
         NULL,      // mSelect,           //NULL,
         &mN,                     //&n,
         mA.array(),
         & mLDA,
         & mSdim,             // output
         mEigen_r.array(),
         mEigen_i.array(),
         mVS,
         & mLdvs,
         mWork,
         & mLWork,
         mBWork,               //NULL
         &mInfo);            //output

  if (mInfo) fatalError();
}

void CEigen::stabilityAnalysis(const C_FLOAT64 & resolution)
{
  C_INT32 mx, mn;            // YH: n is the 4th parameter, not here
  C_INT32 i;
  C_FLOAT64 distt, maxt, tott;
  mResolution = resolution;

  // sort the eigenvalues
  quicksort(mEigen_r, mEigen_i, 0, mN - 1);

  // calculate various eigenvalue statistics
  mEigen_maxrealpart = mEigen_r[0];
  mEigen_maximagpart = fabs(mEigen_i[0]);

  for (i = 0; i < mN; i++)
    {
      // for the largest real part
      if (mEigen_r[i] > mEigen_maxrealpart)
        mEigen_maxrealpart = mEigen_r[i];
      // for the largest imaginary part
      if (fabs(mEigen_i[i]) > mEigen_maximagpart)
        mEigen_maximagpart = fabs(mEigen_i[i]);

      if (fabs(mEigen_r[i]) > resolution)
        {
          // positive real part
          if (mEigen_r[i] >= resolution)
            mEigen_nposreal++;
          // negative real part
          if (mEigen_r[i] <= -resolution)
            mEigen_nnegreal++;
          if (fabs(mEigen_i[i]) > resolution)
            {
              // complex
              mEigen_ncplxconj++;
            }
          else
            {
              // pure real
              mEigen_nreal++;
            }
        }
      else
        {
          if (fabs(mEigen_i[i]) > resolution)
            {
              // pure imaginary
              mEigen_nimag++;
            }
          else
            {
              // zero
              mEigen_nzero++;
            }
        }
    }

  if (mEigen_nposreal > 0)
    {
      if (mEigen_r[0] > fabs(mEigen_r[mN - 1]))
        mx = 0;
      else
        mx = mN - 1;
      if (mEigen_nposreal == mN)
        mn = mEigen_nposreal - 1;
      else if (mEigen_r[mEigen_nposreal - 1] < fabs(mEigen_r[mEigen_nposreal]))
        mn = mEigen_nposreal - 1;
      else
        mn = mEigen_nposreal;
    }
  else
    {
      mx = mN - 1; // index of the largest absolute real part
      mn = 0; // index of the smallest absolute real part
    }

  mEigen_stiffness = fabs(mEigen_r[mx]) / fabs(mEigen_r[mn]);

  maxt = tott = fabs(1 / mEigen_r[mn]);
  distt = 0.0;
  for (i = 1; i < mN; i++)
    if (i != mn)
      {
        distt += maxt - fabs(1 / mEigen_r[i]);
        tott += fabs(1 / mEigen_r[i]);
      }
  mEigen_hierarchy = distt / tott / (mN - 1);
}

// routines for sorting one matrix taking along another one
// useful to sort complex numbers by their real or imaginary parts
C_INT32 CEigen::qs_partition(CVector< C_FLOAT64 > & A, CVector< C_FLOAT64 > & B,
                             C_INT32 p, C_INT32 r)
{
  C_INT32 done = 0, i = p, j = r;
  C_FLOAT64 a, b, x = A[p];
  while (!done)
    {
      while ((A[j] <= x) && (j > p))
        j--;
      while ((A[i] > x) && (i < r))
        i++;
      if (i < j)
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

void CEigen::quicksort(CVector< C_FLOAT64 > & A, CVector< C_FLOAT64 > & B,
                       C_INT32 p, C_INT32 r)
{
  C_INT32 q;
  if (p < r)
    {
      q = qs_partition(A, B, p, r);
      quicksort(A, B, p, q);
      quicksort(A, B, q + 1, r);
    }
}

/**
 * Return number of real eigenvalues WeiSun 3/28/02
 */
const C_INT32 & CEigen::getEigen_nreal() const
  {
    return mEigen_nreal;
  }

/**
 * Return the number of imaginary eigenvalue numbers
 */
const C_INT32 & CEigen::getEigen_nimag() const
  {
    return mEigen_nimag;
  }

const C_INT32 & CEigen::getEigen_ncplxconj() const
  {
    return mEigen_ncplxconj;
  }

/**
 * Return the number of eigenvalues with positive real part
 */
const C_INT32 & CEigen::getEigen_nposreal() const
  {
    return mEigen_nposreal;
  }

/**
 * Return the number of eigenvalues with negative real part
 */
const C_INT32 & CEigen::getEigen_nnegreal() const
  {
    return mEigen_nnegreal;
  }

const CVector< C_FLOAT64 > & CEigen::getEigen_i() const
  {return mEigen_i;}

const CVector< C_FLOAT64 > & CEigen::getEigen_r() const
  {return mEigen_r;}
