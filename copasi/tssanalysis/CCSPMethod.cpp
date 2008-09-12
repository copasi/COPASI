// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CCSPMethod.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/12 14:16:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <math.h>

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
    CTSSAMethod(CCopasiMethod::tssCSP, pParent) //,
    //mpState(NULL),
    //mY(NULL)
{
  assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CCSPMethod::CCSPMethod(const CCSPMethod & src,
                       const CCopasiContainer * pParent):
    CTSSAMethod(src, pParent) //,
    //mpState(NULL),
    //mY(NULL)
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
  initializeIntegrationsParameter();

  assertParameter("Ratio of Modes Separation", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Time Scale of Modes Separation", CCopasiParameter::UDOUBLE, (C_FLOAT64) 0);
  assertParameter("Maximum Relative Error", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-5);
  assertParameter("Maximum Absolute Error", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-10);
  //assertParameter("Maximum Iterations Number", CCopasiParameter::UINT, (unsigned C_INT32) 100);
  //assertParameter("Refinement Iterations Number", CCopasiParameter::UINT, (unsigned C_INT32) 1);
  // assertParameter("Use Stoichiometric Vectors", CCopasiParameter::BOOL, (bool) false);

  createAnnotationsM();
  emptyVectors();
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

void CCSPMethod::sminverse(C_INT & n, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{

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

  C_INT info = 0;

  C_INT * ipiv;
  ipiv = new C_INT [n];

  C_INT N = n;

  CMatrix<C_FLOAT64> TMP;
  TMP.resize(N, N);

  TMP = A;

  C_INT i, j;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      B(i, j) = 0.;

  for (i = 0; i < N; i++)
    B(i, i) = 1.;

  dgesv_(&N, &N, TMP.array(), &N, ipiv, B.array(), &N, &info);

  if (info != 0)
    {
      std::cout << "After dgesv_  INFO\n" << info << std::endl;
      return;
    }

  return;
}

/* find  the new number of fast  according to the time-scale separation ratio */
/*  TODO : equal,complex  eigenvalues are presenting !!! */
void CCSPMethod::findTimeScaleSeparation(C_INT & n, C_INT & k, CVector< C_FLOAT64 > & eigen, C_INT & info)
{

  C_INT i;
  C_FLOAT64 tmp;

  k = 0;
  i = 0;

  if (mTsc)
    for (i = 0; i < n; i++)
      {
        tmp = 1. / eigen[i];
        if (tmp < 0 && fabs(tmp) < mTsc)
          k++;

        else
          {
            if (tmp > 0) info = 1;
            break;
          }
      }
  else
    for (i = 0; i < n - 1; i++)
      {
        if (eigen[i] != eigen[i + 1])
          {
            tmp = eigen[i + 1 ] / eigen[i];

#if 0

            std::cout << "tsc[" << i << "]/tsc[" << i + 1 << "] " << tmp << std::endl;
            std::cout << "mEps " << mEps << std::endl;
#endif

            if (tmp > 0 && tmp < mEps)
              {
                k++;
                if (i)
                  if (eigen(i) == eigen(i - 1)) k++;
              }
            else
              {
                if (tmp < 0) info = 1;
                break;
              }
          }
        else
          {

#if 0
            std::cout << "the following time scales are equal:  " << std::endl;
            std::cout << "tsc[" << i << "] = tsc[" << i + 1 << "] " << std::endl;
#endif
          }
      }

  return;
}

void CCSPMethod::cspstep(C_INT & N, C_INT & M, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{

  C_INT32 reacs_size = mpModel->getReactions().size();
  emptyOutputData(N, N, reacs_size);

#if 1
  std::cout << " *********************  New time step **********************" << std::endl;
#endif

  CVector<C_FLOAT64> g;
  CVector<C_FLOAT64> y;

  CMatrix<C_FLOAT64> J;

  g.resize(N);
  y.resize(N);
  J.resize(N, N);

  C_INT i, j;

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor() / mpModel->getCompartments()[0]->getInitialValue();

  for (j = 0; j < N; j++)
    {
      y[j] = mY[j] * number2conc;
      g[j] = mG[j] * number2conc;
      mYerror[j] = mRerror * y[j] + mAerror;
    }

  J = mJacobian;

#if 0

  std::cout << "concentration of metabolite  and  right hand side :" << std::endl;
  for (j = 0; j < N; j++)
    std::cout << mpModel->getMetabolitesX()[j]->getObjectName() << "  " << y[j] << "  " << g[j] << std::endl;

  std::cout << "current jacobian " << std::endl;
  std::cout << J << std::endl;
#endif

  CMatrix<C_FLOAT64> ALA;
  CMatrix<C_FLOAT64> ALA0;
  CMatrix<C_FLOAT64> TAU;
  CMatrix<C_FLOAT64> F;

  ALA.resize(N, N);
  ALA0.resize(N, N);
  TAU.resize(N, N);
  F.resize(N, 1);

  /* csp iterations */
  C_INT iter = 0;

  CMatrix<C_FLOAT64> QF;
  CMatrix<C_FLOAT64> QSL;

  QF.resize(N, N);
  QSL.resize(N, N);

  mJacobian_initial.resize(N, N);
  mQ.resize(N, N);
  mR.resize(N, N);

  mJacobian_initial = J;

  C_INT info;

  schur(info);

  /* trial basis vectors */

  /* use the matrix of Schur vectors */

  A = mQ;
  B = 0;

  smnorm(N, A, B, N);
  sminverse(N, A, B);

#if 0
  std::cout << "A " << std::endl;
  std::cout << A << std::endl;
  std::cout << "B " << std::endl;
  std::cout << B << std::endl;
#endif

  /* ordered real parts of eigen values */

  CVector<C_FLOAT64> eigen;
  CVector<C_FLOAT64> tsc;

  eigen.resize(N);
  tsc.resize(N);

  for (i = 0; i < N; i++)
    {
      eigen[i] = mR(i, i);

      tsc[i] = 1. / eigen[i];
    }

#if 0
  std::cout << "CSP iteration:  " << std::endl;
  std::cout << "eigen values odered by increasing " << std::endl;
  for (i = 0; i < N; i++)
    std::cout << "eigen[" << i << "]  " << eigen[i] << std::endl;
#endif

#if 1
  std::cout << "time scales :  " << std::endl;
  for (i = 0; i < N; i++)
    std::cout << "1/eigen[" << i << "]  " << fabs(tsc[i]) << std::endl;
#endif

  /* form "transformation" matrix, time derivatives term is omitted  */
  /* ALA = B*J*A  */

  CMatrix<C_FLOAT64> TMP;
  TMP.resize(N, N);

  smmult(B, J, TMP, N, N, N);
  smmult(TMP, A, ALA, N, N, N);

#if 1
  std::cout << "B*J*A should converge to block-diagonal for an ideal basis:" << std::endl;
  std::cout << ALA << std::endl;
#endif

  /* find a new number of  fast modes  */

  info = 0;

  findTimeScaleSeparation(N, M, eigen, info);

  if (info)
    {
      std::cout << "after time scales separation :  " << std::endl;
      std::cout << "info = 0 : negative time scale befor the first slow was found " << std::endl;

      return;
    }
  if (M == N)
    {
      std::cout << "after time scales separation :  " << std::endl;
      std::cout << "number of fast modes = total number of modes" << std::endl;

      return;
    }

  if (M == 0)
    {

      CCopasiMessage(CCopasiMessage::WARNING,
                     MCTSSAMethod + 5, 0);

      std::cout << "after time scales separation :  " << std::endl;
      std::cout << "number of fast modes = 0" << std::endl;

      return;
    }

  std::cout << "CSP iteration:  " << std::endl;

  std::cout << "the new number of modes to be analyzed" << std::endl;
  std::cout << M << std::endl;

  std::cout << "considered time resolution of the solution  " << std::endl;
  std::cout << fabs(tsc[M]) << std::endl;   // to check this

  CVector<C_FLOAT64> gfast;
  CVector<C_FLOAT64> gslow;

  gfast.resize(N);
  gslow.resize(N);

  CMatrix<C_FLOAT64> TAUM;
  CMatrix<C_FLOAT64> ALAM;

  ALAM.resize(M, M);
  TAUM.resize(M, M);

  TAUM = 0;
  ALAM = 0;

  for (i = 0; i < M; i++)
    for (j = 0; j < M; j++)
      ALAM(i, j) = ALA(i, j);

  if (M > 1)
    sminverse(M, ALAM, TAUM);
  else
    TAUM(0, 0) = 1. / ALA(0, 0);

  modesAmplitude(N, M, g, B, F);

  /**
   * correct for the contribution of the fast time-scales to y
   **/

  yCorrection(N, M, y, TAUM, F, A);

  /* right hand side computed  using new y */

  calculateDerivativesX(y.array(), g.array());

  J = 0;

  calculateJacobianX(N, y, J);

  modesAmplitude(N, M, g, B, F);

  ALA = 0;
  TAU = 0;

  /* ALA = B*J*A  */

  smmult(J, A, TMP, N, N, N);
  smmult(B, TMP, ALA, N, N, N);

  for (i = 0; i < M; i++)
    for (j = 0; j < M; j++)
      ALAM(i, j) = ALA(i, j);

  if (M > 1)
    sminverse(M, ALAM, TAUM);
  else
    TAUM(0, 0) = 1. / ALA(0, 0);

cspiteration:

  emptyOutputData(N, M, reacs_size);

#if 1
  std::cout << " *********************  Refinement iteration " << iter << "**********************" << std::endl;
#endif

  CMatrix<C_FLOAT64> A0;
  CMatrix<C_FLOAT64> B0;

  A0.resize(N, N);
  B0.resize(N, N);

#if 0
  std::cout << "last A " << std::endl;
  std::cout << A << std::endl;
  std::cout << "last B " << std::endl;
  std::cout << B << std::endl;
#endif

  basisRefinement(N, M, ALA, TAUM, A, B, A0, B0);

  /* recompute ALA  */

  TMP = 0;
  ALA = 0;
  TAU = 0;

#if 0
  std::cout << "recompute ALA : " << std::endl;
  std::cout << "A0 " << std::endl;
  std::cout << A0 << std::endl;
  std::cout << "B0 " << std::endl;
  std::cout << B0 << std::endl;
  std::cout << "J " << std::endl;
  std::cout << J << std::endl;
#endif

  smmult(J, A0, TMP, N, N, N);
#if 0
  std::cout << "J * A0 " << std::endl;
  std::cout << TMP << std::endl;
#endif
  smmult(B0, TMP, ALA, N, N, N);
#if 0
  std::cout << "B0 * TMP " << std::endl;
  std::cout << ALA << std::endl;
#endif

#if 1
  std::cout << "B0*J*A0 :   " << std::endl;
  std::cout << ALA << std::endl;
#endif

  /* recompute TAU  */

  ALAM.resize(M, M);
  TAUM.resize(M, M);
  TAUM = 0;

  for (i = 0; i < M; i++)
    for (j = 0; j < M; j++)
      ALAM(i, j) = ALA(i, j);

  sminverse(M, ALAM, TAUM);

#if 0

  //sminverse(N, ALA, TAU);

  CMatrix<C_FLOAT64> TEST;
  TEST.resize(M, M);

  //smmult(A0, B0, TEST, N, N, N);

  smmult(ALAM, TAUM, TEST, M, M, M);

  std::cout << "TAUM" << std::endl;
  std::cout << TAUM << std::endl;
  std::cout << "ALAM*TAUM" << std::endl;
  //std::cout << "A0*B0" << std::endl;
  std::cout << TEST << std::endl;
#endif

  /* enforce the criterion to classify  modes*/

  C_INT exhausted;

#if 0
  std::cout << "last amplitudes was:  " << std::endl;
  for (j = 0; j < N; j++)
    std::cout << "F " << j << " = " << F(j, 0) << std::endl;
#endif

  classifyModes(N, M, exhausted, tsc[M - 1], tsc[M], g, A0, B0, F);

  if (exhausted == N)
    {
      std::cout << "after modes classification:  " << std::endl;
      std::cout << "exhausted = tital number of modes" << std::endl;
      return;
    }

  if (exhausted == 0)
    {
      std::cout << "after modes classification:  " << std::endl;
      std::cout << "no exhausted modes for the user given tolerances" << std::endl;

      A = A0;
      B = B0;

      return;

      //iter ++;
      //goto cspiteration;
    }

#if 1
  std::cout << "amplitudes  after refinemnet :  " << std::endl;
  for (i = 0; i < N; i++)
    {

      std::cout << F(i, 0) << std::endl;
    }
#endif

#if 1
  std::cout << "number of exhausted fast modes : " << std::endl;
  std::cout << exhausted << std::endl;
#endif

  M = exhausted;

  CSPradicalPointer(N, M, A0, B0);

  /**
   * correct for the contribution of the fast time-scales to y
   **/

  yCorrection(N, M, y, TAUM, F, A0);

#if 0
  std::cout << "right hand side computed from calculateDerivativesX using new y:  " << std::endl;
#endif

  calculateDerivativesX(y.array(), g.array());
#if 0
  for (i = 0; i < N; i++)
    std::cout << i << "  " << g[i] << std::endl;
#endif

#if 0
  std::cout << "new y and  right hand side :" << std::endl;
  for (j = 0; j < N; j++)
    std::cout << mpModel->getMetabolitesX()[j]->getObjectName() << "  " << y[j] << "  " << g[j] << std::endl;
#endif

  /*  fast subspace projection matrix */
  smmult(A0, B0, QF, N, M, N);

  /* slow subspace projection matrix */
  smsubst(mI, QF, QSL, N, N);

#if 0
  std::cout << "fast subspace projection matrix  " << std::endl;
  std::cout << QF << std::endl;
  std::cout << "slow subspace projection matrix  " << std::endl;
  std::cout << QSL << std::endl;
#endif

  /* decompose right hand side into its fast and slow components */

  for (i = 0; i < N; i++)
    {
      gfast[i] = 0.;
      gslow[i] = 0.;
      for (j = 0; j < N; j++)
        {
          gfast[i] += QF(i, j) * g[j];
          gslow[i] += QSL(i, j) * g[j];
        }
    }

#if 0

  std::cout << "decompose right hand side into its fast and slow components:  " << std::endl;

  std::cout << "fast part of rhs :  " << std::endl;
  /**
   * this fast rhs is the same oder of as slow rhs (component by component)
   * and it's neglect will cause ab oder unity error
   * since it was computed using the trial basis vectors
   * which have never been refined
   **/

  for (i = 0; i < N; i++)
    std::cout << "fast : " << gfast[i] << " slow " << gslow[i]
    << " fast + slow " << gfast[i] + gslow[i] << " g  " << g[i] << std::endl;

  std::cout << "amplitudes  computed using new g:  " << std::endl;
#endif
#if 0
  std::cout << "amplitudes  after correction of y :  " << std::endl;
#endif
  modesAmplitude(N, M, g, B0, F);

  /**
   * compute  CSP Participation Index:
   * a mesure of participation of the r-th elementary reaction to the balansing act of the i-th mode
   * It is assumed that forward and reverse reactions are counted as distinct
   **/

  CSPParticipationIndex(N, tsc[M], B0);

  /**
   * compute CSP Importance Index :
   * a mesure of relative importance  of the contribution of r-th elementaey reaction
   * to the current reaction rate of the i-th spiecies
   **/

  CSPImportanceIndex(N, tsc[M], QSL);

  A = A0;
  B = B0;

  if (M)
    {
      for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
          ALA0(i, j) = ALA(i, j);

      J = 0;
      ALA = 0;
      TAU = 0;

      calculateJacobianX(N, y, J);

#if 0
      std::cout << "Jacobian, computed by calculateJacobianX for the new y, JSL : " << std::endl;
      std::cout << J << std::endl;
#endif

      /* ALA = B*J*A  */

      smmult(J, A, TMP, N, N, N);
      smmult(B, TMP, ALA, N, N, N);

      ALAM.resize(M, M);
      TAUM.resize(M, M);

      for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
          ALAM(i, j) = ALA(i, j);

      sminverse(M, ALAM, TAUM);

#if 1
      std::cout << "B0 * J * A0, after radical correction" << std::endl;
      std::cout << ALA << std::endl;
      std::cout << "ALA0" << std::endl;
      std::cout << ALA0 << std::endl;
#endif

#if 0
      //std::cout << "new TAUM" << std::endl;
      //std::cout << TAUM << std::endl;

      //smmult(ALAM, TAUM, TESTM, M, M, M);

      //std::cout << "ALAM*TAUM" << std::endl;
      //std::cout << TESTM << std::endl;
#endif
    }

  //CSPOutput(N,M,reacs_size);

  if (/*isBlockDiagonal(N, M, ALA0, 1.e-5)*/0) //just to make it compile. It will probably not work
    {
      mSetVectors = 1;
    }
  else
    if (iter < 100)
      {
        iter ++;
        goto cspiteration;
      }
    else
      {
        CCopasiMessage(CCopasiMessage::WARNING,
                       MCTSSAMethod + 6, 0);
        return;
      }

  //mSetVectors = 1;

  //iter++;
  //goto cspiteration;

  return;
}

#ifdef XXXXX
/*  compute  the norm C  of the off-diagonal blocks   */
bool CCSPMethod::isBlockDiagonal(C_INT & N, C_INT & M, CMatrix< C_FLOAT64 > & ALA, C_FLOAT64 small)
{
  C_INT i, j, imax, jmax;
  C_FLOAT64 max = -1.;

  std::cout << "blocks of ALA : " << std::endl;

  std::cout << "upper - left : " << std::endl;

  for (i = 0; i < M; i++)
    {
      for (j = 0 ; j < M; j++)
        std::cout << ALA(i, j) << "  ";

      std::cout << std::endl;
    }

  std::cout << "upper - right : " << std::endl;

  for (i = 0; i < M; i++)
    {
      for (j = M ; j < N; j++)
        std::cout << ALA(i, j) << "  ";

      std::cout << std::endl;
    }

  std::cout << "lower - left : " << std::endl;

  for (i = M; i < N; i++)
    {
      for (j = 0 ; j < M; j++)
        std::cout << ALA(i, j) << "  ";

      std::cout << std::endl;
    }

  std::cout << "upper - right : " << std::endl;

  for (i = M; i < N; i++)
    {
      for (j = M ; j < N; j++)
        std::cout << ALA(i, j) << "  ";

      std::cout << std::endl;
    }

  /* step #1: upper-right block */

  for (i = 0; i < M; i++)
    for (j = M ; j < N; j++)
      if (fabs(ALA(i, j)) > max)
        {
          max = fabs(ALA(i, j));
          imax = i; jmax = j;
        }
  /* step #2: lower-left block */

  for (i = M; i < N; i++)
    for (j = 0 ; j < M; j++)
      if (fabs(ALA(i, j)) > max)
        {
          max = fabs(ALA(i, j));
          imax = i ; jmax = j;
        }
  std::cout << "the norm C of the off-diagonal blocks of ALA is ALA(" << imax << "," << jmax << ") = " << max << std::endl;

  if (max <= small) return 1;
  else
    return 0;
}
#endif

void CCSPMethod::emptyOutputData(C_INT & N, C_INT & M, C_INT & R)
{

  C_INT i, m, r;
  const CCopasiVector< CReaction > & reacs = mpModel->getReactions();

  for (m = 0; m < M; m++)
    for (i = 0; i < N; i++)
      {
        mAmplitude[i] = 0.;
        mRadicalPointer(i, m) = 0;
      }

  for (m = 0; m < M; m++)
    for (r = 0; r < R; r++)
      mFastReactionPointer(r, m) = 0;

  for (i = 0; i < N; i++)
    for (r = 0; r < R; r++)
      mParticipationIndex(r, i) = 0;

  for (i = 0; i < N; i++)
    for (r = 0; r < R; r++)
      mImportanceIndex(r, i) = 0;

  return;
}

void CCSPMethod::CSPOutput(C_INT & N, C_INT & M, C_INT & R)
{

  C_INT i, m, r;
  const CCopasiVector< CReaction > & reacs = mpModel->getReactions();

  std::cout << "Amplitudes of reaction modes :" << std::endl;

  for (m = 0; m < M; m++)
    {
      std::cout << "reaction mode " << m << " :" << std::endl;
      for (i = 0; i < N; i++)
        {
          std::cout << " mode  " << i << "  : " << mAmplitude[i];

          std::cout << std::endl;
        }
      std::cout << std::endl;
      std::cout << "Radical Pointer: whenever is not a small number, species k is said to be CSP radical" << std::endl;

      for (i = 0; i < N; i++)
        std::cout << mpModel->getMetabolitesX()[i]->getObjectName()
        << "   : " << mRadicalPointer(i, m) << std::endl;
    }
  std::cout << std::endl;
  std::cout << " Fast Reaction Pointer of the m-th reaction  mode : whenever is not a small number, " << std::endl;
  std::cout << " the r-th reaction is said to be a fast reaction  " << std::endl;

  for (m = 0; m < M; m++)
    {
      std::cout << "reaction mode " << m << " :" << std::endl;
      for (r = 0; r < R; r++)
        std::cout << reacs[r]->getObjectName() << " :" << mFastReactionPointer(r, m) << std::endl;
    }

  std::cout << std::endl;
  std::cout << " Participation Index : is a mesure of participation of the r-th elementary reaction " << std::endl;
  std::cout << " to the balancing act of the i-th mode " << std::endl;

  for (i = 0; i < N; i++)
    {
      std::cout << "reaction mode " << i << " :" << std::endl;
      for (r = 0; r < R; r++)
        std::cout << reacs[r]->getObjectName() << " :" << mParticipationIndex(r, i) << std::endl;
    }

  std::cout << std::endl;
  std::cout << " Importance Index: is a mesure of relative importance of the contribution of r-th elementary " << std::endl;
  std::cout << " reaction to the current reaction rate of i-th spiecies   " << std::endl;

  for (i = 0; i < N; i++)
    {
      std::cout << mpModel->getMetabolitesX()[i]->getObjectName() << " :" << std::endl;
      for (r = 0; r < R; r++)
        std::cout << reacs[r]->getObjectName() << " :" << mImportanceIndex(r, i) << std::endl;
    }

  return;
}
void CCSPMethod::step(const double & deltaT)
{
  C_INT N = mData.dim;

  C_INT M = 0;

  CMatrix<C_FLOAT64> A;
  CMatrix<C_FLOAT64> B;

  A.resize(N, N);
  B.resize(N, N);

  C_INT i, j;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      {
        A(i, j) = 0;
        B(i, j) = 0;
      }

  mpModel->updateSimulatedValues(mReducedModel);

  for (j = 0; j < N; j++)
    {
      mG[j] = 0.;
      mY[j] = mpModel->getMetabolitesX()[j]->getValue();
    }

  mpModel->calculateDerivativesX(mG.array());

  mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

  cspstep(N, M, A, B);

  setVectors();

  mCurrentStep = + 1;

  /* integrate one time step */

  integrationStep(deltaT);

  return;
}

void CCSPMethod::start(const CState * initialState)
{
  emptyVectors();

  integrationMethodStart(initialState);

  /* CSP related staff */

  mG.resize(mData.dim);
  mYerror.resize(mData.dim);
  mEps = * getValue("Ratio of Modes Separation").pUDOUBLE;
  mTsc = * getValue("Time Scale of Modes Separation").pUDOUBLE;
  mRerror = * getValue("Maximum Relative Error").pUDOUBLE;
  mAerror = * getValue("Maximum Absolute Error").pUDOUBLE;
  //nIter = * getValue("Refinement Iterations Number").pUINT;

  mI.resize(mData.dim, mData.dim);

  C_INT i, j;

  for (i = 0; i < mData.dim; i++)
    for (j = 0; j < mData.dim; j++)
      mI(i, j) = 0.;

  for (i = 0; i < mData.dim; i++)
    mI(i, i) = 1.;

  /*  CSP Output  */

  C_INT32 reacs_size = mpModel->getReactions().size();

  mAmplitude.resize(mData.dim);
  mRadicalPointer.resize(mData.dim, mData.dim);
  mParticipationIndex.resize(reacs_size, mData.dim);
  mImportanceIndex.resize(reacs_size, mData.dim);
  mFastReactionPointer.resize(reacs_size, mData.dim);

  mSetVectors = 0;

  //std::ofstream os;
  //os.open("CSPValues.dat", std::ios::out);

  return;
}

/* compute  CSP radical pointer and fast reaction pointer */
void CCSPMethod::CSPradicalPointer(C_INT & N, C_INT & M, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{

  C_INT i, j, m, r;
  C_INT32 reacs_size = mpModel->getReactions().size();
  const CCopasiVector< CReaction > & reacs = mpModel->getReactions();
  const CMatrix< C_FLOAT64 > & redStoi = mpModel->getRedStoi();
  //C_INT  size = mpModel->getRedStoi().size();

#if 0
  std::cout << "Stoichiometric matrix (iIndependent, jReaction) : " << std::endl;
  std::cout << redStoi << std::endl;
#endif

  CMatrix<C_FLOAT64> A0;
  CMatrix<C_FLOAT64> B0;
  CMatrix<C_FLOAT64> TMP;

  A0.resize(N, reacs_size);
  B0.resize(reacs_size, N);
  TMP.resize(N, reacs_size);

  A0 = 0;
  B0 = 0;

  C_FLOAT64 tmp;

  for (r = 0; r < reacs_size; r++)
    {
      tmp = 0;

      for (i = 0; i < N; i++)
        {
          A0(i, r) = redStoi(i, r);
          tmp += A0(i, r) * A0(i, r);
        }

      for (i = 0; i < N; i++)
        B0(r, i) = A0(i, r) / tmp;
    }

#if 0
  std::cout << " Inverse(redStoi) " << std::endl;
  std::cout << B0 << std::endl;
#endif

  /*  m-th fast mode projection matrix */

  CMatrix<C_FLOAT64> QM;
  QM.resize(N, N);

  QM = 0.;

  for (m = 0; m < M ; m++)
    {

      CMatrix<C_FLOAT64> Qm;
      Qm.resize(N, N);

      for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
          {
            Qm(i, j) = A(i, m) * B(m, j);
          }

#if 0
      std::cout << "CSP iteration: the " << m << "-th fast mode projection matrix  " << std::endl;
      std::cout << Qm << std::endl;
#endif

      /**
       * some comments on the Qm matrix: Qm(i,i) , i = 0,1,...,N,
       * is a mesure of projection of i-th unit vector in the m-th mode,
       * whenever Qm(i,i) is not a small number, species m is said to be a CSP radical
       **/

      C_FLOAT64 tmp = 0.;

#if 0
      std::cout << "the diagonal elements of " << m << "-th fast mode projection matrix  " << std::endl;
#endif
      for (i = 0; i < N ; i++)
        {
          mRadicalPointer(i, m) = Qm(i, i);

          tmp += Qm(i, i);
#if 0
          std::cout << mpModel->getMetabolitesX()[i]->getObjectName() << " corresponding  Qm(i,i) " << Qm(i, i) << std::endl;
#endif
        }

#if 0
      std::cout << "the sum of the diagonal elements of " << m << "-th fast mode projection matrix  " << std::endl;
      std::cout << tmp << std::endl;
#endif

      /* use stoichiometric vectors to build the fast reaction pointer */

#if 0
      std::cout << "Fast reaction pointer " << std::endl;
#endif

      /**
       * Pmr  is a mesure of projection of r-th stoichiometric vector in the m-th mode,
       * whenever Pmr is not a small number, the r-th reaction is said to be a fast reaction
       **/

#if 0
      std::cout << m << "-th mode:" << std::endl;
#endif

      for (r = 0; r < reacs_size; r++)
        {
          C_FLOAT64 Pmr = 0.;

          for (i = 0; i < N; i++)
            {
              TMP(i, r) = 0.;
              for (j = 0; j < N; j++)
                TMP(i, r) += Qm(i, j) * A0(j, r);
            }

          for (j = 0; j < N; j++)
            Pmr += B0(r, j) * TMP(j, r);

          mFastReactionPointer(r, m) = Pmr;

#if 0
          std::cout << "reaction " << reacs[r]->getObjectName() << " :" << Pmr << std::endl;
#endif
        }
    }
  return;
}

/**
 * compute  CSP Participation Index:
 * a mesure of participation of the r-th elementary reaction to the balansing act of the i-th mode
 * It is assumed that forward and reverse reactions are counted as distinct
 **/
void CCSPMethod::CSPParticipationIndex(C_INT & N, C_FLOAT64 & tauM1, CMatrix< C_FLOAT64 > & B0)
{

  C_INT i, r, j;
  C_INT32 reacs_size = mpModel->getReactions().size();
  const CCopasiVector< CReaction > & reacs = mpModel->getReactions();
  const CMatrix< C_FLOAT64 > & redStoi = mpModel->getRedStoi();

#if 0
  std::cout << "Participation Index: " << std::endl;
#endif

  CVector<C_FLOAT64> flux;
  flux.resize(reacs_size);

  CMatrix<C_FLOAT64> P;
  P.resize(N, reacs_size);

  CVector<C_FLOAT64> estim;
  estim.resize(N);

  CVector<C_FLOAT64> ampl;
  ampl.resize(N);

  for (r = 0; r < reacs_size; ++r)
    flux[r] = reacs[r]->calculateFlux();

  for (i = 0; i < N; ++i)
    {
      ampl[i] = 0;

      for (r = 0; r < reacs_size; ++r)
        {

          P(i, r) = 0;

          for (j = 0; j < N; ++j)
            P(i, r) += B0(i, j) * redStoi(j, r);

          ampl[i] += fabs(P(i, r) * flux[r]);
        }

      C_FLOAT64 tmp;

      for (j = 0; j < N; ++j)
        tmp += B0(i, j) * mYerror[j];

      estim[i] = fabs(tmp / tauM1);
    }

  for (i = 0; i < N; ++i)
    {

#if 0
      std::cout << " mode " << i << " : " << std::endl;
#endif

      for (r = 0; r < reacs_size; ++r)
        {
          P(i, r) *= flux[r] / (ampl[i] + estim[i]);

          mParticipationIndex(r, i) = P(i, r);
#if 0
          std::cout << " reaction " << reacs[r]->getObjectName() << " index : " << P(i, r) << std::endl;
#endif
        }
    }

  return;
}

/**
 * compute CSP Importance Index :
 * a mesure of relative importance  of the contribution of r-th elementaey reaction
 * to the current reaction rate of the i-th spiecies
 **/

void CCSPMethod::CSPImportanceIndex(C_INT & N, C_FLOAT64 & tauM1, CMatrix< C_FLOAT64 > & Q)
{

  C_INT i, r;
  C_INT32 reacs_size = mpModel->getReactions().size();
  const CCopasiVector< CReaction > & reacs = mpModel->getReactions();
  const CMatrix< C_FLOAT64 > & redStoi = mpModel->getRedStoi();

#if 0
  std::cout << "Importance Index: " << std::endl;
#endif

  CVector<C_FLOAT64> flux;
  flux.resize(reacs_size);

  CMatrix<C_FLOAT64> S0;
  S0.resize(N, reacs_size);

  CMatrix<C_FLOAT64> S;
  S.resize(N, reacs_size);

  CMatrix<C_FLOAT64> I;
  I.resize(N, reacs_size);

  CVector<C_FLOAT64> estim;
  estim.resize(N);

  CVector<C_FLOAT64> g;
  g.resize(N);

#if 0
  std::cout << "slow subspace projection matrix  " << std::endl;
  std::cout << Q << std::endl;
#endif

  S = redStoi;

  smmult(Q, S, S0, N, N, reacs_size);

  for (r = 0; r < reacs_size; ++r)
    flux[r] = reacs[r]->calculateFlux();

  for (i = 0; i < N; ++i)
    {
      g[i] = 0;

      for (r = 0; r < reacs_size; ++r)
        g[i] += fabs(S0(i, r) * flux[r]);

      estim[i] = fabs(mYerror[i] / tauM1);
    }

  for (i = 0; i < N; ++i)
    {

#if 0
      std::cout << "current reaction rate of " << mpModel->getMetabolitesX()[i]->getObjectName() << " : " << std::endl;
#endif

      for (r = 0; r < reacs_size; ++r)
        {
          I(i, r) = S0(i, r) * flux[r] / (g[i] + estim[i]);

          mImportanceIndex(r, i) = I(i, r);

#if 0
          std::cout << " contribution of the reaction " << reacs[r]->getObjectName() << "  : " << I(i, r) << std::endl;
#endif
        }
    }

  return;
}

/* compute  amplitudes of fast and slow modes */
void CCSPMethod::modesAmplitude(C_INT & N, C_INT & M, CVector< C_FLOAT64 > & g, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & F)
{

  C_INT i, j;

#if 0
  std::cout << " amplitude of  fast and slow  modes : " << std::endl;
  std::cout << "B" << std::endl;
  std::cout << B << std::endl;
  std::cout << "g" << std::endl;
  for (i = 0; i < N; i++)
    std::cout << g[i] << std::endl;
#endif

  F = 0;

  for (i = 0; i < N; i++)
    {
      F(i, 0) = 0.;
      for (j = 0; j < N; j++)
        {
          F(i, 0) += B(i, j) * g[j];
        }

      mAmplitude[i] = F(i, 0);

#if 0
      std::cout << " mode  " << i << "      F :  " << F(i, 0) << std::endl;
#endif
    }

  return;
}

/* correct for the contribution of the fast time-scales  to y  */
void CCSPMethod::yCorrection(C_INT & N, C_INT & M, CVector< C_FLOAT64 > & y, CMatrix< C_FLOAT64 > & TAUM, CMatrix< C_FLOAT64 > & F, CMatrix< C_FLOAT64 > & A)
{
  CMatrix<C_FLOAT64> TMP;
  CVector<C_FLOAT64> dy;

  TMP.resize(N, M);
  dy.resize(N);

  C_INT i, k;

  /* A*TAU*F  */

  smmult(A, TAUM, TMP, N, M, M);

#if 0
  std::cout << std::endl;
  std::cout << "Radical correction :" << std::endl;
  std::cout << "A" << std::endl;
  std::cout << A << std::endl;
  std::cout << "TAU" << std::endl;
  std::cout << TAUM << std::endl;
  std::cout << "TMP" << std::endl;
  std::cout << TMP << std::endl;
  std::cout << "dy" << std::endl;
#endif

  for (i = 0; i < N ; i++) dy[i] = 0.;

  for (i = 0; i < N ; i++)
    for (k = 0; k < M; k++)
      dy[i] += TMP(i, k) * F(k, 0);

  /* contribution of  fast time-scales */

  for (i = 0; i < N; i++)
    {
      y[i] -= dy[i];
#if 0
      std::cout << dy[i] << std::endl;
#endif
    }
  return;
}

/* Refinement Procedre :
 * Lamm, Combustion Science and Technoligy, 1993.
 **/
void CCSPMethod::basisRefinement(C_INT & N, C_INT & M, CMatrix< C_FLOAT64 > & ALA, CMatrix< C_FLOAT64 > & TAU, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & A0, CMatrix< C_FLOAT64 > & B0)
{

  C_INT i, j, n, m;

  CMatrix<C_FLOAT64> P;
  CMatrix<C_FLOAT64> Q;

  P.resize(N, N);
  Q.resize(N, N);

  P = 0.;
  Q = 0.;

  for (m = 0; m < M; m++)
    for (j = M; j < N; j++)
      {
        // std::cout << " m " << m << " j " << j << std::endl;
        for (n = 0; n < M; n++)
          P(m, j) += TAU(m, n) * ALA(n, j);
      }

  for (j = M ; j < N; j++)
    for (m = 0; m < M; m++)
      {
        //std::cout << " j " << j << " m " << m << std::endl;
        for (n = 0; n < M; n++)
          Q(j, m) += ALA(j, n) * TAU(n, m);
      }

#if 0
  std::cout << "P" << std::endl;
  std::cout << P << std::endl;
  std::cout << "Q" << std::endl;
  std::cout << Q << std::endl;
#endif

  A0 = A;
  B0 = B;

  /* step #1 */

  for (m = 0; m < M; m++)
    for (i = 0; i < N; i++)
      for (j = M ; j < N; j++)
        B0(m, i) += P(m, j) * B(j, i);

  for (i = 0; i < N; i++)
    for (j = M ; j < N; j++)
      for (n = 0; n < M ; n++)
        A0(i, j) -= A(i, n) * P(n, j);

#if 0
  std::cout << "refinement step1" << std::endl;
  std::cout << "B0" << std::endl;
  std::cout << B0 << std::endl;
  std::cout << "A0" << std::endl;
  std::cout << A0 << std::endl;
#endif
  /* step #2  */

  A = A0;
  B = B0;

  for (i = M; i < N; i++)
    for (j = 0; j < N; j++)
      for (n = 0; n < M; n++)
        B0(i, j) -= Q(i, n) * B(n, j);

  for (i = 0; i < N; i++)
    for (m = 0; m < M; m++)
      for (j = M; j < N; j++)
        A0(i, m) += A(i, j) * Q(j, m);

#if 0
  std::cout << "after refinement :" << std::endl;
  std::cout << "A0" << std::endl;
  std::cout << A0 << std::endl;
  std::cout << "B0" << std::endl;
  std::cout << B0 << std::endl;
#endif

  smnorm(N, A0, B0, N);

  return;
}

/* evaluate jacobian for the current y */
void CCSPMethod::calculateJacobianX(C_INT & N, CVector<C_FLOAT64> & y, CMatrix <C_FLOAT64> & J)
{
  C_INT i;

  CVector<C_FLOAT64> tmp;
  tmp.resize(N);

  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor() / mpModel->getCompartments()[0]->getInitialValue();

  for (i = 0; i < N; i++)
    tmp[i] = y[i] / number2conc;

  /* write new concentrations in the current state */
  for (i = 0; i < N; i++)
    mpModel->getMetabolitesX()[i]->setValue(tmp[i]);
  //mpModel->getMetabolitesX()[i]->setConcentration(y[i]);

  mpModel->updateSimulatedValues(mReducedModel);
  mpModel->calculateJacobianX(J, 1e-6, 1e-12);

  /* write back concentrations of the current state*/
  for (i = 0; i < N; i++)
    mpModel->getMetabolitesX()[i]->setValue(mY[i]);

  mpModel->updateSimulatedValues(mReducedModel);

  return;
}

/* enforce the criterion to classify */
void CCSPMethod::classifyModes(C_INT & N, C_INT & M, C_INT & exhausted, C_FLOAT64 & tauM, C_FLOAT64 & tauM1 , CVector< C_FLOAT64 > & g, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & F)
{
  C_FLOAT64 number2conc = mpModel->getNumber2QuantityFactor() / mpModel->getCompartments()[0]->getInitialValue();
  CMatrix<C_FLOAT64> Q;

  Q.resize(N, 1);

  C_INT i, j;

#if 0
  std::cout << "classify Modes: amplitude " << std::endl;
  std::cout << "B" << std::endl;
  std::cout << B << std::endl;
  std::cout << "g" << std::endl;
  for (i = 0; i < N; i++)
    std::cout << g[i] << std::endl;
#endif

  F = 0;

  /* evaluate amplitudes */
  for (i = 0; i < N; i++)
    {
      F(i, 0) = 0.;
      for (j = 0; j < N; j++)
        {
          F(i, 0) += B(i, j) * g[j];
        }

#if 0
      std::cout << "F " << i << " = " << F(i, 0) << std::endl;
#endif
    }

#if 0
  std::cout << "classify Modes:  " << std::endl;
  // std::cout << "A" << std::endl;
  // std::cout << A << std::endl;
  std::cout << "F" << std::endl;
  for (i = 0; i < N; i++)
    std::cout << F(i, 0) << std::endl;
#endif

  exhausted = M;

#if 0
  std::cout << "fast modes : " << std::endl;
#endif
  for (j = 0; j < M; ++j)
    {
      C_FLOAT64 tmp, test;

      tmp = fabs(F(j, 0) * tauM);

#if 0
      std::cout << "mode " << j << " : " << std::endl;
      std::cout << "F " << F(j, 0) << std::endl;
      std::cout << "F * tau = " << tmp << std::endl;
#endif

      for (i = 0; i < N; ++i)
        {
          test = tmp * fabs(A(i, j));

#if 0
          std::cout << "component " << i << " test " << test << " mYerror[i] " << mYerror[i] << " mY[i] " << mY[i]*number2conc << std::endl;
#endif
        }

      for (i = 0; i < N; ++i)
        {
          tmp *= fabs(A(i, j));

          if (tmp >= mYerror[i])
            {
              exhausted --;
#if 0
              std::cout << "mode " << j << " is an active mode" << std::endl;
#endif
              break;
            }
        }

#if 0

      C_FLOAT64 tmp1 = 0;
      for (i = 0; i < N; ++i)
        tmp1 += B(j, i) * mYerror[i];

      tmp1 /= tauM;

      std::cout << "F " << F(j, 0) << " estimate " << fabs(tmp1) << std::endl;
#endif
    }

#if 0
  std::cout << "slow modes : " << std::endl;
#endif
  for (j = M; j < N; ++j)
    {
      C_FLOAT64 tmp, test;

      tmp = fabs(F(j, 0) * tauM1);

#if 0
      std::cout << "mode " << j << " : " << std::endl;
      std::cout << "F " << F(j, 0) << std::endl;
      std::cout << "F * tau = " << tmp << std::endl;
#endif

      for (i = 0; i < N; ++i)
        {
          test = tmp * fabs(A(i, j));

#if 0
          std::cout << "component " << i << " test " << test << " mYerror[i] " << mYerror[i] << " mY[i] " << mY[i]*number2conc << std::endl;
#endif
        }

      for (i = 0; i < N; ++i)
        {
          tmp *= fabs(A(i, j));

          if (tmp >= mYerror[i])
            {
#if 0
              std::cout << "mode " << j << " is an active mode" << std::endl;
#endif
              break;
            }
        }
    }

  return;
}

/**
 * Create the CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget.
 * Input for each CArraAnnotations is a seperate CMatrix.
 **/
void CCSPMethod::createAnnotationsM()
{
  CArrayAnnotation *
  pTmp1 = new CArrayAnnotation("Amplitude", this,
                               new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mAmplitudeTab), true);
  pTmp1->setMode(0, pTmp1->STRINGS);
  pTmp1->setMode(1, pTmp1->STRINGS);
  pTmp1->setDescription("Amplitude Table");
  pTmp1->setDimensionDescription(0, "Amplitude");
  pTmp1->setDimensionDescription(1, "Reaction Mode");
  pAmplitudeAnn = pTmp1;

  CArrayAnnotation *
  pTmp2 = new CArrayAnnotation("Radical Pointer", this,
                               new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mRadicalPointerTab), true);
  pTmp2->setMode(0, pTmp2->VECTOR);
  pTmp2->setMode(1, pTmp2->STRINGS);
  pTmp2->setDescription("Radical Pointer Table");
  pTmp2->setDimensionDescription(0, "metabolites");
  pTmp2->setDimensionDescription(1, "Radical Pointer");
  pRadicalPointerAnn = pTmp2;

  CArrayAnnotation *
  pTmp3 = new CArrayAnnotation("Fast Reaction Pointer", this,
                               new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mFastReactionPointerTab), true);
  pTmp3->setMode(0, pTmp3->VECTOR);
  pTmp3->setMode(1, pTmp3->STRINGS);
  pTmp3->setDescription("Fast Reaction Pointer Table");
  pTmp3->setDimensionDescription(0, "Reactions");
  pTmp3->setDimensionDescription(1, "Fast Reaction Pointer");
  pFastReactionPointerAnn = pTmp3;

  CArrayAnnotation *
  pTmp4 = new CArrayAnnotation("Participation Index", this,
                               new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mParticipationIndexTab), true);
  pTmp4->setMode(1, pTmp4->STRINGS);
  pTmp4->setMode(0, pTmp4->VECTOR);
  pTmp4->setDescription("Participation Index Table");
  pTmp4->setDimensionDescription(0, "Reactions");
  pTmp4->setDimensionDescription(1, "Reaction Mode");
  pParticipationIndexAnn = pTmp4;

  CArrayAnnotation *
  pTmp5 = new CArrayAnnotation("Importance Index", this,
                               new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mImportanceIndexTab), true);
  pTmp5->setMode(1, pTmp5->VECTOR);
  pTmp5->setMode(0, pTmp5->VECTOR);
  pTmp5->setDescription("Importance Index Table");
  pTmp5->setDimensionDescription(0, "Reactions");
  pTmp5->setDimensionDescription(1, "Metabolites");
  pImportanceIndexAnn = pTmp5;
}
/**
 * Set the every CArrayAnnotation for the requested step.
 * Set also the desription of CArayAnnotation for both dimensions:
 *    - dimension description could consists of some std::srings
 *      some strings contain the Time Scale values for requested step
 *    - dimension description could consists of arrays of CommonNames
 **/
