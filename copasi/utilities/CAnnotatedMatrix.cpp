// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CAnnotatedMatrix.cpp,v $
//   $Revision: 1.26.2.3 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/15 21:30:43 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file CAnnotatedMatrix.cpp
    \brief Implementation file of class CCopasiArray and CArrayAnnotation
 */

#include <sstream>
#include "CAnnotatedMatrix.h"
#include "CCopasiVector.h"

#include "report/CKeyFactory.h"
#include "report/CArrayElementReference.h"

CArrayAnnotation::CArrayAnnotation(const std::string & name,
                                   const CCopasiContainer * pParent,
                                   CCopasiAbstractArray * array,
                                   const bool & adopt)
    : CCopasiContainer(name, pParent, "Array" , CCopasiObject::Array),
    mpArray(array),
    mDestructArray(adopt),
    mDefaultMode(OBJECTS)
{
  assert(mpArray);

  resize();

  //addObjectReference("Annotated Matrix", *this, CCopasiObject::ValueDbl);
}

CArrayAnnotation::~CArrayAnnotation()
{
  if (mDestructArray)
    pdelete(mpArray);
}

void CArrayAnnotation::setArray(CCopasiAbstractArray * a)
{
  mpArray = a;
}

void CArrayAnnotation::setMode(unsigned int d, Mode m)
{
  mModes[d] = m;
  resizeOneDimension(d);
}

void CArrayAnnotation::setMode(Mode m)
{
  mDefaultMode = m;

  unsigned int i;
  for (i = 0; i < mModes.size(); ++i)
    setMode(i, m);
}

unsigned int CArrayAnnotation::dimensionality() const
  {
    return mModes.size();
  }

void CArrayAnnotation::setCopasiVector(unsigned int d, const CCopasiContainer* v)
{
  assert(d < mCopasiVectors.size());
  assert((mModes[d] == VECTOR) || (mModes[d] == VECTOR_ON_THE_FLY));

  mCopasiVectors[d] = v;
  if (mModes[d] == VECTOR)
    createAnnotationsCNFromCopasiVector(d, mCopasiVectors[d]);
}

void CArrayAnnotation::setAnnotationCN(unsigned int d, unsigned int i, const std::string cn)
{
  assert(d < mAnnotationsCN.size());
  assert(mModes[d] == OBJECTS);

  resizeOneDimension(d);
  assert(i < mAnnotationsCN[d].size());

  mAnnotationsCN[d][i] = cn;
}

void CArrayAnnotation::setAnnotationString(unsigned int d, unsigned int i, const std::string s)
{
  assert(d < mAnnotationsString.size());
  assert(mModes[d] == STRINGS);

  resizeOneDimension(d);
  assert(i < mAnnotationsString[d].size());

  mAnnotationsString[d][i] = s;
}

const std::vector<CRegisteredObjectName> & CArrayAnnotation::getAnnotationsCN(unsigned int d) const
  {
    assert(d < mModes.size());
    assert(mModes[d] != STRINGS);
    assert(mModes[d] != NUMBERS);

    if (mModes[d] == VECTOR_ON_THE_FLY)
      createAnnotationsCNFromCopasiVector(d, mCopasiVectors[d]);

    return mAnnotationsCN[d];
  }

const std::vector<std::string> & CArrayAnnotation::getAnnotationsString(unsigned int d, bool display) const
  {
    assert(d < mModes.size());

    //generate CNs (if necessary)
    if (mModes[d] == VECTOR_ON_THE_FLY)
      createAnnotationsCNFromCopasiVector(d, mCopasiVectors[d]);

    //generate DisplayNames
    if ((mModes[d] == VECTOR) || (mModes[d] == VECTOR_ON_THE_FLY) || (mModes[d] == OBJECTS))
      {
        unsigned int i, imax = mAnnotationsCN[d].size();
        mAnnotationsString[d].resize(imax);
        for (i = 0; i < imax; ++i)
          {
            const CCopasiObject * obj = CCopasiContainer::ObjectFromName(mAnnotationsCN[d][i]);
            if (obj)
              mAnnotationsString[d][i] =
                display ? obj->getObjectDisplayName() : obj->getObjectName();
            else
              mAnnotationsString[d][i] = "???";
          }
      }

    //generate Numbers
    if (mModes[d] == NUMBERS)
      createNumbers(d);

    // if the mode is STRINGS do nothing, mAnnotationsString is supposed to contain
    // the correct strings

    return mAnnotationsString[d];
  }

