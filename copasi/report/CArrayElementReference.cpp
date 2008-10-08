// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CArrayElementReference.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/08 12:54:32 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CArrayElementReference.h"
#include "CCopasiContainer.h"
#include "utilities/CAnnotatedMatrix.h"

CArrayElementReference::CArrayElementReference(const std::string & index, const CCopasiContainer * pParent)
    : CCopasiObject(index, pParent, "ElementReference",
                    CCopasiObject::Reference |
                    CCopasiObject::NonUniqueName |
                    CCopasiObject::ValueDbl),
    mpReference(NULL),
    mIndex(index)
{
  assert(pParent != NULL);
}

void CArrayElementReference::updateMethod(const CCopasiAbstractArray::data_type & value)
{
  if (mpReference)
    *mpReference = value;
}

void * CArrayElementReference::getValuePointer() const
  {
    CArrayAnnotation * tmpAA = dynamic_cast<CArrayAnnotation*>(getObjectParent());
    if (!tmpAA) return NULL;

    //now get the array indices. At the moment only numerical indices...
    //this could be done in the constructor, actually
    unsigned C_INT32 ii = 0;
    CCopasiArray::index_type index;
    while (mIndex.getElementName(ii, false) != "")
      {
        index.push_back(mIndex.getElementIndex(ii));
        ++ii;
      }

    if (index.size() != tmpAA->dimensionality())  //wrong number of indices for this array
      return NULL;

    for (ii = 0; ii < tmpAA->dimensionality(); ++ii)
      if (index[ii] >= tmpAA->size()[ii]) //out of range
        return NULL;

    return &(*tmpAA->array())[index];

    //TODO
    //TODO perhaps we should cache the pointer. This would mean we need to invalidate the pointer
    //if somthing with the array changes

    //return mpReference;
  }

std::string CArrayElementReference::getObjectDisplayName(bool regular, bool richtext) const
  {
    if (getObjectParent())
      return getObjectParent()->getObjectDisplayName(regular, richtext) + mIndex;
    else
      return "Array" + mIndex;
  }

CCopasiObjectName CArrayElementReference::getCN() const
  {
    if (getObjectParent())
      return getObjectParent()->getCN() + mIndex;
    else
      return "Array" + mIndex;
  }

void CArrayElementReference::print(std::ostream * ostream) const
  {
    //if (mpReference)
    //  (*ostream) << *mpReference;

    //TODO perhaps we should cache the
    CCopasiAbstractArray::data_type * tmp = (double*)getValuePointer();
    if (tmp)
      (*ostream) << *tmp;
  };
