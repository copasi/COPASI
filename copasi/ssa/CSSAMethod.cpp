/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ssa/Attic/CSSAMethod.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/09/12 15:16:20 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CSSAMethod class.
 *  Methods to conduct Stoichiometric Stability Analysis.-
 */

#include "copasi.h"

#include "blaswrap.h"
#include "clapackwrap.h"

#include "CSSATask.h"
#include "CSSAMethod.h"
#include "CSSAProblem.h"
#include "elementaryFluxModes/CExtremeCurrentCalculator.h"
#include "elementaryFluxModes/CEFMMethod.h"
#include "elementaryFluxModes/CFluxMode.h"

#include "model/CModel.h"
#include "model/CState.h"

CSSAMethod *
CSSAMethod::createSSAMethod(CCopasiMethod::SubType subType)
{
  CSSAMethod * pMethod = NULL;

  switch (subType)
    {
    case unset:
    case ssaMethod:
      pMethod = new CSSAMethod(subType);
      break;

    default:
      fatalError();
    }

  return pMethod;
}

/**
 *  Default constructor.
 */
CSSAMethod::CSSAMethod(CCopasiMethod::SubType subType,
                       const CCopasiContainer * pParent):
    CCopasiMethod(CCopasiTask::ssa, subType, pParent),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CSSAMethod &" src
 */
