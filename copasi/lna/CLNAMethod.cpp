// Copyright (C) 2011 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <cmath>
#include <limits>

#include "copasi.h"
#include "model/CModel.h"
#include "utilities/utility.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CReadConfig.h"
#include "CLNAMethod.h"
#include "CLNAProblem.h"

#include "lapack/blaswrap.h"
#include "lapack/lapackwrap.h"

// static
CLNAMethod * CLNAMethod::createMethod(CCopasiMethod::SubType /* subType */)
{
  return new CLNAMethod();
}

/**
 * Default constructor
 */
CLNAMethod::CLNAMethod(const CCopasiContainer* pParent):
  CCopasiMethod(CCopasiTask::lna, CCopasiMethod::linearNoiseApproximation, pParent),
  mpModel(NULL),
  mSteadyStateResolution(1.0e-9),
  mSSStatus(CSteadyStateMethod::notFound)
{
  initializeParameter();
  initObjects();
}

CLNAMethod::CLNAMethod(const CLNAMethod & src,
                       const CCopasiContainer * pParent):
  CCopasiMethod(src, pParent),
  mpModel(NULL),
  mSteadyStateResolution(src.mSteadyStateResolution),
  mSSStatus(CSteadyStateMethod::notFound)
{
  initializeParameter();
  initObjects();
}

void CLNAMethod::initObjects()
{
  CArrayAnnotation * tmp;

  tmp = new CArrayAnnotation("B matrix (reduced)", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mBMatrixReduced), true);
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("B matrix (reduced)");
  tmp->setDimensionDescription(0, "Species (reduced system)");
  tmp->setDimensionDescription(1, "Species (reduced system)");
  mBMatrixReducedAnn = tmp;

  tmp = new CArrayAnnotation("Covariance matrix (reduced)", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mCovarianceMatrixReduced), true);
  tmp->setMode(CArrayAnnotation::VECTOR);
  tmp->setDescription("Covariance matrix (reduced)");
  tmp->setDimensionDescription(0, "Species (reduced system)");
  tmp->setDimensionDescription(1, "Species (reduced system)");
  mCovarianceMatrixReducedAnn = tmp;

  tmp = new CArrayAnnotation("Covariance matrix", this,
                             new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mCovarianceMatrix), true);
  tmp->setMode(CArrayAnnotation::VECTOR);
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

      assertParameter("Placeholder Factor", CCopasiParameter::UDOUBLE, 1.0e-009);

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
  if (!mpModel) return;

  mBMatrixReduced.resize(mpModel->getNumIndependentReactionMetabs(), mpModel->getNumIndependentReactionMetabs());
  mBMatrixReducedAnn->resize();
  mBMatrixReducedAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  mBMatrixReducedAnn->setCopasiVector(1, &mpModel->getMetabolitesX());

  mCovarianceMatrixReduced.resize(mpModel->getNumIndependentReactionMetabs(), mpModel->getNumIndependentReactionMetabs());
  mCovarianceMatrixReducedAnn->resize();
  mCovarianceMatrixReducedAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  mCovarianceMatrixReducedAnn->setCopasiVector(1, &mpModel->getMetabolitesX());

  mCovarianceMatrix.resize(mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs(), mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs());
  mCovarianceMatrixAnn->resize();
  mCovarianceMatrixAnn->setCopasiVector(0, &mpModel->getMetabolitesX());
  mCovarianceMatrixAnn->setCopasiVector(1, &mpModel->getMetabolitesX());
}

