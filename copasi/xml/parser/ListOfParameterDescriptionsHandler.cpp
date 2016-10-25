// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfParameterDescriptionsHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "function/CFunction.h"

/**
 * Replace ListOfParameterDescriptions with the name type of the handler and implement the
 * three methods below.
 */
ListOfParameterDescriptionsHandler::ListOfParameterDescriptionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfParameterDescriptions)
{
  init();
}

// virtual
ListOfParameterDescriptionsHandler::~ListOfParameterDescriptionsHandler()
{}

// virtual
CXMLHandler * ListOfParameterDescriptionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ListOfParameterDescriptions:
        mpData->mFunctionParameterKeyMap.clear();
        break;

      case ParameterDescription:
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
bool ListOfParameterDescriptionsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfParameterDescriptions:
        finished = true;

        // We need to remove all parameters which have been temporarily added to the list of variables
        {
          CFunction * pFunction = dynamic_cast<CFunction *>(mpData->pFunction);

          if (pFunction)
            {
              CFunctionParameters & Variables = pFunction->getVariables();
              size_t i = Variables.size() - 1;

              for (; i != C_INVALID_INDEX && Variables[i]->getUsage() == CFunctionParameter::TEMPORARY; i--)
                Variables.remove(Variables[i]->getObjectName());
            }
        }

        break;

      case ParameterDescription:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfParameterDescriptionsHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfParameterDescriptions, HANDLER_COUNT}},
    {"ListOfParameterDescriptions", ListOfParameterDescriptions, ListOfParameterDescriptions, {ParameterDescription, AFTER, HANDLER_COUNT}},
    {"ParameterDescription", ParameterDescription, ParameterDescription, {ParameterDescription, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
