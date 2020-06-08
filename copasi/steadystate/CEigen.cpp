// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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
 *  File name: CEigen.cpp
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .cpp file for the class CEigen.
 *           It is to calculate eigenvalues and eigenvectors of a matrix.
 *
 */

#ifdef SunOS
# include <ieeefp.h>
#endif

#ifdef WIN32
# ifndef _USE_MATH_DEFINES
# define _USE_MATH_DEFINES 1
# endif // _USE_MATH_DEFINES
#endif

#include <cmath>
#include <complex>

#include "copasi/copasi.h"

#include "CEigen.h"

#include "copasi/core/CDataObjectReference.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CSort.h"

#include "copasi/lapack/lapackwrap.h"        //use CLAPACK

/**
 * Default constructor
 */
CEigen::CEigen(const std::string & name,
               const CDataContainer * pParent):
  CDataContainer(name, pParent, "Eigen Values",
                 CDataObject::Container),
  mMaxrealpart(0),
  mMaximagpart(0),
  mNposreal(0),
  mNnegreal(0),
  mNreal(0),
  mNimag(0),
  mNcplxconj(0),
  mNzero(0),
  mStiffness(0),
  mHierarchy(0),

  mMaxRealOfComplex(0.0),
  mImagOfMaxComplex(0.0),
  mFreqOfMaxComplex(0.0),
  mOscillationIndicator(0.0),
  mOscillationIndicator_EV(0.0),
  mBifurcationIndicator_Hopf(0.0),
  mBifurcationIndicator_Fold(0.0),
  mBifurcationIndicator_Hopf_BDT(0.0),
  mBifurcationIndicator_Fold_BDT(0.0),

  mResolution(0),
  mJobvs('N'),
  mSort('N'),
  mpSelect(NULL),
  mN(0),
  mA(),
  mLDA(0),
  mSdim(0),
  mR(),
  mI(),
  mpVS(NULL),
  mLdvs(1),
  mWork(1),
  mLWork(4096),
  mpBWork(NULL),
  mInfo(0)
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

