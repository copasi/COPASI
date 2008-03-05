// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CILDMMethod.cpp,v $
//   $Revision: 1.17 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2008/03/05 11:04:14 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

#include "copasi.h"

#include "CILDMMethod.h"
#include "CTSSAProblem.h"

//#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CMetab.h"
//#include "model/CState.h"
//#include "utilities/CMatrix.h"
//#include "utilities/CAnnotatedMatrix.h"
//#include "report/CCopasiObjectReference.h"

#include "clapackwrap.h"        // CLAPACK
#include "blaswrap.h"           // BLAS

CILDMMethod::CILDMMethod(const CCopasiContainer * pParent):
    CTSSAMethod(CCopasiMethod::tssILDM, pParent) //,
    // mpState(NULL),
    // mY(NULL)
{
  //assert((void *) &mData == (void *) &mData.dim);

  // addObjectReference("Number of slow variables", mSlow, CCopasiObject::ValueInt);
  // addMatrixReference("Contribution of Metabolites to Slow Space", mVslow, CCopasiObject::ValueDbl);

  mData.pMethod = this;
  initializeParameter();
}

CILDMMethod::CILDMMethod(const CILDMMethod & src,
                         const CCopasiContainer * pParent):
    CTSSAMethod(src, pParent) //,
    //mpState(NULL),
    //mY(NULL)
{
  //assert((void *) &mData == (void *) &mData.dim);

  mData.pMethod = this;
  initializeParameter();
}

CILDMMethod::~CILDMMethod()
{
  pdelete(mpState);
}

void CILDMMethod::initializeParameter()
{
  addObjectReference("Number of slow variables", mSlow, CCopasiObject::ValueInt);
  addMatrixReference("Contribution of Metabolites to Slow Space", mVslow, CCopasiObject::ValueDbl);

  initializeIntegrationsParameter();

  createAnnotationsM();
  emptyVectors();
}

