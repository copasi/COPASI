// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CCSPMethod.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2008/03/04 16:54:18 $
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
  initializeIntegrationsParameter();
  
  assertParameter("Ratio of Modes Separation", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Maximum Relative Error", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-15);
  assertParameter("Maximum Absolute Error", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0e-6);
  assertParameter("Use Stoichiometric Vectors", CCopasiParameter::BOOL, (bool) false);

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


/* find  the new number of dead modes  according to the time-scale separation ratio */
/*  TODO : equal eigenvalues are presenting !!! */
void CCSPMethod::findNewNumberOfDeadModes(C_INT & n, C_INT & m, C_INT & k, CVector< C_FLOAT64 > & tsc)
{

 /*
  * short the k smallest eigenvalues such that, if 
  * 
  * |eigen[1]| < |eigen[2]|< ... < |eigen[k]| , 
  *
  * then 
  *     tisc[i+1]/tisc[i] > mEps for i=1,k-1 
  * and 
  *     tisc[k+1]/tisc[k] < mEps  
  */

  C_INT i, max = n - m ;
  C_FLOAT64 tmp;

  k = 0;
  i = 0;

  for (i = 0; i < max - 1 ; i++)
    {
      if (tsc[i] != tsc[i + 1])
        {
          tmp = tsc[i+1] / tsc[i];
#ifdef CSP_DEBUG

          std::cout << "tsc[" << i + 1 << "]/tsc[" << i  << "] " << tmp << std::endl;
#endif

          if (tmp > mEps) k++; 
          else 	
		break;
	}
      else
        {
#ifdef CSP_DEBUG
          std::cout << "the following time scales are equal:  " << std::endl;
          std::cout << "tsc[" << i << "] = tsc[" << i + 1 << "]= " << tsc[i] << std::endl;
#endif
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

void CCSPMethod::cspstep(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B)
{
#ifdef CSP_DEBUG

#endif

   CVector<C_FLOAT64> g;
   CVector<C_FLOAT64> y;

   CMatrix<C_FLOAT64> J;

   g.resize(n);
   y.resize(n);
   J.resize(n, n);

    C_INT j;
  
  for (j = 0; j < n; j++)
    y[j] = mY[j];

   g = mG;
   J = mJacobian;

#ifdef CSP_DEBUG

std::cout << "step: current values " << std::endl;
std::cout << y << std::endl;
std::cout << "step: current right hand side " << std::endl;
std::cout << g << std::endl;
std::cout << "step:  current jacobian " << std::endl;
std::cout << J << std::endl;

#endif
 
   C_INT mold;

/* csp iterations */ 
cspiteration: 

   mold = m;

   if (m) 
   {
    /* correct for the contribution of the fast time-scales to y */

    yCorrection(n, m, y, g, J, A, B); // TODO;

    /* evaluate derivatives and jacobian for the current y */
   
   calculateDerivativesX(y.array(), g.array()); // TODO; 
   calculateJacobianX(n, y, J); // TODO; 

#ifdef CSP_DEBUG

std::cout << "CSP iteration: correct for the contribution of the fast time-scales" << std::endl;
std::cout << " values " << std::endl;
std::cout << y << std::endl;
std::cout << " right hand side " << std::endl;
std::cout << g << std::endl;
std::cout << " jacobian " << std::endl;
std::cout << J << std::endl;

#endif
   }

  CMatrix<C_FLOAT64> Q;
  CMatrix<C_FLOAT64> QSL;
  
  Q.resize(n, n);
  QSL.resize(n, n);

  /*  fast subspace projection matrix */
  smmult(A, B, Q, n, m, n);
  
  /* slow subspace projection matrix */
  smsubst(mI, Q, QSL, n, n);
  
#ifdef CSP_DEBUG

  std::cout << "CSP iteration:"<< std::endl;

  std::cout << "fast subspace projection matrix  " << std::endl;
  std::cout << Q << std::endl;
  std::cout << "slow subspace projection matrix  " << std::endl;
  std::cout << QSL << std::endl;

#endif

  /* projection of the current jacobian into the slow subspace  J*(I-A*B) */

  CMatrix<C_FLOAT64> JSL;
  JSL.resize(n, n);

  smmult(J, QSL, JSL, n, n, n);

  /* find eigenvalues of  JSL and initial basis vectors  */

  mJacobian_initial.resize(n, n);
  mQ.resize(n, n);
  mR.resize(n, n);
  
  mJacobian_initial = JSL;

  C_INT info;

  schur(info);

  CVector<C_FLOAT64> eigen;
  CVector<C_FLOAT64> tsc;

  eigen.resize(n);
  tsc.resize(n);

#ifdef CSP_DEBUG

  std::cout << "CSP iteration:  " << std::endl;
  std::cout << "schur matrix " << std::endl;
  std::cout << mR << std::endl;

  std::cout << "matrix of schur vectors " << std::endl;
  std::cout << mQ << std::endl;
#endif

  C_INT i;

  /* ordered real parts of eigen values */

  for (i = 0; i < n; i++)
    {
      eigen[i] = mR(n - 1 - i, n - 1 - i);

      tsc[i] = 1. / fabs(eigen[i]);
    }

#ifdef CSP_DEBUG
  std::cout << "CSP iteration:  " << std::endl;
  std::cout << "eigen values ordered by decreasing of absolute value of real part " << std::endl;
  for (i = 0; i < n; i++)
    std::cout << "eigen[" << i << "]  " << eigen[i] << std::endl;

  std::cout << "corresponding time scales  " << std::endl;
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
        A0(i, j) = mQ(i, n - 1 - j);
        B0(i, j) = 0;
      }

  smnorm(n, A0, B0, n);
  sminverse(n, n, A0, B0);

#ifdef CSP_DEBUG
  
  std::cout << "CSP iteration:  " << std::endl;

  std::cout << "columne basis vectors are the columne of A0" << std::endl;
  std::cout << A0 << std::endl;

  std::cout << "row basis vectors are the rows of B0" << std::endl;
  std::cout << B0 << std::endl;

#endif

  /* find a new number of dead modes  */

  C_INT k, mnew;
 
  k = 0;
 
  findNewNumberOfDeadModes(n, m, k, tsc);

  mnew = m+k;

#ifdef CSP_DEBUG

  std::cout << "CSP iteration:  " << std::endl;
  
  std::cout << "the new number of dead modes " << std::endl;
  std::cout << mnew << std::endl;

#endif

 CMatrix<C_FLOAT64> A0SL;
 CMatrix<C_FLOAT64> B0SL;
 CMatrix<C_FLOAT64> TMP;

 A0SL.resize(n, n);
 B0SL.resize(n, n);
 TMP.resize(n, n);

 smmult(B0, QSL, B0SL, k, n, n);

 for (i = 0; i < n; i++)
   for (j = 0; j < k; j++)
	B0(j, i) = B0SL(j, i);

  smmult(QSL, A0, A0SL, n, n, k);

  for (i = 0; i < n; i++)
    for (j = 0; j < k; j++)
        A0(i, j) = A0SL(i, j);

  smnorm(n, A0, B0, k);
  smmult( B0, A0, Q, k, n, k);
  sminverse(n, k, Q, TMP); // TODO : check the dimentions
  smmult( TMP, B0, Q, k, k, n);

  for (i = 0; i < n; i++)
    for (j = 0; j < k; j++)
    {
        A(i,m+j) = A0(i,j);
        B(m+j,i) = Q(j,i); // TODO : initial a,b  
    }

    m = mnew;


    
#ifdef CSP_DEBUG

      std::cout << "CSP iteration:  " << std::endl;
      std::cout << "resolution time  " << std::endl;
      std::cout << tsc[k] << std::endl;

#endif

	if (m >= n) 
	{
		
#ifdef CSP_DEBUG

      std::cout << "CSP iteration:  " << std::endl;
      std::cout << "m >= n" << std::endl;
      std::cout << "iterations are terminated with m = " << mold << std::endl;
      
      m = mold;

#endif
	   return; 
	}
  	/* refinement of row vector's b */

  	bRefinement(n, m, A, B, J, B); // TODO

  	/* enforce the criterion to declare exhausted modes*/

	C_INT tot = 0;

  	exhaustedFastModesDetection(n, m, tot, tsc[k], g, A, B); // TODO 

	if (tot != n) 
	{
		
#ifdef CSP_DEBUG

      std::cout << "CSP iteration:  " << std::endl;
      std::cout << "tot = n" << std::endl;
      std::cout << "iterations are terminated with m = " << mold << std::endl;
      
      m = mold;

#endif
	   return; 
	}

#ifdef CSP_DEBUG

        std::cout << "CSP iteration:  " << std::endl;
	std::cout << " number of exhausted fast modes : " << std::endl;
  	std::cout << tot << std::endl;

#endif
	/* refinement of column vector's a, TODO : esli nado  */
        aRefinement(n, m, A, B, J, A);

       goto cspiteration;

  return;
}

void CCSPMethod::step(const double & deltaT)
{

  C_INT n = mData.dim;
  C_INT m = 0;

  CMatrix<C_FLOAT64> A;
  CMatrix<C_FLOAT64> B;

  A.resize(n, n);
  B.resize(n, n);

 C_INT i,j;

 for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) 
    {
    	A(i,j) = 0;
	B(i,j) = 0;
    }

 mpModel->updateSimulatedValues(mReducedModel);

 for (j = 0; j < n; j++)
   {
   	mG[j] = 0.;
	mY[j] = mpModel->getMetabolitesX()[j]->getValue();
	mYerror[j] = mRerror * mY[j] + mAerror;
   }

   mpModel->calculateDerivativesX(mG.array());

   mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);
  
 
 cspstep(n, m, A, B);

  /* integrate one time step */

  integrationStep(deltaT);

  return;
}

void CCSPMethod::start(const CState * initialState)
{
   integrationMethodStart(initialState);
  
  /* CSP related staff */

  mG.resize(mData.dim);
  mYerror.resize(mData.dim);
  mEps = * getValue("Ratio of Modes Separation").pUDOUBLE;
  mRerror = * getValue("Maximum Relative Error").pUDOUBLE;
  mAerror = * getValue("Maximum Absolute Error").pUDOUBLE;

  mI.resize(mData.dim,mData.dim );
  
  C_INT i,j;

  for (i = 0; i <  mData.dim; i++)
    for (j = 0; j <  mData.dim; j++)
      mI(i, j) = 0.;

  for (i = 0; i <  mData.dim; i++)
    mI(i, i) = 1.;
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

  std::cout << "Correction procedure: current B " << std::endl;
  std::cout << B << std::endl;

  std::cout << "Correction procedure: current right hand side " << std::endl;
  std::cout << G << std::endl;

#endif
  /* F=B*G */

  C_INT k = 1;
  smmult(B, G, F, m, n, k);

#ifdef CSP_DEBUG

  std::cout << "Correction procedure: fast modes amplitudes " << std::endl;
  std::cout << F << std::endl;

#endif

  /* contribution of the fast time-scales */
  /* A*TAU*F */
  smmult(TMP, F, DY, n, m, k);

  for (i = 0; i < n; i++)
    y[i] -= DY(i, 0);

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

  mpModel->updateSimulatedValues(mReducedModel);
  mpModel->calculateJacobianX(J, 1e-6, 1e-12);

  /* write back concentrations of the current state*/
  for (i = 0; i < n; i++)
    mpModel->getMetabolitesX()[i]->setValue(tmp[i]);

  mpModel->updateSimulatedValues(mReducedModel);

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

/* enforce the criterion to declare a mode exhausted */
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

