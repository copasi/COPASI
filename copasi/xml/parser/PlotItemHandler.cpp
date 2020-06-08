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

#include "PlotItemHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "ParameterGroupHandler.h"
#include "copasi/plot/CPlotSpecification.h"

PlotItemHandler::PlotItemHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::PlotItem)
{
  init();
}

// virtual
PlotItemHandler::~PlotItemHandler()
{}

// virtual
CXMLHandler * PlotItemHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  std::string name;
  std::string sType;
  CCopasiParameterGroup * pGroup = NULL;

  switch (mCurrentElement.first)
    {
      case PlotItem:
        // create a new CPlotSpecification element depending on the type
        name = mpParser->getAttributeValue("name", papszAttrs);
        sType = mpParser->getAttributeValue("type", papszAttrs);
        mpData->pCurrentPlotItem =
          mpData->pCurrentPlot->createItem(name, toEnum(sType.c_str(), CPlotItem::XMLType, CPlotItem::unset));

        break;

      case ParameterGroup:
        pHandlerToCall = getHandler(mCurrentElement.second);
        pGroup = dynamic_cast< CCopasiParameterGroup * >(mpData->pCurrentPlot->getParameter(pszName));

        if (pGroup != NULL)
          static_cast< ParameterGroupHandler * >(pHandlerToCall)->setDerivedElement(pszName, pGroup);

        break;

      case Parameter:
      case ListOfChannels:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool PlotItemHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;
  CCopasiParameter * pParameter = NULL;

  switch (mCurrentElement.first)
    {
      case PlotItem:
        mpData->pCurrentPlotItem = NULL;
        finished = true;
        break;

      case Parameter:
      case ParameterGroup:
        // Check whether a parameter of that name exist
        pParameter = mpData->pCurrentPlotItem->getParameter(mpData->pCurrentParameter->getObjectName());

        if (pParameter != NULL)
          {
            *pParameter = *mpData->pCurrentParameter;

            if (pParameter != mpData->pCurrentParameter)
              {
                pdelete(mpData->pCurrentParameter);
              }
            else
              {
                mpData->pCurrentParameter = NULL;
              }
          }
        else
          {
            mpData->pCurrentPlotItem->addParameter(mpData->pCurrentParameter);
            mpData->pCurrentParameter = NULL;
          }

        break;

      case ListOfChannels:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * PlotItemHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {PlotItem, HANDLER_COUNT}},
    {"PlotItem", PlotItem, PlotItem, {ParameterGroup, Parameter, ListOfChannels, AFTER, HANDLER_COUNT}},
    {"ParameterGroup", ParameterGroup, ParameterGroup, {ParameterGroup, Parameter, ListOfChannels, AFTER, HANDLER_COUNT}},
    {"Parameter", Parameter, Parameter, {ParameterGroup, Parameter, ListOfChannels, AFTER, HANDLER_COUNT}},
    {"ListOfChannels", ListOfChannels, ListOfChannels, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
