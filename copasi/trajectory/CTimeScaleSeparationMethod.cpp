// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/Attic/CTimeScaleSeparationMethod.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2007/01/29 09:46:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/Attic/CTimeScaleSeparationMethod.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2007/01/29 09:46:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CTimeScaleSeparationMethod.h"
#include "CTrajectoryProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CState.h"
#include "utilities/CMatrix.h"
#include "utilities/CAnnotatedMatrix.h"
#include "report/CCopasiObjectReference.h"

#include "clapackwrap.h"        // CLAPACK
#include "blaswrap.h"           // BLAS

CTimeScaleSeparationMethod::CTimeScaleSeparationMethod(const CCopasiContainer * pParent):
    CTrajectoryMethod(CCopasiMethod::tssMethodDevelopment, pParent),
    mpState(NULL),
    mY(NULL)
{
  assert((void *) &mData == (void *) &mData.dim);

  addObjectReference("Number of slow variables", mSlow, CCopasiObject::ValueInt);
  addVectorReference("Contribution of Metabolites to Slow Space", mVslow, CCopasiObject::ValueDbl);

  mData.pMethod = this;
  initializeParameter();
}

CTimeScaleSeparationMethod::CTimeScaleSeparationMethod(const CTimeScaleSeparationMethod & src,
    const CCopasiContainer * pParent):
    CTrajectoryMethod(src, pParent),
    mpState(NULL),
    mY(NULL)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CTimeScaleSeparationMethod::~CTimeScaleSeparationMethod()
{
  pdelete(mpState);
}

void CTimeScaleSeparationMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Deuflhard Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);

  assertParameter("Integrate Reduced Model", CCopasiParameter::BOOL, (bool) true);
  assertParameter("Relative Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Absolute Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-12);
  assertParameter("Adams Max Order", CCopasiParameter::UINT, (unsigned C_INT32) 12);
  assertParameter("BDF Max Order", CCopasiParameter::UINT, (unsigned C_INT32) 5);
  assertParameter("Max Internal Steps", CCopasiParameter::UINT, (unsigned C_INT32) 10000);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("LSODA.RelativeTolerance")) != NULL)
    {
      setValue("Relative Tolerance", *pParm->getValue().pUDOUBLE);
      removeParameter("LSODA.RelativeTolerance");

      if ((pParm = getParameter("LSODA.AbsoluteTolerance")) != NULL)
        {
          setValue("Absolute Tolerance", *pParm->getValue().pUDOUBLE);
          removeParameter("LSODA.AbsoluteTolerance");
        }

      if ((pParm = getParameter("LSODA.AdamsMaxOrder")) != NULL)
        {
          setValue("Adams Max Order", *pParm->getValue().pUINT);
          removeParameter("LSODA.AdamsMaxOrder");
        }

      if ((pParm = getParameter("LSODA.BDFMaxOrder")) != NULL)
        {
          setValue("BDF Max Order", *pParm->getValue().pUINT);
          removeParameter("LSODA.BDFMaxOrder");
        }

      if ((pParm = getParameter("LSODA.MaxStepsInternal")) != NULL)
        {
          setValue("Max Internal Steps", *pParm->getValue().pUINT);
          removeParameter("LSODA.MaxStepsInternal");
        }
    }

  // Check whether we have a method with "Use Default Absolute Tolerance"
  if ((pParm = getParameter("Use Default Absolute Tolerance")) != NULL)
    {
      C_FLOAT64 NewValue;

      if (*pParm->getValue().pBOOL)
        {
          // The default
          NewValue = 1.e-12;
        }
      else
        {
          C_FLOAT64 OldValue = *getValue("Absolute Tolerance").pUDOUBLE;

          CModel * pModel = CCopasiDataModel::Global->getModel();

          if (pModel == NULL)
            // The default
            NewValue = 1.e-12;
          else
            {
              const CCopasiVectorNS< CCompartment > & Compartment = pModel->getCompartments();
              unsigned C_INT32 i, imax;
              C_FLOAT64 Volume = DBL_MAX;

              for (i = 0, imax = Compartment.size(); i < imax; i++)
                if (Compartment[i]->getValue() < Volume)
                  Volume = Compartment[i]->getValue();

              if (Volume == DBL_MAX)
                // The default
                NewValue = 1.e-12;
              else
                // Invert the scaling as best as we can
                NewValue = OldValue / (Volume * pModel->getQuantity2NumberFactor());
            }
        }

      setValue("Absolute Tolerance", NewValue);
      removeParameter("Use Default Absolute Tolerance");
    }
}

bool CTimeScaleSeparationMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

void CTimeScaleSeparationMethod::integrationStep(const double & deltaT)
{
  mLsodaStatus = 1;
  mState = 1;
  mJType = 2;
  mErrorMsg.str("");
  mLSODA.setOstream(mErrorMsg);

  if (!mData.dim) //just do nothing if there are no variables
    {
      mTime = mTime + deltaT;
      mpState->setTime(mTime);
      *mpCurrentState = *mpState;

      return;
    }

  C_FLOAT64 EndTime = mTime + deltaT;
  C_INT ITOL = 2; // mRtol scalar, mAtol vector
  C_INT one = 1;
  C_INT DSize = mDWork.size();
  C_INT ISize = mIWork.size();

  C_INT i;
  C_INT dim = mData.dim;

  mLSODA(&EvalF,          //  1. evaluate F
         &mData.dim,      //  2. number of variables
         mY,              //  3. the array of current concentrations
         &mTime,          //  4. the current time
         &EndTime,        //  5. the final time
         &ITOL,           //  6. error control
         &mRtol,          //  7. relative tolerance array
         mAtol.array(),   //  8. absolute tolerance array
         &mState,         //  9. output by overshoot & interpolatation
         &mLsodaStatus,   // 10. the state control variable
         &one,            // 11. futher options (one)
         mDWork.array(),  // 12. the double work array
         &DSize,          // 13. the double work array size
         mIWork.array(),  // 14. the int work array
         &ISize,          // 15. the int work array size
         NULL,            // 16. evaluate J (not given)
         &mJType);        // 17. the type of jacobian calculate (2)

  if (mLsodaStatus == -1) mLsodaStatus = 2;

  if ((mLsodaStatus != 1) && (mLsodaStatus != 2) && (mLsodaStatus != -1))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 6, mErrorMsg.str().c_str());
    }

  mpState->setTime(mTime);
  *mpCurrentState = *mpState;

  return;
}

