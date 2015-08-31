// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_COMPARTMENT_CHANGE_COMMAND_H
#define COPASI_COMPARTMENT_CHANGE_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

#include <limits>

class CQCompartment;
class CCopasiObject;

class CompartmentChangeCommand : public CCopasiUndoCommand
{

public:
  CompartmentChangeCommand(CCopasiUndoCommand::Type type,
                           const QVariant& oldValue,
                           const QVariant& newValue,
                           CCopasiObject* pObject,
                           CQCompartment* pWidget,
                           double iValue = std::numeric_limits<double>::quiet_NaN());

  virtual void undo();
  virtual void redo();

protected:
  QVariant mOld, mNew;
  std::string mKey;
  double mIValue;
  CCopasiObject* mpObject;
  CQCompartment* mpWidget;
};


#endif // COPASI_COMPARTMENT_CHANGE_COMMAND_H
