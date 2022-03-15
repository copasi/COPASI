// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * Class CDataObject
 *
 * This class is the base class for all global accessible objects in COPASI.
 *
 * Copyright Stefan Hoops 2002
 */

#include "copasi/core/CDataObject.h"

#include <sstream>
#include <algorithm>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/copasi.h"

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/undo/CData.h"
#include <copasi/utilities/utility.h>

CDataObject::CDataObject()
  : CObjectInterface()
  , CUndoObjectInterface()
  , mObjectName("No Name")
  , mObjectType("Unknown Type")
  , mpObjectParent(NULL)
  , mObjectDisplayName()
  , mpObjectDisplayName(NULL)
  , mpObjectName(NULL)
  , mObjectFlag()
  , mReferencedValidities()
  , mAggregateValidity()
  , mReferences()
  , mPrerequisits()
{}

CDataObject::CDataObject(const std::string & name,
                         const CDataContainer * pParent,
                         const std::string & type,
                         const CFlags< CDataObject::Flag > & flag)
  : CObjectInterface()
  , CUndoObjectInterface()
  , mObjectName()
  , mObjectType(type)
  , mpObjectParent(const_cast< CDataContainer * >(pParent))
  , mObjectDisplayName()
  , mpObjectDisplayName(NULL)
  , mpObjectName(NULL)
  , mObjectFlag(flag)
  , mReferencedValidities()
  , mAggregateValidity()
  , mReferences()
  , mPrerequisits()
{
  if (CRegisteredCommonName::isEnabled())
    {
      CRegisteredCommonName::setEnabled(false);
      setObjectName(name);
      CRegisteredCommonName::setEnabled(true);
    }
  else
    {
      setObjectName(name);
    }

  if (mpObjectParent != NULL &&
      mpObjectParent->hasFlag(Container))
    {
      mpObjectParent->add(this, true);
    }

  addReference(mpObjectParent);
}

CDataObject::CDataObject(const CDataObject & src,
                         const CDataContainer * pParent)
  : CObjectInterface(src)
  , CUndoObjectInterface(src)
  , mObjectName(src.mObjectName)
  , mObjectType(src.mObjectType)
  , mpObjectParent(src.mpObjectParent)
  , mObjectDisplayName()
  , mpObjectDisplayName(NULL)
  , mpObjectName(NULL)
  , mObjectFlag(src.mObjectFlag)
  , mReferencedValidities()
  , mAggregateValidity()
  , mReferences()
  , mPrerequisits()
{
  if (pParent != INHERIT_PARENT)
    {
      mpObjectParent = const_cast< CDataContainer * >(pParent);
    }

  if (mpObjectParent != NULL)
    {
      mpObjectParent->add(this, true);
    }

  addReference(mpObjectParent);
}

CDataObject::~CDataObject()
{
  mAggregateValidity.clear();

  if (mpObjectParent)
    {
      mpObjectParent->remove(this);
    }

  if (!mReferences.empty())
    {
      std::set< CDataContainer * > References(mReferences);
      mReferences.clear();

      std::set< CDataContainer * >::iterator it = References.begin();
      std::set< CDataContainer * >::iterator end = References.end();

      for (; it != end; ++it)
        (*it)->remove(this);
    }

  if (mpObjectDisplayName != NULL)
    {
      mpObjectDisplayName->mpObjectParent = NULL;
      delete mpObjectDisplayName;
    }

  if (mpObjectName != NULL)
    {
      mpObjectName->mpObjectParent = NULL;
      delete mpObjectName;
    }
}

void CDataObject::print(std::ostream * ostream) const {(*ostream) << (*this);}

CCommonName CDataObject::getCN() const
{
  CCommonName CN;

  // if the object has a parent and if the object is not a datamodel,
  // we add the name of the parent to the common name
  if (hasFlag(DataModel))
    {
      CN = (std::string) "CN=Root";
    }
  else if (mpObjectParent)
    {
      std::stringstream tmp;
      tmp << mpObjectParent->getCN();
      size_t Index;

      if (mpObjectParent->hasFlag(Vector)
          && (Index = mpObjectParent->getIndex(this)) != C_INVALID_INDEX)
        {
          if (mpObjectParent->hasFlag(NameVector))
            tmp << "[" << CCommonName::escape(mObjectName) << "]";
          else if (mpObjectParent->hasFlag(Vector))
            tmp << "[" << mpObjectParent->getIndex(this) << "]";
        }
      else
        tmp << "," << CCommonName::escape(mObjectType)
            << "=" << CCommonName::escape(mObjectName);

      CN = tmp.str();
    }
  else
    {
      CN = CCommonName::escape(mObjectType)
           + "=" + CCommonName::escape(mObjectName);
    }

  return CN;
}