void CTimeScaleSeparationMethod::step(const double & deltaT)
{

  C_INT dim = mData.dim;
  C_INT fast = 1;
  C_INT slow = dim - fast;

  C_INT i;

  mQ.resize(dim, dim);
  mR.resize(dim, dim);
  mTd.resize(dim, dim);
  mTdInverse.resize(dim, dim);
  mQz.resize(dim, dim);

  mpModel->applyAssignments();
  mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

  std::cout << "*****************************" << std::endl;
  std::cout << "Next step t=: " << mTime << std::endl;
  /**
   Schur  Decomposition of Jacobian (reordered).  Output:  mQ - transformation matrix
   mR - block upper triangular matrix (with ordered eigenvalues)
  */
  schur();

  /* If complex eigenvalues */

  if (mR(dim - 1, dim - 1) == mR(dim - 2 , dim - 2))
    {
      fast = 2;
      slow = dim - fast;
    }

  C_INT failed = 0;

  /*  do START slow iterations */

  while (slow > 0)
    {

      /**
      Solution of Sylvester equation for given slow, mQ,mR
      Output: mTd, mTdinverse and mQz (mQz is used later for newton iterations)
      */
      sylvester (slow);

      /* Check real parts of eigenvalues of Jacobian */

      for (i = slow ; i < dim; i++)
        if (mR(i - 1, i - 1) >= 0)
          {
            failed = 1;
            goto integration;
          }

      if (fast > 0)
        mEPS = 1 / abs(mR(slow , slow));

      C_INT info;

      mCfast.resize(fast);

      /**
        Deuflhard Iteration:  Prove Deuflhard criteria, find consistent
      initial value for DAE
        output:  info - if Deuflhard is satisfied for this slow;
        transformation matrices
        mTd and mTdinverse
      */
      deuflhard(slow, info);

      /* If the Deuflhard criterion is not satisfied, return to smaller fast */

      if (info)
        {
          fast = fast - 1;
          if (mR(slow - 1, slow - 1) == mR(slow - 2 , slow - 2))
            fast = fast - 1;
          slow = dim - fast;
          std::cout << "deuflhard not work" << std::endl;

          goto integration;
        }

      fast = fast + 1;

      if (fast < dim)
        if (mR(dim - fast - 1, dim - fast - 1) == mR(dim - fast - 2 , dim - fast - 2))
          fast = fast + 1;

      slow = dim - fast;

      //test to be removed

      mat_anal_mod(slow);

      std::cout << " Analysis of Td" << std::endl;
      for (i = 0 ; i < dim; i++)
        std::cout << mpModel->getMetabolitesX()[i]->getObjectName() << "      mVslow " << mVslow[i] << std::endl;

      std::cout << std::endl;

      // end of test
    }

integration:

  std::cout << "slow " << slow << std::endl;

  mat_anal_mod(slow);

  std::cout << std::endl;
  for (i = 0 ; i < dim; i++)
    std::cout << mpModel->getMetabolitesX()[i]->getObjectName() << "      mVslow " << mVslow[i] << std::endl;
  mSlow = slow;

  std::cout << std::endl;

  integrationStep(deltaT);

  return;
}

/** MAT_ANAL_MOD:  mathematical analysis of matrices mTdInverse for post-analysis  */
void CTimeScaleSeparationMethod::mat_anal_mod(C_INT & slow)
{
  C_FLOAT64 denom, length;
  C_INT i, j, dim;

  dim = mData.dim;

  CMatrix<C_FLOAT64> Matrix_anal;
  Matrix_anal.resize(dim, dim);

  // norm  of mTd

  for (j = 0; j < dim; j++)
    {
      length = 0;
      for (i = 0; i < dim; i++)
        {
          length = length + mTdInverse(i, j) * mTdInverse(i, j);
        }
      length = sqrt(length);
      for (i = 0; i < dim; i++)
        Matrix_anal (i, j) = mTdInverse(i, j) / length;
    }

  if (slow > 0)
    {
      denom = 0.0;
      for (i = 0; i < dim; i++)
        {
          for (j = 0; j < slow; j++)
            denom = denom + abs(Matrix_anal(i, j));
        }

      for (i = 0; i < dim; i++)
        mVslow[i] = 0.0;

      for (i = 0; i < dim; i++)
        {
          for (j = 0; j < slow; j++)
            mVslow[i] = mVslow[i] + abs(Matrix_anal(i, j));

          mVslow[i] = (mVslow[i] / denom) * 100;
        }
    }
  else
    for (i = 0; i < dim; i++)
      mVslow[i] = 0;
  return;
}

/** SCHUR:  Schur  Decomposition of Jacobian (reordered).
 Output:  mQ - transformation matrix
 mR - block upper triangular matrix (with ordered eigenvalues)
 */

