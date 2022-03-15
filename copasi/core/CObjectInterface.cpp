// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

      if ((pos = objName.find(ContainerName)) == std::string::npos)
        continue;

      if (pos + ContainerName.length() == objName.length())
        pObject = *it;
      else
        pObject = (*it)->getObject(CCommonName(objName.substr(pos)).getRemainder());
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

CObjectInterface::CObjectInterface():
  mValidity(this)
{}

CObjectInterface::CObjectInterface(const CObjectInterface & src):
  mValidity(src.mValidity, this)
{}

// virtual
CObjectInterface::~CObjectInterface()
{};
