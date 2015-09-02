// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CompartmentChangeCommand.h"

#include <copasi/UI/CQCompartment.h>

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CCompartment.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CEvent.h>
#include <copasi/model/CModelValue.h>

#include <copasi/UI/qtUtilities.h>

CompartmentChangeCommand::CompartmentChangeCommand(CCopasiUndoCommand::Type type,
    const QVariant& oldValue,
    const QVariant& newValue,
    CCopasiObject* pObject,
    CQCompartment* pWidget,
    double iValue /*= std::numeric_limits<double>::quiet_NaN()*/)
  : CCopasiUndoCommand("Compartment", type, "Change", "", TO_UTF8(newValue.toString()), TO_UTF8(oldValue.toString()), pObject->getObjectName())
  , mOld(oldValue)
  , mNew(newValue)
  , mKey(pObject->getKey())
  , mpWidget(pWidget)
  , mIValue(iValue)
{
  switch (type)
    {
      case COMPARTMENT_EXPRESSION_CHANGE:
        setProperty("Expression");
        setText(": Changed compartment expression");
        break;

      case COMPARTMENT_INITIAL_EXPRESSION_CHANGE:
        setProperty("Initial Expression");
        setText(": Changed compartment initial expression");
        break;

      case COMPARTMENT_INITIAL_VOLUME_CHANGE:
        setProperty("Initial Volume");
        setText(": Changed compartment initial volume");
        break;

      case COMPARTMENT_SIMULATION_TYPE_CHANGE:
        setProperty("Simulation Type");
        setText(": Changed compartment simulation type");
        break;

      case COMPARTMENT_SPATIAL_DIMENSION_CHANGE:
        setProperty("Spatial Dimensions");
        setText(": Changed compartment spatial dimensions");
        break;

      default:
        break;
    }
}

void CompartmentChangeCommand::redo()
{
  mpWidget->changeValue(mKey, mType, mNew, mIValue);
}

void CompartmentChangeCommand::undo()
{
  mpWidget->changeValue(mKey, mType, mOld, mIValue);
}