void CILDMMethod::step(const double & deltaT)
{

  C_INT dim = mData.dim;
  C_INT fast = 0;
  C_INT slow = dim - fast;

  C_INT i, j;

  mY_initial.resize(dim);
  mJacobian_initial.resize(dim, dim);
  mQ.resize(dim, dim);
  mR.resize(dim, dim);

  mTd.resize(dim, dim);
  mTdInverse.resize(dim, dim);
  mQz.resize(dim, dim);

  mTd_save.resize(dim, dim);

  //CMatrix<C_FLOAT64> TdInverse_save;
  mTdInverse_save.resize(dim, dim);

  mpModel->updateSimulatedValues(mReducedModel);
  // TO REMOVE : mpModel->applyAssignments();
  mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

  std::cout << std::endl;
  std::cout << "*****************************" << std::endl;
  std::cout << "Next step t=: " << mTime << std::endl;

  C_INT flag_jacob;
  flag_jacob = 1;  // Set flag_jacob=0 to printing Jacobian

  if (flag_jacob == 0)
    {
      std::cout << "Jacobian-initial:" << std::endl;
      std::cout << mJacobian << std::endl;
    }

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
    mY_initial[i] = mY[i];

  CVector<C_FLOAT64> Xconc_initial; //current state converted to concentrations
  Xconc_initial.resize(dim);
  for (i = 0; i < dim; ++i)
    Xconc_initial[i] = mY_initial[i] * number2conc;

  // save initial  Jacobian before next time step
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      mJacobian_initial(i, j) = mJacobian(i, j);

  // Next time step
  integrationStep(deltaT);

  mpModel->updateSimulatedValues(mReducedModel);
  // TO REMOVE : mpModel->applyAssignments();

  // Calculate Jacobian for time step control
  mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

  if (flag_jacob == 0)
    {
      std::cout << "Jacobian_next:" << std::endl;
      std::cout << mJacobian << std::endl;
    }

  //CMatrix<C_FLOAT64> mTd_save;
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      {
        mTd_save(i, j) = 0;
        mTdInverse_save(i, j) = 0;
      }

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      {
        mTd(i, j) = 0;
        mTdInverse(i, j) = 0;
      }

  /** Schur  Decomposition of Jacobian (reordered).
  Output:  mQ - transformation matrix mR - block upper triangular matrix (with ordered eigenvalues) */

  C_INT failed = 0;
  C_INT info_schur = 0;
  CMatrix<C_FLOAT64> orthog_prove;
  orthog_prove.resize(dim, dim);

  C_INT flag_orthog = 1;
  C_INT info;

  schur(info_schur); // TO DO : move the test to the TSSAMethod

  std::cout << "info_schur: " << info_schur << std::endl;

  if (info_schur)
    {
      std::cout << " There are problems with calculation of Jacobi matrix. Please check  the problem is specified suitable. " << std::endl;

      goto integration;
    }

  // Prove of orthogonality of mQ
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      {
        orthog_prove(i, j) = orthog(i, j);
      }

  if (flag_orthog == 0)
    std::cout << "Proof of  matrix Q:" << orthog_prove << std::endl;

  C_INT flag_schur;
  flag_schur = 1;

  if (flag_schur == 0)
    {
      std::cout << "Schur Decomposition" << std::endl;
      std::cout << "mR - block upper triangular matrix :" << std::endl;
      std::cout << mR << std::endl;
      std::cout << "mQ - transformation matrix" << std::endl;
      std::cout << mQ << std::endl;
    }

  /* If complex eigenvalues */
  //BUG 873
  if (mR(dim - 1, dim - 1) == mR(dim - 2 , dim - 2))
    {
      if (dim == 2)
        {
          slow = dim;
          goto integration;
        }
      else
        {
          //  fast = fast + 1;
          //  slow = dim - fast;
        }
    }

  // If positive eigenvalues

  if (mR(dim - 1, dim - 1) >= 0)
    {
      slow = dim;
      fast = 0;
      std::cout << "positive eigenvalues" << std::endl;
      failed = 1;
      goto integration;
    }

  // C_INT number, k;
  C_INT failed_while;

  /** Classical ILDM iterations. The number of slow variables is decreased until the Deuflhard criterium holds */
  /*  do START slow iterations */

  while (slow > 1)
    {

      fast = fast + 1;
      slow = dim - fast;

      if (fast < dim - 1)
        if (mR(slow, slow) == mR(slow - 1 , slow - 1))
          fast = fast + 1;

      slow = dim - fast;

      /** Solution of Sylvester equation for given slow, mQ,mR
      Output: mTd, mTdinverse and mQz (mQz is used later for newton iterations) */

      C_INT info = 0;

      failed_while = 0;

      sylvester (slow, info);

      if (info)
        {
          std::cout << "sylvester not work" << " slow = " << slow << std::endl;
          failed_while = 1;
          goto integration;
        }

      /* Check real parts of eigenvalues of Jacobian */

      for (i = slow ; i < dim; i++)
        if (mR(i , i) >= 0)
          {
            std::cout << "positive eigenvalues for i = " << i << std::endl;
            failed_while = 1;
            goto integration;
          }

      if (fast > 0)
        mEPS = 1 / fabs(mR(slow , slow));

      mCfast.resize(fast);

      /** Deuflhard Iteration:  Prove Deuflhard criteria, find consistent initial value for DAE
      output:  info - if Deuflhard is satisfied for this slow;
      transformation matrices mTd and mTdinverse */

      info = 0;

      C_INT help;
      help = 0;

      deuflhard(slow, info);
      help = help + 1;
      //std::cout << "Test_Deuflh   help=" << help << std::endl;

      failed_while = 0;

      if (info)
        {
          std::cout << "deuflhard not work" << " slow_deufl " << slow << std::endl;
          failed_while = 1;
          goto integration;
        }
    }
  /** end of iterations to find the number of slow modes */

integration:

  if ((failed == 1) || (failed_while == 1))
    {
      if (slow < dim)
        {
          fast = fast - 1;
          slow = dim - fast;
          if ((fast >= 1) && (mR(slow - 1, slow - 1) == mR(slow , slow)))
            fast = fast - 1;
          slow = dim - fast;
        }
    }

  mSlow = slow;

  std::cout << "slow " << mSlow << std::endl;
  std::cout << "fast " << fast << std::endl;
  std::cout << std::endl;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      {
        orthog_prove(i, j) = orthog(i, j);
      }

  if (flag_orthog == 0)
    std::cout << "Proof the orthogonality of  matrix mTdInverse:" << orthog_prove << std::endl;

  // Flag for print Tabs

  C_INT flag_tab;
  flag_tab = 1;    //change flag_tab=0 to print the Analysis Tabs  in the file

  mat_anal_mod(slow);
  mat_anal_metab(slow);
  mat_anal_mod_space(slow);
  mat_anal_fast_space(slow);

  if (flag_tab == 0)
    {
      for (i = 0 ; i < dim; i++)
        {
          std::cout << "Contribution to slow space:" << mpModel->getMetabolitesX()[i]->getObjectName() << "  " << mVslow_space[i] << std::endl;
        }
      std::cout << std::endl;

      for (i = 0 ; i < dim; i++)
        {
          std::cout << "Contribution to mode number " << i + 1 << ". Time scale: " << -(1 / mR(i, i)) << std::endl;
          for (j = 0; j < dim; j++)
            std::cout << mpModel->getMetabolitesX()[j]->getObjectName() << "  " << mVslow(i, j) << std::endl;
          std::cout << std::endl;
        }

      std::cout << std::endl;

      for (i = 0 ; i < dim; i++)
        {
          std::cout << "Metabolite: " << mpModel->getMetabolitesX()[i]->getObjectName() << std::endl;
          for (j = 0; j < dim; j++)
            std::cout << "Mode number" << j + 1 << ": " << mVslow_metab(i, j) << std::endl;
          std::cout << std::endl;
        }

      for (i = 0 ; i < dim; i++)
        std::cout << "Contribution to fast space:" << mpModel->getMetabolitesX()[i]->getObjectName() << "  " << mVfast_space[i] << std::endl;

      std::cout << std::endl;

      if (slow == dim)
        {
          std::cout << "No reduction is possible at this time point " << std::endl;
          std::cout << std::endl;
        }
    }

  C_INT flag_Td;

  flag_Td = 1;

  if (flag_Td == 0)
    {
      std::cout << "Transformation matrix mTd: " << std::endl;
      std::cout << mTd << std::endl;
      std::cout << std::endl;
      std::cout << "Inverse of transformation matrix: mTdInvesre: " << std::endl;
      std::cout << mTdInverse << std::endl;
      std::cout << std::endl;
    }

  transformation_norm(slow, info);

  mpModel->updateSimulatedValues(mReducedModel);
  // TO REMOVE : mpModel->applyAssignments();

  // Calculate Jacobian for time step control

  mpModel->calculateJacobianX(mJacobian, 1e-6, 1e-12);

  // new entry for every entry contains the current data of currently step
  setVectors(slow);

  // set the stepcounter
  mCurrentStep += 1;

  return;
}

