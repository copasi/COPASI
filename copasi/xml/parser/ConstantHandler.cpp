// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ConstantHandler.h"

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
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ConstantHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case COPASI:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ConstantHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Constant", Constant, {BEFORE}},
    {"BEFORE", BEFORE, {Constant, BEFORE}}
  };

  return Elements;
}
