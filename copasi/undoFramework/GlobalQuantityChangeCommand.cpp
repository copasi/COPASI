// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "GlobalQuantityChangeCommand.h"

#include <copasi/UI/CQModelValue.h>

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CCompartment.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CEvent.h>
#include <copasi/model/CModelValue.h>

#include <copasi/UI/qtUtilities.h>

GlobalQuantityChangeCommand::GlobalQuantityChangeCommand(CCopasiUndoCommand::Type type,
    const QVariant& oldValue,
    const QVariant& newValue,
    CCopasiObject* pObject,
    CQModelValue* pWidget,
    double iValue /*= std::numeric_limits<double>::quiet_NaN()*/)
  : CCopasiUndoCommand("Global Quantity", type, "Change", "", TO_UTF8(newValue.toString()), TO_UTF8(oldValue.toString()), pObject->getObjectName())
  , mOld(oldValue)
  , mNew(newValue)
  , mKey(pObject->getKey())
  , mpWidget(pWidget)
  , mIValue(iValue)
{
  switch (type)
    {
      case GLOBALQUANTITY_EXPRESSION_CHANGE:
        setProperty("Expression");
        setText(": Changed global quantity expression");
        break;

      case GLOBALQUANTITY_INITIAL_EXPRESSION_CHANGE:
        setProperty("Initial Expression");
        setText(": Changed global quantity initial expression");
        break;

      case GLOBALQUANTITY_INITIAL_VALUE_CHANGE:
        setProperty("Initial Value");
        setText(": Changed global quantity initial value");
        break;

      case GLOBALQUANTITY_SIMULATION_TYPE_CHANGE:
        setProperty("Simulation Type");
        setText(": Changed global quantity simulation type");
        break;

      case GLOBALQUANTITY_UNIT_CHANGE:
        setProperty("Unit");
        setText(": Changed global quantity unit");
        break;

      default:
        break;
    }
}

GlobalQuantityChangeCommand::~GlobalQuantityChangeCommand()
{

}

void GlobalQuantityChangeCommand::redo()
{
  mpWidget->changeValue(mKey, mType, mNew, mIValue);
}

void GlobalQuantityChangeCommand::undo()
{
  mpWidget->changeValue(mKey, mType, mOld, mIValue);
}
