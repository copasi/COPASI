/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSparseMatrix.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/07 21:20:13 $
   End CVS Header */

///////////////////////////////////////////////////////////
//  CSparseMatrix.cpp
//  Implementation of the Class CSparseMatrix
//  Created on:      29-Jun-2004 16:52:05
///////////////////////////////////////////////////////////

#include <algorithm>
 #include <float.h>
 #include <math.h>

#include "copasi.h"

#include "CSparseMatrix.h"
 #include "CMatrix.h"

// ---------- CSparseMatrixElement

bool CSparseMatrixElement::compareRow(const CSparseMatrixElement * pLhs,
                                      const CSparseMatrixElement * pRhs)
{return pLhs->mRow < pRhs->mRow;}

bool CSparseMatrixElement::compareCol(const CSparseMatrixElement * pLhs,
                                      const CSparseMatrixElement * pRhs)
{return pLhs->mCol < pRhs->mCol;}

CSparseMatrixElement::CSparseMatrixElement(CSparseMatrix & matrix,
    const unsigned C_INT32 & row,
    const unsigned C_INT32 & col,
    const C_FLOAT64 & value):
    mMatrix(matrix),
    mRow(row),
    mCol(col),
    mValue(value)
{}

CSparseMatrixElement::~CSparseMatrixElement()
{}

const C_FLOAT64 & CSparseMatrixElement::operator = (const C_FLOAT64 & value)
{
  if (fabs(value) < mMatrix.getTreshold() &&
      fabs(mValue) >= mMatrix.getTreshold())
    mMatrix.remove(mRow, mCol);
  else if (fabs(value) >= mMatrix.getTreshold() &&
           fabs(mValue) < mMatrix.getTreshold())
    mMatrix.insert(mRow, mCol, value);
  else
    mValue = value;

  return value;
}

CSparseMatrixElement::operator const C_FLOAT64 & () const
{return mValue;}

const unsigned C_INT32 & CSparseMatrixElement::row() const {return mRow;}
const unsigned C_INT32 & CSparseMatrixElement::col() const {return mCol;}

// ---------- CSparseMatrix

CSparseMatrix::CSparseMatrix(const unsigned C_INT32 & rows,
                             const unsigned C_INT32 & cols):
    mThreshold(DBL_EPSILON),
    mNumRows(0),
    mNumCols(0),
    mRowIndex(),
    mColIndex(),
    mRows(),
    mCols(),
    mSearchRow(0),
    mSearchCol(0),
    mElement(*this, this->mSearchRow, this->mSearchCol, 0.0)
{resize(rows, cols);}

CSparseMatrix::CSparseMatrix(const CCompressedColumnFormat & ccf):
    mThreshold(DBL_EPSILON),
    mNumRows(0),
    mNumCols(0),
    mRowIndex(),
    mColIndex(),
    mRows(),
    mCols(),
    mSearchRow(0),
    mSearchCol(0),
    mElement(*this, this->mSearchRow, this->mSearchCol, 0.0)
{*this = ccf;}

CSparseMatrix::~CSparseMatrix()
{cleanup();}

void CSparseMatrix::cleanup()
{
  std::vector< std::vector< CSparseMatrixElement * > >::iterator itRow;
  std::vector< std::vector< CSparseMatrixElement * > >::iterator endRow;

  std::vector< CSparseMatrixElement * >::iterator itElement;
  std::vector< CSparseMatrixElement * >::iterator endElement;

  for (itRow = mRows.begin(), endRow = mRows.end(); itRow != endRow; ++itRow)
    for (itElement = itRow->begin(), endElement = itRow->end(); itElement != endElement; ++itElement)
      delete *itElement;
}

bool CSparseMatrix::resize(const unsigned C_INT32 & rows, const unsigned C_INT32 & cols)
{
  unsigned C_INT32 i;
  mNumRows = rows;
  mNumCols = cols;

  mRowIndex.resize(mNumRows);
  for (i = 0; i < mNumRows; i++)
    mRowIndex[i] = i;

  mColIndex.resize(mNumCols);
  for (i = 0; i < mNumCols; i++)
    mColIndex[i] = i;

  mRows.resize(mNumRows);
  mCols.resize(mNumCols);

  return true;
}

