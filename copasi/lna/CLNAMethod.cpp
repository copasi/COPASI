// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <cmath>
#include <limits>

#include "copasi/copasi.h"

#include "CLNAMethod.h"
#include "CLNAProblem.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/utility.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CReadConfig.h"

#include "copasi/lapack/blaswrap.h"
#include "copasi/lapack/lapackwrap.h"

/**
 * Default constructor
 */
CLNAMethod::CLNAMethod(const CDataContainer * pParent,
                       const CTaskEnum::Method & methodType,
                       const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType),
  mSteadyStateResolution(1.0e-9),
  mSSStatus(CSteadyStateMethod::notFound)
{
  initializeParameter();
  initObjects();
}

CLNAMethod::CLNAMethod(const CLNAMethod & src,
                       const CDataContainer * pParent):
  CCopasiMethod(src, pParent),
  mSteadyStateResolution(src.mSteadyStateResolution),
  mSSStatus(CSteadyStateMethod::notFound)
{
  initializeParameter();
  initObjects();
}

void CLNAMethod::initObjects()
{
  CDataArray * tmp;

  tmp = new CDataArray("B matrix (reduced)", this,
                       new CMatrixInterface<CMatrix<C_FLOAT64> >(&mBMatrixReduced), true);
  tmp->setMode(CDataArray::Mode::Vector);
  tmp->setDescription("B matrix (reduced)");
  tmp->setDimensionDescription(0, "Species (reduced system)");
  tmp->setDimensionDescription(1, "Species (reduced system)");
  mBMatrixReducedAnn = tmp;

  tmp = new CDataArray("Covariance matrix (reduced)", this,
                       new CMatrixInterface<CMatrix<C_FLOAT64> >(&mCovarianceMatrixReduced), true);
  tmp->setMode(CDataArray::Mode::Vector);
  tmp->setDescription("Covariance matrix (reduced)");
  tmp->setDimensionDescription(0, "Species (reduced system)");
  tmp->setDimensionDescription(1, "Species (reduced system)");
  mCovarianceMatrixReducedAnn = tmp;

  tmp = new CDataArray("Covariance matrix", this,
                       new CMatrixInterface<CMatrix<C_FLOAT64> >(&mCovarianceMatrix), true);
  tmp->setMode(CDataArray::Mode::Vector);
  tmp->setDescription("Covariance matrix");
  tmp->setDimensionDescription(0, "Species (full system)");
  tmp->setDimensionDescription(1, "Species (full system)");
  mCovarianceMatrixAnn = tmp;
}

/**
 * Deconstructor
 */
CLNAMethod::~CLNAMethod()
{
  DESTRUCTOR_TRACE;
}

void CLNAMethod::initializeParameter()
{
  /*  CCopasiParameter *pParm;

      assertParameter("Placeholder Factor", CCopasiParameter::Type::UDOUBLE, 1.0e-009);

      if ((pParm = getParameter("LNA.PlaceholderFactor")) != NULL)
      {
      setValue("Placeholder Factor", *pParm->getValue().pUDOUBLE);
      removeParameter("LNA.PlaceholderFactor");
      }
  */
}

bool CLNAMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

void CLNAMethod::resizeAllMatrices()
{
  const CModel & Model = mpContainer->getModel();

  mBMatrixReduced.resize(mpContainer->getCountIndependentSpecies(), mpContainer->getCountIndependentSpecies());
  mBMatrixReducedAnn->resize();
  mBMatrixReducedAnn->setCopasiVector(0, Model.getMetabolitesX());
  mBMatrixReducedAnn->setCopasiVector(1, Model.getMetabolitesX());

  mCovarianceMatrixReduced.resize(mpContainer->getCountIndependentSpecies(), mpContainer->getCountIndependentSpecies());
  mCovarianceMatrixReducedAnn->resize();
  mCovarianceMatrixReducedAnn->setCopasiVector(0, Model.getMetabolitesX());
  mCovarianceMatrixReducedAnn->setCopasiVector(1, Model.getMetabolitesX());

  mCovarianceMatrix.resize(mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies(),
                           mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies());
  mCovarianceMatrixAnn->resize();
  mCovarianceMatrixAnn->setCopasiVector(0, Model.getMetabolitesX());
  mCovarianceMatrixAnn->setCopasiVector(1, Model.getMetabolitesX());
}

