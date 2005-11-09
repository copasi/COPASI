/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/11/09 12:09:50 $
   End CVS Header */

#include "CAnnotatedMatrix.h"
#include "report/CKeyFactory.h"

CCopasiArray::CCopasiArray()
    : mDim(0) {}

CCopasiArray::CCopasiArray(const index_type & sizes)
{
  resize(sizes);
}

void CCopasiArray::resize(const index_type & sizes)
{
  mDim = sizes.size();
  mSizes = sizes;
  mFactors.resize(mDim);

  unsigned int tmpDataSize = 1;
  index_type::const_reverse_iterator it, itEnd = sizes.rend();
  index_type::reverse_iterator itFaktor;
  for (it = sizes.rbegin(), itFaktor = mFactors.rbegin(); it != itEnd; ++it, ++itFaktor)
    {
      *itFaktor = tmpDataSize;
      tmpDataSize *= *it;
    }
  mData.resize(tmpDataSize);
}

CCopasiArray::data_type & CCopasiArray::operator[] (const index_type & index)
{
#ifdef COPASI_DEBUG
  assert(index.size() == mDim);
#endif

  unsigned int tmpindex = 0;
  index_type::const_iterator itIndex, it, itEnd = mFactors.end();
  for (itIndex = index.begin(), it = mFactors.begin(); it != itEnd; ++it, ++itIndex)
    tmpindex += *itIndex * *it;

  return mData[tmpindex];
}

const CCopasiArray::data_type & CCopasiArray::operator[] (const index_type & index) const
  {
#ifdef COPASI_DEBUG
    assert(index.size() == mDim);
#endif

    unsigned int tmpindex = 0;
    index_type::const_iterator itIndex, it, itEnd = mFactors.end();
    for (itIndex = index.begin(), it = mFactors.begin(); it != itEnd; ++it, ++itIndex)
      tmpindex += *itIndex * *it;

    return mData[tmpindex];
  }

//
//*******************************************************

CCopasiMatrixInterface::CCopasiMatrixInterface(CMatrix<C_FLOAT64> * matrix)
    : mMatrix(matrix)
{
  assert(mMatrix);
  mSizes.resize(2);
  mSizes[0] = mMatrix->numRows();
  mSizes[1] = mMatrix->numCols();
}

void CCopasiMatrixInterface::resize(const index_type & sizes)
{
  assert(sizes.size() == 2);
  mSizes = sizes;
  mMatrix->resize(mSizes[0], mSizes[1]);
}

CCopasiArray::data_type & CCopasiMatrixInterface::operator[] (const index_type & index)
{
#ifdef COPASI_DEBUG
  assert(index.size() == 2);
#endif
  return (*mMatrix)(index[0], index[1]);
}

const CCopasiArray::data_type & CCopasiMatrixInterface::operator[] (const index_type & index) const
  {
#ifdef COPASI_DEBUG
    assert(index.size() == 2);
#endif
    return (*mMatrix)(index[0], index[1]);
  }

//
//*******************************************************

CArrayAnnotation::CArrayAnnotation(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   CCopasiAbstractArray * array)
    : CCopasiContainer(name, pParent, "Array" /*, flags */),  //TODO: flags
    mArray(array)
{
  assert(mArray);

  resizeAnnotations();
}

void CArrayAnnotation::resizeAnnotations()
{
  mAnnotations.resize(mArray->dimensionality());
  unsigned int i;
  for (i = 0; i < mArray->dimensionality(); ++i)
    mAnnotations[i].resize(mArray->size()[i]);

  mDimensionDescriptions.resize(mArray->dimensionality());
}

//private
void CArrayAnnotation::resize(const CCopasiAbstractArray::index_type & sizes)
{
  assert(mArray);
  mArray->resize(sizes);
  resizeAnnotations();
}

void CArrayAnnotation::printDebug(std::ostream & out) const
  {
    out << mDescription << std::endl;
    out << "  Dimensionality: " << dimensionality() << std::endl;

    unsigned int i, j;
    for (i = 0; i < dimensionality(); ++i)
      {
        out << "   " << i << ": " << mDimensionDescriptions[i] << std::endl;

        for (j = 0; j < mAnnotations[i].size(); ++j)
          out << "     " << mAnnotations[i][j] << std::endl;

        out << std::endl;
      }
  }

//
//*******************************************************

CAnnotatedMatrixOld::CAnnotatedMatrixOld(const std::string & name,
    const CCopasiContainer * pParent):
    CMatrix<C_FLOAT64>(),
    CCopasiContainer(name, pParent, "AnnotatedMatrix",
                     CCopasiObject::Container |
                     CCopasiObject::NonUniqueName),
    mKey(GlobalKeys.add("AnnotatedMatrix", this))
{
  //initObjects();
  CONSTRUCTOR_TRACE;
}

CAnnotatedMatrixOld::CAnnotatedMatrixOld(const CAnnotatedMatrixOld & src,
    const CCopasiContainer * pParent):
    CMatrix<C_FLOAT64>(),
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("AnnotatedMatrix", this))
{
  //initObjects();
  CONSTRUCTOR_TRACE;
}

CAnnotatedMatrixOld::~CAnnotatedMatrixOld()
{}
