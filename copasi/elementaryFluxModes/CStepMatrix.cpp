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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CStepMatrix.h"

#include "copasi/core/CMatrix.h"
#include "CStepMatrixColumn.h"

CStepMatrix::CStepMatrix():
  CVector< CStepMatrixColumn * >(0),
  mRows(0),
  mPivot(0),
  mFirstUnconvertedRow(0)
{}

CStepMatrix::CStepMatrix(size_t rows):
  CVector< CStepMatrixColumn * >(0),
  mRows(rows),
  mPivot(rows),
  mFirstUnconvertedRow(0)
{
  size_t * pPivot = mPivot.array();

  for (size_t i = 0; i < mRows; ++i, ++pPivot)
    {
      *pPivot = i;
    }
}

CStepMatrix::CStepMatrix(CMatrix< C_INT64 > & nullspaceMatrix):
  CVector< CStepMatrixColumn * >(0),
  mRows(nullspaceMatrix.numRows()),
  mPivot(nullspaceMatrix.numRows()),
  mFirstUnconvertedRow(0)
{
  size_t Cols = nullspaceMatrix.numCols();

  resize(Cols);
  iterator it = array();
  mInsert = mBeyond = it + Cols;

  CVector< CStepMatrixColumn * > Columns(Cols);
  CStepMatrixColumn ** pColumn = Columns.array();
  CStepMatrixColumn ** pColumnEnd = pColumn + Cols;

  for (; pColumn != pColumnEnd; ++pColumn, ++it)
    {
      *pColumn = new CStepMatrixColumn(mRows);

      (*pColumn)->setIterator(it);
      *it = *pColumn;
    }

  size_t i;
  size_t j;
  const C_INT64 * pValue = nullspaceMatrix.array();
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
          if (*pValue > 0)
            {
              hasPositive = true;
            }
          else if (*pValue < 0)
            {
              hasNegative = true;
            }
        }

      if ((!hasNegative && hasPositive))
        {
          convertRow(i, nullspaceMatrix);
        }
    }

  // We need to add the information of the unconverted rows of nullspace matrix
  // to the columns

  if (nullspaceMatrix.size() != 0 &&
      mFirstUnconvertedRow < mRows)
    {
      pValue = & nullspaceMatrix(mFirstUnconvertedRow, 0);
    }
  else
    {
      pValue = NULL;
    }

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
  iterator it = array();

  for (; it != mInsert; ++it)
    {
      if (*it != NULL)
        {
          delete *it;
        }
    }
}

void CStepMatrix::convertRow()
{
  CZeroSet::CIndex Index(mFirstUnconvertedRow);

  iterator it = array();

  for (; it != mInsert; ++it)
    {
      assert(*it != NULL);

      assert((*it)->getMultiplier() >= 0);

      if ((*it)->getMultiplier() > 0)
        {
          (*it)->unsetBit(Index);
        }

      (*it)->truncate();
    }

  mFirstUnconvertedRow++;
}

/*
void CStepMatrix::convertMatrix() {
}
 */

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

  add(pColumn);

  return pColumn;
}

void CStepMatrix::removeColumn(CStepMatrixColumn * pColumn)
{
  delete pColumn;
}

bool CStepMatrix::splitColumns(std::vector< CStepMatrixColumn * > & PositiveColumns,
                               std::vector< CStepMatrixColumn * > & NegativeColumns,
                               std::vector< CStepMatrixColumn * > & NullColumns)
{
  assert(PositiveColumns.empty());
  assert(NegativeColumns.empty());
  assert(NullColumns.empty());

  iterator it = array();

  for (; it != mInsert; ++it)
    {
      assert(*it != NULL);

      const C_INT64 & Value = (*it)->getMultiplier();

      if (Value > 0)
        {
          PositiveColumns.push_back(*it);
        }
      else if (Value < 0)
        {
          NegativeColumns.push_back(*it);
        }
      else
        {
          NullColumns.push_back(*it);
        }
    }

  if (NegativeColumns.empty())
    {
      // We do not have any linear combinations, thus we can convert immediately
      convertRow();

      return false;
    }

  return true;
}

void CStepMatrix::removeInvalidColumns(std::vector< CStepMatrixColumn * > & invalidColumns)
{
  std::vector< CStepMatrixColumn * >::iterator it = invalidColumns.begin();
  std::vector< CStepMatrixColumn * >::iterator end = invalidColumns.end();

  for (; it != end; ++it)
    {
      removeColumn(*it);
    }
}

void CStepMatrix::getAllUnsetBitIndexes(const CStepMatrixColumn * pColumn,
                                        CVector<size_t> & indexes) const
{
  pColumn->getAllUnsetBitIndexes(indexes);

  // Apply the QR pivot
  size_t * pIndex = indexes.array();
  size_t * pIndexEnd = pIndex + indexes.size();

  for (; pIndex != pIndexEnd; ++pIndex)
    *pIndex = mPivot[*pIndex];

  //DebugFile << "@CSM: " << indexes << std::endl;
}

void CStepMatrix::getUnsetBitIndexes(const CStepMatrixColumn * pColumn,
                                     CVector< size_t > & indexes) const
{
  const CZeroSet & ZeroSet = pColumn->getZeroSet();

  indexes.resize(ZeroSet.getNumberOfUnsetBits());
  size_t * pIndex = indexes.array();
  size_t * pIndexEnd = pIndex + indexes.size();

  CZeroSet::CIndex Bit = 0;
  size_t Index = 0;

  for (; pIndex != pIndexEnd; ++Bit, ++Index)
    {
      if (!ZeroSet.isSet(Bit))
        {
          // Apply pivot.
          *pIndex = mPivot[Index];
          pIndex++;
        }
    }

  return;
}

CStepMatrix::const_iterator CStepMatrix::begin() const
{
  return array();
}

CStepMatrix::const_iterator CStepMatrix::end() const
{
  return mInsert;
}

void CStepMatrix::convertRow(const size_t & index,
                             CMatrix< C_INT64 > & nullspaceMatrix)
{
  CZeroSet::CIndex Index(mFirstUnconvertedRow);

  iterator it = array();

  C_INT64 * pValue = & nullspaceMatrix(index, 0);

  if (mFirstUnconvertedRow != index)
    {
      C_INT64 * pFirstUnconvertedValue = & nullspaceMatrix(mFirstUnconvertedRow, 0);

      for (; it != mInsert; ++it, ++pValue, ++pFirstUnconvertedValue)
        {
          // At this point the matrix is compact since no columns have been destroyed,
          // i.e., we do not need to check whether *it != NULL.
          assert(*pValue >= 0);

          if (*pValue > 0)
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
      for (; it != mInsert; ++it, ++pValue)
        {
          if (*pValue != 0)
            {
              (*it)->unsetBit(Index);
            }
        }
    }

  mFirstUnconvertedRow++;
}

void CStepMatrix::compact()
{
  iterator from = array();
  iterator to = array();

  for (; from != mInsert; ++from)
    {
      if (*from != NULL)
        {
          (*from)->setIterator(to);
          *to = *from;

          ++to;
        }
    }

  mInsert = to;
}

std::ostream & operator << (std::ostream & os, const CStepMatrix & m)
{
  os << m.mPivot << std::endl;

  CZeroSet::CIndex Bit;

  CStepMatrix::const_iterator it;
  CStepMatrix::const_iterator end = m.end();

  for (it = m.begin(); it != end; ++it)
    {
      os << **it << std::endl;
    }

  return os;
}
