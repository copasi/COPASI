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

#include <stdlib.h>
#include <cmath>

#include "copasi/copasi.h"

#include "CBitPatternMethod.h"
#include "CEFMProblem.h"
#include "CEFMTask.h"
#include "CStepMatrix.h"
#include "CBitPatternTree.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CChemEqInterface.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/core/CDataObjectReference.h"

#include "copasi/lapack/blaswrap.h"
#include "copasi/lapack/lapackwrap.h"

#define DEBUG_MATRIX

CBitPatternMethod::CBitPatternMethod(const CDataContainer * pParent,
                                     const CTaskEnum::Method & methodType,
                                     const CTaskEnum::Task & taskType):
  CEFMMethod(pParent, methodType, taskType),
  mpModel(NULL),
  mProgressCounter(0),
  mProgressCounterMax(0),
  mhProgressCounter(0),
  mProgressCounter2(0),
  mProgressCounter2Max(0),
  mhProgressCounter2(0),
  mReactionForward(),
  mReactionPivot(0),
  mExpandedStoiTranspose(0, 0),
  mpStepMatrix(NULL),
  mMinimumSetSize(0),
  mStep(0),
  mContinueCombination(true)
{
  initObjects();
}

CBitPatternMethod::CBitPatternMethod(const CBitPatternMethod & src,
                                     const CDataContainer * pParent):
  CEFMMethod(src, pParent),
  mpModel(src.mpModel),
  mProgressCounter(src.mProgressCounter),
  mProgressCounterMax(src.mProgressCounterMax),
  mhProgressCounter(src.mhProgressCounter),
  mProgressCounter2(src.mProgressCounter2),
  mProgressCounter2Max(src.mProgressCounter2Max),
  mhProgressCounter2(src.mhProgressCounter2),
  mReactionForward(src.mReactionForward),
  mReactionPivot(src.mReactionPivot),
  mExpandedStoiTranspose(src.mExpandedStoiTranspose),
  mpStepMatrix(src.mpStepMatrix),
  mMinimumSetSize(src.mMinimumSetSize),
  mStep(src.mStep),
  mContinueCombination(src.mContinueCombination)
{
  initObjects();
}

CBitPatternMethod::~CBitPatternMethod()
{
}

void CBitPatternMethod::initObjects()
{
  addObjectReference("Current Step", mProgressCounter, CDataObject::ValueInt);
}

bool CBitPatternMethod::initialize()
{
  if (!CEFMMethod::initialize())
    {
      return false;
    }

  pdelete(mpStepMatrix);
  mReactionForward.clear();

  mContinueCombination = true;

  CEFMTask * pTask = dynamic_cast< CEFMTask *>(getObjectParent());

  if (pTask == NULL) return false;

  mpModel = &mpContainer->getModel();

  if (mpModel == NULL) return false;

  // We first build the kernel matrix
  CMatrix< C_INT64 > KernelMatrix;
  buildKernelMatrix(KernelMatrix);

  mMinimumSetSize = KernelMatrix.numCols() - 2;

  std::stack< CStepMatrixColumn * > KernelStack;
  CStepMatrixColumn * KernelCol;

  for (unsigned int col = 0; col < KernelMatrix.numCols(); col++)
    {
      KernelCol = new CStepMatrixColumn(KernelMatrix.numRows());

      for (unsigned int row = 0; row < KernelMatrix.numRows(); row++)
        {
          KernelCol->push_front(KernelMatrix(row, col));
        }

      KernelStack.push(KernelCol);
    }

  // Now we create the initial step matrix
  mpStepMatrix = new CStepMatrix(KernelMatrix);
  /*mpStepMatrix = new CStepMatrix(KernelMatrix.numRows());
  buildFluxModeMatrix(mpStepMatrix, KernelStack);

  DebugFile << *mpStepMatrix << std::endl;*/

  /*
  mpStepMatrix = FluxModeMatrix;
  mpStepMatrix.convertMatrix();
  */

  //mpStepMatrix = new CStepMatrix(KernelMatrix);

  mProgressCounter = 0;
  mProgressCounterMax = (unsigned C_INT32) mpStepMatrix->getNumUnconvertedRows();

  if (mProcessReport)
    mhProgressCounter =
      mProcessReport.addItem("Current Step",
                             mProgressCounter,
                             & mProgressCounterMax);

  return true;
}

