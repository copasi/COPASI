// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CCSPMethod.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2007/04/12 12:47:49 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CCSPMethod.h"
#include "CTSSAProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CState.h"
#include "utilities/CMatrix.h"
#include "utilities/CAnnotatedMatrix.h"
#include "report/CCopasiObjectReference.h"

#include "clapackwrap.h"        // CLAPACK
#include "blaswrap.h"           // BLAS

CCSPMethod::CCSPMethod(const CCopasiContainer * pParent):
    CTSSAMethod(CCopasiMethod::tssCSP, pParent),
    mpState(NULL),
    mY(NULL)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CCSPMethod::CCSPMethod(const CCSPMethod & src,
                       const CCopasiContainer * pParent):
    CTSSAMethod(src, pParent),
    mpState(NULL),
    mY(NULL)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CCSPMethod::~CCSPMethod()
{
  pdelete(mpState);
}

void CCSPMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Ratio of Modes Separation", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Maximum Relative Error", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Maximum Absolute Error", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Use Stoichiometric Vectors", CCopasiParameter::BOOL, (bool) false);

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

bool CCSPMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

void CCSPMethod::integrationStep(const double & deltaT)
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
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTSSAMethod + 1, mErrorMsg.str().c_str());
    }

  mpState->setTime(mTime);
  *mpCurrentState = *mpState;

  return;
}

/* multiply submatrix */
void CCSPMethod::smmult(CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & C, C_INT & n1, C_INT & n2, C_INT & n3)
{
  C_INT i, j, k;

  for (i = 0; i < n1 ; i++)
    for (j = 0; j < n3; j++)
      {
        C(i, j) = 0.;
        for (k = 0; k < n2; k++)
          C(i, j) += A(i, k) * B(k, j);
      }
  return;
}

/* substruct submatrix */
void CCSPMethod::smsubst(CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & C, C_INT & n1, C_INT & n2)
{
  C_INT i, j;

  for (i = 0; i < n1 ; i++)
    for (j = 0; j < n2; j++)
      C(i, j) = A(i, j) - B(i, j);

  return;
}

/* add submatrix */
void CCSPMethod::smadd(CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & C, C_INT & n1, C_INT & n2)
{
  C_INT i, j;

  for (i = 0; i < n1 ; i++)
    for (j = 0; j < n2; j++)
      C(i, j) = A(i, j) + B(i, j);

  return;
}

/* normalise submatrix */
void CCSPMethod::smnorm(C_INT & n, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, C_INT & n1)
{
  C_INT i, j;
  C_FLOAT64 c, d;

  for (j = 0; j < n1 ; j++)
    {
      c = 0.0;

      for (i = 0; i < n ; i++)
        {
          d = fabs(A(i, j));
          if (d > c) c = d;
        }

      for (i = 0; i < n ; i++)
        {
          A(i, j) = A(i, j) / c;
          B(j, i) = B(j, i) * c;
        }
    }
  return;
}

