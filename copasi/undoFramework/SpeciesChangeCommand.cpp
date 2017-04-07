// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi.h"
#include "UI/qtUtilities.h"

#include <copasi/undoFramework/SpeciesChangeCommand.h>

#include <copasi/UI/CQSpeciesDetail.h>

SpeciesChangeCommand::SpeciesChangeCommand(CCopasiUndoCommand::Type type,
    const QVariant & oldValue,
    const QVariant & newValue,
    CCopasiObject * pObject,
    CQSpeciesDetail * pWidget,
    double iValue)
  : CCopasiUndoCommand("Species", type, "Change", "", TO_UTF8(newValue.toString()), TO_UTF8(oldValue.toString()), pObject->getObjectName())
  , mOld(oldValue)
  , mNew(newValue)
  , mKey(pObject->getKey())
  , mpWidget(pWidget)
  , mIValue(iValue)
{
  switch (type)
    {
      case SPECIES_COMPARTMENT_CHANGE:
        setProperty("Compartment");
        setText(": Changed species compartment");
        break;

      case SPECIES_EXPRESSION_CHANGE:
        setProperty("Expression");
        setText(": Changed species expression");
        break;

      case SPECIES_INITIAL_EXPRESSION_CHANGE:
        setProperty("Initial Expression");
        setText(": Changed species initial expression");
        break;

      case SPECIES_INITAL_PARTICLENUMBER_CHANGE:
        setProperty("Initial Value");
        setText(": Changed species initial particle number");
        break;

      case SPECIES_INITAL_CONCENTRATION_CHANGE:
        setProperty("Initial Value");
        setText(": Changed species initial concentration");
        break;

      case SPECIES_SIMULATION_TYPE_CHANGE:
        setProperty("Simulation Type");
        setText(": Changed species simulation type");
        break;

      case SPECIES_ADD_NOISE_CHANGE:
        setText(": Changed adding noise");
        setProperty("Function");
        break;

      case SPECIES_NOISE_EXPRESSION_CHANGE:
        setText(": Changed noise expression");
        setProperty("Function");
        break;

      default:
        break;
    }
}

SpeciesChangeCommand::~SpeciesChangeCommand()
{
}

void SpeciesChangeCommand::undo()
{
  mpWidget->changeValue(mKey, mType, mOld, mIValue);
}

void SpeciesChangeCommand::redo()
{
  mpWidget->changeValue(mKey, mType, mNew, mIValue);
}
