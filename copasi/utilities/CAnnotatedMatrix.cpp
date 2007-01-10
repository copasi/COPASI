/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.cpp,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: ssahle $
   $Date: 2007/01/10 10:38:59 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CAnnotatedMatrix.h"
#include "CCopasiVector.h"

#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"

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

  addObjectReference("Annotated Matrix", *this, CCopasiObject::ValueDbl);
}

unsigned int CArrayAnnotation::dimensionality() const
  {
    if (mOnTheFly)
      return mArray->dimensionality();
    else
      return mAnnotations.size();
  }

const std::vector<CRegisteredObjectName> & CArrayAnnotation::getAnnotations(unsigned int d) const
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

std::vector<std::string> CArrayAnnotation::getAnnotationsDisplay(unsigned int d) const
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

std::vector<std::string> CArrayAnnotation::getAnnotationsNames(unsigned int d) const
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

const std::string & CArrayAnnotation::getDimensionDescription(unsigned int d) const
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
  createAnnotationsFromCopasiVector(d, v);
}

const std::string & CArrayAnnotation::getDescription() const
  {return mDescription;}

void CArrayAnnotation::setDescription(const std::string & s)
{mDescription = s;}

//private
bool CArrayAnnotation::updateAnnotations() const
  {
    bool success = true;

    resizeAnnotations();

    unsigned int i;
    for (i = 0; i < mArray->dimensionality(); ++i)
      {
        if (mCopasiVectors[i])
          {
            if (!createAnnotationsFromCopasiVector(i, mCopasiVectors[i]))
              success = false;
          }
        else
          success = false;
      }
    return success;
  }

bool CArrayAnnotation::createAnnotationsFromCopasiVector(unsigned int d,
    const CCopasiContainer* v) const
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
void CArrayAnnotation::resizeAnnotations() const
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

void CArrayAnnotation::print(std::ostream * ostream) const
  {*ostream << *this;}

#define SPC(level) std::string(level, ' ')

void CArrayAnnotation::printRecursively(std::ostream & ostream, C_INT32 level,
                                        CCopasiAbstractArray::index_type & index,
                                        const std::vector<std::vector<std::string> > & display) const
  {
    unsigned C_INT32 indent = 2 * (dimensionality() - 1 - level);

    if (level == 0) //only vector
      {
        ostream << SPC(indent) << "Rows: " << getDimensionDescription(level) << "\n";

        unsigned C_INT32 imax = size()[0];
        for (index[0] = 0; index[0] < imax; ++index[0])
          ostream << SPC(indent) << display[0][index[0]] << "\t" << (*array())[index] << "\n";
      }
    else if (level == 1) //matrix
      {
        ostream << SPC(indent) << "Rows:    " << getDimensionDescription(level - 1) << "\n";
        ostream << SPC(indent) << "Columns: " << getDimensionDescription(level) << "\n";

        unsigned C_INT32 imax = size()[0];
        unsigned C_INT32 jmax = size()[1];
        ostream << SPC(indent);
        for (index[1] = 0; index[1] < jmax; ++index[1])
          ostream << "\t" << display[1][index[1]];
        ostream << "\n";
        for (index[0] = 0; index[0] < imax; ++index[0])
          {
            ostream << SPC(indent) << display[0][index[0]];
            for (index[1] = 0; index[1] < jmax; ++index[1])
              ostream << "\t" << (*array())[index];
            ostream << "\n";
          }
      }
    else //dimensionality > 2
      {
        unsigned C_INT32 i, imax = size()[level];
        for (i = 0; i < imax; ++i)
          {
            //std::cout << "*" << i << std::endl;
            ostream << SPC(indent) << getDimensionDescription(level) << ": " << display[level][i] << "\n";
            index[level] = i;
            printRecursively(ostream, level - 1, index, display);
          }
      }
  }

std::ostream &operator<<(std::ostream &os, const CArrayAnnotation & o)
{
  if (!o.array()) return os;

  if (o.mOnTheFly)
    const_cast<CArrayAnnotation*>(&o)->updateAnnotations();

  //cache the display names
  std::vector<std::vector<std::string> > displaynames;
  unsigned C_INT32 i;
  for (i = 0; i < o.dimensionality(); ++i)
    displaynames.push_back(o.getAnnotationsDisplay(i));

  os << o.getObjectName() << std::endl;
  os << o.getDescription() << std::endl;

  CCopasiAbstractArray::index_type arraysize = o.array()->size();
  if (o.dimensionality() == 0)
    {
      //only one scalar value
      os << (*o.array())[arraysize] << std::endl;
    }
  else
    {
      o.printRecursively(os, o.dimensionality() - 1, arraysize, displaynames);
    }

  return os;
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
