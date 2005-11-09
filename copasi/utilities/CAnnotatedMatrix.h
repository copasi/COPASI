/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/11/09 12:09:50 $
   End CVS Header */

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

    virtual void resize(const index_type & sizes) = 0;

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
 * this class provides an interface to a CMatrix<C_FLOAT64>
 */
class CCopasiMatrixInterface: public CCopasiAbstractArray
  {
  public:

    CCopasiMatrixInterface(CMatrix<C_FLOAT64> * matrix);
    ~CCopasiMatrixInterface() {};

    void resize(const index_type & sizes);

    data_type & operator[] (const index_type & index);
    const data_type & operator[] (const index_type & index) const;

  private:
    CMatrix<C_FLOAT64> * mMatrix;
    //std::vector<data_type> mData;
    std::vector<unsigned int> mSizes;
    //unsigned int mDim;
    //std::vector<unsigned int> mFactors;

  public:
    const index_type & size() const
      {return mSizes;}

    unsigned int dimensionality() const
      {return 2;}
  };

//**********************************************************************

class CArrayAnnotation: public CCopasiContainer
  {
  private:
    CCopasiAbstractArray * mArray;

    std::vector< std::vector<CRegisteredObjectName> > mAnnotations;

    std::vector< std::string > mDimensionDescriptions;

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
    unsigned int dimensionality() const
      {return mAnnotations.size();}

    const std::vector<CRegisteredObjectName> & getAnnotations(unsigned int d) const
      {return mAnnotations[d];}

    const std::string & getDimensionDescription(unsigned int d) const
      {return mDimensionDescriptions[d];}

    const std::string & getDescription() const
      {return mDescription;}

    void resize(const CCopasiAbstractArray::index_type & sizes);

  private:
    void resizeAnnotations();

  public:
    void printDebug(std::ostream & out) const;

    virtual void print(std::ostream * ostream) const
      {printDebug(*ostream);}
  };

//**********************************************************************

#define C_KEYTYPE std::string
#include "CCopasiVector.h"

/**
 */

class CAnnotatedMatrixOld : public CMatrix<C_FLOAT64>, public CCopasiContainer
  {
  private:
    C_KEYTYPE mKey;

    C_KEYTYPE mRowsReference;
    C_KEYTYPE mColumnsReference;

    std::vector<C_KEYTYPE> mRowsReferences;
    std::vector<C_KEYTYPE> mColumnsReferences;

  public:
    CAnnotatedMatrixOld(const std::string & name = "NoName",
                        const CCopasiContainer * pParent = NULL);

    CAnnotatedMatrixOld(const CAnnotatedMatrixOld & src,
                        const CCopasiContainer * pParent = NULL);

    ~CAnnotatedMatrixOld();

    /*const C_KEYTYPE & getRowsReference() const
      {return mRowsReference;}

    const C_KEYTYPE & getColumnsReference() const
      {return mRowsReference;}

    const std::vector<C_KEYTYPE> & getRowsReferences() const
      {return mRowsReferences;}

    const std::vector<C_KEYTYPE> & getColumnsReferences() const
      {return mColumnsReferences;}
    */

    template <class CType1, class CType2>
          void setup(const CCopasiVector<CType1> & rows, const CCopasiVector<CType2> & columns)
      {
        resize(rows.size(), columns.size());
        //all the references
      }
  };

#endif
