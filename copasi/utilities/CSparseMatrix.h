/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSparseMatrix.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/07 21:20:13 $
   End CVS Header */

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
    const unsigned C_INT32 numRows() const;
    const unsigned C_INT32 numCols() const;
    const unsigned C_INT32 numNonZeros() const;

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

  public:
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
  };

#endif // COPASI_CSparseMatrix
