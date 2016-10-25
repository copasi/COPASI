// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfFunctionsHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "function/CFunction.h"

/**
 * Replace ListOfFunctions with the name type of the handler and implement the
 * three methods below.
 */
ListOfFunctionsHandler::ListOfFunctionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfFunctions)
{
  init();
}

// virtual
ListOfFunctionsHandler::~ListOfFunctionsHandler()
{}

// virtual
CXMLHandler * ListOfFunctionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ListOfFunctions:
        break;

      case Function:
        pHandlerToCall = getHandler(Function);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ListOfFunctionsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfFunctions:
        finished = true;
        {
          size_t i, imax = mpData->pFunctionList->size();

          for (i = imax - 1; i != C_INVALID_INDEX; i--)
            {
              CFunction * pFunction =
                dynamic_cast<CFunction *>(&mpData->pFunctionList->operator[](i));

              if (pFunction && !pFunction->compile())
                {
                  CCopasiMessage(CCopasiMessage::RAW, MCXML + 6,
                                 pFunction->getObjectName().c_str(),
                                 mpParser->getCurrentLineNumber());
                  // We can keep the function as the compile is later checked again.
                  // mpData->pFunctionList->CCopasiVector< CEvaluationTree >::remove(i);
                }
            }
        }

        break;

      case Function:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfFunctionsHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfFunctions, HANDLER_COUNT}},
    {"ListOfFunctions", ListOfFunctions, ListOfFunctions, {Function, AFTER, HANDLER_COUNT}},
    {"Function", Function, Function, {Function, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
