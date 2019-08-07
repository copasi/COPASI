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

#include "AssignmentHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CModel.h"

/**
 * Replace Assignment with the name type of the handler and implement the
 * three methods below.
 */
AssignmentHandler::AssignmentHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Assignment)
{
  init();
}

// virtual
AssignmentHandler::~AssignmentHandler()
{}

// virtual
CXMLHandler * AssignmentHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Key;
  const char * TargetCStr;
  std::string Target;

  const CModelEntity* pME = NULL;

  switch (mCurrentElement.first)
    {
      case Assignment:
        mpData->pEventAssignment = NULL;
        TargetCStr = mpParser->getAttributeValue("target", papszAttrs, false);

        if (TargetCStr != NULL)
          Target = TargetCStr;

        if (Target.empty())
          {
            Key = mpParser->getAttributeValue("targetKey", papszAttrs);
            pME = dynamic_cast<const CModelEntity *>(mpData->mKeyMap.get(Key));

            if (pME != NULL)
              {
                Target = pME->getCN();
              }
          }

        if (!Target.empty() &&
            mpData->pEvent->getAssignments().getIndex(Target) == C_INVALID_INDEX)
          {
            mpData->pEventAssignment = new CEventAssignment(Target);
            mpData->pEvent->getAssignments().add(mpData->pEventAssignment, true);
          }

        break;

      case Expression:
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
bool AssignmentHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Assignment:
        finished = true;
        break;

      case Expression:

      {
        size_t Size = CCopasiMessage::size();

        if (mpData->pEventAssignment != NULL)
          mpData->pEventAssignment->setExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          {
            CCopasiMessage::getLastMessage();
          }
      }

      break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * AssignmentHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Assignment, HANDLER_COUNT}},
    {"Assignment", Assignment, Assignment, {Expression, AFTER, HANDLER_COUNT}},
    {"Expression", Expression, CharacterData, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
