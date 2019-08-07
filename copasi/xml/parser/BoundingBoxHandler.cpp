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

#include "BoundingBoxHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLBase.h"

BoundingBoxHandler::BoundingBoxHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::BoundingBox)
{
  init();

  if (mpData->pBoundingBox == NULL)
    {
      mpData->pBoundingBox = new CLBoundingBox();
    }
}

// virtual
BoundingBoxHandler::~BoundingBoxHandler()
{
  pdelete(mpData->pBoundingBox);
}

// virtual
CXMLHandler * BoundingBoxHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case BoundingBox:
        break;

      case Position:
      case Dimensions:
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
bool BoundingBoxHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case BoundingBox:
        finished = true;
        break;

      case Position:
        mpData->pBoundingBox->setPosition(*mpData->pPosition);
        break;

      case Dimensions:
        mpData->pBoundingBox->setDimensions(*mpData->pDimensions);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * BoundingBoxHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {BoundingBox, HANDLER_COUNT}},
    {"BoundingBox", BoundingBox, BoundingBox, {Position, HANDLER_COUNT}},
    {"Position", Position, Point, {Dimensions, HANDLER_COUNT}},
    {"Dimensions", Dimensions, Dimensions, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
