// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*!
    \file CDataContainer.cpp
    \brief Implementation file of class CDataContainer
 */

/**
 * Class CDataContainer
 *
 * This class is the is used to group CDataObjects logically. It itself is
 * an object. Contained objects are still globally accessible.
 *
 * Copyright Stefan Hoops 2002
 */

#include "copasi/copasi.h"

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CDataVector.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataTimer.h"
#include "copasi/core/CDataString.h"

#include "copasi/utilities/CUnit.h"
#include "copasi/undo/CUndoData.h"
#include "copasi/model/CModel.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"

const CObjectInterface::ContainerList CDataContainer::EmptyList;

// static
CDataContainer * CDataContainer::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  return new CDataContainer(data.getProperty(CData::OBJECT_NAME).toString(),
                            NO_PARENT,
                            data.getProperty(CData::OBJECT_TYPE).toString(),
                            CFlags< Flag >(data.getProperty(CData::OBJECT_FLAG).toString()));
}

// virtual
CData CDataContainer::toData() const
{
  return CDataObject::toData();
}

// virtual
bool CDataContainer::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  return CDataObject::applyData(data, changes);
}

// virtual
void CDataContainer::createUndoData(CUndoData & undoData,
                                    const CUndoData::Type & type,
                                    const CData & oldData,
                                    const CCore::Framework & framework) const
{
  CDataObject::createUndoData(undoData, type, oldData, framework);

  if (type == CUndoData::Type::REMOVE)
    {
      appendDeletedDependentData(undoData);
    }

  return;
}

// virtual
bool CDataContainer::appendDeletedDependentData(CUndoData & undoData) const
{
  bool dataAppended = false;

  const CFunctionDB * pFunctionDB = dynamic_cast< const CFunctionDB * >(getObjectAncestor("FunctionDB"));
  const CDataModel * pDataModel = getObjectDataModel();

  if (pFunctionDB == NULL &&
      pDataModel == NULL)
    {
      return dataAppended;
    }

  CDataObject::DataObjectSet Reactions;
  CDataObject::DataObjectSet Metabolites;
  CDataObject::DataObjectSet Values;
  CDataObject::DataObjectSet Compartments;
  CDataObject::DataObjectSet Events;
  CDataObject::DataObjectSet EventAssignments;
  CDataObject::DataObjectSet Tasks;

  if (pFunctionDB != NULL)
    {
      CDataObject::ObjectSet DeletedObjects;
      DeletedObjects.insert(this);
      CDataObject::DataObjectSet Functions;

      pFunctionDB->appendDependentFunctions(DeletedObjects, Functions);

      CDataObject::DataObjectSet::const_iterator it = Functions.begin();
      CDataObject::DataObjectSet::const_iterator end = Functions.end();

      for (; it != end; ++it)
        {
          dataAppended |= undoData.addPreProcessData(CUndoData(CUndoData::Type::REMOVE, *it));
        }
    }

  if (pDataModel != NULL)
    {
      const CModel * pModel = pDataModel->getModel();

      DataObjectSet dependentReactions;
      DataObjectSet dependentMetabolites;
      DataObjectSet dependentCompartments;
      DataObjectSet dependentModelValues;
      DataObjectSet dependentEvents;
      DataObjectSet dependentEventAssignments;

      dataAppended |= pModel->appendAllDependents(*this,
                      dependentReactions,
                      dependentMetabolites,
                      dependentCompartments,
                      dependentModelValues,
                      dependentEvents,
                      dependentEventAssignments);

      DataObjectSet::const_iterator it = dependentEventAssignments.begin();
      DataObjectSet::const_iterator end = dependentEventAssignments.end();

      for (; it != end; ++it)
        {
          undoData.addPreProcessData(CUndoData(CUndoData::Type::REMOVE, *it, undoData.getAuthorID()));
        }

      it = dependentEvents.begin();
      end = dependentEvents.end();

      for (; it != end; ++it)
        {
          undoData.addPreProcessData(CUndoData(CUndoData::Type::REMOVE, *it, undoData.getAuthorID()));
        }

      it = dependentReactions.begin();
      end = dependentReactions.end();

      for (; it != end; ++it)
        {
          undoData.addPreProcessData(CUndoData(CUndoData::Type::REMOVE, *it, undoData.getAuthorID()));
        }

      it = dependentModelValues.begin();
      end = dependentModelValues.end();

      for (; it != end; ++it)
        {
          undoData.addPreProcessData(CUndoData(CUndoData::Type::REMOVE, *it, undoData.getAuthorID()));
        }

      it = dependentMetabolites.begin();
      end = dependentMetabolites.end();

      for (; it != end; ++it)
        {
          undoData.addPreProcessData(CUndoData(CUndoData::Type::REMOVE, *it, undoData.getAuthorID()));
        }

      it = dependentCompartments.begin();
      end = dependentCompartments.end();

      for (; it != end; ++it)
        {
          undoData.addPreProcessData(CUndoData(CUndoData::Type::REMOVE, *it, undoData.getAuthorID()));
        }
    }

  return dataAppended;
}

CDataContainer::CDataContainer() :
  CDataObject(),
  mObjects()
{}

CDataContainer::CDataContainer(const std::string & name,
                               const CDataContainer * pParent,
                               const std::string & type,
                               const CFlags< Flag > & flag):
  CDataObject(name, pParent, type, flag | CDataObject::Container),
  mObjects()
{}

CDataContainer::CDataContainer(const CDataContainer & src,
                               const CDataContainer * pParent):
  CDataObject(src, pParent),
  mObjects()
{}

