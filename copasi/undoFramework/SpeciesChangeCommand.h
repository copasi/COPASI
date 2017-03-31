// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_SPECIES_CHANGE_COMMAND_H
#define COPASI_SPECIES_CHANGE_COMMAND_H

#include <copasi/undoFramework/CCopasiUndoCommand.h>

#include <limits>

class CQSpeciesDetail;
class CCopasiObject;

class SpeciesChangeCommand : public CCopasiUndoCommand
{

public:
  SpeciesChangeCommand(CCopasiUndoCommand::Type type,
                       const QVariant& oldValue,
                       const QVariant& newValue,
                       CCopasiObject* pObject,
                       CQSpeciesDetail* pWidget,
                       double iValue = std::numeric_limits<double>::quiet_NaN());
  ~SpeciesChangeCommand();

  virtual void undo();
  virtual void redo();

protected:
  QVariant mOld, mNew;
  std::string mKey;
  double mIValue;
  CCopasiObject* mpObject;
  CQSpeciesDetail* mpWidget;
};

#endif // COPASI_GLOBAL_QUANTITY_CHANGE_COMMAND_H
