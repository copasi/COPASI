/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.h,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/09/18 12:53:54 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CANNOTATEDMATRIX_H
#define CANNOTATEDMATRIX_H

#include <utilities/CMatrix.h>
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"

//preliminary
#include <string>

#include "copasi.h"

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

//**********************************************************************

class CArrayAnnotation: public CCopasiContainer
  {
  private:
    CCopasiAbstractArray * mArray;

    mutable std::vector< std::vector<CRegisteredObjectName> > mAnnotations;

    mutable std::vector< std::string > mDimensionDescriptions;
    mutable std::vector< const CCopasiContainer * > mCopasiVectors;

    std::string mDescription;

    bool mOnTheFly;

  public:
    CArrayAnnotation(const std::string & name,
                     const CCopasiContainer * pParent,
                     CCopasiAbstractArray * array);

  private:
    CArrayAnnotation();
    CArrayAnnotation(const CArrayAnnotation &);
    CArrayAnnotation & operator=(const CArrayAnnotation &);

  public:

    CCopasiAbstractArray * array()
    {return mArray;}

    const CCopasiAbstractArray * array() const
      {return mArray;}

    bool onTheFly() const
      {return mOnTheFly;}

    void setOnTheFly(bool flag)
    {mOnTheFly = flag;}

    unsigned int dimensionality() const;

    CCopasiAbstractArray::index_type size() const
      {return mArray->size();}

    const std::vector<CRegisteredObjectName> & getAnnotations(unsigned int d) const;
    void setAnnotation(unsigned int d, unsigned int i, const std::string cn);

    std::vector<std::string> getAnnotationsDisplay(unsigned int d) const;
    std::vector<std::string> getAnnotationsNames(unsigned int d) const;

    const std::string & getDimensionDescription(unsigned int d) const;
    void setDimensionDescription(unsigned int d, const std::string & s);

    void setCopasiVector(unsigned int d, const CCopasiContainer* v);

    const std::string & getDescription() const;
    void setDescription(const std::string & s);

    void resize(/*const CCopasiAbstractArray::index_type & sizes*/);

  private:
    void resizeAnnotations() const;

    /**
     * this generates the annotations if onTheFly() == true.
     */
    bool updateAnnotations() const;

    void printDebugLoop(std::ostream & out, CCopasiAbstractArray::index_type & index, unsigned int level) const;

    bool createAnnotationsFromCopasiVector(unsigned int d, const CCopasiContainer* v) const;

    void printDebug(std::ostream & out) const;

    void printRecursively(std::ostream & ostream, C_INT32 level,
                          CCopasiAbstractArray::index_type & index) const;

  public:
    virtual void print(std::ostream * ostream) const;

    friend std::ostream &operator<<(std::ostream &os, const CArrayAnnotation & o);
  };

//**********************************************************************

#endif
