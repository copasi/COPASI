// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_EVENT_CHANGE_COMMAND_H
#define COPASI_EVENT_CHANGE_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

#include <limits>

class CQEventWidget1;
class CDataObject;

class EventChangeCommand : public CCopasiUndoCommand
{

public:
  EventChangeCommand(CCopasiUndoCommand::Type type,
                     const QVariant& oldValue,
                     const QVariant& newValue,
                     CDataObject* pObject,
                     CQEventWidget1* pWidget,
                     const std::string& oldExpression = "",
                     const std::string& newExpression = ""
                    );
  ~EventChangeCommand();

  virtual void undo();
  virtual void redo();

protected:
  QVariant mOld, mNew;
  std::string mKey;
  double mIValue;
  CDataObject* mpObject;
  CQEventWidget1* mpWidget;

  std::string mOldExpression;
  std::string mNewExpression;
};

#endif // COPASI_EVENT_CHANGE_COMMAND_H