bool CBitPatternMethod::calculate()
{
  bool Continue = true;

  if (!initialize())
    {
      if (mProcessReport)
        mProcessReport.finishItem(mhProgressCounter);

      return false;
    }

  while (mpStepMatrix->getNumUnconvertedRows() > 0 &&
         Continue)
    {
      mStep = mpStepMatrix->getFirstUnconvertedRow();

      std::vector< CStepMatrixColumn * > PositiveColumns;
      std::vector< CStepMatrixColumn * > NegativeColumns;
      std::vector< CStepMatrixColumn * > NullColumns;

      if (mpStepMatrix->splitColumns(PositiveColumns,
                                     NegativeColumns,
                                     NullColumns))
        {
          // Process each step.
          // Iterate over all combinations and add/remove columns to the step matrix
          mProgressCounter2 = 0;
          mProgressCounter2Max = (unsigned C_INT32)(PositiveColumns.size() * NegativeColumns.size());

          if (mProcessReport)
            mhProgressCounter2 =
              mProcessReport.addItem("Combinations",
                                     mProgressCounter2,
                                     & mProgressCounter2Max);

          for (unsigned int i = 0; i < NegativeColumns.size(); i++)
            for (unsigned int j = 0; j < PositiveColumns.size(); j++)
              combine(PositiveColumns[j], NegativeColumns[i], NullColumns);

          if (mProcessReport)
            mProcessReport.finishItem(mhProgressCounter2);

          Continue &= mContinueCombination;

          if (Continue)
            {
              // We can now destroy all negative columns, which removes them from
              // the step matrix.
              mpStepMatrix->removeInvalidColumns(NegativeColumns);

              // Remove columns of the step matrix which are no longer extreme rays.
              findRemoveInvalidColumns(NullColumns);

              // We compact the step matrix which has empty columns due to the removal of columns above.
              mpStepMatrix->compact();

              // Now we can convert the processed row.
              mpStepMatrix->convertRow();
            }
        }

      mProgressCounter = mProgressCounterMax - (unsigned C_INT32) mpStepMatrix->getNumUnconvertedRows();

      if (mProcessReport)
        Continue &= mProcessReport.progressItem(mhProgressCounter);
    }

  if (Continue)
    {
      buildFluxModes();
    }

  if (mProcessReport)
    Continue &= mProcessReport.finishItem(mhProgressCounter);

  return true;
}

//TODO: Change combine method to accept columns instead of trees.
void CBitPatternMethod::combine(const CStepMatrixColumn * pPositive,
                                const CStepMatrixColumn * pNegative,
                                const std::vector< CStepMatrixColumn * > NullColumns)
{
  if (mContinueCombination && mProcessReport)
    {
      mContinueCombination = mProcessReport.proceed();
    }

  if (!mContinueCombination)
    {
      return;
    }

  CZeroSet Intersection = CZeroSet::intersection(pPositive->getZeroSet(),
                          pNegative->getZeroSet());

  // Adjacency test
  if (Intersection.getNumberOfSetBits() < mMinimumSetSize)
    {
      return;
    }

  //INSERT RANK TEST HERE

  CStepMatrixColumn * RankTestColumn = new CStepMatrixColumn(Intersection, pPositive, pNegative);
  CMatrix<C_INT64> rtKernel = performRankTest(RankTestColumn);

  if (rtKernel.numCols() > 1)
    {
      return;
    }

  // Assert columns are not null
  if (pPositive != NULL && pNegative != NULL)
    {
      // We need to check whether the existing matrix contains already a leaf which is a superset
      if (Intersection.isExtremeRay(NullColumns))
        {
          // We are sure that the previous Null Tree did not contain any
          // super sets, however the new columns may.

          // We check whether the new columns do not already contain a superset
          if (Intersection.isExtremeRay(mNewColumns))
            {
              CStepMatrixColumn * pColumn = mpStepMatrix->addColumn(Intersection, pPositive, pNegative);

              // Remove all new column which are no longer extreme rays
              std::vector< CStepMatrixColumn * >::iterator it = mNewColumns.begin();
              std::vector< CStepMatrixColumn * >::iterator end = mNewColumns.end();

              for (; it != end; ++it)
                {
                  if ((*it) != NULL &&
                      (*it)->getZeroSet() >= Intersection)
                    {
                      // We need to remove the column from the step matrix, which can be done by deleting it.
                      mpStepMatrix->removeColumn(*it);
                      *it = NULL;
                    }
                }

              mNewColumns.push_back(pColumn);
            }
        }

      mProgressCounter2++;

      if (mProcessReport)
        mContinueCombination = mProcessReport.progressItem(mhProgressCounter2);
    }
}

