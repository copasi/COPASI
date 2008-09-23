// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiArray.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/23 06:22:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASIARRAY_H
#define COPASIARRAY_H

#include <utilities/CMatrix.h>
#include <vector>
#include "copasi.h"

/**
 * This abstract class defines the interface for an n-dimensional array of floats
 */
class CCopasiAbstractArray
  {
  public:
    typedef std::vector<unsigned int> index_type;
    typedef C_FLOAT64 data_type;

    //CCopasiAbstractArray();
    //CCopasiAbstractArray(const index_type & sizes);
    virtual ~CCopasiAbstractArray() {};

    //virtual void resize(const index_type & sizes) = 0;

    virtual data_type & operator[] (const index_type & index) = 0;
    virtual const data_type & operator[] (const index_type & index) const = 0;

    virtual const index_type & size() const = 0;

    virtual unsigned int dimensionality() const = 0;
  };

/**
 * this class contains an n-dimensional array
 */
class CCopasiArray: public CCopasiAbstractArray
  {
  public:
    //typedef std::vector<unsigned int> index_type;
    //typedef C_FLOAT64 data_type;

    CCopasiArray();
    CCopasiArray(const index_type & sizes);
    ~CCopasiArray() {};

    void resize(const index_type & sizes);

    data_type & operator[] (const index_type & index);
    const data_type & operator[] (const index_type & index) const;

  private:
    std::vector<data_type> mData;
    std::vector<unsigned int> mSizes;
    unsigned int mDim;
    std::vector<unsigned int> mFactors;

  public:
    const index_type & size() const
      {return mSizes;}

    unsigned int dimensionality() const
      {return mDim;}
  };

/**
 * this class provides an interface to a CMatrix<C_FLOAT64> or a CLinkMatrixView,
 * that is to every 2-dimensional class that has numRows(), numCols(), and operator()(row, col)
 */

template<class MatrixType>
class CCopasiMatrixInterface: public CCopasiAbstractArray
  {
  public:

    CCopasiMatrixInterface(MatrixType * matrix)
        : mMatrix(matrix)
    {
      assert(mMatrix);
      mSizes.resize(2);
      mSizes[0] = mMatrix->numRows();
      mSizes[1] = mMatrix->numCols();
    }
    ~CCopasiMatrixInterface() {};

    //void resize(const index_type & sizes);

    data_type & operator[] (const index_type & index)
    {
#ifdef COPASI_DEBUG
      assert(index.size() == 2);
#endif
      return (*mMatrix)(index[0], index[1]);
    }

    const data_type & operator[] (const index_type & index) const
      {
#ifdef COPASI_DEBUG
        assert(index.size() == 2);
#endif
        return (*mMatrix)(index[0], index[1]);
      }

  private:
    MatrixType * mMatrix;
    //std::vector<data_type> mData;
    std::vector<unsigned int> mSizes;
    //unsigned int mDim;
    //std::vector<unsigned int> mFactors;

  public:
    const index_type & size() const
      {
        CCopasiMatrixInterface * tmp = const_cast<CCopasiMatrixInterface*>(this);
        tmp->mSizes[0] = mMatrix->numRows();
        tmp->mSizes[1] = mMatrix->numCols();
        return mSizes;
      }

    unsigned int dimensionality() const
      {return 2;}
  };

/**
 * this class provides an interface to a CVector<C_FLOAT64>,
 * or indeed to any container class that has a size() method and
 * a [] operator that returns C_FLOAT64.
 */

template<class VectorType>
class CCopasiVectorInterface: public CCopasiAbstractArray
  {
  public:

    CCopasiVectorInterface(VectorType * vector)
        : mVector(vector)
    {
      assert(mVector);
      mSizes.resize(1);
      mSizes[0] = mVector->size();
    }
    ~CCopasiVectorInterface() {};

    data_type & operator[] (const index_type & index)
    {
#ifdef COPASI_DEBUG
      assert(index.size() == 1);
#endif
      return (*mVector)[index[0]];
    }

    const data_type & operator[] (const index_type & index) const
      {
#ifdef COPASI_DEBUG
        assert(index.size() == 1);
#endif
        return (*mVector)[index[0]];
      }

  private:
    VectorType * mVector;
    mutable std::vector<unsigned int> mSizes;

  public:
    const index_type & size() const
      {
        //CCopasiMatrixInterface * tmp = const_cast<CCopasiMatrixInterface*>(this);
        /*tmp->*/mSizes[0] =        mVector->size();
        return mSizes;
      }

    unsigned int dimensionality() const
      {return 1;}
  };

#endif
