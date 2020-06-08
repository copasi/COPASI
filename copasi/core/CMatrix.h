// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CMatrix
#define COPASI_CMatrix

#include <algorithm> // for std::min
#include <iostream>
#include <assert.h>
#include <string.h>

#include "copasi/core/CVector.h"
#include "copasi/copasi.h"

#undef min
#undef max

template<typename CType> class CMatrix;

template <class CType>
std::ostream &operator<<(std::ostream &os, const CMatrix< CType > & A);

template <class Matrix> class CTransposeView;

template <class Matrix>
std::ostream &operator << (std::ostream &os, const CTransposeView< Matrix > & A);

template <class Matrix> class CLowerTriangularView;

template <class Matrix>
std::ostream &operator<<(std::ostream &os, const CLowerTriangularView< Matrix > & A);

template <class Matrix> class CUpperTriangularView;

template <class Matrix>
std::ostream &operator<<(std::ostream &os, const CUpperTriangularView< Matrix > & A);

template <class Matrix> class CUnitUpperTriangularView;

template <class Matrix>
std::ostream &operator << (std::ostream &os, const CUnitUpperTriangularView< Matrix > & A);

template <class Matrix> class CUnitLowerTriangularView;

template <class Matrix>
std::ostream &operator << (std::ostream &os, const CUnitLowerTriangularView< Matrix > & A);

/**
 * Template class CMatrix < class CType >
 * This template class is a simple matrix class  allowing standard
 * C-style and fortran style access to the elements. It also supplies
 * an ostream operator.
 */
template <class CType>
class CMatrix
{
public:
  typedef CType elementType;

  // Attributes
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
   * The array storing the matrix elements
   */
  CType * mpBuffer;

  // Operations
public:
  /**
   * Default constructor
   * @param size_t rows (default = 0)
   * @param size_t cols (default = 0)
   */
  CMatrix(size_t rows = 0, size_t cols = 0) :
    mRows(0),
    mCols(0),
    mpBuffer(NULL)
  {
    resize(rows, cols);
  }

  /**
   * Copy constructor
   * @param const CMatrix <CType> & src
   */
  CMatrix(const CMatrix <CType> & src):
    mRows(0),
    mCols(0),
    mpBuffer(NULL)
  {
    resize(src.mRows, src.mCols);

    if (mRows && mCols)
      memcpy(mpBuffer, src.mpBuffer, mRows * mCols * sizeof(CType));
  }

  /**
   * Destructor.
   */
  virtual ~CMatrix()
  {
    if (mpBuffer)
      delete [] mpBuffer;
  }

  /**
   * The number of elements stored in the matrix.
   * @return size_t size
   */
  virtual size_t size() const {return mRows * mCols;}

  /**
   * The number of rows of the matrix.
   * @return size_t rows
   */
  virtual size_t numRows() const {return mRows;}

  /**
   * The number of columns of the matrix
   * @return size_t cols
   */
  virtual size_t numCols() const {return mCols;}

  /**
   * Resize the matrix. The previous content is lost
   * @param size_t rows
   * @param size_t cols
   */
  virtual void resize(size_t rows, size_t cols, const bool & copy = false)
  {
    if (rows != mRows ||  cols != mCols)
      {
        size_t OldRows = mRows;
        size_t OldCols = mCols;
        CType * OldArray = mpBuffer;
        mpBuffer = NULL;

        if (rows != 0 && cols != 0)
          {
            try
              {
                // We need to detect size_t overflow
                if ((C_FLOAT64) rows * (C_FLOAT64) cols * (C_FLOAT64) sizeof(CType) >= (C_FLOAT64) std::numeric_limits< size_t >::max())
                  {
                    mpBuffer = NULL;
                  }
                else
                  {
                    mpBuffer = new CType[rows * cols];
                  }
              }

            catch (...)
              {
                mpBuffer = NULL;
              }

            if (mpBuffer == NULL)
              {
                mRows = 0;
                mCols = 0;

                CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, rows * cols * sizeof(CType));
              }

            if (copy &&
                mpBuffer != NULL &&
                OldArray != NULL)
              {
                // We copy the top left matrix (min(rows, OldRows), min(cols, OldCols);
                size_t CopiedRows = std::min(rows, OldRows);
                size_t CopiedColumns = std::min(cols, OldCols);

                CType * pOldRow = OldArray;
                CType * pOldRowEnd = pOldRow +  CopiedRows * OldCols;
                CType * pRow = mpBuffer;

                for (; pOldRow != pOldRowEnd; pOldRow += OldCols, pRow += cols)
                  {
                    memcpy(pRow, pOldRow, CopiedColumns * sizeof(CType));
                  }
              }
          }

        if (OldArray)
          {
            delete [] OldArray;
          }
      }

