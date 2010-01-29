// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CStepMatrix.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/01/29 21:59:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CStepMatrix
#define COPASI_CStepMatrix

#include <list>
#include <vector>

#include "copasi/elementaryFluxModes/CStepMatrixColumn.h"
#include "copasi/utilities/CVector.h"

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
  CStepMatrix(CMatrix< C_INT32 > & nullspaceMatrix);

  ~CStepMatrix();

public:

  const_iterator begin() const;

  const_iterator end() const;

  void convertRow();

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

  // TODO CRITICAL Remove Debug Code
  void removeColumn(CStepMatrixColumn * pColumn);

  bool splitColumns(std::vector< CStepMatrixColumn * > & PositiveColumns,
                    std::vector< CStepMatrixColumn * > & NegativeColumns,
                    std::vector< CStepMatrixColumn * > & NullColumns);

  void removeInvalidColumns(std::vector< CStepMatrixColumn * > & invalidColumns);

  void compact();

  void getUnsetBitIndexes(const CStepMatrixColumn * pColumn,
                          CVector< size_t > & indexes) const;

private:
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

            memset(mInsert, NULL, OldSize * sizeof(CStepMatrixColumn *));

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

  void convertRow(const size_t & index,
                  CMatrix< C_INT32 > & nullspaceMatrix);

  // Attributes
private:
  size_t mRows;

  CVector< size_t > mPivot;

  size_t mFirstUnconvertedRow;

  iterator mInsert;

  iterator mBeyond;
};

#endif // COPASI_CStepMatrix
