/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/05 15:57:04 $
   End CVS Header */

#ifndef CANNOTATEDMATRIX_H
#define CANNOTATEDMATRIX_H

#include <utilities/CMatrix.h>
#include "report/CCopasiContainer.h"

//preliminary
#include <string>

#include "copasi.h"

/**
 * this class contains an n-dimensional array
 */
class CCopasiArray
  {
  public:
    typedef std::vector<unsigned int> index_type;
    typedef C_FLOAT64 data_type;

    CCopasiArray();
    CCopasiArray(const index_type & sizes);

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

#define C_KEYTYPE std::string
#include "CCopasiVector.h"

/**
 */

class CAnnotatedMatrix : public CMatrix<C_FLOAT64>, public CCopasiContainer
  {
  private:
    C_KEYTYPE mKey;

    C_KEYTYPE mRowsReference;
    C_KEYTYPE mColumnsReference;

    std::vector<C_KEYTYPE> mRowsReferences;
    std::vector<C_KEYTYPE> mColumnsReferences;

  public:
    CAnnotatedMatrix(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NULL);

    CAnnotatedMatrix(const CAnnotatedMatrix & src,
                     const CCopasiContainer * pParent = NULL);

    ~CAnnotatedMatrix();

    const C_KEYTYPE & getRowsReference() const
      {return mRowsReference;}

    const C_KEYTYPE & getColumnsReference() const
      {return mRowsReference;}

    const std::vector<C_KEYTYPE> & getRowsReferences() const
      {return mRowsReferences;}

    const std::vector<C_KEYTYPE> & getColumnsReferences() const
      {return mColumnsReferences;}

    template <class CType1, class CType2>
          void setup(const CCopasiVector<CType1> & rows, const CCopasiVector<CType2> & columns)
      {
        resize(rows.size(), columns.size());
        //all the references
      }
  };

#endif
