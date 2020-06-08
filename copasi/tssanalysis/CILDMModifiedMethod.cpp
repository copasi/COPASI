// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CILDMModifiedMethod.h"
#include "CTSSAProblem.h"
#include "CTSSATask.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/math/CMathContainer.h"

#include "copasi/lapack/lapackwrap.h"        // CLAPACK
#include "copasi/lapack/blaswrap.h"           // BLAS

CILDMModifiedMethod::CILDMModifiedMethod(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CTSSAMethod(pParent, methodType, taskType)
{
  initializeParameter();
}

CILDMModifiedMethod::CILDMModifiedMethod(const CILDMModifiedMethod & src,
    const CDataContainer * pParent):
  CTSSAMethod(src, pParent)
{
  initializeParameter();
}

CILDMModifiedMethod::~CILDMModifiedMethod()
{}

void CILDMModifiedMethod::initializeParameter()
{
  CTSSAMethod::initializeParameter();

  addObjectReference("Number of slow variables", mSlow, CDataObject::ValueInt);
  addMatrixReference("Contribution of Species to Slow Space", mVslow, CDataObject::ValueDbl);

  assertParameter("Deuflhard Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0e-4);

  createAnnotationsM();
  emptyVectors();
}

void CILDMModifiedMethod::start()
{
  CTSSAMethod::start();

  integrationMethodStart();

  /* ILDM related staff  */

  mDtol = getValue< C_FLOAT64 >("Deuflhard Tolerance");

  mVslow.resize(mDim, mDim);
  mVslow_metab.resize(mDim, mDim);
  mVslow_space.resize(mDim);
  mVfast_space.resize(mDim);

  emptyVectors();

  return;
}

void CILDMModifiedMethod::step(const double & deltaT)
{

  C_INT dim = mDim;
  C_INT fast = 0;
  C_INT slow = dim - fast;

  C_INT slow2, fast2;

  slow2 = dim;
  fast2 = dim - slow2;

  C_INT i, j;

  mY_initial.resize(dim);
  mJacobian_initial.resize(dim, dim);
  mQ.resize(dim, dim);
  mR.resize(dim, dim);
  mTd.resize(dim, dim);
  mTdInverse.resize(dim, dim);
  mQz.resize(dim, dim);

  mTd_save.resize(dim, dim);

  mTdInverse_save.resize(dim, dim);

  mpContainer->updateSimulatedValues(true);
  // TO REMOVE : Model.applyAssignments();
  mpContainer->calculateJacobian(mJacobian, 1e-6, true);

  C_INT flag_jacob;
  flag_jacob = 1;  // Set flag_jacob=0 to print Jacobian

  //this is an ugly hack that only makes sense if all metabs are in the same compartment
  //at the moment is is the only case the algorithm deals with

  CVector< C_FLOAT64 > Xconc(dim); //current state converted to concentrations
  C_FLOAT64 * pSpecies = mpFirstSpecies;
  C_FLOAT64 * pSpeciesEnd = mpFirstSpecies + mDim;
  C_FLOAT64 * pX = Xconc.array();

  for (; pSpecies != pSpeciesEnd; ++pSpecies, ++pX)
    {
      *pX = mNumber2Concentration **pSpecies;
    }

  memcpy(mY_initial.array(), mpFirstSpeciesRate, mDim * sizeof(C_FLOAT64));

  CVector<C_FLOAT64> Xconc_initial(dim); //current state converted to concentrations
  C_FLOAT64 * pRate = mY_initial.array();
  C_FLOAT64 * pRateEnd = pRate + mDim;
  pX = Xconc_initial.array();

  for (; pRate != pRateEnd; ++pRate, ++pX)
    {
      *pX = mNumber2Concentration **pRate;
    }

  mJacobian_initial = mJacobian;

  // Next time step
  integrationStep(deltaT);

  mpContainer->updateSimulatedValues(true);

  // Calculate Jacobian for time step control
  mpContainer->calculateJacobian(mJacobian, 1e-6, true);

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

  /* Schur  Decomposition of Jacobian (reordered).
  Output:  mQ - transformation matrix mR - block upper triangular matrix (with ordered eigenvalues) */

  C_INT failed = 0;
  C_INT info_schur = 0;

  C_INT number, k;
  C_INT failed_while = 0;

  C_INT flag_deufl;
  flag_deufl = 1;

  C_FLOAT64 max = 0.;

  //C_FLOAT64 max = 0;
  CVector<C_FLOAT64> re;
  CVector<C_FLOAT64> dxdt_relax;
  CVector<C_FLOAT64> x_relax;
  CVector<C_FLOAT64> x_help;
  CVector<C_FLOAT64> dxdt;

  CVector<C_FLOAT64> x_zero;

  CVector<C_FLOAT64> dxdt_zero;

  CVector<C_FLOAT64> dxdt_real;

  CVector<C_FLOAT64> help;

  CVector<C_INT> index;
  CVector<C_INT> index_temp;
  CMatrix<C_FLOAT64> orthog_prove;
  orthog_prove.resize(dim, dim);

  C_INT info;

  CVector<C_INT> index_metab;
  index_metab.resize(dim);

  /* Schur transformation of Jacobian */
  schur(info_schur);

  if (info_schur)
    {
      CCopasiMessage(CCopasiMessage::WARNING,
                     MCTSSAMethod + 9, *mpContainerStateTime - deltaT);

      goto integration;
    }

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      mTdInverse(i, j) = mQ(j, i);

  C_INT flag_schur;

  flag_schur = 1;  // set flag_schur = 0 to print Schur decomposition of jacobian (matrices mR and transformation mQ)

  mY_cons.resize(dim);  // consistent initial vector for DAE

  /* If complex eigenvalues */
  //BUG 873
  if (mR(dim - 1, dim - 1) == mR(dim - 2 , dim - 2))
    if (dim == 2)
      {
        slow = dim;
        goto integration;
      }

  // If positive eigenvalues

  if (mR(dim - 1, dim - 1) >= 0)
    {
      slow = dim;
      fast = 0;
      CCopasiMessage(CCopasiMessage::WARNING,
                     MCTSSAMethod + 10, *mpContainerStateTime - deltaT);

      failed = 1;
      goto integration;
    }

  // Iterations to determine the number of slow metabolites

  while ((slow2 > 1))
    {
      slow2 = slow2 - 1;
      fast2 = dim - slow2;

      if (mR(dim - fast2, dim - fast2) >= 0)
        {
          failed = 1;
          goto integration;
        }

      deuflhard_metab(slow2, info);

      if (info)
        {
          failed_while = 1;
          goto integration;
        }
    }

  //end of iterations to determine the number of slow metabolites

  /* end of the block %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */
  /*  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */

integration:

  slow = slow2;
  fast = fast2;

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

  if (slow == dim)
    CCopasiMessage(CCopasiMessage::WARNING,
                   MCTSSAMethod + 11, *mpContainerStateTime);

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      // mTdInverse(i,j) = mQ(i,j);
      mTd(i, j) = mQ(i, j);

  // Flag for print Tabs

  mat_anal_mod(slow);
  mat_anal_metab(slow);
  mat_anal_mod_space(slow);
  mat_anal_fast_space(slow);

  // This block proves which metabolite could be considered as QSS. In development
  /* Begin of the block %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */

  C_INT flag_dev;
  flag_dev = 1;

  if (flag_dev == 0)
    {
      C_INT temp;
      temp = dim - 1;

      // Mode Analysis to find the dominant metabolites in the modes
      mat_anal_mod(temp);

      //index_metab = -1, if there is no dominant metabolites in corresponding mode,
      //and is equal
      // to the number of dominant metabolite in opposite case
      // Dominant metabolite - its contribution to the mode is larger as 70%

      for (j = 0; j < dim; j++)
        index_metab[j] = -1;

      for (i = 0; i < dim ; i ++)
        for (j = 0; j < dim; j++)
          if (mVslow(dim - i - 1, j) > 70)
            index_metab[i] = j;

      C_FLOAT64 y_cons;

      info = 0;
      k = 0;
      number = index_metab[k];

      if (number > - 1)
        newton_for_timestep(number, y_cons, info);

      while (k < dim - 1)
        {
          if (number > -1)
            {
              dxdt.resize(dim);

              for (j = 0; j < dim; j++)
                dxdt[j] = 0.;

              //CVector<C_FLOAT64> x_help;
              x_help.resize(dim);

              for (j = 0; j < dim; j++)
                {
                  x_help[j] = mY_initial[j] * mNumber2Concentration;
                }

              calculateDerivatives(x_help.array(), dxdt.array(), true);
              info = 0;

              //NEWTON: Looking for consistent initial value for DAE system
              //Output:  y_cons, info

              newton_for_timestep(number, y_cons, info);

              if (info)
                {
                  // TODO info: newton iteration stop
                }

              if (info == 0)
                {
                  // CVector<C_FLOAT64> x_relax;
                  x_relax.resize(dim);

                  for (i = 0; i < dim; i ++)
                    if (i == number)
                      x_relax[i] = y_cons;
                    else
                      x_relax[i] = x_help[i];

                  //CVector<C_FLOAT64> dxdt_relax;
                  dxdt_relax.resize(dim);

                  calculateDerivatives(x_relax.array(), dxdt_relax.array(), true);

                  //CVector<C_FLOAT64> re;
                  re.resize(dim);

                  C_FLOAT64 eps;
                  eps = 1 / fabs(mR(dim - k - 1 , dim - k - 1));

                  // stop criterion for slow reaction modes

                  for (i = 0; i < dim; i++)
                    {
                      if (i == number)
                        re[i] = 0;
                      else
                        {
                          re[i] = fabs(dxdt_relax[i] - dxdt[i]);
                          re[i] = re[i] * eps;
                        }
                    }

                  //C_FLOAT64 max = 0.;
                  for (i = 0; i < dim; i++)
                    if (max < re[i])
                      max = re[i];

                  if (max >= mDtol)
                    info = 1;
                  else
                    info = 0;
                }
            }

          k = k + 1;
          number = index_metab[k];
          max = 0;
        }
    }

  /* end of the of block %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */
  /*  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */

  mpContainer->updateSimulatedValues(true);
  // TO REMOVE : Model.applyAssignments();

  // Calculate Jacobian for time step control

  mpContainer->calculateJacobian(mJacobian, 1e-6, true);

  // new entry for every entry contains the current data of currently step
  setVectors(slow);

  updateCurrentTime();

  // set the step counter
  mCurrentStep += 1;

  return;
}

/**
 EVALSORT for vector sorting
 */

void CILDMModifiedMethod::evalsort(C_FLOAT64 *reval, C_INT *index, const C_INT & dim)
{
  C_INT i, j, min, tmp_ind;
  C_FLOAT64 tmp1r;

  for (i = 0; i < dim - 1; i++)
    {
      min = i;

      for (j = i + 1; j < dim; j++)
        {
          if (reval[j] <= reval[min])
            min = j;
        }

      tmp1r = reval[min];
      tmp_ind = index[min];
      reval[min] = reval[i];
      index[min] = index[i];
      reval[i] = tmp1r;
      index[i] = tmp_ind;
    }

  return;
}

const CDataArray *CILDMModifiedMethod::getVslowPrintAnn() const
{return pVslowPrintAnn;}

const CDataArray *CILDMModifiedMethod::getVslowSpacePrintAnn() const
{return pVslowSpacePrintAnn;}

const CDataArray *CILDMModifiedMethod::getVfastSpacePrintAnn() const
{return pVfastSpacePrintAnn;}

const CDataArray *CILDMModifiedMethod::getVslowMetabPrintAnn() const
{return pVslowMetabPrintAnn;}

/*
  Deuflhard Iteration:  Prove Deuflhard criteria, find consistent initial value for DAE
  output:  info - if Deuflhard is satisfied
 */
void CILDMModifiedMethod::deuflhard_metab(C_INT & slow, C_INT & info)
{
  C_INT i, j, info_newton;
  C_INT dim = mDim;
  C_INT fast = dim - slow;

  C_INT flag_deufl;

  flag_deufl = 1;  // set flag_deufl=0  to print temporaly steps for this function

  C_FLOAT64 max = 0;
  CVector<C_FLOAT64> re;
  CVector<C_FLOAT64> dxdt_relax;
  CVector<C_FLOAT64> x_relax;
  CVector<C_FLOAT64> x_help;
  CVector<C_FLOAT64> dxdt;

  CVector<C_FLOAT64> help;
  help.resize(dim);
  CVector<C_INT> index;
  index.resize(dim);
  CVector<C_INT> index_temp;
  index_temp.resize(dim);

  C_FLOAT64 eps;
  eps = 1 / fabs(mR(dim - fast , dim - fast));
  //eps = fabs(mR(dim - fast - 1, dim - fast - 1)) / fabs(mR(dim - fast , dim - fast));

  mat_anal_fast_space(slow);

  for (i = 0; i < dim; i++)
    {
      index[i] = i;
      index_temp[i] = i;
    }

  for (i = 0; i < dim; i++)
    {
      help[i] = mVfast_space[i];
    }

  evalsort(help.array(), index.array(), dim);

  for (i = 0; i < dim; i++)
    index_temp[i] = index[i];

  for (i = 0; i < dim; i++)
    {
      index[i] = index_temp[dim - i - 1];
    }

  dxdt.resize(dim);

  for (j = 0; j < dim; j++)
    dxdt[j] = 0.;

  //CVector<C_FLOAT64> x_help;
  x_help.resize(dim);

  for (j = 0; j < dim; j++)
    {
      x_help[j] = mY_initial[j] * mNumber2Concentration;
    }

  // Model.calculateDerivativesX(dxdt.array());
  calculateDerivatives(x_help.array(), dxdt.array(), true);

  info_newton = 0;

  newton_new(index.array(), slow, info_newton);

  if (info_newton)
    {
      // TODO
      info = 1;
      return;
    }

  x_relax.resize(dim);

  for (i = 0; i < dim; i++)
    x_relax[i] = mY_cons[i];

  //CVector<C_FLOAT64> dxdt_relax;
  dxdt_relax.resize(dim);

  calculateDerivatives(x_relax.array(), dxdt_relax.array(), true);

  //CVector<C_FLOAT64> re;
  re.resize(dim);

  // stop criterion for slow reaction modes

  for (i = 0; i < dim; i++)
    {
      re[i] = fabs(dxdt_relax[i] - dxdt[i]);
      re[i] = re[i] * eps;

      for (j = 0; j < fast; j ++)
        if (i == index[j])
          re[i] = 0;
    }

  for (i = 0; i < dim; i++)
    if (max < re[i])
      max = re[i];

  if (max >= mDtol)
    info = 1;
  else
    info = 0;

  return;
}

void CILDMModifiedMethod::newton_new(C_INT *index_metab, C_INT & slow, C_INT & info)
{
  C_INT i, j, k, m, iter, iterations, itermax;
  C_INT nrhs, ok, fast, flag_newton;

  flag_newton = 1;  // set flag_newton=1  to print temporaly steps of newton iterations

  C_FLOAT64 tol, err;
  C_INT dim = mDim;

  fast = dim - slow;

  CVector<C_INT> ipiv;
  ipiv.resize(fast);

  CVector<C_FLOAT64> s_22_array;
  s_22_array.resize(fast * fast);

  CVector<C_FLOAT64> gf_newton;
  gf_newton.resize(fast);

  CVector<C_FLOAT64> d_yf;
  d_yf.resize(dim);

  CVector<C_FLOAT64> y_newton;
  y_newton.resize(dim);

  CVector<C_FLOAT64> yf_newton;
  yf_newton.resize(fast);

  CVector<C_FLOAT64> dydt_newton;
  dydt_newton.resize(dim);

  CVector<C_FLOAT64> g_newton;
  g_newton.resize(dim);

  CMatrix<C_FLOAT64> Jac_fast;
  Jac_fast.resize(fast, fast);

  C_FLOAT64 g1, g2 = 0.0;
  mY_cons.resize(dim);

  nrhs = 1;
  tol = 1e-6;
  err = 10.0;
  iter = 0;

  itermax = 150;
  iterations = 0;

  info = 0;

  for (i = 0; i < fast; i++)
    {
      m = index_metab[i];

      for (j = 0; j < fast; j++)
        {
          k = index_metab[ j];

          if ((m > -1) & (k > -1))
            Jac_fast(i, j) = mJacobian_initial(m, k);
          else
            {
              info = 3;
              return;
            }
        }
    }

  for (i = 0; i < dim; i++)
    y_newton[i] = mY_initial[i] * mNumber2Concentration;

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      s_22_array[j + fast * i] = Jac_fast(j, i);

  for (i = 0; i < dim; i++)
    d_yf[i] = 0.;

  while (err > tol)
    {
      iter ++;

      if (iter > itermax)
        {
          info = 1;
          return;
        }

      for (i = 0; i < dim; i++)
        y_newton[i] = y_newton[i] + d_yf[i];

      calculateDerivatives(y_newton.array(), dydt_newton.array(), true);

      for (i = 0; i < fast; i++)
        {
          j = index_metab[i];
          gf_newton[i] = -1. * dydt_newton[j];
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
          return;
        }

      for (i = 0; i < fast; i++)
        d_yf[i] = 0;

      for (j = 0; j < fast; j++)
        {
          k = index_metab[j];

          for (i = 0; i < dim; i ++)
            {
              if (i == k)
                d_yf[k] = gf_newton[j];
            }
        }

      err = -10.;

      for (i = 0; i < fast; i++)
        {
          gf_newton[i] = fabs(gf_newton[i]);

          if (err < gf_newton[i])
            err = gf_newton[i];
        }

      iterations = iterations + 1;

      // stop criterion of newton method

      //   C_FLOAT64 g1, g2 = 0.0;

      //   g2 = err;

      if (iter == 1)
        g1 = 3.0 * err;
      else
        g1 = g2;

      g2 = err;

      if (g2 / g1 > 1.0)
        {
          info = 1;
          return;
        }
    } /* end while */

  for (i = 0; i < dim; i++)
    mY_cons[i] = y_newton[i];

  info = 0;

  return;
}

/*
 * NEWTON for "postprove": Prove of "fast" varibles
 * Output:  y_consistent, info
 */
void CILDMModifiedMethod::newton_for_timestep(C_INT metabolite_number, C_FLOAT64 & y_consistent, C_INT & info)
{
  C_INT i, iter, itermax, flag_newton;
  iter = 0;
  itermax = 150;

  flag_newton = 1;  // set flag_newton=0 to print the iteration steps

  C_FLOAT64 tol, err;
  tol = 1e-6;
  err = 10.0;

  C_INT dim = mDim;

  C_FLOAT64 d_y, deriv;
  d_y = 0;
  deriv = mJacobian_initial(metabolite_number, metabolite_number);

  if (deriv == 0)
    {
      return;
    }

  info = 0;

  //this is an ugly hack that only makes sense if all metabs are in the same compartment
  //at the moment is is the only case the algorithm deals with

  CVector<C_FLOAT64> y_newton; //current state converted to concentrations
  y_newton.resize(dim);

  for (i = 0; i < dim; ++i)
    y_newton[i] = mY_initial[i] * mNumber2Concentration;

  CVector<C_FLOAT64> dydt;
  dydt.resize(dim);

  while (err > tol)
    {
      iter ++;

      if (iter > itermax)
        {
          info = 1;
          break;
        }

      y_newton[metabolite_number] = y_newton[metabolite_number] + d_y;

      calculateDerivatives(y_newton.array(), dydt.array(), true);

      d_y = - 1 / deriv * dydt[metabolite_number];

      if (err > fabs(d_y))
        err = fabs(d_y);
    }

  y_consistent = y_newton[metabolite_number];

  return;
}

/**
 * Empty every vector to be able to fill them with new values for a new calculation.
 * Also nullify the step counter.
 **/
void CILDMModifiedMethod::emptyVectors()
{
  mCurrentStep = 0;
  mVec_mVslow.erase(mVec_mVslow.begin(), mVec_mVslow.end());
  mVec_TimeScale.erase(mVec_TimeScale.begin(), mVec_TimeScale.end());
  mVec_mVslowMetab.erase(mVec_mVslowMetab.begin(), mVec_mVslowMetab.end());
  mVec_mVslowSpace.erase(mVec_mVslowSpace.begin(), mVec_mVslowSpace.end());
  mVec_SlowModes.erase(mVec_SlowModes.begin(), mVec_SlowModes.end());
}

/**
 *upgrade all vectors with values from actually calculalion for current step
 **/
void CILDMModifiedMethod::setVectors(int slowMode)
{
  mVec_mVslow.push_back(mCurrentStep);
  mVec_mVslow[mCurrentStep].resize(mDim, mDim);
  mVec_mVslow[mCurrentStep] = mVslow;

  mVec_TimeScale.push_back(mCurrentStep);
  mVec_TimeScale[mCurrentStep].resize(mDim);
  int i;

  for (i = 0; i < mDim; i++)
    mVec_TimeScale[mCurrentStep][i] = -1 / mR(i, i);

  mVec_mVslowMetab.push_back(mCurrentStep);
  mVec_mVslowMetab[mCurrentStep].resize(mDim, mDim);
  mVec_mVslowMetab[mCurrentStep] = mVslow_metab;

  mVec_mVslowSpace.push_back(mCurrentStep);
  mVec_mVslowSpace[mCurrentStep].resize(mDim);
  mVec_mVslowSpace[mCurrentStep] = mVslow_space;

  mVec_mVfastSpace.push_back(mCurrentStep);
  mVec_mVfastSpace[mCurrentStep].resize(mDim);
  mVec_mVfastSpace[mCurrentStep] = mVfast_space;

  mVec_SlowModes.push_back(mCurrentStep);
  mVec_SlowModes[mCurrentStep] = slowMode;
}

/**
 * Create the CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget.
 * Input for each CArraAnnotations is a separate CMatrix.
 **/
void CILDMModifiedMethod::createAnnotationsM()
{

  tableNames.erase(tableNames.begin(), tableNames.end());

  std::string name;

  name = "Contribution of species to modes";
  tableNames.push_back(name);

  CDataArray *
  pTmp1 = new CDataArray("Contribution of species to modes", this,
                         new CMatrixInterface<CMatrix<C_FLOAT64> >(&mVslowPrint), true);
  pTmp1->setMode(0, CDataArray::Mode::Strings);
  pTmp1->setMode(1, CDataArray::Mode::Vector);
  pTmp1->setDescription(" ");
  pTmp1->setDimensionDescription(0, "Contribution to  mode (TS - corresponding timescale)");
  pTmp1->setDimensionDescription(1, "Species");
  pVslowPrintAnn = pTmp1;

  mapTableToName[name] = pVslowPrintAnn;

  name = "Modes distribution for species";
  tableNames.push_back(name);

  CDataArray *
  pTmp2 = new CDataArray("Modes distribution for species", this,
                         new CMatrixInterface<CMatrix<C_FLOAT64> >(&mVslowMetabPrint), true);
  pTmp2->setMode(1, CDataArray::Mode::Strings);
  pTmp2->setMode(0, CDataArray::Mode::Vector);
  pTmp2->setDescription(" ");
  pTmp2->setDimensionDescription(0, "Mode distribution for each metabolite");
  pTmp2->setDimensionDescription(1, "modes (TS - corresponding  timescale)");
  pVslowMetabPrintAnn = pTmp2;

  mapTableToName[name] = pVslowMetabPrintAnn;

  name = "Slow space";
  tableNames.push_back(name);

  CDataArray *
  pTmp3 = new CDataArray("Slow space", this,
                         new CMatrixInterface<CMatrix<C_FLOAT64> >(&mVslowSpacePrint), true);
  pTmp3->setMode(1, CDataArray::Mode::Strings);
  pTmp3->setMode(0, CDataArray::Mode::Vector);
  pTmp3->setDescription(" ");
  pTmp3->setDimensionDescription(0, "Species");
  pTmp3->setDimensionDescription(1, "Contribution to slow space");
  pVslowSpacePrintAnn = pTmp3;

  mapTableToName[name] = pVslowSpacePrintAnn;

  name = "Fast space";
  tableNames.push_back(name);

  CDataArray *
  pTmp4 = new CDataArray("Fast space", this,
                         new CMatrixInterface<CMatrix<C_FLOAT64> >(&mVfastSpacePrint), true);
  pTmp4->setMode(1, CDataArray::Mode::Strings);
  pTmp4->setMode(0, CDataArray::Mode::Vector);
  pTmp4->setDescription(" ");
  pTmp4->setDimensionDescription(0, "Species");
  pTmp4->setDimensionDescription(1, "Contribution to fast space");
  pVfastSpacePrintAnn = pTmp4;

  mapTableToName[name] = pVfastSpacePrintAnn;
}

void
CILDMModifiedMethod::initializeOutput()
{
}
/**
 * Set the every CArrayAnnotation for the requested step.
 * Set also the description of CArayAnnotation for both dimensions:
 *    - dimension description could consists of some std::srings
 *      some strings contain the Time Scale values for requested step
 *    - dimension description could consists of arrays of CommonNames
 **/
bool CILDMModifiedMethod::setAnnotationM(size_t step)
{
  const CModel & Model = mpContainer->getModel();

  if (mVec_mVslow.size() == 0) return false;

  //if (step > mVec_mVslow.size()) return false;

  if (step > mVec_SlowModes.size()) return false;

  // step -= 1; already done
  double timeScale;
  std::string str;
  std::stringstream sstr;
  sstr.str("");
  sstr.clear();
  int i;

  mVslowPrint.resize(mDim, mDim);
  mVslowPrint = mVec_mVslow[step];
  pVslowPrintAnn->resize();
  pVslowPrintAnn->setCopasiVector(1, Model.getMetabolitesX());

  for (i = 0; i < mDim; i++)
    {
      timeScale = mVec_TimeScale[step][i];

      if (i < mVec_SlowModes[step])
        sstr << "Slow: ";
      else
        sstr << "Fast: ";

      sstr << timeScale;
      str = sstr.str();
      pVslowPrintAnn->setAnnotationString(0, i, str);
      sstr.str("");
      sstr.clear();
    }

  mVslowMetabPrint.resize(mDim, mDim);
  mVslowMetabPrint = mVec_mVslowMetab[step];
  pVslowMetabPrintAnn->resize();
  pVslowMetabPrintAnn->setCopasiVector(0, Model.getMetabolitesX());

  for (i = 0; i < mDim; i++)
    {
      timeScale = mVec_TimeScale[step][i];

      if (i < mVec_SlowModes[step])
        sstr << "Slow: ";
      else
        sstr << "Fast: ";

      sstr << timeScale;
      str = sstr.str();
      pVslowMetabPrintAnn->setAnnotationString(1, i, str);
      sstr.str("");
      sstr.clear();
    }

  sstr << mVec_SlowModes[step];
  // if (mVec_SlowModes[step] > 1)
  // sstr << " slow modes";
  //else
  // sstr << " slow mode";
  sstr << " slow; ";

  C_INT dim = mDim;
  sstr << dim - mVec_SlowModes[step];
  sstr << " fast";

  str = sstr.str();
  mVslowSpacePrint.resize(mDim, 1);

  for (i = 0; i < mDim; i++)
    mVslowSpacePrint(i, 0) = mVec_mVslowSpace[step][i];

  pVslowSpacePrintAnn->resize();
  pVslowSpacePrintAnn->setCopasiVector(0, Model.getMetabolitesX());
  pVslowSpacePrintAnn->setAnnotationString(1, 0, str);

  mVfastSpacePrint.resize(mDim, 1);

  for (i = 0; i < mDim; i++)
    mVfastSpacePrint(i, 0) = mVec_mVfastSpace[step][i];

  pVfastSpacePrintAnn->resize();
  pVfastSpacePrintAnn->setCopasiVector(0, Model.getMetabolitesX());
  pVfastSpacePrintAnn->setAnnotationString(1, 0, str);

  return true;
}

void CILDMModifiedMethod::printResult(std::ostream * ostream) const
{
  const CModel & Model = mpContainer->getModel();

  std::ostream & os = *ostream;
  double timeScale;
  C_INT i, j, istep = 0;

  assert(getObjectDataModel() != NULL);

  C_INT32 stepNumber = mVec_SlowModes.size();

  for (istep = 0; istep < stepNumber; ++istep)
    {

      os << std::endl;
      os << "**************** Time step " << istep + 1
         << ": " << getTimeForStep(istep)
         << " " << Model.getTimeUnitName()
         <<  " **************************  " << std::endl;

      os << std::endl;

      os << "Contribution of species to modes" << std::endl;

      os << "Rows: contribution to  mode (TS - corresponding timescale)" << std::endl;
      os << "Columns: species  ";

      for (j = 0; j < mDim; j++)
        {
          os << "   " << Model.getMetabolitesX()[j].getObjectName();
        }

      os << std::endl;

      for (i = 0; i < mDim; i++)
        {
          timeScale = mVec_TimeScale[istep][i];

          if (i < mVec_SlowModes[istep])
            os << "  Slow (";
          else
            os << "  Fast (";

          os << timeScale << "): ";

          for (j = 0; j < mDim; j++)
            os << mVec_mVslow[istep][i][j] << " ";

          os << std::endl;
        }

      os << std::endl;

      os << "Modes distribution for species" << std::endl;

      os << "Rows: Mode distribution for each species" << std::endl;
      os << "Columns: Modes (TS - corresponding  timescale)" << std::endl;

      for (i = 0; i < mDim; i++)
        {
          timeScale = mVec_TimeScale[istep][i];

          if (i < mVec_SlowModes[istep])
            os << "  Slow (";
          else
            os << "  Fast (";

          os << timeScale << ")";
        }

      os << std::endl;

      for (j = 0; j < mDim; j++)
        {
          os << "  " << Model.getMetabolitesX()[j].getObjectName();

          for (i = 0; i < mDim; i++)
            os << "  " << mVec_mVslowMetab[istep][j][i];

          os << std::endl;
        }

      os << std::endl;

      os << "Slow space" << std::endl;

      os << "Rows: Species" << std::endl;
      os << "Column: Contribution to slow space" << std::endl;

      os << "  " << mVec_SlowModes[istep];
      os << " slow; ";

      os << mDim - mVec_SlowModes[istep];
      os << " fast";
      os << std::endl;

      for (j = 0; j < mDim; j++)
        {
          os  << "  " << Model.getMetabolitesX()[j].getObjectName();
          os  << "  " << mVec_mVslowSpace[istep][j];

          os << std::endl;
        }

      os << std::endl;
      os << "Fast space" << std::endl;

      os << "Rows: Species" << std::endl;
      os << "Column: Contribution to fast space " << std::endl;

      os << "  " << mVec_SlowModes[istep];
      os << " slow; ";

      os << mDim - mVec_SlowModes[istep];
      os << " fast";
      os << std::endl;

      for (j = 0; j < mDim; j++)
        {
          os << "  " << Model.getMetabolitesX()[j].getObjectName();
          os << "  " << mVec_mVfastSpace[istep][j];

          os << std::endl;
        }

      os << std::endl;
    }

  return;
}
