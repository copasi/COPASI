// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CompartmentHandler.h"

/**
 * Replace Compartment with the name type of the handler and implement the
 * three methods below.
 */
CompartmentHandler::CompartmentHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Compartment)
{
  init();
}

// virtual
CompartmentHandler::~CompartmentHandler()
{}

// virtual
CXMLHandler * CompartmentHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool CompartmentHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * CompartmentHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Compartment", Compartment, {BEFORE}},
    {"BEFORE", BEFORE, {Compartment, BEFORE}}
  };

  return Elements;
}
