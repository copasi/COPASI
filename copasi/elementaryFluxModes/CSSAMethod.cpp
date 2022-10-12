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

/**
 *  CSSAMethod class.
 *  Methods to conduct Stoichiometric Stability Analysis.-
 */

#include "copasi/copasi.h"

#include "copasi/lapack/blaswrap.h"
#include "copasi/lapack/lapackwrap.h"

#include "copasi/elementaryFluxModes/CSSAMethod.h"
#include "copasi/elementaryFluxModes/CEFMTask.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/elementaryFluxModes/CEFMMethod.h"
#include "copasi/elementaryFluxModes/CFluxMode.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/utilities/CProcessReport.h"

/**
 *  Copy constructor.
 *  @param "const CSSAMethod &" src
 */
CSSAMethod::CSSAMethod(const CSSAMethod & src,
                       const CDataContainer * pParent):
  CEFMAlgorithm(src, pParent)
{}

CSSAMethod::CSSAMethod(const CDataContainer * pParent) :
  CEFMAlgorithm(CCopasiMethod::stoichiometricStabilityAnalysis, pParent)
{}

// taken from CEFMAlgorithm, modified to make reactions reversible, implicitely,
//  i.e. without changing the model itself.
bool CSSAMethod::initialize()
{
  CEFMTask * pTask = dynamic_cast< CEFMTask *>(getObjectParent());

  if (pTask == NULL) return false;

  mpModel = pTask->getProblem()->getModel();

  if (mpModel == NULL) return false;

  mFluxModes.clear();
  mReactions.cleanup();

  /* ModelStoi is the transpose of the models stoichiometry matrix */
  const CTransposeView< CMatrix< C_FLOAT64 > > ModelStoi(mpModel->getRedStoi());

  unsigned C_INT32 row, numRows = ModelStoi.numRows();
  unsigned C_INT32 col, numCols = ModelStoi.numCols();

  /* Get the reactions from the model */
  /* Note: We have as many reactions as we have rows in ModelStoi */
  CDataVectorNS < CReaction > & Reaction = mpModel->getReactions();

  /* Reversible reaction counter */
  mReversible = 0;

  for (row = 0; row < numRows; row++)
    {
      if (Reaction[row]->isReversible())
        mReversible++;
    }

  unsigned C_INT32 numOrigRows = numRows;
  numRows += mReversible;
  mNumReactions = numRows;

  mReversible = 0;
  /* Size the stoichiometry matrix passed to the algorithm */
  mStoi.resize(numRows);
  std::vector< std::vector< C_FLOAT64 > >::iterator it = mStoi.begin();
  std::vector< std::vector< C_FLOAT64 > >::iterator end = mStoi.end();

  for (; it != end; ++it)
    it->resize(numCols);

  /* Vector to keep track of the rearrangements necessary to put the */
  /* reversible reactions to the top of stoichiometry matrix */
  mReorderedReactions.resize(numRows);
  mIsBackwardReaction.resize(numRows);

  unsigned C_INT32 Insert;
  unsigned C_INT32 InsertReversible = 0;
  unsigned C_INT32 InsertIrreversible = numRows - 1;

  /* Build the transpose of the stoichiometry matrix, */

  /* sort reversible reactions to the top, count them */

  /* and keep track of the rearrangement */

  //for (row = 0; row < numOrigRows; row++)
  for (row = 0; row < numOrigRows; row++)
    {
      if (Reaction[row]->isReversible())
        {
          Insert = InsertReversible++;
          mIsBackwardReaction[Insert] = true;

          mReversible++;
        }
      else
        {
          Insert = InsertIrreversible--;
          mIsBackwardReaction[Insert] = false;
        }

      mReorderedReactions[Insert] = Reaction[row];

      for (col = 0; col < numCols; col++)
        {
          mStoi[Insert][col] = ModelStoi(row, col);

          if (Reaction[row]->isReversible())
            mStoi[InsertReversible - 1][col] = - ModelStoi(row, col);
        }
    }

  mStep = 0;
  mMaxStep = numCols;

  if (mProcessReport)
    mhSteps =
      mProcessReport->addItem("Current Step",
                              CCopasiParameter::Type::UINT,
                              & mStep,
                              & mMaxStep);

  return true;
}

bool CSSAMethod::process(CProcessReportLevel *)
{
  return false;
}

bool
CSSAMethod::calculate()
{
  if (!initialize())
    {
      if (mProcessReport)
        mProcessReport->finishItem(mhSteps);

      return false;
    }

  if (!mpModel)
    {
      if (mProcessReport)
        mProcessReport->finishItem(mhSteps);

      return false;
    }

  //initialize matrices for calculation;
  //  if (mpModel->compileIfNecessary(NULL))
  //    {
  buildStoichiometry();
  buildKineticMatrix();
  buildExtremeCurrents();
  //}
  //  else
  //    return false;

  if (!testForMixingStability())
    {
      if (mProcessReport)
        mProcessReport->finishItem(mhSteps);

      return false;
    }

  if (mProcessReport)
    mProcessReport->finishItem(mhSteps);

  return true;
}

TriLogic
CSSAMethod::isMixingStable(int indexEC)
{return mIsMixingStable[indexEC];}

bool
CSSAMethod::isReactionReversed(int index) const
{return mIsBackwardReaction[index];}

