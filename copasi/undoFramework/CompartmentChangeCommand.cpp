// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <copasi/undoFramework/UndoCompartmentData.h>

CompartmentChangeCommand::CompartmentChangeCommand(CCopasiUndoCommand::Type type,
    const QVariant& oldValue,
    const QVariant& newValue,
    CCopasiObject* pObject,
    CQCompartment* pWidget,
    double iValue /*= std::numeric_limits<double>::quiet_NaN()*/)
  : CCopasiUndoCommand("Compartment", type, "Change", "", TO_UTF8(newValue.toString()), TO_UTF8(oldValue.toString()), pObject->getObjectName())
  , mOld(oldValue)
  , mNew(newValue)
  , mIValue(iValue)
  , mpObject(pObject)
  , mpWidget(pWidget)
  , mpUndoData(NULL)
{
  mKey = pObject->getKey();

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
        mpUndoData = new UndoCompartmentData(dynamic_cast<CCompartment*>(pObject));
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

CompartmentChangeCommand::~CompartmentChangeCommand()
{
  pdelete(mpUndoData);
}

void CompartmentChangeCommand::redo()
{
  mpWidget->changeValue(mKey, mType, mNew, mIValue, NULL);
}

void CompartmentChangeCommand::undo()
{
  mpWidget->changeValue(mKey, mType, mOld, mIValue, mpUndoData);
}
