// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ParameterTextHandler.h"
#include "CXMLParser.h"

#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiParameter.h"

/**
 * Replace ParameterText with the name type of the handler and implement the
 * three methods below.
 */
ParameterTextHandler::ParameterTextHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ParameterText)
{
  init();
}

// virtual
ParameterTextHandler::~ParameterTextHandler()
{}

// virtual
CXMLHandler * ParameterTextHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  std::string name;
  const char * cType;
  CCopasiParameter::Type type;

  switch (mCurrentElement)
    {
      case ParameterText:
        // Parameter has attributes name, type and value
        name = mpParser->getAttributeValue("name", papszAttrs);
        cType = mpParser->getAttributeValue("type", papszAttrs);
        type = toEnum(cType, CCopasiParameter::XMLType, CCopasiParameter::INVALID);

        switch (type)
          {
            case CCopasiParameter::EXPRESSION:
              pHandlerToCall = mpParser->getHandler(CharacterData);
              break;

            default:
              CCopasiMessage(CCopasiMessage::ERROR, MCXML + 16, name.c_str(), cType, mpParser->getCurrentLineNumber());
              break;
          }

        mpData->pCurrentParameter = new CCopasiParameter(name, type, NULL);

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ParameterTextHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ParameterText:
        finished = true;

        if (mpData->pCurrentParameter != NULL)
          {
            mpData->pCurrentParameter->setValue(mpData->CharacterData);
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
CXMLHandler::sProcessLogic * ParameterTextHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, {ParameterText, HANDLER_COUNT}},
    {"ParameterText", ParameterText, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
