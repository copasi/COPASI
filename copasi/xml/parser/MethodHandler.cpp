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

#include "MethodHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "ParameterGroupHandler.h"
#include "copasi/utilities/CTaskEnum.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiMethod.h"

/**
 * Replace Method with the name type of the handler and implement the
 * three methods below.
 */
MethodHandler::MethodHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Method)
{
  init();
}

// virtual
MethodHandler::~MethodHandler()
{}

// virtual
CXMLHandler * MethodHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  std::string name;
  std::string sType;
  CTaskEnum::Method type;

  switch (mCurrentElement.first)
    {
      case Method:
        name = mpParser->getAttributeValue("name", papszAttrs);
        sType = mpParser->getAttributeValue("type", papszAttrs, "default");
        // first set the type of the with setMethodType of the current task
        // object
        type = CTaskEnum::MethodXML.toEnum(sType, CTaskEnum::Method::UnsetMethod);

        if (type != CTaskEnum::Method::UnsetMethod)
          {
            mpData->pCurrentTask->setMethodType(type);
          }
        else
          {
            // We use the default method for this task and issue a warning
            CCopasiMessage(CCopasiMessage::WARNING, MCXML + 18, sType.c_str(),
                           mpParser->getCurrentLineNumber(),
                           CTaskEnum::MethodXML[mpData->pCurrentTask->getMethod()->getSubType()].c_str());
          }

        mpData->pCurrentTask->getMethod()->setObjectName(name);

        pHandlerToCall = getHandler(ParameterGroup);
        static_cast< ParameterGroupHandler * >(pHandlerToCall)->setDerivedElement(pszName, mpData->pCurrentTask->getMethod());
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool MethodHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Method:
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
CXMLHandler::sProcessLogic * MethodHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Method, HANDLER_COUNT}},
    {"Method", Method, Method, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