void CBitPatternMethod::findRemoveInvalidColumns(const std::vector< CStepMatrixColumn * > & nullColumns)
{
  if (mNewColumns.empty())
    {
      return;
    }

  // Determine the columns which became invalid.
  std::vector< CStepMatrixColumn * > InvalidColumns;

  std::vector< CStepMatrixColumn * >::const_iterator NullIt = nullColumns.begin();
  std::vector< CStepMatrixColumn * >::const_iterator NullEnd = nullColumns.end();

  for (; NullIt != NullEnd; ++NullIt)
    {
      if (!((*NullIt)->getZeroSet()).isExtremeRay(mNewColumns))
        {
          InvalidColumns.push_back(*NullIt);
        }
    }

  mpStepMatrix->removeInvalidColumns(InvalidColumns);
  mNewColumns.clear();
}

void CBitPatternMethod::buildKernelMatrix(CMatrix< C_INT64 > & kernelInt)
{
  // Calculate the kernel matrix
  // of the reduced stoichiometry matrix to get the kernel matrix for the:
  //   Nullspace Approach to Determine the Elementary Modes of Chemical Reaction Systems (Wagner 2004)

  CDataVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();
  CDataVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

  size_t ReactionCounter = 0;

  for (; itReaction != endReaction; ++itReaction, ++ReactionCounter)
    {
      if (itReaction->isReversible())
        {
          // mpReorderedReactons->push_back(*itReaction);
          mReactionForward.push_back(std::make_pair(ReactionCounter, false));
        }

      mpReorderedReactions->push_back(itReaction);
      mReactionForward.push_back(std::make_pair(ReactionCounter, true));
    }

  const CMatrix< C_FLOAT64 > & Stoi = mpModel->getRedStoi();

  size_t NumReactions = Stoi.numCols();

  size_t NumExpandedReactions = mReactionForward.size();

  size_t NumSpecies = Stoi.numRows();

  size_t Dim = std::min(NumExpandedReactions, NumSpecies);

  if (Dim == 0)
    {
      return;
    }

  mExpandedStoiTranspose.resize(NumExpandedReactions, NumSpecies);

  const C_FLOAT64 *pStoi = Stoi.array();
  const C_FLOAT64 *pStoiEnd = pStoi + Stoi.size();
  const C_FLOAT64 *pStoiRowEnd;

  C_INT64 *pExpandedStoiTranspose;
  C_INT64 *pExpandedStoiTransposeColumn = mExpandedStoiTranspose.array();

  std::vector< const CReaction * >::const_iterator itReactionPivot;
  std::vector< const CReaction * >::const_iterator endReactionPivot;
  std::vector< std::pair< size_t, bool > >::const_iterator itReactionExpansion;

  for (; pStoi != pStoiEnd; ++pExpandedStoiTransposeColumn)
    {
      pStoiRowEnd = pStoi + NumReactions;
      pExpandedStoiTranspose = pExpandedStoiTransposeColumn;
      itReactionExpansion = mReactionForward.begin();

      for (; pStoi < pStoiRowEnd; ++pStoi, pExpandedStoiTranspose += NumSpecies, ++itReactionExpansion)
        {
          // TODO We should check the we have integer stoichiometry.
          if (itReactionExpansion->second == false)
            {
              *pExpandedStoiTranspose = (C_INT64) - floor(*pStoi + 0.5);

              // Advance the iterators
              ++itReactionExpansion;
              pExpandedStoiTranspose += NumSpecies;
            }

          *pExpandedStoiTranspose = (C_INT64) floor(*pStoi + 0.5);
        }
    }

  // Calculate the kernel of the matrix
  CMatrix< C_INT64 > ExpandedStoiTranspose(mExpandedStoiTranspose);
  CalculateKernel(ExpandedStoiTranspose, kernelInt, mReactionPivot);

  return;
}

