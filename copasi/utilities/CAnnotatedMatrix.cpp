/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/05 15:57:04 $
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

CAnnotatedMatrix::CAnnotatedMatrix(const std::string & name,
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

CAnnotatedMatrix::CAnnotatedMatrix(const CAnnotatedMatrix & src,
                                   const CCopasiContainer * pParent):
    CMatrix<C_FLOAT64>(),
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("AnnotatedMatrix", this))
{
  //initObjects();
  CONSTRUCTOR_TRACE;
}

CAnnotatedMatrix::~CAnnotatedMatrix()
{}
