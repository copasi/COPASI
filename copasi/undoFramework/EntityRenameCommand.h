// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
  virtual ~EntityRenameCommand();

  virtual void undo();
  virtual void redo();

protected:
  CCopasiObject *mpObject;
  CQTabWidget* mpTabWidget;
  std::string mKey;
  CRegisteredObjectName mName;
};

#endif // COPASI_ENTITY_RENAME_COMMAND_H