/**
 Transformation norm story:
Prove the deviation of tranformation matrix
 */
void CILDMMethod::transformation_norm(C_INT & slow, C_INT & info)
{
  C_INT dim = mData.dim;

  C_INT i, j, k, fast;

  fast = dim - slow;

  CMatrix<C_FLOAT64> S_initial;
  S_initial.resize(dim, dim);

  CMatrix<C_FLOAT64> E_initial;
  E_initial.resize(dim, dim);

  // Matrix S_initial = mTdInverse * mJacobian_initial * mTd, where mJacobian_initial,
  // mTd and mTdInverse are calculated at time t

  for (i = 0; i < dim; i++)
    {
      for (j = 0; j < dim; j++)
        {
          E_initial(i, j) = 0.;
          for (k = 0; k < dim; k++)
            E_initial(i, j) = E_initial(i, j) + mJacobian_initial(i, k) * mTd(k, j);
        }
    }

  for (i = 0; i < dim; i++)
    {
      for (j = 0; j < dim; j++)
        {
          S_initial(i, j) = 0.;
          for (k = 0; k < dim; k++)
            S_initial(i, j) = S_initial(i, j) + mTdInverse(i, k) * E_initial(k, j);
        }
    }

  C_INT flag_norm;
  flag_norm = 1;

  if (flag_norm == 0)
    {
      std::cout << "S_initial " << std::endl;
      std::cout << S_initial << std::endl;
    }

  CMatrix<C_FLOAT64> S_new;
  S_new.resize(dim, dim);

  CMatrix<C_FLOAT64> E;
  E.resize(dim, dim);

  // Matrix S_new = mTdInverse * mJacobian * mTd, where mTd and mTdInverse are calculated
  // at time t; mJacobian at the next time point t = t + deltaT

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
          S_new(i, j) = 0.;
          for (k = 0; k < dim; k++)
            S_new(i, j) = S_new(i, j) + mTdInverse(i, k) * E(k, j);
        }
    }

  if (flag_norm == 0)
    {
      std::cout << " S_new: " << std::endl;
      std::cout << S_new << std::endl;
    }

  C_FLOAT64 tol;

  tol = 1e-2;

  CMatrix<C_FLOAT64> S11_new;
  S11_new.resize(slow, slow);

  for (i = 0; i < slow; i++)
    for (j = 0; j < slow; j++)
      S11_new(i, j) = S_new(i, j);

  CMatrix<C_FLOAT64> S12_new;
  S12_new.resize(slow, fast);

  for (i = 0; i < slow; i++)
    for (j = 0; j < fast; j++)
      S12_new(i, j) = S_new(i, j + slow);

  CMatrix<C_FLOAT64> S22_new;
  S22_new.resize(fast, fast);

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      S22_new(i, j) = S_new(i + slow, j + slow);

  CMatrix<C_FLOAT64> S21_new;
  S21_new.resize(fast, slow);

  for (i = 0; i < fast; i++)
    for (j = 0; j < slow; j++)
      S21_new(i, j) = S_new(i + slow, j);

  C_FLOAT64 norm_S11, norm_S12, norm_S22, norm_S21;

  norm_S11 = 0;
  norm_S21 = 0;
  norm_S22 = 0;
  norm_S12 = 0;

  for (i = 0; i < slow; i++)
    for (j = 0; j < slow; j++)
      norm_S11 = norm_S11 + (S11_new(i, j) * S11_new(i, j));

  norm_S11 = sqrt(norm_S11);

  for (i = 0; i < fast; i++)
    for (j = 0; j < slow; j++)
      norm_S21 = norm_S21 + (S21_new(i, j) * S21_new(i, j));

  norm_S21 = sqrt(norm_S21);

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      norm_S22 = norm_S22 + (S22_new(i, j) * S22_new(i, j));

  norm_S22 = sqrt(norm_S22);

  for (i = 0; i < slow; i++)
    for (j = 0; j < fast; j++)
      norm_S12 = norm_S12 + (S12_new(i, j) * S12_new(i, j));

  norm_S12 = sqrt(norm_S12);

  if (flag_norm == 0)
    {
      std::cout << "norm_S11: " << norm_S11 << std::endl;
      std::cout << "norm_S22: " << norm_S22 << std::endl;
      std::cout << "norm_S12: " << norm_S12 << std::endl;
      std::cout << "norm_S21: " << norm_S21 << std::endl;
    }

  info = 0;

  return;
}

