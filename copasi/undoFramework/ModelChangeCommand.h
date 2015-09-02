// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_MODEL_UNIT_CHANGE_COMMAND_H
#define COPASI_MODEL_UNIT_CHANGE_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

class CCopasiObject;
class CQModelWidget;

class ModelChangeCommand : public CCopasiUndoCommand
{

public:
  ModelChangeCommand(CCopasiUndoCommand::Type type,
                     const QVariant& oldValue,
                     const QVariant& newValue,
                     CQModelWidget* pWidget);

  virtual void undo();
  virtual void redo();

protected:
  QVariant mOld, mNew;
  CQModelWidget* mpWidget;
};

#endif // COPASI_MODEL_UNIT_CHANGE_COMMAND_H