const unsigned C_INT32 CSparseMatrix::numRows() const
{return mNumRows;}

const unsigned C_INT32 CSparseMatrix::numCols() const
  {return mNumCols;}

const unsigned C_INT32 CSparseMatrix::numNonZeros() const
  {
    unsigned C_INT32 NonZeros = 0;

    std::vector< std::vector< CSparseMatrixElement * > >::const_iterator itRow;
    std::vector< std::vector< CSparseMatrixElement * > >::const_iterator endRow;

    for (itRow = mRows.begin(), endRow = mRows.end(); itRow != endRow; ++itRow)
      NonZeros += itRow->size();

    return NonZeros;
  }

const std::vector< std::vector< CSparseMatrixElement * > > & CSparseMatrix::getColumns() const
{return mCols;}

std::vector< std::vector< CSparseMatrixElement * > > & CSparseMatrix::getColumns()
{return mCols;}

const std::vector< std::vector< CSparseMatrixElement * > > & CSparseMatrix::getRows() const
  {return mRows;}

std::vector< std::vector< CSparseMatrixElement * > > & CSparseMatrix::getRows()
{return mRows;}

CSparseMatrix & CSparseMatrix::operator = (const CCompressedColumnFormat & ccf)
{
  resize(ccf.numRows(), ccf.numCols());

  const C_FLOAT64 * pValue = ccf.getValues();
  const unsigned C_INT32 * pRowIndex = ccf.getRowIndex();
  const unsigned C_INT32 * pColumnStart = ccf.getColumnStart();

  unsigned C_INT32 i, j, k;
  CSparseMatrixElement * pElement;

  for (j = 0, i = 0; j < mNumCols; j++, pColumnStart++)
    {
      mCols[j].resize(*pColumnStart - *(pColumnStart - 1));

      for (k = 0; i < *pColumnStart; i++, k++, pRowIndex++, pValue++)
        {
          pElement = new CSparseMatrixElement(*this, mRowIndex[*pRowIndex], mColIndex[j], *pValue);
          mCols[j][k] = pElement;
          mRows[*pRowIndex].push_back(pElement); // Note, these are out of order and must be sorted.
        }
    }

  for (i = 0; i < mNumRows; i++)
    std::sort(mRows[i].begin(), mRows[i].end(), &CSparseMatrixElement::compareCol);

  return *this;
}

CSparseMatrix & CSparseMatrix::operator = (const CMatrix< C_FLOAT64 > & matrix)
{
  unsigned C_INT32 i, j;
  CSparseMatrixElement * pElement;

  resize(matrix.numRows(), matrix.numCols());
  const C_FLOAT64 * pTmp = matrix.array();

  for (i = 0; i < mNumRows; i++)
    for (j = 0; j < mNumCols; j++, pTmp++)
      if (fabs(*pTmp) >= mThreshold)
        {
          pElement = new CSparseMatrixElement(*this, mRowIndex[i], mColIndex[j], *pTmp);
          mRows[i].push_back(pElement);
          mCols[j].push_back(pElement); // Note, these are out of order and must be sorted.
        }

  for (j = 0; j < mNumCols; j++)
    std::sort(mCols[j].begin(), mCols[j].end(), &CSparseMatrixElement::compareRow);

  return *this;
}

CSparseMatrix::operator const CMatrix< C_FLOAT64 > () const
  {
    CMatrix< C_FLOAT64 > M;
    M.resize(mNumRows, mNumCols);

    C_FLOAT64 * pTmp = M.array();
    unsigned C_INT32 i;

    std::vector< std::vector< CSparseMatrixElement * > >::const_iterator itRow;
    std::vector< std::vector< CSparseMatrixElement * > >::const_iterator endRow;

    std::vector< CSparseMatrixElement * >::const_iterator itElement;
    std::vector< CSparseMatrixElement * >::const_iterator endElement;

    for (itRow = mRows.begin(), endRow = mRows.end(); itRow != endRow; ++itRow)
      {
        for (i = 0, itElement = itRow->begin(), endElement = itRow->end();
             itElement != endElement; ++itElement, i++)
          {
            for (; i < (*itElement)->col(); i++)
              *pTmp = 0.0;

            *pTmp = **itElement;
          }

        for (; i < mNumCols; i++)
          *pTmp = 0.0;
      }

    return *this;
  }

