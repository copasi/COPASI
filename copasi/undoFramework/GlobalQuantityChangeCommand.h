// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_GLOBAL_QUANTITY_CHANGE_COMMAND_H
#define COPASI_GLOBAL_QUANTITY_CHANGE_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

#include <limits>

class CQModelValue;
class CCopasiObject;

class GlobalQuantityChangeCommand : public CCopasiUndoCommand
{

public:
  GlobalQuantityChangeCommand(CCopasiUndoCommand::Type type,
                              const QVariant& oldValue,
                              const QVariant& newValue,
                              CCopasiObject* pObject,
                              CQModelValue* pWidget,
                              double iValue = std::numeric_limits<double>::quiet_NaN());
  ~GlobalQuantityChangeCommand();

  virtual void undo();
  virtual void redo();

protected:
  QVariant mOld, mNew;
  std::string mKey;
  double mIValue;
  CCopasiObject* mpObject;
  CQModelValue* mpWidget;
};

#endif // COPASI_GLOBAL_QUANTITY_CHANGE_COMMAND_H