/**
NEWTON: Looking for consistent initial value for DAE system
Output:  mCfast, info
 */

void CILDMMethod::newton(C_FLOAT64 *ys, C_INT & slow, C_INT & info)
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
  tol = 1e-6;
  err = 10.0;
  iter = 0;

  itermax = 150;
  iterations = 0;

  info = 0;

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      S_22(i, j) = mQz(i, j);

  for (i = 0; i < fast; i++)
    yf_newton[i] = mCfast[i];

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
          std::cout << "iter > itermax" << iter << std::endl;
          return;
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
        gf_newton[i] = -1. * g_newton[i + slow];

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
        d_yf[i] = gf_newton[i];

      err = -10.;
      for (i = 0; i < fast; i++)
        {
          gf_newton[i] = fabs(gf_newton[i]);
          if (err < gf_newton[i])
            err = gf_newton[i];
        }

      iterations = iterations + 1;

      /* stop criterion of newton method */

      C_FLOAT64 g1, g2;
      if (iter == 1)
        g1 = 3.0 * err;
      else
        g1 = g2;

      g2 = err;

      if (g2 / g1 > 1.0)
        {
          info = 1;
          std::cout << "info : stop criterion" << std::endl;
          break;
        }
    } /* end while */

  for (i = 0; i < fast; i++)
    mCfast[i] = yf_newton[i];

  return;
}

void CILDMMethod::start(const CState * initialState)
{

  integrationMethodStart(initialState);

  /* ILDM related staff  */

  mDtol = mpProblem->getDeufelhardTol(); 

  mVslow.resize(mData.dim, mData.dim);
  mVslow_metab.resize(mData.dim, mData.dim);
  mVslow_space.resize(mData.dim);
  mVfast_space.resize(mData.dim);
  
  return;
}

