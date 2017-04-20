// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "ChangeNotesCommand.h"

#include <copasi/UI/CQNotes.h>

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CCompartment.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CEvent.h>
#include <copasi/model/CModelValue.h>

ChangeNotesCommand::ChangeNotesCommand(CDataObject *pObject,
                                       const std::string &oldName,
                                       const std::string &newName,
                                       CQNotes* pWidget)
  : CCopasiUndoCommand("", INVALID_TYPE, "Change", "Notes", newName, oldName, pObject->getObjectName())
  , mpObject(pObject)
  , mpWidget(pWidget)
{
  mKey = pObject->getKey();

  if (dynamic_cast<CModel*>(pObject))
    {
      setEntityType("Model");
      //setType(Type::);
      setText(": Changed model notes");
    }
  else if (dynamic_cast<CMetab*>(pObject))
    {
      setEntityType("Species");
      setType(SPECIES_DATA_CHANGE);
      setText(": Changed species notes");
    }
  else if (dynamic_cast<CCompartment*>(pObject))
    {
      setEntityType("Compartment");
      setType(COMPARTMENT_DATA_CHANGE);
      setText(": Changed compartment notes");
    }
  else if (dynamic_cast<CReaction*>(pObject))
    {
      setEntityType("Reaction");
      setType(REACTION_DATA_CHANGE);
      setText(": Changed reaction notes");
    }
  else if (dynamic_cast<CEvent*>(pObject))
    {
      setEntityType("Event");
      setType(EVENT_DATA_CHANGE);
      setText(": Changed event notes");
    }
  else if (dynamic_cast<CModelValue*>(pObject))
    {
      setEntityType("Global Quantity");
      setType(GLOBALQUANTITY_DATA_CHANGE);
      setText(": Changed global quantity notes");
    }
}

void ChangeNotesCommand::redo()
{
  mpWidget->changeNotes(mKey, mNewValue);
}

void ChangeNotesCommand::undo()
{
  mpWidget->changeNotes(mKey, mOldValue);
}
