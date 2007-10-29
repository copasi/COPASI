// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSparseMatrix.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/10/29 13:17:19 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
                         const unsigned C_INT32 & rowIndex,
                         const unsigned C_INT32 & colIndex,
                         const C_FLOAT64 & value);

    ~CSparseMatrixElement();

    const C_FLOAT64 & operator = (const C_FLOAT64 & value);
    operator const C_FLOAT64 & () const;

    const unsigned C_INT32 & row() const;
    const unsigned C_INT32 & col() const;

    static bool compareRow(const CSparseMatrixElement * pLhs,
                           const CSparseMatrixElement * pRhs);
    static bool compareCol(const CSparseMatrixElement * pLhs,
                           const CSparseMatrixElement * pRhs);

    // Attributes
  private:
    CSparseMatrix & mMatrix;
    const unsigned C_INT32 & mRow;
    const unsigned C_INT32 & mCol;
    C_FLOAT64 mValue;
  };

class CSparseMatrix
  {
    // Operations
  public:
    CSparseMatrix(const unsigned C_INT32 & rows = 0,
                  const unsigned C_INT32 & cols = 0);
    CSparseMatrix(const CCompressedColumnFormat & ccf);
    ~CSparseMatrix();
    bool resize(const unsigned C_INT32 & rows, const unsigned C_INT32 & columns);
    const unsigned C_INT32 & numRows() const;
    const unsigned C_INT32 & numCols() const;
    unsigned C_INT32 numNonZeros() const;

    const std::vector< std::vector< CSparseMatrixElement *> > & getColumns() const;
    std::vector< std::vector< CSparseMatrixElement *> > & getColumns();
    const std::vector< std::vector< CSparseMatrixElement *> > & getRows() const;
    std::vector< std::vector< CSparseMatrixElement *> > & getRows();

    CSparseMatrix & operator = (const CCompressedColumnFormat & ccf);
    CSparseMatrix & operator = (const CMatrix< C_FLOAT64 > & matrix);
    operator const CMatrix< C_FLOAT64 > () const;

    bool setTreshold(const C_FLOAT64 & threshold);
    const C_FLOAT64 & getTreshold() const;

    CSparseMatrixElement & operator () (const unsigned C_INT32 & row,
                                        const unsigned C_INT32 & col);

    const CSparseMatrixElement & operator () (const unsigned C_INT32 & row,
        const unsigned C_INT32 & col) const;

    bool insert(const unsigned C_INT32 & row,
                const unsigned C_INT32 & col,
                const C_FLOAT64 & value);
    bool remove(const unsigned C_INT32 & row,
                const unsigned C_INT32 & col);

    friend std::ostream &operator <<(std::ostream &os,
                                     const CSparseMatrix & A);

  private:
    void cleanup();

    // Attributes
  private:
    C_FLOAT64 mThreshold;

    unsigned C_INT32 mNumRows;
    unsigned C_INT32 mNumCols;

    std::vector< unsigned C_INT32 > mRowIndex;
    std::vector< unsigned C_INT32> mColIndex;

    std::vector< std::vector< CSparseMatrixElement *> > mRows;
    std::vector< std::vector< CSparseMatrixElement *> > mCols;

    unsigned C_INT32 mSearchRow;
    unsigned C_INT32 mSearchCol;
    CSparseMatrixElement mElement;
  };

class CCompressedColumnFormat
  {
    // Attributes
  private:
    unsigned C_INT32 mNumRows;
    unsigned C_INT32 mNumCols;
    unsigned C_INT32 * mpColumnStart;
    unsigned C_INT32 * mpRowIndex;
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
                           const unsigned C_INT32 & rowIndex = C_INVALID_INDEX);

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

        const unsigned C_INT32 & getColumnIndex() const;

      private:
        // Attributes
        const CCompressedColumnFormat * mpMatrix;

        unsigned C_INT32 mRowIndex;

        const unsigned C_INT32 *mpRowIndex;

        unsigned C_INT32 mColumnIndex;

        const unsigned C_INT32 *mpColumnIndex;

        const C_FLOAT64 *mpCurrent;
      };

    CCompressedColumnFormat(const unsigned C_INT32 & rows,
                            const unsigned C_INT32 & columns,
                            const unsigned C_INT32 & nonZeros);
    CCompressedColumnFormat(const CSparseMatrix & matrix);
    ~CCompressedColumnFormat();

    unsigned C_INT32 numRows() const;
    unsigned C_INT32 numCols() const;
    unsigned C_INT32 numNonZeros() const;
    const C_FLOAT64 * getValues() const;
    C_FLOAT64 * getValues();
    const unsigned C_INT32 * getRowIndex() const;
    unsigned C_INT32 * getRowIndex();
    const unsigned C_INT32 * getColumnStart() const;
    unsigned C_INT32 * getColumnStart();
    CCompressedColumnFormat & operator = (const CSparseMatrix & ccf);

    const_row_iterator beginRow(const unsigned C_INT32 & row) const;
    const_row_iterator endRow(const unsigned C_INT32 & row) const;
  };

#ifdef COPASI_DEBUG
bool SparseMatrixTest(const unsigned C_INT32 & size,
                      const C_FLOAT64 & sparseness,
                      const unsigned C_INT32 & seed = 0,
                      const bool & RMP = true,
                      const bool & DGEMM = true,
                      const bool & SMP = true,
                      const bool & CCMP = true);
#endif

#endif // COPASI_CSparseMatrix
