// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "EventChangeCommand.h"

#include <copasi/UI/CQEventWidget1.h>

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CCompartment.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CEvent.h>
#include <copasi/model/CModelValue.h>

#include <copasi/UI/qtUtilities.h>

EventChangeCommand::EventChangeCommand(CCopasiUndoCommand::Type type,
                                       const QVariant& oldValue,
                                       const QVariant& newValue,
                                       CCopasiObject* pObject,
                                       CQEventWidget1* pWidget,
                                       const std::string& oldExpression /*= ""*/,
                                       const std::string& newExpression /*= ""*/)
  : CCopasiUndoCommand("Event", type, "Change", "", TO_UTF8(newValue.toString()), TO_UTF8(oldValue.toString()), pObject->getObjectName())
  , mOld(oldValue)
  , mNew(newValue)
  , mKey(pObject->getKey())
  , mpWidget(pWidget)
  , mOldExpression(oldExpression)
  , mNewExpression(newExpression)
{
  switch (type)
    {
      case EVENT_DELAY_EXPRESSION_CHANGE:
        setProperty("Delay Expression");
        setText(": Changed event delay expression");
        break;

      case EVENT_DELAY_TYPE_CHANGE:
        setProperty("Delay Type");
        setText(": Changed event delay type");
        break;

      case EVENT_TRIGGER_EXPRESSION_CHANGE:
        setProperty("Trigger Expression");
        setText(": Changed event trigger expression");
        break;

      case EVENT_ASSIGNMENT_ADDED:
        setProperty("Event Assignment");
        setText(": Added event assignment");
        break;

      case EVENT_ASSIGNMENT_REMOVED:
        setProperty("Event Assignment");
        setText(": Removed event assignment");
        break;

      case EVENT_ASSIGNMENT_EXPRESSION_CHANGE:
        setProperty("Event Assignment Expression");
        setText(": Changed event assignment expression");
        break;

      default:
        break;
    }
}

void EventChangeCommand::redo()
{
  mpWidget->changeValue(mKey, mType, mNew, mNewExpression);
}

void EventChangeCommand::undo()
{
  mpWidget->changeValue(mKey, mType, mOld, mOldExpression);
}
