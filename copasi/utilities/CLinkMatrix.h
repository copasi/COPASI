// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CLinkMatrix
#define COPASI_CLinkMatrix

#include "copasi/utilities/CVector.h"
#include "copasi/utilities/CMatrix.h"

template <class CType> class CCopasiVector;
class CCopasiObject;

class CLinkMatrix: public CMatrix< C_FLOAT64 >
{
public:
  /**
   * Default constructor
   */
  CLinkMatrix();

  /**
   * Destructor
   */
  virtual ~CLinkMatrix();

  /**
   * Build the link matrix for the given matrix
   * @param const CMatrix< C_FLOAT64 > & matrix
   * @return bool success
   */
  bool build(const CMatrix< C_FLOAT64 > & matrix);

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
   * @return const size_t & numDependent
   */
  const size_t & getNumDependent() const;

  /**
   * Apply the row pivot
   * @param CMatrix< C_FLOAT64 > & matrix
   * @return bool success
   */
  bool applyRowPivot(CMatrix< C_FLOAT64 > & matrix) const;

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
  CVector< size_t > mRowPivots;

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
  CLinkMatrixView(const CLinkMatrix & A,
                  const size_t & numIndependent);

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
