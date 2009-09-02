// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CStepMatrix.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/02 19:21:19 $
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

template <class CType> class CMatrix;

class CStepMatrix: public std::list< CStepMatrixColumn * >
{
public:
  typedef std::list< CStepMatrixColumn * >::iterator iterator;
  typedef std::list< CStepMatrixColumn * >::const_iterator const_iterator;

  friend std::ostream & operator << (std::ostream &, const CStepMatrix &);

  // Operations
private:
  CStepMatrix();

public:
  CStepMatrix(CMatrix< C_FLOAT64 > & nullspaceMatrix);

  ~CStepMatrix();

  inline void add(CStepMatrixColumn * pColumn)
  {
    if (pColumn != NULL)
      {
        push_back(pColumn);
      }
  }

  inline void remove(CStepMatrixColumn * pColumn)
  {
    if (pColumn != NULL)
      {
        remove(pColumn);
        delete pColumn;
      }
  }

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

  bool splitColumns(std::list< CStepMatrixColumn * > & PositiveColumns,
                    std::list< CStepMatrixColumn * > & NegativeColumns,
                    std::list< CStepMatrixColumn * > & NullColumns);

  void removeInvalidColumns(const std::vector< CStepMatrixColumn * > & invalidColumns);

  void getSetBitIndexes(const CStepMatrixColumn * pColumn,
                        CVector< size_t > & indexes) const;

private:
  void convertRow(const size_t & index,
                  CMatrix< C_FLOAT64 > & nullspaceMatrix);

  // Attributes
private:
  size_t mRows;

  CVector< size_t > mPivot;

  size_t mFirstUnconvertedRow;
};

#endif // COPASI_CStepMatrix
