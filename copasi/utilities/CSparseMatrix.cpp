/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CSparseMatrix.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/12 20:19:46 $
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
  const unsigned C_INT32 * pColumnStart = ccf.getColumnStart() + 1;

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
             itElement != endElement; ++itElement, i++, pTmp++)
          {
            for (; i < (*itElement)->col(); i++, pTmp++)
              *pTmp = 0.0;

            *pTmp = **itElement;
          }

        for (; i < mNumCols; i++, pTmp++)
          *pTmp = 0.0;
      }

    return M;
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

CCompressedColumnFormat::const_row_iterator::const_row_iterator(const CCompressedColumnFormat * pMatrix,
    const unsigned C_INT32 & rowIndex):
    mpMatrix(pMatrix),
    mRowIndex(rowIndex),
    mpRowIndex(NULL),
    mColumnIndex(0),
    mpColumnIndex(NULL),
    mpCurrent(NULL)
{
  if (mpMatrix &&
      mRowIndex != C_INVALID_INDEX &&
      mRowIndex < mpMatrix->numRows())
    {
      mpRowIndex = mpMatrix->getRowIndex() - 1;
      mpColumnIndex = mpMatrix->getColumnStart();

      ++(*this);
    }
}

CCompressedColumnFormat::const_row_iterator::const_row_iterator(const CCompressedColumnFormat::const_row_iterator & src):
    mpMatrix(src.mpMatrix),
    mRowIndex(src.mRowIndex),
    mpRowIndex(src.mpRowIndex),
    mColumnIndex(src.mColumnIndex),
    mpColumnIndex(src.mpColumnIndex),
    mpCurrent(src.mpCurrent)
{}

CCompressedColumnFormat::const_row_iterator::~const_row_iterator()
{}

const C_FLOAT64 & CCompressedColumnFormat::const_row_iterator::operator*() const
  {return *mpCurrent;}

const C_FLOAT64 & CCompressedColumnFormat::const_row_iterator::operator->() const
  {return *mpCurrent;}

bool CCompressedColumnFormat::const_row_iterator::operator!=(const CCompressedColumnFormat::const_row_iterator & rhs)
{return mpCurrent != rhs.mpCurrent;}

CCompressedColumnFormat::const_row_iterator & CCompressedColumnFormat::const_row_iterator::operator=(const CCompressedColumnFormat::const_row_iterator & rhs)
{
  mpMatrix = rhs.mpMatrix;
  mRowIndex = rhs.mRowIndex;
  mpRowIndex = rhs.mpRowIndex;
  mColumnIndex = rhs.mColumnIndex;
  mpColumnIndex = rhs.mpColumnIndex;
  mpCurrent = rhs.mpCurrent;

  return *this;
}

CCompressedColumnFormat::const_row_iterator & CCompressedColumnFormat::const_row_iterator::operator++()
{
  const unsigned C_INT32 * pRowIndexEnd = mpMatrix->getRowIndex() + mpMatrix->numNonZeros();

  mpRowIndex++; // We need to make at least one step forward.
  while (mpRowIndex != pRowIndexEnd && *mpRowIndex != mRowIndex) mpRowIndex++;

  if (mpRowIndex != pRowIndexEnd)
    {
      unsigned C_INT32 index = mpRowIndex - mpMatrix->getRowIndex();
      mpCurrent = mpMatrix->getValues() + index;
      while (*mpColumnIndex <= index) mpColumnIndex++;

      mColumnIndex = mpColumnIndex - mpMatrix->getColumnStart() - 1;
    }
  else
    mpCurrent = NULL;

  return *this;
}

const unsigned C_INT32 & CCompressedColumnFormat::const_row_iterator::getColumnIndex() const
{return mColumnIndex;}

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

  mpColumnStart = new unsigned C_INT32[mNumCols + 1];
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

  unsigned C_INT32 * pRowIndex = mpRowIndex;
  C_FLOAT64 * pValue = mpValue;
  for (i = 0, itCol = matrix.getColumns().begin(), endCol = matrix.getColumns().end();
       itCol != endCol; ++itCol, i++)
    {
      mpColumnStart[i] = k;

      for (itElement = itCol->begin(), endElement = itCol->end();
           itElement != endElement; ++itElement, k++, pRowIndex++, pValue++)
        {
          *pRowIndex = (*itElement)->row();
          *pValue = **itElement;
        }
    }

  return *this;
}

CCompressedColumnFormat::const_row_iterator CCompressedColumnFormat::beginRow(const unsigned C_INT32 & row) const
  {return const_row_iterator(this, row);}