int CLNAMethod::calculateCovarianceMatrixReduced()
{
  // code snippet: transform something into particle space:
  // *(metabs[i]->getCompartment())->getValue()*mpModel->getQuantity2NumberFactor();

  assert(mpModel);

  CCopasiVector< CMetab > & metabs = mpModel->getMetabolitesX();
  CCopasiVector< CReaction > & reacs = mpModel->getReactions();
  const CVector< C_FLOAT64 > & ParticleFlux = mpModel->getParticleFlux();

  size_t numReacs = reacs.size();

  // We need the number of independent metabolites determined by
  // reactions.
  size_t numMetabs = mpModel->getNumIndependentReactionMetabs();

  size_t i, j, k;
  const CMetab * pMetabolite;
  C_FLOAT64 balance_i, balance_j, BContrib;

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
  for (k = 0; k < numReacs; k++)
    {
      const CCopasiVector <CChemEqElement> & Balances =
        reacs[k]->getChemEq().getBalances();

      CCopasiVector<CChemEqElement>::const_iterator itRow;
      CCopasiVector<CChemEqElement>::const_iterator itColumn;
      CCopasiVector<CChemEqElement>::const_iterator itEnd = Balances.end();

      for (itRow = Balances.begin(); itRow != itEnd; ++itRow)
        {
          pMetabolite = (*itRow)->getMetabolite();
          i = metabs.getIndex(pMetabolite);

          if (i < numMetabs)
            {
              balance_i = (*itRow)->getMultiplicity();

              // This check is no longer needed since we check the index for validity, i.e. we are assured to have an independent metabolite
              if ((pMetabolite->getStatus() != CModelEntity::REACTIONS) || (pMetabolite->isDependent())) balance_i = 0.0;

              for (itColumn = Balances.begin(); itColumn != itEnd; ++itColumn)
                {
                  pMetabolite = (*itColumn)->getMetabolite();
                  j = metabs.getIndex(pMetabolite);

                  if (j < numMetabs)
                    {
                      balance_j = (*itColumn)->getMultiplicity();

                      // This check is no longer needed since we check the index for validity, i.e. we are assured to have an independent metabolite
                      if ((pMetabolite->getStatus() != CModelEntity::REACTIONS) || (pMetabolite->isDependent())) balance_j = 0.0;

                      BContrib = ParticleFlux[k] * balance_i * balance_j;
                      mBMatrixReduced[i][j] += BContrib;
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
  C_FLOAT64 resolution = 1e-12;
  mpModel->calculateJacobianX(mJacobianReduced, derivationFactor, resolution);

  // copy the Jacobian (reduced) into A
  CMatrix< C_FLOAT64 > A;
  A.resize(mJacobianReduced.numRows(), mJacobianReduced.numCols());
  C_FLOAT64 * pA = A.array();
  C_FLOAT64 * pAEnd = pA + A.size();
  const C_FLOAT64 * pMatrix = mJacobianReduced.array();

  for (; pA != pAEnd; ++pA, ++pMatrix)
    {
      *pA = *pMatrix;

      if (!finite(*pA) && !isnan(*pA))
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

  for (i = 0; i < mJacobianReduced.numRows(); i++)
    {
      for (j = 0; j < mJacobianReduced.numCols(); j++)
        {
          At[j][i] = mJacobianReduced[i][j];

          if (!finite(At[j][i]) && !isnan(At[j][i]))
            {
              if (At[j][i] > 0)
                At[j][i] = std::numeric_limits< C_FLOAT64 >::max();
              else
                At[j][i] = - std::numeric_limits< C_FLOAT64 >::max();
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

  C_INT i, j;

  C_INT numIndependentMetabs = (C_INT)mpModel->getNumIndependentReactionMetabs();
  C_INT numReactionMetabs = (C_INT)mpModel->getNumIndependentReactionMetabs() + mpModel->getNumDependentReactionMetabs();
  C_INT numDependentMetabs = numReactionMetabs - numIndependentMetabs;

  CMatrix<C_FLOAT64> mL0;
  mL0 = mpModel->getL0();
  mL.resize((size_t)numReactionMetabs, (size_t)numIndependentMetabs);
  mL = 0.0;

  for (i = 0; i < numIndependentMetabs; i++) mL[(size_t)i][(size_t)i] = 1.0;

  for (i = 0; i < numDependentMetabs; i++)
    for (j = 0; j < numIndependentMetabs; j++)
      mL[(size_t)i + (size_t)numIndependentMetabs][(size_t)j] = mL0[(size_t)i][(size_t)j];

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
 * Set the Model
 */
void CLNAMethod::setModel(CModel* model)
{
  mpModel = model;
}

/**
 * the LNA entry point
 * @param status refers to the steady-state solution
 * @param res refers to the resolution
 */
int CLNAMethod::CalculateLNA()
{
  assert(mpModel);

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

const CModel* CLNAMethod::getModel() const
{
  return this->mpModel;
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

  CModel * pModel = pP->getModel();

  if (pModel == NULL)
    return false;

  // Check if the model contains species that have assignments or
  // explicit ODEs.
  if (pModel->getNumAssignmentMetabs() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "LNA is not applicable for a system with species assignments.");
      return false;
    }

  if (pModel->getNumODEMetabs() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "LNA is not applicable for a system with explicit ODEs for species.");
      return false;
    }

  //if (pModel->getCompartments().size() > 1)
  //  {
  //    CCopasiMessage(CCopasiMessage::ERROR, "LNA is not applicable for a system with more than one compartment.");
  //    return false;
  //}

  // Check if the model has a compartment with an assignment or ODE
  CCopasiVector< CCompartment >::const_iterator it = pModel->getCompartments().begin();
  CCopasiVector< CCompartment >::const_iterator end = pModel->getCompartments().end();

  for (; it != end; ++it)
    if ((*it)->getStatus() != CModelEntity::FIXED)
      {
        CCopasiMessage(CCopasiMessage::ERROR, "LNA is not applicable for a system with changing volumes, e.g. compartment assignments or ODEs.");
        return false;
      }

  CCopasiVector< CReaction > & reacs = pModel->getReactions();
  size_t numReacs = reacs.size();
  size_t i;

  for (i = 0; i < numReacs; i++) // for every reaction
    {
      // TEST isReversible() == 0
      if (reacs[i]->isReversible() != 0)
        {
          CCopasiMessage(CCopasiMessage::ERROR, "At least one reaction is reversible. That means it is not possible to calculate the LNA. \nYou can use \"Tools|Convert to irreversible\" which will split the reversible reactions \n into two irreversible reactions. However you should check the kinetics afterwards.");
          return false;
        }
    }

  return true;
}
