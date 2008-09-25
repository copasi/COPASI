// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CArrayElementReference.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/09/25 22:36:03 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CArrayElementReference.h"
#include "CCopasiContainer.h"

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
    //TODO

    return mpReference;
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
