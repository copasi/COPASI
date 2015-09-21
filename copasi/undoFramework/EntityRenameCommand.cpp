// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "EntityRenameCommand.h"

#include <copasi/UI/CQTabWidget.h>

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CCompartment.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CEvent.h>
#include <copasi/model/CModelValue.h>

EntityRenameCommand::EntityRenameCommand(CCopasiObject *pObject,
    const std::string &oldName,
    const std::string &newName,
    CQTabWidget* pWidget)
  : CCopasiUndoCommand("", INVALID_TYPE, "Change", "Name", newName, oldName, pObject->getObjectName())
  , mpObject(pObject)
  , mpTabWidget(pWidget)
  , mKey(pObject->getKey())
{
  if (dynamic_cast<CModel*>(pObject))
    {
      setEntityType("Model");
      //setType(Type::);
      setText(": Renamed model");
    }
  else if (dynamic_cast<CMetab*>(pObject))
    {
      setEntityType("Species");
      setType(SPECIES_DATA_CHANGE);
      setText(": Renamed species");
    }
  else if (dynamic_cast<CCompartment*>(pObject))
    {
      setEntityType("Compartment");
      setType(COMPARTMENT_DATA_CHANGE);
      setText(": Renamed compartment");
    }
  else if (dynamic_cast<CReaction*>(pObject))
    {
      setEntityType("Reaction");
      setType(REACTION_DATA_CHANGE);
      setText(": Renamed reaction");
    }
  else if (dynamic_cast<CEvent*>(pObject))
    {
      setEntityType("Event");
      setType(EVENT_DATA_CHANGE);
      setText(": Renamed event");
    }
  else if (dynamic_cast<CModelValue*>(pObject))
    {
      setEntityType("Global Quantity");
      setType(GLOBALQUANTITY_DATA_CHANGE);
      setText(": Renamed global quantity");
    }
}

void EntityRenameCommand::redo()
{
  mpTabWidget->renameEntity(mKey, mNewValue);
}

void EntityRenameCommand::undo()
{
  mpTabWidget->renameEntity(mKey, mOldValue);
}
