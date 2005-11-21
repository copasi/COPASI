/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/21 16:55:18 $
   End CVS Header */

#include "CAnnotatedMatrix.h"
#include "report/CKeyFactory.h"
#include "CCopasiVector.h"

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

/*void CCopasiMatrixInterface::resize(const index_type & sizes)
{
  assert(sizes.size() == 2);
  mSizes = sizes;
  mMatrix->resize(mSizes[0], mSizes[1]);
}*/

//
//*******************************************************

CArrayAnnotation::CArrayAnnotation(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   CCopasiAbstractArray * array)
    : CCopasiContainer(name, pParent, "Array" /*, flags */),          //TODO: flags
    mArray(array)
{
  assert(mArray);

  resizeAnnotations();
}

unsigned int CArrayAnnotation::dimensionality() const
  {
    if (mOnTheFly)
      return mArray->dimensionality();
    else
      return mAnnotations.size();
  }

const std::vector<CRegisteredObjectName> & CArrayAnnotation::getAnnotations(unsigned int d)
{
  if (mOnTheFly)
    updateAnnotations();

  return mAnnotations[d];
}

void CArrayAnnotation::setAnnotation(unsigned int d, unsigned int i, const std::string cn)
{
  assert(d < mAnnotations.size());
  assert(i < mAnnotations[d].size());

  mAnnotations[d][i] = cn;
}

std::vector<std::string> CArrayAnnotation::getAnnotationsDisplay(unsigned int d)
{
  if (mOnTheFly)
    updateAnnotations();

  std::vector<std::string> ret;

  unsigned int i, imax = mAnnotations[d].size();
  ret.resize(imax);
  for (i = 0; i < imax; ++i)
    ret[i] = CCopasiContainer::ObjectFromName(mAnnotations[d][i])->getObjectDisplayName();

  return ret;
}

std::vector<std::string> CArrayAnnotation::getAnnotationsNames(unsigned int d)
{
  if (mOnTheFly)
    updateAnnotations();

  std::vector<std::string> ret;

  unsigned int i, imax = mAnnotations[d].size();
  ret.resize(imax);
  for (i = 0; i < imax; ++i)
    ret[i] = CCopasiContainer::ObjectFromName(mAnnotations[d][i])->getObjectName();

  return ret;
}

const std::string & CArrayAnnotation::getDimensionDescription(unsigned int d)
{
  if (mOnTheFly)
    mDimensionDescriptions.resize(mArray->dimensionality());

  return mDimensionDescriptions[d];
}

void CArrayAnnotation::setDimensionDescription(unsigned int d, const std::string & s)
{
  assert(d < mDimensionDescriptions.size());
  mDimensionDescriptions[d] = s;
}

void CArrayAnnotation::setCopasiVector(unsigned int d, const CCopasiContainer* v)
{
  assert(d < mCopasiVectors.size());
  mCopasiVectors[d] = v;
}

const std::string & CArrayAnnotation::getDescription() const
  {return mDescription;}

void CArrayAnnotation::setDescription(const std::string & s)
{mDescription = s;}

//private
bool CArrayAnnotation::updateAnnotations()
{
  bool success = true;

  resizeAnnotations();

  unsigned int i;
  for (i = 0; i < mArray->dimensionality(); ++i)
    {
      if (mCopasiVectors[i])
        if (!createAnnotationsFromCopasiVector(i, mCopasiVectors[i]))
          success = false;
        else
          success = false;
    }
  return success;
}

bool CArrayAnnotation::createAnnotationsFromCopasiVector(unsigned int d,
    const CCopasiContainer* v)
{
  if (!v) return false;
  if (! (v->isVector() || v->isNameVector())) return false;
  if (d >= mArray->dimensionality()) return false;

  //now we know we have a vector. A CCopasiVector[N/S], hopefully, so that the following cast is valid:
  const CCopasiVector< CCopasiObject > * pVector =
    reinterpret_cast<const CCopasiVector< CCopasiObject > * >(v);

  if (pVector->size() < mAnnotations[d].size()) return false;

  unsigned int i;
  for (i = 0; i < mAnnotations[d].size(); ++i)
    {
      if (!(*pVector)[i])
        return false;
      else
        mAnnotations[d][i] = (*pVector)[i]->getCN();
    }
  return true;
}

//private
void CArrayAnnotation::resizeAnnotations()
{
  mAnnotations.resize(mArray->dimensionality());
  unsigned int i;
  for (i = 0; i < mArray->dimensionality(); ++i)
    mAnnotations[i].resize(mArray->size()[i]);

  mDimensionDescriptions.resize(mArray->dimensionality());
  mCopasiVectors.resize(mArray->dimensionality());
}

void CArrayAnnotation::resize(/*const CCopasiAbstractArray::index_type & sizes*/)
{
  assert(mArray);
  //mArray->resize(sizes);
  resizeAnnotations();
}

void CArrayAnnotation::printDebugLoop(std::ostream & out, CCopasiAbstractArray::index_type & index, unsigned int level) const
  {
    unsigned int i, imax = mArray->size()[level];
    for (i = 0; i < imax; ++i)
      {
        index[level] = i;

        if (level == dimensionality() - 1)
          {
            out << (*mArray)[index] << "  ";
          }
        else
          {
            printDebugLoop(out, index, level + 1);
            out << std::endl;
          }
      }
  }

void CArrayAnnotation::printDebug(std::ostream & out) const
  {
    out << mDescription << std::endl;
    out << "  Dimensionality: " << dimensionality() << std::endl;

    unsigned int i, j;
    for (i = 0; i < dimensionality(); ++i)
      {
        out << "   " << i << ": " << mDimensionDescriptions[i] << std::endl;

        //std::vector<std::string> names = const_cast<CArrayAnnotation*>(this)->getAnnotationsDisplay(i);

        for (j = 0; j < mAnnotations[i].size(); ++j)
          out << "     " << mAnnotations[i][j] /*<< " :" << names[j]*/ << std::endl;

        out << std::endl;
      }

    CCopasiAbstractArray::index_type index; index.resize(dimensionality());
    printDebugLoop(out, index, 0);
  }

//
//*******************************************************
