// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CArrayElementReference.h"
#include "CCopasiContainer.h"
#include "utilities/CAnnotatedMatrix.h"

CArrayElementReference::CArrayElementReference(const std::vector< CRegisteredObjectName > & index, const CCopasiContainer * pParent)
  : CCopasiObject("Value", pParent, "ElementReference",
                  CCopasiObject::Reference |
                  CCopasiObject::NonUniqueName |
                  CCopasiObject::ValueDbl),
  //    mpReference(NULL),
  mIndex(index),
  mIgnoreUpdateObjectName(false)
{
  assert(pParent != NULL);

  updateObjectName();
}

void CArrayElementReference::updateObjectName()
{
  if (mIgnoreUpdateObjectName) return;

  mIgnoreUpdateObjectName = true;

  std::string ObjectName;
  std::vector< CRegisteredObjectName >::const_iterator it = mIndex.begin();
  std::vector< CRegisteredObjectName >::const_iterator end = mIndex.end();

  for (; it != end; ++it)
    {
      const CCopasiObject * pObject = CObjectInterface::DataObject(getObjectFromCN(*it));

      ObjectName += "[" + ((pObject != NULL) ? CCopasiObjectName::escape(pObject->getObjectDisplayName()) : std::string("not found")) + "]";
    }

  if (ObjectName.empty())
    {
      ObjectName = "[.]";
    }

  setObjectName(ObjectName);

  mIgnoreUpdateObjectName = false;
}

void * CArrayElementReference::getValuePointer() const
{
  CArrayAnnotation * pArray = dynamic_cast< CArrayAnnotation * >(getObjectParent());

  if (pArray != NULL)
    {
      return &pArray->operator [](mIndex);
    }

  return NULL;
}

std::string CArrayElementReference::getObjectDisplayName() const
{
  if (getObjectParent())
    {
      const_cast< CArrayElementReference * >(this)->updateObjectName();

      //if the array has as task as ancestor, use the task (skip the problem/method)
      CCopasiContainer* pT = getObjectAncestor("Task");

      std::string part;

      if (pT)
        part = pT->getObjectDisplayName() + ".";
      else if (getObjectParent()->getObjectParent() && getObjectParent()->getObjectParent()->getObjectType() != "Model")
        part = getObjectParent()->getObjectParent()->getObjectDisplayName() + ".";

      //now part contains the display name of the task, or the parent of the parent
      return part + getObjectParent()->getObjectName() + getObjectName();
    }
  else
    return "Array" + getObjectName();
}

CCopasiObjectName CArrayElementReference::getCN() const
{
  const_cast< CArrayElementReference * >(this)->updateObjectName();

  if (getObjectParent())
    {
      return getObjectParent()->getCN() + getObjectName();
    }
  else
    return "Array" + getObjectName();
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
