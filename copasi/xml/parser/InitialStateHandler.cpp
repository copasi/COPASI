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

#include "InitialStateHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CModelValue.h"

/**
 * Replace InitialState with the name type of the handler and implement the
 * three methods below.
 */
InitialStateHandler::InitialStateHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::InitialState)
{
  init();
}

// virtual
InitialStateHandler::~InitialStateHandler()
{}

// virtual
CXMLHandler * InitialStateHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case InitialState:
        pHandlerToCall = getHandler(CharacterData);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool InitialStateHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;
  std::istringstream Values;
  std::string StringValue;
  std::vector< CModelEntity * >::iterator it;
  std::vector< CModelEntity * >::iterator end;
  double Value;

  switch (mCurrentElement.first)
    {
      case InitialState:
        finished = true;
        Values.str(mpData->CharacterData);

        it = mpData->StateVariableList.begin();
        end = mpData->StateVariableList.end();

        for (Values >> StringValue; it != end; ++it, Values >> StringValue)
          {
            if (Values.fail()) break;

            Value = CCopasiXMLInterface::DBL(StringValue.c_str());
            (*it)->setInitialValue(Value);
          }

        if (it != end || !Values.fail() || !Values.eof())
          {
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 17, mpParser->getCurrentLineNumber());
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
CXMLHandler::sProcessLogic * InitialStateHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {InitialState, HANDLER_COUNT}},
    {"InitialState", InitialState, InitialState, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
