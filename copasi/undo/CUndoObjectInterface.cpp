// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/undo/CUndoObjectInterface.h"
#include "copasi/core/CDataObject.h"
#include "copasi/model/CModelParameter.h"

CUndoObjectInterface::CUndoObjectInterface()
  : mpUuid(NULL)
  , mUuidLocked(false)
{}

CUndoObjectInterface::CUndoObjectInterface(const CUndoObjectInterface & src)
  : mpUuid(src.mpUuid != NULL ? new xg::Guid(*src.mpUuid) : NULL)
  , mUuidLocked(false)
{
#ifdef COPASI_DEBUG_TRACE

  if (mpUuid != NULL)
    {
      std::cout << "Copied UUID: " << *mpUuid;

      if (dynamic_cast< const CDataObject *>(this))
        {
          std::cout << " for CDataObject: " << dynamic_cast< const CDataObject *>(this)->getCN();
        }
      else if (dynamic_cast< const CModelParameter *>(this))
        {
          std::cout << " for CModelParameter: " << dynamic_cast< const CModelParameter *>(this)->getCN();
        }

      std::cout << std::endl;
    }

#endif // COPASI_DEBUG_TRACE
}

// virtual
CUndoObjectInterface::~CUndoObjectInterface()
{}

// virtual
CUndoObjectInterface * CUndoObjectInterface::insert(const CData & data)
{
  return NULL;
}

// virtual
void CUndoObjectInterface::updateIndex(const size_t & index, const CUndoObjectInterface * pUndoObject)
{}

const xg::Guid & CUndoObjectInterface::getUuid() const
{
  if (mpUuid == NULL)
    {
      const_cast< CUndoObjectInterface * >(this)->generateUuid();
    }
  else if (!mUuidLocked)
    {
#ifdef COPASI_DEBUG_TRACE
      std::cout << "Unlocked UUID: " << *mpUuid;

      if (dynamic_cast< const CDataObject *>(this))
        {
          std::cout << " for CDataObject: " << dynamic_cast< const CDataObject *>(this)->getCN() << std::endl;
        }
      else if (dynamic_cast< const CModelParameter *>(this))
        {
          std::cout << " for CModelParameter: " << dynamic_cast< const CModelParameter *>(this)->getCN() << std::endl;
        }

#endif // COPASI_DEBUG_TRACE
    }

  return *mpUuid;
}

bool CUndoObjectInterface::setUuid(const xg::Guid & uuid)
{
  if (!uuid.isValid())
    {
      return false;
    }

  if (mUuidLocked &&
      mpUuid != NULL &&
      mpUuid->isValid())
    {
      return false;
    }

  if (mpUuid == NULL)
    {
      mpUuid = new xg::Guid();
    }

  *mpUuid = uuid;
  mUuidLocked = mpUuid->isValid();

  return true;
}

bool CUndoObjectInterface::setUuid(const std::string & uuid)
{
  xg::Guid UUID(uuid);

  if (!UUID.isValid())
    {
      return false;
    }

  return setUuid(UUID);
}

bool CUndoObjectInterface::generateUuid()
{
  if (mUuidLocked &&
      mpUuid != NULL &&
      mpUuid->isValid())
    {
      return false;
    }

  if (mpUuid == NULL)
    {
      mpUuid = new xg::Guid();
    }

  *mpUuid = xg::newGuid();
  mUuidLocked = mpUuid->isValid();

  return true;
}
