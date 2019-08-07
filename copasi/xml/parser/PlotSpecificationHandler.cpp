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

#include "PlotSpecificationHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "ParameterGroupHandler.h"
#include "copasi/plot/COutputDefinitionVector.h"

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
  const char * name;
  const char * sType;
  const char * active;
  const char * taskTypes;
  CCopasiParameterGroup * pGroup = NULL;

  switch (mCurrentElement.first)
    {
      case PlotSpecification:
        // create a new CPlotSpecification element depending on the type
        mpData->pCurrentPlot = new CPlotSpecification();
        name = mpParser->getAttributeValue("name", papszAttrs);
        mpData->pCurrentPlot->setObjectName(name);
        sType = mpParser->getAttributeValue("type", papszAttrs);
        mpData->pCurrentPlot->setType(toEnum(sType, CPlotItem::XMLType, CPlotItem::curve2d));
        active = mpParser->getAttributeValue("active", papszAttrs, "true");
        mpData->pCurrentPlot->setActive(mpParser->toBool(active));

        taskTypes = mpParser->getAttributeValue("taskTypes", papszAttrs, false);

        if (taskTypes != NULL)
          mpData->pCurrentPlot->setTaskTypes(taskTypes);

        break;

      case ParameterGroup:
        pHandlerToCall = getHandler(mCurrentElement.second);
        pGroup = dynamic_cast< CCopasiParameterGroup * >(mpData->pCurrentPlot->getParameter(pszName));

        if (pGroup != NULL)
          static_cast< ParameterGroupHandler * >(pHandlerToCall)->setDerivedElement(pszName, pGroup);

        break;

      case Parameter:
      case ListOfPlotItems:
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
bool PlotSpecificationHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;
  CCopasiParameter* pParameter;

  switch (mCurrentElement.first)
    {
      case PlotSpecification:
        mpData->pPlotList->add(*mpData->pCurrentPlot);
        pdelete(mpData->pCurrentPlot);

        finished = true;
        break;

      case Parameter:
      case ParameterGroup:
        // Check whether a parameter of that name exist
        pParameter = mpData->pCurrentPlot->getParameter(mpData->pCurrentParameter->getObjectName());

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
            mpData->pCurrentPlot->addParameter(mpData->pCurrentParameter);
            mpData->pCurrentParameter = NULL;
          }

        break;

      case ListOfPlotItems:
        break;

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
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {PlotSpecification, HANDLER_COUNT}},
    {"PlotSpecification", PlotSpecification, PlotSpecification, {ParameterGroup, Parameter, ListOfPlotItems, AFTER, HANDLER_COUNT}},
    {"ParameterGroup", ParameterGroup, ParameterGroup, {ParameterGroup, Parameter, ListOfPlotItems, AFTER, HANDLER_COUNT}},
    {"Parameter", Parameter, Parameter, {ParameterGroup, Parameter, ListOfPlotItems, AFTER, HANDLER_COUNT}},
    {"ListOfPlotItems", ListOfPlotItems, ListOfPlotItems, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