CSSAMethod::CSSAMethod(const CSSAMethod & src,
                       const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CSSAMethod::~CSSAMethod()
{DESTRUCTOR_TRACE;}

bool CSSAMethod::initialize(CSSAProblem* problem)
{
  mpProblem = problem;
  mpModel = mpProblem->getModel();
  mpTask = dynamic_cast< CSSATask * >(getObjectParent());

  buildBackwardReactionVector();

  mNumReactions = mIsBackwardReaction.size();

  return true;
}

/**
 *  Set a pointer to the problem.
 *  This method is used by CSteadyState
 *  @param "CSteadyStateProblem *" problem
 */

/**
 * This instructs the method to calculate a the steady state
 * starting with the initialState given.
 * The steady state is returned in the object pointed to by steadyState.
 * @param CState * steadyState
 * @param const CState * initialState
 * @param C_FLOAT64 * jacobian
 * @param CEigen * eigenValues
 * @return CSSAMethod::ReturnCode returnCode
 */
bool CSSAMethod::process(CProcessReport * handler)
{
  return false;
}

bool
CSSAMethod::calculate()
{
  if (!mpModel) return false;

  //initialize matrices for calculation;
  if (mpModel->compileIfNecessary())
    {
      buildStoichiometry();
      buildKineticMatrix();
      buildExtremeCurrents();
    }
  else
    return false;

  if (!testForMixingStability())
    return false;

  return true;
}

bool
CSSAMethod::isMixingStable(CVector< C_FLOAT64 > &)
{return true;}

bool
CSSAMethod::testForMixingStability()
{
  decomposeJacobian();

  C_INT32 numECs = mExtremeCurrents.size();

  C_INT32 ijmax = mTransformedSubJacobians[0].numRows();

  mNonMixingStableECs.clear();

  C_FLOAT64 outarray[ijmax*ijmax];
  memset(outarray, 0, ijmax*ijmax*sizeof(C_FLOAT64));

  for (int ecIndex = 0; ecIndex < numECs; ++ecIndex)
    {
      C_FLOAT64 *inarray = mTransformedSubJacobians[ecIndex].array();

      // add matrix and its extremeCurrent - upper triangle only
      for (int i = 0; i < ijmax; ++i)
        for (int j = i; j < ijmax; ++j)
          outarray[i + j*ijmax] = inarray[i + j * ijmax] + inarray[j + i * ijmax];

      // get the eigenvalues:
      // input to dsyev_()
      char jobz = 'N';
      char uplo = 'U';
      C_INT32 n = ijmax;
      C_FLOAT64 *A = outarray;
      C_INT32 lda = ijmax;
      C_INT32 lwork = 64 * ijmax;
      // dsyev_() output
      C_FLOAT64 eigenvalues[ijmax];
      C_FLOAT64 work[lwork];
      C_INT32 info;

      dsyev_(&jobz, &uplo, &n, A, &lda, eigenvalues, work, &lwork, &info);

      if (info)
        return false;  // maybe raise an exception here, to discriminate from the sane case

#ifdef COPASI_DEBUG
      std::cout << "eigenvalues:" << std::endl;
      for (int i = 0; i < ijmax; ++i)
        std::cout << eigenvalues[i] << "  " << std::endl;
      std::cout << std::endl;
#endif //COPASI_DEBUG

      for (int i = 0; i < ijmax; ++i)
        {
          if (eigenvalues[i] > 0)
            {
              mNonMixingStableECs.push_back(ecIndex);
              break;
            }
        }
    }

#ifdef COPASI_DEBUG
  std::cout << "There is/are " << mNonMixingStableECs.size()
  << " extreme current(s) not mixing stable!" << std::endl;
#endif //COPASI_DEBUG

  return true;
}

bool
CSSAMethod::decomposeJacobian()
{
  mTransformedSubJacobians.clear();

  // parameters for the double matrix multiplication with dgemm_
  char cN = 'N';                         // don't transpose matrices
  C_INT m = mStoichiometry.numRows();    // the leading dimension of the Stoi.M. and of the resulting M.
  C_INT n = mStoichiometry.numCols();    // the dimensions of matrix diagE, also used as 'k'.

  C_FLOAT64 alpha = 1.;
  C_FLOAT64 beta = 0.;

  CMatrix< C_FLOAT64 > product;
  product.resize(m, m);

  std::vector< CVector<C_FLOAT64> >::iterator iter;
  for (iter = mExtremeCurrents.begin(); iter != mExtremeCurrents.end(); ++iter)
    {
      CMatrix<C_FLOAT64> diagE = diag(*iter);

      // compute N*Ei*kappa^T:
      // As the representation of the matrices in their arrays is in
      // transposed (mathematical) order, we compute kappa*Ei*N^T,
      // which corresponds to
      // (mTransposedKineticMatrix*diagE)*mStoichiometry
      C_FLOAT64 dummy[m*n];
      dgemm_(&cN, &cN,
              &m, &n, &n, &alpha,
              mTransposedKineticMatrix.array(), &m ,
              diagE.array(), &n,
              &beta, dummy, &m);
      dgemm_(&cN, &cN,
              &m, &m, &n, &alpha,
              dummy, &m,
              mStoichiometry.array(), &n,
              &beta, product.array(), &m);

      mTransformedSubJacobians.push_back(product);
    }

  return true;
}

void
CSSAMethod::buildBackwardReactionVector()
{
  mIsBackwardReaction.clear();

  CCopasiVectorNS< CReaction > reactions = mpModel->getReactions();

  // take reversible reactions into account:
  CCopasiVectorNS< CReaction >::iterator iter;
  for (iter = reactions.begin(); iter != reactions.end(); ++iter)
    {
      mIsBackwardReaction.push_back(false);
      if ((*iter)->isReversible())
        mIsBackwardReaction.push_back(true);
    }
}

bool
CSSAMethod::buildStoichiometry()
{
  if (!mpModel) return false;

  CMatrix<C_FLOAT64> stoichiometry = mpModel->getRedStoi();

  //rebuild the stoichiometric matrix with reversible reactions divided into two.

#ifdef COPASI_DEBUG
  std::cout << "stoichiometry: " << std::endl << stoichiometry << std::endl << std::endl;
#endif // COPASI_DEBUG

  CCopasiVectorNS< CReaction > reactions = mpModel->getReactions();

  // build the _transposed_ of stoichiometry, with expanded reversible reactions
  int numRows = stoichiometry.numRows();
  int numCols = mNumReactions;

#ifdef COPASI_DEBUG
  std::cout << "new matrix " << std::endl;
#endif // COPASI_DEBUG

  mStoichiometry.resize(numRows, numCols);
  memset(mStoichiometry.array(), 0, numRows*numCols*sizeof(C_FLOAT64));

  int j = -1;
  uint duplicates = 0;
  std::vector<bool>::iterator iter;
  for (iter = mIsBackwardReaction.begin(); iter != mIsBackwardReaction.end(); ++iter)
    {
      std::vector< C_FLOAT64 > row;
      // if next element in mIsBackwardReaction == true:
      if (*(iter))
        {
          ++duplicates;
          for (uint i = 0; i < stoichiometry.numRows(); ++i)
            {
              mStoichiometry(i, j + duplicates) = -stoichiometry(i, j);
              std::cout << -stoichiometry(i, j) << "  ";
            }
          std::cout << std::endl;
          continue;
        }

      ++j;

      for (uint i = 0; i < stoichiometry.numRows(); ++i)
        {
          mStoichiometry(i, j + duplicates) = stoichiometry(i, j);
          std::cout << stoichiometry(i, j) << "  ";
        }
      std::cout << std::endl;
    }
#ifdef COPASI_DEBUG
  std::cout << std::endl << std::endl << "new stoichiometry:" << std::endl << mStoichiometry << std::endl;
#endif

  return true;
}

bool
CSSAMethod::buildKineticMatrix()
{
  if (!mpModel) return false;

  CCopasiVectorNS< CReaction > & reactions = mpModel->getReactions();

  C_FLOAT64 num_metabolites = mpModel->getMetabolites().size();

  C_FLOAT64 num_reactions = mNumReactions;

  mTransposedKineticMatrix.resize((C_INT64)num_reactions, (C_INT64)num_metabolites);
  memset(mTransposedKineticMatrix.array(), 0, (int)(num_metabolites*num_reactions*sizeof(C_FLOAT64)));

  int ireac = 0, duplicates = 0;
  std::vector<bool>::iterator biter;
  for (biter = mIsBackwardReaction.begin(); biter != mIsBackwardReaction.end(); ++biter)
    {
      CCopasiVector< CChemEqElement > substrates;

      if (*biter)
        {
          ++duplicates;
          substrates = reactions[ireac - duplicates]->getChemEq().getProducts();
        }
      else
        substrates = reactions[ireac - duplicates]->getChemEq().getSubstrates();

      CCopasiVector< CMetab > & metabOrder = mpModel->getMetabolites();

      for (uint jsubst = 0; jsubst < substrates.size(); ++jsubst)
        {
          CCopasiVector< CMetab >::iterator found = find(metabOrder.begin(),
              metabOrder.end(),
              substrates[jsubst]->getMetabolite());
          if (found == metabOrder.end()) return false;
          int kmetab = std::distance(metabOrder.begin(), found);
          mTransposedKineticMatrix[ireac][kmetab] = substrates[jsubst]->getMultiplicity();
        }

      ++ireac;
    }

#ifdef COPASI_DEBUG
  std::cout << "transposed kinetic matrix: " << std::endl
  << mTransposedKineticMatrix << std::endl
  << std::endl;
#endif // COPASI_DEBUG

  return true;
}

bool
CSSAMethod::buildExtremeCurrents()
{
  CExtremeCurrentCalculator *algorithm =
    dynamic_cast< CExtremeCurrentCalculator * >(CEFMMethod::createMethod(CCopasiMethod::ExtremeCurrents));
  mpTask->add(algorithm);

  mExtremeCurrents.clear();
  // break down mStoichiometry into a std::vector< std::vector< C_FLOAT64 > >!!

  algorithm->calculate();
  std::vector< CFluxMode > fluxmodes = algorithm->getFluxModes();

  CVector< C_FLOAT64 > extremecurrent;
  extremecurrent.resize(mNumReactions);

  std::vector< CFluxMode >::iterator iter;
  for (iter = fluxmodes.begin(); iter != fluxmodes.end(); ++iter)
    {
      memset(extremecurrent.array(), 0, extremecurrent.size()*sizeof(C_FLOAT64));
      for (uint i = 0; i < iter->size(); ++i)
        {
          extremecurrent[iter->getReactionIndex(i)] = iter->getMultiplier(i);
        }
      std::cout << "extreme current #" << distance(fluxmodes.begin(), iter) << std::endl
      << "  " << extremecurrent << std::endl << std::endl;
      mExtremeCurrents.push_back(extremecurrent);
    }
  return true;
}

//virtual
bool CSSAMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CSSAProblem * pP = dynamic_cast<const CSSAProblem *>(pProblem);
  if (!pP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not a stoichiometric stability analysis problem.");
      return false;
    }

  return true;
}