void CCSPMethod::sminverse(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{

  /*  int dgetrf_(integer *m, integer *n, doublereal *a, integer *
  * lda, integer *ipiv, integer *info)
  *
  *   -- LAPACK routine (version 3.0) --
  *      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
  *      Courant Institute, Argonne National Lab, and Rice University
  *      March 31, 1993
  *
  *
  *   Purpose
  *   =======
  *
  *   DGETRF computes an LU factorization of a general M-by-N matrix A
  *   using partial pivoting with row interchanges.
  *
  *   The factorization has the form
  *      A = P * L * U
  *   where P is a permutation matrix, L is lower triangular with unit
  *   diagonal elements (lower trapezoidal if m > n), and U is upper
  *   triangular (upper trapezoidal if m < n).
  *
  *   This is the right-looking Level 3 BLAS version of the algorithm.
  *
  *   Arguments
  *   =========
  *
  *   M       (input) INTEGER
  *           The number of rows of the matrix A.  M >= 0.
  *
  *   N       (input) INTEGER
  *           The number of columns of the matrix A.  N >= 0.
  *
  *   A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
  *           On entry, the M-by-N matrix to be factored.
  *           On exit, the factors L and U from the factorization
  *           A = P*L*U; the unit diagonal elements of L are not stored.
  *
  *   LDA     (input) INTEGER
  *           The leading dimension of the array A.  LDA >= max(1,M).
  *
  *   IPIV    (output) INTEGER array, dimension (min(M,N))
  *           The pivot indices; for 1 <= i <= min(M,N), row i of the
  *           matrix was interchanged with row IPIV(i).
  *
  *   INFO    (output) INTEGER
  *           = 0:  successful exit
  *           < 0:  if INFO = -i, the i-th argument had an illegal value
  *           > 0:  if INFO = i, U(i,i) is exactly zero. The factorization
  *                 has been completed, but the factor U is exactly
  *                 singular, and division by zero will occur if it is used
  *                 to solve a system of equations.
  *
  *   =====================================================================
  */
  C_INT info = 0;

  C_INT * ipiv;
  ipiv = new C_INT [n];

  C_INT N = n;
  C_INT M = m;

  dgetrf_(&N, &M, A.array(), &N, ipiv, &info);

  if (info != 0)
    {
      std::cout << "After dgetrf_  INFO\n" << info << std::endl;
      return;
    }

  /*      int dgetrs_(char *trans, integer *n, integer *nrhs,
  * doublereal *a, integer *lda, integer *ipiv, doublereal *b, integer *
  * ldb, integer *info)
  *
  *   -- LAPACK routine (version 3.0) --
  *      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
  *      Courant Institute, Argonne National Lab, and Rice University
  *      March 31, 1993
  *
  *
  *   Purpose
  *   =======
  *
  *   DGETRS solves a system of linear equations
  *      A * X = B  or  A' * X = B
  *   with a general N-by-N matrix A using the LU factorization computed
  *   by DGETRF.
  *
  *   Arguments
  *   =========
  *
  *   TRANS   (input) CHARACTER*1
  *           Specifies the form of the system of equations:
  *           = 'N':  A * X = B  (No transpose)
  *           = 'T':  A'* X = B  (Transpose)
  *           = 'C':  A'* X = B  (Conjugate transpose = Transpose)
  *
  *   N       (input) INTEGER
  *           The order of the matrix A.  N >= 0.
  *
  *   NRHS    (input) INTEGER
  *           The number of right hand sides, i.e., the number of columns
  *           of the matrix B.  NRHS >= 0.
  *
  *   A       (input) DOUBLE PRECISION array, dimension (LDA,N)
  *           The factors L and U from the factorization A = P*L*U
  *           as computed by DGETRF.
  *
  *   LDA     (input) INTEGER
  *           The leading dimension of the array A.  LDA >= max(1,N).
  *
  *   IPIV    (input) INTEGER array, dimension (N)
  *           The pivot indices from DGETRF; for 1<=i<=N, row i of the
  *           matrix was interchanged with row IPIV(i).
  *
  *   B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS)
  *           On entry, the right hand side matrix B.
  *           On exit, the solution matrix X.
  *
  *   LDB     (input) INTEGER
  *           The leading dimension of the array B.  LDB >= max(1,N).
  *
  *   INFO    (output) INTEGER
  *           = 0:  successful exit
  *           < 0:  if INFO = -i, the i-th argument had an illegal value
  *
  *   =====================================================================
  */
  info = 0;
  char T = 'T'; /* difference between fortran's and c's matrix storrage */
  C_INT one = 1;

  C_INT i, j;

  for (i = 0; i < m ; i++)
    {
      for (j = 0; j < m ; j++)
        B(i, j) = 0.;

      B(i, i) = 1.;
    }

  dgetrs_(&T, &N, &one, A.array(), &M, ipiv, B.array(), &N, &info);

  if (info != 0)
    {
      std::cout << "After dgetrs_  INFO\n" << info << std::endl;
      return;
    }

  return;
}

/* Schur decomposition */
void CCSPMethod::schur(C_INT & n, CMatrix< C_FLOAT64 > & A,
                       CMatrix< C_FLOAT64 > & P, CMatrix< C_FLOAT64 > & S)
{

  /* int dgees_(char *jobvs, char *sort, L_fp select, integer *n,
   * doublereal *a, integer *lda, integer *sdim, doublereal *wr,
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

  C_INT dim = n;
  C_INT SDIM = 0;

  CVector<C_FLOAT64> R;
  R.resize(dim*dim);
  C_INT i, j;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      R[j + dim*i] = A(j, i);

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
        S(j, i) = Q.array()[j + dim * i];
        P(j, i) = R.array()[j + dim * i];
      }

  return;
}

void CCSPMethod::map_index(C_FLOAT64 *eval_r, C_INT *index,
                           C_INT & dim)
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

void CCSPMethod::update_nid(C_INT *index, C_INT *nid, C_INT & dim)
{
  C_INT k;

  for (k = 0; k < dim; k++) nid[k] = 0;

  for (k = 1; k < dim - 1; k++)
    if (index[k] == index[k + 1])
      nid[k - 1] = k;
  return;
}

void CCSPMethod::update_pid(C_INT *index, C_INT *pid, C_INT & dim)
{
  C_INT k;

  for (k = 0; k < dim; k++) pid[k] = 0;

  for (k = 1; k < dim; k++)
    if (index[k] == index[k - 1])
      pid[k] = k;
  return;
}
/*********************************************************************************/

/* sort out fast time-scales  according to the time-scale separation ratio */
void CCSPMethod::sortOutTimeScales(C_INT & n, C_INT & M, C_INT & k, CVector< C_FLOAT64 > & tsc)
{
#ifdef CSP_DEBUG

  std::cout << "Sort out time scales: " << std::endl;
#endif

  C_INT max = n - M;
  C_FLOAT64 tmp;

  k = 0;

  C_INT i;

  for (i = 0; i < max - 1 ; i++)
    {
      if (tsc[i] != tsc[i + 1])
        {
          tmp = tsc[i] / tsc[i + 1];
#ifdef CSP_DEBUG

          std::cout << "tsc[" << i << "]/tsc[" << i + 1 << "] " << tmp << std::endl;
#endif

          if (tmp < mEps) k++;
          else i = max;
        }
      else
        {
#ifdef CSP_DEBUG
          std::cout << "the following time scales are equal:  " << std::endl;
          std::cout << "tsc[" << i << "] = tsc[" << i + 1 << "]= " << tsc[i] << std::endl;
#endif
          if (i < max - 1)
            {
              tmp = tsc[i + 1] / tsc[i + 2];

              if (tmp < mEps)
                k += 1;
              else i = max;
            }
          // else TO DO
        }
    }
  return;
}
/* build the fast subspace projection matrix */
void CCSPMethod::fastSubspaceProjectionMatrix(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & Q)
{
  smmult(A, B, Q, n, m, n);

  return;
}

void CCSPMethod::cspstep0(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{
#ifdef CSP_DEBUG

  std::cout << "CSP start procedure " << std::endl;

#endif

  /* compute jacobian and derivatives for the current state */

  C_INT i, j;
  /* n = mData.dim;
  m = n; */

  mpModel->updateSimulatedValues();

  for (j = 0; j < n; j++)
    {
      mG[j] = 0.;
      mY[j] = mpModel->getMetabolitesX()[j]->getValue();
      mYerror[j] = mRerror * mY[j] + mAerror;
    }

  mpModel->calculateDerivativesX(mG.array());

  mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

  /* find eigenvalues of Jacobian  and initial basis vectors  */

  CMatrix<C_FLOAT64> SCHUR;
  CMatrix<C_FLOAT64> SCHURV;

  SCHUR.resize(n, n);
  SCHURV.resize(n, n);

  schur(n, mJacobian, SCHUR, SCHURV);

  CVector<C_FLOAT64> eigen;
  CVector<C_FLOAT64> tsc;

  eigen.resize(n);
  tsc.resize(n);

#ifdef CSP_DEBUG

  std::cout << "CSP start: the schur matrix " << std::endl;
  std::cout << SCHUR << std::endl;

  std::cout << "CSP start: the matrix of schur vectors " << std::endl;
  std::cout << SCHURV << std::endl;
#endif

  /* ordered real parts of eigen values */

  for (i = 0; i < n; i++)
    {
      eigen[i] = SCHUR(n - 1 - i, n - 1 - i);

      tsc[i] = 1. / abs(eigen[i]);
    }

#ifdef CSP_DEBUG

  std::cout << "CSP start: the eigen values ordered by decreasing of absolute value of real part "
  << std::endl;
  for (i = 0; i < n; i++)
    std::cout << "eigen[" << i << "]  " << eigen[i] << std::endl;

  std::cout << "CSP start : the time scales  " << std::endl;
  for (i = 0; i < n; i++)
    std::cout << "1/eigen[" << i << "]  " << tsc[i] << std::endl;

#endif

  CMatrix<C_FLOAT64> A0;
  CMatrix<C_FLOAT64> B0;
  A0.resize(n, n);
  B0.resize(n, n);

  /* trial basis vectors */

  /* use the matrix of Schur vectors */

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      {
        A0(i, j) = SCHURV(i, n - 1 - j);
        B0(i, j) = 0;
      }

  smnorm(n, A0, B0, n);
  sminverse(n, n, A0, B0);

#ifdef CSP_DEBUG

  std::cout << "CSP start: the trial basis vectors " << std::endl;
  std::cout << "columne basis vectors are the columne of A0" << std::endl;
  std::cout << A0 << std::endl;

  std::cout << "row basis vectors are the rows of B0" << std::endl;
  std::cout << B0 << std::endl;

#endif

#ifdef CSP_DEBUG

  /* ideal basis vectors  should diagonalize matrix B*J*A */

  CMatrix<C_FLOAT64> L0;
  CMatrix<C_FLOAT64> TMP;

  L0.resize(n, n);
  TMP.resize(n, n);

  smmult(mJacobian, A0, TMP, n, n, n);
  smmult(B0, TMP, L0, n, n, n);

  std::cout << "CSP start : an ideal basis should diagonalize matrix B0*J*A0" << std::endl;
  std::cout << L0 << std::endl;

#endif

  /* sort out time-scales  */

  C_INT k, fast, l = 0;

  sortOutTimeScales(n, l, k, tsc);

  fast = k;

#ifdef CSP_DEBUG

  std::cout << "CSP start: the number of fast modes " << std::endl;
  std::cout << fast << std::endl;

  if (fast > 0)
    {
      std::cout << "CSP start: the resolution time  " << std::endl;
      std::cout << tsc[k] << std::endl;
    }
#endif
  if (fast > 0)
    {
      m = fast;

      CMatrix<C_FLOAT64> T0;
      T0.resize(m, m);

      sminverse(m, m, L0, T0);

      /* CMatrix<C_FLOAT64> A;
      CMatrix<C_FLOAT64> B;

      A.resize(n,m);
      B.resize(m,n); */

      for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
          {
            A(j, i) = A0 (j, i);
            B(i, j) = B0(i, j);
          }

#ifdef CSP_DEBUG

      if (mStoi)
        {

          /* use stoichiometric vectors to build the fast reaction pointer */

          const CMatrix< C_FLOAT64 > & redStoi = mpModel->getRedStoi();

          for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
              {
                A0(i, j) = redStoi(i, j);
                B0(i, j) = 0;
              }

          smnorm(n, A0, B0, n);
          sminverse(n, n, A0, B0);
        }

      /* build the fast subspace projection matrix */

      CMatrix<C_FLOAT64> Q;
      Q.resize(n, n);

      fastSubspaceProjectionMatrix(n, m, A, B, Q);

      std::cout << "CSP start: the fast subspace projection matrix   " << std::endl;
      std::cout << Q << std::endl;

      CMatrix<C_FLOAT64> Qtmp;
      Qtmp.resize(n, n);

      for (k = 0; k < fast ; ++k)
        {
          CMatrix<C_FLOAT64> Qm;
          Qm.resize(n, n);

          for (j = 0; j < n; ++j)
            for (i = 0; i < n; ++i)
              {
                Qm(i, j) = A(i, k) * B(k, j);
                Qtmp(i, j) += Qm(i, j);
              }

          std::cout << "CSP start: the " << k << "-th fast mode projection matrix  " << std::endl;
          std::cout << Qm << std::endl;

          if (mStoi)
            {
              C_INT r;

              std::cout << "CSP start: the elements of fast reaction pointer of the " << k << "-th mode :  "
              << std::endl;

              C_FLOAT64 Pmr;

              for (r = 0; r < n; ++r)
                for (i = 0; i < n; ++i)
                  {
                    TMP(i, r) = 0.;
                    for (j = 0; j < n; ++j)
                      TMP(i, r) += Qm(i, j) * A0(j, r);

                    Pmr = B0(r, i) * TMP(i, r);
                  }

              std::cout << "Pk(" << r << ") " << Pmr << std::endl;
            }
        }

      std::cout << "CSP start: the summed fast subspace projection matrix (should be = Q):  " << std::endl;
      std::cout << Qtmp << std::endl;
#endif
    }
  else

#ifdef CSP_DEBUG
    std::cout << "CSP start: fast = 0  for the setted Ratio of Modes Separation " << std::endl;
#else
    return; // TO DO: include some WARNING on this subject
#endif

  return;
}

/* correct for the contribution of the fast time-scales  to y  */
void CCSPMethod::yCorrection(C_INT & n, C_INT & m, CVector< C_FLOAT64 > & y, CVector< C_FLOAT64 > & g, CMatrix< C_FLOAT64 > & J, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{
  CMatrix<C_FLOAT64> TMP;
  CMatrix<C_FLOAT64> L;
  CMatrix<C_FLOAT64> TAU;
  CMatrix<C_FLOAT64> TAUA;
  CMatrix<C_FLOAT64> G;
  CMatrix<C_FLOAT64> F;
  CMatrix<C_FLOAT64> DY;

  TMP.resize(n, m);
  L.resize(m, m);
  TAU.resize(m, m);
  G.resize(n, 1);
  F.resize(m, 1);
  DY.resize(n, 1);

  /* B*J*A */

  smmult(J, A, TMP, n, n, m);
  smmult(B, TMP, L, m, n, m);

#ifdef CSP_DEBUG

  /* ideal basis vectors should diagonalize matrix B*J*A */

  std::cout << "Correction procedure: the  matrix B*J*A:" << std::endl;
  std::cout << L << std::endl;

#endif

  sminverse(m, m, L, TAU);

#ifdef CSP_DEBUG

  /* inverse of B*J*A */

  std::cout << "Correction procedure: the inverse of  B*J*A:" << std::endl;
  std::cout << TAU << std::endl;

#endif

  /* A*TAU */

  smmult(A, TAU, TMP, n, m, m);

  /* evaluate the fast mode's amplitude */

  C_INT i;

  for (i = 0; i < n; i++)
    G(i, 0) = g[i];

#ifdef CSP_DEBUG

  std::cout << "Correction procedure: the current B " << std::endl;
  std::cout << B << std::endl;

  std::cout << "Correction procedure: the current right hand side " << std::endl;
  std::cout << G << std::endl;

#endif
  /* F=B*G */

  C_INT k = 1;
  smmult(B, G, F, m, n, k);

#ifdef CSP_DEBUG

  std::cout << "Correction procedure: the fast modes amplitudes " << std::endl;
  std::cout << F << std::endl;

#endif

  /* contribution of the fast time-scales */
  /* A*TAU*F */
  smmult(TMP, F, DY, n, m, k);

  for (i = 0; i < n; i++)
    y[i] -= DY(i, 0);

  return;
}

/* evaluate derivatives for the current y */
void CCSPMethod::calculateDerivativesX(C_INT & n, CVector<C_FLOAT64> & y, CVector <C_FLOAT64> & g)
{
  C_INT i;

  CVector<C_FLOAT64> tmp;
  tmp.resize(n);

  /* make copy of the current state concentrations */
  for (i = 0; i < n; i++)
    tmp[i] = mpModel->getMetabolitesX()[i]->getValue();

  /* write new concentrations in the current state */
  for (i = 0; i < n; i++)
    mpModel->getMetabolitesX()[i]->setConcentration(y[i]);

  mpState->setUpdateDependentRequired(true);
  mpModel->updateSimulatedValues();
  mpModel->calculateDerivativesX(g.array());

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor()
                          / mpModel->getCompartments()[0]->getInitialValue();

  for (i = 0; i < n; ++i)
    g[i] *= number2conc;

  /* write back concentrations of the current state*/
  for (i = 0; i < n; i++)
    mpModel->getMetabolitesX()[i]->setValue(tmp[i]);

  mpState->setUpdateDependentRequired(true);
  mpModel->updateSimulatedValues();

  return;
}

/* evaluate jacobian for the current y */
void CCSPMethod::calculateJacobianX(C_INT & n, CVector<C_FLOAT64> & y, CMatrix <C_FLOAT64> & J)
{
  C_INT i;

  CVector<C_FLOAT64> tmp;
  tmp.resize(n);

  /* make copy of the current state concentrations */
  for (i = 0; i < n; i++)
    tmp[i] = mpModel->getMetabolitesX()[i]->getValue();

  /* write new concentrations in the current state */
  for (i = 0; i < n; i++)
    mpModel->getMetabolitesX()[i]->setConcentration(y[i]);

  mpState->setUpdateDependentRequired(true);
  mpModel->updateSimulatedValues();
  mpModel->calculateJacobianX(J, 1e-6, 1e-12);

  /* write back concentrations of the current state*/
  for (i = 0; i < n; i++)
    mpModel->getMetabolitesX()[i]->setValue(tmp[i]);

  mpState->setUpdateDependentRequired(true);
  mpModel->updateSimulatedValues();

  return;
}

/* detection of  new fast modes */
void CCSPMethod::fastModesDetection(C_INT & n, C_INT & m, C_FLOAT64 & tisc, CMatrix< C_FLOAT64 > & J, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{

  /* the fast subspace projection matrix */

  CMatrix<C_FLOAT64> Q;
  CMatrix<C_FLOAT64> I;
  I.resize(n, n);
  Q.resize(n, n);

  C_INT i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      I(i, j) = 0.;

  for (i = 0; i < n; i++)
    I(i, i) = 1.;

  fastSubspaceProjectionMatrix(n, m, A, B, Q);

#ifdef CSP_DEBUG

  std::cout << "Fast Modes Detection: the fast subspace projection matrix  " << std::endl;
  std::cout << Q << std::endl;

#endif

  /*  the slow subspace projection matrix */

  CMatrix<C_FLOAT64> QSL;
  QSL.resize(n, n);

  smsubst(I, Q, QSL, n, n);

#ifdef CSP_DEBUG

  std::cout << "Fast Modes Detection: the  slow subspace projection matrix   " << std::endl;
  std::cout << QSL << std::endl;

#endif
  /* JSL = J*(I-A*B) */

  CMatrix<C_FLOAT64> JSL;
  JSL.resize(n, n);

  smmult(J, QSL, JSL, n, n, n);

#ifdef CSP_DEBUG

  std::cout << "Fast Modes Detection: the projection of jacobian on the slow space   " << std::endl;
  std::cout << JSL << std::endl;

#endif

  /* find eigenvalues of the projection of Jacobian on the slow subspace and basis vectors  */

  CMatrix<C_FLOAT64> SCHUR;
  CMatrix<C_FLOAT64> SCHURV;

  SCHUR.resize(n, n);
  SCHURV.resize(n, n);

  schur(n, JSL, SCHUR, SCHURV);

  CVector<C_FLOAT64> eigen;
  CVector<C_FLOAT64> tsc;

  eigen.resize(n);
  tsc.resize(n);

#ifdef CSP_DEBUG

  std::cout << "Fast Modes Detection: the schur matrix " << std::endl;
  std::cout << SCHUR << std::endl;

  std::cout << "Fast Modes Detection: the matrix of schur vectors " << std::endl;
  std::cout << SCHURV << std::endl;
#endif

  /* ordered real parts of eigen values */

  for (i = 0; i < n; i++)
    {
      eigen[i] = SCHUR(n - 1 - i, n - 1 - i);

      tsc[i] = 1. / abs(eigen[i]);
    }

#ifdef CSP_DEBUG

  std::cout << "Fast Modes Detection: the eigen values ordered by decreasing of absolute value of real part " << std::endl;
  for (i = 0; i < n; i++)
    std::cout << "eigen[" << i << "]  " << eigen[i] << std::endl;

  std::cout << "Fast Modes Detection: the time scales  " << std::endl;
  for (i = 0; i < n; i++)
    std::cout << "1/eigen[" << i << "]  " << tsc[i] << std::endl;

#endif

  CMatrix<C_FLOAT64> A0;
  CMatrix<C_FLOAT64> B0;
  A0.resize(n, n);
  B0.resize(n, n);

  /*  basis vectors */

  /* use the matrix of Schur vectors */

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      {
        A0(i, j) = SCHURV(i, n - 1 - j);
        B0(i, j) = 0;
      }

  smnorm(n, A0, B0, n);
  sminverse(n, n, A0, B0);

#ifdef CSP_DEBUG

  std::cout << "Fast Modes Detection: the trial basis vectors " << std::endl;
  std::cout << "columne basis vectors are the columne of A0" << std::endl;
  std::cout << A0 << std::endl;

  std::cout << "row basis vectors are the rows of B0" << std::endl;
  std::cout << B0 << std::endl;

#endif

  /* sort out time-scales  */

  C_INT k, fast;

  sortOutTimeScales(n, m, k, tsc);  // ? TO check: with m!=0

  fast = m + k;

#ifdef CSP_DEBUG

  std::cout << " Fast Modes Detection: the number of new fast modes   " << std::endl;
  std::cout << k << std::endl;

  if (k > 0)
    {
      std::cout << "Fast Modes Detection: the resolution time  " << std::endl;
      std::cout << tsc[k] << std::endl;
    }
#endif

  /* project the new basises in the "old" fast subspace */

  CMatrix<C_FLOAT64> A0F;
  CMatrix<C_FLOAT64> B0F;

  A0F.resize(n, n);
  B0F.resize(n, n);

  smmult(B0, Q, B0F, k, n, n);

  for (i = 0; i < n; i++)
    for (j = 0; j < k; j++)
      B0(j, i) = B0F(j, i);

  smmult(Q, A0, A0F, n, n, k);

  for (i = 0; i < n; i++)
    for (j = 0; j < k; j++)
      A0(i, j) = A0F(i, j);

  smnorm(n, A0, B0, k);

  CMatrix<C_FLOAT64> QF;
  CMatrix<C_FLOAT64> QIF;
  CMatrix<C_FLOAT64> TMP;

  QF.resize(k, k);
  QIF.resize(k, k);
  TMP.resize(n, n);

  /* find a projection submatrix for the new found fast modes*/

  smmult(B0, A0, QF, k, n, k);

  sminverse(k, k, QF, QIF);

  smmult(QIF, B0, TMP, k, k, n);

  for (i = 0; i < n; i++)
    for (j = 0; j < k; j++)
      {
        A(i, m + j) = A0(i, j);
        B(m + j, i) = TMP(j, i);
      }

  m = fast;

  tisc = tsc[k + 1];

  return;
}

/* the CSP refinement procedure, step 1 :
 * refine the row  vectors B ,
 * colume vectors A  are known */

void CCSPMethod::bRefinement(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A0, CMatrix< C_FLOAT64 > & B0, CMatrix< C_FLOAT64 > & J, CMatrix< C_FLOAT64 > & B)
{

  CMatrix<C_FLOAT64> TMP;
  CMatrix<C_FLOAT64> L0;
  CMatrix<C_FLOAT64> TAU;
  CMatrix<C_FLOAT64> TMP1;

  TMP.resize(n, m);
  L0.resize(m, m);
  TAU.resize(m, m);
  TMP1.resize(m, n);

  /* B0*J*A0 */
  smmult(J, A0, TMP, n, n, m);
  smmult(B0, TMP, L0, m, n, m);

  sminverse(m, m, L0, TAU);

  /* B=TAU*B0*J */

  smmult(TAU, B0, TMP1, m, m, n);
  smmult(TMP1, J, B, m, n, n);

  return;
}

/* the CSP refinement procedure, step 2 :
 * refine the columen vectors A
 * as the row vectors B  use the refined in step 1*/

void CCSPMethod::aRefinement(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A0, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & J, CMatrix< C_FLOAT64 > & A)
{
  CMatrix<C_FLOAT64> TMP;
  CMatrix<C_FLOAT64> L;
  CMatrix<C_FLOAT64> TAU;

  TMP.resize(n, m);
  L.resize(m, m);
  TAU.resize(m, m);

  /* B*J*A0 */

  smmult(J, A0, TMP, n, n, m);
  smmult(B, TMP, L, m, n, m);

  sminverse(m, m, L, TAU);

  /* A=J*A0*TAU */

  smmult(TMP, TAU, A, n, m, m);

  smnorm(n, A, B, m);

  return;
}

/* enforce the criterion to declare a mode exhausted  */
void CCSPMethod::exhaustedFastModesDetection(C_INT & n, C_INT & m, C_INT & tot, C_FLOAT64 & tisc , CVector< C_FLOAT64 > & g, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{
  CMatrix<C_FLOAT64> G;
  CMatrix<C_FLOAT64> F;
  CMatrix<C_FLOAT64> Q;

  G.resize(n, 1);
  F.resize(m, 1);
  Q.resize(n, 1);

  C_INT i;

  for (i = 0; i < n; i++)
    G(i, 0) = g[i];

  /* evaluate the fast mode's amplitude */

  C_INT k = 1;
  smmult(B, G, F, m, n, k);

#ifdef CSP_DEBUG

  std::cout << "Exhausted Fast Modes Detection: the fast mode's amplitude " << std::endl;
  for (i = 0; i < m; i++)
    std::cout << "F " << i << "  " << F(i, 0) << std::endl;

#endif
  smmult(A, F, Q, n, m, k);

  tot = 0;

  for (i = 0; i < n; ++i)
    if (fabs(Q(i, 0))*tisc < mYerror[i]) tot++;

  return;
}

void CCSPMethod::cspstep(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{
#ifdef CSP_DEBUG

  std::cout << "CSP step procedure: exhausted fast modes are present "
  << std::endl;

#endif

  CVector<C_FLOAT64> g;
  CVector<C_FLOAT64> y;

  CMatrix<C_FLOAT64> J;

  g.resize(n);
  y.resize(n);
  J.resize(n, n);

  C_INT i;

  for (i = 0; i < n; ++i)
    y[i] = mpModel->getMetabolitesX()[i]->getValue();
  g = mG;
  J = mJacobian;

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor()
                          / mpModel->getCompartments()[0]->getInitialValue();

  for (i = 0; i < n; ++i)
    g[i] *= number2conc;

#ifdef CSP_DEBUG

  std::cout << "CSP step: the current jacobian " << std::endl;
  std::cout << J << std::endl;
  std::cout << "CSP step: the current right hand side " << std::endl;
  std::cout << g << std::endl;

#endif

  /* correct for the contribution of the fast time-scales to y */

  yCorrection(n, m, y, g, J, A, B);

  /* evaluate derivatives and jacobian for the current y */

  calculateDerivativesX(n, y, g);
  calculateJacobianX(n, y, J);

#ifdef CSP_DEBUG

  std::cout << "CSP step: the jacobian after correction " << std::endl;
  std::cout << J << std::endl;
  std::cout << "CSP step: the right hand side after correction " << std::endl;
  std::cout << g << std::endl;

#endif

  /* detection of new fast modes */

  C_FLOAT64 tisc;

  fastModesDetection(n, m, tisc, J, A, B);

  if (m > n)
    {
      std::cout << "csp step procedure:  m > n, m, n " << m << n << std::endl;
      return;
    }

  /* refinement of row vector's b */

  bRefinement(n, m, A, B, J, B);

  /* enforce the criterion to declare a mode exhausted */

  C_INT tot;

  exhaustedFastModesDetection(n, m, tot, tisc, g, A, B);

#ifdef CSP_DEBUG

  std::cout << "CSP step: the number of exhausted fast modes : " << std::endl;
  std::cout << tot << std::endl;

#endif

  aRefinement(n, m, A, B, J, A);

  return;
}

void CCSPMethod::step(const double & deltaT)
{

  C_INT n = mData.dim;
  C_INT m = n;

  CMatrix<C_FLOAT64> A;
  CMatrix<C_FLOAT64> B;

  A.resize(n, n);
  B.resize(n, n);

  cspstep0(n, m, A, B);
  cspstep(n, m, A, B);

  /* integrate one time step */

  integrationStep(deltaT);

  return;
}

void CCSPMethod::start(const CState * initialState)
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

  /* CSP related staff */

  mG.resize(mData.dim);
  mYerror.resize(mData.dim);
  mEps = * getValue("Ratio of Modes Separation").pUDOUBLE;
  mRerror = * getValue("Maximum Relative Error").pUDOUBLE;
  mAerror = * getValue("Maximum Absolute Error").pUDOUBLE;

  mStoi = * getValue("Use Stoichiometric Vectors").pBOOL;

  return;
}

void CCSPMethod::initializeAtol()
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

void CCSPMethod::EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{static_cast<Data *>((void *) n)->pMethod->evalF(t, y, ydot);}

void CCSPMethod::evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  assert (y == mY);

  mpState->setTime(*t);

  mpModel->setState(*mpState);
  mpModel->updateSimulatedValues();

  if (mReducedModel)
    mpModel->calculateDerivativesX(ydot);
  else
    mpModel->calculateDerivatives(ydot);

  return;
}
