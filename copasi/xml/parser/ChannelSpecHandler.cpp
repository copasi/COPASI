// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include "ChannelSpecHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/plot/CPlotItem.h"

/**
 * Replace ChannelSpec with the name type of the handler and implement the
 * three methods below.
 */
ChannelSpecHandler::ChannelSpecHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ChannelSpec)
{
  init();
}

// virtual
ChannelSpecHandler::~ChannelSpecHandler()
{}

// virtual
CXMLHandler * ChannelSpecHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  std::string name;
  double min;
  double max;
  const char* sMin;
  const char* sMax;

  switch (mCurrentElement.first)
    {
      case ChannelSpec:
        name = mpParser->getAttributeValue("cn", papszAttrs);

        mpData->pCurrentChannelSpec = new CPlotDataChannelSpec(name);
        sMin = mpParser->getAttributeValue("min", papszAttrs, false);

        if (sMin == NULL)
          {
            mpData->pCurrentChannelSpec->minAutoscale = true;
          }
        else
          {
            min = CCopasiXMLInterface::DBL(sMin);
            mpData->pCurrentChannelSpec->min = min;
          }

        sMax = mpParser->getAttributeValue("max", papszAttrs, false);

        if (sMax == NULL)
          {
            mpData->pCurrentChannelSpec->maxAutoscale = true;
          }
        else
          {
            max = CCopasiXMLInterface::DBL(sMax);
            mpData->pCurrentChannelSpec->max = max;
          }

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ChannelSpecHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ChannelSpec:
        mpData->pCurrentPlotItem->getChannels().push_back(*(mpData->pCurrentChannelSpec));
        pdelete(mpData->pCurrentChannelSpec);
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
CXMLHandler::sProcessLogic * ChannelSpecHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ChannelSpec, HANDLER_COUNT}},
    {"ChannelSpec", ChannelSpec, ChannelSpec, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