void CTimeScaleSeparationMethod::schur()
{

  /*      int dgees_(char *jobvs, char *sort, L_fp select, integer *n,
   *  doublereal *a, integer *lda, integer *sdim, doublereal *wr,
   * doublereal *wi, doublereal *vs, integer *ldvs, doublereal *work,
   * integer *lwork, logical *bwork, integer *info)
   *
   *  -- LAPACK driver routine (version 3.0) --
   *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
   *     Courant Institute, Argonne National Lab, and Rice University
   *     June 30, 1999
   *
   *
   *  Purpose
   *  =======
   *
   *  DGEES computes for an N-by-N real nonsymmetric matrix A, the
   *  eigenvalues, the real Schur form T, and, optionally, the matrix of
   *  Schur vectors Z.  This gives the Schur factorization A = Z*T*(Z**T).
   *
   *  Optionally, it also orders the eigenvalues on the diagonal of the
   *  real Schur form so that selected eigenvalues are at the top left.
   *  The leading columns of Z then form an orthonormal basis for the
   *  invariant subspace corresponding to the selected eigenvalues.
   *
   *  A matrix is in real Schur form if it is upper quasi-triangular with
   *  1-by-1 and 2-by-2 blocks. 2-by-2 blocks will be standardized in the
   *  form
   *          [  a  b  ]
   *          [  c  a  ]
   *
   *  where b*c < 0. The eigenvalues of such a block are a +- sqrt(bc).
   *
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
   *                   eigenvalues; elements 1:ILO-1 and i+1:N of WR and WI
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

  char V = 'V';
  char N = 'N';

  C_INT dim = mData.dim;
  C_INT SDIM = 0;

  CVector<C_FLOAT64> R;
  R.resize(dim*dim);
  C_INT i, j;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      R[j + dim*i] = mJacobian(j, i);

  CVector<C_FLOAT64> eval_r;
  CVector<C_FLOAT64> eval_i;
  eval_r.resize(dim);
  eval_i.resize(dim);

  CVector<C_FLOAT64> Q;
  Q.resize(dim*dim);

  C_INT lwork = 10 * dim;
  CVector< C_FLOAT64 > work;
  work.resize(10*dim);

  CVector< C_INT > Bwork;
  Bwork.resize(dim);

  C_INT info;

  dgees_(&V, &N, NULL, &dim, R.array(), &dim, &SDIM, eval_r.array(), eval_i.array(), Q.array(), &dim, work.array(), &lwork, Bwork.array(), &info);

  if (info)
    {
      std::cout << "Problems with schur decomposition " << std::endl;

      return;
    }

  /* Sorting of Schurmatix */

  CVector<C_FLOAT64> eval_reor;
  eval_reor.resize(dim);

  CVector<C_INT> index;
  index.resize(dim);

  for (i = 0; i < dim; i++)
    eval_reor[i] = eval_r [i];

  for (i = 0; i < dim; i++) index[i] = 0;

  map_index(eval_reor.array(), index.array(), dim);

  CVector<C_INT> nid;
  CVector<C_INT> pid;
  nid.resize(dim);
  pid.resize(dim);

  if (dim > 2)
    {
      update_nid(index.array(), nid.array(), dim);
      update_pid(index.array(), pid.array(), dim);
    }
  else
    {
      for (i = 0; i < dim; i++)
        {
          nid[i] = 0;
          pid[i] = 0;
        }
    }

  bool changed = true;
  C_INT count;

  while (changed == true)
    {
      changed = false;
      count = 0;

      while (count < dim - 1)
        {
          C_INT first;
          C_INT second;

          if (index[count + 1] < index[count])
            {
              changed = true;
              first = count + 2;
              second = count + 1;

              CVector<C_FLOAT64> j_diag;
              j_diag.resize(dim);

              for (i = 0; i < dim; i++)
                j_diag[i] = R.array()[i * dim + i];

              map_index(j_diag.array(), index.array(), dim);
              update_nid(index.array(), nid.array(), dim);
              update_pid(index.array(), pid.array(), dim);

              /*     int dtrexc_(char *compq, integer *n, doublereal *t, integer *
               *     ldt, doublereal *q, integer *ldq, integer *ifst, integer *ilst,
               *     doublereal *work, integer *info)
               *     -- LAPACK routine (version 3.0) --
               *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
               *     Courant Institute, Argonne National Lab, and Rice University
               *     March 31, 1993
               *
               *
               *  Purpose
               *  =======
               *
               *  DTREXC reorders the real Schur factorization of a real matrix
               *  A = Q*T*Q**T, so that the diagonal block of T with row index IFST is
               *  moved to row ILST.
               *
               *  The real Schur form T is reordered by an orthogonal similarity
               *  transformation Z**T*T*Z, and optionally the matrix Q of Schur vectors
               *  is updated by postmultiplying it with Z.
               *
               *  T must be in Schur canonical form (as returned by DHSEQR), that is,
               *  block upper triangular with 1-by-1 and 2-by-2 diagonal blocks; each
               *  2-by-2 diagonal block has its diagonal elements equal and its
               *  off-diagonal elements of opposite sign.
               *
               *  Arguments
               *  =========
               *
               *  COMPQ   (input) CHARACTER*1
               *          = 'V':  update the matrix Q of Schur vectors;
               *          = 'N':  do not update Q.
               *
               *  N       (input) INTEGER
               *          The order of the matrix T. N >= 0.
               *
               *  T       (input/output) DOUBLE PRECISION array, dimension (LDT,N)
               *          On entry, the upper quasi-triangular matrix T, in Schur
               *          Schur canonical form.
               *          On exit, the reordered upper quasi-triangular matrix, again
               *          in Schur canonical form.
               *
               *  LDT     (input) INTEGER
               *          The leading dimension of the array T. LDT >= max(1,N).
               *
               *  Q       (input/output) DOUBLE PRECISION array, dimension (LDQ,N)
               *          On entry, if COMPQ = 'V', the matrix Q of Schur vectors.
               *          On exit, if COMPQ = 'V', Q has been postmultiplied by the
               *          orthogonal transformation matrix Z which reorders T.
               *          If COMPQ = 'N', Q is not referenced.
               *
               *  LDQ     (input) INTEGER
               *          The leading dimension of the array Q.  LDQ >= max(1,N).
               *
               *  IFST    (input/output) INTEGER
               *  ILST    (input/output) INTEGER
               *          Specify the reordering of the diagonal blocks of T.
               *          The block with row index IFST is moved to row ILST, by a
               *          sequence of transpositions between adjacent blocks.
               *          On exit, if IFST pointed on entry to the second row of a
               *          2-by-2 block, it is changed to point to the first row; ILST
               *          always points to the first row of the block in its final
               *          position (which may differ from its input value by +1 or -1).
               *          1 <= IFST <= N; 1 <= ILST <= N.
               *
               *  WORK    (workspace) DOUBLE PRECISION array, dimension (N)
               *
               *  INFO    (output) INTEGER
               *          = 0:  successful exit
               *          < 0:  if INFO = -i, the i-th argument had an illegal value
               *          = 1:  two adjacent blocks were too close to swap (the problem
               *                is very ill-conditioned); T may have been partially
               *                reordered, and ILST points to the first row of the
               *                current position of the block being moved.
               */

              CVector< C_FLOAT64 > work1;
              work1.resize(dim);

              dtrexc_(&V, &dim, R.array(), &dim, Q.array(), &dim, &first, &second, work1.array(), &info);

              if (info)
                {
                  /* TODO */
                  return;
                }

              C_INT tmp;

              if (nid[count] == 0)
                {
                  if (pid[count] == 0)
                    {
                      /* both are not degenerate */

                      tmp = index[count];
                      index[count] = index[count + 1];
                      index[count + 1] = tmp;

                      update_nid(index.array(), nid.array(), dim);
                      update_pid(index.array(), pid.array(), dim);

                      count = count + 1;
                    }
                  else
                    {
                      /* the first is degenerate, the second not */

                      tmp = index[count - 1];
                      index[count - 1] = index[count + 1];
                      index[count + 1] = tmp;

                      update_nid(index.array(), nid.array(), dim);
                      update_pid(index.array(), pid.array(), dim);

                      count = count + 1;
                    }
                }
              else
                {
                  if (pid[count] == 0)
                    {
                      /* the next is deg, prev is not */

                      tmp = index[count];
                      index[count] = index[count + 2];
                      index[count + 2] = tmp;

                      update_nid(index.array(), nid.array(), dim);
                      update_pid(index.array(), pid.array(), dim);

                      count = count + 1;
                    }
                  else
                    {
                      /* both are deg. */

                      tmp = index[count];
                      index[count - 1] = index[count + 1];
                      index[count] = index[count + 1];
                      index[count + 1] = tmp;
                      index[count + 2] = tmp;

                      update_nid(index.array(), nid.array(), dim);
                      update_pid(index.array(), pid.array(), dim);

                      count = count + 1;
                    }
                }
            }
          else
            count = count + 1;
        }
    }

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      {
        mQ(j, i) = Q.array()[j + dim * i];
        mR(j, i) = R.array()[j + dim * i];
      }

  return;
}
/**
SYLVESTER:
Solution of Sylvester equation for given slow, mQ,mR
Output: mTd, mTdinverse,  mQz (is used later for newton iterations)
 */

