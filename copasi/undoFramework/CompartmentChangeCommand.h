// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_COMPARTMENT_CHANGE_COMMAND_H
#define COPASI_COMPARTMENT_CHANGE_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

#include <limits>

class CQCompartment;
class CDataObject;
class UndoCompartmentData;

class CompartmentChangeCommand : public CCopasiUndoCommand
{

public:
  CompartmentChangeCommand(CCopasiUndoCommand::Type type,
                           const QVariant& oldValue,
                           const QVariant& newValue,
                           CDataObject* pObject,
                           CQCompartment* pWidget,
                           double iValue = std::numeric_limits<double>::quiet_NaN());

  ~CompartmentChangeCommand();

  virtual void undo();
  virtual void redo();

protected:
  QVariant mOld, mNew;
  double mIValue;
  CDataObject* mpObject;
  CQCompartment* mpWidget;
  UndoCompartmentData* mpUndoData;
};

#endif // COPASI_COMPARTMENT_CHANGE_COMMAND_H
