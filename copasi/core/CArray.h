// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASIARRAY_H
#define COPASIARRAY_H

#include <vector>
#include <map>

#include "copasi/copasi.h"

#include "copasi/core/CMatrix.h"

/**
 * This abstract class defines the interface for an n-dimensional array of floats
 */
class CArrayInterface
{
public:
  typedef std::vector< size_t > index_type;

  typedef C_FLOAT64 data_type;

  virtual ~CArrayInterface() {};

  virtual data_type & operator[](const index_type & index) = 0;

  virtual const data_type & operator[](const index_type & index) const = 0;

  virtual const index_type & size() const = 0;

  virtual size_t dimensionality() const = 0;
};

/**
 * this class contains an n-dimensional array
 */
class CArray: public CArrayInterface
{
public:

  CArray();

  CArray(const index_type & sizes);

  virtual ~CArray() {};

  void resize(const index_type & sizes);

  virtual data_type & operator[](const index_type & index);

  virtual const data_type & operator[](const index_type & index) const;

  virtual const index_type & size() const;

  size_t dimensionality() const;

private:
  std::vector<data_type> mData;

  index_type mSizes;

  size_t mDim;

  index_type mFactors;
};

/**
 * this class provides an interface to a CMatrix<C_FLOAT64> or a CLinkMatrixView,
 * that is to every 2-dimensional class that has numRows(), numCols(), and operator()(row, col)
 */

template<class MatrixType>
class CMatrixInterface: public CArrayInterface
{
public:

  CMatrixInterface(MatrixType * matrix)
    : mMatrix(matrix)
  {
    assert(mMatrix);
    mSizes.resize(2);
    mSizes[0] = mMatrix->numRows();
    mSizes[1] = mMatrix->numCols();
  }

  virtual ~CMatrixInterface() {};

  data_type & operator[](const index_type & index)
  {
    assert(index.size() == 2);

    return (*mMatrix)(index[0], index[1]);
  }

  const data_type & operator[](const index_type & index) const
  {
    assert(index.size() == 2);

    return (*mMatrix)(index[0], index[1]);
  }

private:
  MatrixType * mMatrix;

  mutable std::vector<size_t> mSizes;

public:
  virtual const index_type & size() const
  {
    mSizes[0] = mMatrix->numRows();
    mSizes[1] = mMatrix->numCols();

    return mSizes;
  }

  size_t dimensionality() const
  {
    return 2;
  }
};

/**
 * this class provides an interface to a CVector<C_FLOAT64>,
 * or indeed to any container class that has a size() method and
 * a [] operator that returns C_FLOAT64.
 */

template<class VectorType>
class CVectorInterface: public CArrayInterface
{
public:

  CVectorInterface(VectorType * vector)
    : mVector(vector)
  {
    assert(mVector);
    mSizes.resize(1);
    mSizes[0] = mVector->size();
  }

  virtual ~CVectorInterface() {};

  data_type & operator[](const index_type & index)
  {
    assert(index.size() == 1);

    return (*mVector)[index[0]];
  }

  const data_type & operator[](const index_type & index) const
  {
    assert(index.size() == 1);

    return (*mVector)[index[0]];
  }

private:
  VectorType * mVector;

  mutable std::vector< size_t > mSizes;

public:
  virtual const index_type & size() const
  {
    mSizes[0] = mVector->size();

    return mSizes;
  }

  size_t dimensionality() const
  {
    return 1;
  }
};

#endif
