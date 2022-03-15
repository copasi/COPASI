// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTSSAMethod class.
 *  This class describes the interface to all  time scale separation analysis methods.
 *  The various method like ILDM or CSP have to be derived from
 *  this class.
 *
 */

#include <sstream>

#include "copasi/copasi.h"

#include "copasi/tssanalysis/CTSSAMethod.h"
#include "copasi/tssanalysis/CTSSAProblem.h"
#include "copasi/tssanalysis/CILDMMethod.h"
#include "copasi/tssanalysis/CILDMModifiedMethod.h"
#include "copasi/tssanalysis/CCSPMethod.h"
#include "copasi/tssanalysis/CTSSAProblem.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/model/CCompartment.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/trajectory/CLsodaMethod.h"
#include "copasi/utilities/CMethodFactory.h"

#include "copasi/lapack/lapackwrap.h"        // CLAPACK
#include "copasi/lapack/blaswrap.h"           // BLAS

/**
 *  Default constructor.
 */
CTSSAMethod::CTSSAMethod(const CDataContainer * pParent,
                         const CTaskEnum::Method & methodType,
                         const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType),
  mpProblem(NULL),
  mpLsodaMethod(NULL),
  mDim(0),
  mY_initial(),
  mJacobian(),
  mJacobian_initial(),
  mQ(),
  mQ_desc(),
  mR(),
  mR_desc(),
  mTd(),
  mTdInverse(),
  mQz(),
  mTd_save(),
  mTdInverse_save(),
  mCfast(),
  mY_cons(),
  mVslow(),
  mVslow_metab(),
  mVslow_space(),
  mVfast_space(),
  mSlow(0),
  mDtol(1e-6),
  mEPS(0.01),
  mNumber2Concentration(1.0),
  mConcentration2Number(1.0),
  mContainerState(),
  mpContainerStateTime(NULL),
  mpFirstSpecies(NULL),
  mpFirstSpeciesRate(NULL),
  mVec_SlowModes(),
  mCurrentTime(),
  mVec_TimeScale(),
  mCurrentStep(0)

{}

/**
 *  Copy constructor.
 *  @param "const CTSSAMethod &" src
 */
CTSSAMethod::CTSSAMethod(const CTSSAMethod & src,
                         const CDataContainer * pParent):
  CCopasiMethod(src, pParent),
  mpProblem(src.mpProblem),
  mpLsodaMethod(NULL),
  mDim(0),
  mY_initial(),
  mJacobian(),
  mJacobian_initial(),
  mQ(),
  mQ_desc(),
  mR(),
  mR_desc(),
  mTd(),
  mTdInverse(),
  mQz(),
  mTd_save(),
  mTdInverse_save(),
  mCfast(),
  mY_cons(),
  mVslow(),
  mVslow_metab(),
  mVslow_space(),
  mVfast_space(),
  mSlow(0),
  mDtol(src.mDtol),
  mEPS(src.mEPS),
  mNumber2Concentration(1.0),
  mConcentration2Number(1.0),
  mContainerState(),
  mpContainerStateTime(NULL),
  mpFirstSpecies(NULL),
  mpFirstSpeciesRate(NULL),
  mVec_SlowModes(),
  mCurrentTime(),
  mVec_TimeScale(),
  mCurrentStep(0)
{}

/**
 *  Destructor.
 */
CTSSAMethod::~CTSSAMethod()
{
  pdelete(mpLsodaMethod);
}

/**
 *  Set a pointer to the problem.
 *  This method is used by CTSSA
 *  @param "CTSSAProblem *" problem
 */
void CTSSAMethod::setProblem(CTSSAProblem * problem)
{mpProblem = problem;}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the current state, i.e., the result of the previous
 *  step.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual time step taken.
 *  @param "const double &" deltaT
 */
void CTSSAMethod::step(const double & /* deltaT */)
{return ;}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the initialState given.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual time step taken.
 */
void CTSSAMethod::start()
{
  mDim = mpContainer->getCountIndependentSpecies();

  mContainerState.initialize(mpContainer->getState(true));

  mpContainerStateTime = mContainerState.array() + mpContainer->getCountFixedEventTargets();
  mpFirstSpecies = mContainerState.array() + mpContainer->getCountFixedEventTargets() + 1 /* Time */ + mpContainer->getCountODEs();
  mpFirstSpeciesRate = mpContainer->getRate(true).array() + mpContainer->getCountFixedEventTargets() + 1 /* Time */ + mpContainer->getCountODEs();

  const CModel & Model = mpContainer->getModel();

  mNumber2Concentration = Model.getNumber2QuantityFactor() / Model.getCompartments()[0].getInitialValue();
  mConcentration2Number =  Model.getQuantity2NumberFactor() * Model.getCompartments()[0].getInitialValue();

  mpLsodaMethod->setMathContainer(mpContainer);
}

