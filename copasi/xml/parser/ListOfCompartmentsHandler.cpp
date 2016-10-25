// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfCompartmentsHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "model/CModel.h"

/**
 * Replace ListOfCompartments with the name type of the handler and implement the
 * three methods below.
 */
ListOfCompartmentsHandler::ListOfCompartmentsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfCompartments)
{
  init();
}

// virtual
ListOfCompartmentsHandler::~ListOfCompartmentsHandler()
{}

// virtual
CXMLHandler * ListOfCompartmentsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ListOfCompartments:
        mpData->pModel->getCompartments().clear();
        break;

      case Compartment:
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
bool ListOfCompartmentsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfCompartments:
        finished = true;
        break;

      case Compartment:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfCompartmentsHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfCompartments, HANDLER_COUNT}},
    {"ListOfCompartments", ListOfCompartments, ListOfCompartments, {Compartment, AFTER, HANDLER_COUNT}},
    {"Compartment", Compartment, Compartment, {Compartment, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
