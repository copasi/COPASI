// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfMetabolitesHandler.h"

/**
 * Replace ListOfMetabolites with the name type of the handler and implement the
 * three methods below.
 */
ListOfMetabolitesHandler::ListOfMetabolitesHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfMetabolites)
{
  init();
}

// virtual
ListOfMetabolitesHandler::~ListOfMetabolitesHandler()
{}

// virtual
CXMLHandler * ListOfMetabolitesHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfMetabolitesHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfMetabolites:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfMetabolitesHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfMetabolites", ListOfMetabolites, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfMetabolites, BEFORE}}
  };

  return Elements;
}
