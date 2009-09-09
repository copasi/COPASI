// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CStepMatrix.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/09 13:50:08 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CStepMatrix.h"
#include "CStepMatrixColumn.h"

#include "utilities/CMatrix.h"

CStepMatrix::CStepMatrix():
    std::list< CStepMatrixColumn * >(),
    mRows(0),
    mPivot(0),
    mFirstUnconvertedRow(0)
{}

CStepMatrix::CStepMatrix(CMatrix< C_FLOAT64 > & nullspaceMatrix):
    std::list< CStepMatrixColumn * >(),
    mRows(nullspaceMatrix.numRows()),
    mPivot(nullspaceMatrix.numRows()),
    mFirstUnconvertedRow(0)
{
  size_t Cols = nullspaceMatrix.numCols();

  CVector< CStepMatrixColumn * > Columns(Cols);
  CStepMatrixColumn ** pColumn = Columns.array();
  CStepMatrixColumn ** pColumnEnd = pColumn + Cols;

  for (; pColumn != pColumnEnd; ++pColumn)
    {
      *pColumn = new CStepMatrixColumn(mRows);
      push_back(*pColumn);
    }

  size_t i;
  size_t j;
  const C_FLOAT64 * pValue = nullspaceMatrix.array();
  size_t * pPivot = mPivot.array();

  std::vector< size_t > NegativeRows;
  bool hasNegative;
  bool hasPositive;

  for (i = 0; i < mRows; ++i, ++pPivot)
    {
      *pPivot = i;

      hasNegative = false;
      hasPositive = false;

      for (j = 0; j < Cols; ++j, ++pValue)
        {
          if (*pValue > 0.0)
            {
              hasPositive = true;
            }
          else if (*pValue < 0.0)
            {
              hasNegative = true;
            }
        }

      if ((hasNegative && !hasPositive) ||
          (!hasNegative && hasPositive))
        {
          convertRow(i, nullspaceMatrix);
        }
    }

  // We need to add the information of the unconverted rows of nullspace matrix
  // to the columns

  pValue = & nullspaceMatrix(mFirstUnconvertedRow, 0);

  for (i = mFirstUnconvertedRow; i < mRows; ++i)
    {
      pColumn = Columns.array();

      for (j = 0; j < Cols; ++j, ++pValue,  ++pColumn)
        {
          (*pColumn)->push_front(*pValue);
        }
    }
}

CStepMatrix::~CStepMatrix()
{
  iterator it = begin();
  const_iterator itEnd = end();

  for (; it != itEnd; ++it)
    {
      delete *it;
    }
}

void CStepMatrix::convertRow()
{
  CZeroSet::CIndex Index(mFirstUnconvertedRow);

  iterator it = begin();
  const_iterator itEnd = end();

  for (; it != itEnd; ++it)
    {
      if ((*it)->getMultiplier() != 0.0)
        {
          (*it)->unsetBit(Index);
        }

      (*it)->truncate();
    }

  mFirstUnconvertedRow++;
}

size_t CStepMatrix::getFirstUnconvertedRow() const
{
  return mFirstUnconvertedRow;
}

size_t CStepMatrix::getNumUnconvertedRows() const
{
  return mRows - mFirstUnconvertedRow;
}

CStepMatrixColumn * CStepMatrix::addColumn(const CZeroSet & set,
    CStepMatrixColumn const * pPositive,
    CStepMatrixColumn const * pNegative)
{
  CStepMatrixColumn * pColumn = new CStepMatrixColumn(set, pPositive, pNegative);
  push_back(pColumn);

  return pColumn;
}

