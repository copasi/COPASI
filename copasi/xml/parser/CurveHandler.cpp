// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CurveHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "layout/CLCurve.h"

/**
 * Replace Curve with the name type of the handler and implement the
 * three methods below.
 */
CurveHandler::CurveHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Curve)
{
  init();

  if (mpData->pCurve == NULL)
    {
      mpData->pCurve = new CLCurve();
    }
}

// virtual
CurveHandler::~CurveHandler()
{
  pdelete(mpData->pCurve);
}

// virtual
CXMLHandler * CurveHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case Curve:
        mpData->pCurve->clear();
        break;

      case ListOfCurveSegments:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool CurveHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Curve:
        finished = true;
        break;

      case ListOfCurveSegments:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * CurveHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Curve, HANDLER_COUNT}},
    {"Curve", Curve, Curve, {ListOfCurveSegments, HANDLER_COUNT}},
    {"ListOfCurveSegments", ListOfCurveSegments, ListOfCurveSegments, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