void CTSSAMethod::initializeOutput()
{
  return;
}

//virtual
bool CTSSAMethod::isValidProblem(const CCopasiProblem * pProblem)
{

  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CTSSAProblem * pTP = dynamic_cast<const CTSSAProblem *>(pProblem);

  if (!pTP)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTSSAMethod + 2);
      return false;
    }

  const CModel & Model = mpContainer->getModel();

  if (Model.getMetabolites().size() == 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTSSAMethod + 18);
      return false;
    }

  if (Model.getCompartments().size() != 1)
    {
      CTaskEnum::Method subType;

      subType = getSubType();

      switch (subType)
        {
          case CTaskEnum::Method::tssILDM:
          case CTaskEnum::Method::tssILDMModified:

            CCopasiMessage(CCopasiMessage::ERROR, MCTSSAMethod + 16);
            return false;

          case CTaskEnum::Method::tssCSP:
            return true;

          default:
            fatalError();
            break;
        }
    }

// Check if the model has a species with an assigments or an ODE
  if (Model.getNumODEMetabs() != 0 || Model.getNumAssignmentMetabs() != 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "TSSA can not be applyed for systems with species determined by assigments or ODE.");
      return false;
    }

// Check if the model has a compartment with an ODE
  CDataVector< CCompartment >::const_iterator it = Model.getCompartments().begin();
  CDataVector< CCompartment >::const_iterator end = Model.getCompartments().end();

  for (; it != end; ++it)
    if (it->getStatus() == CModelEntity::Status::ODE ||
        it->getStatus() ==  CModelEntity::Status::ASSIGNMENT)

      {
        CCopasiMessage(CCopasiMessage::ERROR, " TSSA can not be applyed for systems with non-constant  volumes");
        return false;
      }

// Check if the model has a model parameter  with an ODE

  size_t i;

  for (i = 0; i < Model.getModelValues().size(); i++)
    {
      if (Model.getModelValues()[i].getStatus() == CModelEntity::Status::ODE)
        {
          CCopasiMessage(CCopasiMessage::ERROR, "TSSA can not be applyed for systems with parameters defined by ODE.");
          return false;
        }
    }

// Check if the model contains events
  if (Model.getEvents().size() != 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "TSSA can not be applyed  for systems with events");
      return false;
    }

  return true;
}

C_FLOAT64 CTSSAMethod::getTimeForStep(int step) const
{
  if ((int) mCurrentTime.size() > step)
    return mCurrentTime[step];

  return 0;
};

void CTSSAMethod::initializeParameter()
{
  if (mpLsodaMethod == NULL)
    {
      mpLsodaMethod = static_cast< CLsodaMethod *>(CMethodFactory::create(CTaskEnum::Task::timeCourse, CTaskEnum::Method::deterministic, this));

      mpLsodaMethod->setValue("Integrate Reduced Model", true);
      mpLsodaMethod->setValue("Relative Tolerance", (C_FLOAT64) 1.0e-6);
      mpLsodaMethod->setValue("Absolute Tolerance", (C_FLOAT64) 1.0e-12);
      mpLsodaMethod->setValue("Max Internal Steps", (unsigned C_INT32) 100000);
    }

  return;
}

bool CTSSAMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

void CTSSAMethod::integrationStep(const double & deltaT)
{
  mpLsodaMethod->step(deltaT);
}
/**
MAT_ANAL_MOD:  mathematical analysis of matrices mTdInverse for post-analysis
 */
void CTSSAMethod::mat_anal_mod(C_INT & slow)
{

  C_INT i, j, dim;

  dim = mDim;

  CVector<C_FLOAT64> denom;
  denom.resize(dim);

  CMatrix<C_FLOAT64> Matrix_anal;
  Matrix_anal.resize(dim, dim);

  // norm  of mTd

  if (slow < dim)
    {
      for (j = 0; j < dim; j++)
        denom[j] = 0;

      for (i = 0; i < dim; i++)
        {
          for (j = 0; j < dim; j++)
            denom[i] = denom[i] + fabs(mTdInverse(i, j));
        }

      for (i = 0; i < dim; i++)
        {
          for (j = 0; j < dim; j++)
            mVslow(i, j) = fabs(mTdInverse(i, j)) / denom[i] * 100;

          //  mVslow(i, j) = fabs(mTd(i, j)) / denom[i] * 100;
        }
    }
  else
    for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
        mVslow(i, j) = 0;

  return;
}