const std::string & CArrayAnnotation::getDimensionDescription(unsigned int d) const
  {
    assert(d < mDimensionDescriptions.size());
    return mDimensionDescriptions[d];
  }

void CArrayAnnotation::setDimensionDescription(unsigned int d, const std::string & s)
{
  assert(d < mDimensionDescriptions.size());
  mDimensionDescriptions[d] = s;
}

const std::string & CArrayAnnotation::getDescription() const
  {return mDescription;}

void CArrayAnnotation::setDescription(const std::string & s)
{mDescription = s;}

bool CArrayAnnotation::createAnnotationsCNFromCopasiVector(unsigned int d,
    const CCopasiContainer* v) const
  {
    if (!v) return false;
    if (! (v->isVector() || v->isNameVector())) return false;
    if (d >= mpArray->dimensionality()) return false;

    //now we know we have a vector. A CCopasiVector[N/S], hopefully, so that the following cast is valid:
    const CCopasiVector< CCopasiObject > * pVector =
      reinterpret_cast<const CCopasiVector< CCopasiObject > * >(v);

    mAnnotationsCN[d].resize(pVector->size());
    //if (pVector->size() < mAnnotations[d].size()) return false;

    unsigned int i;
    for (i = 0; i < mAnnotationsCN[d].size(); ++i)
      {
        if (!(*pVector)[i])
          return false;
        else
          mAnnotationsCN[d][i] = (*pVector)[i]->getCN();
      }
    return true;
  }

//private
void CArrayAnnotation::createNumbers(unsigned int /*d*/) const
  {
    //TODO
  }

//private
void CArrayAnnotation::reDimensionalize(unsigned int d)
{
  mAnnotationsCN.resize(d);
  mAnnotationsString.resize(d);
  mDimensionDescriptions.resize(d);
  mCopasiVectors.resize(d);
  mModes.resize(d, mDefaultMode);
}

//private
void CArrayAnnotation::resizeOneDimension(unsigned int d)
{
  if (mModes[d] != VECTOR)
    {
      mAnnotationsCN[d].resize(mpArray->size()[d]);
      mAnnotationsString[d].resize(mpArray->size()[d]);
    }
}

void CArrayAnnotation::resize()
{
  assert(mpArray);
  reDimensionalize(mpArray->dimensionality());

  unsigned int i, imax = mpArray->dimensionality();
  for (i = 0; i < imax; ++i)
    resizeOneDimension(i);
}

const CCopasiObject* CArrayAnnotation::addElementReference(CCopasiAbstractArray::index_type index) const
  {
    //generate the index string
    std::string tmp;
    std::ostringstream indexString;
    unsigned C_INT32 ii = 0;
    for (ii = 0; ii < index.size(); ++ii)
      {
        indexString << "[" << index[ii] << "]";
      }

    return this->getObject(indexString.str());
  }

const CCopasiObject* CArrayAnnotation::addElementReference(C_INT32 u, C_INT32 v) const
  {
    CCopasiAbstractArray::index_type index;
    index.push_back(u);
    index.push_back(v);
    return addElementReference(index);
  }