/**
  Deuflhard Iteration:  Prove Deuflhard criteria, find consistent initial value for DAE
  output:  info - if Deuflhard is satisfied for given slow; transformation matrices
  mTd and mTdinverse
 */
void CILDMMethod::deuflhard(C_INT & slow, C_INT & info)
{
  C_INT i, j;
  C_INT dim = mData.dim;
  C_INT fast = dim - slow;
  C_INT flag_deufl;

  flag_deufl = 1;

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

  //mY_initial.resize(dim);

  CVector<C_FLOAT64> Xconc; //current state converted to concentrations
  Xconc.resize(dim);
  for (i = 0; i < dim; ++i)
    Xconc[i] = mY_initial[i] * number2conc;

  for (i = 0; i < dim; i++)
    {
      c_full[i] = 0.0;
      for (j = 0; j < dim; j++)
        c_full[i] = c_full[i] + mTdInverse(i, j) * Xconc[j];
    }

  for (j = 0; j < slow; j++)
    c_slow[j] = c_full[j];

  for (j = 0; j < fast; j++)
    mCfast[j] = c_full[j + slow];

  CVector<C_FLOAT64> g_full;
  g_full.resize(dim);

  CVector<C_FLOAT64> g_slow;
  g_slow.resize(slow);

  CVector<C_FLOAT64> g_fast;
  g_fast.resize(fast);

  CVector<C_FLOAT64> dxdt;
  dxdt.resize(dim);

  // TO REMOVE: mpModel->applyAssignments();
  mpModel->updateSimulatedValues(mReducedModel);

  for (j = 0; j < dim; j++)
    dxdt[j] = 0.;

  CVector<C_FLOAT64> x_help;
  x_help.resize(dim);

  if (flag_deufl == 0)
    std::cout << "Prove from the DeuflhardFunction " << std::endl;

  for (j = 0; j < dim; j++)
    {
      x_help[j] = mY_initial[j] * number2conc;
    }

  // mpModel->calculateDerivativesX(dxdt.array());
  calculateDerivativesX(x_help.array(), dxdt.array());
  //convert dxdt to concentration units...
  //  for (i = 0; i < dim; ++i)
  //   dxdt[i] *= number2conc;

  for (i = 0; i < dim; i++)
    {
      g_full[i] = 0.0;
      for (j = 0; j < dim; j++)
        g_full[i] = g_full[i] + mTdInverse(i, j) * dxdt[j];
    }

  for (j = 0; j < slow; j++)
    g_slow[j] = g_full[j];

  info = 0;

  /**  NEWTON: Looking for consistent initial value for DAE system
  Output:  mCfast, info */
  newton(c_slow.array(), slow, info);

  if (info)
    {
      /* TODO */
      std::cout << "info: newton iteration stop" << std::endl;

      return;
    }

  /* calculation of g_relax at point x_relax (after relaxing yf to slow manifold)*/

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

  if (flag_deufl == 0)
    {
      std::cout << std::endl;
      for (i = 0; i < dim; i++)
        {
          std::cout << "x_help[" << i << "] = " << x_help[i] << std::endl;
          std::cout << "x_relax: " << x_relax[i] << std::endl;
        }
      std::cout << std::endl;
    }

  calculateDerivativesX(x_relax.array(), dxdt_relax.array());

  for (i = 0; i < dim; i++)
    {
      g_relax[i] = 0.0;
      for (j = 0; j < dim; j++)
        g_relax[i] = g_relax[i] + mTdInverse(i, j) * dxdt_relax[j];
    }

  if (flag_deufl == 0)
    {
      std::cout << std::endl;
      for (i = 0; i < dim; i++)
        {
          std::cout << "g_full[" << i << "] = " << g_full[i] << std::endl;
          std::cout << "g_relax[" << i << "] = " << g_relax[i] << std::endl;
        }
      std::cout << std::endl;
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

  if (max >= mDtol)
    info = 1;
  else
    info = 0;

  if (flag_deufl == 0)
    {
      std:: cout << "max from DeuflhardFunction: " << max << std::endl;
      std::cout << "end of DeuflhardFunction" << std::endl;
      std::cout << std::endl;
    }

  return;
}
