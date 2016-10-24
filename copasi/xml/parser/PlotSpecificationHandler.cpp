// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "PlotSpecificationHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

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

  switch (mCurrentElement.first)
    {
      case PlotSpecification:
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool PlotSpecificationHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case PlotSpecification:
        finished = true;
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * PlotSpecificationHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {PlotSpecification, HANDLER_COUNT}},
    {"PlotSpecification", PlotSpecification, PlotSpecification, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