const CObjectInterface * CDataObject::getObject(const CCommonName & cn) const
{
  if (cn == "")
    {
      return this;
    }

  if (cn == "Property=DisplayName")
    {
      if (mpObjectDisplayName == NULL)
        {
          mpObjectDisplayName = new CDataObjectReference< std::string >("DisplayName", NULL, mObjectDisplayName, DisplayName);
          mpObjectDisplayName->mpObjectParent = static_cast< CDataContainer * >(const_cast< CDataObject * >(this));
        }

      mObjectDisplayName = getObjectDisplayName();

      return mpObjectDisplayName;
    }
  else if (cn == "Reference=Name"
           || cn == "Property=Name")
    {
      if (mpObjectName == NULL)
        {
          mpObjectName = new CDataObjectReference< std::string >("Name", NULL, *const_cast< std::string * >(&mObjectName));
          mpObjectName->mpObjectParent = static_cast< CDataContainer * >(const_cast< CDataObject * >(this));
        }

      return mpObjectName;
    }

  return NULL;
}

const CObjectInterface * CDataObject::getObjectFromCN(const CCommonName & cn) const
{
  CObjectInterface::ContainerList ListOfContainer;
  ListOfContainer.push_back(getObjectDataModel());

  return CObjectInterface::GetObjectFromCN(ListOfContainer, cn);
}

// static
void CDataObject::sanitizeObjectName(std::string & name)
{
  // We need to ensure that the name does not include any control character (below 0x20),
  // e.g. we convert '\t' (tab), '\n' (newline) and '\r' (return) to ' ' (space 0x20).
  std::string::iterator it = name.begin();
  std::string::iterator end = name.end();

  for (; it != end; ++it)
    if (0x00 <= *it && *it < 0x20)
      {
        *it = 0x20;
      }

  std::string::size_type pos = name.find_first_not_of(0x20);

  if (pos == std::string::npos)
    {
      name.clear();
      return;
    }

  name.erase(name.begin(), name.begin() + pos);

  pos = name.find_last_not_of(0x20);

  if (pos == std::string::npos)
    return;

  name.erase(name.begin() + pos + 1, name.end());
}

bool CDataObject::setObjectName(const std::string & name)
{
  std::string Name = (name == "") ? "No Name" : name;

  if (!hasFlag(StaticString))
    sanitizeObjectName(Name);

  if (Name == mObjectName) return true;

  std::string escapedName = CCommonName::escape(Name);

  if (isNumber(name))
    escapedName = "\"" + escapedName + "\"";

  if (mpObjectParent != NULL &&
      mpObjectParent->hasFlag(NameVector) &&
      mpObjectParent->getObject("[" + escapedName + "]") != NULL)
    return false;

  std::string OldName = mObjectName;

  std::string oldCN = this->getCN();
  mObjectName = Name;

  std::set< CDataContainer * >::iterator it = mReferences.begin();
  std::set< CDataContainer * >::iterator end = mReferences.end();

  for (; it != end; ++it)
    (*it)->objectRenamed(this, OldName);

  if (CRegisteredCommonName::isEnabled() &&
      mpObjectParent != NULL)
    {
      CRegisteredCommonName::handle(oldCN, this->getCN());
    }

  return true;
}

/*virtual*/
std::string CDataObject::getObjectDisplayName() const
{
  std::string ret = "";

  if (mpObjectParent)
    {
      ret = mpObjectParent->getObjectDisplayName();

      if (ret == "(CN)Root" ||
          ret == "ModelList[]" ||
          ret.substr(0, 7) == "(Model)")
        {
          ret = "";
        }
    }

  if (ret.length() >= 2)
    if ((ret.substr(ret.length() - 2) == "[]") && (!hasFlag(Reference)))
      {
        ret.insert(ret.length() - 1, getObjectName());

        if (hasFlag(NameVector) || hasFlag(Vector) || getObjectType() == "ParameterGroup")
          ret += "[]";

        return ret;
      }

  if ((ret.length() != 0) && (ret[ret.length() - 1] != '.'))
    ret += ".";

  if (hasFlag(NameVector) ||
      hasFlag(Vector) ||
      getObjectType() == "ParameterGroup")
    ret += getObjectName() + "[]";
  else if (hasFlag(Reference) ||
           getObjectType() == "Parameter" ||
           getObjectType() == getObjectName())
    ret += getObjectName();
  else
    ret += "(" + getObjectType() + ")" + getObjectName();

  return ret;
}