/**
MAT_ANAL_METAB:  mathematical analysis of matrices mTd for post-analysis
 */
void CTSSAMethod::mat_anal_metab(C_INT & slow)
{
  C_INT i, j, dim;

  dim = mDim;

  CVector<C_FLOAT64> denom;
  denom.resize(dim);

  if (slow < dim)
    {
      for (j = 0; j < dim; j++)
        denom[j] = 0;

      for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
          denom[i] = denom[i] + fabs(mTd(i, j));

      for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
          mVslow_metab(i, j) = fabs(mTd(i, j)) / denom[i] * 100;
    }
  else
    for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
        mVslow_metab(i, j) = 0;

  return;
}

/**
MAT_ANAL_MOD_space:  mathematical analysis of matrices mTdInverse for post-analysis
 */

void CTSSAMethod::mat_anal_mod_space(C_INT & slow)
{
  C_FLOAT64 denom, length;
  C_INT i, j, dim;

  dim = mDim;
  C_INT fast;
  fast = dim - slow;

  CMatrix<C_FLOAT64> Matrix_anal;
  Matrix_anal.resize(dim, dim);

  for (j = 0; j < dim; j++)
    {
      length = 0;

      for (i = 0; i < dim; i++)
        length = length + mTdInverse(i, j) * mTdInverse(i, j);

      length = sqrt(length);
      length = 1;

      for (i = 0; i < dim; i++)
        Matrix_anal(i, j) = mTdInverse(i, j) / length;
    }

  if ((slow < dim) & (slow > 0))
    {
      denom = 0.0;

      for (i = 0; i < dim; i++)
        {
          for (j = 0; j < slow; j++)
            denom = denom + fabs(Matrix_anal(j, i));
        }

      for (i = 0; i < dim; i++)
        mVslow_space[i] = 0.0;

      for (j = 0; j < dim; j++)
        {
          for (i = 0; i < slow; i++)
            mVslow_space[j] = mVslow_space[j] + fabs(Matrix_anal(i, j));

          mVslow_space[j] = (mVslow_space[j] / denom) * 100;
        }
    }
  else
    for (i = 0; i < dim; i++)
      mVslow_space[i] = 0;

  return;
}

/**
MAT_ANAL_fast_space:  mathematical analysis of matrices mTdInverse for post-analysis
 */

void CTSSAMethod::mat_anal_fast_space(C_INT & slow)
{
  C_FLOAT64 denom, length;
  C_INT i, j, dim;

  dim = mDim;
  C_INT fast;
  fast = dim - slow;

  CMatrix<C_FLOAT64> Matrix_anal;
  Matrix_anal.resize(dim, dim);

  for (j = 0; j < dim; j++)
    {
      length = 0;

      for (i = 0; i < dim; i++)
        length = length + mTdInverse(i, j) * mTdInverse(i, j);

      length = sqrt(length);
      length = 1;

      for (i = 0; i < dim; i++)
        Matrix_anal(i, j) = mTdInverse(i, j) / length;
    }

  if (slow < dim)
    {
      denom = 0.0;

      for (i = 0; i < dim; i++)
        {
          for (j = slow; j < dim; j++)
            denom = denom + fabs(Matrix_anal(j, i));
        }

      for (i = 0; i < dim; i++)
        mVfast_space[i] = 0.0;

      for (j = 0; j < dim; j++)
        {
          for (i = slow; i < dim; i++)
            mVfast_space[j] = mVfast_space[j] + fabs(Matrix_anal(i, j));

          mVfast_space[j] = (mVfast_space[j] / denom) * 100;
        }
    }
  else
    for (i = 0; i < dim; i++)
      mVfast_space[i] = 0;

  return;
}

/**
MAT_ANAL_fast_space:  mathematical analysis of matrices mTdInverse for post-analysis
 */