void CTimeScaleSeparationMethod::sylvester(C_INT slow)
{
  char N1 = 'N';
  char N2 = 'N';
  C_INT isgn = -1;

  C_INT dim = mData.dim;

  C_INT fast = dim - slow;
  C_INT info;

  C_INT i, j, k;

  C_FLOAT64 scale = -1;

  CVector<C_FLOAT64> st_slow;
  st_slow.resize(slow*slow);

  CVector<C_FLOAT64> st_fast;
  st_fast.resize(fast*fast);

  CVector<C_FLOAT64> st_coup;
  st_coup.resize(slow*fast);

  CMatrix<C_FLOAT64> S_coup;
  S_coup.resize(slow, fast);

  for (i = 0; i < slow; i++)
    for (j = 0; j < slow; j++)
      st_slow[j + slow*i] = mR(j, i);

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      st_fast[j + fast*i] = mR(j + slow, i + slow);

  for (i = 0; i < slow; i++)
    for (j = 0; j < fast; j++)
      S_coup(i, j) = mR(i, j + slow);

  for (j = 0; j < fast; j++)
    for (i = 0; i < slow; i++)
      st_coup[i + slow*j] = S_coup(i, j);

  /*     int dtrsyl_(char *trana, char *tranb, integer *isgn, integer
   *     *m, integer *n, doublereal *a, integer *lda, doublereal *b, integer *
   *     ldb, doublereal *c__, integer *ldc, doublereal *scale, integer *info)
   *
   *     -- LAPACK routine (version 3.0) --
   *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
   *     Courant Institute, Argonne National Lab, and Rice University
   *     March 31, 1993
   *
   *
   *  Purpose
   *  =======
   *
   *  DTRSYL solves the real Sylvester matrix equation:
   *
   *     op(A)*X + X*op(B) = scale*C or
   *     op(A)*X - X*op(B) = scale*C,
   *
   *  where op(A) = A or A**T, and  A and B are both upper quasi-
   *  triangular. A is M-by-M and B is N-by-N; the right hand side C and
   *  the solution X are M-by-N; and scale is an output scale factor, set
   *  <= 1 to avoid overflow in X.
   *
   *  A and B must be in Schur canonical form (as returned by DHSEQR), that
   *  is, block upper triangular with 1-by-1 and 2-by-2 diagonal blocks;
   *  each 2-by-2 diagonal block has its diagonal elements equal and its
   *  off-diagonal elements of opposite sign.
   *
   *  Arguments
   *  =========
   *
   *  TRANA   (input) CHARACTER*1
   *          Specifies the option op(A):
   *          = 'N': op(A) = A    (No transpose)
   *          = 'T': op(A) = A**T (Transpose)
   *          = 'C': op(A) = A**H (Conjugate transpose = Transpose)
   *
   *  TRANB   (input) CHARACTER*1
   *          Specifies the option op(B):
   *          = 'N': op(B) = B    (No transpose)
   *          = 'T': op(B) = B**T (Transpose)
   *          = 'C': op(B) = B**H (Conjugate transpose = Transpose)
   *
   *  ISGN    (input) INTEGER
   *          Specifies the sign in the equation:
   *          = +1: solve op(A)*X + X*op(B) = scale*C
   *          = -1: solve op(A)*X - X*op(B) = scale*C
   *
   *  M       (input) INTEGER
   *          The order of the matrix A, and the number of rows in the
   *          matrices X and C. M >= 0.
   *
   *  N       (input) INTEGER
   *          The order of the matrix B, and the number of columns in the
   *          matrices X and C. N >= 0.
   *
   *  A       (input) DOUBLE PRECISION array, dimension (LDA,M)
   *          The upper quasi-triangular matrix A, in Schur canonical form.
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A. LDA >= max(1,M).
   *
   *  B       (input) DOUBLE PRECISION array, dimension (LDB,N)
   *          The upper quasi-triangular matrix B, in Schur canonical form.
   *
   *  LDB     (input) INTEGER
   *          The leading dimension of the array B. LDB >= max(1,N).
   *
   *  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N)
   *          On entry, the M-by-N right hand side matrix C.
   *          On exit, C is overwritten by the solution matrix X.
   *
   *  LDC     (input) INTEGER
   *          The leading dimension of the array C. LDC >= max(1,M)
   *
   *  SCALE   (output) DOUBLE PRECISION
   *          The scale factor, scale, set <= 1 to avoid overflow in X.
   *
   *  INFO    (output) INTEGER
   *          = 0: successful exit
   *          < 0: if INFO = -i, the i-th argument had an illegal value
   *          = 1: A and B have common or very close eigenvalues; perturbed
   *               values were used to solve the equation (but the matrices
   *               A and B are unchanged).
   */

  dtrsyl_(&N1, &N2, &isgn, &slow, &fast, st_slow.array(), &slow, st_fast.array(), &fast, st_coup.array(), &slow, &scale, &info);

  /*  if (info) TODO*/
  if (info)
    {
      std::cout << "Problems with the solution of sylvester equation" << std::endl;
      return;
    }

  CMatrix<C_FLOAT64> Cmat;
  Cmat.resize(dim, dim);

  CMatrix<C_FLOAT64> C;
  C.resize(dim, dim);

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      Cmat(i, j) = 0.;

  for (j = 0; j < fast; j++)
    for (i = 0; i < slow; i++)
      Cmat(i, j + slow) = st_coup[i + slow * j];

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      if (i == j)
        C(i, j) = 1. + Cmat(i, j);
      else
        C(i, j) = Cmat(i, j);

  for (i = 0; i < dim; i++)
    {
      for (j = 0; j < dim; j++)
        {
          mTd(i, j) = 0.;
          for (k = 0; k < dim; k++)
            mTd(i, j) = mTd(i, j) + mQ(i, k) * C(k, j);
        }
    }

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      if (i == j)
        C(i, j) = 1. - Cmat(i, j);
      else
        C(i, j) = - Cmat(i, j);

  CMatrix<C_FLOAT64> transp_Qt;
  transp_Qt.resize(dim, dim);

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      transp_Qt(i, j) = mQ(j, i);

  for (i = 0; i < dim; i++)
    {
      for (j = 0; j < dim; j++)
        {
          mTdInverse(i, j) = 0.0;
          for (k = 0; k < dim; k++)
            mTdInverse(i, j) = mTdInverse(i, j) + C(i, k) * transp_Qt(k, j);
        }
    }

  CMatrix<C_FLOAT64> E;
  E.resize(dim, dim);

  CMatrix<C_FLOAT64> S;
  S.resize(dim, dim);

  for (i = 0; i < dim; i++)
    {
      for (j = 0; j < dim; j++)
        {
          E(i, j) = 0.;
          for (k = 0; k < dim; k++)
            E(i, j) = E(i, j) + mJacobian(i, k) * mTd(k, j);
        }
    }

  for (i = 0; i < dim; i++)
    {
      for (j = 0; j < dim; j++)
        {
          S(i, j) = 0.;
          for (k = 0; k < dim; k++)
            S(i, j) = S(i, j) + mTdInverse(i, k) * E(k, j);
        }
    }

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      mQz(i, j) = 0.;

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      mQz(i, j) = S(i + slow, j + slow);

  return;
}