const std::string & CDataObject::getObjectName() const {return mObjectName;}

const std::string & CDataObject::getObjectType() const {return mObjectType;}

bool CDataObject::setObjectParent(const CDataContainer * pParent)
{
  if (pParent == mpObjectParent)
    return true;

  CCommonName OldCN;

  if (mpObjectParent != NULL &&
      pParent != NULL) // we only remove if we have a new parent otherwise we may have a memory leak.
    {
      if (CRegisteredCommonName::isEnabled())
        {
          OldCN = getCN();
        }

      mpObjectParent->remove(this);
    }

  removeReference(mpObjectParent);
  mpObjectParent = const_cast<CDataContainer *>(pParent);
  addReference(mpObjectParent);

  if (CRegisteredCommonName::isEnabled() &&
      !OldCN.empty())
    {
      CRegisteredCommonName::handle(OldCN, getCN());
    }

  return true;
}

CDataContainer * CDataObject::getObjectParent() const {return mpObjectParent;}

void CDataObject::addReference(const CDataContainer * pReference)
{
  if (pReference != NULL)
    {
      mReferences.insert(const_cast< CDataContainer * >(pReference));
    }
}

void CDataObject::removeReference(const CDataContainer * pReference)
{
  mReferences.erase(const_cast< CDataContainer * >(pReference));
}

CDataContainer *
CDataObject::getObjectAncestor(const std::string & type) const
{
  CDataContainer * p = getObjectParent();

  while (p)
    {
      if (p->getObjectType() == type) return p;

      p = p->getObjectParent();
    }

  return NULL;
}

const CObjectInterface::ObjectSet & CDataObject::getPrerequisites() const
{
  return mPrerequisits;
}

bool CDataObject::prerequisitsContains(const DataObjectSet & objects) const
{
  ObjectSet::const_iterator itPrerequisit = mPrerequisits.begin();
  ObjectSet::const_iterator endPrerequisit = mPrerequisits.end();
  DataObjectSet::const_iterator itObject = objects.begin();
  DataObjectSet::const_iterator endObject = objects.end();

  while (itPrerequisit != endPrerequisit && itObject != endObject)
    {
      if (*itPrerequisit < *itObject)
        ++itPrerequisit;
      else if (*itObject < *itPrerequisit)
        ++itObject;
      else
        return true;
    }

  return false;
}

bool CDataObject::isPrerequisiteForContext(const CObjectInterface * pObject,
    const CCore::SimulationContextFlag & /* context */,
    const CObjectInterface::ObjectSet & changedObjects) const
{
  // If the object is among the changed objects it does not depend on anything else.
  if (changedObjects.find(this) != changedObjects.end())
    return false;

#ifdef COPASI_DEBUG
  const CObjectInterface::ObjectSet & Prerequisites = getPrerequisites();

  // This method should only be called for objects which are prerequisites.
  // We check for this only in debug mode.
  assert(Prerequisites.find(pObject) != Prerequisites.end());
#endif // COPASI_DEBUG

  return true;
}

void * CDataObject::getValuePointer() const
{
  return NULL;
}

// virtual
const CDataObject * CDataObject::getDataObject() const
{
  return this;
}

const CDataObject * CDataObject::getValueObject() const
{
  return NULL;
}

// static
CDataObject * CDataObject::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CDataObject * pDataObject = new CDataObject(data.getProperty(CData::OBJECT_NAME).toString(),
      NO_PARENT,
      data.getProperty(CData::OBJECT_TYPE).toString(),
      CFlags< Flag >(data.getProperty(CData::OBJECT_FLAG).toString()));

  pDataObject->setUuid(data.getProperty(CData::OBJECT_NAME).toString());

  return pDataObject;
}

// virtual
void CDataObject::destruct()
{
  delete this;
}