void CTSSAMethod::mat_anal_fast_space_thomas(C_INT & slow)
{
  C_FLOAT64 scalar_product, absolute_value_1;
  C_INT i, j, k, dim;

  dim = mDim;
  C_INT fast;
  fast = dim - slow;

  //C_FLOAT64 number2conc = 1.;

  //this is an ugly hack that only makes sense if all metabs are in the same compartment
  //at the moment is is the only case the algorithm deals with

  CVector<C_FLOAT64> Xconc; //current state converted to concentrations
  Xconc.resize(dim);

  for (i = 0; i < dim; ++i)
    Xconc[i] = mY_initial[i] * mNumber2Concentration;

  CVector<C_FLOAT64> d_full;
  d_full.resize(dim);
  CVector<C_FLOAT64> d_transformed;
  d_transformed.resize(dim);

  for (j = 0; j < dim; j++)
    {
      for (i = 0; i < slow; i++)
        d_full[i] = 0.0;

      for (i = slow; i < dim; i++)
        d_full[i] = mQ(j, i) * Xconc[j];

      for (i = 0; i < dim; i ++)
        {
          d_transformed[i] = 0.0;

          for (k = 0; k < dim; k++)
            d_transformed[i] += mQ(i, k) * d_full[k];
        }

      scalar_product = d_transformed[j];
      absolute_value_1 = 0.0;

      for (i = 0; i < dim; i++)
        absolute_value_1 += d_transformed[i] * d_transformed[i];

      absolute_value_1 = sqrt(absolute_value_1);

      if (absolute_value_1 * Xconc[j] > 0.0)
        scalar_product = scalar_product / absolute_value_1;
      else
        scalar_product = -2.0;

      mVfast_space[j] = scalar_product;
    }

  return;
}

double CTSSAMethod::orthog(C_INT & number1, C_INT & number2)
{
  C_FLOAT64 product = 0;
  C_INT k, dim;

  dim = mDim;

  for (k = 0; k < dim; k++)
    product = product + mTdInverse(k, number1) * mTdInverse(k, number2);

  return product;
}

/**
 SCHUR:  Schur  Decomposition of Jacobian (reordered).
 Output:  mQ - transformation matrix
 mR - block upper triangular matrix (with ordered eigenvalues)
 */

void CTSSAMethod::schur(C_INT &info)
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
  // TO REMOVE : L_fp select;
  C_INT dim = mDim;
  C_INT SDIM = 0;

  CVector<C_FLOAT64> R;
  R.resize(dim * dim);
  C_INT i, j;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      R[j + dim * i] = mJacobian_initial(j, i);

  CVector<C_FLOAT64> eval_r;
  CVector<C_FLOAT64> eval_i;
  eval_r.resize(dim);
  eval_i.resize(dim);

  CVector<C_FLOAT64> Q;
  Q.resize(dim * dim);

  C_INT lwork = 10 * dim;
  CVector< C_FLOAT64 > work;
  work.resize(10 * dim);

  CVector< C_LOGICAL > Bwork;
  Bwork.resize(dim);

  dgees_(&V, &N, NULL, &dim, R.array(), &dim, &SDIM, eval_r.array(), eval_i.array(), Q.array(), &dim, work.array(), & lwork, Bwork.array(), &info);

  if (info)
    {
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

          bool diagorder = false;

          CTaskEnum::Method subType;

          subType = getSubType();

          switch (subType)
            {
              case CTaskEnum::Method::tssILDM:
                diagorder = (index[count + 1] < index[count]);
                break;

              case CTaskEnum::Method::tssILDMModified:
                diagorder = (index[count + 1] < index[count]);
                break;

              case CTaskEnum::Method::tssCSP:
                diagorder = (index[count + 1] > index[count]);
                break;

              default:
                fatalError();
                break;
            }

          //ILDM : if (index[count + 1] < index[count])
          //CSP:  if (index[count + 1] > index[count])
          if (diagorder)
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
 SCHUR_desc:  Schur  Decomposition of Jacobian (reordered).
 Output:  mQ_desc - transformation matrix
 mR_desc - block upper triangular matrix (with ordered eigenvalues)
 */

void CTSSAMethod::schur_desc(C_INT &info)
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
  // TO REMOVE : L_fp select;
  C_INT dim = mDim;
  C_INT SDIM = 0;

  CVector<C_FLOAT64> R;
  R.resize(dim * dim);
  C_INT i, j;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      R[j + dim * i] = mJacobian_initial(j, i);

  CVector<C_FLOAT64> eval_r;
  CVector<C_FLOAT64> eval_i;
  eval_r.resize(dim);
  eval_i.resize(dim);

  CVector<C_FLOAT64> Q;
  Q.resize(dim * dim);

  C_INT lwork = 10 * dim;
  CVector< C_FLOAT64 > work;
  work.resize(10 * dim);

  CVector< C_LOGICAL > Bwork;
  Bwork.resize(dim);

  dgees_(&V, &N, NULL, &dim, R.array(), &dim, &SDIM, eval_r.array(), eval_i.array(), Q.array(), &dim, work.array(), & lwork, Bwork.array(), &info);

  if (info)
    {
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

  map_index_desc(eval_reor.array(), index.array(), dim);

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

              map_index_desc(j_diag.array(), index.array(), dim);
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
        mQ_desc(j, i) = Q.array()[j + dim * i];
        mR_desc(j, i) = R.array()[j + dim * i];
      }

  return;
}