bool
CSSAMethod::testForMixingStability()
{
  decomposeJacobian();

  C_INT32 numECs = mExtremeCurrents.size();

  C_INT32 ijmax = mTransformedSubJacobians[0].numRows();

  mIsMixingStable.clear();

  C_FLOAT64 outarray[ijmax * ijmax];
  memset(outarray, 0, ijmax * ijmax * sizeof(C_FLOAT64));

  for (int ecIndex = 0; ecIndex < numECs; ++ecIndex)
    {
      C_FLOAT64 *inarray = mTransformedSubJacobians[ecIndex].array();

      // add matrix and its extremeCurrent - upper triangle only
      for (int i = 0; i < ijmax; ++i)
        for (int j = i; j < ijmax; ++j)
          outarray[i + j * ijmax] = inarray[i + j * ijmax] + inarray[j + i * ijmax];

      // get the eigenvalues AND eigenvectors:
      // input to dsyev_()
      char jobz = 'V';
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

      CVector<C_FLOAT64> EC = mExtremeCurrents[ecIndex];

      // set the state to 'stable' (1 - stable; 0 - unknown; -1 - not mixing stable)
      TriLogic state = TriTrue;

      int partMetabs[ijmax];
      memset(&partMetabs, 0, ijmax * sizeof(int));

      for (int j = 0; j < EC.size(); ++j)
        {
          if (EC[j])
            {
              // if one reaction's kinetic function is not Mass Action Law,
              //  this method is not valid and we can say nothing definite
              //  about the stability of this EC.
              std::string type = mReorderedReactions[j]->getFunction()->getObjectName();

              if (type.find("Mass action") == std::string::npos &&
                  type.find("Constant flux") == std::string::npos)
                {
                  state = TriUnspecified;
                  break;
                }

              for (int i = 0; i < ijmax; ++i)
                {
                  if (mStoi[j][i])
                    {
                      partMetabs[i] = 1;
                      break;
                    }
                }
            }
        }

      if (state == TriTrue)
        {
          // eigenvalues are sorted in rising order, and if the last ev is
          //   not positive, we have still to look after zero evs.
          if (eigenvalues[ijmax - 1] > 0)
            state = TriFalse;
          else
            {
              int zeroes = 0;

              for (int i = 0; i < ijmax && state == 1; ++i)
                {
                  // only count zero eigenvals if the eigenvector contains a reaction
                  //  that is participating in this extreme current.
                  if (eigenvalues[i] == 0)
                    {
                      for (int j = 0; j < ijmax; ++ j)
                        if (partMetabs[j] && outarray[i * ijmax + j])
                          if (++zeroes)
                            break;

                      if (zeroes == 2)
                        state = TriFalse;
                    }
                }
            }
        }

      mIsMixingStable.push_back(state);
    }

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
      C_FLOAT64 dummy[m * n];
      dgemm_(&cN, &cN,
             &m, &n, &n, &alpha,
             mTransposedKineticMatrix.array(), &m,
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

bool
CSSAMethod::buildStoichiometry()
{
  if (!mpModel) return false;

  //rebuild the stoichiometric matrix with reversible reactions divided into two.

  // build the _transposed_ of stoichiometry, with expanded reversible reactions
  int numRows = mStoi[0].size();
  int numCols = mStoi.size();

  mStoichiometry.resize(numRows, numCols);
  memset(mStoichiometry.array(), 0, numRows * numCols * sizeof(C_FLOAT64));

  for (int i = 0; i < numRows; ++i)
    for (int j = 0; j < numCols; ++j)
      mStoichiometry(i, j) = mStoi[j][i];

  return true;
}

bool
CSSAMethod::buildKineticMatrix()
{
  if (!mpModel) return false;

  C_FLOAT64 num_metabolites = mpModel->getNumIndependentReactionMetabs();

  C_FLOAT64 num_reactions = mNumReactions;

  mTransposedKineticMatrix.resize((C_INT64)num_reactions, (C_INT64)num_metabolites);
  memset(mTransposedKineticMatrix.array(), 0, (int)(num_metabolites * num_reactions * sizeof(C_FLOAT64)));

  CDataVector< CMetab > & metabOrder = mpModel->getMetabolitesX();

  for (int ireac = 0; ireac < mIsBackwardReaction.size(); ++ireac)
    {
      CDataVector< CChemEqElement > substrates;

      if (mIsBackwardReaction[ireac])
        substrates = mReorderedReactions[ireac]->getChemEq().getProducts();
      else
        substrates = mReorderedReactions[ireac]->getChemEq().getSubstrates();

      for (int jsubst = 0; jsubst < substrates.size(); ++jsubst)
        {
          CDataVector< CMetab >::iterator found = find(metabOrder.begin(),
                                                  metabOrder.end(),
                                                  substrates[jsubst]->getMetabolite());

          if ((*found)->isDependent()) continue;

          int kmetab = std::distance(metabOrder.begin(), found);
          mTransposedKineticMatrix[ireac][kmetab] = substrates[jsubst]->getMultiplicity();
        }
    }

  return true;
}

bool
CSSAMethod::buildExtremeCurrents()
{
  mExtremeCurrents.clear();

  calculateFluxModes();

  std::vector< CFluxMode > fluxmodes = getFluxModes();

  CVector< C_FLOAT64 > extremecurrent;
  extremecurrent.resize(mNumReactions);

  std::vector< CFluxMode >::iterator iter;

  for (iter = fluxmodes.begin(); iter != fluxmodes.end(); ++iter)
    {
      memset(extremecurrent.array(), 0, extremecurrent.size()*sizeof(C_FLOAT64));
      unsigned C_INT32 i;

      for (i = 0; i < iter->size(); ++i)
        {
          extremecurrent[iter->getReactionIndex(i)] = iter->getMultiplier(i);
        }
    }

  return true;
}
