// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "EventHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/utilities/CVersion.h"
#include "copasi/model/CModel.h"

/**
 * Replace Event with the name type of the handler and implement the
 * three methods below.
 */
EventHandler::EventHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Event),
  mKey()
{
  init();
}

// virtual
EventHandler::~EventHandler()
{}

// virtual
CXMLHandler * EventHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Name;
  bool DelayAssignment;
  bool FireAtInitialTime;
  bool PersistentTrigger;

  switch (mCurrentElement.first)
    {
      case Event:
        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);
        DelayAssignment =
          mpParser->toBool(mpParser->getAttributeValue("delayAssignment", papszAttrs, false));
        FireAtInitialTime =
          mpParser->toBool(mpParser->getAttributeValue("fireAtInitialTime", papszAttrs, false));

        if (mpData->pVersion->getVersionDevel() <= 90)
          {
            PersistentTrigger = true;
          }
        else
          {
            PersistentTrigger = mpParser->toBool(mpParser->getAttributeValue("persistentTrigger", papszAttrs, true));
          }

        mpData->pEvent = new CEvent();
        addFix(mKey, mpData->pEvent);
        mpData->pEvent->setObjectName(Name);
        mpData->pEvent->setDelayAssignment(DelayAssignment);
        mpData->pEvent->setFireAtInitialTime(FireAtInitialTime);
        mpData->pEvent->setPersistentTrigger(PersistentTrigger);

        mpData->pModel->getEvents().add(mpData-> pEvent, true);
        break;

      case MiriamAnnotation:
      case Comment:
      case TriggerExpression:
      case DelayExpression:
      case PriorityExpression:
      case ListOfAssignments:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case ListOfUnsupportedAnnotations:
        mpData->mUnsupportedAnnotations.clear();
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool EventHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Event:
        finished = true;
        break;

      case MiriamAnnotation:
        mpData->pEvent->setMiriamAnnotation(mpData->CharacterData, mpData->pEvent->getKey(), mKey);
        mpData->CharacterData = "";
        break;

      case Comment:
        mpData->pEvent->setNotes(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:
        mpData->pEvent->getUnsupportedAnnotations() = mpData->mUnsupportedAnnotations;

        break;

      case TriggerExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpData->pEvent->setTriggerExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          {
            CCopasiMessage msg = CCopasiMessage::getLastMessage();
          }
      }

      break;

      case DelayExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpData->pEvent->setDelayExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          {
            CCopasiMessage msg = CCopasiMessage::getLastMessage();
          }
      }

      break;

      case PriorityExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpData->pEvent->setPriorityExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          {
            CCopasiMessage msg = CCopasiMessage::getLastMessage();
          }
      }

      break;

      case ListOfAssignments:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * EventHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Event, HANDLER_COUNT}},
    {"Event", Event, Event, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, TriggerExpression, DelayExpression, PriorityExpression, ListOfAssignments, AFTER, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {Comment, ListOfUnsupportedAnnotations, TriggerExpression, DelayExpression, PriorityExpression, ListOfAssignments, AFTER, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {ListOfUnsupportedAnnotations, TriggerExpression, DelayExpression, PriorityExpression, ListOfAssignments, AFTER, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {TriggerExpression, DelayExpression, PriorityExpression, ListOfAssignments, AFTER, HANDLER_COUNT}},
    {"TriggerExpression", TriggerExpression, CharacterData, {DelayExpression, PriorityExpression, ListOfAssignments, AFTER, HANDLER_COUNT}},
    {"DelayExpression", DelayExpression, CharacterData, {PriorityExpression, ListOfAssignments, AFTER, HANDLER_COUNT}},
    {"PriorityExpression", PriorityExpression, CharacterData, {ListOfAssignments, AFTER, HANDLER_COUNT}},
    {"ListOfAssignments", ListOfAssignments, ListOfAssignments, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
