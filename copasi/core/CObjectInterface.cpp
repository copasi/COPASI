// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "CObjectInterface.h"

#include "CDataContainer.h"
#include "CRootContainer.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CFunction.h"

// static
const CDataObject * CObjectInterface::DataObject(const CObjectInterface * pInterface)
{
  if (pInterface != NULL)
    {
      return pInterface->getDataObject();
    }

  return NULL;
}

// static
CObjectInterface * CObjectInterface::GetObjectFromCN(const CObjectInterface::ContainerList & listOfContainer,
    const CCommonName & objName)
{
  return CRegisteredCommonName::GetObjectFromCN(listOfContainer, objName);
}

// static
CObjectInterface * CObjectInterface::__GetObjectFromCN(const CObjectInterface::ContainerList & listOfContainer,
    const CCommonName & objName)
{
  CCommonName Primary = objName.getPrimary();
  std::string Type = Primary.getObjectType();

  // Check that we have a fully qualified CN
  // Note, CN=Root may point to the root container or a data model;

  if (objName.getPrimary() != "CN=Root" &&
      Type != "Separator" &&
      Type != "String")
    {
      return NULL;
    }

  const CObjectInterface * pObject = NULL;

  const CDataModel * pDataModel = NULL;

  CObjectInterface::ContainerList::const_iterator it = listOfContainer.begin();

  CObjectInterface::ContainerList::const_iterator end = listOfContainer.end();

  CCommonName ContainerName;

  std::string::size_type pos;

  bool CheckDataModel = true;

  //favor to search the list of container first
  for (; it != end && pObject == NULL; ++it)
    {
      if (*it == NULL)
        {
          continue;
        }

      if (pDataModel == NULL)
        {
          pDataModel = (*it)->getObjectDataModel();
        }

      CheckDataModel &= (pDataModel != *it);

      ContainerName = (*it)->getCN();

      while (ContainerName.getRemainder() != "")
        {
          ContainerName = ContainerName.getRemainder();
        }

      if ((pos = std::string(objName).find(ContainerName)) == std::string::npos)
        continue;

      if (pos + std::string(ContainerName).length() == std::string(objName).length())
        pObject = *it;
      else
        pObject = (*it)->getObject(CCommonName(std::string(objName).substr(pos)).getRemainder());
    }

  // if not found check the data model if we have one and have not yet done so
  if (pObject == NULL &&
      pDataModel != NULL &&
      CheckDataModel)
    {
      pObject = pDataModel->getObject(objName);
    }

  // if still not found search the root container
  if (pObject == NULL)
    {
      pObject = CRootContainer::getRoot()->getObject(objName);
    }

  return const_cast< CObjectInterface * >(pObject);
}

CObjectInterface::CObjectInterface()
  : mValidity(this)
{}

// virtual
CObjectInterface::~CObjectInterface()
{}

// virtual final
const CObjectInterface * CObjectInterface::getChildObject(const CCommonNameComponent::shared_ptr & pCN) const
{
  return resolve(pCN);
}

// virtual final
const CObjectInterface * CObjectInterface::getObject(const CCommonName & cn) const
{
  return cn.resolve(DataObject(this));
}

// virtual
const CCommonNameComponent::shared_ptr & CObjectInterface::getCNComponent() const
{
  static const CCommonNameComponent::shared_ptr empty;
  return empty;
}

// virtual final
CCommonName CObjectInterface::getCN() const
{
  return getCNComponent();
}

bool CObjectInterface::appendPrerequisites(CObjectInterface::ObjectSet & prerequisites) const
{
  bool appended = false;

  ObjectSet::const_iterator it = getPrerequisites().begin();
  ObjectSet::const_iterator end = getPrerequisites().end();

  for (; it != end; ++it)
    {
      if (prerequisites.insert(*it).second)
        {
          appended = true;
          (*it)->appendPrerequisites(prerequisites);
        }
    }

  return appended;
}