CEigen::CEigen(const CEigen & src,
               const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mMaxrealpart(src.mMaxrealpart),
  mMaximagpart(src.mMaximagpart),
  mNposreal(src.mNposreal),
  mNnegreal(src.mNnegreal),
  mNreal(src.mNreal),
  mNimag(src.mNimag),
  mNcplxconj(src.mNcplxconj),
  mNzero(src.mNzero),
  mStiffness(src.mStiffness),
  mHierarchy(src.mHierarchy),

  mMaxRealOfComplex(src.mMaxRealOfComplex),
  mImagOfMaxComplex(src.mImagOfMaxComplex),
  mFreqOfMaxComplex(src.mFreqOfMaxComplex),
  mOscillationIndicator(src.mOscillationIndicator),
  mOscillationIndicator_EV(src.mOscillationIndicator_EV),
  mBifurcationIndicator_Hopf(src.mBifurcationIndicator_Hopf),
  mBifurcationIndicator_Fold(src.mBifurcationIndicator_Fold),
  mBifurcationIndicator_Hopf_BDT(src.mBifurcationIndicator_Hopf_BDT),
  mBifurcationIndicator_Fold_BDT(src.mBifurcationIndicator_Fold_BDT),

  mResolution(src.mResolution),
  mJobvs(src.mJobvs),
  mSort(src.mSort),
  mpSelect(NULL),
  mN(src.mN),
  mA(src.mA),
  mLDA(src.mLDA),
  mSdim(src.mSdim),
  mR(src.mR),
  mI(src.mI),
  mpVS(NULL),
  mLdvs(src.mLdvs),
  mWork(src.mWork),
  mLWork(src.mLWork),
  mpBWork(NULL),
  mInfo(src.mInfo)
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

/**
 * Deconstructor
 */
CEigen::~CEigen()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CEigen::print(std::ostream * ostream) const {(*ostream) << (*this);}

void CEigen::initObjects()
{
  addObjectReference("Maximum real part", mMaxrealpart, CDataObject::ValueDbl);
  addObjectReference("Maximum imaginary part", mMaximagpart, CDataObject::ValueDbl);
  addObjectReference("# Positive eigenvalues", mNposreal, CDataObject::ValueInt);
  addObjectReference("# Negative eigenvalues", mNnegreal, CDataObject::ValueInt);
  addObjectReference("# Real eigenvalues", mNreal, CDataObject::ValueInt);
  addObjectReference("# Imaginary eigenvalues", mNimag, CDataObject::ValueInt);
  addObjectReference("# Complex conjugated eigenvalues", mNcplxconj, CDataObject::ValueInt);
  addObjectReference("# Zero eigenvalues", mNzero, CDataObject::ValueInt);
  addObjectReference("Stiffness", mStiffness, CDataObject::ValueDbl);
  addObjectReference("Time hierachy", mHierarchy, CDataObject::ValueDbl);
  addObjectReference("Resolution", mResolution, CDataObject::ValueDbl);
  addVectorReference("Vector of real part of eigenvalues", mR, CDataObject::ValueDbl);
  addVectorReference("Vector of imaginary part of eigenvalues", mI, CDataObject::ValueDbl);

  addObjectReference("Maximum real part of complex eigenvalue", mMaxRealOfComplex, CDataObject::ValueDbl);
  addObjectReference("Imaginary part of largest complex eigenvalue", mImagOfMaxComplex, CDataObject::ValueDbl);
  addObjectReference("Linear Frequency of largest complex eigenvalue", mFreqOfMaxComplex, CDataObject::ValueDbl);
  addObjectReference("Oscillation indicator", mOscillationIndicator, CDataObject::ValueDbl);
  addObjectReference("EV-based oscillation indicator", mOscillationIndicator_EV, CDataObject::ValueDbl);
  addObjectReference("Hopf bifurcation test function", mBifurcationIndicator_Hopf, CDataObject::ValueDbl);
  addObjectReference("Fold bifurcation test function", mBifurcationIndicator_Fold, CDataObject::ValueDbl);
  addObjectReference("Hopf bifurcation test function (BDT)", mBifurcationIndicator_Hopf_BDT, CDataObject::ValueDbl);
  addObjectReference("Fold bifurcation test function (BDT)", mBifurcationIndicator_Fold_BDT, CDataObject::ValueDbl);
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

//Get the max eigenvalue real part
const C_FLOAT64 & CEigen::getMaxrealpart() const
{
  return mMaxrealpart;
}

//Get the max eigenvalue imaginary  part
const C_FLOAT64 & CEigen::getMaximagpart() const
{
  return mMaximagpart;
}

// Get the number of zero eigenvalues
const size_t & CEigen::getNzero() const
{
  return mNzero;
}

//Get the eigenvalue stiffness
const C_FLOAT64 & CEigen::getStiffness() const
{
  return mStiffness;
}

//Get the eigenvalue hierarchy
const C_FLOAT64 & CEigen::getHierarchy() const
{
  return mHierarchy;
}

//initialize variables for eigenvalue calculations
//
void CEigen::initialize()
{
  cleanup();

  mNreal = mNimag = mNposreal = mNnegreal =
                                  mNzero = mNcplxconj = 0;

  mLDA = mN > 1 ? mN : 1;

  mR.resize(mN);
  mI.resize(mN);
}

void CEigen::cleanup()
{}

void CEigen::calcEigenValues(const CMatrix< C_FLOAT64 > & matrix)
{
  assert(matrix.numRows() == matrix.numCols());
  mN = (C_INT) matrix.numRows();
  initialize();

  if (!mN) return;

  // copy the jacobian into mA
  mA.resize(matrix.numRows(), matrix.numCols());
  C_FLOAT64 * pA = mA.array();
  C_FLOAT64 * pAEnd = pA + mA.size();
  const C_FLOAT64 * pMatrix = matrix.array();

  for (; pA != pAEnd; ++pA, ++pMatrix)
    {
      *pA = *pMatrix;

      if (!std::isfinite(*pA) && !std::isnan(*pA))
        {
          if (*pA > 0)
            *pA = std::numeric_limits< C_FLOAT64 >::max();
          else
            *pA = - std::numeric_limits< C_FLOAT64 >::max();
        }
    }

  // Querry for the work array size.
  mLWork = -1;
  dgees_(&mJobvs, // 'N'
         &mSort, // 'N'
         NULL, // NULL,
         &mN, // n,
         mA.array(),
         & mLDA,
         & mSdim, // output
         mR.array(),
         mI.array(),
         mpVS,
         & mLdvs,
         mWork.array(),
         & mLWork,
         mpBWork, // NULL
         &mInfo);        // output

  if (mInfo != 0)
    {
      // Exception
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCEigen + 1, -mInfo);
    }

  mLWork = (C_INT) mWork[0];
  mWork.resize(mLWork);

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
  dgees_(&mJobvs, // 'N'
         &mSort, // 'N'
         NULL, // NULL,
         &mN, // n,
         mA.array(),
         & mLDA,
         & mSdim, // output
         mR.array(),
         mI.array(),
         mpVS,
         & mLdvs,
         mWork.array(),
         & mLWork,
         mpBWork, // NULL
         &mInfo);        // output

  if (mInfo != 0)
    {
      if (mInfo < 0)
        {
          // Exception
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCEigen + 1, -mInfo);
        }
      else if (mInfo <= mN)
        {
          // Warning
          CCopasiMessage(CCopasiMessage::WARNING, MCEigen + 2, mInfo);
        }
      else if (mInfo == mN + 1)
        {
          // Warning
          CCopasiMessage(CCopasiMessage::WARNING, MCEigen + 3, mInfo);
        }
      else if (mInfo == mN + 2)
        {
          // Warning
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCEigen + 4, mInfo);
        }
      else // Catch all, should never happen.
        fatalError();
    }

  return;
}