int CLNAMethod::calculateCovarianceMatrixReduced()
{
  // code snippet: transform something into particle space:
  // *(metabs[i]->getCompartment())->getValue()*mpModel->getQuantity2NumberFactor();

  CVectorCore< CMathReaction > & Reactions = mpContainer->getReactions();
  const CVectorCore< C_FLOAT64 > & ParticleFluxex = mpContainer->getParticleFluxes();

  //size_t numReacs = Reactions.size();

  // We need the number of independent metabolites determined by
  // reactions.
  size_t numMetabs = mpContainer->getCountIndependentSpecies();

  // calculate covariances
  // first, set BMatrix (reduced) to zero
  mBMatrixReduced.resize(numMetabs, numMetabs);
  mBMatrixReduced = 0.0;

  // second, set CovarianceMatrixReduced to zero
  mCovarianceMatrixReduced.resize(numMetabs, numMetabs);
  mCovarianceMatrixReduced = 0.0;

  // then, calculate the contribution for each reaction
  // and add these contributions to the respective mBMatrix elements
  // only consider independent metabolites determined by reactions,
  // e.g. those that contribute to the reduced stoichiometry matrix.
  // Note: This could also be computed using mRedStoi in CModel.
  //       However, then it would probably be less efficient for very
  //       big systems since mRedStoi should be sparse there.
  const CMathReaction * pReaction = Reactions.array();
  const CMathReaction * pReactionEnd = pReaction + Reactions.size();
  const C_FLOAT64 * pParticleFlux = ParticleFluxex.array();

  size_t FirstReactionSpeciesIndex = mpContainer->getCountFixedEventTargets() + 1 + mpContainer->getCountODEs();
  CMathObject * pFirstReactionSpecies = mpContainer->getMathObject(mpContainer->getState(false).array() + FirstReactionSpeciesIndex);
  CMathObject * pSpecies;

  for (; pReaction != pReactionEnd; ++pReaction, ++pParticleFlux)
    {
      const CMathReaction::Balance & Balances = pReaction->getNumberBalance();
      const CMathReaction::SpeciesBalance * pBalanceRow;
      const CMathReaction::SpeciesBalance * pBalanceColumn;
      const CMathReaction::SpeciesBalance * pBalanceEnd = Balances.array() + Balances.size();
      //C_FLOAT64 * pBMatrixReduced = mBMatrixReduced.array();

      for (pBalanceRow = Balances.array(); pBalanceRow != pBalanceEnd; ++pBalanceRow)
        {
          pSpecies = mpContainer->getMathObject(pBalanceRow->first);

          if (pSpecies->getSimulationType() == CMath::SimulationType::Independent)
            {
              size_t i = pSpecies - pFirstReactionSpecies;

              for (pBalanceColumn = Balances.array(); pBalanceColumn != pBalanceEnd; ++pBalanceColumn)
                {
                  pSpecies = mpContainer->getMathObject(pBalanceColumn->first);

                  if (pSpecies->getSimulationType() == CMath::SimulationType::Independent)
                    {
                      size_t j = pSpecies - pFirstReactionSpecies;
                      mBMatrixReduced(i, j) += *pParticleFlux * pBalanceRow->second * pBalanceColumn->second;
                    }
                }
            }
        }
    }

  // finally, solve the Lyapunov equation A*C + C*A^T + B = 0 for C
  // using the Bartels & Stewart algorithm (1972)

  // 1. (Schur) transform the Jacobian matrix A (reduced) and its transpose At

  // get the Jacobian (reduced)
  C_FLOAT64 derivationFactor = 1e-6;
  mpContainer->calculateJacobian(mJacobianReduced, derivationFactor, true);

  // copy the Jacobian (reduced) into A
  CMatrix< C_FLOAT64 > A;
  A.resize(mJacobianReduced.numRows(), mJacobianReduced.numCols());
  C_FLOAT64 * pA = A.array();
  C_FLOAT64 * pAEnd = pA + A.size();
  const C_FLOAT64 * pMatrix = mJacobianReduced.array();

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

  char jobvs = 'V'; // Schur vectors are computed
  char sort = 'N'; // Eigenvalues are not ordered
  C_INT n = (C_INT)A.numRows();
  C_INT lda = n > 1 ? n : 1;
  C_INT sdim; // output
  CVector< C_FLOAT64 > wr_A;
  wr_A.resize((size_t)n);
  CVector< C_FLOAT64 > wi_A;
  wi_A.resize((size_t)n);
  CMatrix< C_FLOAT64> vs_A; // output (unitary matrix)
  C_INT ldvs_A = n;
  vs_A.resize((size_t)ldvs_A, (size_t)ldvs_A);
  CVector< C_FLOAT64 > work = 1;
  C_INT lwork;
  C_LOGICAL * pbwork = NULL;
  C_INT info;

  // LWORK workspace query
  lwork = -1;
  dgees_(&jobvs,
         &sort,
         NULL,
         &n,
         A.array(),
         &lda,
         &sdim,
         wr_A.array(),
         wi_A.array(),
         vs_A.array(),
         &ldvs_A,
         work.array(),
         &lwork,
         pbwork,
         &info);

  if (info != 0)
    {
      // TODO(juergen): add appropriate exception message(s)!
      //      CCopasiMessage(CCopasiMessage::EXCEPTION, MCLNA + 1, -mInfo);
    }

  lwork = (C_INT) work[0];
  work.resize((size_t)lwork);

  dgees_(&jobvs,
         &sort,
         NULL,
         &n,
         A.array(), // input: matrix / output: real Schur form
         &lda,
         &sdim,
         wr_A.array(),
         wi_A.array(),
         vs_A.array(),
         &ldvs_A,
         work.array(),
         &lwork,
         pbwork,
         &info);

  if (info != 0)
    {
      // TODO(juergen): add appropriate exception message(s)!
      //      CCopasiMessage(CCopasiMessage::EXCEPTION, MCLNA + 1, -mInfo);
    }

  // now, (Schur) transform the transposed Jacobian (reduced)

  // copy the transposed Jacobian (reduced) into At
  CMatrix< C_FLOAT64 > At;
  At.resize(mJacobianReduced.numCols(), mJacobianReduced.numRows());
  const C_FLOAT64 * pJacobian = mJacobianReduced.array();
  //const C_FLOAT64 * pJacobianEnd = pJacobian + mJacobianReduced.size();

  for (size_t i = 0; i < mJacobianReduced.numRows(); ++i)
    {
      for (size_t j = 0; j < mJacobianReduced.numCols(); ++j)
        {
          C_FLOAT64 & at = At[j][i];

          at = mJacobianReduced[i][j];

          if (!std::isfinite(at) && !std::isnan(at))
            {
              if (at > 0)
                at = std::numeric_limits< C_FLOAT64 >::max();
              else
                at = - std::numeric_limits< C_FLOAT64 >::max();
            }
        }
    }

  jobvs = 'V'; // Schur vectors are computed
  sort = 'N'; // Eigenvalues are not ordered
  n = (C_INT)At.numRows();
  lda = n > 1 ? n : 1;
  //  C_INT sdim; // output
  CVector< C_FLOAT64 > wr_At;
  wr_At.resize((size_t)n);
  CVector< C_FLOAT64 > wi_At;
  wi_At.resize((size_t)n);
  CMatrix< C_FLOAT64 > vs_At; // output (unitary matrix)
  C_INT ldvs_At = n;
  vs_At.resize((size_t)ldvs_At, (size_t)ldvs_At);
  work = 1;
  //  C_INT lwork;
  pbwork = NULL;
  //  C_INT info;

  // LWORK workspace query
  lwork = -1;
  dgees_(&jobvs,
         &sort,
         NULL,
         &n,
         At.array(),
         &lda,
         &sdim,
         wr_At.array(),
         wi_At.array(),
         vs_At.array(),
         &ldvs_At,
         work.array(),
         &lwork,
         pbwork,
         &info);

  if (info != 0)
    {
      // TODO(juergen): add appropriate exception message(s)!
      //      CCopasiMessage(CCopasiMessage::EXCEPTION, MCLNA + 1, -mInfo);
    }

  lwork = (C_INT) work[0];
  work.resize((size_t)lwork);

  dgees_(&jobvs,
         &sort,
         NULL,
         &n,
         At.array(), // input: matrix / output: real Schur form
         &lda,
         &sdim,
         wr_At.array(),
         wi_At.array(),
         vs_At.array(),
         &ldvs_At,
         work.array(),
         &lwork,
         pbwork,
         &info);

  if (info != 0)
    {
      // TODO(juergen): add appropriate exception message(s)!
      //      CCopasiMessage(CCopasiMessage::EXCEPTION, MCLNA + 1, -mInfo);
    }

  // 2. transform the mBMatrixReduced B to new coordinates
  //    BMatrixReduced_transformed = (unitary At)^T * mBMatrixReduced * (unitary A);

  char transa = 'T'; // (unitary A) will be transposed
  char transb = 'N'; // mBMatrixReduced will not be transposed
  C_FLOAT64 alpha = 1.0;
  C_FLOAT64 beta = 0.0;
  CMatrix< C_FLOAT64 > D;
  C_INT ldd = n;
  D.resize((size_t)n, (size_t)n);

  dgemm_(&transa,
         &transb,
         &n,
         &n,
         &n,
         &alpha,
         vs_At.array(),
         &n,
         mBMatrixReduced.array(),
         &n,
         &beta,
         D.array(), // output: multiplied matrix
         &ldd);

  transa = 'N';
  CMatrix< C_FLOAT64 > BMatrixReduced_transformed;
  C_INT BMatrixReduced_transformed_d = n;
  BMatrixReduced_transformed.resize((size_t)n, (size_t)n);

  dgemm_(&transa,
         &transb,
         &n,
         &n,
         &n,
         &alpha,
         D.array(),
         &n,
         vs_A.array(), // (unitary At)
         &n,
         &beta,
         BMatrixReduced_transformed.array(),
         &BMatrixReduced_transformed_d);

  // 3. Solve the simplified Lyapunov (Sylvester) Equation

  char trana = 'N'; // no transpose of A
  char tranb = 'N'; // no transpose of B
  C_INT isgn = 1; // sign in the equation is "+"
  C_FLOAT64 scale; // output

  //  DTRSYL solves the real Sylvester matrix equation:
  //
  //     op(A)*X + X*op(B) = scale*C or
  //     op(A)*X - X*op(B) = scale*C,
  //
  //  where op(A) = A or A**T, and  A and B are both upper quasi-
  //  triangular. A is M-by-M and B is N-by-N; the right hand side C and
  //  the solution X are M-by-N; and scale is an output scale factor, set
  //  <= 1 to avoid overflow in X.
  dtrsyl_(&trana,
          &tranb,
          &isgn,
          &n,
          &n,
          At.array(), // Schur transform of the Jacobian (reduced)
          &n,
          A.array(), // Schur transform of the transposed Jacobian (reduced)
          &n,
          BMatrixReduced_transformed.array(), // output / input (the coordinate-transformed mBMatrix (reduced))
          &n,
          &scale,
          &info);

  if (info != 0)
    {
      // TODO(juergen): add appropriate exception message(s)!
      //      CCopasiMessage(CCopasiMessage::EXCEPTION, MCLNA + 1, -mInfo);
    }

  // 4. Calculate the original matrix C: -(unitary At)*BMatrixReduced_transformed*(unitary A)^T;

  transa = 'N';
  transb = 'N';
  alpha = -1.0;
  beta = 0.0;
  ldd = n;
  D.resize((size_t)n, (size_t)n);

  dgemm_(&transa,
         &transb,
         &n,
         &n,
         &n,
         &alpha,
         vs_At.array(),
         &n,
         BMatrixReduced_transformed.array(), // BMatrixReduced_transformed.array() holds the output of dtrsyl() now
         &n,
         &beta,
         D.array(),
         &ldd);

  transa = 'N';
  transb = 'T';
  alpha = 1.0;
  beta = 0.0;
  mCovarianceMatrixReduced.resize((size_t)n, (size_t)n);

  dgemm_(&transa,
         &transb,
         &n,
         &n,
         &n,
         &alpha,
         D.array(),
         &n,
         vs_A.array(),
         &n,
         &beta,
         mCovarianceMatrixReduced.array(),
         &n);

  return LNA_OK;
}

