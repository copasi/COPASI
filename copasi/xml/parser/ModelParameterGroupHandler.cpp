// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ModelParameterGroupHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "model/CModelParameterGroup.h"

/**
 * Replace ModelParameterGroup with the name type of the handler and implement the
 * three methods below.
 */
ModelParameterGroupHandler::ModelParameterGroupHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ModelParameterGroup)
{
  init();
}

// virtual
ModelParameterGroupHandler::~ModelParameterGroupHandler()
{}

// virtual
CXMLHandler * ModelParameterGroupHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * CN;
  const char * pType;
  CModelParameter::Type Type;

  switch (mCurrentElement.first)
    {
      case ModelParameterGroup:
        // Element specific code.
        assert(!mpData->ModelParameterGroupStack.empty());

        CN = mpParser->getAttributeValue("cn", papszAttrs);
        pType = mpParser->getAttributeValue("type", papszAttrs);
        Type = toEnum(pType, CModelParameter::TypeNames, CModelParameter::Group);

        {
          CModelParameterGroup * pModelParameterGroup = new CModelParameterGroup(mpData->ModelParameterGroupStack.top(), Type);
          pModelParameterGroup->setCN(std::string(CN));
          mpData->ModelParameterGroupStack.push(pModelParameterGroup);
        }
        break;

      case ModelParameter:
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
bool ModelParameterGroupHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ModelParameterGroup:
        finished = (mLevel == 0);
        mpData->pCurrentModelParameter = mpData->ModelParameterGroupStack.top();
        mpData->ModelParameterGroupStack.pop();
        break;

      case ModelParameter:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  if (mpData->pCurrentModelParameter != NULL)
    {
      mpData->ModelParameterGroupStack.top()->add(mpData->pCurrentModelParameter);
      mpData->pCurrentModelParameter = NULL;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ModelParameterGroupHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ModelParameterGroup, HANDLER_COUNT}},
    {"ModelParameterGroup", ModelParameterGroup, ModelParameterGroup, {ModelParameterGroup, ModelParameter, AFTER, HANDLER_COUNT}},
    {"ModelParameter", ModelParameter, ModelParameter, {ModelParameterGroup, ModelParameter, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