/**
SYLVESTER:
Solution of Sylvester equation for given slow, mQ,mR
Output: mTd, mTdinverse, mQz (is used later for Newton iterations)
 */

void CTSSAMethod::sylvester(C_INT slow, C_INT & info)
{
  char N1 = 'N';
  char N2 = 'N';
  C_INT isgn = -1;

  C_INT dim = mDim;

  C_INT fast = dim - slow;
  //  C_INT info;

  C_INT i, j, k;

  C_FLOAT64 scale = -1;

  CVector<C_FLOAT64> st_slow;
  st_slow.resize(slow * slow);

  CVector<C_FLOAT64> st_fast;
  st_fast.resize(fast * fast);

  CVector<C_FLOAT64> st_coup;
  st_coup.resize(slow * fast);

  CMatrix<C_FLOAT64> S_coup;
  S_coup.resize(slow, fast);

  for (i = 0; i < slow; i++)
    for (j = 0; j < slow; j++)
      st_slow[j + slow * i] = mR(j, i);

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      st_fast[j + fast * i] = mR(j + slow, i + slow);

  for (i = 0; i < slow; i++)
    for (j = 0; j < fast; j++)
      S_coup(i, j) = mR(i, j + slow);

  for (j = 0; j < fast; j++)
    for (i = 0; i < slow; i++)
      st_coup[i + slow * j] = -S_coup(i, j);

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
            E(i, j) = E(i, j) + mJacobian_initial(i, k) * mTd(k, j);
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

  C_INT flag_sylvester;

  flag_sylvester = 1;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      mQz(i, j) = 0.;

  for (i = 0; i < fast; i++)
    for (j = 0; j < fast; j++)
      mQz(i, j) = S(i + slow, j + slow);

  return;
}

void CTSSAMethod::calculateDerivatives(C_FLOAT64 * X1, C_FLOAT64 * Y1, bool useReducedModel)
{
  CVector< C_FLOAT64 > SavedState = mpContainer->getValues();

  C_FLOAT64 * pSpecies = mpFirstSpecies;
  C_FLOAT64 * pSpeciesEnd = mpFirstSpecies + mDim;
  C_FLOAT64 * pX = X1;

  for (; pSpecies != pSpeciesEnd; ++pSpecies, ++pX)
    {
      *pSpecies = mConcentration2Number **pX;
    }

  mpContainer->updateSimulatedValues(useReducedModel);

  const C_FLOAT64 * pRate = mpFirstSpeciesRate;
  const C_FLOAT64 * pRateEnd = mpFirstSpeciesRate + mDim;
  C_FLOAT64 * pY = Y1;

  for (; pRate != pRateEnd; ++pRate, ++pY)
    {
      *pY = mNumber2Concentration **pRate;
    }

  mpContainer->setValues(SavedState);

  return;
}

/**
MAP_INDEX used for sorting of SchurDecompostion
 */

void CTSSAMethod::map_index(C_FLOAT64 *eval_r, C_INT *index, const C_INT & dim)
{
  C_INT i, j, count;
  C_INT max;
  C_FLOAT64 max_value, factor;

  CVector< C_FLOAT64 > abs_eval_r(dim);

  max_value = eval_r[0];

  for (i = 1; i < dim; i++)
    if (eval_r[i] > max_value)
      max_value = eval_r[i];

  if (max_value > 0)
    factor = 1.1;
  else
    {
      if (max_value == 0)
        {
          max_value = 10;
          factor = 1;
        }
      else
        factor = 0.;
    }

  for (i = 0; i < dim; i++)
    {
      index[i] = 0;
      //abs_eval_r[i] = fabs(eval_r[i]);
      abs_eval_r[i] = (eval_r[i]);
    }

  count = dim;

  for (i = 0; i < dim; i++)
    {
      max = i;

      for (j = 0; j < dim; j++)
        {
          //if (abs_eval_r[j] > abs_eval_r[max])
          if (abs_eval_r[j] < abs_eval_r[max])
            max = j;
        }

      index[max] = count;
      abs_eval_r[max] = factor * max_value;
      count --;
    }

  for (i = 0; i < dim - 1; i++)
    if (eval_r[i] == eval_r[i + 1])
      index[i + 1] = index[i];

  return;
}

