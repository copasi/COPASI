// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CLinkMatrix
#define COPASI_CLinkMatrix

#include "copasi/core/CVector.h"
#include "copasi/core/CMatrix.h"

template <class CType> class CDataVector;
class CDataObject;

class CLinkMatrix: public CMatrix< C_FLOAT64 >
{
public:
  /**
   * Default constructor
   */
  CLinkMatrix();

  /**
   * Copy constructor
   */
  CLinkMatrix(const CLinkMatrix & src);

  /**
   * Destructor
   */
  virtual ~CLinkMatrix();

  /**
   * Build the link matrix for the given matrix
   * @param const CMatrix< C_FLOAT64 > & matrix
   * @param size_t maxRank (default: C_INVALID_INDEX)
   * @return bool success
   */
  bool build(const CMatrix< C_FLOAT64 > & matrix, size_t maxRank = C_INVALID_INDEX);

  /**
   * Clear the pivot and swap vectors
   */
  void clearPivoting();

  /**
   * Right multiply the given matrix M with L, i.e., P = alpha M * L.
   * Note the columns of M must be in the same order as L.
   * @param const C_FLOAT64 & alpha
   * @param const CMatrix< C_FLOAT64> & M
   * @param CMatrix< C_FLOAT64> & P
   * @result bool success;
   */
  bool rightMultiply(const C_FLOAT64 & alpha, const CMatrix< C_FLOAT64> & M, CMatrix< C_FLOAT64> & P) const;

  /**
   * Left multiply the given matrix M with L, i.e., P = L * M
   * @param const CMatrix< C_FLOAT64> & M
   * @param CMatrix< C_FLOAT64> & P
   * @result bool success;
   */
  bool leftMultiply(const CMatrix< C_FLOAT64> & M, CMatrix< C_FLOAT64> & P) const;

  /**
   * Retrieve the pivot vector used to create the link matrix
   * @return const CVector< size_t > & rowPivots
   */
  const CVector< size_t > & getRowPivots() const;

  /**
   * Retrieve the number of linear independent rows of the input matrix
   * @return const size_t & numIndependent
   */
  const size_t & getNumIndependent() const;

  /**
   * Retrieve the number of linear dependent rows of the input matrix
   * @return size_t numDependent
   */
  size_t getNumDependent() const;

  /**
   * Do the row pivot
   * @param CMatrix< C_FLOAT64 > & matrix
   * @return bool success
   */
  bool doRowPivot(CMatrix< C_FLOAT64 > & matrix) const;

  /**
   * Undo the row pivot
   * @param CMatrix< C_FLOAT64 > & matrix
   * @return bool success
   */
  bool undoRowPivot(CMatrix< C_FLOAT64 > & matrix) const;

  /**
   * Do the column pivot
   * @param CMatrix< C_FLOAT64 > & matrix
   * @return bool success
   */
  bool doColumnPivot(CMatrix< C_FLOAT64 > & matrix) const;

  /**
   * Undo the column pivot
   * @param CMatrix< C_FLOAT64 > & matrix
   * @return bool success
   */
  bool undoColumnPivot(CMatrix< C_FLOAT64 > & matrix) const;

  /**
   * Apply the row pivot
   * @param CVectorCore< class CType > & vector
   * @return bool success
   */
  template <class CType> bool applyRowPivot(CVectorCore< CType > & vector) const
  {
    if (vector.size() < mRowPivots.size())
      {
        return false;
      }

    CVector< bool > Applied(mRowPivots.size());
    Applied = false;

    CType Tmp;

    size_t i, imax = mRowPivots.size();
    size_t to;
    size_t from;

    for (i = 0; i < imax; i++)
      if (!Applied[i])
        {
          to = i;
          from = mRowPivots[to];

          if (from != i)
            {
              Tmp = vector[to];

              while (from != i)
                {
                  vector[to] = vector[from];
                  Applied[to] = true;

                  to = from;
                  from = mRowPivots[to];
                }

              vector[to] = Tmp;
            }

          Applied[to] = true;
        }

    return true;
  }

private:
  /**
   * Internal method performing apply and undo of column pivoting.
   * @param CMatrix< C_FLOAT64 > & matrix
   * @param const C_INT & incr
   * @return bool success
   */
  bool applyColumnPivot(CMatrix< C_FLOAT64 > & matrix, const C_INT & incr) const;

  /**
   * Internal method performing apply and undo of row pivoting.
   * @param CMatrix< C_FLOAT64 > & matrix
   * @param const CVector< size_t > & pivots
   * @return bool success
   */
  bool applyRowPivot(CMatrix< C_FLOAT64 > & matrix,
                     const CVector< size_t > & pivots) const;

  /**
   * Complete the pivot information.
   */
  void completePivotInformation();

  /**
   * The row pivoting performed to create the link matrix
   */
  CVector< size_t > mRowPivots;

  /**
   * The pivot vector used for undoing row swapping
   */
  CVector< size_t > mPivotInverse;

  /**
   *  The swap vector used for column swapping
   */
  CVector< C_INT > mSwapVector;

  /**
   * The number of linear independent rows.
   */
  size_t mIndependent;
};

class CLinkMatrixView
{
public:
  typedef  C_FLOAT64 elementType;

private:
  const CLinkMatrix * mpA;
  const size_t * mpNumIndependent;
  static const C_FLOAT64 mZero;
  static const C_FLOAT64 mUnit;

public:
  /**
   * Default constructor
   * @param const const CLinkMatrix & A
   * @param const size_t & mNumIndependent
   */
  CLinkMatrixView(const CLinkMatrix & A);

  /**
   * Destructor.
   */
  ~CLinkMatrixView();

  /**
   * Assignment operator
   * @param const CLinkMatrixView & rhs
   * @return CLinkMatrixView & lhs
   */
  CLinkMatrixView & operator = (const CLinkMatrixView & rhs);

  /**
   * The number of rows of the matrix.
   * @return size_t rows
   */
  size_t numRows() const;

  /**
   * The number of columns of the matrix
   * @return size_t cols
   */
  size_t numCols() const;

  /**
   * Retrieve a matrix element  using the c-style indexing.
   * @param const size_t & row
   * @param const size_t & col
   * @return elementType & element
   */
  inline C_FLOAT64 & operator()(const size_t & row,
                                const size_t & col) const
  {
    if (row >= *mpNumIndependent)
      return *const_cast< C_FLOAT64 * >(&(*mpA)(row - *mpNumIndependent, col));
    else if (row != col)
      return *const_cast< C_FLOAT64 * >(&mZero);
    else
      return *const_cast< C_FLOAT64 * >(&mUnit);
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CLinkMatrixView & A
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os,
                                  const CLinkMatrixView & A);
};

#endif // COPASI_CLinkMatrix
