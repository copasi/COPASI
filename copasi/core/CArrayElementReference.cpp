// Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CDataArray.h"
#include "CArrayElementReference.h"

// static
CArrayElementReference * CArrayElementReference::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  std::vector< std::string > Index;

  if (data.isSetProperty(CData::ARRAY_ELEMENT_INDEX))
    {
      const std::vector< CDataValue > & DataIndex = data.getProperty(CData::ARRAY_ELEMENT_INDEX).toDataValues();
      Index.resize(DataIndex.size());

      std::vector< CDataValue >::const_iterator it = DataIndex.begin();
      std::vector< CDataValue >::const_iterator end = DataIndex.end();
      std::vector< std::string >::iterator itIndex = Index.begin();

      for (; it != end; ++it, ++itIndex)
        {
          *itIndex = it->toString();
        }
    }

  return new CArrayElementReference(Index, NO_PARENT, CFlags< Flag >(data.getProperty(CData::OBJECT_FLAG).toString()));
}

// virtual
CData CArrayElementReference::toData() const
{
  CData Data = CDataObject::toData();

  Data.addProperty(CData::ARRAY_ELEMENT_INDEX, std::vector< CDataValue >(mIndex.begin(), mIndex.end()));

  return Data;
}

// virtual
bool CArrayElementReference::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataObject::applyData(data, changes);

  if (data.isSetProperty(CData::ARRAY_ELEMENT_INDEX))
    {
      const std::vector< CDataValue > & Index = data.getProperty(CData::ARRAY_ELEMENT_INDEX).toDataValues();
      mIndex.resize(Index.size());

      std::vector< CDataValue >::const_iterator it = Index.begin();
      std::vector< CDataValue >::const_iterator end = Index.end();
      std::vector< CRegisteredCommonName >::iterator itIndex = mIndex.begin();

      for (; it != end; ++it, ++itIndex)
        {
          *itIndex = it->toString();
        }
    }

  return success;
}

CArrayElementReference::CArrayElementReference(const std::vector< std::string > & index,
    const CDataContainer * pParent,
    const CFlags< Flag > & flag)
  : CDataObject("Value", pParent, "ElementReference",
                flag | CDataObject::Reference | CDataObject::NonUniqueName | CDataObject::ValueDbl),
    //    mpReference(NULL),
    mIndex(index.begin(), index.end()),
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
      return &pArray->operator [](CDataArray::name_index_type(mIndex.begin(), mIndex.end()));
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