bool CStepMatrix::splitColumns(std::list< CStepMatrixColumn * > & PositiveColumns,
                               std::list< CStepMatrixColumn * > & NegativeColumns,
                               std::list< CStepMatrixColumn * > & NullColumns)
{
  PositiveColumns.clear();
  NegativeColumns.clear();

  iterator it = begin();
  const_iterator itEnd = end();

  while (it != itEnd)
    {
      const C_FLOAT64 & Value = (*it)->getMultiplier();

      if (Value > 0.0)
        {
          PositiveColumns.push_back(*it);
          ++it;
        }
      else if (Value < 0.0)
        {
          NegativeColumns.push_back(*it);

          // Since all negative columns have to be removed this is the perfect place to do so.
          it = erase(it);
        }
      else
        {
          NullColumns.push_back(*it);
          ++it;
        }
    }

  if (NegativeColumns.empty())
    {
      convertRow();

      return false;
    }
  else if (PositiveColumns.empty())
    {
      // We can not remove the negative columns therefore we add them again.
      std::list< CStepMatrixColumn * >::const_iterator itNeg = NegativeColumns.begin();
      std::list< CStepMatrixColumn * >::const_iterator endNeg = NegativeColumns.end();

      for (; itNeg != endNeg; ++itNeg)
        {
          push_back(*itNeg);
        }

      convertRow();

      return false;
    }

  return true;
}

void CStepMatrix::removeInvalidColumns(const std::vector< CStepMatrixColumn * > & invalidColumns)
{
  std::vector< CStepMatrixColumn * >::const_iterator it = invalidColumns.begin();
  std::vector< CStepMatrixColumn * >::const_iterator end = invalidColumns.end();

  for (; it != end; ++it)
    {
      remove(*it);
      delete *it;
    }
}

void CStepMatrix::getSetBitIndexes(const CStepMatrixColumn * pColumn,
                                   CVector< size_t > & indexes) const
{
  const CZeroSet & ZeroSet = pColumn->getZeroSet();

  indexes.resize(ZeroSet.getNumberOfSetBits());
  size_t * pIndex = indexes.array();
  size_t * pIndexEnd = pIndex + indexes.size();

  CZeroSet::CIndex Bit = 0;
  size_t Index = 0;

  for (; pIndex != pIndexEnd; ++Bit, ++Index)
    {
      if (ZeroSet.isSet(Bit))
        {
          *pIndex = mPivot[Index];
          pIndex++;
        }
    }

  return;

  // TODO CRITICAL Apply pivot.
}

void CStepMatrix::convertRow(const size_t & index,
                             CMatrix< C_FLOAT64 > & nullspaceMatrix)
{
  CZeroSet::CIndex Index(mFirstUnconvertedRow);

  iterator it = begin();
  const_iterator itEnd = end();
  C_FLOAT64 * pValue = & nullspaceMatrix(index, 0);

  if (mFirstUnconvertedRow != index)
    {
      C_FLOAT64 * pFirstUnconvertedValue = & nullspaceMatrix(mFirstUnconvertedRow, 0);

      for (; it != itEnd; ++it, ++pValue, ++pFirstUnconvertedValue)
        {
          if (*pValue != 0.0)
            {
              (*it)->unsetBit(Index);
            }

          *pValue = *pFirstUnconvertedValue;
        }

      // We need to remember the reordering.
      size_t tmp = mPivot[index];
      mPivot[index] = mPivot[mFirstUnconvertedRow];
      mPivot[mFirstUnconvertedRow] = tmp;
    }
  else
    {
      for (; it != itEnd; ++it, ++pValue)
        {
          if (*pValue != 0.0)
            {
              (*it)->unsetBit(Index);
            }
        }
    }

  mFirstUnconvertedRow++;
}

std::ostream & operator << (std::ostream & os, const CStepMatrix & m)
{
  os << m.mPivot << std::endl;

  size_t i;
  CZeroSet::CIndex Bit;

  CStepMatrix::const_iterator it;
  CStepMatrix::const_iterator end = m.end();

  for (i = 0, Bit = 0; i < m.mFirstUnconvertedRow; ++i, ++Bit)
    {
      for (it = m.begin(); it != end; ++it)
        {
          if ((*it)->getZeroSet().isSet(Bit))
            {
              os << "*\t";
            }
          else
            {
              os << ".\t";
            }
        }

      os << std::endl;
    }

  for (i = m.mRows - m.mFirstUnconvertedRow; i > 0;)
    {
      --i;

      for (it = m.begin(); it != end; ++it)
        {
          os << (*it)->getReaction()[i] << '\t';
        }

      os << std::endl;
    }

  return os;
}
