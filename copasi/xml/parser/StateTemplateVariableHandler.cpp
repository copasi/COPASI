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

#include "StateTemplateVariableHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CModelValue.h"

/**
 * Replace StateTemplateVariable with the name type of the handler and implement the
 * three methods below.
 */
StateTemplateVariableHandler::StateTemplateVariableHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::StateTemplateVariable)
{
  init();
}

// virtual
StateTemplateVariableHandler::~StateTemplateVariableHandler()
{}

// virtual
CXMLHandler * StateTemplateVariableHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * ObjectReference;
  CModelEntity * pME;

  switch (mCurrentElement.first)
    {
      case StateTemplateVariable:
        ObjectReference = mpParser->getAttributeValue("objectReference",  papszAttrs);
        pME = dynamic_cast< CModelEntity * >(mpData->mKeyMap.get(ObjectReference));

        if (pME != NULL)
          mpData->StateVariableList.push_back(pME);
        else
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                         mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool StateTemplateVariableHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case StateTemplateVariable:
        finished = true;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * StateTemplateVariableHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {StateTemplateVariable, HANDLER_COUNT}},
    {"StateTemplateVariable", StateTemplateVariable, StateTemplateVariable, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