void CCSPMethod::setAnnotationM(int step)
{
  double timeScale;
  std::string str;
  std::stringstream sstr;
  sstr.str("");
  sstr.clear();
  int i, j;

  if (!step) return;
  step -= 1;

  // fill pAmplitudeAnn

  mAmplitudeTab.resize(mVec_mAmplitude[step].numRows(), 1);
  for (i = 0; i < mVec_mAmplitude[step].numRows(); i++)
    mAmplitudeTab(i, 0) = mVec_mAmplitude[step][i][0];
  pAmplitudeAnn->resize();
  for (i = 0; i < mVec_mAmplitude[step].numRows(); i++)
    {
      sstr << i + 1;
      str = sstr.str();
      pAmplitudeAnn->setAnnotationString(0, i, str);
      sstr.str("");
      sstr.clear();
    }
  sstr.str("");
  str = sstr.str();
  pAmplitudeAnn->setAnnotationString(1, 0, str);

  // fill pRadicalPointerAnn
  mRadicalPointerTab.resize(mVec_mRadicalPointer[step].numCols(),
                            mVec_mRadicalPointer[step].numRows());
  mRadicalPointerTab = mVec_mRadicalPointer[step];
  pRadicalPointerAnn->resize();
  pRadicalPointerAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  for (i = 0; i < mVec_mRadicalPointer[step].numCols(); i++)
    {
      sstr << "mode ";
      sstr << i;
      str = sstr.str();
      pRadicalPointerAnn->setAnnotationString(1, i, str);
      sstr.str("");
      sstr.clear();
    }

  // fill pFastReactionPointerAnn
  mFastReactionPointerTab.resize(mVec_mFastReactionPointer[step].numCols(),
                                 mVec_mFastReactionPointer[step].numRows());
  mFastReactionPointerTab = mVec_mFastReactionPointer[step];
  pFastReactionPointerAnn->resize();
  for (i = 0; i < mVec_mFastReactionPointer[step].numCols(); i++)
    {
      sstr << "mode ";
      sstr << i;
      str = sstr.str();
      pFastReactionPointerAnn->setAnnotationString(1, i, str);
      sstr.str("");
      sstr.clear();
    }
  pFastReactionPointerAnn->setCopasiVector(0, &mpModel->getReactions());

  // fill pParticipationIndexAnn
  mParticipationIndexTab.resize(mVec_mParticipationIndex[step].numCols(),
                                mVec_mParticipationIndex[step].numRows());
  mParticipationIndexTab = mVec_mParticipationIndex[step];
  pParticipationIndexAnn->resize();
  for (i = 0; i < mVec_mParticipationIndex[step].numCols(); i++)
    {
      sstr << "mode ";
      sstr << i;
      str = sstr.str();
      pParticipationIndexAnn->setAnnotationString(1, i, str);
      sstr.str("");
      sstr.clear();
    }
  pParticipationIndexAnn->setCopasiVector(0, &mpModel->getReactions());

  // fill pmImportanceIndexAnn
  mImportanceIndexTab.resize(mVec_mImportanceIndex[step].numCols(),
                             mVec_mImportanceIndex[step].numRows());
  mImportanceIndexTab = mVec_mImportanceIndex[step];
  pParticipationIndexAnn->resize();
  pImportanceIndexAnn->setCopasiVector(0, &mpModel->getReactions());
  pImportanceIndexAnn->setCopasiVector(1, &mpModel->getMetabolitesX());
}

