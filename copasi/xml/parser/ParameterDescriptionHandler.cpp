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

#include "ParameterDescriptionHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/function/CFunction.h"

/**
 * Replace ParameterDescription with the name type of the handler and implement the
 * three methods below.
 */
ParameterDescriptionHandler::ParameterDescriptionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ParameterDescription)
{
  init();
}

// virtual
ParameterDescriptionHandler::~ParameterDescriptionHandler()
{}

// virtual
CXMLHandler * ParameterDescriptionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Key;
  const char * Name;
  const char * order;
  unsigned C_INT32 Order;
  const char * role; /*substrate, product, modifier, constant, other*/
  CFunctionParameter::Role Role;
  const char * minOccurs;
  unsigned C_INT32 MinOccurs;
  const char * maxOccurs;
  unsigned C_INT32 MaxOccurs;

  //std::string Usage[] = {"SUBSTRATE", "PRODUCT", "MODIFIER", "PARAMETER"};
  CFunctionParameter * pParm = NULL;
  CFunction * pFunction = dynamic_cast<CFunction *>(mpData->pFunction);

  switch (mCurrentElement.first)
    {
      case ParameterDescription:
        Key = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);

        order = mpParser->getAttributeValue("order", papszAttrs);
        Order = (unsigned C_INT32) atoi(order);

        role = mpParser->getAttributeValue("role", papszAttrs);
        Role = CFunctionParameter::RoleNameXML.toEnum(role, CFunctionParameter::Role::VARIABLE);
        //if (Role == "") fatalError();

        minOccurs = mpParser->getAttributeValue("minOccurs", papszAttrs, "1");
        MinOccurs = strToUnsignedInt(minOccurs);

        maxOccurs = mpParser->getAttributeValue("maxOccurs", papszAttrs, "1");

        if (std::string("unbounded") == std::string(maxOccurs))
          MaxOccurs = (unsigned C_INT32) - 1;
        else
          MaxOccurs = strToUnsignedInt(maxOccurs);

        if (mpData->mPredefinedFunction)
          {
            addFix(Key, pFunction->getVariables()[Name]);
          }
        else if (pFunction != NULL)
          {
            // If we are here we have a user defined function.
            // We need to check whether the variable exists within the function.
            size_t Index =
              pFunction->getVariables().findParameterByName(Name);

            bool isUsed = true;

            if (Index == C_INVALID_INDEX)
              {
                // We add the missing parameter and mark it as unused.
                pFunction->getVariables().add(Name,
                                              CFunctionParameter::DataType::FLOAT64,
                                              Role);

                Index = pFunction->getVariables().findParameterByName(Name);
                isUsed = false;
              }

            // Make sure that we have enough parameter to swap
            size_t Counter = 0;

            while (Order >= pFunction->getVariables().size())
              {
                std::string NewName = StringPrint("TMP_%d", Counter++);

                while (!pFunction->getVariables().add(NewName,
                                                      CFunctionParameter::DataType::FLOAT64,
                                                      CFunctionParameter::Role::TEMPORARY)) {};

                NewName = StringPrint("TMP_%d", Counter++);
              }

            // Assure that the order is correct
            if (Order != Index)
              pFunction->getVariables().swap(Order, Index);

            pParm = pFunction->getVariables()[Order];
            pParm->setObjectName(Name);
            pParm->setUsage(Role);
            pParm->setIsUsed(isUsed);

            if (MaxOccurs == 1 && MinOccurs == 1)
              pParm->setType(CFunctionParameter::DataType::FLOAT64);
            else
              pParm->setType(CFunctionParameter::DataType::VFLOAT64);

            mpData->mFunctionParameterKeyMap[Order] = Key;
          }
        else
          {
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                           mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
          }

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool ParameterDescriptionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ParameterDescription:
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
CXMLHandler::sProcessLogic * ParameterDescriptionHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ParameterDescription, HANDLER_COUNT}},
    {"ParameterDescription", ParameterDescription, ParameterDescription, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