void CTimeScaleSeparationMethod::evalsort(C_FLOAT64 *reval, const C_INT & dim)
{
  C_INT i, j, min;
  C_FLOAT64 tmp1r;

  for (i = 0; i < dim - 1; i++)
    {
      min = i;

      for (j = i + 1; j < dim; j++)
        {
          if (reval[j] < reval[min])
            min = j;
        }

      tmp1r = reval[min];
      reval[min] = reval[i];
      reval[i] = tmp1r;
    }
  return;
}

/**
  Deuflhard Iteration:  Prove Deuflhard criteria, find consistent initial value for DAE
  output:  info - if Deuflhard is satisfied for given slow; transformation matrices
  mTd and mTdinverse
 */
void CTimeScaleSeparationMethod::deuflhard(C_INT & slow, C_INT & info)
{

  C_INT i, j;
  C_INT dim = mData.dim;
  C_INT fast = dim - slow;

  /* calculations before relaxing yf to slow manifold */

  CVector<C_FLOAT64> c_full;
  c_full.resize(dim);

  CVector<C_FLOAT64> c_slow;
  c_slow.resize(slow);

  /* the vector mY is the current state of the system*/

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor()
                          / mpModel->getCompartments()[0]->getInitialValue();

  //this is an ugly hack that only makes sense if all metabs are in the same compartment
  //at the moment is is the only case the algorithm deals with

  CVector<C_FLOAT64> Xconc; //current state converted to concentrations
  Xconc.resize(dim);
  for (i = 0; i < dim; ++i)
    Xconc[i] = mY[i] * number2conc;

  for (i = 0; i < dim; i++)
    {
      c_full[i] = 0.0;
      for (j = 0; j < dim; j++)
        c_full[i] = c_full[i] + mTdInverse(i, j) * Xconc[j];
    }

  for (j = 0; j < slow; j++)
    c_slow[j] = c_full[j];

  for (j = 0; j < fast; j++)
    {
      mCfast[j] = c_full[j + slow];
    }

  CVector<C_FLOAT64> g_full;
  g_full.resize(dim);

  CVector<C_FLOAT64> g_slow;
  g_slow.resize(slow);

  CVector<C_FLOAT64> g_fast;
  g_fast.resize(fast);

  CVector<C_FLOAT64> dxdt;
  dxdt.resize(dim);

  mpModel->applyAssignments();

  for (j = 0; j < dim; j++)
    dxdt[j] = 0.;

  mpModel->calculateDerivativesX(dxdt.array());

  //convert dxdt to concentration units...
  for (i = 0; i < dim; ++i)
    dxdt[i] *= number2conc;

  for (i = 0; i < dim; i++)
    {
      g_full[i] = 0.0;
      for (j = 0; j < dim; j++)
        g_full[i] = g_full[i] + mTdInverse(i, j) * dxdt[j];
      std::cout << "g_full: " << g_full[i] << std::endl;
    }

  // std::cout << "mTdInverse: " << mTdInverse << std::endl;

  for (j = 0; j < slow; j++)
    g_slow[j] = g_full[j];

  info = 0;

  /**
  NEWTON: Looking for consistent initial value for DAE system
  Output:  mCfast, info
  */
  newton(c_slow.array(), slow, info);

  if (info)
    {
      /* TODO */
      std::cout << "info:deuflhard  stop" << std::endl;

      return;
    }

  /* calculation of g_relax at point x_relax
     (after relaxing yf to slow manifold)*/

  CVector<C_FLOAT64> c_relax;
  c_relax.resize(dim);

  CVector<C_FLOAT64> x_relax;
  x_relax.resize(dim);

  CVector<C_FLOAT64> dxdt_relax;
  dxdt_relax.resize(dim);

  CVector<C_FLOAT64> g_relax;
  g_relax.resize(dim);

  for (i = 0; i < slow; i++)
    c_relax[i] = c_slow[i];

  for (i = slow; i < dim; i++)
    c_relax[i] = mCfast[i - slow];

  for (i = 0; i < dim; i++)
    {
      x_relax[i] = 0.0;
      for (j = 0; j < dim; j++)
        x_relax[i] = x_relax[i] + mTd(i, j) * c_relax[j];
    }

  calculateDerivativesX(x_relax.array(), dxdt_relax.array());

  for (i = 0; i < dim; i++)
    {
      g_relax[i] = 0.0;
      for (j = 0; j < dim; j++)
        g_relax[i] = g_relax[i] + mTdInverse(i, j) * dxdt_relax[j];
      std::cout << "g_relax: " << g_relax[i] << std::endl;
    }

  CVector<C_FLOAT64> re;
  re.resize(slow);

  /* stop criterion for slow reaction modes */

  for (i = 0; i < slow; i++)
    {
      re[i] = fabs(g_relax[i] - g_slow[i]);
      re[i] = re[i] * mEPS;
    }

  C_FLOAT64 max = 0.;

  for (i = 0; i < slow; i++)
    if (max < re[i])
      max = re[i];

  C_FLOAT64 max1;
  C_FLOAT64 norm = 0;

  for (i = 0; i < slow; i++)
    norm = norm + fabs(g_relax[i] - g_slow[i]);

  max1 = norm * mEPS;

  std::cout << "max: " << max << std::endl;
  std::cout << "max1: " << max << std::endl;
  std::cout << "mEPS: " << mEPS << std::endl;
  std::cout << "mDtol: " << mDtol << std::endl;
  std::cout << "***Next ILDM iterations " << std::endl;
  std::cout << std::endl;

  if (max >= mDtol)
    info = 1;
  else
    info = 0;

  return;
}

