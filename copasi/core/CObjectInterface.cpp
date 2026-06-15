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