bool CSparseMatrix::setTreshold(const C_FLOAT64 & threshold)
{
  if (threshold < mThreshold)
    {
      std::vector< std::vector< CSparseMatrixElement * > >::iterator itRow;
      std::vector< std::vector< CSparseMatrixElement * > >::iterator endRow;

      std::vector< CSparseMatrixElement * >::reverse_iterator itElement;
      std::vector< CSparseMatrixElement * >::reverse_iterator endElement;

      for (itRow = mRows.begin(), endRow = mRows.end(); itRow != endRow; ++itRow)
        for (itElement = itRow->rbegin(), endElement = itRow->rend(); itElement != endElement; ++itElement)
          if (fabs(**itElement) < threshold)
            remove((*itElement)->row(), (*itElement)->col());
    }

  mThreshold = threshold;

  return true;
}

const C_FLOAT64 & CSparseMatrix::getTreshold() const
{return mThreshold;}

CSparseMatrixElement & CSparseMatrix::operator () (const unsigned C_INT32 & row,
    const unsigned C_INT32 & col)
{
  mSearchRow = row;
  mSearchCol = col;

  std::vector< CSparseMatrixElement * >::iterator found
  = std::lower_bound(mCols[col].begin(), mCols[col].end(), &mElement, CSparseMatrixElement::compareRow);

  if (found != mCols[col].end() &&
      (*found)->row() == row) return **found;

  return mElement;
}

const CSparseMatrixElement & CSparseMatrix::operator () (const unsigned C_INT32 & row,
    const unsigned C_INT32 & col) const
  {
    const_cast<CSparseMatrix *>(this)->mSearchRow = row;
    const_cast<CSparseMatrix *>(this)->mSearchCol = col;

    std::vector< CSparseMatrixElement * >::const_iterator found
    = std::lower_bound(mCols[col].begin(), mCols[col].end(), &mElement, CSparseMatrixElement::compareRow);

    if (found != mCols[col].end() &&
        (*found)->row() == row) return **found;

    return mElement;
  }

bool CSparseMatrix::insert(const unsigned C_INT32 & row,
                           const unsigned C_INT32 & col,
                           const C_FLOAT64 & value)
{
  mSearchRow = row;
  mSearchCol = col;

  std::vector< CSparseMatrixElement * >::iterator found
  = std::lower_bound(mCols[col].begin(), mCols[col].end(), &mElement, CSparseMatrixElement::compareRow);

  if (found != mCols[col].end() &&
      (*found)->row() == row) return false; // The element already exists.

  CSparseMatrixElement * pElement = new CSparseMatrixElement(*this, mRowIndex[row], mColIndex[col], value);
  mCols[col].insert(found, pElement);

  found = std::lower_bound(mRows[row].begin(), mRows[row].end(), &mElement, CSparseMatrixElement::compareCol);
  mRows[row].insert(found, pElement);

  return true;
}

bool CSparseMatrix::remove(const unsigned C_INT32 & row,
                           const unsigned C_INT32 & col)
{
  mSearchRow = row;
  mSearchCol = col;

  std::vector< CSparseMatrixElement * >::iterator found
  = std::lower_bound(mCols[col].begin(), mCols[col].end(), &mElement, CSparseMatrixElement::compareRow);

  if (found == mCols[col].end()) return false; // The element does not exist.

  mCols[col].erase(found);

  found = std::lower_bound(mRows[row].begin(), mRows[row].end(), &mElement, CSparseMatrixElement::compareCol);
  mRows[row].erase(found);

  delete *found;

  return true;
}

std::ostream &operator<<(std::ostream &os, const CSparseMatrix & A)
{
  os << "Matrix(" << A.mNumRows << "x" << A.mNumCols << ")" << std::endl;

  unsigned C_INT32 i;

  std::vector< std::vector< CSparseMatrixElement * > >::const_iterator itRow;
  std::vector< std::vector< CSparseMatrixElement * > >::const_iterator endRow;

  std::vector< CSparseMatrixElement * >::const_iterator itElement;
  std::vector< CSparseMatrixElement * >::const_iterator endElement;

  for (itRow = A.mRows.begin(), endRow = A.mRows.end(); itRow != endRow; ++itRow)
    {
      for (i = 0, itElement = itRow->begin(), endElement = itRow->end();
           itElement != endElement; ++itElement, i++)
        {
          for (; i < (*itElement)->col(); i++)
            os << "\t" << 0.0;

          os << "\t" << **itElement;
        }

      for (; i < A.mNumCols; i++)
        os << "\t" << 0.0;

      os << std::endl;
    }

  return os;
}