/**
NEWTON: Looking for consistent initial value for DAE system
Output:  mCfast, info
 */

void CTimeScaleSeparationMethod::newton(C_FLOAT64 *ys, C_INT & slow, C_INT & info)
{
  C_INT i, j, iter, iterations, itermax;
  C_INT nrhs, ok, fast;

  C_FLOAT64 tol, err;
  C_INT dim = mData.dim;

  fast = dim - slow;

  CVector<C_INT> ipiv;
  ipiv.resize(fast);

  CVector<C_FLOAT64> s_22_array;
  s_22_array.resize(fast*fast);

  CVector<C_FLOAT64> gf_newton;
  gf_newton.resize(fast);

  CVector<C_FLOAT64> d_yf;
  d_yf.resize(fast);

  CVector<C_FLOAT64> y_newton;
  y_newton.resize(dim);

  CVector<C_FLOAT64> yf_newton;
  yf_newton.resize(fast);

  CVector<C_FLOAT64> x_newton;
  x_newton.resize(dim);

  CVector<C_FLOAT64> dxdt_newton;
  dxdt_newton.resize(dim);

  CVector<C_FLOAT64> g_newton;
  g_newton.resize(dim);

  CMatrix<C_FLOAT64> S_22;
  S_22.resize(fast, fast);

  nrhs = 1;
  tol = 0.0001;
  err = 10.0;
  iter = 0;

  itermax = 10;
  iterations = 0;

  info = 0;

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      S_22(i, j) = mQz(i, j);

  for (i = 0; i < fast; i++)
    {
      yf_newton[i] = mCfast[i];
    }

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      s_22_array[j + fast*i] = S_22(j, i);

  for (i = 0; i < fast; i++)
    d_yf[i] = 0.;

  while (err > tol)
    {
      iter ++;
      if (iter > itermax)
        {
          info = 1;
          std::cout << "iter>itermax" << iter << std::endl;
          break;
        }

      for (i = 0; i < fast; i++)
        yf_newton[i] = yf_newton[i] + d_yf[i];

      /* back transformation */

      for (i = 0; i < slow; i++)
        y_newton[i] = ys[i];

      for (i = slow; i < dim; i++)
        y_newton[i] = yf_newton[i - slow];

      for (i = 0; i < dim; i++)
        {
          x_newton[i] = 0.0;
          for (j = 0; j < dim; j++)
            x_newton[i] = x_newton[i] + mTd(i, j) * y_newton[j];
        }

      calculateDerivativesX(x_newton.array(), dxdt_newton.array());

      for (i = 0; i < dim; i++)
        {
          g_newton[i] = 0.;
          for (j = 0; j < dim; j++)
            g_newton[i] = g_newton[i] + mTdInverse(i, j) * dxdt_newton[j];
        }

      for (i = 0; i < fast; i++)
        {
          gf_newton[i] = -1. * g_newton[i + slow];
        }

      /*       int dgesv_(integer *n, integer *nrhs, doublereal *a, integer
       * *lda, integer *ipiv, doublereal *b, integer *ldb, integer *info)
       *
       *  -- LAPACK driver routine (version 3.0) --
       *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
       *     Courant Institute, Argonne National Lab, and Rice University
       *     March 31, 1993
       *
       *
       *  Purpose
       *  =======
       *
       *  DGESV computes the solution to a real system of linear equations
       *     A * X = B,
       *  where A is an N-by-N matrix and X and B are N-by-NRHS matrices.
       *
       *  The LU decomposition with partial pivoting and row interchanges is
       *  used to factor A as
       *     A = P * L * U,
       *  where P is a permutation matrix, L is unit lower triangular, and U is
       *  upper triangular.  The factored form of A is then used to solve the
       *  system of equations A * X = B.
       *
       *  Arguments
       *  =========
       *
       *  N       (input) INTEGER
       *          The number of linear equations, i.e., the order of the
       *          matrix A.  N >= 0.
       *
       *  NRHS    (input) INTEGER
       *          The number of right hand sides, i.e., the number of columns
       *          of the matrix B.  NRHS >= 0.
       *
       *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
       *          On entry, the N-by-N coefficient matrix A.
       *          On exit, the factors L and U from the factorization
       *          A = P*L*U; the unit diagonal elements of L are not stored.
       *
       *  LDA     (input) INTEGER
       *          The leading dimension of the array A.  LDA >= max(1,N).
       *
       *  IPIV    (output) INTEGER array, dimension (N)
       *          The pivot indices that define the permutation matrix P;
       *          row i of the matrix was interchanged with row IPIV(i).
       *
       *  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS)
       *          On entry, the N-by-NRHS matrix of right hand side matrix B.
       *          On exit, if INFO = 0, the N-by-NRHS solution matrix X.
       *
       *  LDB     (input) INTEGER
       *          The leading dimension of the array B.  LDB >= max(1,N).
       *
       *
       * INFO    (output) INTEGER
       *          = 0:  successful exit
       *          < 0:  if INFO = -i, the i-th argument had an illegal value
       *          > 0:  if INFO = i, U(i,i) is exactly zero.  The factorization
       *                has been completed, but the factor U is exactly
       *                singular, so the solution could not be computed.
       */

      dgesv_(&fast, &nrhs, s_22_array.array(), &fast, ipiv.array(), gf_newton.array(), &fast, &ok);

      if (ok != 0)
        {
          info = 2;
          std::cout << "info : dgesv_ ok != 0" << std::endl;
          break;
        }

      for (i = 0; i < fast; i++)
        {
          d_yf[i] = gf_newton[i];
        }

      // err = -10.;
      for (i = 0; i < fast; i++)
        {
          gf_newton[i] = abs(gf_newton[i]);
          if (err > gf_newton[i])
            err = gf_newton[i];
        }

      iterations = iterations + 1;

      /* stop criterion of newton method */

      /* if (iter == 1)
       g1 = 3.0 * err;
      else
       g1 = g2;

      g2 = err;

      if (g2/g1 > 1.0)
      {
       info =1;
       std::cout << "info : stop criterion" << std::endl;
       break;
      } */
    } /* end while */

  for (i = 0; i < fast; i++)
    mCfast[i] = yf_newton[i];

  return;
}