void CBitPatternMethod::buildFluxModes()
{
  CStepMatrix::const_iterator it = mpStepMatrix->begin();
  CStepMatrix::const_iterator end = mpStepMatrix->end();

  CVector< size_t > Indexes;
  size_t NumSpecies = mExpandedStoiTranspose.numCols();

  for (; it != end; ++it)
    {
      getUnsetBitIndexes(*it, Indexes);

      size_t NumReactions = Indexes.size();

      // Remove trivial modes, i.e., reversible reactions
      if (NumReactions == 2 &&
          (*mpReorderedReactions)[mReactionForward[Indexes[0]].first] ==
          (*mpReorderedReactions)[mReactionForward[Indexes[1]].first])
        {
          continue;
        }

      // Build the stoichiometry matrix reduced to the reactions participating in the current mode.
      CMatrix< C_INT64 > A(NumReactions, NumSpecies);

      size_t * pIndex = Indexes.array();
      size_t * pIndexEnd = pIndex + NumReactions;
      C_INT64 * pARow = A.array();

      for (; pIndex != pIndexEnd; ++pIndex, pARow += NumSpecies)
        {
          memcpy(pARow, &mExpandedStoiTranspose(*pIndex, 0), NumSpecies * sizeof(C_INT64));
        }

      // Calculate the kernel of the matrix
      CMatrix< C_INT64 > ExpandedStoiTranspose(A);
      CMatrix< C_INT64 > Kernel;
      CVector< size_t > Pivot;
      CalculateKernel(ExpandedStoiTranspose, Kernel, Pivot);

      size_t NumCols = Kernel.numCols();

      // Now we create the flux mode as we have the multiplier and reaction indexes.
      // We need to invert the sign of the multiplier for reactions which are not forward.
      // A flux mode is reversible if all reactions are reversible;

      C_INT64 * pColumn = Kernel.array();
      C_INT64 * pColumnEnd = pColumn + NumCols;

      for (; pColumn != pColumnEnd; ++pColumn)
        {
          std::map< size_t, C_FLOAT64 > Reactions;
          bool Reversible = true;

          pIndex = Indexes.array();
          C_INT64 * pFluxMultiplier = pColumn;

          for (; pIndex != pIndexEnd; ++pIndex, pFluxMultiplier += NumCols)
            {
              if (*pFluxMultiplier < 0)
                {
                  break;
                }
              else if (*pFluxMultiplier < 0)
                {
                  continue;
                }

              std::pair< size_t, bool > & ReactionForward = mReactionForward[*pIndex];

              Reactions[ReactionForward.first] =
                (C_FLOAT64)((ReactionForward.second == true) ? *pFluxMultiplier : -*pFluxMultiplier);

              if (!(*mpReorderedReactions)[ReactionForward.first]->isReversible())
                {
                  Reversible = false;
                }
            }

          if (pIndex != pIndexEnd)
            {
              continue;
            }

          addMode(CFluxMode(Reactions, Reversible));
        }
    }
}

