// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "EntityRenameCommand.h"

#include <copasi/UI/CQTabWidget.h>

#include "copasi.h"

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CCompartment.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CEvent.h>
#include <copasi/model/CModelValue.h>
#include <copasi/CopasiDataModel/CCopasiDataModel.h>

EntityRenameCommand::EntityRenameCommand(CCopasiObject *pObject,
    const std::string &oldName,
    const std::string &newName,
    CQTabWidget* pWidget)
  : CCopasiUndoCommand("", INVALID_TYPE, "Change", "Name", newName, oldName, pObject->getObjectName())
  , mpObject(pObject)
  , mpTabWidget(pWidget)
  , mKey(pObject->getKey())
  , mName(pObject->getCN())
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

EntityRenameCommand::~EntityRenameCommand()
{
}

void EntityRenameCommand::redo()
{
  if (mpTabWidget->getDataModel() != NULL)
    {
      const CCopasiObject* pObject =
        dynamic_cast<const CCopasiObject*>(mpTabWidget->getDataModel()->getObject(mName));

      if (pObject != NULL)
        mpTabWidget->renameEntity(pObject->getKey(), mNewValue);
    }

  mpTabWidget->renameEntity(mKey, mNewValue);
}

void EntityRenameCommand::undo()
{
  if (mpTabWidget->getDataModel() != NULL)
    {
      const CCopasiObject* pObject =
        dynamic_cast<const CCopasiObject*>(mpTabWidget->getDataModel()->getObject(mName));

      if (pObject != NULL)
        mpTabWidget->renameEntity(pObject->getKey(), mOldValue);
    }

  mpTabWidget->renameEntity(mKey, mOldValue);
}
