// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/undo/CUndoObjectInterface.h"
#include "copasi/core/CDataObject.h"
#include "copasi/model/CModelParameter.h"

// Uncomment the line below to enable debug output
// #define DEBUG_UUID
CUndoObjectInterface::CUndoObjectInterface()
  : mpUuid(NULL)
  , mUuidLocked(false)
{}

CUndoObjectInterface::CUndoObjectInterface(const CUndoObjectInterface & src)
  : mpUuid(src.mpUuid != NULL ? new xg::Guid(*src.mpUuid) : NULL)
  , mUuidLocked(false)
{
#ifdef DEBUG_UUID

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

#endif // DEBUG_UUID
}

// virtual
CUndoObjectInterface::~CUndoObjectInterface()
{
  if (mpUuid != NULL)
    delete mpUuid;
}

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
#ifdef DEBUG_UUID
      std::cout << "Unlocked UUID: " << *mpUuid;

      if (dynamic_cast< const CDataObject *>(this))
        {
          std::cout << " for CDataObject: " << dynamic_cast< const CDataObject *>(this)->getCN() << std::endl;
        }
      else if (dynamic_cast< const CModelParameter *>(this))
        {
          std::cout << " for CModelParameter: " << dynamic_cast< const CModelParameter *>(this)->getCN() << std::endl;
        }

#endif // DEBUG_UUID
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
