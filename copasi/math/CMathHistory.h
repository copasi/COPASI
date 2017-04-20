// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathHistory
#define COPASI_CMathHistory

#include "copasi/core/CVector.h"

class CMathHistoryCore: protected CVectorCore< C_FLOAT64 >
{
public:
  CMathHistoryCore(const size_t & rows = 0,
                   const size_t & cols = 0,
                   const size_t & colsAllocated = 0,
                   C_FLOAT64 * pArray = NULL);

private:
  CMathHistoryCore(const CMathHistoryCore & src);

public:
  virtual ~CMathHistoryCore();

  C_FLOAT64 * operator [](const size_t & row);

  const CVectorCore< C_FLOAT64 > & getRow(const size_t & row);

  void setRow(const size_t & row, const CVectorCore< C_FLOAT64 > & values);

  /**
   * Initialize the core history to reference an externally allocated array
   * @param const size_t & rows
   * @param const size_t & cols
   * @param const size_t & colsAllocated
   * @param C_FLOAT64 * pArray
   */
  void initialize(const size_t & rows,
                  const size_t & cols,
                  const size_t & colsAllocated,
                  C_FLOAT64 * pArray);

  /**
   * Initialize the core vector to reference an other core vector.
   * @param const CMathHistoryCore & src
   */
  void initialize(const CMathHistoryCore & src);

  CMathHistoryCore & operator = (const CMathHistoryCore & rhs);

  const size_t & rows() const;

  const size_t & cols() const;

  const size_t & colsAllocated() const;

  const size_t & size() const;

  C_FLOAT64 * array();

  const C_FLOAT64 * array() const;

protected:
  /**
   * Number of rows in the matrix.
   */
  size_t mRows;

  /**
   * Number of columns in the matrix
   */
  size_t mCols;

  /**
   * Number of columns allocated
   */
  size_t mColsAllocated;
};

class CMathHistory: public CMathHistoryCore
{
public:
  CMathHistory(const size_t & rows = 0,
               const size_t & cols = 0,
               const size_t & colsAllocated = 0);

  CMathHistory(const CMathHistoryCore & src);

  CMathHistory(const CMathHistory & src);

  virtual ~CMathHistory();

  CMathHistory & operator = (const CMathHistoryCore & rhs);

  CMathHistory & operator = (const CMathHistory & rhs);

  void resize(const size_t & rows,
              const size_t & cols,
              const size_t & colsAllocated);

protected:
  void copy(const CMathHistoryCore & src);
};

#endif // COPASI_CMathHistory
