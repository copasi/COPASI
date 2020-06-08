// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include "ParameterTextHandler.h"
#include "CXMLParser.h"

#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CCopasiParameter.h"

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

  switch (mCurrentElement.first)
    {
      case ParameterText:
        // Parameter has attributes name, type and value
        name = mpParser->getAttributeValue("name", papszAttrs);
        cType = mpParser->getAttributeValue("type", papszAttrs);
        type = CCopasiParameter::XMLType.toEnum(cType, CCopasiParameter::Type::INVALID);

        switch (type)
          {
            case CCopasiParameter::Type::EXPRESSION:
              pHandlerToCall = getHandler(CharacterData);
              break;

            default:
              if (cType != NULL) // in that case the error is logged by the parser
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

  switch (mCurrentElement.first)
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
    {"BEFORE", BEFORE, BEFORE, {ParameterText, HANDLER_COUNT}},
    {"ParameterText", ParameterText, ParameterText, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