CDataContainer::~CDataContainer()
{
  objectMap::iterator it = mObjects.begin();
  objectMap::iterator end = mObjects.end();

  for (; it != end; ++it)
    if (*it != NULL)
      {
        if ((*it)->getObjectParent() == this)
          {
            (*it)->setObjectParent(NULL);

            if (*it != NULL) delete (*it);
          }
        else
          {
            (*it)->removeReference(this);
          }
      }
}

const CObjectInterface * CDataContainer::getObject(const CCommonName & cn) const
{
  if (cn == "")
    {
      if (hasFlag(Root))
        return NULL;
      else
        return this;
    }

  if (cn == "Reference=Name"
      || cn == "Property=Name"
      || cn == "Property=DisplayName")
    {
      return CDataObject::getObject(cn);
    }

  std::string Name = cn.getObjectName();
  std::string Type = cn.getObjectType();

  if (getObjectName() == Name && getObjectType() == Type)
    return getObject(cn.getRemainder());

  if (Name == "CMIRIAMInfoObject" &&
      Type == "CMIRIAMInfo" &&
      CAnnotation::castObject(this) != NULL)
    {
      // Create a MIRIAM Info if needed.
      const CMIRIAMInfo * pInfo = CAnnotation::allocateMiriamInfo(const_cast< CDataContainer * >(this));
      return pInfo->getObject(cn.getRemainder());
    }

  //check if the first part of the cn matches one of the children (by name and type)
  objectMap::range range = mObjects.equal_range(Name);

  while (range.first != range.second && (*range.first)->getObjectType() != Type) ++range.first;

  if (range.first == range.second) //not found in the list of children
    {
      if (Type == "String")
        return new CDataString(Name, this);
      else if (Type == "Separator")
        return new CCopasiReportSeparator(Name, this);
      else if (getObjectName() == "Root" && Type == "Vector" && CRootContainer::getRoot() != this)
        return CRootContainer::getRoot()->getObject(cn);
      else
        return NULL;
    }

  const CObjectInterface * pObject = NULL;

  //handle objects where the array flag is set. Currently this applies to the
  //CArrayAnnotation object. Since this is also a container, we have to do this
  //before handling general containers.
  if ((*range.first)->hasFlag(Array))
    {
      //we need to call the getObject() method of the child array with the
      //remainder of the cn, with the indices in square brackets, or with an empty string

      //if there are no indices there could still be a remainder (since the array can also be
      //a container)
      if (cn.getElementName(0, false) == "") //no indices
        return (*range.first)->getObject(cn.getRemainder());

      return (*range.first)->getObject(cn);
    }

  //handle generic containers.
  if ((*range.first)->hasFlag(Container))
    return (*range.first)->getObject(cn.getRemainder());

  if ((*range.first)->hasFlag(Matrix))
    {
      if (cn.getElementName(0, false) == "")
        return *range.first;

      pObject = (*range.first)->getObject("[" + cn.getElementName(0, false) + "]" +                   //TODO really?
                                          "[" + cn.getElementName(1, false) + "]");

      if ((*range.first)->getObjectType() == "Reference" || !pObject)
        return pObject;
      else
        return pObject->getObject(cn.getRemainder());
    }

  return (*range.first)->getObject(cn.getRemainder());
}

const CDataContainer::objectMap & CDataContainer::getObjects() const
{return mObjects;}

CDataContainer::objectMap & CDataContainer::getObjects()
{return mObjects;}

const CDataObject * CDataContainer::getValueObject() const
{
  void * ptr = getValuePointer();

  if (ptr == NULL) return NULL;

  objectMap::const_iterator it = mObjects.begin();
  objectMap::const_iterator end = mObjects.end();

  for (; it != end; ++it)
    if (ptr == (*it)->getValuePointer()) return *it;

  return NULL;
}

void CDataContainer::initObjects() {}

// virtual
bool CDataContainer::add(CDataObject * pObject,
                         const bool & adopt)
{
  if (pObject == NULL)
    {
      return false;
    }

  bool success = mObjects.insert(pObject).second;

  if (adopt)
    pObject->setObjectParent(this);
  else
    pObject->addReference(this);

  validityChanged(pObject->getValidity());

  return success;
}

// virtual
bool CDataContainer::remove(CDataObject * pObject)
{
  if (pObject != NULL)
    {
      validityRemoved(pObject->getValidity());
      pObject->removeReference(this);
    }

  return mObjects.erase(pObject);
}

// virtual
size_t CDataContainer::getIndex(const CDataObject * pObject) const
{
  return C_INVALID_INDEX;
}

void CDataContainer::getDescendants(CDataObject::DataObjectSet & descendants, const bool & recursive) const
{
  const CDataContainer * pContainer;
  objectMap::const_iterator it = mObjects.begin();
  objectMap::const_iterator end = mObjects.end();

  for (; it != end; ++it)
    if ((*it)->getObjectParent() == this)
      {
        descendants.insert(*it);

        if (recursive &&
            (pContainer = dynamic_cast< const CDataContainer * >(*it)) != NULL)
          {
            pContainer->getDescendants(descendants, recursive);
          }
      }
}

void CDataContainer::objectRenamed(CDataObject * pObject, const std::string & oldName)
{
  mObjects.objectRenamed(pObject, oldName);
}

// virtual
const std::string CDataContainer::getUnits() const
{return "?";}

// virtual
std::string CDataContainer::getChildObjectUnits(const CDataObject * /* pObject */) const
{return "?";}

// virtual
CUndoObjectInterface * CDataContainer::insert(const CData & data)
{
  return NULL;
}
