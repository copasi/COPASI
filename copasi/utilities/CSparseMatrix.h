// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSparseMatrix.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/25 17:15:54 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

///////////////////////////////////////////////////////////
//  CSparseMatrix.h
//  Implementation of the Class CSparseMatrix
//  Created on:      29-Jun-2004 16:52:05
///////////////////////////////////////////////////////////

#ifndef COPASI_CSparseMatrix
#define COPASI_CSparseMatrix

#include <vector>
#include <cstddef>

class CCompressedColumnFormat;
class CSparseMatrix;
template < typename ValueType > class CMatrix;

class CSparseMatrixElement
{
  // Operations
private:
  CSparseMatrixElement();

public:
  CSparseMatrixElement(CSparseMatrix & matrix,
                       const size_t & rowIndex,
                       const size_t & colIndex,
                       const C_FLOAT64 & value);

  ~CSparseMatrixElement();

  const C_FLOAT64 & operator = (const C_FLOAT64 & value);
  operator const C_FLOAT64 & () const;

  const size_t & row() const;
  const size_t & col() const;

  static bool compareRow(const CSparseMatrixElement * pLhs,
                         const CSparseMatrixElement * pRhs);
  static bool compareCol(const CSparseMatrixElement * pLhs,
                         const CSparseMatrixElement * pRhs);

  // Attributes
private:
  CSparseMatrix & mMatrix;
  const size_t & mRow;
  const size_t & mCol;
  C_FLOAT64 mValue;
};

class CSparseMatrix
{
  // Operations
public:
  CSparseMatrix(const size_t & rows = 0,
                const size_t & cols = 0);
  CSparseMatrix(const CCompressedColumnFormat & ccf);
  ~CSparseMatrix();
  bool resize(const size_t & rows, const size_t & columns);
  const size_t & numRows() const;
  const size_t & numCols() const;
  size_t numNonZeros() const;

  const std::vector< std::vector< CSparseMatrixElement *> > & getColumns() const;
  std::vector< std::vector< CSparseMatrixElement *> > & getColumns();
  const std::vector< std::vector< CSparseMatrixElement *> > & getRows() const;
  std::vector< std::vector< CSparseMatrixElement *> > & getRows();

  CSparseMatrix & operator = (const CCompressedColumnFormat & ccf);
  CSparseMatrix & operator = (const CMatrix< C_FLOAT64 > & matrix);
  operator const CMatrix< C_FLOAT64 > () const;

  bool setTreshold(const C_FLOAT64 & threshold);
  const C_FLOAT64 & getTreshold() const;

  CSparseMatrixElement & operator()(const size_t & row,
                                    const size_t & col);

  const CSparseMatrixElement & operator()(const size_t & row,
                                          const size_t & col) const;

  bool insert(const size_t & row,
              const size_t & col,
              const C_FLOAT64 & value);
  bool remove(const size_t & row,
              const size_t & col);

  friend std::ostream &operator <<(std::ostream &os,
                                   const CSparseMatrix & A);

private:
  void cleanup();

  // Attributes
private:
  C_FLOAT64 mThreshold;

  size_t mNumRows;
  size_t mNumCols;

  std::vector< size_t > mRowIndex;
  std::vector< size_t> mColIndex;

  std::vector< std::vector< CSparseMatrixElement *> > mRows;
  std::vector< std::vector< CSparseMatrixElement *> > mCols;

  size_t mSearchRow;
  size_t mSearchCol;
  CSparseMatrixElement mElement;
};

class CCompressedColumnFormat
{
  // Attributes
private:
  size_t mNumRows;
  size_t mNumCols;
  size_t * mpColumnStart;
  size_t * mpRowIndex;
  C_FLOAT64 * mpValue;

  // Operations
private:
  CCompressedColumnFormat();

  // Iterator
public:
#if (defined __GNUC__ && __GNUC__ < 3)
  class const_row_iterator: public std::forward_iterator< C_FLOAT64, ptrdiff_t >
#else
  class const_row_iterator:
      public std::iterator< std::forward_iterator_tag, C_FLOAT64, ptrdiff_t >
#endif

  {
  public:
    /**
     * Default constructor.
     */
    const_row_iterator(const CCompressedColumnFormat * pMatrix = NULL,
                       const size_t & rowIndex = C_INVALID_INDEX);

    /**
     * Copy constructor
     * @param const iterator & src
     */
    const_row_iterator(const const_row_iterator & src);

    /**
     * Destructor
     */
    ~const_row_iterator();

    /**
     * Dereference operator * returns the node the iterator points to.
     * @return C_FLOAT64 &
     */
    const C_FLOAT64 & operator*() const;

    /**
     * Dereference operator * returns the node the iterator points to.
     * @return C_FLOAT64 &
     */
    const C_FLOAT64 & operator->() const;

    /**
     * Comparison operator !=
     * @param const const_row_iterator & rhs
     * @return bool not-equal
     */
    bool operator!=(const const_row_iterator & rhs);

    /**
     * Assignement operator from a node to an iterator
     * @param const const_row_iterator & rhs
     * @return iterator &
     */
    const_row_iterator & operator=(const const_row_iterator & rhs);

    /**
     * Prefix increment operator ++
     * @return iterator &
     */
    const_row_iterator & operator++();

    const size_t & getColumnIndex() const;

  private:
    // Attributes
    const CCompressedColumnFormat * mpMatrix;

    size_t mRowIndex;

    const size_t *mpRowIndex;

    size_t mColumnIndex;

    const size_t *mpColumnIndex;

    const C_FLOAT64 *mpCurrent;
  };

  CCompressedColumnFormat(const size_t & rows,
                          const size_t & columns,
                          const size_t & nonZeros);
  CCompressedColumnFormat(const CSparseMatrix & matrix);
  ~CCompressedColumnFormat();

  size_t numRows() const;
  size_t numCols() const;
  size_t numNonZeros() const;
  const C_FLOAT64 * getValues() const;
  C_FLOAT64 * getValues();
  const size_t * getRowIndex() const;
  size_t * getRowIndex();
  const size_t * getColumnStart() const;
  size_t * getColumnStart();
  CCompressedColumnFormat & operator = (const CSparseMatrix & ccf);

  const_row_iterator beginRow(const size_t & row) const;
  const_row_iterator endRow(const size_t & row) const;
};

#ifdef COPASI_DEBUG
bool SparseMatrixTest(const size_t & size,
                      const C_FLOAT64 & sparseness,
                      const unsigned C_INT32 & seed = 0,
                      const bool & RMP = true,
                      const bool & DGEMM = true,
                      const bool & SMP = true,
                      const bool & CCMP = true);
#endif

#endif // COPASI_CSparseMatrix
