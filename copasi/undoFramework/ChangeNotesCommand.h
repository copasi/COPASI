// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_NOTES_COMMAND_H
#define COPASI_NOTES_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

class CDataObject;
class CQNotes;

class ChangeNotesCommand : public CCopasiUndoCommand
{
public:
  ChangeNotesCommand(CDataObject *pObject,
                     const std::string& oldName,
                     const std::string& newName,
                     CQNotes* pWidget);

  virtual void undo();
  virtual void redo();

protected:
  CDataObject *mpObject;
  CQNotes* mpWidget;
};

#endif // COPASI_NOTES_COMMAND_H