/**
 * Re-calculate covariances for the full system
 */
void CLNAMethod::calculateCovarianceMatrixFull()
{
  // the covariance matrix of the full system is calculated from
  // the covariance matrix of the reduced system by:
  // mL*mCovarianceMatrixReduced*mL^T, with mL the link matrix

  C_INT i;

  C_INT numIndependentMetabs = (C_INT) mpContainer->getCountIndependentSpecies();
  C_INT numDependentMetabs = (C_INT) mpContainer->getCountDependentSpecies();
  C_INT numReactionMetabs = numIndependentMetabs + numDependentMetabs;

  const CLinkMatrix & L = mpContainer->getModel().getL0();

  mL.resize((size_t)numReactionMetabs, (size_t)numIndependentMetabs);
  mL = 0.0;

  for (i = 0; i < numIndependentMetabs; i++) mL[(size_t)i][(size_t)i] = 1.0;

  memcpy(mL[numIndependentMetabs], L.array(), sizeof(C_FLOAT64) * L.size());

  CMatrix< C_FLOAT64 > D;
  D.resize((size_t)numIndependentMetabs, (size_t)numReactionMetabs);
  D = 0.0;

  // take care of different memory layouts in C and FORTRAN (e.g. BLAS routines)
  char transa = 'T';
  char transb = 'T';
  C_FLOAT64 alpha = 1.0;
  C_FLOAT64 beta = 0.0;

  dgemm_(&transa,
         &transb,
         &numReactionMetabs,
         &numIndependentMetabs,
         &numIndependentMetabs,
         &alpha,
         mL.array(),
         &numIndependentMetabs,
         mCovarianceMatrixReduced.array(),
         &numIndependentMetabs,
         &beta,
         D.array(),
         &numReactionMetabs);

  // take care of different memory layouts in C and FORTRAN (e.g. BLAS routines)
  transa = 'N';
  transb = 'N';
  alpha = 1.0;
  beta = 0.0;
  mCovarianceMatrix.resize((size_t)numReactionMetabs, (size_t)numReactionMetabs);
  mCovarianceMatrix = 0.0;

  dgemm_(&transa,
         &transb,
         &numReactionMetabs,
         &numReactionMetabs,
         &numIndependentMetabs,
         &alpha,
         D.array(),
         &numReactionMetabs,
         mL.array(),
         &numIndependentMetabs,
         &beta,
         mCovarianceMatrix.array(),
         &numReactionMetabs);
}

