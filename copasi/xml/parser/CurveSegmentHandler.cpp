// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CurveSegmentHandler.h"

/**
 * Replace CurveSegment with the name type of the handler and implement the
 * three methods below.
 */
CurveSegmentHandler::CurveSegmentHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::CurveSegment)
{
  init();
}

// virtual
CurveSegmentHandler::~CurveSegmentHandler()
{}

// virtual
CXMLHandler * CurveSegmentHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool CurveSegmentHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case CurveSegment:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * CurveSegmentHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"CurveSegment", CurveSegment, {BEFORE}},
    {"BEFORE", BEFORE, {CurveSegment, BEFORE}}
  };

  return Elements;
}