void CTimeScaleSeparationMethod::calculateDerivativesX(C_FLOAT64 * X1, C_FLOAT64 * Y1)
{
  C_INT i, imax;
  C_INT indep;

  indep = mpModel->getNumIndependentMetabs();

  CVector<C_FLOAT64> tmp;
  tmp.resize(indep);

  /* make copy of the current state concentrations */
  for (i = 0, imax = indep; i < imax; i++)
    tmp[i] = mpModel->getMetabolitesX()[i]->getValue();

  /* write new concentrations in the current state */
  for (i = 0, imax = indep; i < imax; i++)
    mpModel->getMetabolitesX()[i]->setConcentration(X1[i]);

  mpState->setUpdateDependentRequired(true);
  mpModel->applyAssignments();
  mpModel->calculateDerivativesX(Y1);

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor()
                          / mpModel->getCompartments()[0]->getInitialValue();
  for (i = 0; i < imax;++i)
    Y1[i] *= number2conc;

  /* write back concentrations of the current state*/
  for (i = 0, imax = indep; i < imax; i++)
    mpModel->getMetabolitesX()[i]->setValue(tmp[i]);

  mpState->setUpdateDependentRequired(true);
  mpModel->applyAssignments();

  return;
}

/**
MAP_INDEX used for sorting of SchurDecompostion
 */