/**
 * the LNA entry point
 * @param status refers to the steady-state solution
 * @param res refers to the resolution
 */
int CLNAMethod::CalculateLNA()
{
  if (((mSSStatus == CSteadyStateMethod::found) || (mSSStatus == CSteadyStateMethod::foundEquilibrium)) && (mEVStatus == CLNAMethod::allNeg))
    {
      if (calculateCovarianceMatrixReduced() == LNA_OK)
        {
          calculateCovarianceMatrixFull();
          return LNA_OK;
        }
    }

  // something went wrong
  mBMatrixReduced = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mCovarianceMatrixReduced = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mCovarianceMatrix = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  return LNA_NOT_OK;
}

/**
 * Read some parameters from configuration file.
 */
C_INT32 CLNAMethod::load(CReadConfig & C_UNUSED(configBuffer))
{
  C_INT32 Fail = 0;
  /*
    if ((Fail = configBuffer.getVariable("SSMCAUnscaled", "C_INT16",
                                          (void *) & mSSReder,
                                          CReadConfig::LOOP)))
    return Fail;
  */
  return Fail;
}

bool CLNAMethod::process()
{
  return (CalculateLNA() == LNA_OK);
  // maybe, introduce additional checks here later
}

void CLNAMethod::setSteadyStateStatus(CSteadyStateMethod::ReturnCode SSStatus)
{
  mSSStatus = SSStatus;
}

