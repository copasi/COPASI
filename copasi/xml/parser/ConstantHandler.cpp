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

#include "ConstantHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CReaction.h"

/**
 * Replace Constant with the name type of the handler and implement the
 * three methods below.
 */
ConstantHandler::ConstantHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Constant)
{
  init();
}

// virtual
ConstantHandler::~ConstantHandler()
{}

// virtual
CXMLHandler * ConstantHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Key;
  const char * Name;
  const char * Value;

  switch (mCurrentElement.first)
    {
      case Constant:
        Key = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);
        Value = mpParser->getAttributeValue("value", papszAttrs);

        mpData->pReaction->getParameters().addParameter(Name,
            CCopasiParameter::Type::DOUBLE,
            (C_FLOAT64) CCopasiXMLInterface::DBL(Value));

        addFix(Key, mpData->pReaction->getParameters().getParameter(Name));
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool ConstantHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Constant:
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
CXMLHandler::sProcessLogic * ConstantHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Constant, HANDLER_COUNT}},
    {"Constant", Constant, Constant, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
