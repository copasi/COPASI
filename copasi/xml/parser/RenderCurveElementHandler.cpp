// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "RenderCurveElementHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLRenderPoint.h"
#include "copasi/layout/CLRenderCubicBezier.h"

/**
 * Replace RenderCurveElement with the name type of the handler and implement the
 * three methods below.
 */
RenderCurveElementHandler::RenderCurveElementHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::RenderCurveElement)
{
  init();
}

// virtual
RenderCurveElementHandler::~RenderCurveElementHandler()
{}

// virtual
CXMLHandler * RenderCurveElementHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * X;
  const char * Y;
  const char * Z;
  const char * BP1X;
  const char * BP1Y;
  const char * BP1Z;
  const char * BP2X;
  const char * BP2Y;
  const char * BP2Z;
  CLRenderPoint* pCurveElement = NULL;

  switch (mCurrentElement.first)
    {
      case RenderCurveElement:
        X = mpParser->getAttributeValue("x", papszAttrs);
        Y = mpParser->getAttributeValue("y", papszAttrs);
        Z = mpParser->getAttributeValue("z", papszAttrs, "0.0");
        BP1X = mpParser->getAttributeValue("basePoint1_x", papszAttrs, false);
        BP1Y = mpParser->getAttributeValue("basePoint1_y", papszAttrs, false);
        BP1Z = mpParser->getAttributeValue("basePoint1_z", papszAttrs, "0.0");
        BP2X = mpParser->getAttributeValue("basePoint2_x", papszAttrs, false);
        BP2Y = mpParser->getAttributeValue("basePoint2_y", papszAttrs, false);
        BP2Z = mpParser->getAttributeValue("basePoint2_z", papszAttrs, "0.0");

        // for a cubic bezier, x any y value for both basepoints are mandatory
        if (BP1X != NULL && BP1Y != NULL && BP2X != NULL && BP2Y != NULL)
          {
            pCurveElement = new CLRenderCubicBezier(CLRelAbsVector(BP1X), CLRelAbsVector(BP1Y), CLRelAbsVector(BP1Z),
                                                    CLRelAbsVector(BP2X), CLRelAbsVector(BP2Y), CLRelAbsVector(BP2Z),
                                                    CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z));
          }
        else
          {
            pCurveElement = new CLRenderPoint(CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z));
          }

        mpData->pListOfCurveElements->push_back(pCurveElement);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool RenderCurveElementHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case RenderCurveElement:
        finished = true;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * RenderCurveElementHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {RenderCurveElement, HANDLER_COUNT}},
    {"Element", RenderCurveElement, RenderCurveElement, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