/**
 *upgrade all vectors with values from actually calculalion for current step
 **/
void CCSPMethod::setVectors()
{

  mVec_mAmplitude.push_back(mCurrentStep);
  mVec_mAmplitude[mCurrentStep].resize(mAmplitude.size(), 1);
  C_INT i;

  for (i = 0; i < mAmplitude.size();i++)
    mVec_mAmplitude[mCurrentStep][i][0] = mAmplitude[i];

#if 0
  std::cout << "mCurrentStep " << mCurrentStep << std::endl;
  for (i = 0; i < mAmplitude.size(); i++)
    {
      std::cout << " test mode  " << i << "  : " << mAmplitude[i];
      std::cout << "  mVec_mAmplitude[mCurrentStep][i][0]  " << i << "  : " << mVec_mAmplitude[mCurrentStep][i][0];

      std::cout << std::endl;
    }
#endif

  mVec_mRadicalPointer.push_back(mCurrentStep);
  mVec_mRadicalPointer[mCurrentStep].resize(mRadicalPointer.numCols(), mRadicalPointer.numRows());
  mVec_mRadicalPointer[mCurrentStep] = mRadicalPointer;

  mVec_mFastReactionPointer.push_back(mCurrentStep);
  mVec_mFastReactionPointer[mCurrentStep].resize(mFastReactionPointer.numCols(), mFastReactionPointer.numRows());
  mVec_mFastReactionPointer[mCurrentStep] = mFastReactionPointer;

  mVec_mParticipationIndex.push_back(mCurrentStep);
  mVec_mParticipationIndex[mCurrentStep].resize(mParticipationIndex.numCols(), mParticipationIndex.numRows());
  mVec_mParticipationIndex[mCurrentStep] = mParticipationIndex;

  mVec_mImportanceIndex.push_back(mCurrentStep);
  mVec_mImportanceIndex[mCurrentStep].resize(mImportanceIndex.numCols(), mImportanceIndex.numRows());
  mVec_mImportanceIndex[mCurrentStep] = mImportanceIndex;

  mCurrentTime.push_back(mCurrentStep);
  mCurrentTime[mCurrentStep] = mTime;
}

/**
 * Empty every vector to be able to fill them with new values for a new calculation.
 * Also nullify the step counter.
 **/
void CCSPMethod::emptyVectors()
{
  mCurrentStep = 0;
  mVec_mAmplitude.erase(mVec_mAmplitude.begin(), mVec_mAmplitude.end());
  mVec_mRadicalPointer.erase(mVec_mRadicalPointer.begin(), mVec_mRadicalPointer.end());
  mVec_mFastReactionPointer.erase(mVec_mFastReactionPointer.begin(), mVec_mFastReactionPointer.end());
  mVec_mParticipationIndex.erase(mVec_mParticipationIndex.begin(), mVec_mParticipationIndex.end());
  mVec_mImportanceIndex.erase(mVec_mImportanceIndex.begin(), mVec_mImportanceIndex.end());
}
