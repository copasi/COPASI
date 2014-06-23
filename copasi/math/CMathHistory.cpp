// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CMathHistory.h"

CMathHistoryCore::CMathHistoryCore(const size_t & rows,
                                   const size_t & cols,
                                   const size_t & colsAllocated,
                                   C_FLOAT64 * pArray):
  CVectorCore< C_FLOAT64 >(rows * colsAllocated, pArray),
  mRows(rows),
  mCols(cols),
  mColsAllocated(colsAllocated)
{
  assert(cols <= colsAllocated);
}

// virtual
CMathHistoryCore::~CMathHistoryCore()
{}

C_FLOAT64 * CMathHistoryCore::operator [](const size_t & row)
{
  return mVector + row * mColsAllocated;
}

CVectorCore< C_FLOAT64 > CMathHistoryCore::getRow(const size_t & row)
{
  return CVectorCore< C_FLOAT64 >(mCols, mVector + row * mColsAllocated);
}

void CMathHistoryCore::setRow(const size_t & row, const CVectorCore< C_FLOAT64 > & values)
{
  getRow(row) = values;
}

void CMathHistoryCore::initialize(const size_t & rows,
                                  const size_t & cols,
                                  const size_t & colsAllocated,
                                  C_FLOAT64 * pArray)
{
  assert(cols <= colsAllocated);

  CVectorCore< C_FLOAT64 >::initialize(rows * colsAllocated, pArray);

  mRows = rows;
  mCols = cols;
  mColsAllocated = colsAllocated;
}

void CMathHistoryCore::initialize(const CMathHistoryCore & src)
{
  CVectorCore< C_FLOAT64 >::initialize(src);

  mRows = src.mRows;
  mCols = src.mCols;
  mColsAllocated = src.mColsAllocated;
}

CMathHistoryCore & CMathHistoryCore::operator = (const CMathHistoryCore & rhs)
{
  *static_cast< CVectorCore< C_FLOAT64 > * >(this) =
    *static_cast<const CVectorCore< C_FLOAT64 > * >(&rhs);

  assert(mRows == rhs.mRows &&
         mCols == rhs.mCols &&
         mColsAllocated == rhs.mColsAllocated);

  return *this;
}

const size_t & CMathHistoryCore::rows() const
{
  return mRows;
}

const size_t & CMathHistoryCore::cols() const
{
  return mCols;
}

const size_t & CMathHistoryCore::colsAllocated() const
{
  return mColsAllocated;
}

const size_t & CMathHistoryCore::size() const
{
  return mSize;
}

C_FLOAT64 * CMathHistoryCore::array()
{
  return mVector;
}

const C_FLOAT64 * CMathHistoryCore::array() const
{
  return mVector;
}

CMathHistory::CMathHistory(const size_t & rows,
                           const size_t & cols,
                           const size_t & colsAllocated):
  CMathHistoryCore()
{
  resize(rows, cols, colsAllocated);
}

CMathHistory::CMathHistory(const CMathHistoryCore & src):
  CMathHistoryCore()
{
  copy(src);
}

CMathHistory::CMathHistory(const CMathHistory & src):
  CMathHistoryCore()
{
  copy(src);
}

// virtual
CMathHistory::~CMathHistory()
{
  pdelete(mVector);
}

CMathHistory & CMathHistory::operator = (const CMathHistoryCore & rhs)
{
  copy(rhs);

  return *this;
}

CMathHistory & CMathHistory::operator = (const CMathHistory & rhs)
{
  copy(rhs);

  return *this;
}

void CMathHistory::resize(const size_t & rows,
                          const size_t & cols,
                          const size_t & colsAllocated)
{
  assert(cols <= colsAllocated);

  mRows = rows;
  mCols = cols;
  mColsAllocated = colsAllocated;

  size_t NewSize = mRows * mColsAllocated;

  if (mSize == NewSize)
    {
      return;
    }

  pdelete(mVector);

  mSize = NewSize;

  if (mSize > 0)
    {
      try
        {
          // We need to detect size_t overflow
          if ((C_FLOAT64) mSize * (C_FLOAT64) sizeof(C_FLOAT64) >= (C_FLOAT64) std::numeric_limits< size_t >::max())
            {
              mVector = NULL;
            }
          else
            {
              mVector = new C_FLOAT64[mSize];
            }
        }

      catch (...)
        {
          mSize = 0;
          mVector = NULL;
        }
    }

  // Check if allocation failed
  if (mVector == NULL &&
      NewSize > 0)
    {
      mRows = 0;
      mCols = 0;
      mColsAllocated = 0;

      CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, NewSize * sizeof(C_FLOAT64));
    }
}

void CMathHistory::copy(const CMathHistoryCore & src)
{
  if (this != &src)
    {
      mRows = src.rows();
      mCols = src.cols();
      mColsAllocated = src.colsAllocated();

      if (mSize != src.size())
        {
          resize(mRows, mCols, mColsAllocated);
        }

      if (mSize != 0)
        {
          memcpy((void *) mVector,
                 (void *) src.array(),
                 mSize * sizeof(C_FLOAT64));
        }
    }
}