    mRows = rows;
    mCols = cols;
  }

  /**
   * Assignment operator
   * @param const CMatrix <CType> & rhs
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator = (const CMatrix <CType> & rhs)
  {
    if (this == &rhs)
      return *this;

    // Independent from whether the mpBuffer or rhs.mpBuffer is NULL we need to resize;
    if (mRows != rhs.mRows || mCols != rhs.mCols)
      resize(rhs.mRows, rhs.mCols);

    // don't use memcpy on NULL buffers
    if (rhs.mpBuffer != NULL && mpBuffer != NULL)
      memcpy(mpBuffer, rhs.mpBuffer, mRows * mCols * sizeof(CType));

    return *this;
  }

  /**
   * Assignment operator
   * @param const CType & value
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator = (const CType & value)
  {
    CType * pIt = mpBuffer;
    CType * pEnd = pIt + mRows * mCols;

    for (; pIt != pEnd; ++pIt) *pIt = value;

    return *this;
  }

#ifdef XXXX
  /**
   * Scalar multiplication operator
   * @param const CType & value
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator *(const CType & value)
  {
    size_t i, imax = mRows * mCols;
    CType * tmp = mpBuffer;

    for (i = 0; i < imax; i++, tmp++) *tmp *= value;

    return *this;
  }

  /**
   * Scalar division operator
   * @param const CType & value
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator / (const CType & value)
  {return (*this) * (1.0 / value);}

  /**
   * + operator
   * @param const CMatrix <CType> & rhs
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator + (const CMatrix <CType> & rhs)
  {
    assert(mRows == rhs.mRows && mCols == rhs.mCols);

    size_t i, imax = mRows * mCols;
    CType * tmp1 = mpBuffer;
    CType * tmp2 = rhs.mpBuffer;

    for (i = 0; i < imax; i++, tmp1++, tmp2++) *tmp1 += *tmp2;

    return *this;
  }
#endif // XXXX

  /**
   * Retrieve a row of the matrix using c-style indexing
   * @param size_t row
   * @return CType * row
   */
  virtual inline CType * operator[](size_t row)
  {return mpBuffer + row * mCols;}

  /**
   * Retrieve a row of the matrix using c-style indexing
   * @param size_t row
   * @return const CType * row
   */
  virtual inline const CType * operator[](size_t row) const
  {return mpBuffer + row * mCols;}

  /**
   * Retrieve a matrix element using c-style indexing.
   * @param const size_t & row
   * @param const size_t & col
   * @return const elementType & element
   */
  virtual inline elementType & operator()(const size_t & row,
                                          const size_t & col)
  {
    assert(row < mRows && col < mCols);
    return *(mpBuffer + row * mCols + col);
  }

  /**
   * Retrieve a matrix element using c-style indexing.
   * @param const size_t & row
   * @param const size_t & col
   * @return const elementType & element
   */
  virtual inline const elementType & operator()(const size_t & row,
      const size_t & col) const
  {
    assert(row < mRows && col < mCols);
    return *(mpBuffer + row * mCols + col);
  }

  /**
   * Retrieve the array of the matrix elements. This is suitable
   * for interfacing with clapack routines.
   * @return CType * array
   */
  virtual CType * array() {return mpBuffer;}

  /**
   * Retrieve the array of the matrix elements. This is suitable
   * for interfacing with clapack routines.
   * @return const CType * array
   */
  virtual const CType * array() const {return mpBuffer;}

  /**
   * Reorder the rows according to the provided pivots
   * @param const CVector<size_t> & pivot
   * @return bool success
   */
  bool applyPivot(const CVector<size_t> & pivot)
  {
    if (pivot.size() != mRows) return false;

    CVector< bool > Applied(mRows);
    Applied = false;
    CType *pTmp = new CType[mCols];

    size_t i;
    size_t to;
    size_t from;

    for (i = 0; i < mRows; i++)
      if (!Applied[i])
        {
          to = i;
          from = pivot[i];

          if (to != from)
            {
              memcpy(pTmp, mpBuffer + i * mCols, mCols * sizeof(CType));

              while (from != i)
                {
                  memcpy(mpBuffer + to * mCols, mpBuffer + from * mCols, mCols * sizeof(CType));
                  Applied[to] = true;

                  to = from;
                  from = pivot[to];
                }

              memcpy(mpBuffer + to * mCols, pTmp, mCols * sizeof(CType));
            }

          Applied[to] = true;
        }

    pdeletev(pTmp);
    return true;
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CMatrix< CType > & A
   * @return ostream & os
   */
#if defined SWIG
  friend std::ostream &operator <<(std::ostream &os,
                                   const CMatrix< CType > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend std::ostream &operator <<(std::ostream &os,
                                   const CMatrix< CType > & A);
#else
  friend std::ostream &operator << <> (std::ostream &os,
                                       const CMatrix< CType > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CFortranAccess
{
public:
  typedef typename Matrix::elementType elementType;

private:
  Matrix & mA;

public:
  CFortranAccess(Matrix & A):
    mA(A)
  {}

  ~CFortranAccess() {}

  /**
   * Retrieve a row of the matrix using Fortran style indexing.
   * @param size_t row
   * @return elementType * row
   */
  inline elementType * operator[](size_t row)
  {return mA[row - 1] - 1;}

  /**
   * Retrieve a row of the matrix using Fortran style indexing.
   * @param size_t row
   * @return const elementType * row
   */
  inline const elementType * operator[](size_t row) const
  {return mA[row - 1] - 1;}

  /**
   * Retrieve a matrix element using Fortran style indexing.
   * @param const size_t & row
   * @param const size_t & col
   * @return const elementType & element
   */
  inline elementType & operator()(const size_t & row,
                                  const size_t & col)
  {return mA(row - 1, col - 1);}

  /**
   * Retrieve a matrix element using Fortran style indexing.
   * @param const size_t & row
   * @param const size_t & col
   * @return const elementType & element
   */
  inline const elementType & operator()(const size_t & row,
                                        const size_t & col) const
  {return mA(row - 1, col - 1);}
};

template <class Matrix>
class CUpperTriangularView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;
  elementType mZero;

public:
  CUpperTriangularView(const Matrix & A, const elementType zero):
    mA(A),
    mZero(zero)
  {}

  ~CUpperTriangularView() {}

  /**
   * The number of rows of the matrix.
   * @return size_t rows
   */
  size_t numRows() const {return mA.numRows();}

  /**
   * The number of columns of the matrix
   * @return size_t cols
   */
  size_t numCols() const {return mA.numCols();}

  /**
   * Retrieve a matrix element using the indexing style of the matrix.
   * @param const size_t & row
   * @param const size_t & col
   * @return elementType element
   */
  inline elementType operator()(const size_t & row,
                                const size_t & col) const
  {
    if (row > col)
      return mZero;
    else
      return mA(row, col);
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CUpperTriangularView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUpperTriangularView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUpperTriangularView< Matrix > & A);
#else
  friend
  std::ostream &operator << <>(std::ostream &os,
                               const CUpperTriangularView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CLowerTriangularView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;
  elementType mZero;

public:
  CLowerTriangularView(const Matrix & A, const elementType zero):
    mA(A),
    mZero(zero)
  {}

  ~CLowerTriangularView() {}

  /**
   * The number of rows of the matrix.
   * @return size_t rows
   */
  size_t numRows() const {return mA.numRows();}

  /**
   * The number of columns of the matrix
   * @return size_t cols
   */
  size_t numCols() const {return mA.numCols();}

  /**
   * Retrieve a matrix element using the indexing style of the matrix.
   * @param const size_t & row
   * @param const size_t & col
   * @return elementType element
   */
  inline elementType operator()(const size_t & row,
                                const size_t & col) const
  {
    if (row < col)
      return mZero;
    else
      return mA(row, col);
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CLowerTriangularView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CLowerTriangularView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CLowerTriangularView< Matrix > & A);
#else
  friend
  std::ostream &operator << <>(std::ostream &os,
                               const CLowerTriangularView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CUnitUpperTriangularView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;
  elementType mZero;
  elementType mUnit;

public:
  CUnitUpperTriangularView(const Matrix & A,
                           const elementType zero,
                           const elementType unit):
    mA(A),
    mZero(zero),
    mUnit(unit)
  {}

  ~CUnitUpperTriangularView() {}

  /**
   * The number of rows of the matrix.
   * @return size_t rows
   */
  size_t numRows() const {return mA.numRows();}

  /**
   * The number of columns of the matrix
   * @return size_t cols
   */
  size_t numCols() const {return mA.numCols();}

  /**
   * Retrieve a matrix element  using the indexing style of the matrix.
   * @param const size_t & row
   * @param const size_t & col
   * @return elementType element
   */
  inline elementType operator()(const size_t & row,
                                const size_t & col) const
  {
    if (row < col)
      return mA(row, col);
    else if (row > col)
      return mZero;
    else
      return mUnit;
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CUnitUpperTriangularView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUnitUpperTriangularView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUnitUpperTriangularView< Matrix > & A);
#else
  friend
  std::ostream &operator << <>(std::ostream &os,
                               const CUnitUpperTriangularView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CUnitLowerTriangularView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;
  elementType mZero;
  elementType mUnit;

public:
  CUnitLowerTriangularView(const Matrix & A,
                           const elementType zero,
                           const elementType unit):
    mA(A),
    mZero(zero),
    mUnit(unit)
  {}

  ~CUnitLowerTriangularView() {}

  /**
   * The number of rows of the matrix.
   * @return size_t rows
   */
  size_t numRows() const {return mA.numRows();}

  /**
   * The number of columns of the matrix
   * @return size_t cols
   */
  size_t numCols() const {return mA.numCols();}

  /**
   * Retrieve a matrix element using the indexing style of the matrix.
   * @param const size_t & row
   * @param const size_t & col
   * @return elementType element
   */
  inline elementType operator()(const size_t & row,
                                const size_t & col) const
  {
    if (row > col)
      return mA(row, col);
    else if (row < col)
      return mZero;
    else
      return mUnit;
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CUnitLowerTriangularView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUnitLowerTriangularView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUnitLowerTriangularView< Matrix > & A);
#else
  friend
  std::ostream &operator << <> (std::ostream &os,
                                const CUnitLowerTriangularView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CTransposeView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;

public:
  CTransposeView(const Matrix & A): mA(A) {}

  ~CTransposeView() {}

  /**
   * The number of rows of the matrix.
   * @return size_t rows
   */
  size_t numRows() const {return mA.numCols();}

  /**
   * The number of columns of the matrix
   * @return size_t cols
   */
  size_t numCols() const {return mA.numRows();}

  /**
   * Retrieve a matrix element using the indexing style of the matrix.
   * @param const size_t & row
   * @param const size_t & col
   * @return elementType element
   */
  inline elementType operator()(const size_t & row,
                                const size_t & col) const
  {return mA(col, row);}

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CTransposeView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CTransposeView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CTransposeView< Matrix > & A);
#else
  friend
  std::ostream &operator << <>(std::ostream &os,
                               const CTransposeView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class CType>
std::ostream &operator<<(std::ostream &os, const CMatrix< CType > & A)
{
  os << "Matrix(" << A.mRows << "x" << A.mCols << ")" << std::endl;

  size_t i, j;
  CType * tmp = A.mpBuffer;

  for (i = 0; i < A.mRows; i++)
    {
      for (j = 0; j < A.mCols; j++)
        os << "\t" << *(tmp++);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator<<(std::ostream &os,
                         const CUpperTriangularView< Matrix > & A)
{
  size_t i, imax = A.numRows();
  size_t j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator<<(std::ostream &os,
                         const CLowerTriangularView< Matrix > & A)
{
  size_t i, imax = A.numRows();
  size_t j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator << (std::ostream &os,
                           const CUnitUpperTriangularView< Matrix > & A)
{
  size_t i, imax = A.numRows();
  size_t j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator << (std::ostream &os,
                           const CUnitLowerTriangularView< Matrix > & A)
{
  size_t i, imax = A.numRows();
  size_t j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator << (std::ostream &os,
                           const CTransposeView< Matrix > & A)
{
  size_t i, imax = A.numRows();
  size_t j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

#endif // COPASI_CMatrix