// virtual
CData CDataObject::toData() const
{
  CData Data;

  Data.addProperty(CData::OBJECT_UUID, getUuid().str());
  Data.addProperty(CData::OBJECT_NAME, mObjectName);
  Data.addProperty(CData::OBJECT_TYPE, mObjectType);
  Data.addProperty(CData::OBJECT_FLAG, mObjectFlag.to_string());

  std::string CN = (mpObjectParent != NULL) ? mpObjectParent->getCN() : std::string("");
  size_t Index = (mpObjectParent != NULL) ? mpObjectParent->getIndex(this) : C_INVALID_INDEX;

  std::vector< CData > References;
  std::set< CDataContainer * >::iterator it = mReferences.begin();
  std::set< CDataContainer * >::iterator end = mReferences.end();

  for (; it != end; ++it)
    if (*it != mpObjectParent)
      {
        if (CN.empty())
          {
            CN = (*it)->getCN();
            Index = (*it)->getIndex(this);
          }
        else
          {
            CData ReferenceData;

            ReferenceData.addProperty(CData::OBJECT_REFERENCE_CN, (*it)->getCN());
            ReferenceData.addProperty(CData::OBJECT_REFERENCE_INDEX, (*it)->getIndex(this));

            References.push_back(ReferenceData);
          }
      }

  if (!References.empty())
    {
      Data.addProperty(CData::OBJECT_REFERENCES, References);
    }

  Data.addProperty(CData::OBJECT_PARENT_CN, CN);
  Data.addProperty(CData::OBJECT_INDEX, Index);

  return Data;
}

// virtual
bool CDataObject::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = true;

  if (data.isSetProperty(CData::OBJECT_NAME))
    {
      success &= setObjectName(data.getProperty(CData::OBJECT_NAME).toString());
    }

  if (data.isSetProperty(CData::OBJECT_UUID))
    {
      success &= setUuid(data.getProperty(CData::OBJECT_UUID).toString());
    }

  if (mpObjectParent != NULL &&
      data.isSetProperty(CData::OBJECT_INDEX))
    {
      mpObjectParent->updateIndex(data.getProperty(CData::OBJECT_INDEX).toSizeT(), this);
    }

  if (data.isSetProperty(CData::OBJECT_REFERENCES))
    {
      CDataModel * pDataModel = getObjectDataModel();
      assert(pDataModel != NULL);

      const std::vector< CData > & References = data.getProperty(CData::OBJECT_REFERENCES).toDataVector();

      std::vector< CData >::const_iterator it = References.begin();
      std::vector< CData >::const_iterator end = References.end();

      CData Data;
      Data.addProperty(CData::OBJECT_POINTER, this);

      for (; it != end; ++it)
        {
          CDataContainer * pReference = dynamic_cast< CDataContainer * >(const_cast< CObjectInterface * >(pDataModel->getObject(it->getProperty(CData::OBJECT_REFERENCE_CN).toString())));

          if (pReference != NULL)
            {
              Data.addProperty(CData::OBJECT_REFERENCE_INDEX, it->getProperty(CData::OBJECT_REFERENCE_INDEX));
              pReference->insert(Data);
            }
        }
    }

  return success;
}

// virtual
void CDataObject::createUndoData(CUndoData & undoData, const CUndoData::Type & type, const CData & oldData, const CCore::Framework & framework) const
{
  if (type != CUndoData::Type::CHANGE)
    {
      undoData = CUndoData(type, this);
      return;
    }

  undoData.addProperty(CData::OBJECT_NAME, oldData.getProperty(CData::OBJECT_NAME), mObjectName);
  // The UUID of an object must never be changed.
  // undoData.addProperty(CData::OBJECT_UUID, oldData.getProperty(CData::OBJECT_UUID), getUuid().str());
  undoData.addProperty(CData::OBJECT_TYPE, oldData.getProperty(CData::OBJECT_TYPE), mObjectType);
  undoData.addProperty(CData::OBJECT_PARENT_CN, oldData.getProperty(CData::OBJECT_PARENT_CN), (mpObjectParent != NULL) ? mpObjectParent->getCN() : std::string(""));
  undoData.addProperty(CData::OBJECT_FLAG, oldData.getProperty(CData::OBJECT_FLAG), mObjectFlag.to_string());
  undoData.addProperty(CData::OBJECT_INDEX, oldData.getProperty(CData::OBJECT_INDEX), (mpObjectParent != NULL) ? mpObjectParent->getIndex(this) : C_INVALID_INDEX);

  std::vector< CData > References;
  std::set< CDataContainer * >::iterator it = mReferences.begin();
  std::set< CDataContainer * >::iterator end = mReferences.end();

  for (; it != end; ++it)
    if (*it != mpObjectParent)
      {
        CData ReferenceData;

        ReferenceData.addProperty(CData::OBJECT_REFERENCE_CN, (*it)->getCN());
        ReferenceData.addProperty(CData::OBJECT_REFERENCE_INDEX, (*it)->getIndex(this));

        References.push_back(ReferenceData);
      }

  if (!References.empty())
    {
      undoData.addProperty(CData::OBJECT_REFERENCES, oldData.getProperty(CData::OBJECT_REFERENCES), References);
    }

  return;
}

