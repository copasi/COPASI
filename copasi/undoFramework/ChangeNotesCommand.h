// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_NOTES_COMMAND_H
#define COPASI_NOTES_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

class CCopasiObject;
class CQNotes;

class ChangeNotesCommand : public CCopasiUndoCommand
{
public:
  ChangeNotesCommand(CCopasiObject *pObject,
                     const std::string& oldName,
                     const std::string& newName,
                     CQNotes* pWidget);

  virtual void undo();
  virtual void redo();

protected:
  CCopasiObject *mpObject;
  CQNotes* mpWidget;
  std::string mKey;
};


#endif // COPASI_NOTES_COMMAND_H