#ifdef XXXX
void CBitPatternMethod::convertToIntegers(CMatrix< C_FLOAT64 > & values)
{
  bool Problems = false;

  static const C_FLOAT64 limit = 10.0 / std::numeric_limits< C_INT32 >::max();

  size_t Size = values.size();
  size_t Columns = values.numCols();

  C_FLOAT64 * pColumn = values.array();
  C_FLOAT64 * pColumnEnd = pColumn + Columns;
  C_FLOAT64 * pValue = values.array();
  C_FLOAT64 * pValueEnd = pColumn + Size;

  for (; pColumn < pColumnEnd; ++pColumn)
    {
      size_t Multiplier = 1;
      size_t m00, m01, m10, m11;
      size_t maxden = 10000000;
      C_INT32 GCD1, GCD2;
      size_t ai;

      C_FLOAT64 x;

      for (pValue = pColumn; pValue < pValueEnd; pValue += Columns)
        {
          x = fabs(*pValue);

          if (x < 100 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              continue;
            }

          /*
           * Find rational approximation to given real number
           * David Eppstein / UC Irvine / 8 Aug 1993
           *
           * With corrections from:
           *   Arno Formella, May 2008
           *   Stefan Hoops, Sept 2009
           *
           * Based on the theory of continued fractions
           * if x = a1 + 1/(a2 + 1/(a3 + 1/(a4 + ...)))
           * then best approximation is found by truncating this series
           * (with some adjustments in the last term).
           *
           * Note the fraction can be recovered as the first column of the matrix
           *  (a1 1 ) (a2 1 ) (a3 1 ) ...
           *  (1  0 ) (1  0 ) (1  0)
           * Instead of keeping the sequence of continued fraction terms,
           * we just keep the last partial product of these matrices.
           */

          /* initialize matrix */
          m00 = m11 = 1;
          m01 = m10 = 0;

          /* loop finding terms until denom gets too big */
          while (m10 * (ai = (size_t) x) + m11 <= maxden)
            {
              size_t t;
              t = m00 * ai + m01;
              m01 = m00;
              m00 = t;

              t = m10 * ai + m11;
              m11 = m10;
              m10 = t;

              if (fabs(x - (C_FLOAT64) ai) < limit)
                break;     // SH: We reached the numerical precision of the machine;

              x = 1 / (x - (C_FLOAT64) ai);
            }

          if ((C_FLOAT64) m10 * (C_FLOAT64) ai + (C_FLOAT64) m11 > (C_FLOAT64) maxden)
            {
              Problems = true;
            }

          if (fabs(fabs(*pValue) - ((C_FLOAT64) m00) / ((C_FLOAT64) m10)) > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              ai = (maxden - m11) / m10;
              m00 = m00 * ai + m01;
              m10 = m10 * ai + m11;
            }

          // Find the greatest common divisor (GCD) of the multiplier and the current denominator.
          // Euclidean algorithm
          GCD1 = m10;
          GCD2 = Multiplier;

          GCD(GCD1, GCD2);

          // Calculate the least common multiplier: LCM = v1 * v2 / GCD(v1, v2)
          Multiplier *= m10 / GCD1;
        }

      for (pValue = pColumn; pValue < pValueEnd; pValue += Columns)
        {
          *pValue *= Multiplier;
        }
    }
}
#endif //

void CBitPatternMethod::getAllUnsetBitIndexes(const CStepMatrixColumn * pColumn,
    CVector<size_t> & indexes) const
{
  mpStepMatrix->getAllUnsetBitIndexes(pColumn, indexes);

  // Apply the QR pivot
  size_t * pIndex = indexes.array();
  size_t * pIndexEnd = pIndex + indexes.size();

  for (; pIndex != pIndexEnd; ++pIndex)
    *pIndex = mReactionPivot[*pIndex];

  //DebugFile << "@CBPM: " << indexes << std::endl;
}

void CBitPatternMethod::getUnsetBitIndexes(const CStepMatrixColumn * pColumn,
    CVector< size_t > & indexes) const
{
  mpStepMatrix->getUnsetBitIndexes(pColumn, indexes);

  // Apply the QR pivot
  size_t * pIndex = indexes.array();
  size_t * pIndexEnd = pIndex + indexes.size();

  for (; pIndex != pIndexEnd; ++pIndex)
    {
      *pIndex = mReactionPivot[*pIndex];
    }
}