bool CDataObject::hasFlag(const Flag & flag) const
{
  return mObjectFlag.isSet(flag);
}

const std::string & CDataObject::getKey() const
{
  static std::string DefaultKey("");

  return DefaultKey;
}

// virtual
const std::string CDataObject::getUnits() const
{
  if (mpObjectParent != NULL)
    return mpObjectParent->getChildObjectUnits(this);

  return "?";
}

std::ostream &operator<<(std::ostream &os, const CDataObject & o)
{
  os << "Name:      " << o.getObjectDisplayName() << std::endl;
  os << "Type:      " << o.getObjectType() << std::endl;
  os << "Container: " << o.hasFlag(CDataObject::Container) << std::endl;
  os << "Vector:    " << o.hasFlag(CDataObject::Vector) << std::endl;
  os << "VectorN:   " << o.hasFlag(CDataObject::NameVector) << std::endl;
  os << "Matrix:    " << o.hasFlag(CDataObject::Matrix) << std::endl;
  os << "Reference: " << o.hasFlag(CDataObject::Reference) << std::endl;
  os << "Bool:      " << o.hasFlag(CDataObject::ValueBool) << std::endl;
  os << "Int:       " << o.hasFlag(CDataObject::ValueInt) << std::endl;
  os << "Dbl:       " << o.hasFlag(CDataObject::ValueDbl) << std::endl;

  return os;
}

/**
 * Returns a pointer to the CDataModel the element belongs to.
 * If there is no instance of CDataModel in the ancestor tree, NULL
 * is returned.
 */
CDataModel * CDataObject::getObjectDataModel() const
{
  const CDataObject * pObject = this;

  while (pObject != NULL)
    {
      if (pObject->hasFlag(DataModel))
        return const_cast< CDataModel * >(static_cast<const CDataModel * >(pObject));

      pObject = pObject->getObjectParent();
    }

  return NULL;
}

const CValidity & CDataObject::getValidity() const
{
  return mAggregateValidity;
}

// virtual
void CDataObject::validityChanged(const CValidity & changedValidity)
{
  bool ValidityRefreshNeeded = false;

  if (changedValidity.empty())
    {
      ValidityRefreshNeeded = (mReferencedValidities.erase(&changedValidity) > 0);
    }
  else
    {
      mReferencedValidities.insert(& changedValidity);
      ValidityRefreshNeeded = true;
    }

  if (ValidityRefreshNeeded)
    {
      refreshAggregateValidity();
    }
}

void CDataObject::validityRemoved(const CValidity & changedValidity)
{
  bool ValidityRefreshNeeded = (mReferencedValidities.erase(&changedValidity) > 0);

  if (ValidityRefreshNeeded)
    {
      refreshAggregateValidity();
    }
}

void CDataObject::addIssue(const CIssue & issue)
{
  mValidity.add(issue);
}

void CDataObject::removeIssue(const CIssue & issue)
{
  mValidity.remove(issue);
}

void CDataObject::refreshAggregateValidity()
{
  mAggregateValidity.clear();
  std::set< const CValidity * >::const_iterator it = mReferencedValidities.begin();
  std::set< const CValidity * >::const_iterator end = mReferencedValidities.end();

  for (; it != end; ++it)
    {
      mAggregateValidity |= **it;
    }

  std::set< CDataContainer * >::iterator itReference = mReferences.begin();
  std::set< CDataContainer * >::iterator endReference = mReferences.end();

  for (; itReference != endReference; ++itReference)
    {
      (*itReference)->validityChanged(mAggregateValidity);
    }
}

void CDataObject::calculateValue()
{}
