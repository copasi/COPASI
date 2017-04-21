// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/core/CDataContainer.h"
#include "core/CDataArray.h"
#include "CArrayElementReference.h"

CArrayElementReference::CArrayElementReference(const std::vector< CRegisteredCommonName > & index,
    const CDataContainer * pParent,
    const CFlags< Flag > & flag)
  : CDataObject("Value", pParent, "ElementReference",
                flag | CDataObject::Reference | CDataObject::NonUniqueName | CDataObject::ValueDbl),
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
  std::vector< CRegisteredCommonName >::const_iterator it = mIndex.begin();
  std::vector< CRegisteredCommonName >::const_iterator end = mIndex.end();

  for (; it != end; ++it)
    {
      const CDataObject * pObject = CObjectInterface::DataObject(getObjectFromCN(*it));

      if (pObject != NULL)
        {
          ObjectName += "[" + CCommonName::escape(pObject->getObjectDisplayName()) + "]";
        }
      else
        {
          size_t Index;

          if (strToIndex(*it, Index))
            {
              ObjectName += "[" + *it + "]";
            }
          else
            {
              ObjectName += "[" + std::string("not found") + "]";
            }
        }
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
  CDataArray * pArray = dynamic_cast< CDataArray * >(getObjectParent());

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
      CDataContainer* pT = getObjectAncestor("Task");

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

CCommonName CArrayElementReference::getCN() const
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
  CArrayInterface::data_type * tmp = (double*)getValuePointer();

  if (tmp)
    (*ostream) << *tmp;
};