// private
void CBitPatternMethod::addMode(const CFluxMode & mode)
{
  std::vector< CFluxMode >::iterator itMode = mpFluxModes->begin();
  std::vector< CFluxMode >::iterator endMode = mpFluxModes->end();

  for (; itMode != endMode; ++itMode)
    {
      if (itMode->isReversed(mode))
        {
          return;
        }
    }

  mpFluxModes->push_back(mode);
  return;
}

// static
bool CBitPatternMethod::CalculateKernel(CMatrix< C_INT64 > & matrix,
                                        CMatrix< C_INT64 > & kernel,
                                        CVector< size_t > & rowPivot)
{
  // Gaussian elimination
  size_t NumRows = matrix.numRows();
  size_t NumCols = matrix.numCols();

  assert(NumRows > 0);
  assert(NumCols > 0);

  // Initialize row pivots
  rowPivot.resize(NumRows);
  size_t * pPivot = rowPivot.array();

  for (size_t i = 0; i < NumRows; i++, pPivot++)
    {
      *pPivot = i;
    }

  CVector< size_t > RowPivot(rowPivot);

  CVector< C_INT64 > Identity(NumRows);
  Identity = 1;

  C_INT64 * pColumn = matrix.array();
  C_INT64 * pColumnEnd = pColumn + NumCols;

  C_INT64 * pActiveRow;
  C_INT64 * pActiveRowStart = pColumn;
  C_INT64 * pActiveRowEnd = pColumnEnd;

  C_INT64 * pRow;
  C_INT64 * pRowEnd = pColumn + matrix.size();

  C_INT64 * pCurrent;
  C_INT64 * pIdentity;

  CVector< C_INT64 > SwapTmp(NumCols);

  size_t CurrentRowIndex = 0;
  size_t CurrentColumnIndex = 0;
  size_t NonZeroIndex = 0;

  CVector< bool > IgnoredColumns(NumCols);
  IgnoredColumns = false;
  bool * pIgnoredColumn = IgnoredColumns.array();
  size_t IgnoredColumnCount = 0;

  // For each column
  for (; pColumn < pColumnEnd; ++pColumn, ++CurrentColumnIndex, ++pIgnoredColumn)
    {
      assert(CurrentColumnIndex == CurrentRowIndex + IgnoredColumnCount);

      // Find non zero entry in current column.
      pRow = pActiveRowStart + CurrentColumnIndex;
      NonZeroIndex = CurrentRowIndex;

      for (; pRow < pRowEnd; pRow += NumCols, ++NonZeroIndex)
        {
          if (*pRow != 0)
            break;
        }

      if (NonZeroIndex >= NumRows)
        {
          *pIgnoredColumn = true;
          IgnoredColumnCount++;

          continue;
        }

      if (NonZeroIndex != CurrentRowIndex)
        {
          // Swap rows
          memcpy(SwapTmp.array(), matrix[CurrentRowIndex], NumCols * sizeof(C_INT64));
          memcpy(matrix[CurrentRowIndex], matrix[NonZeroIndex], NumCols * sizeof(C_INT64));
          memcpy(matrix[NonZeroIndex], SwapTmp.array(), NumCols * sizeof(C_INT64));

          // Record pivot
          size_t tmp = RowPivot[CurrentRowIndex];
          RowPivot[CurrentRowIndex] = RowPivot[NonZeroIndex];
          RowPivot[NonZeroIndex] = tmp;

          C_INT64 TMP = Identity[CurrentRowIndex];
          Identity[CurrentRowIndex]  = Identity[NonZeroIndex];
          Identity[NonZeroIndex] = TMP;
        }

      if (*(pActiveRowStart + CurrentColumnIndex) < 0)
        {
          for (pRow = pActiveRowStart; pRow < pActiveRowEnd; ++pRow)
            {
              *pRow *= -1;
            }

          Identity[CurrentRowIndex] *= -1;
        }

      // For each row
      pRow = pActiveRowStart + NumCols;
      pIdentity = Identity.array() + CurrentRowIndex + 1;

      C_INT64 ActiveRowValue = *(pActiveRowStart + CurrentColumnIndex);
      *(pActiveRowStart + CurrentColumnIndex) = Identity[CurrentRowIndex];

      for (; pRow < pRowEnd; pRow += NumCols, ++pIdentity)
        {
          C_INT64 RowValue = *(pRow + CurrentColumnIndex);

          if (RowValue == 0)
            continue;

          *(pRow + CurrentColumnIndex) = 0;

          // compute GCD(*pActiveRowStart, *pRow)
          C_INT64 GCD1 = abs64(ActiveRowValue);
          C_INT64 GCD2 = abs64(RowValue);

          GCD(GCD1, GCD2);

          C_INT64 alpha = ActiveRowValue / GCD1;
          C_INT64 beta = RowValue / GCD1;

          // update rest of row
          pActiveRow = pActiveRowStart;
          pCurrent = pRow;
          *pIdentity *= alpha;

          GCD1 = abs64(*pIdentity);

          for (; pActiveRow < pActiveRowEnd; ++pActiveRow, ++pCurrent)
            {
              // Assert that we do not have a numerical overflow.
              assert(fabs(((C_FLOAT64) alpha) * ((C_FLOAT64) * pCurrent) - ((C_FLOAT64) beta) * ((C_FLOAT64) * pActiveRow)) < std::numeric_limits< C_INT64 >::max());

              *pCurrent = alpha **pCurrent - beta **pActiveRow;

              // We check that the row values do not have any common divisor.
              if (GCD1 > 1 &&
                  (GCD2 = abs64(*pCurrent)) > 0)
                {
                  GCD(GCD1, GCD2);
                }
            }

          if (GCD1 > 1)
            {
              *pIdentity /= GCD1;

              pActiveRow = pActiveRowStart;
              pCurrent = pRow;

              for (; pActiveRow < pActiveRowEnd; ++pActiveRow, ++pCurrent)
                {
                  *pCurrent /= GCD1;
                }
            }
        }

      pActiveRowStart += NumCols;
      pActiveRowEnd += NumCols;
      CurrentRowIndex++;

      // DebugFile << matrix << std::endl;
      // DebugFile << Identity << std::endl;
    }

  assert(CurrentColumnIndex == CurrentRowIndex + IgnoredColumnCount);
  assert(CurrentColumnIndex == NumCols);

  // std::cout << matrix << std::endl;
  // std::cout << IgnoredColumns << std::endl;
  // std::cout << Identity << std::endl;
  // std::cout << RowPivot << std::endl << std::endl;

  size_t KernelRows = NumRows;
  size_t KernelCols = NumRows + IgnoredColumnCount - NumCols;

  assert(KernelCols > 0);

  kernel.resize(KernelRows, KernelCols);

  CMatrix< C_INT64 > Kernel(KernelRows, KernelCols);
  Kernel = 0;

  C_INT64 * pKernelInt = Kernel.array();
  C_INT64 * pKernelIntEnd = pKernelInt + Kernel.size();

  pActiveRowStart = matrix[CurrentRowIndex];
  pActiveRowEnd = matrix[NumRows];

  // Null space matrix identity part
  pIdentity = Identity.array() + CurrentRowIndex;
  C_INT64 * pKernelColumn = Kernel.array();

  for (; pActiveRowStart < pActiveRowEnd; pActiveRowStart += NumCols, ++pKernelColumn, ++pIdentity)
    {
      pKernelInt = pKernelColumn;
      pIgnoredColumn = IgnoredColumns.array();

      pRow = pActiveRowStart;
      pRowEnd = pRow + NumCols;

      if (*pIdentity < 0)
        {
          *pIdentity *= -1;

          for (; pRow < pRowEnd; ++pRow, ++pIgnoredColumn)
            {
              if (*pIgnoredColumn)
                {
                  continue;
                }

              *pKernelInt = - *pRow;
              pKernelInt += KernelCols;
            }
        }
      else
        {
          for (; pRow < pRowEnd; ++pRow, ++pIgnoredColumn)
            {
              if (*pIgnoredColumn)
                {
                  continue;
                }

              *pKernelInt = *pRow;
              pKernelInt += KernelCols;
            }
        }
    }

  pIdentity = Identity.array() + CurrentRowIndex;
  pKernelInt = Kernel[CurrentRowIndex];

  for (; pKernelInt < pKernelIntEnd; pKernelInt += KernelCols + 1, ++pIdentity)
    {
      *pKernelInt = *pIdentity;
    }

  // Undo the reordering introduced by Gaussian elimination to the kernel matrix.
  pPivot = RowPivot.array();
  pRow = Kernel.array();
  pRowEnd = pRow + Kernel.size();

  for (; pRow < pRowEnd; ++pPivot, pRow += KernelCols)
    {
      memcpy(kernel[*pPivot], pRow, KernelCols * sizeof(C_INT64));
    }

  return true;
}