// ---------- CCompressedColumnFormat

CCompressedColumnFormat::CCompressedColumnFormat():
    mNumRows(0),
    mNumCols(0),
    mpColumnStart(new unsigned C_INT32[1]),
    mpRowIndex(NULL),
    mpValue(NULL)
{mpColumnStart[mNumCols] = 0;}

CCompressedColumnFormat::CCompressedColumnFormat(const unsigned C_INT32 & rows,
    const unsigned C_INT32 & columns,
    const unsigned C_INT32 & nonZeros):
    mNumRows(rows),
    mNumCols(columns),
    mpColumnStart(new unsigned C_INT32[columns + 1]),
    mpRowIndex(nonZeros ? new unsigned C_INT32[nonZeros] : NULL),
    mpValue(nonZeros ? new C_FLOAT64[nonZeros] : NULL)
{mpColumnStart[mNumCols] = nonZeros;}

CCompressedColumnFormat::CCompressedColumnFormat(const CSparseMatrix & matrix):
mNumRows(0),
mNumCols(0),
mpColumnStart(NULL),
mpRowIndex(NULL),
mpValue(NULL)
{*this = matrix;}

CCompressedColumnFormat::~CCompressedColumnFormat()
{
  pdelete(mpValue);
  pdelete(mpRowIndex);
  pdelete(mpColumnStart);
}

unsigned C_INT32 CCompressedColumnFormat::numRows() const
  {return mNumRows;}

unsigned C_INT32 CCompressedColumnFormat::numCols() const
  {return mNumCols;}

unsigned C_INT32 CCompressedColumnFormat::numNonZeros() const
  {return mpColumnStart[mNumCols];}

const C_FLOAT64 * CCompressedColumnFormat::getValues() const
  {return mpValue;}

C_FLOAT64 * CCompressedColumnFormat::getValues()
{return mpValue;}

const unsigned C_INT32 * CCompressedColumnFormat::getRowIndex() const
  {return mpRowIndex;}

unsigned C_INT32 * CCompressedColumnFormat::getRowIndex()
{return mpRowIndex;}

const unsigned C_INT32 * CCompressedColumnFormat::getColumnStart() const
  {return mpColumnStart;}

unsigned C_INT32 * CCompressedColumnFormat::getColumnStart()
{return mpColumnStart;}

CCompressedColumnFormat & CCompressedColumnFormat::operator = (const CSparseMatrix & matrix)
{
  pdelete(mpValue);
  pdelete(mpRowIndex);
  pdelete(mpColumnStart);

  mNumRows = matrix.numRows();
  mNumCols = matrix.numCols();

  mpColumnStart = new unsigned C_INT32[mNumCols + 1],
                  mpColumnStart[mNumCols] = matrix.numNonZeros();

  if (mpColumnStart[mNumCols])
    {
      mpRowIndex = new unsigned C_INT32[mpColumnStart[mNumCols]];
      mpValue = new C_FLOAT64[mpColumnStart[mNumCols]];
    }
  else
    {
      mpRowIndex = NULL;
      mpValue = NULL;
    }

  unsigned C_INT32 k = 0;
  unsigned C_INT32 i;

  std::vector< std::vector< CSparseMatrixElement * > >::const_iterator itCol;
  std::vector< std::vector< CSparseMatrixElement * > >::const_iterator endCol;

  std::vector< CSparseMatrixElement * >::const_iterator itElement;
  std::vector< CSparseMatrixElement * >::const_iterator endElement;

  for (i = 0, itCol = matrix.getColumns().begin(), endCol = matrix.getColumns().end();
       itCol != endCol; ++itCol, i++)
    {
      mpColumnStart[i] = k;

      for (itElement = itCol->begin(), endElement = itCol->end();
           itElement != endElement; ++itElement, k++)
        {
          mpRowIndex[k] = (*itElement)->row();
          mpValue[k] = **itElement;
        }
    }

  return *this;
}
