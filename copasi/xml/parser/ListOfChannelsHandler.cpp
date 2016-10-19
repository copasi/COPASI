// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfChannelsHandler.h"

/**
 * Replace ListOfChannels with the name type of the handler and implement the
 * three methods below.
 */
ListOfChannelsHandler::ListOfChannelsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfChannels)
{
  init();
}

// virtual
ListOfChannelsHandler::~ListOfChannelsHandler()
{}

// virtual
CXMLHandler * ListOfChannelsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfChannelsHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ListOfChannelsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfChannels", ListOfChannels, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfChannels, BEFORE}}
  };

  return Elements;
}
