// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CStepMatrix
#define COPASI_CStepMatrix

#include <algorithm> // for std::max
#include <list>
#include <vector>

#include "copasi/elementaryFluxModes/CStepMatrixColumn.h"
#include "copasi/core/CVector.h"

template <class CType> class CMatrix;

class CStepMatrix: private CVector< CStepMatrixColumn * >
{
private:
  typedef CStepMatrixColumn ** iterator;

public:
  typedef CStepMatrixColumn *const* const_iterator;

  friend std::ostream & operator << (std::ostream &, const CStepMatrix &);

  // Operations
private:
  CStepMatrix();

public:
  CStepMatrix(size_t rows);

  CStepMatrix(CMatrix< C_INT64 > & nullspaceMatrix);

  ~CStepMatrix();

public:

  const_iterator begin() const;

  const_iterator end() const;

  void add(CStepMatrixColumn * pColumn)
  {
    if (pColumn != NULL)
      {
        if (mInsert >= mBeyond)
          {
            size_t OldSize = size();

            resize(std::max((size_t) 2, 2 * OldSize), true);

            mInsert = array() + OldSize;
            mBeyond = array() + size();

            memset(mInsert, 0x0, OldSize * sizeof(CStepMatrixColumn *));

            //We need to update the iterators.
            iterator it = array();
            iterator end = mInsert;

            for (; it != end; ++it)
              {
                if (*it != NULL)
                  {
                    (*it)->setIterator(it);
                  }
              }
          }

        pColumn->setIterator(mInsert);
        *mInsert = pColumn;

        mInsert++;
      }

    return;
  }

  void convertRow();

  //void convertMatrix();

  size_t getFirstUnconvertedRow() const;

  size_t getNumUnconvertedRows() const;

  /**
   * Add the linear combination of the two columns to the step matrix if
   * appropriate and remove columns if necessary.
   * @param const CZeroSet & set
   * @param const CStepMatrixColumn * pPositive
   * @param const CStepMatrixColumn * pNegative
   * @return CStepMatrixColumn * pColumn
   */
  CStepMatrixColumn * addColumn(const CZeroSet & set,
                                const CStepMatrixColumn * pPositive,
                                const CStepMatrixColumn * pNegative);

  void removeColumn(CStepMatrixColumn * pColumn);

  bool splitColumns(std::vector< CStepMatrixColumn * > & PositiveColumns,
                    std::vector< CStepMatrixColumn * > & NegativeColumns,
                    std::vector< CStepMatrixColumn * > & NullColumns);

  void removeInvalidColumns(std::vector< CStepMatrixColumn * > & invalidColumns);

  void compact();

  void getAllUnsetBitIndexes(const CStepMatrixColumn * pColumn,
                             CVector<size_t> & indexes) const;

  void getUnsetBitIndexes(const CStepMatrixColumn * pColumn,
                          CVector< size_t > & indexes) const;

private:

  void convertRow(const size_t & index,
                  CMatrix< C_INT64 > & nullspaceMatrix);

  // Attributes
private:
  size_t mRows;

  CVector< size_t > mPivot;

  size_t mFirstUnconvertedRow;

  iterator mInsert;

  iterator mBeyond;
};

#endif // COPASI_CStepMatrix