CMatrix<C_INT64> CBitPatternMethod::performRankTest(CStepMatrixColumn * pIntersectColumn)
{
  CVector<size_t> Indexes;

  getAllUnsetBitIndexes(pIntersectColumn, Indexes);

  size_t NumReactions = Indexes.size();
  size_t NumSpecies = mExpandedStoiTranspose.numCols();

  // Build the stoichiometry matrix reduced to the reactions participating in the current mode.
  CMatrix< C_INT64 > A(NumReactions, NumSpecies);

  size_t * pIndex = Indexes.array();
  size_t * pIndexEnd = pIndex + NumReactions;
  C_INT64 * pARow = A.array();

  for (; pIndex != pIndexEnd; ++pIndex, pARow += NumSpecies)
    {
      memcpy(pARow, &mExpandedStoiTranspose(*pIndex, 0), NumSpecies * sizeof(C_INT64));
    }

  // Calculate the kernel of the matrix
  CMatrix< C_INT64 > ExpandedStoiTranspose(A);
  CMatrix< C_INT64 > Kernel;
  CVector< size_t > Pivot;

  //DebugFile << ExpandedStoiTranspose << std::endl;
  CalculateKernel(ExpandedStoiTranspose, Kernel, Pivot);

  return Kernel;
}

void CBitPatternMethod::buildFluxModeMatrix(CStepMatrix * fluxModeMatrix,
    std::stack<CStepMatrixColumn *> kernelStack)
{
  CStepMatrixColumn * KernelCol;
  unsigned int col, row;

  while (!kernelStack.empty())
    {
      KernelCol = kernelStack.top();
#ifdef COPASI_DEBUG_TRACE
      DebugFile << "Current Column: " << *KernelCol << std::endl;
#endif // COPASI_DEBUG_TRACE
      CMatrix<C_INT64> RankKernel = performRankTest(KernelCol);
#ifdef COPASI_DEBUG_TRACE
      DebugFile << "New Rank Kernel " << RankKernel << std::endl;
#endif // COPASI_DEBUG_TRACE

      if (RankKernel.numCols() == 1)
        {
          fluxModeMatrix->add(KernelCol);
        }
      else if (RankKernel.numCols() > 1)
        {
          for (col = 0; col < RankKernel.numCols(); col++)
            {
              KernelCol = new CStepMatrixColumn(RankKernel.numRows());

              for (row = 0; row < RankKernel.numRows(); row++)
                {
                  KernelCol->push_front(RankKernel(row, col));
                }

              kernelStack.push(KernelCol);
            }
        }

      kernelStack.pop();
    }
}

/*
Future Implementation:
After building left kernel of the stoichiometric matrix 'SP', parse through each vector column 'vi' in SP.
  SP contains "pre-flux modes" which must be checked based on rank test.
Build the stoichiometric transpose submatrix NTvi based on involved reactions in vi.
Calculate the left kernel of NTvi, 'K'.
If #cols in K = 1:
  Move vi from SP into new step matrix 'SF'.
Else if #cols in K > 1:
  Add each unique nontrivial kernel vector into SP.

The end result is that SF will contain only flux modes, but not all possible flux modes.
Through this method we never have to remove any elements from the matrix.

After this we then build the initial step matrix from SF.
 */
