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

#include "GradientStopHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"

GradientStopHandler::GradientStopHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::GradientStop)
{
  init();
}

// virtual
GradientStopHandler::~GradientStopHandler()
{}

// virtual
CXMLHandler * GradientStopHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Offset;
  const char * StopColor;
  CLGradientStop Stop;

  switch (mCurrentElement.first)
    {
      case GradientStop:
        Offset = mpParser->getAttributeValue("offset", papszAttrs);
        StopColor = mpParser->getAttributeValue("stop-color", papszAttrs);

        Stop.setOffset(Offset);
        Stop.setStopColor(StopColor);
        mpData->pGradient->addGradientStop(&Stop);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool GradientStopHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case GradientStop:
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
CXMLHandler::sProcessLogic * GradientStopHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {GradientStop, HANDLER_COUNT}},
    {"Stop", GradientStop, GradientStop, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
