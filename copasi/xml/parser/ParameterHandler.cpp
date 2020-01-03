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

#include "ParameterHandler.h"

#include "CXMLParser.h"
#include "copasi/utilities/CCopasiParameter.h"

/**
 * Replace Parameter with the name type of the handler and implement the
 * three methods below.
 */
ParameterHandler::ParameterHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Parameter)
{
  init();
}

// virtual
ParameterHandler::~ParameterHandler()
{}

// virtual
CXMLHandler * ParameterHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  const char * cValue = NULL;
  const char * cType = NULL;

  std::string name;
  std::string sValue("");
  bool UnmappedKey = false;

  void * pValue = NULL;
  CCopasiParameter::Type type;

  C_FLOAT64 d;
  C_INT32 i;
  size_t ui;
  bool b;

  switch (mCurrentElement.first)
    {
      case Parameter:
        // Parameter has attributes name, type and value
        name = mpParser->getAttributeValue("name", papszAttrs);
        cType = mpParser->getAttributeValue("type", papszAttrs);
        type = CCopasiParameter::XMLType.toEnum(cType, CCopasiParameter::Type::INVALID);
        cValue = mpParser->getAttributeValue("value", papszAttrs);

        if (cValue != NULL)
          {
            sValue = cValue;
          }

        switch (type)
          {
            case CCopasiParameter::Type::DOUBLE:
              d = CCopasiXMLInterface::DBL(sValue.c_str());
              pValue = &d;
              break;

            case CCopasiParameter::Type::UDOUBLE:
              d = CCopasiXMLInterface::DBL(sValue.c_str());
              pValue = &d;
              break;

            case CCopasiParameter::Type::INT:
              i = strToInt(sValue.c_str());
              pValue = &i;
              break;

            case CCopasiParameter::Type::UINT:
              ui = strToUnsignedInt(sValue.c_str());
              pValue = &ui;
              break;

            case CCopasiParameter::Type::BOOL:

              if (sValue == "0" || sValue == "false")
                {
                  b = false;
                }
              else
                {
                  b = true;
                }

              pValue = &b;
              break;

            case CCopasiParameter::Type::STRING:
            case CCopasiParameter::Type::FILE:
            case CCopasiParameter::Type::CN:
              pValue = &sValue;
              break;

            case CCopasiParameter::Type::KEY:
            {
              if (sValue != "" &&
                  CKeyFactory::isValidKey(sValue))
                {
                  CDataObject * pObject = mpData->mKeyMap.get(sValue);

                  if (pObject)
                    {
                      sValue = pObject->getKey();
                    }
                  else
                    {
                      UnmappedKey = true;
                    }
                }

              pValue = &sValue;
            }
            break;

            default:
              if (cType != NULL) // otherwise missing attribute will have been logged
                CCopasiMessage(CCopasiMessage::ERROR, MCXML + 16, name.c_str(), cType, mpParser->getCurrentLineNumber());

              pValue = NULL;
              break;
          }

        mpData->pCurrentParameter = new CCopasiParameter(name, type, pValue);

        if (UnmappedKey)
          {
            mpData->UnmappedKeyParameters.push_back(mpData->pCurrentParameter->getKey());
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
bool ParameterHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Parameter:
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
CXMLHandler::sProcessLogic * ParameterHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Parameter, HANDLER_COUNT}},
    {"Parameter", Parameter, Parameter, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