void CEigen::stabilityAnalysis(const C_FLOAT64 & resolution)
{
  if (!mN) return;

  size_t mx, mn;            // YH: n is the 4th parameter, not here
  size_t i;
  C_FLOAT64 distt, maxt, tott;
  mResolution = resolution;

  // sort the eigenvalues
  CVector<size_t> Pivot;

  sortWithPivot(mR.array(), mR.array() + mR.size(), CompareDoubleWithNaN(), Pivot);

  // The sort order is ascending however we need descending
  size_t *pTo = Pivot.array();
  size_t *pFrom = pTo + mN - 1;

  for (; pTo < pFrom; ++pTo, --pFrom)
    {
      size_t Tmp = *pFrom;
      *pFrom = *pTo;
      *pTo = Tmp;
    }

  mR.applyPivot(Pivot);
  mI.applyPivot(Pivot);

  // calculate various eigenvalue statistics
  mMaxrealpart = mR[0];
  mMaxRealOfComplex = mR[mN - 1] - 1;
  mMaximagpart = fabs(mI[0]);
  mImagOfMaxComplex = 0.0;

  for (i = 0; (C_INT) i < mN; i++)
    {
      // for the largest real part
      if (mR[i] > mMaxrealpart)
        mMaxrealpart = mR[i];

      // for the largest imaginary part
      if (fabs(mI[i]) > mMaximagpart)
        mMaximagpart = fabs(mI[i]);

      // for the largest complex eigenvalue
      if ((fabs(mI[i]) > resolution) && (mR[i] > mMaxRealOfComplex))
        {
          mMaxRealOfComplex = mR[i];
          mImagOfMaxComplex = fabs(mI[i]);
        }

      if (fabs(mR[i]) > resolution)
        {
          // positive real part
          if (mR[i] >= resolution)
            mNposreal++;

          // negative real part
          if (mR[i] <= -resolution)
            mNnegreal++;

          if (fabs(mI[i]) > resolution)
            {
              // complex
              mNcplxconj++;
            }
          else
            {
              mI[i] = 0.0;
              // pure real
              mNreal++;
            }
        }
      else
        {
          mR[i] = 0.0;

          if (fabs(mI[i]) > resolution)
            {
              // pure imaginary
              mNimag++;
            }
          else
            {
              mI[i] = 0.0;
              // zero
              mNzero++;
            }
        }
    }

  if (mImagOfMaxComplex == 0)
    mMaxRealOfComplex = mR[mN - 1]; //default value

  mFreqOfMaxComplex = mImagOfMaxComplex / (2 * M_PI);

  if (mNposreal > 0)
    {
      if (mR[0] > fabs(mR[mN - 1]))
        mx = 0;
      else
        mx = mN - 1;

      if ((C_INT) mNposreal == mN)
        mn = mNposreal - 1;
      else if (mR[mNposreal - 1] < fabs(mR[mNposreal]))
        mn = mNposreal - 1;
      else
        mn = mNposreal;
    }
  else
    {
      mx = mN - 1; // index of the largest absolute real part
      mn = 0; // index of the smallest absolute real part
    }

  mStiffness = fabs(mR[mx]) / fabs(mR[mn]);

  maxt = tott = fabs(1 / mR[mn]);
  distt = 0.0;

  for (i = 1; (C_INT) i < mN; i++)
    if (i != mn)
      {
        distt += maxt - fabs(1 / mR[i]);
        tott += fabs(1 / mR[i]);
      }

  mHierarchy = distt / tott / (mN - 1);

  //we calculate an oscillation indicator based on the eigenvalues. It is using a rather heuristical approach
  if (mN < 2) // at least 2 Eigenvalues are required for oscillations
    mOscillationIndicator_EV = 0;
  else
    {
      if (fabs(mI[0]) > resolution)
        mOscillationIndicator_EV = mR[0] * (mR[0] > 0 ? fabs(mI[0]) / (0.01 + fabs(mI[0])) : 2 - fabs(mI[0]) / (0.01 + fabs(mI[0])));
      else
        mOscillationIndicator_EV = 2 * mR[1] - (mR[0] > 0 ? 2 * mR[0] : 0);
    }

  //bifurcation test functions, according to Kuznetsov "Elements of applied bifurcation theory"
  // this function can also be calculated without using the eigenvalues, but since we already
  //have them we can use them

  std::complex<C_FLOAT64> tmpcpl = 1.0;
  size_t index_min = 0; // the index of the EV with smallest abs real part
  C_FLOAT64 tmpmin = 1e300;

  for (i = 0; (C_INT) i < mN; i++)
    {
      tmpcpl *= std::complex<C_FLOAT64>(mR[i], mI[i]);

      if (fabs(mR[i]) < tmpmin)
        {
          tmpmin = fabs(mR[i]);
          index_min = i;
        }
    }

  mBifurcationIndicator_Fold = std::abs<C_FLOAT64>(tmpcpl);

  tmpcpl = 1.0;

  for (i = 0; (C_INT) i < mN - 1; i++)
    {
      tmpcpl *= (std::complex<C_FLOAT64>(mR[i], mI[i]) + std::complex<C_FLOAT64>(mR[i + 1], mI[i + 1]));
    }

  mBifurcationIndicator_Hopf = (tmpcpl.real());

  //now the test functions from the "Bifurcation discovery tool" (as described in the publication by Chickarmane et al.)

  //calculate the product of EVs excluding the minimal one
  tmpcpl = 1.0;

  for (i = 0; (C_INT) i < mN; i++)
    {
      if (i != index_min)
        tmpcpl *= std::complex<C_FLOAT64>(mR[i], mI[i]);
    }

  mBifurcationIndicator_Fold_BDT = mBifurcationIndicator_Fold / (1 - 0.99 * exp(-std::abs<C_FLOAT64>(tmpcpl)));

  C_FLOAT64 tmp_product = 1.0;

  for (i = 0; (C_INT) i < mN; i++)
    {
      tmp_product *= mR[i] / (1 - 0.99 * exp(-mI[i]));
    }

  mBifurcationIndicator_Hopf_BDT = tmp_product;

  mOscillationIndicator = 0.0; //not used at the moment.
}

