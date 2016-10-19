// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "PlotSpecificationHandler.h"

/**
 * Replace PlotSpecification with the name type of the handler and implement the
 * three methods below.
 */
PlotSpecificationHandler::PlotSpecificationHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::PlotSpecification)
{
  init();
}

// virtual
PlotSpecificationHandler::~PlotSpecificationHandler()
{}

// virtual
CXMLHandler * PlotSpecificationHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool PlotSpecificationHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case PlotSpecification:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * PlotSpecificationHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"PlotSpecification", PlotSpecification, {BEFORE}},
    {"BEFORE", BEFORE, {PlotSpecification, BEFORE}}
  };

  return Elements;
}
