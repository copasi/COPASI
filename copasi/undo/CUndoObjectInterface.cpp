// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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
  : mUuidLocked(false)
#ifdef COPASI_USE_CROSSGUID
  , mpUuid(NULL)
#else
  , mUuid()
#endif
{}

CUndoObjectInterface::CUndoObjectInterface(const CUndoObjectInterface & src)
  : mUuidLocked(false)
#ifdef COPASI_USE_CROSSGUID
  , mpUuid(src.mpUuid != NULL ? new xg::Guid(*src.mpUuid) : NULL)
#else
  , mUuid(src.mUuid)
#endif
{
#ifdef COPASI_USE_CROSSGUID
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
#endif
}

// virtual
CUndoObjectInterface::~CUndoObjectInterface()
{
#ifdef COPASI_USE_CROSSGUID
  if (mpUuid != NULL)
    delete mpUuid;
#endif
}

// virtual
CUndoObjectInterface * CUndoObjectInterface::insert(const CData & data)
{
  return NULL;
}

// virtual
void CUndoObjectInterface::updateIndex(const size_t & index, const CUndoObjectInterface * pUndoObject)
{}

std::string CUndoObjectInterface::getUuidString() const
{
#ifdef COPASI_USE_CROSSGUID
  return getUuid().str();
#else
  return uuids::to_string(getUuid());
#endif
}
#ifdef COPASI_USE_CROSSGUID

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
#else
const uuids::uuid & CUndoObjectInterface::getUuid() const
{
  if (mUuid.is_nil())
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

  return mUuid;
}

bool CUndoObjectInterface::setUuid(const uuids::uuid & uuid)
{
  if (uuid.is_nil())
    {
      return false;
    }

  if (mUuidLocked &&
      !mUuid.is_nil())
    {
      return false;
    }

  mUuid = uuid;
  mUuidLocked = !mUuid.is_nil();

  return true;
}
#endif
bool CUndoObjectInterface::setUuid(const std::string & uuid)
{
#ifdef COPASI_USE_CROSSGUID

  xg::Guid UUID(uuid);

  if (!UUID.isValid())
    {
      return false;
    }

  return setUuid(UUID);
#else
  auto UUID = uuids::uuid::from_string(uuid);
  // stduuid only constructs from valid strings
  if (!UUID.has_value())
    return false;

  return setUuid(*UUID);

#endif
}

bool CUndoObjectInterface::generateUuid()
{
#ifdef COPASI_USE_CROSSGUID

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
#else
  if (mUuidLocked &&
      !mUuid.is_nil())
    {
      return false;
    }
  static std::random_device rd;
  static std::mt19937 gen{rd()};
  static uuids::uuid_random_generator uuid_generator(gen);
  mUuid = uuid_generator();
  mUuidLocked = !mUuid.is_nil();
  return true;

#endif
}