CCompressedColumnFormat::const_row_iterator CCompressedColumnFormat::endRow(const unsigned C_INT32 & /* row */) const
  {return const_row_iterator(this);}

// ---------- SparseMatrixTest

#ifdef COPASI_DEBUG
#include "randomGenerator/CRandom.h"
#include "report/CCopasiTimer.h"

bool SparseMatrixTest(const unsigned C_INT32 & size,
                      const C_FLOAT64 & sparseness,
                      const unsigned C_INT32 & seed)
{
  unsigned C_INT32 i, j, l, loop = 1;
  CRandom * pRandom =
    CRandom::createGenerator(CRandom::mt19937, seed);

  // If the sparseness is not specified we expect 4 metabolites per reaction
  C_FLOAT64 Sparseness = sparseness;
  if (Sparseness == 0.0) Sparseness = 4.0 / size;

  CMatrix< C_FLOAT64 > M(size, size);
  CSparseMatrix S(size, size);
  CMatrix< C_FLOAT64 > MM(size, size);
  CSparseMatrix SS(size, size);
  C_FLOAT64 tmp;

  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      {
        if (pRandom->getRandomCC() < Sparseness)
          S(i, j) = (pRandom->getRandomCC() - 0.5) * 100.0;
        if (pRandom->getRandomCC() < Sparseness)
          SS(i, j) = (pRandom->getRandomCC() - 0.5) * 100.0;
      }

  M = S;
  MM = SS;

  CCompressedColumnFormat C(S);
  CCompressedColumnFormat CC(SS);

  DebugFile << "Memory requirements for sparseness:\t" << Sparseness << std::endl;

  tmp = sizeof(CMatrix< C_FLOAT64 >) + size * size * sizeof(C_FLOAT64);
  DebugFile << "Matrix(" << size << "x" << size << "):\t" << tmp << std::endl;

  C_FLOAT64 tmp2 = sizeof(CSparseMatrix)
                   + 2 * size * sizeof(std::vector<CSparseMatrixElement *>)
                   + 2 * size * sizeof(C_FLOAT64)
                   + S.numNonZeros() * sizeof(CSparseMatrixElement);
  DebugFile << "Sparse(" << size << "x" << size << "):\t" << tmp2 << std::endl;
  DebugFile << "Sparse/Matrix:\t" << tmp2 / tmp << std::endl;

  tmp2 = sizeof(CCompressedColumnFormat)
         + 2 * C.numNonZeros() * sizeof(C_FLOAT64)
         + (size + 1) * sizeof(C_FLOAT64);
  DebugFile << "CompressedColumnFormat(" << size << "x" << size << "):\t" << tmp2 << std::endl;
  DebugFile << "CompressedColumnFormat/Matrix:\t" << tmp2 / tmp << std::endl << std::endl;

  CCopasiTimer CPU(CCopasiTimer::CPU);

  // Regular Matrix Product
  CPU.start();
  for (l = 0; l < loop; l++)
    {
      CMatrix< C_FLOAT64 > MR(M.numRows(), MM.numCols());
      const C_FLOAT64 *pTmp1, *pTmp2, *pTmp4, *pTmp5;
      const C_FLOAT64 *pEnd1, *pEnd2, *pEnd4;
      C_FLOAT64 *pTmp3;

      pTmp1 = M.array();
      pEnd1 = pTmp1 + M.numRows() * M.numCols();

      pEnd2 = MM.array() + MM.numCols();
      pTmp3 = MR.array();

      for (; pTmp1 < pEnd1; pTmp1 += M.numRows())
        for (pTmp2 = MM.array(); pTmp2 < pEnd2; pTmp2++, pTmp3++)
          {
            *pTmp3 = 0.0;

            for (pTmp4 = pTmp1, pTmp5 = pTmp2, pEnd4 = pTmp4 + M.numRows();
                 pTmp4 < pEnd4; pTmp4++, pTmp5 += MM.numRows())
              * pTmp3 += *pTmp4 * *pTmp5;
          }
    }

  CPU.actualize();
  DebugFile << "Matrix * Matrix:\t";
  CPU.print(&DebugFile);
  DebugFile << std::endl;

  // Sparse Matrix Product

  CPU.start();
  for (l = 0; l < loop; l++)
    {
      CSparseMatrix SR(S.numRows(), SS.numCols());
      C_FLOAT64 Tmp;
      std::vector< std::vector< CSparseMatrixElement * > >::const_iterator itRow;
      std::vector< std::vector< CSparseMatrixElement * > >::const_iterator endRow;
      std::vector< CSparseMatrixElement * >::const_iterator itRowElement;
      std::vector< CSparseMatrixElement * >::const_iterator endRowElement;
      std::vector< std::vector< CSparseMatrixElement * > >::const_iterator itCol;
      std::vector< std::vector< CSparseMatrixElement * > >::const_iterator endCol;
      std::vector< CSparseMatrixElement * >::const_iterator itColElement;
      std::vector< CSparseMatrixElement * >::const_iterator endColElement;

      for (itRow = S.getRows().begin(), endRow = S.getRows().end(); itRow != endRow; ++itRow)
        {
          endRowElement = itRow->end();

          for (itCol = SS.getColumns().begin(), endCol = SS.getColumns().end(); itCol != endCol; ++itCol)
            {
              Tmp = 0;
              itRowElement = itRow->begin();
              itColElement = itCol->begin();
              endColElement = itCol->end();

              while (itRowElement != endRowElement &&
                     itColElement != endColElement)
                {
                  while (itRowElement != endRowElement &&
                         (*itRowElement)->col() < (*itColElement)->row()) ++itRowElement;
                  if (itRowElement == endRowElement) break;

                  while (itColElement != endColElement &&
                         (*itColElement)->row() < (*itRowElement)->col()) ++itColElement;
                  if (itColElement == endColElement) break;

                  if ((*itRowElement)->col() != (*itColElement)->row()) continue;

                  Tmp += **itRowElement * **itColElement;
                  ++itRowElement;
                  ++itColElement;
                }

              if (fabs(Tmp) < SR.getTreshold()) continue;

              SR.insert((*itRow->begin())->row(), (*itCol->begin())->col(), Tmp);
            }
        }
    }

  CPU.actualize();
  DebugFile << "Sparse * Sparse:\t";
  CPU.print(&DebugFile);
  DebugFile << std::endl;

  /*
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      assert(fabs(MR(i, j) - SR(i, j)) < SR.getTreshold());
  */

  // Compressed Column Format Product
  CPU.start();
  for (l = 0; l < loop; l++)
    {
      CCompressedColumnFormat CR(C.numRows(), CC.numCols(), 0);
      CSparseMatrix TmpR(C.numRows(), CC.numCols());
      C_FLOAT64 Tmp;
      unsigned C_INT32 imax = C.numRows();
      unsigned C_INT32 jmax = C.numCols();
      C_FLOAT64 * pColElement, * pEndColElement;
      unsigned C_INT32 * pColElementRow, * pEndColElementRow;
      unsigned C_INT32 * pColStart;
      CCompressedColumnFormat::const_row_iterator itRowElement;
      CCompressedColumnFormat::const_row_iterator endRowElement = C.endRow(0);

      for (j = 0, pColStart = CC.getColumnStart(); j < jmax; j++, pColStart++)
        {
          for (i = 0; i < imax; i++)
            {
              Tmp = 0;

              itRowElement = C.beginRow(i);
              pColElement = CC.getValues() + *pColStart;
              pEndColElement = CC.getValues() + *(pColStart + 1);
              pColElementRow = CC.getRowIndex() + *pColStart;
              pEndColElementRow = CC.getRowIndex() + *(pColStart + 1);

              while (itRowElement != endRowElement &&
                     pColElement != pEndColElement)
                {
                  while (itRowElement != endRowElement &&
                         itRowElement.getColumnIndex() < *pColElementRow) ++itRowElement;
                  if (!(itRowElement != endRowElement)) break;

                  while (pColElement != pEndColElement &&
                         *pColElementRow < itRowElement.getColumnIndex())
                    {
                      ++pColElement;
                      ++pColElementRow;
                    }
                  if (pColElement == pEndColElement) break;

                  if (itRowElement.getColumnIndex() != *pColElementRow) continue;

                  Tmp += *itRowElement * *pColElement;
                  ++itRowElement;
                  ++pColElement;
                  ++pColElementRow;
                }

              if (fabs(Tmp) < TmpR.getTreshold()) continue;

              TmpR.insert(i, j, Tmp);
            }
        }

      CR = TmpR;
    }

  CPU.actualize();
  DebugFile << "Compressed * Compressed:\t";
  CPU.print(&DebugFile);
  DebugFile << std::endl;

  /*
    for (i = 0; i < size; i++)
      for (j = 0; j < size; j++)
        assert(fabs(MR(i, j) - TmpR(i, j)) < SR.getTreshold());
  */ 
  // Mixed Matrix Product

  DebugFile << std::endl;
  DebugFile << std::endl;

  return true;
}
#endif