/**
This is the test only.  We try to reorder the Schur matrix from slowest mode (on the bottom) to the fastest (on the top)
The function map_index_desc()  is used on the end of schur()  in order to produce the orthogonal slow space
 */
void CTSSAMethod::map_index_desc(C_FLOAT64 *eval_r, C_INT *index, const C_INT & dim)
{
  C_INT i, j, count;
  C_INT min;
  C_FLOAT64 min_value, factor;

  CVector< C_FLOAT64 > abs_eval_r(dim);

  factor = 1.1;

  min_value = eval_r[0];

  for (i = 1; i < dim; i++)
    if (eval_r[i] < min_value)
      min_value = eval_r[i];

  for (i = 0; i < dim; i++)
    {
      index[i] = 0;
      //abs_eval_r[i] = fabs(eval_r[i]);
      abs_eval_r[i] = (eval_r[i]);
    }

  count = dim;

  for (i = 0; i < dim; i++)
    {
      min = i;

      for (j = 0; j < dim; j++)
        {
          //if (abs_eval_r[j] > abs_eval_r[max])
          if (abs_eval_r[j] >= abs_eval_r[min])
            min = j;
        }

      index[min] = count;
      abs_eval_r[min] = factor * min_value;
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
void CTSSAMethod::update_nid(C_INT *index, C_INT *nid, const C_INT & dim)
{
  C_INT k;

  for (k = 0; k < dim; k++)
    nid[k] = 0;

  for (k = 1; k < dim - 1; k++)
    if (index[k] == index[k + 1])
      nid[k - 1] = k;

  return;
}

/**
UPDATE_PID: used for sorting of SchurDecompostion
 */
void CTSSAMethod::update_pid(C_INT *index, C_INT *pid, const C_INT & dim)
{
  C_INT k;

  for (k = 0; k < dim; k++)
    pid[k] = 0;

  for (k = 1; k < dim; k++)
    if (index[k] == index[k - 1])
      pid[k] = k;

  return;
}

void CTSSAMethod::integrationMethodStart()
{
  mpLsodaMethod->start();
}

/**************** display matrix methods ***********************************/

// to activate the printing  set flag_...=0:

//  flag_jacob=0  to print Jacobian
//  flag_schur=0  to print matrices of Schur decomposition
//  flag_tab =0 to print the Tabs with slow space Analysis
//  flag_deufl=0 to prove the Deuflhard algorithm
//  flag_Td =0  to print the transformation matrices mTd and mTdInverse
//  flag_sylvester=0  to print the transformed Jacobian:  mTdInverse*Jacobian_initial*mTd (should be diagonal)
//  flag_norm =0 for printing "norm story"
//  flag_orthog =0 to print the matrices proved the orthogonality of transformation

const int & CTSSAMethod::getCurrentStep() const
{
  return mCurrentStep;
}

/**
 * return mVec_TimeScale for visualization in ILDM-tab
 * in the CQTSSAResultSubWidget
 **/
CVector< C_FLOAT64> CTSSAMethod::getVec_TimeScale(int step)
{
  return mVec_TimeScale[step - 1];
}

/**
 * Empty every vector to be able to fill them with new values for a new calculation.
 * Also nullify the step counter.
 **/
void CTSSAMethod::emptyVectors()
{}

/**
 *upgrade all vectors with values from actually calculation for current step
 **/
void CTSSAMethod::setVectors(int /* slowMode */)
{}

/**
 * Create the CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget.
 * Input for each CArraAnnotations is a separate CMatrix.
 **/
void CTSSAMethod::createAnnotationsM()
{}

void CTSSAMethod::updateCurrentTime()
{
  mCurrentTime.push_back(mCurrentStep);
  mCurrentTime[mCurrentStep] = *mpContainerStateTime;
}

const std::vector<std::string>& CTSSAMethod::getTableNames() const
{
  return tableNames;
}

const CDataArray *CTSSAMethod::getTable(const std::string &name)
{
  return mapTableToName[name];
}
