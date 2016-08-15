// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "ModelChangeCommand.h"

#include <copasi/UI/CQModelWidget.h>

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CCompartment.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CEvent.h>
#include <copasi/model/CModelValue.h>

#include <copasi/UI/qtUtilities.h>

ModelChangeCommand::ModelChangeCommand(CCopasiUndoCommand::Type type,
                                       const QVariant& oldValue,
                                       const QVariant& newValue,
                                       CQModelWidget* pWidget)
  : CCopasiUndoCommand("Model", type, "Change", "", TO_UTF8(newValue.toString()), TO_UTF8(oldValue.toString()))
  , mOld(oldValue)
  , mNew(newValue)
  , mpWidget(pWidget)
{
  switch (type)
    {
      case MODEL_INITIAL_TIME_CHANGE:
        setProperty("Initial Time");
        setText(": Changed model initial time");
        break;

      case MODEL_TIME_UNIT_CHANGE:
        setProperty("Time Unit");
        setText(": Changed model time unit");
        break;

      case MODEL_QUANTITY_UNIT_CHANGE:
        setProperty("Quantity Unit");
        setText(": Changed model quantity unit");
        break;

      case MODEL_LENGTH_UNIT_CHANGE:
        setProperty("Length Unit");
        setText(": Changed model length unit");
        break;

      case MODEL_AREA_UNIT_CHANGE:
        setProperty("Area Unit");
        setText(": Changed model area unit");
        break;

      case MODEL_VOLUME_UNIT_CHANGE:
        setProperty("Volume Unit");
        setText(": Changed model volume unit");
        break;

      case MODEL_AVOGADRO_NUMBER_CHANGE:
        setProperty("Avogadro's #");
        setText(": Changed Avogadro's #");
        break;

      case MODEL_STOCHASTIC_CORRECTION_CHANGE:
        setProperty("Stochastic Correction");
        setText(": Changed model stochastic correction");
        break;

      default:
        break;
    }
}

ModelChangeCommand::~ModelChangeCommand()
{
}

void ModelChangeCommand::redo()
{
  mpWidget->changeValue(mType, mNew);
}

void ModelChangeCommand::undo()
{
  mpWidget->changeValue(mType, mOld);
}