/**
 * Return number of real eigenvalues WeiSun 3/28/02
 */
const size_t & CEigen::getNreal() const
{
  return mNreal;
}

/**
 * Return the number of imaginary eigenvalue numbers
 */
const size_t & CEigen::getNimag() const
{
  return mNimag;
}

const size_t & CEigen::getNcplxconj() const
{
  return mNcplxconj;
}

/**
 * Return the number of eigenvalues with positive real part
 */
const size_t & CEigen::getNposreal() const
{
  return mNposreal;
}

/**
 * Return the number of eigenvalues with negative real part
 */
const size_t & CEigen::getNnegreal() const
{
  return mNnegreal;
}

const CVector< C_FLOAT64 > & CEigen::getI() const
{return mI;}

const CVector< C_FLOAT64 > & CEigen::getR() const
{return mR;}

std::ostream &operator<<(std::ostream &os, const CEigen &A)
{
  os << std::endl;
  os << "KINETIC STABILITY ANALYSIS";
  os << std::endl;
  os << "The linear stability analysis based on the eigenvalues" << std::endl;
  os << "of the Jacobian matrix is only valid for steady states." << std::endl;
  os << std::endl;
  os << "Summary:" << std::endl;
  os << "This state ";

  // Output statistics

  if (A.mMaxrealpart > A.mResolution)
    os << "is unstable";
  else if (A.mMaxrealpart < -A.mResolution)
    os << "is asymptotically stable";
  else
    os << "'s stability is undetermined";

  if (A.mMaximagpart > A.mResolution)
    {
      os << "," << std::endl;
      os << "transient states in its vicinity have oscillatory components";
    }

  os << "." << std::endl;
  os << std::endl;

  os << "Eigenvalue statistics:" << std::endl;
  // Output Max Real Part
  os << " Largest real part: ";
  os << std::setprecision(6) << A.mMaxrealpart << std::endl;
  // Output Max imaginary Part
  os << " Largest absolute imaginary part:  ";
  os << std::setprecision(6) << A.mMaximagpart << std::endl;

  if (A.mImagOfMaxComplex > A.mResolution)
    os << " The complex eigenvalues with the largest real part are:  "
       << A.mMaxRealOfComplex << " +|- " << A.mImagOfMaxComplex << "i" << std::endl;

  // Output Eigen-nreal
  os.unsetf(std::ios_base::scientific);
  os.unsetf(std::ios_base::showpoint);
  os << " " << A.mNreal;
  os << " are purely real" << std::endl;
  // Output Eigen-nimage
  os << " " << A.mNimag;
  os << " are purely imaginary" << std::endl;
  // Output Eigen-ncplxconj
  os << " " << A.mNcplxconj;
  os << " are complex" << std::endl;
  // Output Eigen-nzero
  os << " " << A.mNzero;
  os << " are equal to zero" << std::endl;
  // Output Eigen-nposreal
  os << " " << A.mNposreal;
  os << " have positive real part" << std::endl;
  // Output Eigen-nnegreal
  os << " " << A.mNnegreal;
  os << " have negative real part" << std::endl;

  // Set point manipulators
  os.setf(std::ios_base::showpoint);
  // Output Eigne-stiffness
  os << " stiffness = " << A.mStiffness << std::endl;
  os << " time hierarchy = " << A.mHierarchy << std::endl;

  os << std::endl;
  os << "Fold bifurcaton test functions (standard, bifurcation discovery tool): " << A.mBifurcationIndicator_Fold
     << ", " << A.mBifurcationIndicator_Fold_BDT <<  std::endl;
  os << "Hopf bifurcaton test functions (standard, bifurcation discovery tool): " << A.mBifurcationIndicator_Hopf
     << ", " << A.mBifurcationIndicator_Hopf_BDT <<  std::endl;

  os << std::endl;
  os << "Oscillation indicator: " << A.mOscillationIndicator_EV  << std::endl;

  return os;
}