void CTimeScaleSeparationMethod::map_index(C_FLOAT64 *eval_r, C_INT *index, const C_INT & dim)
{
  C_INT i, j, count;
  C_INT max;

  CVector< C_FLOAT64 > abs_eval_r(dim);

  for (i = 0; i < dim; i++)
    {
      index[i] = 0;
      abs_eval_r[i] = abs(eval_r[i]);
    }

  count = dim;

  for (i = 0; i < dim; i++)
    {

      max = i;

      for (j = 0; j < dim; j++)
        {
          if (abs_eval_r[j] > abs_eval_r[max])
            max = j;
        }

      index[max] = count;
      abs_eval_r[max] = -1;
      count --;
    }

  for (i = 0; i < dim - 1; i++)
    if (eval_r[i] == eval_r[i + 1])
      index[i + 1] = index[i];

  return;
}
/**
UPDATE_NID: used for sorting of SchurDecompostion
 */
void CTimeScaleSeparationMethod::update_nid(C_INT *index, C_INT *nid, const C_INT & dim)
{
  C_INT k;

  for (k = 0; k < dim; k++) nid[k] = 0;

  for (k = 1; k < dim - 1; k++)
    if (index[k] == index[k + 1])
      nid[k - 1] = k;
  return;
}

/**
UPDATE_PID: used for sorting of SchurDecompostion
 */
void CTimeScaleSeparationMethod::update_pid(C_INT *index, C_INT *pid, const C_INT & dim)
{
  C_INT k;

  for (k = 0; k < dim; k++) pid[k] = 0;

  for (k = 1; k < dim; k++)
    if (index[k] == index[k - 1])
      pid[k] = k;
  return;
}

void CTimeScaleSeparationMethod::start(const CState * initialState)
{
  /* Retrieve the model to calculate */
  mpModel = mpProblem->getModel();

  /* Reset lsoda */

  mLsodaStatus = 1;
  mState = 1;
  mJType = 2;
  mErrorMsg.str("");
  mLSODA.setOstream(mErrorMsg);

  /* Release previous state and make the initialState the current */
  pdelete(mpState);
  mpState = new CState(*initialState);
  mY = mpState->beginIndependent();
  mTime = mpState->getTime();

  mReducedModel = true; /* * getValue("Integrate Reduced Model").pBOOL; */
  if (mReducedModel)
    {
      mpState->setUpdateDependentRequired(true);
      mData.dim = mpState->getNumIndependent();
    }
  else
    {
      mpState->setUpdateDependentRequired(false);
      mData.dim = mpState->getNumIndependent() + mpModel->getNumDependentMetabs();
    }

  mYdot.resize(mData.dim);

  mJacobian.resize(mData.dim, mData.dim);

  /* Tolerance for Deuflhard criterium  */

  mDtol = * getValue("Deuflhard Tolerance").pUDOUBLE;

  mVslow.resize(mData.dim);

  /* Configure lsoda */
  mRtol = * getValue("Relative Tolerance").pUDOUBLE;
  initializeAtol();

  mDWork.resize(22 + mData.dim * std::max<C_INT>(16, mData.dim + 9));
  mDWork[4] = mDWork[5] = mDWork[6] = mDWork[7] = mDWork[8] = mDWork[9] = 0.0;
  mIWork.resize(20 + mData.dim);
  mIWork[4] = mIWork[6] = mIWork[9] = 0;

  mIWork[5] = * getValue("Max Internal Steps").pUINT;
  mIWork[7] = * getValue("Adams Max Order").pUINT;
  mIWork[8] = * getValue("BDF Max Order").pUINT;

  return;
}

void CTimeScaleSeparationMethod::initializeAtol()
{
  C_FLOAT64 * pTolerance = getValue("Absolute Tolerance").pUDOUBLE;

  mAtol.resize(mData.dim);
  C_FLOAT64 * pAtol = mAtol.array();
  C_FLOAT64 * pEnd = pAtol + mAtol.size();

  CModelEntity **ppEntity = mpModel->getStateTemplate().beginIndependent();
  CMetab * pMetab;

  for (; pAtol != pEnd; ++pAtol, ++ppEntity)
    {
      *pAtol = *pTolerance;

      // Rescale for metabolites as we are using particle numbers
      if ((pMetab = dynamic_cast< CMetab * >(*ppEntity)) != NULL)
        {
          *pAtol *=
            pMetab->getCompartment()->getValue() * mpModel->getQuantity2NumberFactor();
        }
    }
}

void CTimeScaleSeparationMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CTimeScaleSeparationMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  assert (y == mY);

  mpState->setTime(*t);

  mpModel->setState(*mpState);
  mpModel->applyAssignments();

  if (mReducedModel)
    mpModel->calculateDerivativesX(ydot);
  else
    mpModel->calculateDerivatives(ydot);

  return;
}
