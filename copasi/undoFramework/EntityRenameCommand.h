// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_ENTITY_RENAME_COMMAND_H
#define COPASI_ENTITY_RENAME_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

class CCopasiObject;
class CQTabWidget;

class EntityRenameCommand : public CCopasiUndoCommand
{
public:
  EntityRenameCommand(CCopasiObject *pObject,
                      const std::string& oldName,
                      const std::string& newName,
                      CQTabWidget* pTabWidget);

  virtual void undo();
  virtual void redo();

protected:
  CCopasiObject *mpObject;
  CQTabWidget* mpTabWidget;
  std::string mKey;
};

#endif // COPASI_ENTITY_RENAME_COMMAND_H
