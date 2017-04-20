// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_GLOBAL_QUANTITY_CHANGE_COMMAND_H
#define COPASI_GLOBAL_QUANTITY_CHANGE_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

#include <limits>

class CQModelValue;
class CDataObject;

class GlobalQuantityChangeCommand : public CCopasiUndoCommand
{

public:
  GlobalQuantityChangeCommand(CCopasiUndoCommand::Type type,
                              const QVariant& oldValue,
                              const QVariant& newValue,
                              CDataObject* pObject,
                              CQModelValue* pWidget,
                              double iValue = std::numeric_limits<double>::quiet_NaN());
  ~GlobalQuantityChangeCommand();

  virtual void undo();
  virtual void redo();

protected:
  QVariant mOld, mNew;
  std::string mKey;
  double mIValue;
  CDataObject* mpObject;
  CQModelValue* mpWidget;
};

#endif // COPASI_GLOBAL_QUANTITY_CHANGE_COMMAND_H