const CCopasiObject * CArrayAnnotation::getObject(const CCopasiObjectName & cn) const
  {
    //std::cout << "CArrayAnnotation::getObject() " << cn << std::endl;

    if (cn == "")
      {
        return this;
      }

    //if there are no indices there could still be other children. This can be handled
    //by the container base class
    if (cn.getElementName(0, false) == "") //no indices
      return this->CCopasiContainer::getObject(cn);

    //so now we know we have indices. So we check if the array element reference
    //exists, if not we create it. Then getObject() of the element reference is called
    //with the remainder TODO

    /*
        //first get the array indices. At the moment only numerical indices...
        C_INT32 ii = 0;
        CCopasiArray::index_type index;
        while (cn.getElementName(ii, false) != "")
          {
            index.push_back(cn.getElementIndex(ii));
            ++ii;
          }
    */
    //first get the index string
    std::string tmp;
    std::string indexString;
    C_INT32 ii = 0;
    while ((tmp = cn.getElementName(ii, false)) != "")
      {
        indexString += "[" + tmp + "]";
        ++ii;
      }

    const CCopasiObject* pObject = NULL; //this will contain the element reference

    //if the reference object already exists, its name will be identical to the index
    std::pair< objectMap::const_iterator, objectMap::const_iterator > range =
      mObjects.equal_range(indexString);
    objectMap::const_iterator it = range.first;
    while (it != range.second && it->second->getObjectType() != "ElementReference") ++it;

    if (it == range.second) //not found
      {
        //create new element reference
        pObject = new CArrayElementReference(cn, this);
      }
    else
      {
        pObject = it->second;
      }

    if (pObject)
      return pObject->getObject(cn.getRemainder());
    else
      return NULL;

    /*
    if (index.size() != dimensionality())  //wrong number of indices for this array
      return NULL;

    unsigned C_INT32 i;
    for (i = 0; i < dimensionality(); ++i)
      if (index[i] >= size()[i]) //out of range
        return NULL;
    */

    //TODO remove element children after resize
    //TODO check optimization expression widget...
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
            ostream << SPC(indent) << getDimensionDescription(level) << ": " << display[level][i] << "\n";
            index[level] = i;
            printRecursively(ostream, level - 1, index, display);
          }
      }
  }

#undef SPC

std::ostream &operator<<(std::ostream &os, const CArrayAnnotation & o)
{
  if (!o.array()) return os;

  //cache the display names
  std::vector<std::vector<std::string> > displaynames;
  unsigned C_INT32 i;
  for (i = 0; i < o.dimensionality(); ++i)
    displaynames.push_back(o.getAnnotationsString(i));

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

bool CArrayAnnotation::isEmpty()
{
  // either the dimension itself ...
  int dim = dimensionality();
  //  std::cout << "Dimensionality = " << dim << std::endl;
  if (dim == 0) return true;

  // ... or the size of each dimension should be greater than zero.
  int idx = 0;
  for (idx = 0; idx < dim; idx++)
    {
      // std::cout << "size of dim " << idx << " = " << getAnnotationsString(idx, true).size()
      //     << " -vs- " << getAnnotationsCN(idx).size() << " -vs- " << size()[idx] << std::endl;
      // if (!getAnnotationsCN(idx).size()) // -> incl. 'sink' and 'source'
      if (!size()[idx])
        return true;
    }

  return false;
}

std::string CArrayAnnotation::getObjectDisplayName(bool regular, bool richtext) const
  {
    std::string part;
    if (getObjectParent() && getObjectParent()->getObjectType() != "Model")
      part = getObjectParent()->getObjectDisplayName(regular, richtext) + ".";

    return part + getObjectName() + "[[]]";
  }

// void CArrayAnnotation::printDebugLoop(std::ostream & out, CCopasiAbstractArray::index_type & index, unsigned int level) const
//   {
//     unsigned int i, imax = mArray->size()[level];
//     for (i = 0; i < imax; ++i)
//       {
//         index[level] = i;
//
//         if (level == dimensionality() - 1)
//           {
//             out << (*mArray)[index] << "  ";
//}
//         else
//           {
//             printDebugLoop(out, index, level + 1);
//             out << std::endl;
//}
//}
//}
//
// void CArrayAnnotation::printDebug(std::ostream & out) const
//   {
//     out << mDescription << std::endl;
//     out << "  Dimensionality: " << dimensionality() << std::endl;
//
//     unsigned int i, j;
//     for (i = 0; i < dimensionality(); ++i)
//       {
//         out << "   " << i << ": " << mDimensionDescriptions[i] << std::endl;
//
//         //std::vector<std::string> names = const_cast<CArrayAnnotation*>(this)->getAnnotationsDisplay(i);
//
//         for (j = 0; j < mAnnotations[i].size(); ++j)
//           out << "     " << mAnnotations[i][j] /*<< " :" << names[j]*/ << std::endl;
//
//         out << std::endl;
//}
//
//     CCopasiAbstractArray::index_type index; index.resize(dimensionality());
//     printDebugLoop(out, index, 0);
//}
