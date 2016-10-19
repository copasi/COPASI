// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfUnsupportedAnnotationsHandler.h"

/**
 * Replace ListOfUnsupportedAnnotations with the name type of the handler and implement the
 * three methods below.
 */
ListOfUnsupportedAnnotationsHandler::ListOfUnsupportedAnnotationsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfUnsupportedAnnotations)
{
  init();
}

// virtual
ListOfUnsupportedAnnotationsHandler::~ListOfUnsupportedAnnotationsHandler()
{}

// virtual
CXMLHandler * ListOfUnsupportedAnnotationsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfUnsupportedAnnotationsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfUnsupportedAnnotations:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfUnsupportedAnnotationsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfUnsupportedAnnotations, BEFORE}}
  };

  return Elements;
}