void CLNAMethod::setEigenValueStatus(CLNAMethod::EVStatus status)
{
  mEVStatus = status;
}

void CLNAMethod::setSteadyStateResolution(C_FLOAT64 resolution)
{
  this->mSteadyStateResolution = resolution;
}

//virtual
bool CLNAMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CLNAProblem * pP = dynamic_cast<const CLNAProblem *>(pProblem);

  if (!pP)
    {
      //not a CLNAProblem
      CCopasiMessage(CCopasiMessage::ERROR, "Problem is not a LNA problem.");
      return false;
    }

  const CModel & Model = mpContainer->getModel();

  // Check if the model contains species that have assignments or
  // explicit ODEs.
  if (Model.getNumAssignmentMetabs() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "LNA is not applicable for a system with species assignments.");
      return false;
    }

  if (Model.getNumODEMetabs() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "LNA is not applicable for a system with explicit ODEs for species.");
      return false;
    }

  //if (Model.getCompartments().size() > 1)
  //  {
  //    CCopasiMessage(CCopasiMessage::ERROR, "LNA is not applicable for a system with more than one compartment.");
  //    return false;
  //}

  // Check if the model has a compartment with an assignment or ODE
  CDataVector< CCompartment >::const_iterator it = Model.getCompartments().begin();
  CDataVector< CCompartment >::const_iterator end = Model.getCompartments().end();

  for (; it != end; ++it)
    if (it->getStatus() != CModelEntity::Status::FIXED)
      {
        CCopasiMessage(CCopasiMessage::ERROR, "LNA is not applicable for a system with changing volumes, e.g. compartment assignments or ODEs.");
        return false;
      }

  const CDataVector< CReaction > & reacs = Model.getReactions();

  size_t numReacs = reacs.size();

  size_t i;

  for (i = 0; i < numReacs; i++) // for every reaction
    {
      // TEST isReversible() == 0
      if (reacs[i].isReversible() != 0)
        {
          CCopasiMessage(CCopasiMessage::ERROR, "At least one reaction is reversible. That means it is not possible to calculate the LNA. \nYou can use \"Tools|Convert to irreversible\" which will split the reversible reactions \n into two irreversible reactions. However you should check the kinetics afterwards.");
          return false;
        }
    }

  return true;
}
