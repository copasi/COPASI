// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.h,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/04/01 12:40:45 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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
        /*tmp->*/mSizes[0] =  mVector->size();
        return mSizes;
      }

    unsigned int dimensionality() const
      {return 1;}
  };

//**********************************************************************

class CArrayAnnotation: public CCopasiContainer
  {
  public:

    /**
     * The annotation to an array can work in different modes. The mode
     * for each dimension can be changes independently.
     *
     * OBJECTS: The CNs for the rows, cols, ... of the array are given explicitly
     *
     * VECTOR: A CCopasiVector is provided from which the CNs are generated at
     * the time the vector is set
     *
     * VECTOR_ON_THE_FLY: A CCopasiVector is provided, but the CNs are generated
     * every time the annotations are retrieved (so that they are alway up to date).
     *
     * STRINGS: The annotations for the rows, cols, ... are given explicitly
     * as strings.
     *
     * NUMBERS: The rows, cols, ... of the array are only annotation with
     * runnng numbers (starting with 0)-
     */
    enum Mode
    {
      OBJECTS,
      VECTOR,
      VECTOR_ON_THE_FLY,
      STRINGS,
      NUMBERS
    };

  private:
    CCopasiAbstractArray * mArray;

    mutable std::vector< std::vector<CRegisteredObjectName> > mAnnotationsCN;
    mutable std::vector< std::vector<std::string> > mAnnotationsString;

    std::vector< std::string > mDimensionDescriptions;
    std::vector< const CCopasiContainer * > mCopasiVectors;

    /**
     * This contains the mode for the different dimensions
     */
    std::vector<Mode> mModes;

    /**
     * This contains the default mode that is used if during a resize()
     * the dimensionality is increased.
     */
    Mode mDefaultMode;

    std::string mDescription;

  public:
    CArrayAnnotation(const std::string & name,
                     const CCopasiContainer * pParent,
                     CCopasiAbstractArray * array);

  private:
    CArrayAnnotation();
    CArrayAnnotation(const CArrayAnnotation &);
    CArrayAnnotation & operator=(const CArrayAnnotation &);

  public:

    /**
     *  let the ArrayAnnotation point to a different array.
     *  If you use this method without updating the annotations afterwards
     *  it is your responsibility to make sure the new array fits the
     *  existing annotation (in dimensionality and, if not in VECTOR_ON_THE_FLY mode,
     *  in size).
     */
    void setArray(CCopasiAbstractArray * a);

    CCopasiAbstractArray * array()
    {return mArray;}

    const CCopasiAbstractArray * array() const
      {return mArray;}

    /**
     * set the mode for the dimension d
     */
    void setMode(unsigned int d, Mode m);

    /**
     * set the mode for all dimensions, this also sets the
     * default mode that is used when resizing the ArrayAnnotion
     * to a larger dimensionality
     */
    void setMode(Mode m);

    Mode getMode(unsigned int d) const
      {return mModes[d];};

    Mode getDefaultMode() const
      {return mDefaultMode;};

    unsigned int dimensionality() const;

    CCopasiAbstractArray::index_type size() const
      {return mArray->size();}

    /**
     * Associates a dimension d of the array with a CCopasiVector of
     * CCopasiObjects. If the mode of the dimension d is VECTOR than
     * the CNs of the objects in the vector are generated and stored immediately.
     * If the mode is VECTOR_ON_THE_FLY the CNs are generated when getAnnotationsCN()
     * or getAnnotationsString() is called.
     */
    void setCopasiVector(unsigned int d, const CCopasiContainer* v);

    void setAnnotationCN(unsigned int d, unsigned int i, const std::string cn);
    void setAnnotationString(unsigned int d, unsigned int i, const std::string s);

    /**
     * returns the vector of CNs that correspond to the rows, columns, ... of the array.
     * This method must not be called if the mode for the dimension d is STRINGS or NUMBERS
     */
    const std::vector<CRegisteredObjectName> & getAnnotationsCN(unsigned int d) const;

    /**
     * This returns strings that annotate the rows, columns, ... of the array.
     * If the mode is OBJECTS, VECTOR, or VECTOR_ON_THE_FLY the display argument determines
     * if the object name or the object display name is used.
     * Note that this method returns a reference. The content that the reference points to
     * may be changes by later calls to the getAnnotationsCN() method with the same value for d.
     * Specifically if you use this method to obtain a reference to the list of display names
     * and then call the method again to get the plain object names, the first reference will
     * after that also point to the plain object names.
     */
    const std::vector<std::string> & getAnnotationsString(unsigned int d, bool display = true) const;

    const std::string & getDimensionDescription(unsigned int d) const;
    void setDimensionDescription(unsigned int d, const std::string & s);

    const std::string & getDescription() const;
    void setDescription(const std::string & s);

    /**
     * adjust the dimensionality and size to that of the array
     */
    void resize();

  private:
    /**
     *  resize the internal vectors according to the dimensionality of the array
     */
    void reDimensionalize(unsigned int d);

    void resizeOneDimension(unsigned int d);

    //void printDebugLoop(std::ostream & out, CCopasiAbstractArray::index_type & index, unsigned int level) const;

    /**
     *  generate the list of CNs from the copasi vector v.
     *  v needs to be a CCopasiVector (or derived from it)!
     */
    bool createAnnotationsCNFromCopasiVector(unsigned int d, const CCopasiContainer* v) const;

    void createNumbers(unsigned int d) const;

    //void printDebug(std::ostream & out) const;

    void printRecursively(std::ostream & ostream, C_INT32 level,
                          CCopasiAbstractArray::index_type & index,
                          const std::vector<std::vector<std::string> > & display) const;

  public:
    virtual void print(std::ostream * ostream) const;

    friend std::ostream &operator<<(std::ostream &os, const CArrayAnnotation & o);
  };

//**********************************************************************

#endif
