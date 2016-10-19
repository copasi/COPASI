// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ChannelSpecHandler.h"

/**
 * Replace ChannelSpec with the name type of the handler and implement the
 * three methods below.
 */
ChannelSpecHandler::ChannelSpecHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ChannelSpec)
{
  init();
}

// virtual
ChannelSpecHandler::~ChannelSpecHandler()
{}

// virtual
CXMLHandler * ChannelSpecHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ChannelSpecHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ChannelSpecHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ChannelSpec", ChannelSpec, {BEFORE}},
    {"BEFORE", BEFORE, {ChannelSpec, BEFORE}}
  };

  return Elements;
}
